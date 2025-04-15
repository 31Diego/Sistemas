#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

static int *numero_compartido;
static sem_t *semaforo_sincro;

int main(void)
{
    pid_t lee, escribe;

    numero_compartido = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    semaforo_sincro = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(semaforo_sincro, 1, 0);

    lee = fork();
    if (lee > 0) {
        escribe = fork();
    }

    if (lee == 0) {
        printf("Introduce un número:\n");
        scanf("%d", numero_compartido);
        sem_post(semaforo_sincro);  
    }
    else if (escribe == 0) {
        sem_wait(semaforo_sincro);
        char tecla;
        printf("El número introducido fue: %d\n", *numero_compartido);
        printf("Pulsa cualquier tecla para terminar...\n");
        scanf(" %c", &tecla);
        printf("Soy el proceso escribe: ¡me voy!\n");
        exit(0);
    }
    else {
        while (wait(NULL) > 0);
    }

    sem_destroy(semaforo_sincro);
    munmap(numero_compartido, sizeof(int));
    munmap(semaforo_sincro, sizeof(sem_t));

    printf("Soy el proceso padre: ¡me voy!\n");
    return 0;
}






