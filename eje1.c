#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


// Semaforos para los recursos
pthread_mutex_t recurso1, recurso2;

// Función para el proceso 1
void *proceso1(void *arg) {
  while (1) {
    // Intenta adquirir el recurso 1
    pthread_mutex_lock(&recurso1);
    printf("Proceso 1 adquirió el recurso 1\n");

    // Intenta adquirir el recurso 2
    pthread_mutex_lock(&recurso2);
    printf("Proceso 1 adquirió el recurso 2\n");

    // Libera los recursos en orden inverso
    pthread_mutex_unlock(&recurso2);
    pthread_mutex_unlock(&recurso1);

    // Espera un tiempo aleatorio
    sleep(rand() % 5);
  }
  return NULL;
}

// Función para el proceso 2
void *proceso2(void *arg) {
  while (1) {
    // Intenta adquirir el recurso 2
    pthread_mutex_lock(&recurso2);
    printf("Proceso 2 adquirió el recurso 2\n");

    // Intenta adquirir el recurso 1
    pthread_mutex_lock(&recurso1);
    printf("Proceso 2 adquirió el recurso 1\n");

    // Libera los recursos en orden inverso
    pthread_mutex_unlock(&recurso1);
    pthread_mutex_unlock(&recurso2);

    // Espera un tiempo aleatorio
    sleep(rand() % 5);
  }
  return NULL;
}

int main() {
  // Inicializa los semaforos
  pthread_mutex_init(&recurso1, NULL);
  pthread_mutex_init(&recurso2, NULL);

  // Crea los hilos
  pthread_t hilo1, hilo2;
  pthread_create(&hilo1, NULL, proceso1, NULL);
  pthread_create(&hilo2, NULL, proceso2, NULL);

  // Espera a que los hilos terminen (no terminarán)
  pthread_join(hilo1, NULL);
  pthread_join(hilo2, NULL);

  return 0;
}
