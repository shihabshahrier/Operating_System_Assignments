#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAX 10
#define BUFLEN 6
#define NUMTHREAD 2

void *consumer(void *id);
void *producer(void *id);

char buffer[BUFLEN];
char source[BUFLEN];
int pCount = 0;
int cCount = 0;
int buflen;

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
int thread_id[NUMTHREAD] = {0, 1};
int i = 0;
int j = 0;

int main() {
  pthread_t thread[NUMTHREAD];

  strncpy(source, "abcdef", BUFLEN);
  buflen = strlen(source);

  pthread_create(&thread[0], NULL, producer, &thread_id[0]);
  pthread_create(&thread[1], NULL, consumer, &thread_id[1]);

  pthread_join(thread[0], NULL);
  pthread_join(thread[1], NULL);

  return 0;
}

void *producer(void *id) {
  int tid = *((int *)id);

  while (pCount < MAX) {
    pthread_mutex_lock(&count_mutex);

    while (i == BUFLEN)
      pthread_cond_wait(&full, &count_mutex);

    buffer[i++] = source[pCount % buflen];
    printf("%d produced  %c  by Thread  %d\n", pCount, buffer[i - 1], tid);

    pCount++;

    pthread_cond_signal(&nonEmpty);
    pthread_mutex_unlock(&count_mutex);

    sleep(1);
  }

  pthread_exit(NULL);
}

void *consumer(void *id) {
  int tid = *((int *)id);

  while (cCount < MAX) {
    pthread_mutex_lock(&count_mutex);

    while (i == 0)
      pthread_cond_wait(&nonEmpty, &count_mutex);

    printf("%d consumed  %c  by Thread  %d\n", cCount, buffer[i - 1], tid);
    buffer[i - 1] = '\0';
    i--;

    cCount++;

    pthread_cond_signal(&full);
    pthread_mutex_unlock(&count_mutex);

    sleep(1);
  }

  pthread_exit(NULL);
}
