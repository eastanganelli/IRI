#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define BYTE 1024

using namespace std;

enum ERRFILE { NOFILE, NOTOPEN, YESOPEN };

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
		return ERRFILE::NOFILE;
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
	return ERRFILE::YESOPEN;

}

void imprimir_datos_de_file(char* file_name, int cant_falabras, float size_kilobytes) {
	printf("%s\n\tSize: %.2f KB\n\tWords: %d\n\n", file_name, size_kilobytes, cant_falabras);
}

int main(int argc, char* argv[]) {
	/*
	* No se pasaron archivos por parametro
	* Tiene que ser si o si menor a 1, sino levanto el -dump pero
	* no tengo los nombres de los archivos
	*/
	if (argc < 2) return 1;

	char** archivos = NULL;

	archivos = new char* [argc - 1];

	if (archivos == NULL) {
		cout << "NO RAM";
		return 1;
	}
	
	for (int i = 1; i < argc; i++) {
		int tam = strlen(argv[i]) + 1;
		archivos[i - 1] = new char[tam];
		strcpy(archivos[i - 1], argv[i]);
	}

	int cant_archivos = argc - 1;

	int i = 0;
	do {
		int cant_pal = 0;
		float tam_kb = 0;
		if (abrir_archivo(archivos[i], &cant_pal, &tam_kb) != ERRFILE::NOFILE)
			imprimir_datos_de_file(archivos[i], cant_pal, tam_kb);

		i++;
	} while (i != cant_archivos);

	//Elimino la matriz
	{
		i = 0;

		while (i < cant_archivos)
			delete[] archivos[i++];

		delete[] archivos;
	}

	return 0;
}