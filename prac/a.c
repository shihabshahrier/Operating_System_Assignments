#include <stdio.h>
int main(int argc, char **argv) {
  FILE *fptr;
  char abc[20];
  fptr = fopen("a.txt", "r");
  fscanf(fptr, "%s", abc);
  printf("%s", abc);
  fclose(fptr);
  return 0;
}