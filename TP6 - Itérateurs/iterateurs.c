#include "iterateurs.h"



/* !!!!! ITÉRATEURS POUR LES ENTIERS POSITIFS (0 JUSQU'À N-1) !!!!! **/	

iterateur entier_init(int n){
	iterateur it = malloc(sizeof(struct iterateur_s));
	
	it->valeur = 0;
	it->est_fini = n <= 0;
	
	return it;
}		

void entier_suivant(iterateur it, int n){
	(it->valeur)++;
	it->est_fini = (it->valeur == n);
}	

void entier_termine(iterateur it){
	free(it);
}	


/* !!!!! ITÉRATEURS POUR LES CHAÎNES DE CARACTÈRES !!!!! **/	

iterateur string_init(char* ch){
	iterateur it = malloc(sizeof(struct iterateur_s));
	
	it->valeur = ch[0];
	it->est_fini = (ch[0] == '\0');
	it->data.curseur_string = ch;
	
	return it;
}		

void string_suivant(iterateur it, char* ch){	
	char* ptr = it->data.curseur_string;
	
	ptr++;
	
	it->valeur = *ptr;
	it->est_fini = (*ptr == '\0');
	it->data.curseur_string = ptr;	
}	

void string_termine(iterateur it){
	free(it);
}	

//~ À vous de compléter pour les 5 structures de données restantes...


/**
 * @file iterateurs.c
 * @author 
 * */

/* !!!!! ITÉRATEURS POUR LES ENTIERS POSITIFS (0 JUSQU'À N-1) !!!!! **/	

iterateur entier_init(int n) {
    iterateur it = (iterateur)malloc(sizeof(struct iterateur_s));
    it->valeur = 0; // Start from 0
    it->est_fini = false;
    return it;
}

void entier_suivant(iterateur it, int n) {
    if (it->valeur < n - 1) {
        it->valeur++;
    } else {
        it->est_fini = true;
    }
}

void entier_termine(iterateur it) {
    free(it);
}

/* !!!!! ITÉRATEURS POUR LES CHAÎNES DE CARACTÈRES !!!!! **/	

iterateur string_init(char* ch) {
    iterateur it = (iterateur)malloc(sizeof(struct iterateur_s));
    it->data.curseur_string = ch;
    it->est_fini = false;
    return it;
}

void string_suivant(iterateur it, char* ch) {
    if (*(it->data.curseur_string) != '\0') {
        (it->data.curseur_string)++;
    } else {
        it->est_fini = true;
    }
}

void string_termine(iterateur it) {
    free(it);
}

/* !!!!! ITÉRATEURS POUR LES LISTES !!!!! **/	

iterateur liste_init(Liste l) {
    iterateur it = (iterateur)malloc(sizeof(struct iterateur_s));
    it->valeur = l->premier->valeur;
    it->est_fini = false;
    return it;
}

void liste_suivant(iterateur it, Liste l) {
    if (l->suivant != NULL) {
        it->valeur = l->suivant->valeur;
        l->suivant = l->suivant->suivant;
    } else {
        it->est_fini = true;
    }
}

void liste_termine(iterateur it) {
    free(it);
}

/* !!!!! ITÉRATEURS POUR LES LISTES CHAÎNEES !!!!! **/	

iterateur liste_chainee_init(ListeChainee l) {
    iterateur it = (iterateur)malloc(sizeof(struct iterateur_s));
    it->valeur = l->valeur;
    it->est_fini = false;
    return it;
}

void liste_chainee_suivant(iterateur it, ListeChainee l) {
    if (l->suivant != NULL) {
        it->valeur = l->suivant->valeur;
        l->suivant = l->suivant->suivant;
    } else {
        it->est_fini = true;
    }
}

void liste_chainee_termine(iterateur it) {
    free(it);
}

/* !!!!! ITÉRATEURS POUR LES ENSEMBLES !!!!! **/	

iterateur ensemble_init(Ensemble E) {
    iterateur it = (iterateur)malloc(sizeof(struct iterateur_s));
    it->valeur = E->premier->valeur;
    it->est_fini = false;
    return it;
}

void ensemble_suivant(iterateur it, Ensemble E) {
    if (E->suivant != NULL) {
        it->valeur = E->suivant->valeur;
        E->suivant = E->suivant->suivant;
    } else {
        it->est_fini = true;
    }
}

void ensemble_termine(iterateur it) {
    free(it);
}

/* !!!!! ITÉRATEURS POUR LES FILES DE PRIORITE !!!!! **/	

iterateur file_priorite_init(FilePriorite f) {
    iterateur it = (iterateur)malloc(sizeof(struct iterateur_s));
    it->valeur = f->premier->valeur;
    it->est_fini = false;
    return it;
}

void file_priorite_suivant(iterateur it, FilePriorite f) {
    if (f->suivant != NULL) {
        it->valeur = f->suivant->valeur;
        f->suivant = f->suivant->suivant;
    } else {
        it->est_fini = true;
    }
}

void file_priorite_termine(iterateur it) {
    free(it);
}

/* !!!!! ITÉRATEURS POUR LES AVL !!!!! **/	

iterateur avl_init(avl A) {
    iterateur it = (iterateur)malloc(sizeof(struct iterateur_s));
    // Traverse to the leftmost node
    while (A->gauche != NULL) {
        A = A->gauche;
    }
    it->valeur = A->valeur;
    it->est_fini = false;
    return it;
}

void avl_suivant(iterateur it, avl A) {
    // Check if there's a right subtree
    if (A->droite != NULL) {
        A = A->droite;
        // Traverse to the leftmost node of the right subtree
        while (A->gauche != NULL) {
            A = A->gauche;
        }
        it->valeur = A->valeur;
    } else {
        // Otherwise, go to the parent nodes until finding a larger value
        avl parent = A->parent;
        while (parent != NULL && A == parent->droite) {
            A = parent;
            parent = parent->parent;
        }
        if (parent == NULL) {
            // No larger value found
            it->est_fini = true;
        } else {
            it->valeur = parent->valeur;
        }
    }
}

void avl_termine(iterateur it) {
    free(it);
}

