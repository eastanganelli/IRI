#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define CSVfile "misempleados.csv"

enum puesto { DISENYADOR, PROGRAMADOR, ADMINISTRACION, RECURSOSHUMANOS };
typedef enum puesto ePuesto;

struct empleado {
    int dni;
    char* nombreYApellido;
    char* fecNac;
    ePuesto posicion;
};
typedef struct empleado sEmpleado;
typedef sEmpleado* ptrEmpleado; // ptrEmpleado = struct empleado*;

int main() {
    ptrEmpleado ListaEmpleados = NULL;
    ListaEmpleados = new sEmpleado[2];
    //ListaEmpleados = (ptrEmpleado)malloc(sizeof(sEmpleado)*5);

    /*
    {
        ListaEmpleados[0].dni = 323232;
        ListaEmpleados[0].fecNac[0] = 31;
        ListaEmpleados[0].fecNac[1] = 5;
        ListaEmpleados[0].fecNac[2] = 1995;
        ListaEmpleados[0].posicion = PROGRAMADOR;
        ListaEmpleados[0].nombreYApellido = new char[25];
        strcpy(ListaEmpleados[0].nombreYApellido, "pedro picapiedra");

        ListaEmpleados[1].dni = 498345;
        ListaEmpleados[1].fecNac[0] = 27;
        ListaEmpleados[1].fecNac[1] = 12;
        ListaEmpleados[1].fecNac[2] = 1993;
        ListaEmpleados[1].posicion = DISENYADOR;
        ListaEmpleados[1].nombreYApellido = new char[25];
        strcpy(ListaEmpleados[1].nombreYApellido, "vilma picapiedra");
    }

    FILE* archivo = NULL;
    archivo = fopen(CSVfile, "w+");
    if(archivo == NULL)
        return -1;

    for(int i = 0; i < 2; i++)
        fprintf(archivo, "%d,%s,%s,%d\n", ListaEmpleados[i].dni, ListaEmpleados[i].nombreYApellido, ListaEmpleados[i].fecNac, ListaEmpleados[i].posicion);
    */

    FILE* archivo = NULL;
    archivo = fopen(CSVfile, "r+");
    if(archivo == NULL)
        return -1;

    for(int i = 0; i < 2; i++) {
        int dni;
        ePuesto posicion;
        char auxnomape[25], auxfecnac[15];
        fscanf(archivo, "%d,%[^,],%[^,],%d", &dni, &auxnomape, &auxfecnac, &posicion);
        ListaEmpleados[i].dni = dni;
        ListaEmpleados[i].posicion = posicion;
        ListaEmpleados[i].nombreYApellido = new char[25];
        ListaEmpleados[i].fecNac = new char[12];
        strcpy(ListaEmpleados[i].nombreYApellido, auxnomape);
        strcpy(ListaEmpleados[i].fecNac, auxfecnac);
    }

    for(int i = 0; i < 2; i++)
        printf("%d,%s,%s,%d\n", ListaEmpleados[i].dni, ListaEmpleados[i].nombreYApellido, ListaEmpleados[i].fecNac, ListaEmpleados[i].posicion);

    fclose(archivo);
    for(int i = 0; i < 2; i++)
        delete[] ListaEmpleados[i].nombreYApellido;
    delete[] ListaEmpleados;

    return 0;
}

/*
enum memoria { VACIO, AMEM, NOMEM };
typedef enum memoria eMem;

int** crear_matrix_new(int alto, int ancho, eMem* ESTADO);
int** crear_matrix_c(int alto, int ancho);

int main() {
    srand(time(NULL));
    int** matriz = NULL;
    int** matriz2 = NULL;
    eMem ControlErrores = VACIO;
    matriz = crear_matrix_new(3,4,&ControlErrores);

    if(ControlErrores == NOMEM) {
        printf("ERROR CREAR MEMORIA CON NEW");
        return 0;
    }

    matriz2 = crear_matrix_c(3, 4);

    if(matriz == NULL) {
        printf("ERROR CREAR MEMORIA CON MALLOC");
        return 0;
    }

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 4; j++) {
            matriz2[i][j] = rand() % 15;
            matriz[i][j]  = rand() % 15;
        }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++)
            printf(" %d -", matriz[i][j]);
        printf("\n");
    }
    printf("\n\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++)
            printf(" %d -", matriz2[i][j]);
        printf("\n");
    }

    for(int i = 0; i < 3; i++)
        delete[] matriz[i];
    delete[] matriz;

    for(int i = 0; i < 3; i++)
        free(matriz2[i]);
    free(matriz2);

    return 0;
}

int** crear_matrix_new(int alto, int ancho, eMem* ESTADO) {
    int** aux = NULL;
    aux = new int*[alto];
    if(aux == NULL) {
        *ESTADO = NOMEM;
        return NULL;
    }
    int i;
    for(i = 0; i < alto; i++)
        aux[i] = new int[ancho];


    *ESTADO = AMEM;
    return aux;
}

int** crear_matrix_c(int alto, int ancho) {
    int** aux = NULL;
    aux = (int**)malloc(alto*sizeof(int*));
    //new = * => new int* => **
    int i;
    for(i = 0; i < alto; i++)
        aux[i] = (int*)malloc(ancho*sizeof(int));

    return aux;
}
*/
