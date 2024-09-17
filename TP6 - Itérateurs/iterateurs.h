/**
 * @file iterateurs.h
 * @author 
 * */

#ifndef __ITERATEURS__H__
#define __ITERATEURS__H__


#include "stdbool.h"

//~ Les entêtes de tous les fichiers qu'on a écrits jusqu'à alors (sauf union_find)
#include "liste.h"
#include "ensemble.h"
#include "file_priorite.h"
#include "avl.h"



 /* !!!!! DÉFINITION DE LA STRUCTURE !!!!! **/	
 

/**
 * @brief **La structure générique utilisée dans les itérateurs.** \n
 * Un itérateur c'est avant tout deux fonctions `init` et `next`
 * mais on a besoin de stocker des données entre chaque appel
 * de fonction `next`: c'est tout l'intérêt de cette structure. \n
 * Les itérateurs de ce TP partagent tous le même type, ce qui rajoute
 * un peu de complexité dans la définition de ce type. Deux champs sont 
 * communs à tous les types : **valeur** et **est_fini** qui désignent 
 * respectivement la valeur actuelle de l'itérateur et un booléen qui 
 * détermine si oui ou non on doit arrêter la boucle. \n
 * Un dernier champ est là si vous estimez qu'il faut stocker des 
 * informations supplémentaires pour telle ou telle structure de données.
 * On utilise pour cela une "union" , un truc de C plutôt rarement utilisé
 * mais qui convient parfaitement ici. Pour plus de détails, voir le 
 * sujet du TP.
 */
struct iterateur_s{
	type_base valeur;  /**< l'élément actuel de la structure de données
	* que nous parcourons (on suppose que les éléments de chaque structure
	* de données sont de `type_base`) */
	bool est_fini;  /**<  un booléen qui vaut vrai si la boucle/l'itérateur
	* doit s'arrêter maintenant. */
	
	/**
	 * @brief Union permettant de stocker dans la structure de type `struct iterateur_s`
	 * des informations propres à la structure de données sur laquelle on itère. \n
	 * Si vous avez besoin de plusieurs paramètres, pensez à définir un `struct`
	 * au préalable.
	 */
	union donnees_supplementaires{
		char* curseur_string; /**< Utilisé pour les `char *` \n
		* Adresse de l'élement en cours. */
		
		//~ À vous de compléter selon le conteneur...
		
	} data;	  /**< élément d'une union qui permet de stocker une information
	supplémentaire qui dépendra du type de la structure qu'on itère.  */
};


/**
 * Pour chaque structure de données qu'on veut parcourir il faudra définir 
 * trois fonctions (remplacer `xxx` par le même mot): \n
 * 1. `iterateur xxxx_init(type_structure l)` une fonction `init` qui 
 * alloue et initialise un itérateur de sorte que sa valeur soit égale à 
 * la première valeur de la structure (et potentiellement certains valeurs
 * dans le champ `data` de l'itérateur) \n
 * 2. `iterateur xxxx_suivant(iterateur it, type_structure l)` une fonction
 * `next̀` qui fait passer à l'élément suivant (ou met le champ `est_fini` à 
 * `true` si jamais il n'y a pas d'élément suivant.) \n
 * 3. `void xxxx_termine(iterateur it, type_structure l)` une fonction moins 
 * usuelle qui sert à terminer proprement la boucle. Principalement, ça sert à 
 * désallouer notre itérateur.
 * J'aurais pu automatiquement désallouer l'itérateur, mais dans certains contextes,
 * on peut vouloir désallouer autre chose que l'itérateur.
 * Par exemple, si le conteneur sur lequel on voulait itérer était un graphe,
 * et qu'on souhaitait parcourir les sommets selon un parcours en largeur,
 * alors il aurait fallu allouer d'autres structures, notamment pour marquer 
 * les sommets. Ces structures devront être libérées pour de l'appel de cette 
 * fonction  `termine` \n
 */
 


/**
 * @brief Un itérateur va être un pointeur vers la structure `iterateur_s`.
 * Bien penser à allouer cet itérateur lors de l'`init` et à le désallouer
 * lors de la terminaison.
 */
