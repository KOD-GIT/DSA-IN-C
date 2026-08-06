int smallestNumber(int n, int t) {
    while (1) {
        int x = n;
        int product = 1;

        if (x == 0)
            product = 0;
        else {
            while (x > 0) {
                product *= (x % 10);
                x /= 10;
            }
        }

        if (product % t == 0)
            return n;

        n++;
    }
}