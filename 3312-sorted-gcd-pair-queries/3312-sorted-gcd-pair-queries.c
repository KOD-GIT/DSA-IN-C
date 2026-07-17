#include <stdlib.h>

static long long choose2(long long x) {
    return x * (x - 1) / 2;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* gcdValues(int* nums, int numsSize, long long* queries, int queriesSize, int* returnSize) {
    *returnSize = queriesSize;

    int maxVal = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxVal) maxVal = nums[i];
    }

    int *freq = (int *)calloc(maxVal + 1, sizeof(int));
    int *divCnt = (int *)calloc(maxVal + 1, sizeof(int));
    long long *gcdCnt = (long long *)calloc(maxVal + 1, sizeof(long long));
    long long *prefix = (long long *)calloc(maxVal + 1, sizeof(long long));

    for (int i = 0; i < numsSize; i++)
        freq[nums[i]]++;

    // Count numbers divisible by each value
    for (int d = 1; d <= maxVal; d++) {
        for (int m = d; m <= maxVal; m += d)
            divCnt[d] += freq[m];
    }

    // Inclusion-Exclusion to count pairs with GCD exactly d
    for (int d = maxVal; d >= 1; d--) {
        gcdCnt[d] = choose2(divCnt[d]);
        for (int m = d + d; m <= maxVal; m += d)
            gcdCnt[d] -= gcdCnt[m];
    }

    // Prefix counts
    for (int i = 1; i <= maxVal; i++)
        prefix[i] = prefix[i - 1] + gcdCnt[i];

    int *ans = (int *)malloc(sizeof(int) * queriesSize);

    for (int i = 0; i < queriesSize; i++) {
        long long k = queries[i] + 1;

        int lo = 1, hi = maxVal;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (prefix[mid] >= k)
                hi = mid;
            else
                lo = mid + 1;
        }
        ans[i] = lo;
    }

    free(freq);
    free(divCnt);
    free(gcdCnt);
    free(prefix);

    return ans;
}