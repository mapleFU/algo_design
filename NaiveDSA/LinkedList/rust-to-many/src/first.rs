use std::mem;

pub struct Node<T> {
    val: T,
    next: Link<T>,
}

pub type Link<T> = Option<Box<Node<T>>>;

pub struct List<T> {
    head: Link<T>,
}

impl<T> Default for List<T> {
    fn default() -> Self {
        List { head: None }
    }
}

impl<T> List<T> {
    pub fn push(&mut self, t: T) {
        let new_node = Node {
            val: t,
            // head first replace as 0
            next: mem::replace(&mut self.head, None),
        };
        // then fill new val to it.
        self.head = Some(Box::new(new_node));
    }

    pub fn pop(&mut self) -> Option<T> {
        // operation with head.
        mem::replace(&mut self.head, None).map(|node| {
            self.head = node.next;
            node.val
        })
    }

    pub fn peek(&self) -> Option<&T> {
        self.head.as_ref().map(|node| &node.val)
    }
}

impl<T> Drop for List<T> {
    fn drop(&mut self) {
        while let Some(node) = mem::replace(&mut self.head, None) {
            mem::replace(&mut self.head, node.next);
        }
    }
}

pub struct ListIntoIter<T> {
    current_head: List<T>,
}

impl<T> Iterator for ListIntoIter<T> {
    type Item = T;

    fn next(&mut self) -> Option<Self::Item> {
        self.current_head.pop()
    }
}

impl<T> IntoIterator for List<T> {
    type Item = T;
    type IntoIter = ListIntoIter<T>;

    fn into_iter(self) -> Self::IntoIter {
        //                let n = ListIntoIter {
        //                    current_head: self.head,
        //                };
        //                mem::forget(self);
        //                n
        ListIntoIter { current_head: self }
    }
}

pub struct ListIter<'a, T> {
    current_iter: &'a Link<T>,
}

impl<'a, T> Iterator for ListIter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<Self::Item> {
        // 1. as_ref got an ref of `Link<T>`.
        // 2. map take and clone it, it's &Box<Node<T>>
        // 3. self.current_iter = &node.next, changes of multiple ref.
        self.current_iter.as_ref().map(|node| {
            self.current_iter = &node.next;
            &node.val
        })
    }
}

#[cfg(test)]
#[allow(unused)]
pub struct FuckTp<T> {
    head: Link<T>,
}

impl<T> List<T> {
    pub fn iter(&self) -> ListIter<T> {
        ListIter {
            current_iter: &self.head,
        }
    }

    pub fn iter_mut(&mut self) -> ListMutIter<T> {
        ListMutIter {
            current_iter: self.head.as_mut(),
        }
    }

    #[cfg(test)]
    pub fn fuck_tp(mut self) -> FuckTp<T> {
        let head = mem::replace(&mut self.head, None);
        mem::forget(self);
        FuckTp { head }
    }

    pub fn iter_mut2(&mut self) -> NmMutIter<T> {
        NmMutIter {
            current_iter: &mut self.head,
        }
    }
}

pub struct ListMutIter<'a, T> {
    current_iter: Option<&'a mut Box<Node<T>>>,
}

impl<'a, T> Iterator for ListMutIter<'a, T> {
    type Item = &'a mut T;

    fn next(&mut self) -> Option<&'a mut T> {
        // 1. take make `current_iter` as None, and map get it content.
        // 2. `node` is a `&mut Box<Node<T>>` with lifetime `'a`.
        // 3. change current and return value with lifetime `'a`.
        self.current_iter.take().map(|node| {
            self.current_iter = node.next.as_mut();
            &mut node.val
        })
    }
}

#[allow(unused)]
pub struct NmMutIter<'a, T> {
    current_iter: &'a mut Link<T>,
}

impl<'a, T> Iterator for NmMutIter<'a, T> {
    type Item = &'a mut T;

    fn next(&mut self) -> Option<Self::Item> {
        // 这里 take 了 reference, 然后返回，相当于返回 mut ref.
        //        self.current_iter.as_mut().map(|mut node| {
        //            self.current_iter = &mut node.next;
        //            // Note: cannot return mut ref, if we return it, we will have multiple mut reference
        //            &mut node.val
        //        })

        // 目标：返回一个 1. 非 self 的  2. 生命周期为 'a 的引用
        // take 本身返回一个 Box<Node<T>>, 表示"后面肯定有我"
        // 所以这里无论如何应该是 Option<&mut ref>, 要不然可能改变原来的数据结构

        // https://stackoverflow.com/questions/57036513/rust-errore0495-cannot-infer-an-appropriate-lifetime-for-autoref-due-to-conf/57036923#57036923
        //        self.current_iter.as_mut().map(|mut node| {
        //            self.current_iter = &mut node.next;
        //            &mut node.val
        //        })

        unimplemented!()
    }
}

#[cfg(test)]
mod test {
    use crate::first::List;

    #[test]
    fn test_push() {
        let mut l = List::default();
        for i in 0..10 {
            l.push(i);
        }
    }

    #[test]
    fn test_pop() {
        let mut l = List::default();
        for i in 0..10 {
            l.push(i);
        }

        for i in (0..10).rev() {
            assert_eq!(l.pop(), Some(i));
        }

        for _ in 0..10 {
            assert_eq!(l.pop(), None);
        }
    }

    #[test]
    fn test_peak() {
        let mut l = List::default();
        let mut to_cmp = None;
        for i in 0..10 {
            assert_eq!(l.peek().map(|v: &i32| v.to_owned()), to_cmp);
            to_cmp = Some(i);
            l.push(i);
        }
    }

    #[test]
    fn test_iter() {
        let build_init = || {
            let mut l = List::default();
            for i in 0..10 {
                l.push(i);
            }
            l
        };

        {
            let mut cnt = 9;
            for i in build_init() {
                assert_eq!(i, cnt);
                cnt -= 1;
            }
        }

        {
            let mut cnt = 9;
            let init = build_init();
            for i in init.iter() {
                assert_eq!(i, &cnt);
                cnt -= 1;
            }

            cnt = 9;
            for i in init.iter() {
                assert_eq!(i, &cnt);
                cnt -= 1;
            }
        }

        {
            let mut cnt = 9;
            let mut init = build_init();
            for i in init.iter_mut() {
                assert_eq!(i, &cnt);
                cnt -= 1;
                *i += 10;
            }

            let mut cnt = 19;
            for i in init {
                assert_eq!(i, cnt);
                cnt -= 1;
            }
        }
    }
}
