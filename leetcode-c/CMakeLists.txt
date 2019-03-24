project(leetcode-c)

set (CMAKE_CXX_STANDARD 11)

add_library(lib p344_reverse_string.c p541_preverse_string_2.cpp)
add_executable(p344-test test.c)

add_executable(lp longest_palindrome_substring_5.cpp)
add_executable(ms multiply_strings.cpp)
add_executable(long-pd longest_palindrome_409.cpp)

add_executable(memory-leak memory_leak.c)

add_executable(next-permulation p31_next_permulation.cpp)

add_executable(two-sum p1_two_sum.cpp)
add_executable(all-dup-in-arr p442_find_all_duplicates_in_array.cpp)
add_executable(mid-of-two p4_medium_of_two_sorted.cpp)

add_executable(rev-link-list p206_reverse_link_list.cpp)
add_executable(del-list-node p237_delete_node.cpp)

add_executable(merge-sorted-list p21_merge_sorted_list.cpp)
add_executable(sort-list p148_sort_list.cpp)
add_executable(middle-linked-list p876_middle_of_linked_list.cpp)