#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>


int main(void){
    puts("este mensaje sale por la pantalla");
    exexlp("/bin/ls", "ls", NULL);
    puts("hola");
    return 0;
}