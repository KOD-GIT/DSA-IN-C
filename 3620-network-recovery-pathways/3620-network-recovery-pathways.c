#include <stdlib.h>
#include <stdbool.h>

typedef long long ll;

typedef struct {
    int to;
    int cost;
    int next;
} Edge;

int cmp(const void *a,const void *b) {
    return (*(int *)a - *(int *)b);
}

int findMaxPathScore(int** edges, int edgesSize, int* edgesColSize,
                     bool* online, int onlineSize, long long k) {

    int n = onlineSize;
    int m = edgesSize;

    if (m == 0) return -1;

    Edge *graph = (Edge *)malloc(sizeof(Edge) * m);
    int *head = (int *)malloc(sizeof(int) * n);
    int *indeg = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
        head[i] = -1;

    int idx = 0;

    int *vals = (int *)malloc(sizeof(int) * m);

    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int c = edges[i][2];

        vals[i] = c;

        graph[idx].to = v;
        graph[idx].cost = c;
        graph[idx].next = head[u];
        head[u] = idx++;

        indeg[v]++;
    }

    /* Topological order */
    int *queue = (int *)malloc(sizeof(int) * n);
    int *topo = (int *)malloc(sizeof(int) * n);

    int front = 0, back = 0;

    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            queue[back++] = i;

    int t = 0;

    while (front < back) {
        int u = queue[front++];
        topo[t++] = u;

        for (int e = head[u]; e != -1; e = graph[e].next) {
            int v = graph[e].to;
            if (--indeg[v] == 0)
                queue[back++] = v;
        }
    }

    qsort(vals, m, sizeof(int), cmp);

    int unique = 0;
    for (int i = 0; i < m; i++) {
        if (i == 0 || vals[i] != vals[unique - 1])
            vals[unique++] = vals[i];
    }

    ll *dp = (ll *)malloc(sizeof(ll) * n);
    const ll INF = (1LL << 60);

    int ans = -1;
    int lo = 0, hi = unique - 1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int limit = vals[mid];

        for (int i = 0; i < n; i++)
            dp[i] = INF;

        dp[0] = 0;

        for (int i = 0; i < t; i++) {
            int u = topo[i];

            if (dp[u] == INF)
                continue;

            for (int e = head[u]; e != -1; e = graph[e].next) {
                int v = graph[e].to;
                int c = graph[e].cost;

                if (c < limit)
                    continue;

                if (v != n - 1 && !online[v])
                    continue;

                if (dp[v] > dp[u] + (ll)c)
                    dp[v] = dp[u] + (ll)c;
            }
        }

        if (dp[n - 1] <= k) {
            ans = limit;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    free(graph);
    free(head);
    free(indeg);
    free(queue);
    free(topo);
    free(vals);
    free(dp);

    return ans;
}
