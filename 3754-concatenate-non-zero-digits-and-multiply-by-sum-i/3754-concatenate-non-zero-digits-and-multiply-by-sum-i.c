long long sumAndMultiply(int n) {
    if (n == 0) return 0;

    int digits[10];
    int len = 0;

    while (n > 0) {
        digits[len++] = n % 10;
        n /= 10;
    }

    long long x = 0;
    int sum = 0;

    for (int i = len - 1; i >= 0; i--) {
        if (digits[i] != 0) {
            x = x * 10 + digits[i];
            sum += digits[i];
        }
    }

    return x * sum;
}