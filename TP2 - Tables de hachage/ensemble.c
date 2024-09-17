#include "ensemble.h" // Include the header file for the ensemble data structure
#include "liste_chainee.h" 
#include "liste.h" 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Function to calculate the hash value (alveole)
size_t alveole(Ensemble e, type_base x) {
    // Calculate the hash value using a random constant A and bitwise AND operation
    size_t hash = (size_t)(e->A * (objet_vers_nombre(x) & 4294967295) * e->nb_alveoles);
    return hash % e->nb_alveoles; // Return the bucket index
}

// Function to create an empty ensemble
Ensemble ensemble_vide() {
    srand(time(NULL)); // Seed the random number generator

    // Allocate memory for the ensemble structure
    Ensemble e = (Ensemble)malloc(sizeof(struct TableHachage));

    e->nb_alveoles = 8; // Initial number of buckets
    e->table = (ListeChainee*)malloc(e->nb_alveoles * sizeof(ListeChainee)); // Allocate memory for the array of linked lists

    e->taille = 0; // Initial number of elements
    e->A = ((double)rand() / RAND_MAX) * 0.5 + 0.25; // Random constant A between 0.25 and 0.75
    
    return e; // Return the empty ensemble
}

// Function to add an element to the ensemble
void ajouter(Ensemble e, type_base x) {

    // Check if the load factor exceeds 0.5

    if (e->taille >= e->nb_alveoles / 2) {
        // Reallocate the hash table with double the number of slots

        size_t new_nb_alveoles = e->nb_alveoles * 2;

        ListeChainee* new_table = malloc(new_nb_alveoles * sizeof(ListeChainee));

        // Initialize the new table with empty linked lists
        for (size_t i = 0; i < new_nb_alveoles; i++) {
            new_table[i] = liste_chainee_init();
        }

        // Réaffecter les éléments de l'ancienne table à la nouvelle
        for (size_t i = 0; i < e->nb_alveoles; i++) {

            Cellule* current = e->table[i];

            while (current != NULL) {

                Cellule* next = current->suivant;
                size_t new_hash_code = alveole(e, current->valeur);
                inserer_en_tete(&(new_table[new_hash_code]), current->valeur);
                e->taille++;
                free(current);
                current = next;

            }
        }
        
        // Libérer l'ancienne table de hachage
        free(e->table);
        
        // Mettre à jour la nouvelle table et le nombre d'alvéoles
        e->table = new_table;
        e->nb_alveoles = new_nb_alveoles;
    }

    // Add the element to the appropriate alveole
    size_t index = alveole(e, x) % e->nb_alveoles;
    liste_chainee_ajouter(e->table[index], x);
    e->taille++;
}

bool appartient(Ensemble e, type_base x) {
    // Calculer l'alvéole où rechercher l'élément
    size_t hash_code = alveole(e, x);
    
    // Parcourir la liste chaînée correspondante
    Cellule* current = e->table[hash_code];

    while (current != NULL) {
        if (current->valeur == x) {
            // L'élément a été trouvé
            return true;
        }
        current = current->suivant;
    }
    
    // L'élément n'a pas été trouvé dans la liste
    return false;
}

void supprimer(Ensemble e, type_base x) {
    // Calculer l'alvéole où chercher et supprimer l'élément
    size_t hash_code = alveole(e, x);
    
    // Rechercher l'élément dans la liste chaînée correspondante
    e->table[hash_code] = supprimer_lc(e->table[hash_code], x);
    
    // Décrémenter le nombre d'éléments dans la table
    e->taille--;
    
    // Vérifier si le nombre d'éléments devient inférieur au huitième du nombre d'alvéoles
    if (e->nb_alveoles >= 16 && e->taille < e->nb_alveoles / 8) {

        // Réallouer une nouvelle table de hachage avec la moitié des alvéoles
        size_t new_nb_alveoles = e->nb_alveoles / 2;

        ListeChainee* new_table = calloc(new_nb_alveoles, sizeof(ListeChainee));
        
        // Réinitialiser le nombre d'éléments dans la nouvelle table
        e->taille = 0;
        
        // Réaffecter les éléments de l'ancienne table à la nouvelle
        for (size_t i = 0; i < e->nb_alveoles; i++) {

            e->table[i] = liste_chainee_vers_liste(e->table[i]);
            
            while (e->table[i] != NULL) {
                type_base element = extraire_premier(&(e->table[i]));
                size_t new_hash_code = alveole(e, element);
                inserer_en_tete(&(new_table[new_hash_code]), element);
                e->taille++;
            }
        }
        
        // Libérer l'ancienne table de hachage
        free(e->table);
        
        // Mettre à jour la nouvelle table et le nombre d'alvéoles
        e->table = new_table;
        e->nb_alveoles = new_nb_alveoles;
    }
}


// Function to free the memory associated with the ensemble
void liberer_ensemble(Ensemble e) {
    for (size_t i = 0; i < e->nb_alveoles; i++) {
        liberer_liste_chainee(e->table[i]);
    }
    free(e->table);
    free(e);
}

// Function to convert an ensemble to a list
Liste ensemble_vers_liste(Ensemble e) {
    Liste nouvelle_liste = liste_vide();
    for (size_t i = 0; i < e->nb_alveoles; i++) {
        ListeChainee current = e->table[i];
        while (current != NULL) {
            ajouter_en_fin (nouvelle_liste, current->valeur);
            current = current->suivant;
        }
    }
    return nouvelle_liste;
}

// Function to convert a list to an ensemble
Ensemble liste_vers_ensemble(Liste l) {
    Ensemble e = ensemble_vide();
    Liste current = l;
    while (current != NULL) {
        ajouter(e, current->valeur);
        current = current->suivant;
    }
    return e;
}
