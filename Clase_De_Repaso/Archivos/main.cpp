#include "archivos.h"
#include "archivoscsv.h"
#include "archivosbin.h"

void imprimir_lista_empleados(ptrEmpleado Listado, int tam);
void imprimir_db_empleados(ptrDB Listado, int tam);

int main() {
    ptrEmpleado ListaEmpleados = NULL; int largoEmpleados = 0;
    ptrDB BaseDeDatos = NULL; int largoDB = 0;
    
    FILE* EmpleadosFile = NULL;
    FILE* DBFile = NULL;

    char* pathDB = new char[96];
    strcpy(pathDB, EmpleadosDAT);

    char* pathEmpleados = new char[96];
    strcpy(pathEmpleados, EmpleadosCSV);

    DBFile = abrir_archivo(pathDB, LECBIN);
    EmpleadosFile = abrir_archivo(pathEmpleados, LEC);

    if (DBFile == NULL) {
        printf("El Archivo No Existe La DB!\nAhora crearemos uno\n");
        DBFile = abrir_archivo(pathDB, ESCRIBIN);
        init_base_de_datos(DBFile, miniDB, 6);
    } else {
        BaseDeDatos = leer_base_de_datos(DBFile, &largoDB);
        imprimir_db_empleados(BaseDeDatos, largoDB);
    }

    if (EmpleadosFile == NULL) {
        printf("El Archivo No Existe La Lista de Empleados!\nAhora crearemos uno\n");
        EmpleadosFile = abrir_archivo(pathEmpleados, ESCRI);
        init_datos_empleados(EmpleadosFile, miniEmpleados, 6);
    }
    else {
        ListaEmpleados = leer_datos_empleados(EmpleadosFile, &largoEmpleados);
        imprimir_lista_empleados(ListaEmpleados, largoEmpleados);
    }

    cerrar_archivo(DBFile);
    cerrar_archivo(EmpleadosFile);
    
    
#pragma region Limpieza de Variables Dinámicas
    //ListaEmpleados
        delete[] ListaEmpleados;
    //ListaDB
        delete[] BaseDeDatos;

#pragma endregion
    return 0;
}

void imprimir_lista_empleados(ptrEmpleado Listado, int tam) {
    printf("\nImprimir lista de Empleados\n");
    for (int i = 0; i < tam; i++) {
        sEmpleado aux = Listado[i];
        printf("%d,%s,%s,%d\n", aux.dni, aux.nombreYApellido, aux.fecNac, aux.posicion);
    }
}

void imprimir_db_empleados(ptrDB Listado, int tam) {
    printf("\nImprimir Base de Datos\n");
    for (int i = 0; i < tam; i++)
        printf("%d,%s,%d\n", Listado[i].dni, Listado[i].contrasenya, Listado[i].miEstado);
}