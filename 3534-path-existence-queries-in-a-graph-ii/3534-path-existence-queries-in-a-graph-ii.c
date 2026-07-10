#include <stdlib.h>

typedef struct {
    int val;
    int idx;
} Node;

int cmp(const void *a, const void *b) {
    Node *x = (Node *)a;
    Node *y = (Node *)b;
    if (x->val != y->val) return x->val - y->val;
    return x->idx - y->idx;
}

int* pathExistenceQueries(int n, int* nums, int numsSize, int maxDiff,
                          int** queries, int queriesSize,
                          int* queriesColSize, int* returnSize) {
    Node *arr = (Node *)malloc(sizeof(Node) * n);

    for (int i = 0; i < n; i++) {
        arr[i].val = nums[i];
        arr[i].idx = i;
    }

    qsort(arr, n, sizeof(Node), cmp);

    int *pos = (int *)malloc(sizeof(int) * n);
    int *comp = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        pos[arr[i].idx] = i;

    comp[0] = 0;
    for (int i = 1; i < n; i++) {
        comp[i] = comp[i - 1];
        if (arr[i].val - arr[i - 1].val > maxDiff)
            comp[i]++;
    }

    int *next = (int *)malloc(sizeof(int) * n);
    int r = 0;
    for (int i = 0; i < n; i++) {
        if (r < i) r = i;
        while (r + 1 < n && arr[r + 1].val - arr[i].val <= maxDiff)
            r++;
        next[i] = r;
    }

    int LOG = 0;
    while ((1 << LOG) <= n) LOG++;

    int **up = (int **)malloc(sizeof(int *) * LOG);
    up[0] = next;

    for (int k = 1; k < LOG; k++) {
        up[k] = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            up[k][i] = up[k - 1][up[k - 1][i]];
    }

    int *ans = (int *)malloc(sizeof(int) * queriesSize);

    for (int q = 0; q < queriesSize; q++) {
        int u = pos[queries[q][0]];
        int v = pos[queries[q][1]];

        if (u == v) {
            ans[q] = 0;
            continue;
        }

        if (comp[u] != comp[v]) {
            ans[q] = -1;
            continue;
        }

        if (u > v) {
            int t = u;
            u = v;
            v = t;
        }

        int cur = u;
        int steps = 0;

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][cur] < v) {
                cur = up[k][cur];
                steps += (1 << k);
            }
        }

        ans[q] = steps + 1;
    }

    for (int k = 1; k < LOG; k++)
        free(up[k]);
    free(up);
    free(next);
    free(pos);
    free(comp);
    free(arr);

    *returnSize = queriesSize;
    return ans;
}