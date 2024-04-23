#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#define N 10
uint64_t get_value(uint64_t n) {
  assert(n < N);
  return n + 1;
}
void put_value(uint64_t n, uint64_t v) {
  assert(n < N);
}
uint64_t core(uint64_t n, char const *p);
int main() {
    static const char* p = "55B000002*";
    printf("%ld", core(0, "135*P135*P"));
    /*ssert(core(0, "12*") == 2);
    assert(core(0, "22*") == 4);
    assert(core(0, "34*") == 12);
    assert(core(0, "4827*") == 14);
    assert(core(0, "48*27**") == 448);
    assert(core(0, "n") == 0);
    assert(core(12, "n") == 12);
    assert(core(UINT64_MAX, "n") == UINT64_MAX);
    assert(core(0, "1-") == UINT64_MAX);
    assert(core(0, "3-") == UINT64_MAX - 2);
    assert(core(0, "19-") == UINT64_MAX - 8);
    assert(core(0, "19-8+") == UINT64_MAX);
    assert(core(0, "19-9+") == 0);
    assert(core(0, "12E") == 1);
    assert(core(0, "1243E") == 4);
    assert(core(0, "1243EC") == 3);
    assert(core(0, "1243ECC") == 2);
    assert(core(0, "1243ECCC") == 1);
    assert(core(0, "10B") == 1);
    assert(core(0, "41B0") == 4);
    assert(core(0, "451B0*") == 20);
    assert(core(0, "55B000002*") == 10);
    assert(core(0, "G") == 1);
    assert(core(1, "G") == 2);
      assert(core(0, "G") == 10);
  assert(core(0, "123+") == 5);
  assert(core(0, "123+G") == 10);
  assert(core(0, "123+G+") == 15);
  assert(core(0, "123+G3+") == 13);
  assert(core(0, "123+G123+") == 5);
  assert(core(0, "123+G123+G123+") == 5);
  printf("G \x1B[32mpassed\x1B[0m\n");

  printf("Running P test - if no confirmation then test failed...\n");
  assert(core(0, "35*") == 15);
  assert(core(0, "135*P") == 1);
  assert(core(0, "135*P135*P") == 1);
  assert(core(0, "135*P135*P135*") == 15);*/
    return 0;
}
/*

*/