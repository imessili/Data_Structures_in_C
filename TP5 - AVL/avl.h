/**
 * @file avl.h
 * @author Cours M1 Structures de données avancées
 * */


#ifndef __AVL__H__
#define __AVL__H__


#include <stdbool.h>
#include "liste.h"


/**
 * @brief Structure qui encode un noeud des arbres AVL.
 */
struct NoeudAvl {
	
	int valeur; /**< La valeur stockée dans le noeud. 
	* (Ici pas de couples clé/valeur pour simplifier) */
	
	int facteur_equilibrage; /**< La différence entre la hauteur
	* du sous-arbre droit avec le sous-arbre gauche. \n
	* Si le facteur d'équilibrage est positif, alors l'arbre penche à 
	* droite ; sinon, il penche à gauche. \n
	* Un AVL est un arbre binaire de recherche dont le facteur 
	* d'équilibrage est -1, 0 ou 1 sur chacun des noeuds. */
	
	struct NoeudAvl* gauche; /**< Le pointeur vers le sous-arbre gauche.
	Vaut NULL si le noeud n'a pas d'enfant gauche. */
	
	struct NoeudAvl* droite; /**< Le pointeur vers le sous-arbre droit.
	Vaut NULL si le noeud n'a pas d'enfant droit. */
};

/**
 * @brief Un "avl" est un pointeur vers un noeud.
 */
typedef struct NoeudAvl* avl;



// Fonction utile pour le débuguage (Elle vous est fournie.) 

/**
 * @brief Ecrit un fichier .dot dessinant un avl. \n
 * Pour obtenir une image à partir de ce fichier .dot, on pourra 
 * par exemple écrire en ligne de commande : 
 * @code ̀dot -Tsvg mon_avl.dot -o mon_avl.svg
 * @endcode
 * **Complexité :** O(taille de l'avl)
 * @param nom_fichier le nom du fichier dans lequel écrire le .dot 
 * (il sera écrasé si jamais il existe déjà.),
 * @param a un avl dont nous voulons avoir le fichier .dot.
 */
void avl_vers_dot(const char* nom_fichier, avl a);



/* PROTOTYPE DES FONCTIONS QUE VOUS DEVEZ CODER */


/* -- Fonctions de base -- */


/**
 * @brief On donne un autre alias pour `avl`, à savoir `ArbreBinaire` (
 * afin d'insister sur le fait que notre arbre n'est pas forcément un AVL.
 * On peut voir les avl comme un sous-type des arbres binaires. \n
 * Dans les faits, les deux types sont identiques, c'est juste une vue
 * de l'esprit (c n'est pas un langage orienté objet...)
 */
typedef avl ArbreBinaire;


/**
 * @brief Renvoie un arbre réduit un simple noeud.
 * Pas d'enfant gauche ni d'enfant droit. \n 
 * Ne pas oublier de remplir le champ `facteur_equilibrage` \n
 * **Complexité :** O(1)
 * @param valeur un entier qui sera la valeur du noeud.
 * @returns un pointeur sur un noeud de valeur **valeur**.
 */
avl creer_noeud(int valeur);

/**
 * @brief Détermine si un entier appartient à un avl. \n
 * La fonction ne parcourira pas tout l'arbre, seulement la branche 
 * qui est nécessaire. \n
 * **Complexité :** O(nombre de noeuds) si a est un arbre binaire classique,
 * O(log(nombre de noeuds)) si a est un avl.
 * @param a un avl ou un arbre binaire de recherche,
 * @param x un entier dont on se demande s'il est dans a.
 * @returns true si x est dans a,
 * false sinon.
 */
bool rechercher_abr(ArbreBinaire a, int x);

/**
 * @brief Insertion d'un entier en tant que feuille, sans respecter les
 * conditions des avl. \n
 * L'arbre sera modifié, mais on renverra quand même un pointeur
 * sur la racine de l'arbre. Pour insérer un noeud dans l'arbre on
 * écrira alors `a = inserer_sans_equilibrage(a,x);`. 
 * Écrire simplement `inserer_sans_equilibrage(a,x);` marchera uniquement
 * si `a` n'est pas le pointeur nul. \n
 * La feuille sera insérée à l'unique endroit possible, et outre cette 
 * insertion, la forme de l'arbre ne sera pas changée.
 * Aucun facteur d'équilibrage ne sera mis à jour. 
 * Cette fonction implémentera l'insertion classique dans des Arbres 
 * Binaires de Recherche, comme on voit habituellement en L2. \n
 * **Complexité :** O(nombre de noeuds)
 * @param a un arbre binaire de recherche,
 * @param x l'entier à ajouter dans a.
 * @returns 
 */
avl inserer_sans_equilibrage(ArbreBinaire a, int x);

/**
 * @brief Libère de la mémoire chaque noeud d'un avl. \n
 * **Complexité :** O(nombre de noeuds)
 * @param a un avl dont on veut libérer chaque noeud.
 */
void liberer_avl(ArbreBinaire a);


/* -- Fonctions qui testent si un arbre est un AVL -- */

/**
 * @brief Réalise un parcours infixe d'un arbre (non forcément avl)
 * sous forme d'une liste. \n
 * **Complexité :** O(nombre de noeuds) - attention à ne pas faire quelque
 * chose de quadratique !
 * @param a un arbre binaire.
 * @returns une liste contenant tous les élements triés selon l'ordre infixe.
 */
Liste parcours_infixe(ArbreBinaire a);

