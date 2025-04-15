#include <stdio.h>

int main (void){
    int a = 5;
    int *p = NULL;

    printf("el valor de la variable a es: %d y su direccion es %p\n", a, &a);
    p=&a;
    printf("el puntero apunta a %p y esa direccion contiene el valor %d\n", p, *p);
    return 0;


}