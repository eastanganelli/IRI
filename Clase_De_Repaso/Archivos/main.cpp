#include "archivos.h"
#include "archivoscsv.h"
#include "archivosbin.h"

void imprimir_lista_empleados(ptrEmpleado Listado, int tam);
void imprimir_db_empleados(ptrDB Listado, int tam);

eBooleano existe_empleado(ptrEmpleado Lista, int tam, int dni);

ptrEmpleado anyadir_empleado();
int modificar_empleado(ptrEmpleado Listado, int tam);
void eliminar_empleado(ptrEmpleado* Listado, int* longitud, int dni);

int main() {
    // Listados y sus respectivas longitudes
    ptrEmpleado ListaEmpleados = NULL; int largoEmpleados = 0;
    ptrDB BaseDeDatos = NULL; int largoDB = 0;
    
    // Punteros tipo FILE, que almacenarán las direcciones
    // de nuestro csv y dat
    FILE* EmpleadosFile = NULL, * DBFile = NULL;

    char* pathDB = new char[96], * pathEmpleados = new char[96];
    
    strcpy(pathDB, EmpleadosDAT);
    strcpy(pathEmpleados, EmpleadosCSV);

    DBFile = abrir_archivo(pathDB, LECBIN);
    EmpleadosFile = abrir_archivo(pathEmpleados, LEC);

    // Verificamos si el archivo .dat existe o no
    // En caso de no existir, creamos uno
    if (DBFile == NULL) {
        printf("\nEl Archivo No Existe La DB!\nAhora crearemos uno\n");
        DBFile = abrir_archivo(pathDB, ESCRIBIN);
        init_base_de_datos(DBFile, miniDB, 6);
        cerrar_archivo(DBFile);
    } else {
        BaseDeDatos = leer_base_de_datos(DBFile, &largoDB);
        imprimir_db_empleados(BaseDeDatos, largoDB);
        cerrar_archivo(DBFile);
    }

    // Verificamos si el archivo .csv existe o no
    // En caso de no existir, creamos uno
    if (EmpleadosFile == NULL) {
        printf("\nEl Archivo No Existe La Lista de Empleados!\nAhora crearemos uno\n");
        EmpleadosFile = abrir_archivo(pathEmpleados, ESCRI);
        init_datos_empleados(EmpleadosFile, miniEmpleados, 6);
        cerrar_archivo(EmpleadosFile);
    }
    else {
        ListaEmpleados = leer_datos_empleados(EmpleadosFile, &largoEmpleados);
        imprimir_lista_empleados(ListaEmpleados, largoEmpleados);
        cerrar_archivo(EmpleadosFile);
        
        {
            int seleccion = -1;
            printf("\n1: Agregar\t2: Modificar\t3: Eliminar\t0: Salir -> ");
            (void)scanf("%d", &seleccion);
            switch (seleccion) {
                case 1: {
                    ptrEmpleado nuevoEmpleado = NULL;
                    nuevoEmpleado = anyadir_empleado();
                    if (nuevoEmpleado != NULL) {
                        EmpleadosFile = abrir_archivo(pathEmpleados, APPEND);
                        imprimir_datos_empleados(EmpleadosFile, nuevoEmpleado, 1);
                        cerrar_archivo(EmpleadosFile);

                        printf("\nEmpleado [DNI: %d], fue anyadido exitosamente!!\n", nuevoEmpleado->dni);

                        delete nuevoEmpleado;
                    }
                    printf("\nNuevo Empleado, no fue anyadido al sistema!!\n");
                    break;
                }
                case 2: {
                    int posicion = modificar_empleado(ListaEmpleados, largoEmpleados);
                    system("cls");
                    if (posicion != -1) {
                        EmpleadosFile = abrir_archivo(pathEmpleados, LEC);
                        modificar_dato_empleado(EmpleadosFile, ListaEmpleados, posicion);
                        cerrar_archivo(EmpleadosFile);

                        printf("\nEmpleado [DNI: %d], fue modificado exitosamente!!\n", ListaEmpleados[posicion].dni);

                        break;
                    }
                    printf("\nEmpleado Buscado, no fue encontrado!!\n");
                    break;
                }
                case 3: {
                    int dni = -1;
                    printf("\nIngrese DNI del Empleado que desea eliminar: ");
                    (void)scanf("%d", &dni);

                    eBooleano existeEmpleado = existe_empleado(ListaEmpleados, largoEmpleados, dni);

                    if (existeEmpleado) {
                        eliminar_empleado(&ListaEmpleados, &largoEmpleados, dni);

                        EmpleadosFile = abrir_archivo(pathEmpleados, ESCRI);
                        imprimir_datos_empleados(EmpleadosFile, ListaEmpleados, largoEmpleados);
                        cerrar_archivo(EmpleadosFile);

                        system("cls");

                        printf("\nEmpleado [DNI: %d], fue eliminado exitosamente!!\n\nTabla ACtualizada!\n", dni);
                        imprimir_lista_empleados(ListaEmpleados, largoEmpleados);
                        break;
                    }
                    printf("\nEmpleado Buscado, no fue encontrado!!\n");
                    break;
                }
                case 0: break;
                default: {
                    printf("\nOpción incorrecta!\n");
                    break;
                }
            }
        }

    }
    
#pragma region Limpieza de Variables Dinámicas
    // ListaDB
        if (BaseDeDatos != NULL) {
            delete[] BaseDeDatos;
            BaseDeDatos = NULL;
        }
    // ListaEmpleados
        if (ListaEmpleados != NULL) {
            delete[] ListaEmpleados;
            ListaEmpleados = NULL;
        }
#pragma endregion
    return 0;
}

