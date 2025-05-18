#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>


int numeros[5];
long factoriales[5];
pthread_mutex_t mutex;


long factorial(int numero) {

	long resultado = 1;

	for(int i = 1; i<= numero; i++) {

		resultado = resultado * i;
	}
	return resultado;
}


void *hilo_calcular_pares() {

	for(int i = 0; i < 5; i++) {
		if(i % 2 == 0) {
			pthread_mutex_lock(&mutex);
			factoriales[i] = factorial(numeros[i]);
			pthread_mutex_unlock(&mutex);
		}
	}
	return NULL;

}
void *hilo_calcular_impares() {

	for(int i = 0; i < 5; i++) {
		if(i % 2 != 0) {
			pthread_mutex_lock(&mutex);
			factoriales[i] = factorial(numeros[i]);
			pthread_mutex_unlock(&mutex);
		}
	}
	return NULL;

}

int main() {

	int tuberia[2];
	pipe(tuberia);


	srand(time(NULL));

	for(int i = 0; i < 5; i++) {
		numeros[i] = (rand() % 20) + 1;
	}
	
    pthread_mutex_init(&mutex, NULL);
	pid_t pid = fork();

	if(pid < 0) {

		printf("error en el proceso\n");

	} else if(pid == 0) {


		pthread_t pares, impares;

		pthread_create(&pares, NULL, hilo_calcular_pares, NULL);
		pthread_create(&impares, NULL, hilo_calcular_impares, NULL);

		pthread_join(pares, NULL);
		pthread_join(impares, NULL);

		close(tuberia[0]);
		write(tuberia[1], factoriales, sizeof(factoriales));
		close(tuberia[1]);

	} else {
	    close(tuberia[1]);
	    
	    long factoriales_calculados[5];
	    
	    read(tuberia[0], factoriales_calculados, sizeof(factoriales_calculados));
	    close(tuberia[0]);
	    
	    printf("numeros: ");
	    for(int i = 0; i < 5; i++){
	      
	        printf(" %d ", numeros[i]);
	        
	    }
	    printf("\n");
	    
	    printf("factoriales_calculados: ");
	    for(int i = 0; i < 5; i++){
	        
	        printf(" %ld ", factoriales_calculados[i]);
	    }
	    
	    wait(NULL);

	}
	
	pthread_mutex_destroy(&mutex);



	return 0;
}


//Desarrolle un programa en C que implemente la siguiente funcionalidad:
//
//Cree un proceso padre que genere un array de 5 números aleatorios entre 1 y 20 (tipo entero). El array se llama números. El proceso también crea otro array de 5 elementos que inicialmente estará vacío, llamado “factoriales”. Utilizar un como tipo de variable el long.
//
//El proceso padre debe crear un proceso hijo utilizando fork().
//
//El proceso hijo debe crear 2 hilos (threads) utilizando pthread_create().
//
//Los hilos deben calcular el factorial de los números del array, de manera paralela, y almacenarlos en la posición adecuada dentro del array “factoriales. Es decir, el resultado de calcular el factorial del número que ocupa la posición 0 del array de números debe estar almacenado en la posición 0 del array de factoriales.
//
//El primer hilo procesa los números en posiciones pares (0, 2, 4)
//
//El segundo hilo procesa los números en posiciones impares (1, 3)
//
//Utilice un mutex para proteger el acceso a las variables compartidas cuando los hilos almacenen sus resultados.
//
//El array de resultados debe enviarse desde el proceso hijo al proceso padre utilizando una tubería (pipe). Si no podemos / sabemos / funciona mandar el array, hacerlo número a número
//
//El proceso padre debe mostrar cada número y su factorial.
//
//El proceso padre debe esperar a que el hijo termine antes de finalizar.
