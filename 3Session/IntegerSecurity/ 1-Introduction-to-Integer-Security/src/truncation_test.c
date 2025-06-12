#include <stdio.h>

int main() {
    int big = 300;
    char small = big;  // truncation
    printf("Original: %d, After Truncation: %d\n", big, small);
    return 0;
}