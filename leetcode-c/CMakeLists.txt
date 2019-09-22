project(leetcode-c)

set (CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.12)

add_library(lib p344_reverse_string.c p541_preverse_string_2.cpp)
add_executable(p344-test test.c)

add_executable(lp p5_longest_palindrome_substring_5.cpp)
add_executable(ms multiply_strings.cpp)
add_executable(long-pd longest_palindrome_409.cpp)

add_executable(memory-leak memory_leak.c)

add_executable(next-permulation p31_next_permulation.cpp)

add_executable(two-sum p1_two_sum.cpp)
add_executable(all-dup-in-arr p442_find_all_duplicates_in_array.cpp)
add_executable(mid-of-two p4_medium_of_two_sorted.cpp)
add_executable(remove-element p27_remove_element.cpp)

add_executable(rev-link-list p206_reverse_link_list.cpp)
add_executable(del-list-node p237_delete_node.cpp)

add_executable(merge-sorted-list p21_merge_sorted_list.cpp)
add_executable(sort-list p148_sort_list.cpp)
add_executable(middle-linked-list p876_middle_of_linked_list.cpp)

add_executable(max-depth-bst p104_max_depth_binary_tree.cpp)

add_executable(minimun-delta minimum_delta.cpp)
add_executable(rational-calc rational_calc.cpp)

add_executable(add-two-numbers p2_fake_add_two_numbers.cpp)

add_executable(add-two-numbers-real p2_add_two_numbers.cpp)

add_executable(longest-substring-without-duplicate p3_longest_substring_without_duplicate.cpp)

add_executable(zigzag-conversion p6_zigzag_conversion.cpp)

add_executable(binary-search p704_binary_search.cpp)

add_executable(search-in-2D-matrix-2 p240_search_in_2D_matrix.cpp)

add_executable(find-the-duplicate-number p287_find_the_duplicate_number.cpp)

add_executable(remove-duplicate-from-sorted-array p26_remove_duplicate_from_sorted_array.cpp)

add_executable(add-binary p67_add_binary.cpp)
add_executable(plus-one p66_plus_one.cpp)
add_executable(multiple-strings p43_multiple_strings.cpp)
add_executable(Remove-Nth-Node-From-End-of-List p19_remove_nth_node_from_end_of_list.cpp)

add_executable(partition_equal_subset_sum p416_partition_equal_subset_sum.cpp)

add_executable(replace-words p648_replace_words.cpp)

add_executable(Construct-Binary-Tree-from-Preorder-and-Inorder-Traversal p105_rebuild_binary_tree.cpp)

add_executable(Find_Minimum_in_Rotated_Sorted_Array p153_Find_Minimum_in_Rotated_Sorted_Array.cpp)

add_executable(kth-largest-element-in-array p215_kth_largest_element_in_array.cpp)