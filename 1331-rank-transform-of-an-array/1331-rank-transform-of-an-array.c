#include <stdlib.h>

int cmp(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;

    return (x > y) - (x < y);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* arrayRankTransform(int* arr, int arrSize, int* returnSize) {
    *returnSize = arrSize;

    int* ans = (int*)malloc(arrSize * sizeof(int));

    if (arrSize == 0)
        return ans;

    int* temp = (int*)malloc(arrSize * sizeof(int));

    for (int i = 0; i < arrSize; i++)
        temp[i] = arr[i];

    qsort(temp, arrSize, sizeof(int), cmp);

    int unique = 0;

    for (int i = 0; i < arrSize; i++) {
        if (i == 0 || temp[i] != temp[i - 1])
            temp[unique++] = temp[i];
    }

    for (int i = 0; i < arrSize; i++) {
        int left = 0, right = unique - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (temp[mid] == arr[i]) {
                ans[i] = mid + 1;
                break;
            } else if (temp[mid] < arr[i]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    free(temp);

    return ans;
}