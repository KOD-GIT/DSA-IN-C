int uniqueXorTriplets(int* nums, int numsSize) {
    const int MAXX = 2048;

    char dp[4][2048] = {0};
    dp[0][0] = 1;

    for (int i = 0; i < numsSize; i++) {
        int v = nums[i];
        for (int k = 3; k >= 1; k--) {
            for (int x = 0; x < MAXX; x++) {
                if (dp[k - 1][x])
                    dp[k][x ^ v] = 1;
            }
        }
    }

    char seen[2048] = {0};

 
    for (int i = 0; i < numsSize; i++)
        seen[nums[i]] = 1;

    for (int x = 0; x < MAXX; x++)
        if (dp[3][x])
            seen[x] = 1;

    int ans = 0;
    for (int x = 0; x < MAXX; x++)
        ans += seen[x];

    return ans;
}