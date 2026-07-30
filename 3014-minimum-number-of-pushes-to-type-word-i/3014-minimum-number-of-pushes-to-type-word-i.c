int minimumPushes(char* word) {
    int n = strlen(word);
    int cost = 0;

    for (int i = 0; i < n; i++) {
        cost += (i / 8) + 1;
    }

    return cost;
}