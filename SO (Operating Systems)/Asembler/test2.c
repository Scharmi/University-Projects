#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#define SIZE 6

uint64_t inverse_permutation (size_t arg1, int* arg2);
int main() {
    int tab[SIZE] = {2,0,1,5,3,4};
    printf("Wynik mojej funkcji to %lu\n", inverse_permutation(SIZE, tab));
    printf("Tablica po wywolaniu funkcji to:");
    for (int i = 0; i < SIZE; i++) {
        printf(" %d", tab[i]);
    }
    printf("\n");
}