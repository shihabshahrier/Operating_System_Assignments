#include <stdio.h>

struct Process {
  char id[3];
  int arrivalTime;
  int burstTime;
  int remainingTime;
};

void sjfPreemptive(struct Process processes[], int n) {
  int currentTime = 0;
  int completed = 0;

  while (completed < n) {
    int shortestJob = -1;
    int shortestBurst = 9999; 

    for (int i = 0; i < n; i++) {
      if (processes[i].arrivalTime <= currentTime &&
          processes[i].remainingTime < shortestBurst &&
          processes[i].remainingTime > 0) {
        shortestJob = i;
        shortestBurst = processes[i].remainingTime;
      }
    }

    if (shortestJob == -1) {
      currentTime++;
      continue;
    }

    printf("%s ", processes[shortestJob].id);
    processes[shortestJob].remainingTime--;
    currentTime++;

    if (processes[shortestJob].remainingTime == 0) {
      completed++;
    }
  }

  printf("\n");
}

int main() {
  struct Process processes[] = {{"P1", 0, 5, 5},
                                {"P2", 2, 2, 2},
                                {"P3", 3, 7, 7},
                                {"P4", 4, 4, 4},
                                {"P5", 5, 5, 5}};

  int n = sizeof(processes) / sizeof(processes[0]);

  printf("Gantt Chart: ");
  sjfPreemptive(processes, n);

  int completionTime[n];
  int turnaroundTime[n];
  int waitingTime[n];

  int totalTime = 0;

  for (int i = 0; i < n; i++) {
    totalTime += processes[i].burstTime;
    completionTime[i] = totalTime;
    turnaroundTime[i] = completionTime[i] - processes[i].arrivalTime;
    waitingTime[i] = turnaroundTime[i] - processes[i].burstTime;
  }

  printf("\n");
  printf("Process\tCT\tTAT\tWT\n");

  for (int i = 0; i < n; i++) {
    printf("%s\t\t%d\t%d\t%d\n", processes[i].id, completionTime[i],
           turnaroundTime[i], waitingTime[i]);
  }

  return 0;
}
