#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(void)
{
    int var1=10, var2=20;
    pid_t pid;
    printf("hola soy el proceso padre, el primero con pid %n\n", getpid);

    pid=fork();
    if(pid>0){
        puts("soy el proceso padre quedo a la espera de que acabe el hijo");
        while(wait(NULL)>0){
            printf("la var1 es %d y la var2 es %d, el hijo ha terminado", var1, var2);
        }
    }
    else if(pid==0){
        printf("soy el proceso %d y mi padre es el proceso %d\n", getpid(), getppid() );
        puts("introduce un numero: ");
        scanf("%d, &var1");
        puts("introduce otro numero:");
        scanf("%d", &var2);
        if (suma ==0 && res)
    }
}