///////////////////////////////////////////////////////////
// Verrecchia Thomas & François Derrida 
// Projet IN104 - Semestre 2 ENSTA Paris
///////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include "gene.h"

/*
Cette classe représente un chromosome composé d'un ensemble de gène.
Ce chromosome peut être découpé et recomposé. Un ensemble de 
chromosome constituent une population. Un chromosome représente un
élément de l'espace des solutions. Il contient l'ensemble des données
"power" et "target" à chaque instant de la course.
*/

class chromosome{

    int size;
    std::vector<gene> genes;

    //Correspond aux valeurs minimales et maximales pour le power, target_x et target_y
    std::vector<gene> minRanges;
    std::vector<gene> maxRanges;
    double fitness;
    bool evaluation_status;
public:
    chromosome(int init_size); //Permet de créer un chromosome
    bool randomChromosome(); //Génère un chromosome aléatoire
    double evaluate(); //Evalue un chromosome

    // Getters
    double getSize(){return size;};
    double getFitness();
    double getEvaluation_status(void){return evaluation_status;};
    gene getMinRanges(int i){return minRanges[i];};
    gene getMaxRanges(int i){return maxRanges[i];};

    // Setters
    void setMinRanges(std::vector<gene> limit);
    void setMaxRanges(std::vector<gene> limit);
    void setGenes(std::vector<gene> genes); //Permet de fixer tous les gènes du chromosome.
    void setGene(int i, gene value){genes[i] = value; evaluation_status = false;}; //Permet de fixer un seul gène du chromosome à l'indice i.

    void displayChromosome();
};

