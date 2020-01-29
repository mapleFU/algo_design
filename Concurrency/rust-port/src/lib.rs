#![feature(box_into_raw_non_null)]
#![feature(wait_until)]
#![feature(dropck_eyepatch)]
#![feature(never_type)]

extern crate num_cpus;

pub mod queue;
pub mod stack;

pub mod thread_pool;

pub use queue::List as LockFreeQueue;
