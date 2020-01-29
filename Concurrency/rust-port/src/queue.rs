use std::collections::VecDeque;
use std::marker::PhantomData;
use std::mem;
use std::ptr::NonNull;
use std::sync::atomic::Ordering;
use std::sync::Mutex;
use std::sync::{atomic, Condvar};

pub trait ThreadSafeQueue<T> {
    fn push_back(&self, obj: T);
    fn pop_front_wait(&self) -> T;
    fn pop_front(&self) -> Option<T>;
    fn len(&self) -> usize;

    fn is_empty(&self) -> bool {
        self.len() == 0
    }
}

//unsafe impl<T> Sync for ThreadSafeQueue<T> {}
unsafe impl<T> Sync for NaiveMutexDeque<T> {}

pub struct NaiveMutexDeque<T> {
    deque: Mutex<VecDeque<T>>,
    cond: Condvar,
}

impl<T> Default for NaiveMutexDeque<T> {
    fn default() -> Self {
        NaiveMutexDeque {
            deque: Default::default(),
            cond: Condvar::default(),
        }
    }
}

impl<T> ThreadSafeQueue<T> for NaiveMutexDeque<T> {
    fn push_back(&self, obj: T) {
        self.deque.lock().unwrap().push_back(obj);
    }

    fn pop_front_wait(&self) -> T {
        let mux = self.deque.lock().unwrap();
        let m = self.cond.wait_until(mux, |mu| !mu.is_empty());
        m.unwrap().pop_front().unwrap()
    }

    fn pop_front(&self) -> Option<T> {
        self.deque.lock().unwrap().pop_front()
    }

    fn len(&self) -> usize {
        self.deque.lock().unwrap().len()
    }
}

pub struct Node<T> {
    val: T,
    next: Link<T>,
}

impl<T> Node<T> {
    pub fn new(obj: T) -> Self {
        Node {
            next: None,
            val: obj,
        }
    }
}

pub type Link<T> = Option<NonNull<Node<T>>>;

/// Invariant: first got lock of head, then tail.
pub struct List<T> {
    head: Mutex<Link<T>>,
    tail: Mutex<Link<T>>,
    size: atomic::AtomicUsize,
    _marker: PhantomData<Box<Option<T>>>,
}

impl<T: Default> Default for List<T> {
    fn default() -> Self {
        let v = T::default();
        let virtual_node = Box::new(Node::new(v));
        let node = Box::into_raw_non_null(virtual_node);
        List {
            head: Mutex::new(Some(node)),
            tail: Mutex::new(Some(node)),
            size: atomic::AtomicUsize::new(0),
            _marker: Default::default(),
        }
    }
}

impl<T: Default> List<T> {
    pub fn new() -> Self {
        Self::default()
    }
}

impl<T> ThreadSafeQueue<T> for List<T> {
    fn push_back(&self, obj: T) {
        let mut tail = self.tail.lock().unwrap();

        unsafe {
            // old tail
            let t = tail.as_mut().unwrap();

            let origin = mem::replace(&mut (*(t.as_ptr())).val, obj);

            let new_node = Box::new(Node::new(origin));
            let new_node = Some(Box::into_raw_non_null(new_node));

            (*(t.as_ptr())).next = new_node;

            *tail = new_node;
        }

        self.size.fetch_add(1, Ordering::SeqCst);
    }

    fn pop_front_wait(&self) -> T {
        unimplemented!()
    }

    fn pop_front(&self) -> Option<T> {
        let mut head = self.head.lock().unwrap();
        {
            let tail = self.tail.lock().unwrap();
            if head.as_ref().unwrap().as_ptr() == tail.as_ref().unwrap().as_ptr() {
                // no content.
                return None;
            }
        }
        let ch = head.as_ref().unwrap();

        self.size.fetch_sub(1, Ordering::SeqCst);

        unsafe {
            let h = Box::from_raw(ch.as_ptr());
            *head = (*h).next;
            Some((*h).val)
        }
    }

    fn len(&self) -> usize {
        self.size.load(Ordering::SeqCst)
    }
}

impl<T> Drop for List<T> {
    fn drop(&mut self) {
        while let Some(_) = self.pop_front() {}
    }
}

#[cfg(test)]
mod test {
    use super::{List, ThreadSafeQueue};

    #[test]
    fn test_push_pop() {
        let l = List::new();
        let bound = 100;

        assert!(l.empty());

        for i in 0..bound {
            l.push_back(i);
        }

        assert_eq!(l.len(), bound);

        for i in 0..bound {
            assert_eq!(l.pop_front(), Some(i));
        }

        for _ in 0..bound {
            assert_eq!(l.pop_front(), None);
        }
    }
}
