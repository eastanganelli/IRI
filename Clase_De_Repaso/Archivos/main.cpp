#include "archivoscsv.h"
#include "archivosbin.h"



int main() {
    ptrEmpleado ListaEmpleados = NULL;
    ListaEmpleados = new sEmpleado[2];

    for(int i = 0; i < 2; i++)
        fprintf(archivo, "%d,%s,%s,%d\n", ListaEmpleados[i].dni, ListaEmpleados[i].nombreYApellido, ListaEmpleados[i].fecNac, ListaEmpleados[i].posicion);

    FILE* archivo = NULL;

    for (int i = 0; i < 2; i++)
        printf("%d,%s,%s,%d\n", ListaEmpleados[i].dni, ListaEmpleados[i].nombreYApellido, ListaEmpleados[i].fecNac, ListaEmpleados[i].posicion);

    
    
#pragma region Limpieza de Variables Dinámicas
    { //ListaEmpleados
        for (int i = 0; i < 2; i++)
            delete[] ListaEmpleados[i].nombreYApellido;
        delete[] ListaEmpleados;
    }

#pragma endregion


    return 0;
}