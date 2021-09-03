#include <iostream>
#include "numeros.h"

using namespace std;

int main(int argc, char* argv[])
{
    /*cout << "You have entered " << argc << " arguments:" << "\n";

    for (int i = 0; i < argc; ++i)
        cout << argv[i] << "\n";*/

    int selector = stoi(argv[1]);

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