typedef struct iterateur_s* iterateur;


 /* !!!!! DÉFINITION DES MACROS !!!!! **/	
 
 
 
 /**
 * @brief `ACCOLE_TYPE` est une macro qui donne le nom d'une des 
 * fonctions mentionnées ci-dessus selon le type de `x`. \n
 * Par exemple si ̀`nom_fonction` vaut `init̀` et `x` est une variable entière
 * alors ̀̀`ACCOLE_TYPE(init,x)` vaudra entier_init. \n
 * Explication : `_Generic` permet d'associer un _objet c_ (ici une fonction)
 * selon le type d'une variable (ici `x`). \n
 * En outre, le double dièse ## signifie qu'on concatène deux trucs 
 * (des `tokens`) ensemble. \n
 * **Si on veut rajouter un itérateur pour un autre type, c'est ici qu'il faudra le renseigner.**
 */
#define ACCOLE_TYPE(nom_fonction, x) _Generic((x), \
                int: entier_##nom_fonction, \
                char*: string_##nom_fonction, \
                Liste: liste_##nom_fonction, \
                ListeChainee: liste_chainee_##nom_fonction, \
                Ensemble: ensemble_##nom_fonction, \
                FilePriorite: file_priorite_##nom_fonction, \
                avl: avl_##nom_fonction \
				)
                
#define ITER(x) ( (iterateur) __iter__ ## x )

 /**
 * @brief C'est ici que la magie noire opère. Je ne détaillerais pas ici pourquoi 
 * ça fonctionne (c'est un peu compliqué). L'utilisation reste relativement simple :
 * on écrit `for( EACH(var,conteneur) ){  ...  }` et on va allouer une variable nommée
 * `var` de type `type_base`, locale à la boucle, qui va parcourir tous les éléments
 * de `conteneur`. 
 */
    
#define EACH(x,l) type_base* __iter__ ## x = (type_base*) ACCOLE_TYPE(init,l)(l), x = ITER(x)->valeur; \
				!ITER(x)->est_fini || (ACCOLE_TYPE(termine,l) ( ITER(x) ),false) ;\
				ACCOLE_TYPE(suivant,l) (ITER(x),l), x = ITER(x)->valeur


/* !!!!! ITÉRATEURS POUR LES ENTIERS POSITIFS (0 JUSQU'À N-1) !!!!! **/	

/**
 * @brief Le `init` pour l'itérateur sur les entiers. \n   
 * **Complexité :** O(1)
 * @param n un entier, 
 * @returns un élément de type `iterateur̀` qui contient les informations
 * au niveau du premier élément.
 */
iterateur entier_init(int n);

/**
 * @brief  Le `next` pour l'itérateur sur les entiers. \n   
 * **Complexité :** O(1) 
 * @param it un itérateur sur les entiers,
 * @param n un entier, l'élément sur lequel on veut itérer.
 */
void entier_suivant(iterateur it, int n);

/**
 * @brief Désalloue toutes les données propres à l'itérateur sur les entiers.
 * **Complexité :** O(1)
 * @param it un itérateur sur les entiers,
 */
void entier_termine(iterateur it);


/* !!!!! ITÉRATEURS POUR LES CHAÎNES DE CARACTÈRES !!!!! **/	

/**
 * @brief Le `init` pour l'itérateur sur les chaînes de caractères. \n   
 * **Complexité :** O(1)
 * @param ch une chaîne de caractères, 
 * @returns un élément de type `iterateur̀` qui contient les informations
 * au niveau du premier élément.
 */
iterateur string_init(char* ch);

/**
 * @brief  Le `next` pour l'itérateur sur les chaînes de caractères. \n   
 * **Complexité :** O(1) 
 * @param it un itérateur sur les chaînes de caractères,
 * @param ch une chaîne de caractères, l'élément sur lequel on veut itérer.
 */
void string_suivant(iterateur it, char* ch);

/**
 * @brief Désalloue toutes les données propres à l'itérateur sur les chaînes de caractères. \n
 * **Complexité :** O(1)
 * @param it un itérateur sur les chaînes de caractères,
 */
void string_termine(iterateur it);



/* !!!!! ITÉRATEURS POUR LES LISTES !!!!! **/	

/**
 * @brief Le `init` pour l'itérateur sur les listes. \n   
 * **Complexité :** O(1)
 * @param l une liste, 
 * @returns un élément de type `iterateur̀` qui contient les informations
 * au niveau du premier élément.
 */
iterateur liste_init(Liste l);

/**
 * @brief  Le `next` pour l'itérateur sur les listes. \n   
 * **Complexité :** O(1) 
 * @param it un itérateur sur les listes,
 * @param l une liste, l'élément sur lequel on veut itérer.
 */
