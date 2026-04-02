#include "dynamic_array.h"


int main(void) {
    int* nums = nullptr;

    arr_push(nums, 1);
    arr_push(nums, 2);
    arr_push(nums, 3);
    arr_push(nums, 4);

    int num1 = 0;
    arr_pop(nums, num1);

    printf("----------------------\nPop num is: %d\n\n", num1);

    arr_foreach(nums, i) {
        printf("Foreach num is: %d\n", nums[i]);
    }

    printf("\nArray len is: %zu\n----------------------", arr_len(nums));

    arr_free(nums);

    return 0;
}
