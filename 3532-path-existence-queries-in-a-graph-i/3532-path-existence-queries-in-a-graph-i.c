/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdbool.h>

bool* pathExistenceQueries(int n, int* nums, int numsSize, int maxDiff,
                           int** queries, int queriesSize,
                           int* queriesColSize, int* returnSize) {
    *returnSize = queriesSize;

    bool *ans = (bool *)malloc(sizeof(bool) * queriesSize);

    // Component ID for each index
    int *comp = (int *)malloc(sizeof(int) * n);

    int id = 0;
    comp[0] = 0;

    for (int i = 1; i < n; i++) {
        if (nums[i] - nums[i - 1] > maxDiff)
            id++;
        comp[i] = id;
    }

    for (int i = 0; i < queriesSize; i++) {
        int u = queries[i][0];
        int v = queries[i][1];
        ans[i] = (comp[u] == comp[v]);
    }

    free(comp);
    return ans;
}