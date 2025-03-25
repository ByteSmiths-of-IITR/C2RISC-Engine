#include <stdio.h>

// Function to perform fast exponentiation
long long fastExpo(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long base, exp, mod;
    printf("Enter base, exponent and modulus: ");
    scanf("%lld %lld %lld", &base, &exp, &mod);

    long long result = fastExpo(base, exp, mod);
    printf("Result: %lld\n", result);

    return 0;
}