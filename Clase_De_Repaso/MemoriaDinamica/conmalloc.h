#include "gblheaders.h"

int** crear_matrix_malloc(int alto, int ancho) {
    //Inicializar el puntero con NULL
    int** aux = NULL;

    //Creamos el puntero
    aux = (int**)malloc(alto * sizeof(int*));

    //Es recomendable revisar que la memoria creada este
    //Sino tendremos problemas con nuestro programa
    /*
    if(aux == NULL)
        return aux;
    */
    
    //Creamos los vectores internos de nuestra matriz
    //Recordar con aux[i], almacenará la dirección de memoria
    //de nuestro vector interno --> Ver Figura 1
    for (int i = 0; i < alto; i++) {
        aux[i] = (int*)malloc(ancho * sizeof(int));
        //aux[i] = (int*)calloc(sizeof(int), ancho);
    }

    return aux;
}

void  cambiar_matriz_tam_realloc(int*** matriz, int altura) {
    //Realloc cambiara el tamaño del array principal
    //No es necesario castear ni asignar a la variable
    realloc(*matriz, sizeof(int**) * altura);
}

void eliminar_matrix_free(int**& matriz, int altura) {
    //Eliminamos cada vector que esta contenido dentro
    //del vector principal
    
    //Liberamos la memoria del vector en la posición i
    //Es muy importante hacer este for, sino quedará memoria sin liberar
    for (int i = 0; i < altura; i++) 
        free(matriz[i]); 

    //Liberamos el vector principal
    free(matriz);

    //Igualamos el puntero a NULL
    matriz = NULL;
}

//NOTAS AL PIE DE PAGINA
//1) Por qué debo castear el malloc/calloc?
////El malloc debe ser casteado para poder asignar a la varible, ie: int* = (int*)malloc(sizeof(int));
////Ejemplo explicativo: Si tengo un camión (int**), tengo que poder engancharle un trailer para camión,
////osea que, el trailer de camión puede ser utilizado para llegar otros vehiculos como autos ( (int**)malloc(sizeof(int*)) ).
////El auto (int*), puedo engancharlo con un trailer de motos ( (int*)malloc(sizeof(int)) ). [Moto => int]