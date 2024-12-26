#include <stdbool.h>
#include <stdio.h>

struct Process {
  char id[3];
  int arrivalTime;
  int burstTime;
  int remainingTime;
};

void roundRobin(struct Process processes[], int n, int timeQuantum) {
  int currentTime = 0;
  bool completed[n];

  for (int i = 0; i < n; i++) {
    completed[i] = false;
    processes[i].remainingTime = processes[i].burstTime;
  }

  while (1) {
    bool allCompleted = true;

    for (int i = 0; i < n; i++) {
      if (processes[i].arrivalTime <= currentTime &&
          processes[i].remainingTime > 0) {
        allCompleted = false;

        if (processes[i].remainingTime <= timeQuantum) {
          currentTime += processes[i].remainingTime;
          processes[i].remainingTime = 0;
        } else {
          currentTime += timeQuantum;
          processes[i].remainingTime -= timeQuantum;
        }

        printf("%s ", processes[i].id);
      }
    }

    if (allCompleted) {
      break;
    }
  }

  printf("\n");
}

int main() {
  struct Process processes[] = {
      {"P1", 0, 8, 0}, {"P2", 1, 5, 0}, {"P3", 2, 10, 0}, {"P4", 3, 11, 0}};

  int n = sizeof(processes) / sizeof(processes[0]);
  int timeQuantum = 6;

  printf("Gantt Chart: ");
  roundRobin(processes, n, timeQuantum);

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
