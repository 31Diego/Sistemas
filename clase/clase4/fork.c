#include <stdio.h>
#include <unistd.h>


int main(void){
    fork();
    fork();
    fork();

    printf("holamundo %d\n", getpid);
    return 0;
    
}