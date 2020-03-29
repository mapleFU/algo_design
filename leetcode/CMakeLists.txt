project(leetcode-c)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set (CMAKE_CXX_STANDARD 20)
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

# The problem here is so naive.
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

add_executable(majority-element p169_majority_element.cpp)

add_executable(fib-number p509_fibonacci_number.cpp)

add_executable(super-pow p372_super_pow.cpp)

add_executable(regular-expression-matching p10_regular_expression_matching.cpp)

# TODO: this problem remains unfinished, please finish it later
add_executable(valid-number p65_validate_number.cpp)

add_executable(symmetic-tree p101_symmetic_tree.cpp)

add_executable(subtree-of-another-tree p572_subtree_of_another_tree.cpp)

add_executable(lcs-of-bst p236_lowest_common_ancenstor_of_binary_tree.cpp)

# TODO: this problem remains unfinished, please finish it later
add_executable(atoi p8_atoi.cpp)

add_executable(kth-largest-element-in-stream p703_kth_largest_element_in_stream.cpp)

add_executable(longest-arithmetic-subsequence-of-given-difference p1218_Longest_Arithmetic_Subsequence_of_Given_Difference.cpp)

add_executable(reverse-integer p7_reverse_integer.cpp)

# TODO: Solve on this algorithm is wrong, please find the right way to solve it.
add_executable(coin-change p322_coin_change.cpp)
add_executable(coin-change2 p518_coin_change2.cpp)

# TODO: FINISH IT
add_executable(odd-even-jump p975_odd_even_jump.cpp)

# TODO: FINISH IT
add_executable(add-stone-weight2 p1049_last_stone_weight2.cpp)

add_executable(lru-cache p146_LRU_Cache.cpp)

add_executable(word-break p139_word_break.cpp)

add_executable(logest-increasing-subsequence p300_longest_increasing_subsequence.cpp)

add_executable(p136-single-number p136_single_number.cpp)

add_executable(max-sub-array p53_maxium_sub_array.cpp)

add_executable(valid-parenthese p20_valid_parenthese.cpp)

add_executable(search_insert_pos p35_search_insert_position.cpp)

add_executable(min-stack p155_min_stack.cpp)

add_executable(linked-list-cycle p141_linked_list_cycle.cpp)
add_executable(linked-list-cycle2 p142_linked_list_cycle_2.cpp)

add_executable(maximum-product-subarray p152_maximum_product_subarray.cpp)
add_executable(number-of-islands p200_number_off_islands.cpp)

# TODO: finish it.
add_executable(course-schedule p207_course_schedule.cpp)

# TODO: please optimize it.
add_executable(implement-trie p208_implement_trie.cpp)

add_executable(remove-invalid-parentheses p301_remove_invalid_parentheses.cpp)

add_executable(range-sum-query p307_range_sum_query.cpp)

add_executable(edit-distance p72_edit_distance.cpp)

add_executable(longest-valid-parenthese p32_longest_valid_parenthese.cpp)

# TODO: finish it.
add_executable(Sliding-Window-Maximum p239_sliding_window_maximum.cpp)

add_executable(merge-two-binary-trees p617_merge_two_binary_trees.cpp)

add_executable(counting-bits p338_counting_bits.cpp)

add_executable(new-21-game p837_new_21_game.cpp)

add_subdirectory(concurrency)