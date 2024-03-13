#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Número de filósofos
#define NUM_FILOSOFOS 5

// Semaforos para los tenedores
pthread_mutex_t tenedores[NUM_FILOSOFOS];

// Función para pensar
void pensar(int id) {
  printf("Filosofo %d pensando...\n", id);
  sleep(rand() % 5);
}

// Función para comer
void comer(int id) {
  printf("Filosofo %d comiendo...\n", id);
  sleep(rand() % 5);
}

// Función para el filósofo
void *filosofo(void *arg) {
  int id = *(int *)arg;
  int tenedor_izquierdo = id;
  int tenedor_derecho = (id + 1) % NUM_FILOSOFOS;

  while (1) {
    pensar(id);

    // Intenta adquirir el tenedor izquierdo
    pthread_mutex_lock(&tenedores[tenedor_izquierdo]);
    printf("Filosofo %d tomó el tenedor izquierdo\n", id);

    // Intenta adquirir el tenedor derecho
    pthread_mutex_lock(&tenedores[tenedor_derecho]);
    printf("Filosofo %d tomó el tenedor derecho\n", id);

    comer(id);

    // Libera los tenedores en orden inverso
    pthread_mutex_unlock(&tenedores[tenedor_derecho]);
    pthread_mutex_unlock(&tenedores[tenedor_izquierdo]);
  }

  return NULL;
}

int main() {
  // Inicializa los semaforos
  for (int i = 0; i < NUM_FILOSOFOS; i++) {
    pthread_mutex_init(&tenedores[i], NULL);
  }

  // Crea los hilos
  pthread_t hilos[NUM_FILOSOFOS];
  int ids[NUM_FILOSOFOS];
  for (int i = 0; i < NUM_FILOSOFOS; i++) {
    ids[i] = i;
    pthread_create(&hilos[i], NULL, filosofo, &ids[i]);
  }

  // Espera a que los hilos terminen (no terminarán)
  for (int i = 0; i < NUM_FILOSOFOS; i++) {
    pthread_join(hilos[i], NULL);
  }

  return 0;
}
