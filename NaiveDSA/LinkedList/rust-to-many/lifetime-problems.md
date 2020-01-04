## Pop

最早实现 `pop` 的时候，我被生命周期炸了：

```rust
 		pub fn pop(&mut self) -> Option<T> {
        match &mut self.head {
            // self.head == null
            Link::Nil => None,
            Link::Node(s) => {
                // head = head->next;
                // return old head
                let (val, next) = (s.val, s.next);
                self.head = next;
                Some(val)
            }
        }
		}
```

如果 val 并非是能 clone 的话，明显有：

1. `s` is `&mut Link::Node`
2. `val` is `&T`, `next` is `&mut Link<T>`
3. `Some(val)` 如果在 T 是 `clone ` 的时候才行

这个时候可以看看 `mem::replace`, 这玩意能帮我们：https://github.com/rust-unofficial/patterns/blob/master/idioms/mem-replace.md

最后可以实现成这样：

```rust
        // operation with head.
        mem::replace(&mut self.head, None).map(|node| {
            self.head = node.next;
            node.val
        })
```

## `as_ref`

```rust
match &self.head {
    None => None,
    Some(node) => Some(&node.val),
}
```

`self.head.map` 中，map 的签名是：

```rust
pub fn map<U, F: FnOnce(T) -> U>(self, f: F) -> Option<U>;
```

所以必要时应该提供一个 `as_ref`

## Drop 和 Into

```rust
impl<T> IntoIterator for List<T> {
    type Item = T;
    type IntoIter = ListIntoIter<T>;

    fn into_iter(self) -> Self::IntoIter {
        //        let n = ListIntoIter {
        //            current_head: self.head,
        //        };
        //        mem::forget(self);
        //        n
        ListIntoIter { current_head: self }
    }
}
```

其实我一开始试图让 `ListIntoIter` 和  `ListIntoIter` 有同样的成员，然后 drop ... 再实现一遍，拿到 head 就行，对 List 用 `mem::forget`. 总觉得这个有点像 C++ 的 move constructor, 正确实现掏空资源/swap 就行。不过这里换了个实现...就是把 self 整个给打包走...

然后问题出现了：

```
error[E0509]: cannot move out of type `first::List<T>`, which implements the `Drop` trait
   --> src/first.rs:128:19
    |
128 |             head: self.head,
    |                   ^^^^^^^^^
    |                   |
    |                   cannot move out of here
    |                   move occurs because `self.head` has type `std::option::Option<std::boxed::Box<first::Node<T>>>`, which does not implement the `Copy` trait

```

好吧，实际上要实现我上述的逻辑没准可以：

```rust
    #[cfg(test)]
    pub fn fuck_tp(mut self) -> FuckTp<T> {
        let head = mem::replace(&mut self.head, None);
        mem::forget(self);
        FuckTp {
            head,
        }
    }
```

这样似乎能够比较好的处理，感觉即使不 forget 也是安全的。不过最终参考实现：

```rust
#[cfg(test)]
pub struct FuckTp<T> {
    head: Link<T>
}

#[cfg(test)]
pub struct ListIntoIter<T>(List<T>);
```

总觉得这个直接包裹 `List` 的明显就优雅多了（哭）。

这个可以看看 Rust 的 newtype pattern: https://github.com/rust-unofficial/patterns/blob/master/patterns/newtype.md 

如果要实现一个用 `mem::forget` 的 `into_iter`, 可以参考：

```rust
    #[inline]
    fn into_iter(mut self) -> IntoIter<T> {
        unsafe {
            let begin = self.as_mut_ptr();
            let end = if mem::size_of::<T>() == 0 {
                arith_offset(begin as *const i8, self.len() as isize) as *const T
            } else {
                begin.add(self.len()) as *const T
            };
            let cap = self.buf.capacity();
            mem::forget(self);
            IntoIter {
                buf: NonNull::new_unchecked(begin),
                phantom: PhantomData,
                cap,
                ptr: begin,
                end,
            }
        }
    }
```

Vec 的 IntoIter 也实现了 Drop:

```rust
#[stable(feature = "rust1", since = "1.0.0")]
unsafe impl<#[may_dangle] T> Drop for IntoIter<T> {
    fn drop(&mut self) {
        // destroy the remaining elements
        for _x in self.by_ref() {}

        // RawVec handles deallocation
        let _ = unsafe { RawVec::from_raw_parts(self.buf.as_ptr(), self.cap) };
    }
}
```



```rust
#[stable(feature = "rust1", since = "1.0.0")]
unsafe impl<#[may_dangle] T> Drop for Vec<T> {
    fn drop(&mut self) {
        unsafe {
            // use drop for [T]
            ptr::drop_in_place(&mut self[..]);
        }
        // RawVec handles deallocation
    }
}
```

我真不知道哪个好 = =, 哎，看实现吧。

## Iter && IterMut

```rust
pub struct ListIter<'a, T> {
    current_iter: &'a Link<T>,
}

impl<'a, T> Iterator for ListIter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<Self::Item> {
        //        match self.current_iter {
        //            None => None,
        //            Some(node) => {
        //                let v = Some(&node.val);
        //                self.current_iter = &node.next;
        //                v
        //            }
        //        }

        //        self.current_iter.map(|node| {
        //            self.current_iter = &node.next;
        //            &node.val
        //        })

        self.current_iter.as_ref().map(|node| {
            self.current_iter = &node.next;
            &node.val
        })
    }
}
```

这个其实没啥问题，被 Comment 的两端都可以编译。但是换成 Mut 就不行了，我遇到了这个问题：https://stackoverflow.com/questions/57036513/rust-errore0495-cannot-infer-an-appropriate-lifetime-for-autoref-due-to-conf

这里有一些奇葩东西：

* `take` vs `as_ref`:
  * 