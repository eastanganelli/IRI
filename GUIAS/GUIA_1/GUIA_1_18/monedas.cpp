#include "monedas.h"

int cantidad_caras()
{
	int i = 0, cara = 0, cara_consec = 0;
	
	srand(time(NULL));
	while (i < N)
	{
		moneda aux = (moneda)(rand() % 2);
		if (aux == H)
		{
			//printf("CARA\n");
			cara++;
			if (cara == CONSEC) {
				cara_consec++;
				cara = 0;
			}
		}
		else
		{
			//printf("SECA\n");
			cara = 0;
		}
		/*
		Otra forma de escribir 'if'
		condicion ? verdadero : falso;
		aux == H ? printf("CARA\n") : printf("SECA\n");
		*/
		i++;
	}

	return cara_consec;
}

