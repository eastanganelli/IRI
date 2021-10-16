#include <time.h>
#include "conmalloc.h"
#include "connew.h"

#define MAX 6
#define MIN 3

void init_matriz(int** matriz, int alto, int ancho);
void imprimir_matriz(int** matriz, int alto, int ancho);

int main() {
    srand(time(NULL));

    int alto = -1, ancho = -1;

    alto  = rand() % (MAX - MIN) + MIN;
    ancho = rand() % (MAX - MIN) + MIN;
    printf("Matriz Con New, Delete y memcpy\n");
    { //Usando New, Delete y memcpy
        int** matriz = NULL;
        eMem ControlErrores = VACIO;
        matriz = crear_matrix_new(alto, ancho, &ControlErrores);

        //Revisamos nuestra variable de control de errores
        //Sino avisaremos al usuario y cerramos programa
        //La misma se retorna por derecha y la matriz por izquierda
        if (ControlErrores == NOMEM) {
            printf("ERROR CREAR MEMORIA CON NEW");
            return -1;
        }

        init_matriz(matriz, alto, ancho);

        printf("Impresion Pre-CambiarTamanyo\n");
        imprimir_matriz(matriz, alto, ancho);

        cambiar_matriz_tam_memcpy(&matriz, alto - 1);
        printf("\nImpresion Post-CambiarTamanyo\n");
        imprimir_matriz(matriz, alto - 1, ancho);

        eliminar_matrix_delete(matriz, alto - 1);

        if (matriz == NULL)
            printf("Matrix Eliminada Exitosamente");
    }

    printf("\n<----------------------------------------------------->\n\nMatriz Con Malloc, Calloc, Realloc y Free\n");

    { //Usando Malloc, Calloc, Realloc y Free
        int** matriz = NULL;
        matriz = crear_matrix_malloc(alto, ancho);

        //Revisamos nuestra matriz no sea nula
        //Sino avisaremos al usuario y cerramos programa
        if (matriz == NULL) {
            printf("ERROR CREAR MEMORIA CON MALLOC");
            return -1;
        }

        init_matriz(matriz, alto, ancho);

        printf("Impresion Pre-CambiarTamanyo\n");
        imprimir_matriz(matriz, alto, ancho);

        cambiar_matriz_tam_realloc(&matriz, alto - 1);
        printf("\nImpresion Post-CambiarTamanyo\n");
        imprimir_matriz(matriz, alto - 1, ancho);

        eliminar_matrix_free(matriz, alto - 1);

        if (matriz == NULL)
            printf("Matrix Eliminada Exitosamente");
    }

    return 0;
}

void init_matriz(int** matriz, int alto, int ancho) {
    for (int i = 0; i < alto; i++)
        for (int j = 0; j < ancho; j++)
            matriz[i][j] = rand() % (MAX - MIN) + MIN;
}

void imprimir_matriz(int** matriz, int alto, int ancho) {
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            printf("%d", matriz[i][j]);

            if (j + 1 < ancho) printf(" - ");
        } printf("\n");
    }
}