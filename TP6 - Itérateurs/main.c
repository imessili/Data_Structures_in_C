#include <stdlib.h>
#include <stdio.h>


#include "iterateurs.h"



int main(){
	
	//~ Exemple pour les entiers :
	for( EACH(i,8) ){
		printf("%d ",i);
	}
	
	printf("\n************ \n");
	
	//~ Exemple pour les chaînes de caractères :
	char* phrase_exemple = "Ca marche ?!";
	for( EACH(lettre,phrase_exemple) ){
		printf("%c%c",lettre,lettre);
	}
	
	printf("\n************ \n");
	

	return EXIT_SUCCESS;
}
