/**
 * @file union_find.h
 * @author Cours M1 Structures de données avancées
 * */

#ifndef __UNION_FIND__H__
#define __UNION_FIND__H__

#include <stdlib.h>
#include "liste.h"
#include <stdbool.h>


#ifndef __TYPE__BASE__
#define __TYPE__BASE__

/**
 * @brief On travaille ici avec des entiers : 
 * les éléments sont numérotés de 0 jusqu'à n-1
 */
typedef int type_base;
#endif



/**
 * @brief Structure des forêts Union Find.
 * On considère que les élements constituant les ensembles sont des entiers
 * numérotés de 0 jusqu'à n-1, où n est le nombre d'éléments. \n
 * Pour l'union, on va greffer l'arbre le plus petit comme enfant de l'arbre le plus grand. \n
 * Pour le "find", on va utiliser la compression de chemins.
 */
struct UnionFind {
	
	size_t nombre_elements; /**<  Le nombre d'éléments de base. */
	
	size_t nombre_ensembles;  /**< Le nombre d'ensemble dans notre partition. */
	
	Liste parent; /**<  `parent[i]` indique le numéro du parent de `i`.
	* On rappelle que `i` est une racine d'un arbre de la forêt 
	* si et seulement si parent[i] vaut i. */
	
	Liste taille_arbre; /**< Si `i` est racine d'un arbre de la forêt, 
	* alors `taille_arbre[i]` est le nombre d'éléments dans cet arbre.
	* Si `i` n'est pas racine de son arbre, alors avec la compression de chemins, 
	* il se peut que `taille_arbre[i]` ne corresponde pas au nombre de noeuds
	* dans le sous-arbre.
	*/
										
};


/**
 * @brief On implémente les partitions d'ensembles disjoints comme pointeurs
 * sur la structure Partition.
 */
typedef struct UnionFind* Partition;


/* Prototype des fonctions */

/**
 * @brief Crée une partition faite uniquement avec des singletons (= ensembles de taille 1) \n
 * **Complexité :** O(nombre_elements) 
 * @param nombre_elements le nombre d'éléments de base.
 * @returns une partition de taille `nombre_elements` où chaque élément est de taille 1. 
 */
Partition initialiser_partition(size_t nombre_elements);


/**
 * @brief Modifie une partition de sorte à ajouter un nouveau singleton. \n
 * Le singleton sera un ensemble de taille 1 constitué de l'entier n,
 * où n est le nombre d'éléments **précédemment** dans la partition.  \n
 * **Complexité amortie :** O(1)
 * @param p une partition dans laquelle on veut ajouter un élément.
 */ 
void ajouter_singleton(Partition p);


/**
 * @brief Donne le nombre d'éléments qui sont dans les ensembles disjoints. \n
 * **Complexité :** O(1) \n
 * @param p une partition.
 * @returns son nombre d'éléments.
 */
size_t nombre_elements(Partition p);


/**
 * @brief Donne le nombre d'ensembles d'une partition. \n
 * **Complexité :** O(1) \n
 * @param p une partition.
 * @returns son nombre d'éléments.
 */
size_t nombre_ensembles(Partition p);


/**
 * @brief Désalloue la mémoire associée à la partition
 * (dont notamment les listes sous-jacentes). \n
 * **Complexité :** O(1). 
 * @param p la partition dont on aimerait libérer la mémoire 
 */
void liberer_partition(Partition p);


/**
 * @brief Renvoie un représentant d'un ensemble, étant donné un élément
 * dans cet ensemble. 
 * Ici, le représentant correspond à la racine de l'arbre où se trouve l'élément. \n
 * Implémente l'opération "find" avec compression de chemins. \n
 * On provoquera une erreur si jamais l'élément n'est pas dans la partition. \n
 * **Complexité (amortie) :** alpha(n),
 * où alpha est l'inverse de la fonction Ackermann,
 * et n le nombre d'éléments dans la partition.  
 * @param p une partition,
 * @param x un élément.
 * @returns la racine de l'arbre où se trouve x dans p.
 */
int trouver(Partition p, int x);


/**
 * @brief Détermine si deux éléments appartiennent au même ensemble. \n
 * **Complexité (amortie) :** alpha(n),
 * où alpha est l'inverse de la fonction Ackermann,
 * et n le nombre d'éléments dans la partition.  ǹ
 * @param p une partition,
 * @param x un élément de p,
 * @param y un élément de p.
 * @returns true si x et y appartient dans le même ensemble dans p,
 * false sinon.
 */
bool meme_ensemble(Partition p, int x, int y);


/**
 * @brief Fusionne deux ensembles étant donnés deux éléments dans chacun des ensembles. \n
 * On implémentera l'union où on greffera l'arbre le plus petit sur l'arbre le plus gros. \n
 * On provoquera une erreur si jamais un des deux éléments n'est pas dans la partition.
 * On ne fera rien si les éléments appartiennent dans le même ensemble. \n
 * **Complexité (amortie) :** alpha(n),
 * où alpha est l'inverse de la fonction Ackermann,
 * et n le nombre d'éléments dans la partition. 
 * @param p une partition,
 * @param x un élément du premier ensemble,
 * @param y un élément du second ensemble.
 */
void unir(Partition p, int x, int y);

#endif
