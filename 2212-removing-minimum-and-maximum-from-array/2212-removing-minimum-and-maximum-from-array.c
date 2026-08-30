int minimumDeletions(int* nums, int numsSize) {
    int minIndex = 0, maxIndex = 0;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < nums[minIndex])
            minIndex = i;

        if (nums[i] > nums[maxIndex])
            maxIndex = i;
    }

    if (minIndex > maxIndex) {
        int temp = minIndex;
        minIndex = maxIndex;
        maxIndex = temp;
    }

    int front = maxIndex + 1;

    int back = numsSize - minIndex;

    int mixed = (minIndex + 1) + (numsSize - maxIndex);

    int ans = front;

    if (back < ans)
        ans = back;

    if (mixed < ans)
        ans = mixed;

    return ans;
}