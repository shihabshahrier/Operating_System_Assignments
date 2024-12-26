#include <stdio.h>

int main() {

  int *ptr;
  int num[5] = {1, 2, 3, 4, 5};
  ptr = num;
  int len = sizeof(num) / sizeof(num[0]);

  for (int i = 0; i < len; i++) {
    printf("%d", *ptr);
    ptr++;
  }

  return 0;
}