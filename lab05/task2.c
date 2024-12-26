#include <stdio.h>

int main() {
  int n = 6;
  int m = 4;

  int alloc[6][4] = {{0, 1, 0, 3}, {2, 0, 0, 3}, {3, 0, 2, 0},
                     {2, 1, 1, 5}, {0, 0, 2, 2}, {1, 2, 3, 1}};

  int max[6][4] = {{6, 4, 3, 4}, {3, 2, 2, 4}, {9, 1, 2, 6},
                   {2, 2, 2, 8}, {4, 3, 3, 7}, {6, 2, 6, 5}};

  int avail[4] = {2, 2, 2, 1};

  int need[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      need[i][j] = max[i][j] - alloc[i][j];
    }
  }

  int finish[n];
  for (int i = 0; i < n; i++) {
    finish[i] = 0;
  }

  int work[m];
  for (int i = 0; i < m; i++) {
    work[i] = avail[i];
  }

  int safeSeq[n];
  int count = 0;

  while (count < n) {
    int found = 0;
    for (int p = 0; p < n; p++) {
      if (finish[p] == 0) {
        int canExecute = 1;
        for (int j = 0; j < m; j++) {
          if (need[p][j] > work[j]) {
            canExecute = 0;
            break;
          }
        }
        if (canExecute) {
          for (int j = 0; j < m; j++) {
            work[j] += alloc[p][j];
          }
          safeSeq[count] = p;
          finish[p] = 1;
          count++;
          found = 1;
        }
      }
    }
    if (!found) {
      break;
    }
  }

  printf("Safe sequence of process execution: ");
  for (int i = 0; i < n; i++) {
    printf("P%d", safeSeq[i]);
    if (i < n - 1) {
      printf(" -> ");
    }
  }
  printf("\n");

  return 0;
}
