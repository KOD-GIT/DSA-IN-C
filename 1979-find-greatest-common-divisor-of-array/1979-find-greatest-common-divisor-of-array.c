int findGCD(int* nums, int numsSize) {
    int mn = nums[0], mx = nums[0];

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < mn)
            mn = nums[i];
        else if (nums[i] > mx)
            mx = nums[i];
    }

    while (mn) {
        int t = mx % mn;
        mx = mn;
        mn = t;
    }

    return mx;
}