PROJECT(Concurrency)

CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

set (CMAKE_CXX_STANDARD 17)

# describes a thread-safe queue
add_subdirectory(queue)

add_subdirectory(thread_pool)