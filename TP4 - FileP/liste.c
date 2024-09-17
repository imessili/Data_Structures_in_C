#include "liste.h"
#include <stdlib.h>
#include <stdio.h>

// Function to double the capacity
size_t double_capacity(size_t old_capacity) {
    return old_capacity * 2;
}

Liste liste_vide() {
    // Allocate memory for the structure
    Liste l = malloc(sizeof(struct TableauDynamique)); 
    
    // Handle memory allocation failure
    if (l == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    
    l->taille = 0;     // Initialize the size to 0
    l->capacite = 8;   // Set the initial capacity to 8

    l->tableau = malloc(l->capacite * sizeof(type_base));

    // Assign a default resizing function that doubles the capacity
    l->fonction_calcul_capacite = double_capacity;

    fprintf(stderr, "Empty list created!\n");
    return l;
}

size_t longueur(Liste l) {
    return l->taille;
}

void liberer_liste(Liste l) {

    if (l != NULL) {

        if (l->tableau != NULL) {
            // Free the memory allocated for the array
            free(l->tableau); 
        }
        // Free the memory allocated for the structure itself
        free(l); 
    }
}

void ajouter_en_fin(Liste l, type_base x) {
    
    if (l == NULL) {
        printf("List is Null\n");
        return;
    }

    if (l->tableau == NULL) {
        printf("List is Empty\n");
    }

    

    if (l->taille < l->capacite) {
        l->tableau[l->taille] = x;
        l->taille++;

    } else {

        size_t new_capacity = l->fonction_calcul_capacite(l->capacite);
        type_base *new_array = realloc(l->tableau, new_capacity * sizeof(type_base));

        if (new_array == NULL) {
            // Handle memory reallocation failure
            fprintf(stderr, "Error: Memory reallocation failed\n");
            return; // You may need to change the return type of your function to void* or int to accommodate this return statement.
        }

        l->tableau = new_array;
        l->tableau[l->taille] = x;
        l->taille++;
        l->capacite = new_capacity;
        
    }
}


void supprimer_dernier(Liste l) {
    if (l->taille > 0) {

        l->taille--;

    } else {
        // If there are no elements in the array, print an error message and terminate the program
        fprintf(stderr, "Error: Trying to delete from an empty list.\n");
        exit(EXIT_FAILURE);
    }
}

type_base element(Liste l, int pos) {
    // Vérifier si la liste est vide
    if (l == NULL) {
        fprintf(stderr, "Erreur: Liste vide.\n");
        exit(EXIT_FAILURE);
    }

    // Déterminer l'index réel de l'élément en fonction de la position
    size_t index;
    if (pos >= 0) {
        index = (size_t)pos;
    } else {
        index = l->taille + (size_t)pos;
    }

    // Vérifier si l'index est valide
    if (index < 0 || index >= l->taille) {
        fprintf(stderr, "Erreur: Position invalide.\n");
        exit(EXIT_FAILURE);
    }

    // Retourner l'élément à l'index spécifié
    return l->tableau[index];
}

void modifier(Liste l, int pos, type_base nouvelle_valeur) {
    // Vérifier si la liste est vide
    if (l == NULL) {
        fprintf(stderr, "Erreur: Liste vide.\n");
        exit(EXIT_FAILURE);
    }

    // Déterminer l'index réel de l'élément en fonction de la position
    size_t index;
    if (pos >= 0) {
        index = (size_t)pos;
    } else {
        index = l->taille + (size_t)pos;
    }

    // Vérifier si l'index est valide
    if (index < 0 || index >= l->taille) {
        fprintf(stderr, "Erreur: Position invalide.\n");
        exit(EXIT_FAILURE);
    }

    // Modifier l'élément à l'index spécifié
    l->tableau[index] = nouvelle_valeur;
}

void inserer(Liste l, int pos, type_base x) {
    // Vérifier si la liste est vide
    if (l == NULL) {
        fprintf(stderr, "Erreur: Liste vide.\n");
        exit(EXIT_FAILURE);
    }

    // Déterminer l'index réel de l'élément en fonction de la position
    size_t index;
    if (pos >= 0) {
        index = (size_t)pos;
    } else {
        index = l->taille + (size_t)pos;
    }

    // Vérifier si l'index est valide
    if (index < 0 || index > l->taille) {
        fprintf(stderr, "Erreur: Position invalide.\n");
        exit(EXIT_FAILURE);
    }

    // Si la liste est pleine, réallouer de la mémoire pour augmenter la capacité
    if (l->taille == l->capacite) {
        size_t new_capacity = l->fonction_calcul_capacite(l->capacite);
        type_base *nouveau_tableau = realloc(l->tableau, new_capacity * sizeof(type_base));
        
        if (nouveau_tableau == NULL) {
            fprintf(stderr, "Erreur: Échec de l'allocation de mémoire.\n");
            exit(EXIT_FAILURE);
        }
        
        l->tableau = nouveau_tableau;
        l->capacite = new_capacity;
    }

    // Décaler les éléments pour faire de la place pour le nouvel élément
    for (size_t i = l->taille; i > index; i--) {
        l->tableau[i] = l->tableau[i - 1];
    }

    // Insérer le nouvel élément à la position spécifiée
    l->tableau[index] = x;
    l->taille++;
}
