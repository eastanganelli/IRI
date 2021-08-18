#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define MAX 25
#define MIN 0

enum booleano { VERDADERO = 0, FALSO = 1 };

int es_mayor(int nums[N]);
int es_minimo(int nums[N]);
float cal_promedio(int nums[N]);

int main() {

    srand(time(NULL));

    int i = 0, numeros[N];
    int max_val = -1, min_val = -1;
    float promedio = 0;

    for(i = 0; i < N; i++) {
        numeros[i] = (rand()% MAX) - MIN;
        printf("%d - ", numeros[i]);
    }
    printf("\n");
    max_val = es_mayor(numeros);
    min_val = es_minimo(numeros);
    promedio = cal_promedio(numeros);
    printf("\nEl Valor Maximo es: %d", max_val);
    printf("\nEl Valor Minimo es: %d", min_val);
    printf("\nEl Valor Promedio es: %.2f", promedio);

    return 0;
}

int es_mayor(int nums[N]) {
    int i = 0, maximo = -1;

    if(maximo == -1) maximo = nums[i];
    for(i = 0; i < N; i++) {
        if(nums[i] > maximo)
            maximo = nums[i];
    }

    return maximo;
}

int es_minimo(int nums[N]) {
    int i = 0, minimo = -1;

    if(minimo == -1) minimo = nums[i];
    for(i = 0; i < N; i++) {
        if(nums[i] < minimo)
            minimo = nums[i];
    }

    return minimo;
}


float cal_promedio(int nums[N]) {
    float promedio = 0;
    int i = 0, suma = 0;

    for(i = 0; i < N; i++)
        suma += nums[i];

    promedio = ((float)suma/(i+1));

    return promedio;
}
