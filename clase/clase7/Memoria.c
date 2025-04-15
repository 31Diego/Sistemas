#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/mman.h>

void terminar(int signo) {
    printf("Me largo!\n");
    exit(0);
}

int main() {
    int *shared_mem = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    signal(SIGUSR1, terminar);

    pid_t escritor = fork();
    if (escritor == 0) {
        // Proceso escritor
        *shared_mem = 42;  // Escribir un número en la memoria compartida
        printf("(Escritor) Número escrito: %d\n", *shared_mem);
        pause(); // Esperar señal de terminación
        exit(0);
    }

    pid_t lector = fork();
    if (lector == 0) {
        // Proceso lector
        sleep(1);  // Asegurar que el escritor haya escrito el número
        printf("(Lector) Número leído: %d\n", *shared_mem);
        pause(); // Esperar señal de terminación
        exit(0);
    }

    // Proceso padre
    printf("Pulse Enter para salir...\n");
    getchar();  // Esperar la tecla Enter

    // Terminar los procesos hijos
    kill(escritor, SIGUSR1);
    kill(lector, SIGUSR1);
    wait(NULL);
    wait(NULL);
    
    printf("(Padre) Me largo!\n");
    return 0;
}