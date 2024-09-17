/**
 * @file liste.h
 * @author Cours M1 Structures de données avancées
 * */

#ifndef __LISTE__H__
#define __LISTE__H__

#include <stdlib.h>


/* !!! A CHANGER ICI SI VOUS NE VOULEZ PAS TRAVAILLER AVEC DES ENTIERS !!! */

#ifndef __TYPE__BASE__
#define __TYPE__BASE__

/**
 * @brief Le type des éléments DANS le tableau dynamique.
 * Ce qu'il faut changer si on ne veut pas travailler avec des entiers.
 */
typedef int type_base;

#endif

/**
 * @brief Implémentation de la structure tableau dynamique
 * 
 */
struct TableauDynamique {
	
	type_base* tableau; 	 /**< L'adresse du bloc mémoire où se situe les valeurs.  */
	
	size_t taille; 	 /**< Le nombre actuel d'éléments. */

	size_t capacite; /**< Le nombre maximum d'éléments que peut stocker
	la structure sans faire de réallocation. */

	size_t (*fonction_calcul_capacite) (size_t); /**< Un pointeur vers la 
	fonction qui indique comment la nouvelle capacité à partir de l'ancienne. \n
	Ce champ n'a qu'une utilité pédagogique. Normalement on coderait ça en dur. */
									
};


// Le type abstrait en question s'appelle "Liste"
/**
 * @brief Un pointeur vers la structure TableauDynamique
 */
typedef struct TableauDynamique* Liste;


/* Prototype des fonctions */


/**
 * @brief La taille de la liste.
 * @param l liste.
 * @returns le nombre d'éléments dans la liste.
 * 
 * 
 */
size_t longueur(Liste l);


/**	
 * @brief Renvoie une liste sans élément.
 * Par défaut, la capacité est fixée à 8 et on double la capacité à
 * chaque réallocation. \n
 * Complexité : O(1)
 * @returns une liste vide. */
Liste liste_vide();


/**	
 * @brief Désalloue la mémoire associée à la liste
 * Désalloue le tableau et la structure elle-même.
 * Complexité : O(1)
 * @param l liste */
void liberer_liste(Liste l);


/**
 * @brief Ajoute un élément à la fin de la liste `l`.
 * Un équivalent de append en python. \n
 * Complexité **amortie** : O(1)
 * @param l liste,
 * @param x élément à ajouter à la fin.
 * 
 * 
 */
void ajouter_en_fin(Liste l, type_base x);


/**
 * @brief Supprime le dernier élément de la liste `l`.
 * Provoque une erreur s'il n'y pas d'éléments dans la liste. \n
 * Complexité (non amortie): O(1)
 * @param l liste. 
 */
void supprimer_dernier(Liste l);

/**
 * @brief Renvoie l'élement d'une liste à une position donnée.
 * Si `pos` est négatif, alors il désigne le (-pos)-ième élément
 * en partant de la fin.
 * Déclenche une erreur si la position n'est pas dans les bornes de la liste. \n
 * L'équivalent en python simplement de `l[pos]`. \n 
 * Complexité : O(1)
 * @param l liste,
 * @param pos index de l'élement à renvoyer (nombre négatif possible)
 * @returns l'élement qui se situe à l'index `pos`.
 */
type_base element(Liste l, int pos);


/**
 * @brief Modifie l'élement d'une liste à une position donnée.
 * Équivalent de `l[pos] = nouvelle_valeur`. \n
 * Provoque une erreur si la position n'est pas dans les bornes de la liste. \n
 * Complexité : O(1)
 * @param l liste,
 * @param pos index de l'élément à modifier.
 * @param nouvelle_valeur ce par quoi on veut remplacer la valeur.  
 */
void modifier(Liste l, int pos, type_base nouvelle_valeur);


/**
 * @brief Échange deux éléments d'une liste étant données leurs positions. \n
 * Équivalent python es que de `l[pos1],l[pos2] = l[pos2],l[pos1]`. \n
 * Provoque une erreur si une des positions n'est pas dans les bornes de la liste. \n
 * **Complexité :** O(1)
 * @param l liste,
 * @param pos1 index du premier élément dont on souhaite changer la position,
 * @param pos2 index du second élément dont on souhaite changer la position.
 */
void echanger(Liste l, int pos1, int pos2);


/**
 * @brief Renvoie l'adresse d'un élément dans un liste. 
 * La fonction renvoie un pointeur nul si jamais l'élément
 * n'appartient pas dans la liste. \n
 * Complexité : O(taille de la liste)
 * @param l liste,
 * @param x valeur de l'élément qu'on souhaite trouver dans l.
 * @returns un pointeur sur x si x appartient à l ; NULL dans le contraire.
 */
type_base* rechercher(Liste l, type_base x);


/**
 * @brief Insère un élément dans la liste à une position donnée. 
 * L'équivalent en python de `l.insert(pos,x). \n
 * Provoque une erreur si la position n'est pas dans les bornes de la liste. \n
 * Complexité : O(taille de la liste)
 * @param l liste,
 * @param pos index à laquelle il faut insérer l'élément,
 * @param x valeur de l'élément à insérer.
 */
void inserer(Liste l, int pos, type_base x);


#endif
