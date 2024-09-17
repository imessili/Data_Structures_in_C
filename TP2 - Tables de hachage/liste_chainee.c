#include "liste_chainee.h"
#include <stdlib.h>
#include <stdio.h>

ListeChainee liste_chainee_vide() {
    ListeChainee l = NULL;
    return l;
}

ListeChainee ajouter_debut(ListeChainee l, type_base x){

    if (l == NULL){
        
        l = malloc(sizeof(struct Noeud));
        
        l->valeur = x;
        l->suivant = NULL;
        
        return l;

    }else{

        ListeChainee l_debut = malloc(sizeof(struct Noeud));

        // Handle memory allocation failure
        if (l_debut == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }

        l_debut->valeur = x;
        l_debut->suivant = l;

        l = l_debut;

        return l;
    }

}

void liberer_liste_chainee(ListeChainee l) {
    ListeChainee temp;

    while (l != NULL) {
        temp = l;               
        l = l->suivant;         
        free(temp);            
    }
}

ListeChainee rechercher_lc(ListeChainee l, type_base x) {

    while (l != NULL) {

        if (l->valeur == x) {
            return l;
        }

        l = l->suivant;
    }
    return NULL; // Return NULL only if the element is not found
}

ListeChainee supprimer_lc(ListeChainee l, type_base x) {
    
    if (l == NULL) {

        fprintf(stderr, "Erreur: La liste est vide.\n");
        exit(EXIT_FAILURE);

    }

    ListeChainee prec = NULL;
    ListeChainee current = l;

    // Recherche de l'occurrence à supprimer
    while (current != NULL && current->valeur != x) {

        prec = current;
        current = current->suivant;

    }

    // Si l'élément n'est pas trouvé dans la liste
    if (current == NULL) {

        fprintf(stderr, "Erreur: %d n'est pas présent dans la liste.\n", x);
        exit(EXIT_FAILURE);

    }

    // Si l'élément à supprimer est en tête de liste
    if (prec == NULL) {

        l = l->suivant;

    } else {

        prec->suivant = current->suivant;

    }

    free(current); // Libération de la mémoire associée au noeud supprimé
    return l;
}

type_base extraire_premier(ListeChainee* adr_l) {
    
    if (*adr_l == NULL) {

        fprintf(stderr, "Erreur: La liste est vide.\n");
        exit(EXIT_FAILURE);

    }

    ListeChainee premier = *adr_l;

    type_base valeur = premier->valeur;

    *adr_l = premier->suivant;

    free(premier); // Libération de la mémoire associée au premier nœud
    
    return valeur;
}


Liste liste_chainee_vers_liste(ListeChainee l) {

    Liste nouvelle_liste = liste_vide();
    ListeChainee current = l;

    // Parcours de la liste chaînée et ajout des éléments à la liste
    while (current != NULL) {

        ajouter_en_fin(nouvelle_liste, current->valeur);
        current = current->suivant;
        
    }

    return nouvelle_liste;
}

void afficher_liste_chainee(ListeChainee l) {
    printf("Liste : ");
    while (l != NULL) {
        printf("%d -> ", l->valeur);
        l = l->suivant;
    }
    printf("NULL\n");
}