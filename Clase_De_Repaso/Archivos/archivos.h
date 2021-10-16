#include "gblheader.h"

enum booleano { FALSO, VERDADERO };
typedef enum booleano eBool;

eBool existe_archivo(char* path) {
	//Le paso al fopen la ruta del archivo
	//Si al tratar de leer el archivo no puede,
	//devolverá NULL, sino un puntero tipo FILE
	FILE* archivo = fopen(path, "r+");
	
	if (archivo == NULL)
		//Si puedo abrir el archivo
		return VERDADERO;

	//No puedo abrir el archivo
	return FALSO;
}

FILE* abrir_archivo(char* path, char modo[5]) {
	//Le paso al fopen la ruta del archivo
	//Y el modo r, w, a, r+, w+, a+
	//OJO si apren con w/w+, van a crear un archivo
	//y si el mismo ya existía, lo van a sobreescribir,
	//es decir, van a borrar los datos anteriormente escritos
	//https://www.cplusplus.com/reference/cstdio/fopen/
	FILE* archivo = fopen(path, modo);
	return archivo;
}

void cerrar_archivo(FILE* archivo) {
	//Recuerden que siempre tenemos que cerrar el archivo
	//si ya no lo vamos a utilizar más
	fclose(archivo);

	//Asignamos NULL al archivo
	archivo = NULL;
}