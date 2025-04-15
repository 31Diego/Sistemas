#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pthread.h>

void *funcion1();
void *funcion2();
int numero = 0;

pthread_t hilo1, hilo2;

int main(void)
{
    printf("soy el proceso padre con ID %d y mi hilo de ejecucion tiene ID %d\n", getpid(), (unsigned int)pthread_self());

    pthread_create(&hilo1, NULL, &funcion1, NULL);
    pthread_create(&hilo2, NULL, &funcion2, NULL);
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    printf("soy el proceso padre y el valor de la variable es %d\n", numero);

    return 0;
}
void *funcion1()
{
    printf("soy el proceso %d, hilo %d/n", getpid(), (unsigned int)pthread_self());
    numero = 7;
    return 0;
}

void *funcion2()
{
    sleep(1);

    printf("soy el proceso %d, hilo %d/n", getpid(), (unsigned int)pthread_self());
    printf("soy el hilo dos, la variable vale %d y la voy a cambiar a 10\n", numero);

    numero = 10;
    return 0;
}