void imprimir_lista_empleados(ptrEmpleado Listado, int tam) {
    printf("\nImprimir lista de Empleados\nID\tNombre y Apellido\tFec Nacimiento\tPuesto\n");
    for (int i = 0; i < tam; i++) {
        sEmpleado aux = Listado[i];
        printf("%d\t%s\t%s\t%d\n", aux.dni, aux.nombreYApellido, aux.fecNac, aux.posicion);
    }
}

void imprimir_db_empleados(ptrDB Listado, int tam) {
    printf("\nImprimir Base de Datos\nID\tPassword\tEstado\n");
    for (int i = 0; i < tam; i++)
        printf("%d\t%s\t%d\n", Listado[i].dni, Listado[i].contrasenya, Listado[i].miEstado);
}

eBooleano existe_empleado(ptrEmpleado Lista, int tam, int dni) {
    for (int i = 0; i < tam; i++)
        if (Lista[i].dni == dni)
            return VERDADERO;

    return FALSO;
}

ptrEmpleado anyadir_empleado() {
    ptrEmpleado aux = new sEmpleado;
    *aux = { 0, '\0', '\0', 0 };
    if (aux != NULL) {
        system("cls");
        printf("\nIngresar DNI:\t");
        (void)scanf("%d%*c", &aux->dni);
        printf("\nIngresar Nombre y Apellido:\t");
        gets_s(aux->nombreYApellido, 85);
        printf("\nIngresar Fecha nacimiento: [Formato: dd/mm/aaaa]\t");
        gets_s(aux->fecNac, 11);
        printf("\nIngresar Posicion:\t");
        (void)scanf("%d", &aux->posicion);
    }
    return aux;
}

int modificar_empleado(ptrEmpleado Listado, int tam) {
    ptrEmpleado aux = new sEmpleado;
    int i = -1;

    printf("\nSeleccionar Empleado por DNI: ");
    (void)scanf("%d", &aux->dni);

    for (i = 0; i < tam; i++) {
        if (Listado[i].dni == aux->dni) {
            *aux = Listado[i];
            break;
        }
    }

    printf("\nIngrese la nueva posicion: ");
    (void)scanf("%d", &aux->posicion);

    Listado[i] = *aux;
    delete aux;

    return i;
}

// Por qué uso un 'for' para copiar los datos y no un memcpy? Piense luego lea la respuesta
// RESPUESTA -> ABRIR CUANDO SE PUDRIO DE PENSAR
/*
    En este caso tengo que utilizar un 'for', ya que al estar quitando un elemento que esta contenido
    entre los limites, es más rápido copiar los datos con el 'for'.
    Recordar que memcpy, copia los datos del Origen al Destino, por ende, si el dato que no queremos está
    en el medio, lo volveremos en vez de quitarlo.
    Si quisiera usar memcpy, tendriamos que llevar el elemento que queremos eliminar a lo ultimo
    y de esa forma eliminamos el elemento
*/
void eliminar_empleado(ptrEmpleado* Listado, int* longitud, int dni) {
    int nueva_longitud = *longitud - 1;
    ptrEmpleado auxListado = new sEmpleado[nueva_longitud];

    //Método peligroso
    /*for (int i = 0, j = 0; j < nueva_longitud; i++) {
        sEmpleado EmpleadoCheck = (*Listado)[i];
        if (EmpleadoCheck.dni != dni) {
            auxListado[j] = (*Listado)[i];
            j++;
        }
    }*/

    //Método Seguro
    {
        int i = 0, posicion = 0;
        sEmpleado aux = { 0, '\0', '\0', 0 };

        //Buscamos la posición dónde esta el nodo posicion = N - 1
        for (posicion = 0; (*Listado)[posicion].dni == dni; posicion++);

        aux = (*Listado)[posicion - 1];

        //Corremos todos los nodos uno hacia la izquierda
        //Arrancar desde la posicion
        for (i = posicion - 1; i < nueva_longitud; i++)
            (*Listado)[i] = (*Listado)[i + 1];

        (*Listado)[i] = aux;

        memcpy(auxListado, *Listado, (*longitud) * sizeof(sEmpleado));
    }

    //Asignamos la nueva longitud para devolverla por derecha
    *longitud = nueva_longitud;

    // Eliminamos el Array de la vieja Lista
    delete[] *Listado;

    // Asignamos el Nuevo Array a *Listado
    (*Listado) = auxListado;
}

// NOTAS PIE DE PAGINA
////  * vs ->
// Que es el operador flecha ( -> ) y para que sirve?
// El operador es  foo->bar y es equivalente a (*foo).bar.
////
//// (*foo)[i]
// Debido a que estamos pasando puntero por referencia, para acceder al valor contenido en el array
// tenemos que utilizar (*foo) y luego indicarle la posición del Array 
////
//// Como evitar arrastrar el '\n' en el scanf al dar Enter?
// Para evitar arrastar el enter, se puede usar getchar(), fflush(stdin) o agregar '%*c' dentro del scanf()
// Por ejemplo: scanf("%d%*c", &aux->dni);
////