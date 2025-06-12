#include <stdio.h>
#include <limits.h>

int main() {
    printf("int:       [%d, %d]\n", INT_MIN, INT_MAX);
    printf("unsigned:  [0, %u]\n", UINT_MAX);
    printf("short:     [%d, %d]\n", SHRT_MIN, SHRT_MAX);
    printf("ushort:    [0, %u]\n", USHRT_MAX);
    return 0;
}