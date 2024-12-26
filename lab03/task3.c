#include <stdbool.h>
#include <stdio.h>

struct Process {
  char name[3];
  int arrivalTime;
  int burstTime;
  int priority;
  int remainingTime;
};

void priorityScheduling(struct Process processes[], int n) {
  int currentTime = 0;
  int completed = 0;
  int queueSize = 0;
  struct Process *currentProcess = NULL;
  int completionTimes[n];
  int turnaroundTimes[n];
  int waitingTimes[n];

  while (completed < n) {
    for (int i = 0; i < n; i++) {
      if (processes[i].arrivalTime <= currentTime &&
          processes[i].remainingTime > 0) {
        if (currentProcess == NULL ||
            processes[i].priority < currentProcess->priority) {
          if (currentProcess != NULL) {
            currentProcess->remainingTime +=
                currentTime - processes[i].arrivalTime;
          }
          currentProcess = &processes[i];
        }
      }
    }

    if (currentProcess == NULL && queueSize > 0) {
      int highestPriorityIdx = 0;
      for (int i = 1; i < queueSize; i++) {
        if (processes[i].priority < processes[highestPriorityIdx].priority) {
          highestPriorityIdx = i;
        }
      }
      currentProcess = &processes[highestPriorityIdx];
      currentProcess->remainingTime +=
          currentTime - currentProcess->arrivalTime;
    }

    if (currentProcess != NULL) {
      printf("%s ", currentProcess->name);
      currentProcess->remainingTime--;

      if (currentProcess->remainingTime == 0) {
        currentProcess->remainingTime = -1;
        completed++;
        queueSize--;
        completionTimes[completed - 1] = currentTime + 1;
        currentProcess = NULL;
      }
    } else {
      printf("Idle ");
    }

    currentTime++;
  }
  printf("\n\n");

  printf("Process\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++) {
    turnaroundTimes[i] = completionTimes[i] - processes[i].arrivalTime;
    waitingTimes[i] = turnaroundTimes[i] - processes[i].burstTime;
    if (waitingTimes[i] < 0) {
      waitingTimes[i] = 0;
    }
    printf("%s\t\t%d\t%d\t%d\n", processes[i].name, completionTimes[i],
           turnaroundTimes[i], waitingTimes[i]);
  }
}

int main() {
  struct Process processes[] = {{"P1", 0, 15, 2, 15},
                                {"P2", 14, 5, 4, 5},
                                {"P3", 3, 10, 0, 10},
                                {"P4", 9, 22, 3, 22},
                                {"P5", 7, 16, 1, 16}};

  int n = sizeof(processes) / sizeof(processes[0]);

  printf("Gantt chart:\n");
  priorityScheduling(processes, n);

  return 0;
}
