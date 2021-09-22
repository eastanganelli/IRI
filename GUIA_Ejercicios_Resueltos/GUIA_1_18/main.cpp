/*
18. Escribir un programa en C que imprima en pantalla el resultado
de tirar 10000 monedas (H,T). Así mismo, contar la cantidad de veces
que se tiraron 10 caras (H) consecutivas.
*/

#include <stdlib.h>
#include <stdio.h>

#include "monedas.h"

int main() {

	//Se puede usar una función con retorno e imprimir? Si, no? Por que?
	printf("Hubo %d Caras consecutivas\n", cantidad_caras());

	system("pause");
	return 0;
}