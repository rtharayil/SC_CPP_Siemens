#include <stdio.h>
#include <limits.h>

int main() {
    int max = INT_MAX;
    printf("Max: %d\n", max);
    max = max + 1;
    printf("After Overflow: %d\n", max); // wraps to INT_MIN
    return 0;
}