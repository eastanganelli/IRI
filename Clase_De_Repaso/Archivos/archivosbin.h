#include "gblheader.h"

#define EmpleadosDAT "midatabases.dat"

enum estado { ALTA, BAJA, SUSPENDIDO };
typedef enum estado eEstado;

struct BaseDeDatos {
	int dni;
	char contrasenya[25];
    eEstado miEstado;
};
typedef struct BaseDeDatos sDB;
typedef sDB* ptrDB;

sDB miniDB[6] = {
    { 232323, "pass123", ALTA },
    { 932425, "pass456", SUSPENDIDO },
    { 734356, "pass789", BAJA },
    { 234323, "pass101112", ALTA },
    { 232343, "pass131415", SUSPENDIDO },
    { 212312, "pass161718", BAJA }
};

//Esta función inicializa el archivo con datos, en caso de no existir
void init_base_de_datos(FILE* datEmpleados, sDB listado[6], int tam) {
    fwrite(listado, sizeof(sDB), tam, datEmpleados);
}

void escribir_base_de_datos(FILE* datEmpleados, ptrDB listado, int tam) {
    //Escribe en el archivo, el array de sDB
    fwrite(listado, sizeof(sDB), tam, datEmpleados);
}

int tam_binario(FILE* dat) {
    int tam = 0;

    //Llevamos el cursor al final del archivo
    fseek(dat, 0, SEEK_END);

    //ftell nos devuelve la posición del cursor
    //Dividimos la posición por el tamaño de sDB
    //Eso nos dará la cantidad de elemento que tenemos de sDB
    tam = ftell(dat)/sizeof(sDB);

    //Devolvemos el cursor al inicio del archivo
    fseek(dat, 0, SEEK_SET);

    return tam;
}

ptrDB leer_base_de_datos(FILE* datEmpleados, int* tam) {
    //Creamos un Listado de struct empleado* o ptrEmpleado
    //El new tiene que ser con sEmpleado, si usamos ptrEmpleado
    //estariamos devoliendo un puntero doble [[ Revisar Notas del archivo de connew.h ]]
    ptrDB Listado = new sDB[0];

    //Le pedimos a la función tam_binario
    //que nos diga la longitud/cantidad de elementos
    //que tenemos de sDB
    int bin_largo = tam_binario(datEmpleados);

    //Levantamos los N elementos de sDB, y lo asignamos en
    //la variable Listado.
    fread(Listado, sizeof(sDB), bin_largo, datEmpleados);

    //Devolvemos por derecha, el tamaño del archivo
    *tam = bin_largo;

    return Listado;
}