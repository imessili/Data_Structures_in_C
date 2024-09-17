/**
 * @file benchmark.h
 * @author Julien Courtiel
 * */

#ifndef __BENCHMARK__H__
#define __BENCHMARK__H__

#include <time.h>

/**
 * @brief Alias pour une fonction qui prend en paramètre un "size_t" et
 * qui ne renvoie rien.
 */
typedef void(*fonction)(size_t);

/**
 * @brief Constante qui détermine combien de nanosecondes on doit attendre au 
 * minimum pour chaque fonction quand on fait le benchmark
 */
#define NB_NS_PAR_FCT_BENCHMARK 100000000

/**
 * @brief Affiche le temps que met chacune des fonctions dans le tableau.
 * Exemple d'utilisation :  
 * `fonction mes_fonctions[] = {ma_fonction1, ma_fonction2, ma_fonction3};` \n
 * `test_rapidite(mes_fonctions,3,100000);`
 * @param tab_fonctions un tableau de fonctions avec un paramètre (de type size_t) et sans sortie,
 * @param nb_fonctions le nombre de fonctions dans ce tableau,
 * @param taille la taille à laquelle vont être testées les fonctions.
 */
void test_rapidite(fonction* tab_fonctions, size_t nb_fonctions, size_t taille);

#endif
