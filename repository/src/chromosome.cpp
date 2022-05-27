///////////////////////////////////////////////////////////
// Verrecchia Thomas & François Derrida 
// Projet IN104 - Semestre 2 ENSTA Paris
/////////////////////////////////////////////////////////// 

#include <cstdio>
#include <iostream>
#include "chromosome.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>

chromosome::chromosome( int init_size ) : size(init_size)
{
	genes.reserve(init_size);
	evaluation_status = false;	
}

bool chromosome::randomChromosome(){
    int i;
    float value_power, value_range_x, value_range_y;
    float limit_power, limit_range_x,limit_range_y;

    // Vérifie si les valeurs minimales et maximales ont été fixées correctements.
    if( (minRanges.size() != size) || (maxRanges.size() != size) )
		return false;
    
    // Assigne des valeurs aléatoires pour chaques gènes
    for (i=0; i<size; i++){
        limit_power = maxRanges[i][0] - minRanges[i][0];
        limit_range_x = maxRanges[i][1] - minRanges[i][1];
        limit_range_y = maxRanges[i][2] - minRanges[i][2];

        value_power = (((float)rand()/(float)RAND_MAX) * limit_power) + minRanges[i][0];
        value_range_x = (((float)rand()/(float)RAND_MAX) * limit_range_x) + minRanges[i][1];
        value_range_y = (((float)rand()/(float)RAND_MAX) * limit_range_y) + minRanges[i][2];

        gene value{value_power,value_range_x,value_range_y};

        genes.push_back(value);
    }

    // On indique que l'on a pas encore évalué le gène.
    evaluation_status = false;
    return true;
}

// Fonction en cours de production
double chromosome::evaluate(){
    return 1.2;
}

double chromosome::getFitness(){
    if(evaluation_status){
        return fitness;
    }else{
       return evaluate(); 
    }
}

void chromosome::setMinRanges(std::vector<gene> limit){
    int i;
    if(limit.size() != getSize())
		return;
	minRanges.clear();
	for(i = 0; i < limit.size(); ++i)
	{
		minRanges.push_back(limit[i]);
	}
}

void chromosome::setMaxRanges(std::vector<gene> limit){
    int i;
    if(limit.size() != getSize())
		return;
	maxRanges.clear();
	for(i = 0; i < limit.size(); ++i)
	{
		maxRanges.push_back(limit[i]);
	}
}

void chromosome::setGenes(std::vector<gene> genes){
    int i;
	if(genes.size() != getSize())
		return;
	genes.clear();
	for(i = 0; i < genes.size(); ++i)
	{
		genes.push_back(genes[i]);
	}
	evaluation_status = false;
}

void chromosome::displayChromosome(){
    int i;
    for (i=0; i<size; i++){
        printf("power: %f, target x: %f, target y: %f,\n",genes[i][0],genes[i][1],genes[i][2]);
    }
}