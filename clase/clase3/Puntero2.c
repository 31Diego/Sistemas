#include <stdio.h>
#include <string.h>

int main(void)
{
    char str1[7] = "hola";
    char str2[] = "mundo";

    strcat(str1, str2);
    printf("la cadena concatenada es %s\n ", str1);
    return 0;
}