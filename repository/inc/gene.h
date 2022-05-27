///////////////////////////////////////////////////////////
// Verrecchia Thomas & François Derrida 
// Projet IN104 - Semestre 2 ENSTA Paris
///////////////////////////////////////////////////////////

/*
Cette classe représente un gène, brique de base de l'algorithme génétique. 
Il contient les données "power" et "target" à un instant t de la course.
Un ensemble de gènes forment un chromosome et un ensemble de chromosome forment
une population.
*/

#include <iostream>

class gene {
public:
    float power;
    float target_x;
    float target_y;

    float &operator[](int i) {
        if(i == 0) {
            return power;
        }
        if(i == 1) {
            return target_x;
        }
        if(i == 2) {
            return target_y;
        }
        else{
            printf("erreur dans la saisie, les indices doivent être 0,1 ou 2");
        }
    }
};