#include <union_find.h>
#include <stdlib.h>

// Function to create a partition with only singletons
Partition initialiser_partition(size_t nombre_elements) {

    Partition p = (Partition)malloc(sizeof(struct UnionFind));
    
    p->nombre_elements = nombre_elements;
    p->nombre_ensembles = nombre_elements;

    p->parent = liste_vide();

    for (size_t i = 0; i < nombre_elements; i++) {
        ajouter_en_fin(p->parent, i);
    }

    p->taille_arbre = liste_vide();

    for (size_t i = 0; i < nombre_elements; i++) {
        ajouter_en_fin(p->taille_arbre, 1);
    }

    return p;
}

// Function to add a new singleton to the partition
void ajouter_singleton(Partition p) {

    size_t nouvel_element = p->nombre_elements;
    p->nombre_elements++;

    ajouter_en_fin(p->parent, nouvel_element);
    ajouter_en_fin(p->taille_arbre, 1);

    p->nombre_ensembles++;
}

// Function to get the number of elements in the partition
size_t nombre_elements(Partition p) {
    return p->nombre_elements;
}

// Function to get the number of sets in the partition
size_t nombre_ensembles(Partition p) {
    return p->nombre_ensembles;
}

// Function to free the memory associated with the partition
void liberer_partition(Partition p) {
    liberer_liste(p->parent);
    liberer_liste(p->taille_arbre);
    free(p);
}

// Function to find the representative of an element
int trouver(Partition p, int x) {
    
    if (x < 0 || x >= p->nombre_elements) {
        fprintf(stderr, "Error: Element out of bounds\n");
        exit(EXIT_FAILURE);
    }

    while (element(p->parent, x) != x) {
        x = element(p->parent, x);
    }

    return x;
}

// Function to check if two elements are in the same set
bool meme_ensemble(Partition p, int x, int y) {
    return trouver(p, x) == trouver(p, y);
}

// Function to merge two sets
void unir(Partition p, int x, int y) {
    int root_x = trouver(p, x);
    int root_y = trouver(p, y);

    if (root_x == root_y) {
        return;
    }

    if (element(p->taille_arbre, root_x) < element(p->taille_arbre, root_y)) {
        modifier(p->parent, root_x, root_y);
        modifier(p->taille_arbre, root_y, element(p->taille_arbre, root_x) + element(p->taille_arbre, root_y));
    } else {
        modifier(p->parent, root_y, root_x);
        modifier(p->taille_arbre, root_x, element(p->taille_arbre, root_x) + element(p->taille_arbre, root_y));
    }

    p->nombre_ensembles--;
}
