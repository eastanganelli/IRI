#include "archivos.h"
#define EmpleadosCSV "misempleados.csv"

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

void imprimir_datos_empleados(FILE* csvEmpleados, ptrEmpleado Listado, int tamListado) {
    //El fprintf es como el printf, solo que tenemos que pasarle un puntero del tipo FILE
    //para que pueda escribir en el archivo.
    //Recuerden que hay que seperar los datos con ' , '!!
    //https://www.geeksforgeeks.org/csv-file-management-using-c/
    for (int i = 0; i < tamListado; i++);
        fprintf(csvEmpleados, "%d,%s,%s,%d\n", Listado[i].dni, Listado[i].nombreYApellido, Listado[i].fecNac, Listado[i].posicion);
}

ptrEmpleado leer_datos_empleados(FILE* csvEmpleados) {
    //Creamos un Listado de struct empleado* o ptrEmpleado
    //El new tiene que ser con sEmpleado, si usamos ptrEmpleado
    //estariamos devoliendo un puntero doble [[ Revisar Notas del archivo de connew.h ]]
    ptrEmpleado Listado = new sEmpleado[0];

    for (int i = 0; i < 2; i++) {
        //Creamos variables para grabar con el fscanf
        int dni;
        ePuesto posicion;
        char auxnomape[25], auxfecnac[15];

        //fscanf leera del archivo dos integer y dos cadenas de strings
        //El %s no se puede usar para leer el archivo ya que el mismo leerá
        //hasta el espacio que encuentre, para evitar este problema utilizaremos %[^,].
        //El %[^,] leerá hasta toparse con la ' , '.
        fscanf(csvEmpleados, "%d,%[^,],%[^,],%d", &dni, &auxnomape, &auxfecnac, &posicion);

        //Asignamos los datos que levantamos del archivo
        //en nuestro lista y su posición correspondiente
        Listado[i].dni = dni;
        Listado[i].posicion = posicion;
        Listado[i].nombreYApellido = new char[25];
        Listado[i].fecNac = new char[12];
        strcpy(Listado[i].nombreYApellido, auxnomape);
        strcpy(Listado[i].fecNac, auxfecnac);
    }
}