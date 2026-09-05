int firstStableIndex(int* nums, int numsSize, int k) {
    int n = numsSize;


    int* suffixMin = (int*)malloc(n * sizeof(int));

    suffixMin[n - 1] = nums[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        suffixMin[i] = nums[i] < suffixMin[i + 1]
                       ? nums[i]
                       : suffixMin[i + 1];
    }

    int prefixMax = nums[0];

    for (int i = 0; i < n; i++) {
        if (nums[i] > prefixMax) {
            prefixMax = nums[i];
        }

        if ((long long)prefixMax - suffixMin[i] <= k) {
            free(suffixMin);
            return i;
        }
    }

    free(suffixMin);
    return -1;
}