#include <stdio.h>

int main()
{
    int numero_usuario;
    int primer_numero_secuencia = 0;
    int segundo_numero_secuencia = 1;
    int proximo_numero_secuencia;

    printf("Introduce un numero: ");
    scanf("%d", &numero_usuario);

    if (numero_usuario > 0)
    {
        for (int i = 0; i < numero_usuario; i++)
        {
            if (i == 0)
            {
                printf("%d ", primer_numero_secuencia);
            }
            else if (i == 1)
            {
                printf("%d ", segundo_numero_secuencia);
            }
            else
            {
                proximo_numero_secuencia = primer_numero_secuencia + segundo_numero_secuencia;
                primer_numero_secuencia = segundo_numero_secuencia;
                segundo_numero_secuencia = proximo_numero_secuencia;
                printf("%d ", proximo_numero_secuencia);
            }
        }
    }
    else
    {
        numero_usuario = -numero_usuario;
        primer_numero_secuencia = 0;
        segundo_numero_secuencia = 1;

        for (int i = 2; i <= numero_usuario; i++)
        {
            proximo_numero_secuencia = primer_numero_secuencia + segundo_numero_secuencia;
            primer_numero_secuencia = segundo_numero_secuencia;
            segundo_numero_secuencia = proximo_numero_secuencia;
        }
        printf("%d", segundo_numero_secuencia);
    }

    printf("\n");
    return 0;
}


