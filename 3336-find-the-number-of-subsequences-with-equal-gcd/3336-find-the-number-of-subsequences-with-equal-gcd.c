#define MOD 1000000007

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int subsequencePairCount(int* nums, int numsSize) {
    long long dp[201][201] = {0};
    long long next[201][201];

    dp[0][0] = 1;

    for (int k = 0; k < numsSize; k++) {
        int x = nums[k];

        for (int i = 0; i <= 200; i++) {
            for (int j = 0; j <= 200; j++) {
                next[i][j] = dp[i][j];
            }
        }

        for (int g1 = 0; g1 <= 200; g1++) {
            for (int g2 = 0; g2 <= 200; g2++) {
                if (dp[g1][g2] == 0)
                    continue;

                int ng1 = (g1 == 0) ? x : gcd(g1, x);
                int ng2 = (g2 == 0) ? x : gcd(g2, x);

                next[ng1][g2] =
                    (next[ng1][g2] + dp[g1][g2]) % MOD;

                next[g1][ng2] =
                    (next[g1][ng2] + dp[g1][g2]) % MOD;
            }
        }

        for (int i = 0; i <= 200; i++) {
            for (int j = 0; j <= 200; j++) {
                dp[i][j] = next[i][j];
            }
        }
    }

    long long ans = 0;

    for (int g = 1; g <= 200; g++) {
        ans = (ans + dp[g][g]) % MOD;
    }

    return (int)ans;
}