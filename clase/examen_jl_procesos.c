#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <math.h>
#include <wait.h>
#include <sys/mman.h>

void master_f();
void escribir();
void calcula_primo();
void es_fibonnaci();

long double factorial (int);
int es_primo (long double);

static int *lanzar_fibonacci, *lanzar_primo;
static int *seguir_leyendo;//1 seguimos leyendo números, 0 acabamos
static int *hayDato;
static int *dato;
static long double *fact;


int main ()
{
	system("clear");
	lanzar_fibonacci = mmap(NULL, sizeof *lanzar_fibonacci, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	lanzar_primo = mmap(NULL, sizeof *lanzar_primo, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	seguir_leyendo = mmap(NULL, sizeof *seguir_leyendo, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	hayDato = mmap(NULL, sizeof *hayDato, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	dato = mmap(NULL, sizeof *dato, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	fact = mmap(NULL, sizeof *fact, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*lanzar_fibonacci=0;
	*lanzar_primo=0;
	*seguir_leyendo=1;
	*hayDato=0;
	
	pid_t master, escribe, primo, fibonacci;
	master=fork();
	if (master>0)
	{
		escribe=fork();
		if (escribe>0)
		{
			primo=fork();
			if (primo>0)
			{
				fibonacci=fork();
			}
		}
	}
	if (master==0)
	{
		master_f();
	}
	else if (escribe==0)
	{
		escribir();
	}
	else if (primo==0)
	{
		calcula_primo();
	}
	else if (fibonacci==0)
	{
		es_fibonnaci();
	}
	else
	{
		while(wait(NULL)>0);
	}
	

	return 0;
}

void master_f()
{
	while (*seguir_leyendo==1)
	{
		while(*hayDato==1) usleep(10);
		printf("Introduce un número:");
		scanf("%d", &*dato);
		if (*dato==-1)
		{
			*seguir_leyendo=0;
			*hayDato=1;
			break;
		}
		*hayDato=1;	
	}
	return;
}
void escribir()
{
	while (*seguir_leyendo==1)
	{
		while(*hayDato==0) usleep(10);
		if (*seguir_leyendo==0)break;
		printf("\nEl factorial de %d es %.0LF\nVoy a realizar los otros calculos", *dato, factorial(*dato));
		*fact=*fact-1;
		printf(" para %.0LF\n", *fact);
		*lanzar_fibonacci=1;
		*lanzar_primo=1;
		while(*lanzar_fibonacci!=0 || *lanzar_primo!=0)usleep(10);
		*hayDato=0;	
	}
	return;
}
long double factorial(int num)
{
	int i; 
	for (i=1, *fact=1;i<=num;i++)
	{
		*fact=*fact*i;
	}
	return *fact;
}
int es_primo (long double num)
{
	int flag=1;// 1 si es primo, 0 si no lo es
	for (long double i=2; i<num; i++)
	{
		if ((unsigned long long)num%(unsigned long long)i == 0)
		{
			flag=0;
			break;
		}
	}
	if (flag==1)
		return 1;
	else 
		return 0;
}
void calcula_primo()
{
	while (1)
	{
		while(*lanzar_primo==0)usleep(10);
		if (es_primo(*fact))
		{
			printf("El numero %.0LF es primo\n", *fact);
		}
		else
		{
			printf("El numero %.0LF no es primo\n", *fact);
		}
		*lanzar_primo=0;
	}	
	return;
}
void es_fibonnaci()
{
	while (1)
	{
		while(*lanzar_fibonacci==0)usleep(10);
		long double i, t1, t2, siguiente;
		for (t1 = 0, t2= 1; t2 <= *fact; ++i) {
			siguiente = t1 + t2;
			t1 = t2;
			t2 = siguiente;
		}
		if (t1==*fact)
		{
			printf("El numero %.0LF pertenece a la serie Fibonacci\n", *fact);
		}
		else
		{
			printf("El numero %.0LF no pertenece a la serie Fibonacci\n", *fact);
		}
		*lanzar_fibonacci=0;
	}
	
	return;
}
