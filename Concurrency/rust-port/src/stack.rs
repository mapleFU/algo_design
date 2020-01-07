use std::collections::LinkedList;
use std::sync::atomic::AtomicPtr;
use std::sync::{Condvar, Mutex, MutexGuard};

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
    pub(crate) guard: Mutex<LinkedList<T>>,
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
    guard: LockStack<T>,
    cond: Condvar,
}

impl_sync!(CondStack<T>);

impl<T: Copy> Stack<T> for CondStack<T> {
    fn push(&self, obj: T) {
        self.guard.push(obj);
        self.cond.notify_one();
    }

    fn empty(&self) -> bool {
        self.guard.empty()
    }

    fn pop(&self) -> Option<T> {
        self.guard.pop()
    }

    fn pop_wait(&self) -> T {
        let result = self.guard.guard.lock();
        let mut entity: MutexGuard<LinkedList<T>> = result.unwrap();

        if !entity.is_empty() {
            return entity.pop_back().unwrap();
        } else {
            let e = self.cond.wait_until(entity, |cfg| cfg.len() > 0);
            entity = e.unwrap();
            return entity.pop_back().unwrap();
        }
    }
}

pub struct AtomicStack<T> {
    head: AtomicLink<T>,
}

pub struct AtomicNode<T> {
    val: T,
    next: AtomicLink<T>,
}

impl<T> AtomicNode<T> {
    pub fn new(obj: T) -> Self {
        AtomicNode {
            next: Default::default(),
            val: obj,
        }
    }
}

pub type AtomicLink<T> = AtomicPtr<AtomicNode<T>>;

#[cfg(test)]
mod test {
    use crate::stack::{CondStack, LockStack, Stack};
    use std::sync::Arc;
    use std::thread::spawn;

    fn concurrency_get_test<T: Stack<i32> + Default + Sync + Send + 'static>() {
        let s1 = T::default();
        let cnt_size = 10000;
        for i in 0..cnt_size {
            s1.push(i);
        }

        let arc = Arc::new(s1);
        let mut tasks = vec![];
        for _ in 0..5 {
            let stack = arc.clone();
            tasks.push(spawn(move || {
                let mut cnt = 0;
                while !stack.empty() {
                    if stack.pop().is_some() {
                        cnt += 1;
                    }
                }
                cnt
            }));
        }

        assert_eq!(cnt_size, tasks.into_iter().map(|t| t.join().unwrap()).sum());
    }

    #[test]
    fn test_stack_1() {
        concurrency_get_test::<LockStack<i32>>();
    }

    #[test]
    fn test_stack_2() {
        concurrency_get_test::<CondStack<i32>>();
    }

    #[test]
    fn test_cond_wait() {
        let cond = CondStack::default();
        let mut task_vec = vec![];
        let arc_cond = Arc::new(cond);
        let task_cnt = 10;
        for _ in 0..task_cnt {
            let cond_t = arc_cond.clone();
            task_vec.push(spawn(move || cond_t.pop_wait()));
        }

        for i in 0..task_cnt {
            arc_cond.push(i);
        }

        let mut v: Vec<i32> = task_vec.into_iter().map(|t| t.join().unwrap()).collect();
        v.sort();

        assert_eq!(v.len() as i32, task_cnt);
        for ta in 0..task_cnt {
            assert_eq!(ta, v[ta as usize]);
        }
    }
}
