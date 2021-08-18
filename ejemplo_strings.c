#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define FIN '\n'
#define N	  15
#define BLK   4

char* nuevo_string(int tam);
void anadir_texto(char* string_, int tam);

int main()
{
    const char ejemplo[N] = "Hola_Mundo";
    int tam_String = 0;
    char* string_ = NULL;

    tam_String = strlen(ejemplo);

    string_ = nuevo_string(tam_String);
    if (string_ == NULL)
        return 0;

    strcpy(string_, ejemplo);

    printf("Pre Texto: %s\n", string_);

    anadir_texto(string_, tam_String);

    printf("Post Texto: %s\n", string_);

    printf("Texto: %s [0x%u]\n", string_, &string_);

    free(string_);

    return 0;
}

char* nuevo_string(int tam)
{
    char* aux = NULL;
    aux = (char*)malloc(tam * sizeof(char));

    //Esta es otra forma de crear arreglos o arrays
    // aux = (char*)calloc(tamanio, sizeof(char));


    return aux;
}

void anadir_texto(char* string_, int tam)
{
    char* texto_in = NULL;
    char lectura;
    int i = 0;

    texto_in = (char*)malloc(sizeof(char) * BLK);
    if (texto_in == NULL)
        return;
    *texto_in = '\0';

    printf("Ingrese un string [Terminar con ENTER]: ");

    do
    {
        if (i >= strlen(texto_in))
            texto_in = (char*)realloc(texto_in, (i + BLK) * sizeof(char));

        scanf("%c", &lectura);
        fflush(stdin);
        if (lectura == FIN) {
            *(texto_in + i) = '\0';
            break;
        }

        texto_in[i] = lectura;
        i++;
    }
    while (lectura != FIN);

    if(strcmp(string_, texto_in) > 0)
        printf("El String Derecha es mas grande\n");
    else if(strcmp(string_, texto_in) < 0)
        printf("El String izquierda es mas grande\n");
    else
        printf("Ambos String son iguales\n");

    strcat(string_, texto_in);

    free(texto_in);
}
