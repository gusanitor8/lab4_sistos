#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_PROCESOS 5
#define MAX_RECURSOS 3

int disponibles[MAX_RECURSOS];
int asignados[MAX_PROCESOS][MAX_RECURSOS];
int maximo[MAX_PROCESOS][MAX_RECURSOS];
int necesarios[MAX_PROCESOS][MAX_RECURSOS];
bool finalizado[MAX_PROCESOS];

void inicializar() {
    // Inicializar recursos disponibles
    for (int i = 0; i < MAX_RECURSOS; i++) {
        disponibles[i] = 0;
        for (int j = 0; j < MAX_PROCESOS; j++) {
            asignados[j][i] = 0;
            maximo[j][i] = 0;
            necesarios[j][i] = 0;
        }
    }

    // Definir recursos disponibles
    disponibles[0] = 10;
    disponibles[1] = 5;
    disponibles[2] = 7;

    // Definir máximos recursos necesarios por proceso
    maximo[0][0] = 7;
    maximo[0][1] = 5;
    maximo[0][2] = 3;

    maximo[1][0] = 3;
    maximo[1][1] = 2;
    maximo[1][2] = 2;

    maximo[2][0] = 9;
    maximo[2][1] = 0;
    maximo[2][2] = 2;

    maximo[3][0] = 2;
    maximo[3][1] = 2;
    maximo[3][2] = 2;

    maximo[4][0] = 4;
    maximo[4][1] = 3;
    maximo[4][2] = 3;

    // Inicializar necesarios
    for (int i = 0; i < MAX_PROCESOS; i++) {
        for (int j = 0; j < MAX_RECURSOS; j++) {
            necesarios[i][j] = maximo[i][j] - asignados[i][j];
        }
        finalizado[i] = false;
    }
}

bool puedeEjecutar(int proceso) {
    // Verificar si el proceso puede ejecutar de manera segura
    for (int i = 0; i < MAX_RECURSOS; i++) {
        if (necesarios[proceso][i] > disponibles[i])
            return false;
    }
    return true;
}

void asignarRecursos(int proceso) {
    // Asignar recursos al proceso
    for (int i = 0; i < MAX_RECURSOS; i++) {
        disponibles[i] -= necesarios[proceso][i];
        asignados[proceso][i] += necesarios[proceso][i];
        necesarios[proceso][i] = 0;
    }
    finalizado[proceso] = true;
}

void liberarRecursos(int proceso) {
    // Liberar recursos asignados por el proceso
    for (int i = 0; i < MAX_RECURSOS; i++) {
        disponibles[i] += asignados[proceso][i];
        asignados[proceso][i] = 0;
    }
    finalizado[proceso] = false;
}

void simularEjecucion() {
    // Simula la ejecución continua del sistema
    srand(time(NULL));

    while (true) {
        // Seleccionar un proceso aleatorio
        int proceso = rand() % MAX_PROCESOS;

        // Solicitar recursos para el proceso
        printf("Proceso %d solicita recursos...\n", proceso);
        if (puedeEjecutar(proceso)) {
            asignarRecursos(proceso);
            printf("Recursos asignados al proceso %d.\n", proceso);
        } else {
            printf("No se pueden asignar recursos al proceso %d. Esperando...\n", proceso);
        }

        // Liberar recursos aleatorios
        proceso = rand() % MAX_PROCESOS;
        printf("Proceso %d libera recursos...\n", proceso);
        liberarRecursos(proceso);
        printf("Recursos liberados del proceso %d.\n", proceso);

        // Verificar si todos los procesos han finalizado
        bool todosFinalizados = true;
        for (int i = 0; i < MAX_PROCESOS; i++) {
            if (!finalizado[i]) {
                todosFinalizados = false;
                break;
            }
        }
        if (todosFinalizados) break;
    }
}

int main() {
    inicializar();

    // Ejecutar la simulación continua del sistema
    simularEjecucion();

    return 0;
}
