int uniqueXorTriplets(int* nums, int numsSize) {
    if (numsSize <= 2)
        return numsSize;

    int ans = 1;
    while (ans <= numsSize)
        ans <<= 1;

    return ans;
}