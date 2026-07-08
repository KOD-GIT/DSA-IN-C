#define MOD 1000000007LL

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumAndMultiply(char* s, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int n = strlen(s);

    long long *preSum = (long long *)malloc((n + 1) * sizeof(long long));
    preSum[0] = 0;

    int *pos = (int *)malloc(n * sizeof(int));
    int *dig = (int *)malloc(n * sizeof(int));
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        int d = s[i] - '0';
        preSum[i + 1] = preSum[i] + d;
        if (d != 0) {
            pos[cnt] = i;
            dig[cnt] = d;
            cnt++;
        }
    }

    long long *pow10 = (long long *)malloc((cnt + 1) * sizeof(long long));
    long long *prefVal = (long long *)malloc((cnt + 1) * sizeof(long long));

    pow10[0] = 1;
    for (int i = 1; i <= cnt; i++)
        pow10[i] = (pow10[i - 1] * 10) % MOD;

    prefVal[0] = 0;
    for (int i = 0; i < cnt; i++)
        prefVal[i + 1] = (prefVal[i] * 10 + dig[i]) % MOD;

    int *ans = (int *)malloc(sizeof(int) * queriesSize);

    for (int q = 0; q < queriesSize; q++) {
        int l = queries[q][0];
        int r = queries[q][1];

        long long sum = preSum[r + 1] - preSum[l];

        // lower_bound(pos >= l)
        int lo = 0, hi = cnt;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (pos[mid] < l)
                lo = mid + 1;
            else
                hi = mid;
        }
        int L = lo;

        // upper_bound(pos <= r)
        lo = 0;
        hi = cnt;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (pos[mid] <= r)
                lo = mid + 1;
            else
                hi = mid;
        }
        int R = lo - 1;

        if (L > R) {
            ans[q] = 0;
            continue;
        }

        int len = R - L + 1;

        long long x = (prefVal[R + 1] -
                      (prefVal[L] * pow10[len]) % MOD + MOD) % MOD;

        ans[q] = (int)((x * (sum % MOD)) % MOD);
    }

    free(preSum);
    free(pos);
    free(dig);
    free(pow10);
    free(prefVal);

    *returnSize = queriesSize;
    return ans;
}