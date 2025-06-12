#include <stdio.h>
#include <limits.h>

int main() {
    int min = INT_MIN;
    printf("Min: %d\n", min);
    min = min - 1;  // This causes integer underflow
    printf("After Underflow: %d\n", min); // wraps to INT_MAX
    return 0;
}