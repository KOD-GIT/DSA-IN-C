int minSumOfLengths(int* arr, int arrSize, int target) {
    int best[arrSize];
    int left = 0, sum = 0;
    int ans = arrSize + 1;

    for (int i = 0; i < arrSize; i++)
        best[i] = arrSize + 1;

    for (int right = 0; right < arrSize; right++) {
        sum += arr[right];

        while (sum > target) {
            sum -= arr[left++];
        }

        if (sum == target) {
            int len = right - left + 1;

            // Previous non-overlapping subarray
            if (left > 0 && best[left - 1] <= arrSize) {
                int total = len + best[left - 1];
                if (total < ans)
                    ans = total;
            }

            // Store shortest subarray found so far
            best[right] = len;
        }

        // Carry forward previous best
        if (right > 0 && best[right - 1] < best[right])
            best[right] = best[right - 1];
    }

    return ans == arrSize + 1 ? -1 : ans;
}