/**
 * @file verification_fonctions_union_find.c
 * @author Julien Courtiel
 * */


#include "verification_fonctions_union_find.h"
#include <stdbool.h>
#include <assert.h>
#include <time.h>


/**
 * @brief Permet de vérifier le bon fonctionnement et la rapidité de 
 * votre fonction qui compte le nombre de composantes connexes. \n
 * Une liste de la bonne taille est tirée aléatoirement.
 * @param votre_fonction la fonction que vous avez écrit 
 * (elle doit prendre une Liste et un size_t en entrées et un size_t en sortie)
 * @param nombre_aretes la moitié de la taille de la liste tirée aléatoirement 
 * (ça correspond aux nombre d'arêtes)
 */
void test_nombre_composantes(size_t (*votre_fonction) (Liste, size_t), size_t nombre_aretes ){

	assert(nombre_aretes >= 1);
	
    // Je commence par construire une liste aléatoire de la bonne taille :
    Liste l = liste_vide();


	ajouter_en_fin(l,0);
	ajouter_en_fin(l,1);
	size_t nb_sommets = 2;
	size_t sol = 1;
	int prec;
	bool touche;
	
	for(size_t i = 1; i < nombre_aretes ; i++){
		
		if (rand() % 4 < 3 && i > 1 ){		
			if (!touche && rand() % 7 == 0){
				touche = true;
				ajouter_en_fin(l, prec + (rand() %  (nb_sommets - prec) ) );
				ajouter_en_fin(l, rand() % prec ) ;
				sol--;
			}
			else{			
				if ( rand() % 3 == 0  && nb_sommets-prec > 3 ) 	{
					ajouter_en_fin(l,  prec + (rand() % (nb_sommets - prec) )    );
					ajouter_en_fin(l,  prec + (rand() % (nb_sommets - prec) ) );
				}
				else{
					ajouter_en_fin(l,  nb_sommets    );
					ajouter_en_fin(l,  prec + (rand() % (nb_sommets - prec) ) );
					nb_sommets++;
				}
				
			}
		}
		else {
			touche = false;
			ajouter_en_fin(l,nb_sommets);
			ajouter_en_fin(l,nb_sommets+1);
			prec = nb_sommets;
			nb_sommets += 2;
			sol++;
		}
		
		size_t tmp = rand() % (i+1);
		echanger(l,2*tmp,longueur(l)-2);
		echanger(l,2*tmp+1,longueur(l)-1);
		
	}


	
	Liste num = liste_vide();
	for(size_t i = 0; i < nb_sommets; i++){
		ajouter_en_fin(num,i);
		echanger(num,rand()%(i+1),i);
	}
	
	
	for(size_t i = 0; i < longueur(l); i++){
		modifier(l,i,element(num,element(l,i)));
	}
	liberer_liste(num);
	
	
	// J'affiche l'entrée si la taille est inférieure à 30
	if (nombre_aretes < 30) {
		printf("\nListe testée :\n");
		for(size_t i = 0; i < longueur(l); i++){
			printf("%d",element(l,i));
			if (i < longueur(l) - 1) {
				if (i % 2 ) printf(" , "); else printf(",");
			}
			else{
				printf("\n");
			}
		}	
	}	

	
	


	
	
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
	
    // Je teste votre fonction ici :
    assert( votre_fonction(l,nb_sommets) == sol );
    


    clock_gettime(CLOCK_MONOTONIC, &end);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Temps d'exécution (pour une taille %ld et un nombre de sommets %ld): %f secondes \n", nombre_aretes, nb_sommets, elapsed_time_ns/1000.0/1000.0/1000.0);

    liberer_liste(l);
}


/**
 * @brief Permet de vérifier le bon fonctionnement et la rapidité de 
 * votre fonction qui compte l'indice de l'apparition du premier cycle. \n
 * Une liste de la bonne taille est tirée aléatoirement.
 * @param votre_fonction la fonction que vous avez écrit 
 * (elle doit prendre une Liste et un size_t en entrées et un int en sortie)
 * @param nombre_aretes la moitié de la taille de la liste tirée aléatoirement 
 * pour le test qu'on suppose supérieure à 3.
 * (ça correspond aux nombre d'arêtes)
 */
void test_apparition_premier_cycle(int (*votre_fonction) (Liste, size_t), size_t nombre_aretes ){

	assert(nombre_aretes > 3);
	
    // Je commence par construire une liste aléatoire de la bonne taille :
    // (le code est un peu long)
    Liste l = liste_vide();

	size_t taille_cycle = 3 + rand() % ( (nombre_aretes-3) /2 + 1);
	size_t avant = rand() % (nombre_aretes - taille_cycle);
	size_t apres = nombre_aretes - avant - taille_cycle;
	
	int sommet_precedent = taille_cycle-1;
	
	bool touche_le_cycle;   
	
	for(size_t i = 0; i < avant ; i++){
		
		if (rand() % 4 < 3 && i > 0){		
			if (!touche_le_cycle && rand() % 10 == 0){
				touche_le_cycle = true;
				ajouter_en_fin(l,sommet_precedent);
				ajouter_en_fin(l, rand() % taille_cycle ) ;
			}
			else{					
				ajouter_en_fin(l,sommet_precedent);
				ajouter_en_fin(l,sommet_precedent+1);
				sommet_precedent++;
			}
		}
		else {
			touche_le_cycle = false;
			ajouter_en_fin(l,sommet_precedent+1);
			ajouter_en_fin(l,sommet_precedent+2);
			sommet_precedent += 2;
		}
		
		size_t tmp = rand() % (i+1);
		echanger(l,2*tmp,longueur(l)-2);
		echanger(l,2*tmp+1,longueur(l)-1);
		
	}
	
	int sol = -1;
	size_t nb_sommets = sommet_precedent + 4 + apres;
	
	for(size_t i = 0; i < taille_cycle ; i++){
		ajouter_en_fin(l, i);
		ajouter_en_fin(l, (i+1) % taille_cycle);
		
		size_t tmp = rand() % (longueur(l)/2-sol-1) + 1;
		
		sol += tmp;
		
		echanger(l,2*sol,longueur(l)-2);
		echanger(l,2*sol+1,longueur(l)-1);
		tmp = sol;
	}
	
	for(size_t i = 0; i < apres ; i++){
		ajouter_en_fin(l, rand() % nb_sommets );
		ajouter_en_fin(l, rand() % nb_sommets );
	}	
	Liste num = liste_vide();
	for(size_t i = 0; i < nb_sommets; i++){
		ajouter_en_fin(num,i);
		echanger(num,rand()%(i+1),i);
	}
	for(size_t i = 0; i < longueur(l); i++){
		modifier(l,i,element(num,element(l,i)));
	}
	
	liberer_liste(num);
	
	
	// J'affiche l'entrée si la taille est inférieure à 30
	if (nombre_aretes < 30) {
		printf("\nListe testée :\n");
		for(size_t i = 0; i < longueur(l); i++){
			printf("%d",element(l,i));
			if (i < longueur(l) - 1) {
				if (i % 2 ) printf(" , "); else printf(",");
			}
			else{
				printf("\n");
			}
		}	
	}	

	
	
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
	
    // Je teste votre fonction ici :
    assert( votre_fonction(l,nb_sommets) == sol );
    


    clock_gettime(CLOCK_MONOTONIC, &end);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Temps d'exécution (pour une taille %ld et un nombre de sommets %ld): %f secondes \n", nombre_aretes, nb_sommets, elapsed_time_ns/1000.0/1000.0/1000.0);

    liberer_liste(l);
}

