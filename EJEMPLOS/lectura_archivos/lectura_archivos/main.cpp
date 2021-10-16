#include <stdlib.h>
#include <stdio.h>

FILE* abrir_archivo(char* direccion);

int main() {
	FILE* archivo = NULL;

	return 0;
}

FILE* abrir_archivo(char* direccion, char* modo) {
	FILE* aux = fopen(direccion, modo);
	if(aux != nullptr)
		return aux;
	return nullptr;
}