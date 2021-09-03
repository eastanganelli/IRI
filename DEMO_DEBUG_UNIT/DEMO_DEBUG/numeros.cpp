#include "numeros.h"


float pitagoras_iri(float cat1, float cat2) {
	float hipotenusa = 0, redondeo;
	
	hipotenusa = sqrt(pow(cat1, cuadrado) + pow(cat2, cuadrado));
	redondeo = roundf(hipotenusa * 100) / 100;

	return redondeo;
}

float area_circulo(float radio) {
	float area, redondeo;

	area = M_PI * pow(radio, 2);
	redondeo = roundf(area * 100) / 100;

	return redondeo;
}

float perimetro_circulo(float radio) {
	float per, redondeo;

	per = 2* M_PI * radio; // PI = atan(1)*4
	redondeo = roundf(per * 100) / 100;

	return redondeo;
}

float volumen_esfera(float radio) {
	float volumen, redondeo;
	
	volumen = (4 / 3) * M_PI * pow(radio, 3);
	redondeo = roundf(volumen * 100) / 100;

	return redondeo;
}