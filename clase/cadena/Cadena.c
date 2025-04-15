#include <stdio.h>
#include <string.h>

char buscarRepetido(char *cadena) {
    int i, j;
    for (i = 0; cadena[i] != '\0'; i++) {
        for (j = 0; j < i; j++) {
            if (cadena[i] == cadena[j]) {
                return cadena[i];
            }
        }
    }
    return '0'; 
}

int main() {
    char cadena[100];
    printf("Escribe algo: ");
    fgets(cadena, 100, stdin);
    
    char resultado = buscarRepetido(cadena);
    if (resultado != '0') {
        printf("Se repite primero: %c\n", resultado);
    } else {
        printf("Nada se repite.\n");
    }
    
    return 0;
}

