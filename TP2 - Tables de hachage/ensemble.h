/**
 * @file ensemble.h
 * @author Julien Courtiel
 * */

#ifndef __ENSEMBLE__H__
#define __ENSEMBLE__H__

#include <stdlib.h>
#include <stdbool.h>
#include "liste_chainee.h"
#include "liste.h"

/* Description de la structure */

/**
 * @brief Structure codant une table de hachage \n
 * On autorisera à avoir des doublons.
 * Par contre, on s'imposera les contraintes suivantes :
 * @li le nombre d'alvéoles vaut au minimum le double du nombre d'éléments 
 * (sauf si la taille est inférieure à 2)
 * @li le nombre d'alvéoles vaut au maximum l'octuple du nombre d'éléments
 * @li la fonction de hachage sera une fonction multiplicative randomisée :
 * elle sera de la forme  `k -> |_ A * (k & 4294967295) * nb_alveoles _| modulo nb_alveoles`,
 * où A est un réel (aléatoire) entre 0.25 et 0.75. \n
 * (k & 4294967295) est l'opération qui permet de garder les 32 bits les plus faibles de k :
 * le problème c'est que l'opération k * nb_alveoles fait perdre de la précision
 * si k est supérieur à 2**32.
 */
 
struct TableHachage{
	
	ListeChainee* table; /**< L'adresse de la table de hachage (listes chaînées). */
	
	size_t nb_alveoles; /**< La taille du tableau **table** */
	
	size_t taille;  /**< Le nombre d'éléments dans la table. */
	
	double A; /**< La constante A dans la fonction de hachage
	* `k -> |_ A * (k & 4294967295) * nb_alveoles _| modulo nb_alveoles`,
	* où k est l'entier associé à l'objet.  */
};

/**
 * @brief On implémente notre type "Ensemble" avec une table de hachage.
 */
typedef struct TableHachage* Ensemble;


/* Pour pouvoir hacher les éléments qu'on veut insérer dans notre table de hachage,
 * il faut indiquer comment on transforme ces éléments en nombres.
 * Pour l'instant le type de base ce sont les entiers, donc pour ce faire,
 * on réalise un cast (_transtypage_ en français) tout simple. 
 * Si on changeait "type_base", on aurait alors (sûrement) envie de changer
 * la fonction. 
 * Si on ne sait pas comment transformer notre objet de base en entier,
 * alors on ne peut pas utiliser de table de hachage*/
/**
 * @brief Transforme un élément en un entier. 
 * (Première étape de la fonction de la hachage)
 * @param x élement de type type_base (ici entier)  
 * @returns un cast de x en size_t
 */
static inline size_t objet_vers_nombre(type_base x){
	return (size_t) x ;
}


/* Prototype des fonctions */

/**
 * @brief Renvoie un ensemble sans élément à l'intérieur. \n
 * Le nombre d'alvéoles initial est fixé à 8.
 * La table sera allouée dynamiquement.
 * On choisira A comme un réel aléatoire entre 0.25 et 0.75. \n
 * (Ne pas oubliez de changer la graine en fonction du temps!)
 * @returns un ensemble vide
 */
Ensemble ensemble_vide();

/**
 * @brief Donne le numéro de l'alvéole où est censée se trouver une certaine valeur. \n
 * La fonction en question est `k -> |_ A * (k & 4294967295) * nb_alveoles _| modulo nb_alveoles`. 
 * Au préalable, on utilisera la fonction `objet_vers_nombre` afin de transformer
 * notre paramètre en size_t.
 * **Complexité :** O(1) (sous condition que la transformation en entier s'effectue en temps constant)
 * @param e un ensemble, 
 * @param x une valeur,
 * @returns le code de hachage de x pour e.
 */
size_t alveole(Ensemble e, type_base x);


/**
 * @brief Ajoute un élément dans la table de hachage. \n
 * On utilisera la fonction `alveole` pour savoir dans quelle case ajouter l'élément.
 * On s'autorisera à avoir des doublons. \n
 * Si jamais le nombre d'éléments devient supérieur à la moitié du nombre d'alvéoles,
 * on réallouera un nouvelle table de hachage où on a doublé de nombre d'alvéoles.
 * **Complexité :** O(1) (en amorti)
 * @param e un ensemble,
 * @param x une valeur qu'on veut ajouter dans e.
 */
void ajouter(Ensemble e, type_base x);



/**
 * @brief Détermine si un élément appartient à un ensemble \n
 * **Complexité :** O(1) (en moyenne)
 * @param e un ensemble,
 * @param x une valeur qu'on recherche dans e.
 * @returns **true** si x appartient dans e, **false** sinon.
 */
bool appartient(Ensemble e, type_base x);



/**
 * @brief Supprime une occurrence d'un élément dans la table de hachage. \n
 * Si jamais le nombre d'éléments devient inférieur au huitième du nombre d'alvéoles,
 * on réallouera un nouvelle table de hachage où on a reduit de moitié le nombre d'alvéoles
 * (sauf si le nombre d'alvéoles devient inférieur à 8). \n
 * Déclenche une erreur si jamais la valeur n'est pas dans e. \n
 * **Complexité :** O(1) (en moyenne et en amorti)
 * @param e un ensemble,
 * @param x une valeur dont on veut supprimer une occurrence dans e.
 */
void supprimer(Ensemble e, type_base x);


/**
 * @brief Libère la mémoire associée à un ensemble. \n
 * On désallouera chaque liste chaînée, la table, ainsi que la structure elle-même.
 * **Complexité :** O(1) 
 * @param e un ensemble.
 */
void liberer_ensemble(Ensemble e);


/**
 * @brief Convertit un ensemble en une liste (voir TP précédent) \n
 * L'ensemble n'est pas modifié. \n
 * **Complexité :** O(taille de l'ensemble)
 * @param e un ensemble.
 * @returns une liste contenant les mêmes éléments que **e** (l'ordre n'a 
 * pas d'importance).
 */
Liste ensemble_vers_liste(Ensemble e);

/**
 * @brief Convertit une liste en un ensemble. \n
 * La liste n'est pas modifiée. \n
 * **Complexité :** O(taille de la liste)
 * @param l une liste.
 * @returns un ensemble contenant les mêmes élements que **l**.
 */
Ensemble liste_vers_ensemble(Liste l);

#endif
