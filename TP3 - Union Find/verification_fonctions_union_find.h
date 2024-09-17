/**
 * @file verification_fonctions_union_find.h
 * @author Julien Courtiel
 * */


#include "liste.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Permet de vérifier le bon fonctionnement et la rapidité de 
 * votre fonction qui compte le nombre de composantes connexes. \n
 * Une liste de la bonne taille est tirée aléatoirement.
 * @param votre_fonction la fonction que vous avez écrite
 * (elle doit prendre une Liste et un size_t en entrées et un size_t en sortie)
 * @param nombre_aretes la moitié de la taille de la liste tirée aléatoirement 
 * (ça correspond aux nombre d'arêtes)
 */
void test_nombre_composantes(size_t (*votre_fonction) (Liste, size_t), size_t nombre_aretes );


/**
 * @brief Permet de vérifier le bon fonctionnement et la rapidité de 
 * votre fonction qui compte l'indice de l'apparition du premier cycle. \n
 * Une liste de la bonne taille est tirée aléatoirement.
 * @param votre_fonction la fonction que vous avez écrit e
 * (elle doit prendre une Liste et un size_t en entrées et un int en sortie)
 * @param nombre_aretes la moitié de la taille de la liste tirée aléatoirement 
 * pour le test qu'on suppose supérieure à 3.
 * (ça correspond aux nombre d'arêtes)
 */
void test_apparition_premier_cycle(int (*votre_fonction) (Liste, size_t), size_t nombre_aretes );
