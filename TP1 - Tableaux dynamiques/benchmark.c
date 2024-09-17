/**
 * @file benchmark.h
 * @author Julien Courtiel
 * */

#include "benchmark.h"
#include <stdio.h>
#include <time.h>

void test_rapidite(fonction* tab_fonctions, size_t nb_fonctions, size_t taille){

	struct timespec start, end;
	
	for(size_t i = 0; i < nb_fonctions; i++){

		long elapsed_time_ns = 0;		
		long nb_essais = 0;
		while( elapsed_time_ns < NB_NS_PAR_FCT_BENCHMARK){
			clock_gettime(CLOCK_MONOTONIC, &start);
			
			tab_fonctions[i](taille);

			clock_gettime(CLOCK_MONOTONIC, &end);
			elapsed_time_ns += (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
			nb_essais++;
		}
		
		elapsed_time_ns /= nb_essais;
	
		printf("Temps d'exécution moyen de la fonction %ld (pour une taille %ld): %f secondes (sur %ld essais)\n", i+1, taille, elapsed_time_ns/1000.0/1000.0/1000.0, nb_essais);
	}
}


