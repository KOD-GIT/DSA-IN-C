#include <assert.h>

long long sumAndMultiply(int n) {
    assert(0 <= n);

    long long nnz = 0;
    long long digsum = 0;
    long long mul10 = 1;

    while (n > 0) {
        if (n%10 != 0) {
            nnz = mul10*(n%10) + nnz;
            digsum += n%10;
            mul10 *= 10;
        }

        n = n/10;
    }

    return digsum*nnz;
}