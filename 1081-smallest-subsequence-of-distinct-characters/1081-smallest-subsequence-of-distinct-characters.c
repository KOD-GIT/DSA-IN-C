char* smallestSubsequence(char* s) {
    int last[26];
    int visited[26] = {0};
    int n = strlen(s);


    for (int i = 0; i < n; i++)
        last[s[i] - 'a'] = i;

    char *stack = (char *)malloc((n + 1) * sizeof(char));
    int top = -1;

    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';

        if (visited[c])
            continue;

        while (top >= 0 &&
               stack[top] > s[i] &&
               last[stack[top] - 'a'] > i) {
            visited[stack[top] - 'a'] = 0;
            top--;
        }

        stack[++top] = s[i];
        visited[c] = 1;
    }

    stack[top + 1] = '\0';
    return stack;
}