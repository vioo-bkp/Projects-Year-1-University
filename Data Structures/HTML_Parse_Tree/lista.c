// Mateescu Viorel-Cristian

#include "structures.h"
#include <stdlib.h>

/* Functie pentru eliberarea memoriei ocupata de o lista generica. */

void DistrLG(ACell *List){
	ACell aux_cell;
	while(*List){
		aux_cell = *List;
		*List = aux_cell->urm;
		free(aux_cell);
	}
}

/* Functie pentru inserarea unui element intr-o lista generica.
   
   Inserarea se realizeaza la finalul listei generice. */

int InsLG(ACell *List, void *elem){
	ACell aux_cell = (ACell)calloc(1, sizeof(TCell));
	if(!aux_cell){
		return 1;
	}
	
	aux_cell->info = elem;
	aux_cell->urm = NULL;

	if(*List == NULL){
		*List = aux_cell;
	} else {
		ACell p = *List, ant = NULL;
		for(; p != NULL; ant = p, p = p->urm);
			
		ant->urm = aux_cell;
	}
	return 0;
}
