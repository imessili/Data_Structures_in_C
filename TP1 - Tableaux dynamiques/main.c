#include "liste.h"
#include "benchmark.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


int main(){

	/** À décommenter pour tester ! (Il faudra que vous rajoutiez des tests vous-même.) **/
	
	int i;
	Liste l = liste_vide();
	

	for (i = 0; i < 10; i++) {
		ajouter_en_fin(l,i);
	}
	
	for (i = 0; i < longueur(l); i++) {
		printf("%d\n",element(l,i));
	}

	supprimer_dernier(l);
	supprimer_dernier(l);

	for (i = 0; i < longueur(l); i++) {
		printf("%d\n",element(l,i));
	}

	printf("longeur : %zu\n",longueur(l));

	inserer(l, 5, 20);

	for (i = 0; i < longueur(l); i++) {
		printf("%d\n",element(l,i));
	}


	//assert(longueur(l) == 0);
	//assert(longueur(l) == 2);
	//assert(element(l,0) == 4);
	//assert(element(l,-1) == 8);


	return EXIT_SUCCESS;
}
