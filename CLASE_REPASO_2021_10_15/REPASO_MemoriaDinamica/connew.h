#include "gblheaders.h"

enum memoria { VACIO, AMEM, NOMEM };
typedef enum memoria eMem;

// int** crear_matrix_new(int alto, int ancho, eMem* ESTADO)
// Recibe alto, ancho de la matriz y un Estado puntero del tipo eMem
// Retorna un puntero doble del tipo int por izq y por derecha
// se devuelve el error
int** crear_matrix_new(int alto, int ancho, eMem* ESTADO) {
    // Inicializar el puntero con NULL
    int** aux = NULL;

    // Creamos el puntero
    aux = new int* [alto];

    if (aux == NULL) {
        *ESTADO = NOMEM;
        return NULL;
    }
    
    // Creamos los vectores internos de nuestra matriz
    // Recordar con aux[i], almacenará la dirección de memoria
    // de nuestro vector interno --> Ver Figura 1
    for (int i = 0; i < alto; i++)
        aux[i] = new int[ancho];


    *ESTADO = AMEM;
    return aux;
}

// void cambiar_matriz_tam_memcpy(int*** matriz, int altura)
// Recibe una matriz con puntero triple tipo int y la nueva altura
// Se devuelve la matriz utilizando retorno por derecha
void cambiar_matriz_tam_memcpy(int*** matriz, int altura) {
    // Para usar el memcpy, se tiene que incluir
    // la libreria string.h [ include <string.h> ]

    // Crear un varible puntero auxiliar
    int** nuevaMatriz = new int* [altura];

    // memcpy es una función que copia memoria de un puntero
    // a otro.
    // Este metodo sería el equivalente a realloc
    memcpy(nuevaMatriz, *matriz, sizeof(int**) * altura);

    // Eliminamos nuestra matriz
    delete[] * matriz;

    // Asignamos nuestra nueva matriz al puntero
    // que recibimos por referencia
    *matriz = nuevaMatriz;
}

void eliminar_matrix_delete(int**& matriz, int altura) {
    // Eliminamos cada vector que esta contenido dentro
    // del vector principal

    // Liberamos la memoria del vector en la posición i
    // Es muy importante hacer este for, sino quedará memoria sin liberar
    for (int i = 0; i < altura; i++)
        delete [] matriz[i];

    // Liberamos el vector principal
    delete [] matriz;

    // Igualamos el puntero a NULL
    matriz = NULL;
}

// NOTAS AL PIE DE PAGINA
// 1) new = * => new int* => **