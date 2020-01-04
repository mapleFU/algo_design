use std::mem;

pub struct Node<T> {
    val: T,
    next: Link<T>,
}

pub enum Link<T> {
    Nil,
    Node(Box<Node<T>>),
}

#[derive(Default)]
pub struct List<T> {
    head: Link<T>,
}

impl<T> Default for Link<T> {
    fn default() -> Self {
        Link::Nil
    }
}

impl<T> List<T> {
    //    fn replace_head_with_next(&mut self, next: Link<T>) -> Link<T> {
    //        unimplemented!()
    //    }

    pub fn push(&mut self, t: T) {
        let new_node = Node {
            val: t,
            // head first replace as 0
            next: mem::replace(&mut self.head, Link::Nil),
        };
        // then fill new val to it.
        self.head = Link::Node(Box::new(new_node));
    }

    pub fn pop(&mut self) -> Option<T> {
        //        match &mut self.head {
        //            // self.head == null
        //            Link::Nil => {
        //                None
        //            },
        //            Link::Node(s) => {
        //                // head = head->next;
        //                // return old head
        //                let (val, next) = (s.val, s.next);
        //                self.head = next;
        //                Some(val)
        //            }
        //        }
        // operation with head.
        match mem::replace(&mut self.head, Link::Nil) {
            Link::Nil => None,
            Link::Node(node) => {
                self.head = node.next;
                Some(node.val)
            }
        }
    }
}

impl<T> Drop for List<T> {
    fn drop(&mut self) {
        while let Link::Node(node) = mem::replace(&mut self.head, Link::Nil) {
            mem::replace(&mut self.head, node.next) ;
        };
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
}
