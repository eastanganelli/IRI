#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "numeros.h"
#define max 6
#define min 3

char preguntasGBL[15][22] = {
    { "Preguntas numero 1" },
    { "Preguntas numero 2" },
    { "Preguntas numero 3" },
    { "Preguntas numero 4" },
    { "Preguntas numero 5" },
    { "Preguntas numero 6" },
    { "Preguntas numero 7" },
    { "Preguntas numero 8" },
    { "Preguntas numero 9" },
    { "Preguntas numero 10" },
    { "Preguntas numero 11" },
    { "Preguntas numero 12" },
    { "Preguntas numero 13" },
    { "Preguntas numero 14" },
    { "Preguntas numero 15" }
};

using namespace std;

int main(int argc, char* argv[]) {

    cout << "You have entered " << argc << " arguments:" << "\n";

    for (int i = 0; i < argc; ++i)
        cout << argv[i] << "\n";

    int selector = stoi(argv[1]);

   // int selector = 1;

    switch (selector) {
        case 1: {
            float cat1 = stof(argv[2]), cat2 = stof(argv[3]);
            printf("SQRT(Cateto 1 [%.2f]^2 Cateto 2 [%.2f]^2) = Hipotenusa %.2f", cat1, cat2, pitagoras_iri(cat1, cat2));
            break;
        }
        case 2: {
            float radio = stof(argv[2]);
            printf("Area del Ciruclo [Radio: %.2f] =  %.2f", radio, area_circulo(radio));
            break;
        }
        case 3: {
            float radio = stof(argv[2]);
            printf("Perimetro del Ciruclo [Radio: %.2f] =  %.2f", radio, perimetro_circulo(radio));
            break;
        }
        case 4: {
            float radio = stof(argv[2]);
            printf("Volumen del Ciruclo [Radio: %.2f] =  %.2f", radio, volumen_esfera(radio));
            break;
        }
        default:
            printf("Ingrese un selector entre 1 y 4");
    }
    return 0;
}