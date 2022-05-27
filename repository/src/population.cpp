///////////////////////////////////////////////////////////
// Verrecchia Thomas & François Derrida 
// Projet IN104 - Semestre 2 ENSTA Paris
///////////////////////////////////////////////////////////

#include <cstdio>
#include <iostream>
#include "population.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>

population::population( int init_size,int chromosome_size){
    sorted_value = false;
    chromosomes.reserve(2*init_size);
    nextGen.reserve(init_size);
}

bool population::initialisation(){
    int i;
    // Vérifie si les valeurs minimales et maximales ont été fixées correctements.
    if( (chromomaxRanges.size() != chromosome_size) || (chromominRanges.size() != chromosome_size) )
		return false;

    for(i=0; i< size; i++){
        chromosome chromo (chromosome_size);
        chromo.setMaxRanges(chromomaxRanges);
        chromo.setMinRanges(chromominRanges);
        chromo.randomChromosome();
        chromo.evaluate();
        if(!sorted_value){
            chromosomes.push_back(chromo);
        }else{
			std::vector<chromosome>::iterator it = chromosomes.begin();
			while((it != chromosomes.end()) &&
					(it->getFitness() > chromo.getFitness()) )
				it++;
				chromosomes.insert(it, chromo);
        }
        
    }
    return true;
}   

bool population::selection(int n_best){
    int i;
    for (i=0; i<size; i++){
        
    }
}

bool population::evaluate(){
    int i;
	float f;
	float sumFitness = meanFitness = 0.0;
	maxFitness = -1000000;
	for(i = 0; i < size; ++i)
	{
		f = chromosomes[i].getFitness();
		sumFitness += f;
		if(f > maxFitness) maxFitness = f;
	}
	meanFitness = sumFitness/(double)size;
	return true;
}

bool population::crossover(){

}

bool population::mutate(){

}

bool population::replace(){
    
}