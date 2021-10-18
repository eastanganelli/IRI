#include "gblheader.h"

#define EmpleadosCSV "misempleados.csv"

enum puesto { DISENYADOR, PROGRAMADOR, ADMINISTRACION, RECURSOSHUMANOS };
typedef enum puesto ePuesto;

struct empleado {
    int dni;
    char nombreYApellido[156];
    char fecNac[12];
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

//Esta función inicializa el archivo con datos, en caso de no existir
void init_datos_empleados(FILE* csvEmpleados, sEmpleado Listado[6], int tamListado) {
    int i;
    for (i = 0; i < tamListado; i++)
        fprintf(csvEmpleados, "%d,%s,%s,%d\n", miniEmpleados[i].dni, miniEmpleados[i].nombreYApellido, miniEmpleados[i].fecNac, miniEmpleados[i].posicion);
}

void imprimir_datos_empleados(FILE* csvEmpleados, ptrEmpleado Listado, int tamListado) {
    int i;

    //El fprintf es como el printf, solo que tenemos que pasarle un puntero del tipo FILE
    //para que pueda escribir en el archivo.
    //Recuerden que hay que seperar los datos con ' , '!!
    //https://www.geeksforgeeks.org/csv-file-management-using-c/
    for (i = 0; i < tamListado; i++);
        fprintf(csvEmpleados, "%d,%s,%s,%d\n", Listado[i].dni, Listado[i].nombreYApellido, Listado[i].fecNac, Listado[i].posicion);
}

ptrEmpleado leer_datos_empleados(FILE* csvEmpleados, int* tam) {
    int i = 0;

    //Creamos un Listado de struct empleado* o ptrEmpleado
    //El new tiene que ser con sEmpleado, si usamos ptrEmpleado
    //estariamos devoliendo un puntero doble [[ Revisar Notas del archivo de connew.h ]]
    ptrEmpleado Listado = new sEmpleado[1];

    for (i = 0; !feof(csvEmpleados); i++) {
        //Creamos variables para grabar con el fscanf
        int dni = 0;
        ePuesto posicion = DISENYADOR;
        char auxnomape[25] = "\0", auxfecnac[15] = "\0";

        //fscanf leera del archivo dos integer y dos cadenas de strings
        //El %s no se puede usar para leer el archivo ya que el mismo leerá
        //hasta el espacio que encuentre, para evitar este problema utilizaremos %[^,].
        //El %[^,] leerá hasta toparse con la ' , '.
        fscanf(csvEmpleados, "%d,%[^,],%[^,],%d", &dni, &auxnomape, &auxfecnac, &posicion);

        //Cambiamos el tamaño del Listado
        if(i <= i+1) {
            //Esta explicado en el proyecto de ejemplo de
            //Memoria dinámica en el archivo de connew.h
            ptrEmpleado aux = new sEmpleado[i+1];
            memcpy(aux, Listado, sizeof(sEmpleado));
            delete[] Listado;
            Listado = aux;
        }

        //Asignamos los datos que levantamos del archivo
        //en nuestro lista y su posición correspondiente
        Listado[i].dni = dni;
        Listado[i].posicion = posicion;
        strcpy(Listado[i].nombreYApellido, auxnomape);
        strcpy(Listado[i].fecNac, auxfecnac);
    }

    //Devovlemos por derecha el tamaño de la Lista
    *tam = i;

    return Listado;
}