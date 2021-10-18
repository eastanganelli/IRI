#include "gblheader.h"

enum booleano { FALSO = 0, VERDADERO = 1 };
typedef enum booleano eBooleano;

// eModo_Archivo
// Para .txt, .csv:
//	LEC: r+
//	ESCRI: w+
//	APPEND: a+
// Para .dat, .bin:
//	LECBIN: rb+
//	ESCRIBIN: wb+
//	APPENDBIN: ab+
enum modo_archivo { LEC, ESCRI, APPEND, LECBIN, ESCRIBIN, APPENDBIN };
typedef enum modo_archivo eModo_Archivo;

char modosFile[9][4] = {
	"r+", "w+", "a+", "rb+", "wb+", "ab+"
};

// FILE* abrir_archivo(char* path, eModo_Archivo modo)
// Le paso al fopen la ruta del archivo y el modo de apertura r+, w+, a+, rb+, wb+, ab+
// OJO si abren con w/w+, van a crear un archivo  y si el mismo ya existía, lo van a sobreescribir,
// es decir, van a borrar los datos anteriormente escritos
// Documentación: https://www.cplusplus.com/reference/cstdio/fopen/
FILE* abrir_archivo(char* path, eModo_Archivo modo) {
	FILE* archivo = fopen(path, modosFile[modo]);
	return archivo;
}

void cerrar_archivo(FILE* archivo) {
	// Recuerden que siempre tenemos que cerrar el archivo
	// si ya no lo vamos a utilizar más
	fclose(archivo);

	// Asignamos NULL al archivo
	archivo = NULL;
}