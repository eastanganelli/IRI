#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define DUMP "../dump.bin"

struct fileInfo {
	char filename[50];
	float filesize;
	int numberWords;
};
typedef struct fileInfo sfileInfo;

int main() {
	FILE* dumpFile = fopen(DUMP, "rb");

	sfileInfo* archivos = new sfileInfo[2];
	fread(archivos, sizeof(sfileInfo), 2, dumpFile);
	fclose(dumpFile);

	for (int i = 0; i < 2; i++)
		std::cout << "Nombre: "  << archivos[i].filename << " Size: " << archivos[i].filesize << " Palabras:" << archivos[i].numberWords << std::endl;

	return 0;
}