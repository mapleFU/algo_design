use std::collections::LinkedList;
use std::sync::{Arc, Condvar, Mutex, MutexGuard};

/// `Stack` is a trait for stack, user can push pop in this stack.
pub trait Stack<T> {
    fn push(&self, obj: T);

    fn empty(&self) -> bool;

    fn pop(&self) -> Option<T>;

    fn pop_wait(&self) -> T {
        unimplemented!()
    }
}

macro_rules! impl_sync {
    ($t: ty) => {
        unsafe impl<T> Sync for $t {}
    };
}

#[derive(Default)]
pub struct LockStack<T> {
    guard: Mutex<LinkedList<T>>,
}

impl_sync!(LockStack<T>);

impl<T: Copy> Stack<T> for LockStack<T> {
    fn push(&self, obj: T) {
        let mut guard = self.guard.lock().unwrap();
        guard.push_back(obj);
    }

    fn empty(&self) -> bool {
        self.guard.lock().unwrap().is_empty()
    }

    /// If there is nothing, calling to pop will immediately got None.
    fn pop(&self) -> Option<T> {
        let mut guard = self.guard.lock().unwrap();
        match guard.back() {
            Some(&s) => {
                guard.pop_back();
                Some(s)
            }
            None => None,
        }
    }
}

#[derive(Default)]
pub struct CondStack<T> {
    guard: Arc<Mutex<LinkedList<T>>>,
    cond: Condvar,
}

impl_sync!(CondStack<T>);

impl<T: Copy> Stack<T> for CondStack<T> {
    fn push(&self, obj: T) {
        let mut guard = self.guard.lock().unwrap();
        guard.push_back(obj);
        self.cond.notify_one();
    }

    fn empty(&self) -> bool {
        self.guard.lock().unwrap().is_empty()
    }

    fn pop(&self) -> Option<T> {
        let mut guard = self.guard.lock().unwrap();
        match guard.back() {
            Some(&s) => {
                guard.pop_back();
                Some(s)
            }
            None => None,
        }
    }

    fn pop_wait(&self) -> T {
        let result = self.guard.lock();
        let mut entity: MutexGuard<LinkedList<T>> = result.unwrap();
        if !entity.is_empty() {
            entity.pop_back().unwrap()
        } else {
            let e = self.cond.wait(entity);
            let mut entity = e.unwrap();
            entity.pop_back().unwrap()
        }
    }
}

