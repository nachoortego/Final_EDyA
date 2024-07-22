#include <stdio.h>
#include <stdlib.h>

int main() {
  int N, M, D;
  scanf("%d%d%d", &N, &M, &D);
  int i1 , j1;
  scanf("%d%d", &i1, &j1);
  int i2 , j2;
  scanf("%d%d", &i2, &j2);

  printf("%d %d %d\n", N, M, D);
  printf("%d %d\n", i1, j1);
  printf("%d %d\n", i2, j2);

  return 0;
}