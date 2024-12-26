#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define MaxCrops 5
#define warehouseSize 5
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
char crops[MaxCrops] = {'R', 'W', 'P', 'S', 'M'};
char warehouse[warehouseSize] = {'N', 'N', 'N', 'N', 'N'};
pthread_mutex_t mutex;

void *Farmer(void *far) {
  int farmerId = *((int *)far);

  while (1) {
    char crop = crops[farmerId - 1];

    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < warehouseSize; i++) {
      if (warehouse[i] == 'N') {
        warehouse[i] = crop;
        printf("Farmer %d: Insert crop %c at %d\n", farmerId, crop, i);
        break;
      }
    }

    pthread_mutex_unlock(&mutex);
    sem_post(&full);

    sleep(1);
  }
}

void *ShopOwner(void *sho) {
  int shopOwnerId = *((int *)sho);

  while (1) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < warehouseSize; i++) {
      if (warehouse[i] != 'N') {
        char crop = warehouse[i];
        printf("Shop owner %d: Remove crop %c from %d\n", shopOwnerId, crop, i);
        warehouse[i] = 'N';
        break;
      }
    }

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    sleep(1);
  }
}

int main() {
  pthread_t Far[5], Sho[5];
  pthread_mutex_init(&mutex, NULL);
  sem_init(&empty, 0, warehouseSize);
  sem_init(&full, 0, 0);

  int farmerIds[5] = {1, 2, 3, 4, 5};
  int shopOwnerIds[5] = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; i++) {
    pthread_create(&Far[i], NULL, Farmer, &farmerIds[i]);
    pthread_create(&Sho[i], NULL, ShopOwner, &shopOwnerIds[i]);
  }

  sleep(10);

  for (int i = 0; i < 5; i++) {
    pthread_cancel(Far[i]);
    pthread_cancel(Sho[i]);
  }

  pthread_mutex_destroy(&mutex);
  sem_destroy(&empty);
  sem_destroy(&full);

  return 0;
}
