#define _CRT_SECURE_NO_WARNINGS
/*
* 
Según concepto trifásico, los números de Penco presentan las siguientes características: la parte entera del promedio 
del primero con el ultimo dígito debe encontrarse dentro del conjunto de los dígitos restantes de dicho numero.

Desarrollar un programa que solicite un numero e indique si cumple dicha condición. El numero ingresado debe contener por 
lo menos 3 dígitos.
Ej:
637298 --- 6+8=14 ---- 14/2=7
Es un numero de Penco.

45
El numero no dispone de los dígitos necesarios.

376 --- 3+6=9 ---- 9/2=4
No es un numero de Penco.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum PENCO { SIPENCO, NOPENCO, ERROR };

PENCO es_penco(int mi_valor);
void resize_arr(int*& vector, int tam);

int main() {
	int valor = -1;

	printf("Ingrese un valor: ");
	scanf("%d", &valor);

	if (valor < 100)
		printf("\nEl numero no dispone de los dígitos necesarios");
	else {
		switch (es_penco(valor)) {
			case SIPENCO: {
				printf("El valor [ %d ] es Numero de Penco", valor);
				break;
			}
			case NOPENCO: {
				printf("El valor [ %d ] NO es Numero de Penco", valor);
				break;
			}
			default: {
				printf("Error al pedir memoria");
				break;
			}
		}
	}
	return 0;
}

void resize_arr(int*& vector, int tam) {
	int* vector_aux = new int[tam];

	memcpy(vector_aux, vector, (tam-1)*sizeof(vector[0]));

	delete[] vector;

	vector = vector_aux;

}

//123456 -> 1 -> 2 <- 6 5 4 3 2 1 
/*
* 123456 % 10 = 6 -> 123456 / 10
* 12345 % 10 = 5 -> 12345 / 10
* 1234 % 10 = 4 -> 1234 / 10
* 123 % 10 = 3 -> 123 / 10
* 12 % 10 = 2 -> 12 /10
* 1 => 
*/
PENCO es_penco(int mi_valor) {
	int len_arr = 1;
	int* mis_digitos = new int[len_arr];

	int aux = -3;
	if (mis_digitos != NULL) {
		do {
			mis_digitos[len_arr - 1] = mi_valor % 10;
			aux = mi_valor % 10;

			mi_valor = mi_valor / 10;

			len_arr++;
			resize_arr(mis_digitos, len_arr);

		} while (mi_valor > 9 /*mi_valor >= 10*/);
		mis_digitos[len_arr - 1] = mi_valor;

		int penco_res = (mis_digitos[len_arr - 1] + mis_digitos[0]) / 2;

		int bandera = 0;

		for (int i = 1; i < len_arr - 1; i++) {
			if (penco_res == mis_digitos[i]) {
				bandera = 1;
				break;
			}
		}

		delete[] mis_digitos;
		             //if(1)    if(1 == 1) <==   if(1 != 0)             
		if (bandera) //if(TRUE) if(bandera == 1) if(bandera != 0)
			return SIPENCO;

		return NOPENCO;
	}
	return ERROR;
}