/**
 * @brief Renvoie la hauteur d'un arbre (non forcément avl) \n
 * Par défaut la hauteur du pointeur nul est -1. \n
 * **Complexité :** O(nombre de noeuds)
 * @param a un arbre binaire.
 * @returns la hauteur de a (c'est-à-dire la profondeur maximale pour
 * un noeud dans l'arbre).
 */
int hauteur_abr(ArbreBinaire a);

/**
 * @brief Détermine si un arbre respecte toutes les conditions d'un AVL.
 * **Complexité :** O(nombre de noeuds)
 * @param a un arbre binaire.
 * @returns true si a est un avl, false sinon.
 */
bool est_avl(ArbreBinaire a);




/* -- Rotations simples -- */

/**
 * @brief Procéde à une rotation gauche simple de l'arbre. \n
 * Autrement si l'arbre est de la forme : 
 @verbatim
    x     
  /  \    
 G    y   
     / \  
    M   D 
 @endverbatim
 * où x et y sont la valeurs des noeuds et G, M, D sont des sous-arbres,
 * alors l'arbre sera modifié en : 
 @verbatim
    y    
    / \   
   x   D  
  / \     
 G   M    
 @endverbatim
 * Attention, on modifiera ici la valeur des noeuds de sorte que la racine
 * du nouvel arbre soit à la même adresse que la racine de l'ancien arbre. \n 
 * Provoque une erreur si l'arbre n'est pas sous la forme ci-dessus.
 * Les facteurs d'équilibrage doivent être corrects après rotation. \n
 * **Complexité :** O(1)
 * @param a un avl dont l'enfant droit est non nul.
 */
void rotation_gauche(avl a);

/**
 * @brief Procéde à une rotation gauche simple de l'arbre. \n
 * Autrement si l'arbre est de la forme : 
 @verbatim
    y    
    / \   
   x   D  
  / \     
 G   M    
 @endverbatim
 * où x et y sont la valeurs des noeuds et G, M, D sont des sous-arbres,
 * alors l'arbre sera modifié en : 
 @verbatim
    x     
  /  \    
 G    y   
     / \  
    M   D 
 @endverbatim
 * (Il s'agit de l'inverse de la fonction précédente.)
 * Attention, on modifiera ici la valeur des noeuds de sorte que la racine
 * du nouvel arbre soit à la même adresse que la racine de l'ancien arbre. \n 
 * Provoque une erreur si l'arbre n'est pas sous la forme ci-dessus.
 * Les facteurs d'équilibrage doivent être corrects après rotation. \n
 * **Complexité :** O(1)
 * @param a un avl dont l'enfant gauche est non nul.
 */
void rotation_droite(avl a);



/* -- Insertion -- */
/** On va ici découper notre fonction en 3 pour que ce soit plus
 * facile à écrire. */
 
/**
 * @brief Première étape de l'insertion d'une valeur dans un avl. \n
 * On insère une feuille comme dans `insertion_sans_reequilibrage`
 * mais en plus on doit renvoyer le dernier noeud de facteur 
 * d'équilibrage non nul. \n
 * On ne modifiera pas pour l'instant les facteurs d'équilibrage.
 * **Complexité :** O(log(nombre de noeuds))  
 * @param a un avl,
 * @param x la valeur du noeud qu'on veut insérer.
 * @returns le sous-arbre le plus bas de a qui contient x comme feuille 
 * et qui a un facteur d'équilibrage différent de 0.
 */
avl dernier_noeud_desequilibre_et_insertion(avl a, int x);


/**
 * @brief Deuxième étape de l'insertion d'une valeur dans un avl. \n 
 * Le premier paramètre sera la sortie de la fonction 
 * `dernier_noeud_desequilibre_et_insertion`.
 * Cette fonction actualise tous les facteurs d'équilibrage le long du chemin
 * partant de ce paramètre jusqu'à la feuille qu'on a insérée 
 * (qui a donc pour valeur **x**)\n
 * **Complexité :** O(log(nombre de noeuds de **a_mettre_a_jour**))  
 * @param a_mettre_a_jour un avl,
 * @param x la valeur du noeud qu'on veut insérer.
 */
void reequilibrage_jusqu_a_feuille(avl a_mettre_a_jour, int x);

/**
 * @brief Procède à l'insertion d'une valeur dans un avl. \n
 * L'arbre sera modifié, mais on renverra quand même un pointeur
 * sur la racine de l'arbre. Pour insérer un noeud dans l'arbre on
 * écrira alors `a = inserer_avl(a,x);`. \n
 * L'arbre renvoyé doit respecter toutes les conditions d'un AVL à la fin. \n
 * Après avoir utilisé les deux dernières fonctions, il faudra vérifier si
 * le sous-arbre renvoyé par `dernier_noeud_desequilibre_et_insertion` 
 * présente un déséquilibre.
 * Si c'est le cas, on procèdera à une rotation simple
 * ou à une rotation double selon les 4 cas du cours :
 * 	a. déséquilibre gauche-gauche 
 * 	b. déséquilibre gauche-droite
 * 	c. déséquilibre droite-droite
 * 	d. déséquilibre droite-gauche\n
 * **Complexité :** O(log(nombre de noeuds)) 
 * @param a un avl,
 * @param x la valeur du noeud qu'on veut insérer.
 * @returns a modifié de telle sorte que a soit inséré.
 */
avl inserer_avl(avl a, int x);


/* -- Fonction un peu plus facile pour finir -- */

/**
 * @brief Renvoie la hauteur d'un avl. \n
 * **Complexité :** O(log(nombre de noeuds)) -
 * pas besoin ici de parcourir tout l'arbre !
 * @param a un avl.
 * @returns la hauteur de a.
 */
int hauteur_avl(avl a);

#endif
