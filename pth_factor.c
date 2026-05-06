#include <stdio.h>
#include <stdlib.h>

#define MAX_FACTORS 20000

long pthFactor(long n, long p) {
    long small[MAX_FACTORS];
    long large[MAX_FACTORS];
    int sc = 0, lc = 0;

    for (long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            small[sc++] = i;
            if (i != n / i)
                large[lc++] = n / i;
        }
    }

    // check small factors first
    if (p <= (long)sc)
        return small[p - 1];

    // check large factors (stored in descending order)
    p -= sc;
    if (p <= (long)lc)
        return large[lc - p];

    // p exceeds total number of factors
    return 0;
}

int main(void) {
    long n, p;
    scanf("%ld %ld", &n, &p);
    printf("%ld\n", pthFactor(n, p));
    return 0;
}
