#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "avl.h"




int main() {
	
	
	struct NoeudAvl zero = {0, 0, NULL, NULL};
	struct NoeudAvl minus_two = {-2, 1, NULL, &zero};
	struct NoeudAvl four = {4, 0, NULL, NULL};
	struct NoeudAvl luftballons = {99, 0, NULL, NULL};
	struct NoeudAvl two = {2, 0, &minus_two, &four};
	struct NoeudAvl seven = {7, 1, NULL, &luftballons};
	struct NoeudAvl five = {5, -1, &two, &seven};
	avl arbre_test = &five;


	avl_vers_dot("dessin_test", arbre_test);
	
	
	
	/* Décommentez les lignes que vous souhaitez afin de tester vos insertions : */
	
	// int tab[] = {14,18,11,7,53,4,13,12,8,60,20,16,27};
	// size_t taille = sizeof(tab)/sizeof(int);
	
	// ou
	
	// size_t taille = 40;
	// int tab[taille];
	// for( int i = 0 ; i < (int) taille ; i++) tab[i] = i+1;
	
	
	// ou
	
	// size_t taille = 40;
	// int tab[taille];
	// tab[0] = 1;
	// for( int i = 1 ; i < (int) taille ; i++) {
	//	int j = rand() % (i+1);
	// 	tab[i] = tab[j];
	//	tab[j] = i+1; 
	// }
	
	
	// puis :
	
	// avl a = NULL;
	// for(size_t i = 0; i < taille ; i++) {
	// 		a = inserer_avl(a,tab[i]);		
	// }
	// avl_vers_dot("experimentation", a);
	
	
	return EXIT_SUCCESS;
}