void liste_suivant(iterateur it, Liste l);

/**
 * @brief Désalloue toutes les données propres à l'itérateur sur les listes. \n
 * **Complexité :** O(1)
 * @param it un itérateur sur les listes
 */
void liste_termine(iterateur it);


/* !!!!! ITÉRATEURS POUR LES LISTES CHAÎNEES !!!!! **/	

/**
 * @brief Le `init` pour l'itérateur sur les listes chaînées. \n   
 * **Complexité :** O(1)
 * @param lc une liste chaînée, 
 * @returns un élément de type `iterateur̀` qui contient les informations
 * au niveau du premier élément.
 */
iterateur liste_chainee_init(ListeChainee l);

/**
 * @brief  Le `next` pour l'itérateur sur les listes chaînées. \n   
 * **Complexité :** O(1) 
 * @param it un itérateur sur les listes,
 * @param l une liste, l'élément sur lequel on veut itérer.
 */
void liste_chainee_suivant(iterateur it, ListeChainee l);

/**
 * @brief Désalloue toutes les données propres à l'itérateur sur les listes. \n
 * **Complexité :** O(1)
 * @param it un itérateur sur les listes,
 */
void liste_chainee_termine(iterateur it);


/* !!!!! ITÉRATEURS POUR LES ENSEMBLES !!!!! **/	

/**
 * @brief Le `init` pour l'itérateur sur les ensembles. \n   
 * **Complexité :** O(1) 
 * @param E un ensemble, 
 * @returns un élément de type `iterateur̀` qui contient les informations
 * au niveau du premier élément.
 */
iterateur ensemble_init(Ensemble E);

/**
 * @brief  Le `next` pour l'itérateur sur les ensembles. \n   
 * **Complexité :** O(1) (en moyenne)
 * @param it un itérateur sur les ensembles,
 * @param E un ensemble, l'élément sur lequel on veut itérer.
 */
void ensemble_suivant(iterateur it, Ensemble E);

/**
 * @brief Désalloue toutes les données propres à l'itérateur sur les ensembles. \n
 * **Complexité :** O(1)
 * @param it un itérateur sur les ensembles
 */
void ensemble_termine(iterateur it);
		
		
		
/* !!!!! ITÉRATEURS POUR LES FILES DE PRIORITE !!!!! **/	
//~ L'itérateur ne parcourira pas forcément les éléments de manière croissante


/**
 * @brief Le `init` pour l'itérateur sur les files de priorité. \n   
 * **Complexité :** O(1) 
 * @param f une file de priorité, 
 * @returns un élément de type `iterateur̀` qui contient les informations
 * au niveau du premier élément.
 */
iterateur file_priorite_init(FilePriorite f);

/**
 * @brief  Le `next` pour l'itérateur sur les files de priorités. \n   
 * **Complexité :** O(1) 
 * @param it un itérateur sur les files de priorités,
 * @param f une file de priorité, l'élément sur lequel on veut itérer.
 */
void file_priorite_suivant(iterateur it, FilePriorite f);

/**
 * @brief Désalloue toutes les données propres à l'itérateur sur les files de priorités. \n
 * **Complexité :** O(1)
 * @param it un itérateur sur les files de priorités
 */
void file_priorite_termine(iterateur it);
			


/* !!!!! ITÉRATEURS POUR LES AVL !!!!! **/	
//~ L'itérateur DEVRA parcourir les éléments de manière croissante


/**
 * @brief Le `init` pour l'itérateur sur les AVL. \n   
 * **Complexité :** O(1) 
 * @param A un AVL, 
 * @returns un élément de type `iterateur̀` qui contient les informations
 * au niveau du premier élément.
 */
iterateur avl_init(avl A);

/**
 * @brief  Le `next` pour l'itérateur sur les AVL. \n  
 * Les éléments sont itérés de manière croissante. 
 * **Complexité :** O(log(n)) (mais O(1) en amorti)
 * @param it un itérateur sur les AVL,
 * @param A un AVL, l'élément sur lequel on veut itérer.
 */
void avl_suivant(iterateur it, avl A);

/**
 * @brief Désalloue toutes les données propres à l'itérateur sur les AVL. \n
 * **Complexité :** O(log(n)) 
 * @param it un itérateur sur les AVL,
 */
void avl_termine(iterateur it);


#endif
