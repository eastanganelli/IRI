#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum PARIDAD { PAR, IMPAR };
enum IMPRIMIR { MAXIMO, MINIMO, PROMEDIO };

const int gblList[15] = {30, 79, 33, 92, 21, 42, 85, 25, 76, 17, 90, 73, 81, 32, 98};

int array_size(int* mi_array);
int* nuevo_array();
int* resize_array(int* arreglo, int lenarr);
int valor_max_min(int* vector, int arr_len, IMPRIMIR metodo);
PARIDAD valor_par_impar(int valor);
int* pares_e_impares(int* main_vec, int lenarr, IMPRIMIR metodo, int*& pares, int*& impares);

void imprimir(int* primos, int* pares, int* impares) {
	printf("\nPrimos: ");
	for (int i = 0; primos[i] != NULL; i++)
		printf("%d, ", primos[i]);

	printf("\nPares: ");
	for (int i = 0; pares[i] != NULL; i++)
		printf("%d, ", pares[i]);

	printf("\nImpares: ");
	for (int i = 0;  impares[i] != NULL; i++)
		printf("%d, ", impares[i]);

	printf("\n---------------------------------\n\n");
}

int main() {
	int* mi_arrray = new int[15];
	for (int i = 0; i < 15; i++) mi_arrray[i] = gblList[i];
		
	/*
	* Considero que el array que recibe mi función
	* en ningún momento es null y tiene más de 1 elemento
	*/

	int* paresI = NULL, * imparesI = NULL;

	int* primosI   = pares_e_impares(mi_arrray, 15, MAXIMO, paresI, imparesI);
	imprimir(primosI, paresI, imparesI);

	int* paresII = NULL, * imparesII = NULL;

	int* primosII  = pares_e_impares(mi_arrray, 15, MINIMO, paresII, imparesII);
	imprimir(primosII, paresII, imparesII);

	int* paresIII = NULL, * imparesIII = NULL;

	int* primosIII = pares_e_impares(mi_arrray, 15, PROMEDIO, paresIII, imparesIII);
	imprimir(primosIII, paresII, imparesII);

	{
		delete[] primosI;
		delete[] primosII;
		delete[] primosIII;

		delete[] paresI;
		delete[] imparesI;

		delete[] paresII;
		delete[] imparesII;

		delete[] paresIII;
		delete[] imparesIII;
	}

	return 0;
}


int* pares_e_impares(int* main_vec, int lenarr, IMPRIMIR metodo, int*& pares, int*& impares) {
	
#pragma region Pares e Impares
	int par_len = 0, impar_len = 0;

	for (int i = 0; i < lenarr; i++) {
		if (valor_par_impar(main_vec[i]) == PARIDAD::PAR) {
			pares = par_len == 0 ? nuevo_array() : resize_array(pares, par_len);
			pares[par_len] = main_vec[i];
			par_len++;
		} else {
			impares = impar_len == 0 ? nuevo_array() : resize_array(impares, impar_len);
			impares[impar_len] = main_vec[i];
			impar_len++;
		}
	}
	pares = resize_array(pares, par_len);
	pares[par_len] = NULL;
	impares = resize_array(impares, impar_len);
	impares[impar_len] = NULL;
#pragma endregion

#pragma region Maximo, Minimo y Promedio
	switch (metodo) {
	case MAXIMO: {
		printf("MAXIMO [%d]", valor_max_min(main_vec, lenarr, metodo));
		break;
	}
	case MINIMO: {
		printf("MINIMO [%d]", valor_max_min(main_vec, lenarr, metodo));
		break;
	}
	case PROMEDIO: {
		int sum = 0;

		for (int i = 0; i < lenarr; i++) sum += main_vec[i];

		printf("PROMEDIO [%.2f]", (float)(sum / lenarr));
		break;
	}
	}
#pragma endregion

#pragma region Numeros Primos
	int* primos = NULL;

	int primos_len = 0;
	for (int i = 0; i < lenarr; i++) {
		int c_flag = 0;

		//Verifico si el valor es primo o no
		for (int j = 1; j <= main_vec[i]; j++) {
			if (main_vec[i] % j == 0) 
				c_flag++;
		}

		if (c_flag == 2) {
			primos = primos_len == 0 ? nuevo_array() : resize_array(primos, primos_len);
			primos[primos_len] = main_vec[i];
			primos_len++;
		}
	}
	primos = resize_array(primos, primos_len);
	primos[primos_len] = NULL;
#pragma endregion

	return primos;
}

int valor_max_min(int* vector, int arr_len, IMPRIMIR metodo) {
	int mi_valor = vector[0];
	for (int i = 1; i < arr_len; i++) {
		switch (metodo) {
			case MAXIMO: {
				if (mi_valor < vector[i])
					mi_valor = vector[i];
				break;
			}
			case MINIMO: {
				if (mi_valor > vector[i])
					mi_valor = vector[i];
				break;
			}
		}
	} return mi_valor;
}

int array_size(int* mi_array) {
	int lenarr = sizeof(mi_array) / sizeof(*mi_array);

	return lenarr;
}

int* nuevo_array() {
	int* mi_vec = new int[1];

	return mi_vec;
}

int* resize_array(int* arreglo, int lenarr) {
	int* aux = NULL;
	
	aux = new int[lenarr + 1];
	
	if (aux != NULL) {
		memcpy(aux, arreglo, lenarr * sizeof(*arreglo));

		delete[] arreglo;
	}

	return aux;
}

PARIDAD valor_par_impar(int valor) {
	if (valor % 2 == 0)
		return PAR;

	return IMPAR;
}