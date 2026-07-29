#include <stdlib.h>
#include <string.h>

#define LIMIT 1000001LL

char* smallestPalindrome(char* s, int k) {
    int n = strlen(s);
    int freq[26] = {0};

    for (int i = 0; i < n; i++)
        freq[s[i] - 'a']++;

    char mid = 0;
    int cnt[26] = {0};
    int m = 0;

    for (int i = 0; i < 26; i++) {
        cnt[i] = freq[i] / 2;
        m += cnt[i];
        if (freq[i] & 1)
            mid = 'a' + i;
    }


    int *spf = (int *)malloc((m + 1) * sizeof(int));
    int *primes = (int *)malloc((m + 1) * sizeof(int));
    int pc = 0;

    for (int i = 0; i <= m; i++)
        spf[i] = i;

    for (int i = 2; i <= m; i++) {
        if (spf[i] == i) {
            primes[pc++] = i;
            if ((long long)i * i <= m) {
                for (int j = i * i; j <= m; j += i)
                    if (spf[j] == j)
                        spf[j] = i;
            }
        }
    }

    int *exp = (int *)calloc(pc, sizeof(int));


    for (int i = 0; i < pc; i++) {
        int p = primes[i];
        int e = 0;

        int x = m;
        while (x) {
            x /= p;
            e += x;
        }

        for (int j = 0; j < 26; j++) {
            x = cnt[j];
            while (x) {
                x /= p;
                e -= x;
            }
        }
        exp[i] = e;
    }

    long long evaluate() {
        long long ans = 1;
        for (int i = 0; i < pc; i++) {
            for (int j = 0; j < exp[i]; j++) {
                if (ans > LIMIT / primes[i])
                    return LIMIT;
                ans *= primes[i];
            }
        }
        return ans;
    }

    if (evaluate() < k) {
        char *res = (char *)malloc(1);
        res[0] = '\0';
        free(spf);
        free(primes);
        free(exp);
        return res;
    }

    char *half = (char *)malloc(m + 1);
    int pos = 0, rem = m;

    while (rem) {
        for (int c = 0; c < 26; c++) {
            if (!cnt[c]) continue;

            int x = cnt[c];
            while (x > 1) {
                int p = spf[x];
                int idx = 0;
                while (primes[idx] != p) idx++;
                exp[idx]++;
                x /= p;
            }

            x = rem;
            while (x > 1) {
                int p = spf[x];
                int idx = 0;
                while (primes[idx] != p) idx++;
                exp[idx]--;
                x /= p;
            }

            long long ways = evaluate();

            if (ways >= k) {
                half[pos++] = 'a' + c;
                cnt[c]--;
                rem--;
                break;
            }

            k -= (int)ways;

            x = cnt[c];
            while (x > 1) {
                int p = spf[x];
                int idx = 0;
                while (primes[idx] != p) idx++;
                exp[idx]--;
                x /= p;
            }

            x = rem;
            while (x > 1) {
                int p = spf[x];
                int idx = 0;
                while (primes[idx] != p) idx++;
                exp[idx]++;
                x /= p;
            }
        }
    }

    half[m] = '\0';

    char *ans = (char *)malloc(n + 1);

    for (int i = 0; i < m; i++)
        ans[i] = half[i];

    int idx = m;

    if (mid)
        ans[idx++] = mid;

    for (int i = m - 1; i >= 0; i--)
        ans[idx++] = half[i];

    ans[idx] = '\0';

    free(half);
    free(spf);
    free(primes);
    free(exp);

    return ans;
}