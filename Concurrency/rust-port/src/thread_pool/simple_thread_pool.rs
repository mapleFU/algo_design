use crate::queue::{NaiveMutexDeque, ThreadSafeQueue};
use std::default::Default;
use std::mem;
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::Arc;
use std::thread::{spawn, JoinHandle};

use num_cpus;

#[allow(unused)]
pub struct SimpleThreadPool {
    done: Arc<AtomicBool>,
    work_queue: Arc<NaiveMutexDeque<Box<dyn FnOnce() + Send + 'static>>>,
    threads: Vec<JoinHandle<()>>,
}

#[allow(unused)]
fn worker_thread(
    done: Arc<AtomicBool>,
    queue: Arc<NaiveMutexDeque<Box<dyn FnOnce() + Send + 'static>>>,
) {
    while done.load(Ordering::SeqCst) {
        let task = queue.pop_front_wait();
        task();
    }
}

impl SimpleThreadPool {
    #[allow(unused)]
    fn worker_thread(&self) {
        while self.done.load(Ordering::SeqCst) && !self.work_queue.is_empty() {
            let task = self.work_queue.pop_front_wait();
            // run task.
            task();
        }
    }

    pub fn new() -> Self {
        let cores = num_cpus::get();
        let mut pool = SimpleThreadPool {
            done: Arc::new(AtomicBool::new(false)),
            work_queue: Arc::new(NaiveMutexDeque::default()),
            threads: Default::default(),
        };
        for _ in 0..cores {
            let done_clone = pool.done.clone();
            let queue_clone = pool.work_queue.clone();
            let t = spawn(move || worker_thread(done_clone, queue_clone));
            pool.threads.push(t);
        }

        pool
    }

    pub fn submit<F>(&self, func: F)
    where
        F: FnOnce<(), Output = ()> + Send + 'static,
    {
        let f: Box<dyn FnOnce<(), Output = ()> + Send + 'static> = Box::new(func);
        self.work_queue.push_back(f);
    }
}

impl Drop for SimpleThreadPool {
    fn drop(&mut self) {
        self.done.store(true, Ordering::SeqCst);
        for thread in mem::take(&mut self.threads).into_iter() {
            thread.join().unwrap();
        }
    }
}

#[cfg(test)]
mod test {
    use crate::thread_pool::simple_thread_pool::SimpleThreadPool;

    #[test]
    fn test_simple_count() {
        let counting_func = || {
            let mut v = 0;
            for i in 0..1000000 {
                v = (v * 1024 + i * v) % 12232142;
            }
        };
        let mut p = SimpleThreadPool::new();

        for _ in 0..1000 {
            p.submit(counting_func);
        }
    }
}
