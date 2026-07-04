typedef struct Node {
    int v;
    int w;
    struct Node *next;
} Node;

void dfs(int u, Node **adj, bool *vis, int *ans) {
    vis[u] = true;

    for (Node *cur = adj[u]; cur != NULL; cur = cur->next) {
        if (cur->w < *ans)
            *ans = cur->w;

        if (!vis[cur->v])
            dfs(cur->v, adj, vis, ans);
    }
}

int minScore(int n, int** roads, int roadsSize, int* roadsColSize) {
    Node **adj = (Node **)calloc(n + 1, sizeof(Node *));

    for (int i = 0; i < roadsSize; i++) {
        int u = roads[i][0];
        int v = roads[i][1];
        int w = roads[i][2];

        Node *a = (Node *)malloc(sizeof(Node));
        a->v = v;
        a->w = w;
        a->next = adj[u];
        adj[u] = a;

        Node *b = (Node *)malloc(sizeof(Node));
        b->v = u;
        b->w = w;
        b->next = adj[v];
        adj[v] = b;
    }

    bool *vis = (bool *)calloc(n + 1, sizeof(bool));
    int ans = INT_MAX;

    dfs(1, adj, vis, &ans);

    return ans;
}
