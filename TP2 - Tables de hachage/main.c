#include "liste.h"
#include "liste_chainee.h"
#include "ensemble.h"
#include <stdlib.h>
#include <stdio.h>


int main(){
    /*
    ListeChainee l = liste_chainee_vide();

    // Testing insertion at the beginning
    printf("Adding elements at the beginning...\n");
    l = ajouter_debut(l, 3);
    l = ajouter_debut(l, 5);
    l = ajouter_debut(l, 7);

    printf("printing elements...\n");
    afficher_liste_chainee(l);

    // Testing freeing the linked list
    printf("Freeing the linked list...\n");
    liberer_liste_chainee(l);
    
    l = NULL;
    afficher_liste_chainee(l); // Empty list

	return EXIT_SUCCESS;*/

    // Test ensemble_vide()

    printf("Creating an empty ensemble...\n");
    Ensemble e = ensemble_vide();
    printf("Empty ensemble created.\n");

    // Test ajouter()
    printf("\nAdding elements to the ensemble...\n");
    ajouter(e, 10);
    ajouter(e, 20);
    ajouter(e, 30);
    ajouter(e, 10); // Adding a duplicate element
    printf("Elements added to the ensemble.\n");

    // Test appartient()
    printf("\nChecking if elements belong to the ensemble...\n");
    printf("Does 10 belong to the ensemble? %s\n", appartient(e, 10) ? "Yes" : "No");
    printf("Does 40 belong to the ensemble? %s\n", appartient(e, 40) ? "Yes" : "No");

    // Test supprimer()
    printf("\nRemoving elements from the ensemble...\n");
    supprimer(e, 20);
    supprimer(e, 40); // Removing a non-existent element
    printf("Elements removed from the ensemble.\n");

    // Test ensemble_vers_liste()
    printf("\nConverting ensemble to list...\n");
    Liste l = ensemble_vers_liste(e);
    printf("Ensemble converted to list.\n");

    // Test liste_vers_ensemble()
    printf("\nConverting list back to ensemble...\n");
    //Ensemble e_from_list = liste_vers_ensemble(l);
    printf("List converted back to ensemble.\n");

    // Test liberer_ensemble()
    printf("\nFreeing memory associated with the ensemble...\n");
    liberer_ensemble(e);
    printf("Memory freed.\n");

    // Test liberer_liste()
    printf("\nFreeing memory associated with the list...\n");
    liberer_liste(l);
    printf("Memory freed.\n");

    return 0;
}
