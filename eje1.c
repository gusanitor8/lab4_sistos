#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

// declaramos los semaforos
int semaphore_a = 1;
int semaphore_b = 1;

// declaramos las funciones de los semaforos
void wait_(int s){
    printf("bloqueando semaforo\n");
    while(s <= 0);
    s--;
}

void signal_(int s){
    printf("liberando semaforo\n");
    s++;
}

// declaramos la funcion del hilo
void* thread_function_a(){
    wait_(semaphore_a);
    wait_(semaphore_b);
    printf("hilo a\n");
    for (int i = 0; i < 1000000; i++);

    signal_(semaphore_a);
    signal_(semaphore_b);
}

void* thread_function_b(){
    wait_(semaphore_b);
    wait_(semaphore_a);

    printf("hilo b\n");
    for (int i = 0; i < 1000000; i++);

    signal_(semaphore_b);
    signal_(semaphore_a);
}

void process_creation(){    
    pthread_t thread_id_a;
    pthread_t thread_id_b;

    pthread_create(&thread_id_a, NULL, thread_function_a, NULL);
    pthread_create(&thread_id_b, NULL, thread_function_b, NULL);

    pthread_join(thread_id_a, NULL);
    pthread_join(thread_id_b, NULL);
}


int main(){
    process_creation();
    // while (true){
    //    process_creation();
    // }
    return 0;
}