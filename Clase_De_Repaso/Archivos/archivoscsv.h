#include "gblheader.h"

#define EmpleadosCSV "misempleados.csv"
#define BLK 3

enum puesto { DISENYADOR, PROGRAMADOR, ADMINISTRACION, RECURSOSHUMANOS };
typedef enum puesto ePuesto;

struct empleado {
    int dni;
    char nombreYApellido[85];
    char fecNac[11];
    ePuesto posicion;
};
typedef struct empleado sEmpleado;
typedef sEmpleado* ptrEmpleado; // ptrEmpleado = struct empleado*;

sEmpleado miniEmpleados[6] = {
    { 232323, "Cindy Lauper", "25/03/1963", DISENYADOR },
    { 932425, "John Van Halen", "01/12/1955", PROGRAMADOR },
    { 734356, "James Hetfield", "25/09/1985", ADMINISTRACION },
    { 234323, "Lemmy Kilmister", "31/05/1995", RECURSOSHUMANOS },
    { 232343, "Amy Lee", "13/04/1980", PROGRAMADOR },
    { 212312, "Tom Arya", "06/03/1946", DISENYADOR }
};

// void realloc_empleados(ptrEmpleado* Listado, int longitud)
// Cambia de forma dinámica, el tamaño del Array Listado
void realloc_empleados(ptrEmpleado* Listado, int longitud) {
    // Creamos el array la nueva longitud
    ptrEmpleado auxArray = new sEmpleado[longitud];

    // Copiamos los datos del Array de Origen al Array Nuevo
    memcpy(auxArray, *Listado, longitud * sizeof(sEmpleado));

    // Borramos el puntero del viejo Array
    delete[] * Listado;

    // Retornamos el nuevo Array;
    *Listado = auxArray;
}

// void init_datos_empleados(FILE* csvEmpleados, sEmpleado Listado[6], int tamListado)
// Esta función inicializa el archivo con datos, en caso de no existir
void init_datos_empleados(FILE* csvEmpleados, sEmpleado Listado[6], int tamListado) {
    int i = 0;
    for (i = 0; i < tamListado; i++)
        fprintf(csvEmpleados, "%d,%s,%s,%d\n", miniEmpleados[i].dni, miniEmpleados[i].nombreYApellido, miniEmpleados[i].fecNac, miniEmpleados[i].posicion);
}

// void imprimir_datos_empleados(FILE* csvEmpleados, ptrEmpleado Listado, int tamListado)
// Imprime los datos del Array Listado en el archivo CSV 
// Documentación: https://www.geeksforgeeks.org/csv-file-management-using-c/
void imprimir_datos_empleados(FILE* csvEmpleados, ptrEmpleado Listado, int tamListado) {
    int i = 0;

    // El fprintf es como el printf, solo que tenemos que pasarle un puntero del tipo FILE
    // para que pueda escribir en el archivo.
    // Recuerden que hay que seperar los datos con ' , '!!
    for (i = 0; i < tamListado; i++)
        fprintf(csvEmpleados, "%d,%s,%s,%d\n", Listado[i].dni, Listado[i].nombreYApellido, Listado[i].fecNac, Listado[i].posicion);
}

// ptrEmpleado leer_datos_empleados(FILE* csvEmpleados, int* tam_total)
// Lee los datos del archivo csvEmpleados, y devuelve por derecha
// la cantidad de elementos obtenidos del archivo, por izq se retorna
// el listado obtenido
ptrEmpleado leer_datos_empleados(FILE* csvEmpleados, int* tam_total) {
    int i = 0, tam = BLK;
    // Creamos un Listado de struct empleado* o ptrEmpleado
    // El new tiene que ser con sEmpleado, si usamos ptrEmpleado
    // estariamos devoliendo un puntero doble [[ Revisar Notas del archivo de connew.h ]]
    ptrEmpleado Listado = new sEmpleado[BLK];

    for (i = 0; !feof(csvEmpleados); i++) {
        // Modificamos el tamaño del array
        if(i >= tam) {
            tam += BLK;
            realloc_empleados(&Listado, tam);
        }

        // Creamos variables para grabar con el fscanf
        sEmpleado aux = { 0, '\0', '\0', DISENYADOR };

        // fscanf leera del archivo dos integer y dos cadenas de strings
        // El %s no se puede usar para leer el archivo ya que el mismo leerá
        // hasta el espacio que encuentre, para evitar este problema utilizaremos %[^,].
        // El %[^,] leerá hasta toparse con la ' , '.
        fscanf(csvEmpleados, "%d,%[^,],%[^,],%d", &aux.dni, &aux.nombreYApellido, &aux.fecNac, &aux.posicion);

        // Asignamos los datos que levantamos del archivo
        // en nuestro lista y su posición correspondiente
        Listado[i] = aux;
    }

    // Eliminamos el exceso de memoria pedida al sistema
    {
        tam = tam - (tam - i) - 1;
        realloc_empleados(&Listado, tam);
        *tam_total = tam;
    }

    // Retornamos la lista obtenida
    return Listado;
}

// int buscar_linea_modificar(FILE* csvEmpleado, ptrEmpleado ListaModificada)
// Busca la linea a modificar y dejamos el cursor al inicio del registro
// que queremos cambiar/reemplazar el/los dato/s.
// Documentación: http://www.cplusplus.com/reference/cstdio/fseek/
// http://www.cplusplus.com/reference/cstdio/ftell/
void buscar_linea_con_DNI_modificar(FILE* csvEmpleado, int dni) {
    int buscar_dni = -1, posicion = 0;
    while (!feof(csvEmpleado)) {
        posicion = ftell(csvEmpleado);
        fscanf(csvEmpleado, "%d,", &buscar_dni);
        if (buscar_dni == dni) {
            fseek(csvEmpleado, 0, posicion);
            break;
        }
    }
}

// void modificar_dato_empleado(FILE* csvEmpleado, ptrEmpleado Listado, int pos)
// Esta función modifica un registro indicado usando su posición en tabla
void modificar_dato_empleado(FILE* csvEmpleado, ptrEmpleado Listado, int pos) {
    buscar_linea_con_DNI_modificar(csvEmpleado, Listado[pos].dni);
    
    fprintf(csvEmpleado, "%d,%s,%s,%d\n", Listado[pos].dni, Listado[pos].nombreYApellido, Listado[pos].fecNac, Listado[pos].posicion);
}