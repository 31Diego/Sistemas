#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_DATOS 10
#define MAX_VALOR 50

int datos[NUM_DATOS];
int suma = 0;
int producto = 1; 

pthread_mutex_t mutex;

void *hilo_suma()
{
    for (int i = 0; i < NUM_DATOS; i++)
    {
        pthread_mutex_lock(&mutex);
        suma += datos[i];
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

void *hilo_producto()
{
    for (int i = 0; i < NUM_DATOS; i++)
    {
        pthread_mutex_lock(&mutex);
        producto *= datos[i];
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

int main()
{
    int tuberia[2];
    pipe(tuberia);

    srand(time(NULL));
    for (int i = 0; i < NUM_DATOS; i++)
    {
        datos[i] = (rand() % MAX_VALOR) + 1;
        printf("dato:[%d] = %d\n", i, datos[i]);
    }

    pid_t pid = fork();

    if (pid == 0)
    {
        close(tuberia[0]);

        pthread_mutex_init(&mutex, NULL);

        pthread_t t1, t2;
        pthread_create(&t1, NULL, hilo_suma, NULL);
        pthread_create(&t2, NULL, hilo_producto, NULL);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        pthread_mutex_destroy(&mutex);

        write(tuberia[1], &suma, sizeof(int));
        write(tuberia[1], &producto, sizeof(long long));

        close(tuberia[1]);
        exit(0);
    }
    else
    {
        close(tuberia[1]);

        wait(NULL);

        int resultado_suma;
        long long resultado_producto;

        read(tuberia[0], &resultado_suma, sizeof(int));
        read(tuberia[0], &resultado_producto, sizeof(long long));
        close(tuberia[0]);

        printf("\nsoy el padre y he recibido los datos y las operaciones:\n");
        printf("suma: %d\n", resultado_suma);
        printf("producto: %lld\n", resultado_producto);
    }

    return 0;
}

