#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define LIMITE 1000

typedef struct {
    int variable;
    pthread_mutex_t mutex;
} compartido_t;

int main(void)
{
    compartido_t *datos_compartidos;

    datos_compartidos = mmap(NULL, sizeof(compartido_t),
                             PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_ANONYMOUS,
                             -1, 0);

    if (datos_compartidos == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    datos_compartidos->variable = 0;

    // Inicializar atributos del mutex para procesos
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&datos_compartidos->mutex, &attr);

    pid_t suma = fork();
    if (suma == 0) {
        for (int i = 0; i < LIMITE; i++) {
            pthread_mutex_lock(&datos_compartidos->mutex);
            datos_compartidos->variable += 1;
            pthread_mutex_unlock(&datos_compartidos->mutex);
        }
        exit(0);
    }

    pid_t resta = fork();
    if (resta == 0) {
        for (int i = 0; i < LIMITE; i++) {
            pthread_mutex_lock(&datos_compartidos->mutex);
            datos_compartidos->variable -= 1;
            pthread_mutex_unlock(&datos_compartidos->mutex);
        }
        exit(0);
    }

    // Esperar a los dos procesos hijos
    waitpid(suma, NULL, 0);
    waitpid(resta, NULL, 0);

    printf("Valor final de la variable: %d\n", datos_compartidos->variable);

    // Limpiar
    pthread_mutex_destroy(&datos_compartidos->mutex);
    pthread_mutexattr_destroy(&attr);
    munmap(datos_compartidos, sizeof(compartido_t));

    return 0;
}
