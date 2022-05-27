///////////////////////////////////////////////////////////
// Verrecchia Thomas & François Derrida 
// Projet IN104 - Semestre 2 ENSTA Paris
///////////////////////////////////////////////////////////

/*
Cette classe représente une population, Il contient l'ensemble des chromosomes.
Un ensemble de gènes forment un chromosome et un ensemble de chromosome forment
une population.
*/

#include <iostream>
#include <vector>
#include "chromosome.h"

class population{

    int size;
    int chromosome_size;
    std::vector<chromosome> chromosomes;
    std::vector<chromosome> nextGen;

    //Correspond aux valeurs minimales et maximales pour le power, target_x et target_y pour les chromosomes
    std::vector<gene> chromominRanges;
	std::vector<gene> chromomaxRanges;

    double mutationRate;
    double crossoverRate;
    bool sorted_value;
    double maxFitness;
    double meanFitness;
    double Fitness;

public:
    population(int init_size, int chromosome_size); //Permet de créer un chromosome

    // Getters
    int getSize(){return size;};
    gene getMinRanges(int i){return chromominRanges[i];};
    gene getMaxRanges(int i){return chromomaxRanges[i];};
    double getMutationRate();
    double getCrossoverRate();
    bool getSorted_value();
    double getMaxFitness(){return maxFitness;};
    double getMeanFitness(){return meanFitness;};
    double getFitness(int i){return chromosomes[i].getFitness();}

    // Setters
    void setMinRanges(std::vector<gene> limit);
    void setMaxRanges(std::vector<gene> limit);
    void setMutationRate(float mRate) {mutationRate = mRate;};
	void setCrossoverRate(float cRate) {crossoverRate = cRate;};

    bool initialisation(); // Initialise la population
    bool selection(int n_best); //Selectionne les n meilleurs solutions et les mets dans la prochaine génération
    bool evaluate();
    bool mutate();
    bool crossover();
    bool replace(); //Remplace la génération actuelle par la prochaine génération 

	
	



};