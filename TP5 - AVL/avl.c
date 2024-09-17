#include <stdio.h>
#include <stdlib.h>
#include "avl.h"



/* POUR DEBUGGER : fonction qui transforme des avl en fichiers .dot */

#include "string.h"

void avl_to_dot_walker(FILE* fd, avl a, avl parent){
	if (a) {
		if (a != parent) fprintf(fd, "%ld -> %ld\n", (size_t) parent, (size_t) a);
		fprintf(fd, "%ld [label=\"%d\"];\n", (size_t) a, a->valeur);
		fprintf(fd, "%ld [xlabel=\"%d\"];\n", (size_t) a, a->facteur_equilibrage);
		avl_to_dot_walker(fd, a->gauche, a);
		avl_to_dot_walker(fd, a->droite, a);
	}
}

void avl_vers_dot(const char* nom_fichier, avl a){
	int n = strlen(nom_fichier);
	char nom_fichier_complet[n + 5];
	strcpy(nom_fichier_complet,nom_fichier);
	strcat(nom_fichier_complet,".dot");
	FILE* fd = fopen(nom_fichier_complet, "w+");
	fputs("digraph G {\nrankdir=\"TB\";\n", fd);
	if (a){
		avl_to_dot_walker(fd, a, a);
	}
	fputs("}\n", fd);
	fclose(fd);
}

// Fonctions de base

avl creer_noeud(int valeur) {
    avl nouveau_noeud = (avl)malloc(sizeof(struct NoeudAvl));
    if (nouveau_noeud != NULL) {
        nouveau_noeud->valeur = valeur;
        nouveau_noeud->facteur_equilibrage = 0;
        nouveau_noeud->gauche = NULL;
        nouveau_noeud->droite = NULL;
    }
    return nouveau_noeud;
}

bool rechercher_abr(ArbreBinaire a, int x) {

    while (a != NULL) {
        
        if (a->valeur == x)
            return true;
        else if (x < a->valeur)
            a = a->gauche;
        else
            a = a->droite;
    }
    return false;
}

avl inserer_sans_equilibrage(ArbreBinaire a, int x) {
    if (a == NULL)
        return creer_noeud(x);
    if (x < a->valeur)
        a->gauche = inserer_sans_equilibrage(a->gauche, x);
    else if (x > a->valeur)
        a->droite = inserer_sans_equilibrage(a->droite, x);
    return a;
}

void liberer_avl(ArbreBinaire a) {
    if (a != NULL) {
        liberer_avl(a->gauche);
        liberer_avl(a->droite);
        free(a);
    }
}

// Fonctions pour tester si un arbre est AVL

Liste parcours_infixe(ArbreBinaire a) {
    Liste l = creer_liste();
    if (a != NULL) {
        l = concatener_listes(parcours_infixe(a->gauche), ajouter_en_queue(l, a->valeur));
        l = concatener_listes(parcours_infixe(a->droite), l);
    }
    return l;
}

int hauteur_abr(ArbreBinaire a) {
    if (a == NULL)
        return -1;
    int hauteur_gauche = hauteur_abr(a->gauche);
    int hauteur_droite = hauteur_abr(a->droite);
    return 1 + (hauteur_gauche > hauteur_droite ? hauteur_gauche : hauteur_droite);
}

bool est_avl(ArbreBinaire a) {
    if (a == NULL)
        return true;
    int diff_hauteur = hauteur_abr(a->gauche) - hauteur_abr(a->droite);
    return (diff_hauteur >= -1 && diff_hauteur <= 1 && est_avl(a->gauche) && est_avl(a->droite));
}

// Rotations simples

void rotation_gauche(avl a) {
    avl y = a->droite;
    a->droite = y->gauche;
    y->gauche = a;
    a = y;
}

void rotation_droite(avl a) {
    avl x = a->gauche;
    a->gauche = x->droite;
    x->droite = a;
    a = x;
}

// Insertion

avl dernier_noeud_desequilibre_et_insertion(avl a, int x) {
    if (a == NULL)
        return NULL;
    avl dernier_desequilibre = NULL;
    if (x < a->valeur) {
        dernier_desequilibre = dernier_noeud_desequilibre_et_insertion(a->gauche, x);
        if (dernier_desequilibre == NULL)
            a->facteur_equilibrage--;
    } else {
        dernier_desequilibre = dernier_noeud_desequilibre_et_insertion(a->droite, x);
        if (dernier_desequilibre == NULL)
            a->facteur_equilibrage++;
    }
    if (a->facteur_equilibrage < -1 || a->facteur_equilibrage > 1)
        dernier_desequilibre = a;
    return dernier_desequilibre;
}

void reequilibrage_jusqu_a_feuille(avl a_mettre_a_jour, int x) {
    if (a_mettre_a_jour == NULL)
        return;
    if (x < a_mettre_a_jour->valeur)
        a_mettre_a_jour->facteur_equilibrage--;
    else
        a_mettre_a_jour->facteur_equilibrage++;
    reequilibrage_jusqu_a_feuille(x < a_mettre_a_jour->valeur ? a_mettre_a_jour->gauche : a_mettre_a_jour->droite, x);
}

avl inserer_avl(avl a, int x) {
    if (a == NULL)
        return creer_noeud(x);
    avl dernier_desequilibre = dernier_noeud_desequilibre_et_insertion(a, x);
    reequilibrage_jusqu_a_feuille(a, x);
    if (dernier_desequilibre != NULL) {
        if (x < dernier_desequilibre->valeur) {
            if (x < dernier_desequilibre->gauche->valeur)
                rotation_droite(dernier_desequilibre);
            else {
                rotation_gauche(dernier_desequilibre->gauche);
                rotation_droite(dernier_desequilibre);
            }
        } else {
            if (x > dernier_desequilibre->droite->valeur)
                rotation_gauche(dernier_desequilibre);
            else {
                rotation_droite(dernier_desequilibre->droite);
                rotation_gauche(dernier_desequilibre);
            }
        }
    }
    return a;
}

// Autre fonction

int hauteur_avl(avl a) {
    return hauteur_abr(a);
}
