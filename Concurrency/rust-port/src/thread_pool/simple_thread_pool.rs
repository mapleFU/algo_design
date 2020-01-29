use crate::queue::{NaiveMutexDeque, ThreadSafeQueue};
use std::default::Default;
use std::sync::atomic::{AtomicBool, Ordering};
use std::thread::{spawn, JoinHandle};

use num_cpus;
use std::sync::Arc;

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
        while self.done.load(Ordering::SeqCst) {
            let task = self.work_queue.pop_front_wait();
            // run task.
            task();
        }
    }

    pub fn new(&self) -> Self {
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
}
