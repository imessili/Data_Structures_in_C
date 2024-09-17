#include "file_priorite.h"

// Function to compare two elements (default implementation)
bool est_plus_petit_par_defaut(type_base x, type_base y) {
    return x < y;
}

// Function to create an empty priority queue
FilePriorite file_priorite_vide() {

    FilePriorite f = (FilePriorite)malloc(sizeof(struct TasBinaire));

    if (f == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    f->valeurs = liste_vide();
    f->est_plus_petit = est_plus_petit_par_defaut;

    return f;
}

// Function to free the memory associated with a priority queue
void liberer_file_priorite(FilePriorite f) {

    liberer_liste(f->valeurs);
    free(f);

}

// Function to get the number of elements in the priority queue
size_t longueur_file_priorite(FilePriorite f) {

    return longueur_liste(f->valeurs);

}

// Function to get the left child position
size_t position_enfant_gauche(size_t pos) {

    return 2 * pos + 1;

}

// Function to get the right child position
size_t position_enfant_droit(size_t pos) {

    return 2 * pos + 2;

}

// Function to get the parent position
size_t position_parent(size_t pos) {
    if (pos == 0) {
        fprintf(stderr, "Error: Root has no parent\n");
        exit(EXIT_FAILURE);
    }
    return (pos - 1) / 2;
}

// Function to add an element to the priority queue
void ajouter_file_priorite(FilePriorite f, type_base x) {

    ajouter_en_fin(f->valeurs, x);

    size_t position_actuelle = longueur_liste(f->valeurs) - 1;

    size_t position_parent_actuelle = position_parent(position_actuelle);

    while (position_actuelle > 0 && 
                f->est_plus_petit(/*f->valeurs[position_actuelle]*/element_liste(f->valeurs, position_actuelle),
                                  /*f->valeurs[position_parent_actuelle]*/element_liste(f->valeurs, position_parent_actuelle))) {

        echanger_elements(f->valeurs, position_actuelle, position_parent_actuelle);
        position_actuelle = position_parent_actuelle;
        position_parent_actuelle = position_parent(position_actuelle);

    }
}

// Function to get the minimum element of the priority queue
type_base minimum(FilePriorite f) {
    if (longueur_liste(f->valeurs) == 0) {
        fprintf(stderr, "Error: Priority queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return element_liste(f->valeurs, 0);
}

// Function to extract and return the minimum element from the priority queue
type_base extraire_minimum(FilePriorite f) {

    type_base min = element_liste(f->valeurs, 0);

    modifier_element_liste(f->valeurs, 0, dernier_element_liste(f->valeurs));

    supprimer_dernier_element(f->valeurs);

    size_t taille = longueur_liste(f->valeurs);

    size_t pos = 0;

    while (true) {

        size_t enfant_gauche = position_enfant_gauche(pos);
        size_t enfant_droit = position_enfant_droit(pos);

        if (enfant_gauche >= taille) {
            break;
        }

        size_t enfant_min;

        if (f->est_plus_petit(element_liste(f->valeurs, enfant_gauche),
                                element_liste(f->valeurs, enfant_droit))) {
            enfant_min = enfant_gauche;
        } else {
            enfant_min = enfant_droit;
        }
        
        if (f->est_plus_petit(element_liste(f->valeurs, enfant_min),
                              element_liste(f->valeurs, pos))) {
            echanger_elements(f->valeurs, pos, enfant_min);
            pos = enfant_min;
        } else {
            break;
        }
    }
    return min;
}

// Function to convert a list to a priority queue (min or max)
FilePriorite liste_vers_file_priorite(Liste l, bool est_file_min) {
    FilePriorite f = file_priorite_vide();
    size_t taille = longueur_liste(l);
    for (size_t i = 0; i < taille; i++) {
        ajouter_file_priorite(f, element_liste(l, i));
    }
    return f;
}

// Function to sort a list using heap sort
void tri_par_tas(Liste l) {
    FilePriorite f = liste_vers_file_priorite(l, true);
    for (size_t i = 0; i < longueur_liste(l); i++) {
        modifier_element_liste(l, i, extraire_minimum(f));
    }
    liberer_file_priorite(f);
}

#endif
