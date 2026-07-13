/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sequentialDigits(int low, int high, int* returnSize) {
    int* result = (int*)malloc(36 * sizeof(int));
    *returnSize = 0;

    for (int len = 2; len <= 9; len++) {
        for (int start = 1; start + len - 1 <= 9; start++) {
            int num = 0;

            for (int digit = start; digit < start + len; digit++) {
                num = num * 10 + digit;
            }

            if (num >= low && num <= high) {
                result[(*returnSize)++] = num;
            }
        }
    }

    return result;
}