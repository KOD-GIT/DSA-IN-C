int find(int* parent, int x) {
    if (parent[x] != x)
        parent[x] = find(parent, parent[x]);
    return parent[x];
}

void unite(int* parent, int* size, int a, int b) {
    int pa = find(parent, a);
    int pb = find(parent, b);

    if (pa == pb)
        return;

    if (size[pa] < size[pb]) {
        int temp = pa;
        pa = pb;
        pb = temp;
    }

    parent[pb] = pa;
    size[pa] += size[pb];
}

int countCompleteComponents(int n, int** edges, int edgesSize,
                            int* edgesColSize) {
    int parent[n];
    int size[n];
    int edgeCount[n];

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        size[i] = 1;
        edgeCount[i] = 0;
    }

    for (int i = 0; i < edgesSize; i++) {
        unite(parent, size, edges[i][0], edges[i][1]);
    }

    for (int i = 0; i < edgesSize; i++) {
        int root = find(parent, edges[i][0]);
        edgeCount[root]++;
    }

    int count = 0;

    for (int i = 0; i < n; i++) {
        if (find(parent, i) == i) {
            int vertices = size[i];
            int requiredEdges = vertices * (vertices - 1) / 2;

            if (edgeCount[i] == requiredEdges)
                count++;
        }
    }

    return count;
}