#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

// unsorted
bool UniqueElement_sort (int *array, int size) {
    for(int i = 1;i < size; i++) {
        for(int j = 0; j < i; j++) {
            if (array[i] == array[j]) 
                return false;
        }
    }
    return true;
}

// sorted
bool UniqueElement_sort2 (int *sorted_array, int size) {
    for(int i = 0;i < size - 1;i++) {
        if (sorted_array[i] == sorted_array[i + 1])
            return false;
    }
    return true;
}

int main() {
    int s1[] = {1, 7, 2, 6, 8, 8};
    bool value = UniqueElement_sort(s1, sizeof(s1) / sizeof(int));
    assert(value == false);
    printf("Passed the tests!\n");
    return 0;
}
