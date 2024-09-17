/**
 * @file liste_chainee.h
 * @author 
 * */

#ifndef __LISTE__CHAINEE__H__
#define __LISTE__CHAINEE__H__

#include <stdlib.h>
#include "liste.h"


/* !!! A CHANGER ICI SI VOUS NE VOULEZ PAS TRAVAILLER AVEC DES ENTIERS !!! */
#ifndef __TYPE__BASE__
#define __TYPE__BASE__

/**
 * @brief Le type des éléments DANS la liste chaînée/table de hachage.
 * Ce qu'il faut changer si on ne veut pas travailler avec des entiers.
 */
typedef int type_base;

#endif


/* Définition de la structure */


/**
 * @brief La structure classique des noeuds d'une liste (simplement) chaînée
 */
struct Noeud{
	type_base valeur; /**<  L'étiquette du noeud */
	struct Noeud* suivant; /**<  L'adresse du noeud suivant. 
	Si le noeud est le dernier de la liste, alors ce champ est le pointeur nul. */
};

/**
 * @brief Implémentation du type "liste chaînée" 
 */
typedef struct Noeud* ListeChainee;


/* Prototype des fonctions */



/**
 * @brief Renvoie une liste chaînée sans élément \n
 * **Complexité :** O(1)
 * @returns une liste chaînée vide
 */
ListeChainee liste_chainee_vide();



/**
 * @brief Insère un noeud au début d'une liste chaînée.\n
 * Ce nouveau noeud est alloué de manière dynamique. 
 * Les autres noeuds gardent la même adresse. (pas de duplication)\n
 * **Complexité :** O(1)
 * @param l liste chaînée,
 * @param x valeur qu'on veut ajouter au début de la liste,
 * @returns une liste dont le premier noeud est étiqueté par x, et dont
 * la suite est donnée par l.
 */
ListeChainee ajouter_debut(ListeChainee l, type_base x);


/**
 * @brief Libére chaque noeud de la liste chaînée. \n
 * **Complexité :** O(taille de la liste)
 * @param l liste chaînée.
 */
void liberer_liste_chainee(ListeChainee l);


/**
 * @brief Renvoie l'adresse du noeud avec une valeur donnée dans une liste chaînée. \n
 * La fonction renvoie un pointeur nul si jamais l'élément
 * n'appartient pas dans la liste. 
 * On pourra ainsi tester si une valeur **x** est dans la liste chaînée **l** 
 * avec la condition `if (rechercher_lc(l,x))` \n
 * **Complexité :** O(taille de la liste)
 * @param l liste chaînée,
 * @param x valeur de l'élément qu'on souhaite trouver dans l.
 * @returns un pointeur sur x si x appartient à l ; NULL dans le contraire.
 */
ListeChainee rechercher_lc(ListeChainee l, type_base x);



/**
 * @brief Supprime une occurrence d'une valeur dans une liste chaînée. \n
 * La mémoire associée au noeud supprimé est libérée.  
 * Les autres noeuds gardent la même adresse (aucun nouveau noeud n'est créé). \n
 * Si la valeur n'est pas dans la liste chaînée, déclenche une erreur. \n
 * **Complexité :** O(taille de la liste)
 * @param l liste chaînée,
 * @param x valeur dont on souhaite supprimer une occurrence dans l.
 * @returns l dans laquelle on a supprimé un noeud de valeur x (s'il existe).
 */
ListeChainee supprimer_lc(ListeChainee l, type_base x);



/**
 * @brief Supprime le premier noeud de la chaîne et renvoie sa valeur. \n
 * La mémoire allouée pour ce premier noeud est également libérée. \n
 * **Complexité :** O(1)
 * @param adr_l, pointeur vers une liste chaînée supposée non nulle.
 * La liste pointée par adr_l est modifiée de sorte à ce que l'élément de
 * tête soit supprimé.
 * @returns la valeur du premier noeud de la liste pointée par adr_l.
 */
type_base extraire_premier(ListeChainee* adr_l);
/* En C, il n'y a pas de méthode directe pour qu'une fonction renvoie
 * deux valeurs. Ici on aurait bien aimé renvoyer la valeur de l'élément
 * de tête + la liste sans cette tête.
 * L'astuce couramment employée est de passer **en adresse** une variable qu'on
 * modifie. Ici, il s'agit de la liste chaîne elle-même.
 * Ne pas oublier donc que quand on appelle la fonction on écrira
 * `extraire_premier(&l)` (ne pas oublier l'esperluette) */
 

/**
 * @brief Convertit une liste chaînée en une liste (voir TP précédent). \n
 * La liste chaînée n'est pas modifiée. \n
 * **Complexité :** O(taille de la liste chaînée)
 * @param l une liste chaînée.
 * @returns une liste qui contient les mêmes éléments que **l**.
 */
Liste liste_chainee_vers_liste(ListeChainee l);


void afficher_liste_chainee(ListeChainee l);


#endif
