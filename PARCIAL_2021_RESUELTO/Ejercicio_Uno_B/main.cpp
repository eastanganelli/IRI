#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define BYTE 1024
#define DUMP "../dump.bin"

using namespace std;

enum ERRFILE { NOFILE, NOTOPEN, YESOPEN };
enum ERRPTR  { NOPTR, YESPTR };

/*
int palabra, tamanio;
abrir_archivo(&palabra, &tamanio);
*/

struct fileInfo {
	char filename[50];
	float filesize;
	int numberWords;
};
typedef struct fileInfo sfileInfo;

ERRFILE abrir_archivo(char* nombre_archivo, int* cant_pal, float* file_size) { //ERRFILE abrir_archivo(char* nombre_archivo, int*& cant_pal, float*& file_size)
	/* 
	* Esto me permite acceder a los archivos
	* que están en la carpeta principal
	*/
	char* file_path = new char[4];
	strcpy(file_path, "../");
	strcat(file_path, nombre_archivo);

	FILE* mi_archivo = fopen(file_path, "r");
	//Verifico el archivo si existe o no
	if (mi_archivo == NULL) {
		*file_size = 0;
		*cant_pal = (int)*file_size;
		return NOFILE;
	}
	//Cuento las palabras
	int aux_cant_pal = 1;
	while (!(feof(mi_archivo))) {
		char caracter = fgetc(mi_archivo);
		/*
		Considero que el archivo esta cargado y seteado de forma correcta
		Es decir, no hay salto de lineas por demas, ni espacios extras, ni basura en el inicio,
		por el medio del archivo ni al final
		*/
		if (caracter == ' ' || caracter == '\n' || caracter == '.' || caracter == ',') aux_cant_pal++;
	}
	//levanto tam del archivo
	float tamanio = 0;
	tamanio = ftell(mi_archivo) / (float)BYTE;

	//SIEMPRE CERRAR EL ARCHIVO
	fclose(mi_archivo);

	//Retornamos los datos
	*cant_pal = aux_cant_pal;
	*file_size = tamanio;
	return YESOPEN;

}

void imprimir_datos_de_file(sfileInfo* mi_archivo, int miflag, char* file_name, int cant_falabras, float size_kilobytes) {
	/*
	* (*mi_archivo).filesize;
	* mi_archivo->filesize;
	*/

	if (miflag == 2) {
		//Escribo los datos en mi nodo de la estrcutura
		mi_archivo->filesize = size_kilobytes;
		mi_archivo->numberWords = cant_falabras;
		strcpy(mi_archivo->filename, file_name);
	}

	//Imprimo los datos
	printf("%s\n\tSize: %.2f KB\n\tWords: %d\n\n", file_name, size_kilobytes, cant_falabras);
}

ERRPTR new_or_resize(sfileInfo*& archivos, int size_vec) {
	sfileInfo* aux = new sfileInfo[size_vec + 1];

	if (aux != NULL) {
		/*
		* Si archivo es NULL, le paso el puntero de aux
		* Si archivo no es NULL, redimensiono el array
		*/
		if (archivos != NULL) {
			memcpy(aux, archivos, size_vec);
			delete[] archivos;
		} archivos = aux;
	} else return NOPTR;

	return YESPTR;
}

int main(int argc, char* argv[]) {
	/*
	* No se pasaron archivos por parametro
	* Tiene que ser si o si menor a 1, sino levanto el -dump pero
	* no tengo los nombres de los archivos
	*/
	if (argc < 2) return 1;

	sfileInfo* archivos = NULL;

	int sin_flag = (!strcmp(argv[1], "-dump")) ? 2 : 1;
	//           if(!strcmp(argv[1], "-dump")) { sin_flag = 2; } else { sin_flag = 1 }

	int vec_size = 0;

	for (int i = sin_flag; i < argc; i++) {
		int cant_pal = 0;
		float tam_kb = 0;
		if (abrir_archivo(argv[i], &cant_pal, &tam_kb) != ERRFILE::NOFILE) {

			if (new_or_resize(archivos, vec_size) == ERRPTR::NOPTR) return 1;

			imprimir_datos_de_file(&(archivos[vec_size]), sin_flag, argv[i], cant_pal, tam_kb);
			
			/*
			* Incremento pos del vector de archivo ACA
			* Si mi archivo no existe, no cargo datos a mi array
			*/
			vec_size++;
		}
	}

	if (sin_flag == 2) {
		FILE* dumpFile = fopen(DUMP, "a+b");

		if (dumpFile != NULL) {
			int tam = (argc - sin_flag);
			tam > 0 ? fwrite(archivos, sizeof(sfileInfo), tam, dumpFile) : 0 ;
			fclose(dumpFile);
		} return 1;
	}

	//Elimino el Vector
	delete[] archivos;

	return 0;
}