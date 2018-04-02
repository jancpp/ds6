//
//  ExpProfiling.cpp
//  ds6
//
//  Created by Jan Polzer on 3/11/18.
//  Copyright © 2018 Jan Polzer. All rights reserved.
//

#include "ExpProfiling.h"

// Measure time that take to insert @size random numbers into hash tables
template <class T>
void ExpProfiling::insertTime (int m, int size, int seed, T *table, float &time) {
    clock_t start = 0;
    int randomNumber = 0;
    srand(seed);
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        start = clock();
        table->insert(randomNumber);
        time += (float)(clock() - start) / CLOCKS_PER_SEC;
    }
}

// Measure time that take to find or not find @size random numbers into hash tables
template <class T>
void ExpProfiling::timeFoundNotFound (int m, int size, int seed, T *table, float &timeFound, float &timeNotFound) {
    clock_t start = 0;
    int randomNumber = 0;
    srand(seed);
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        start = clock();
        if (table->find(randomNumber) == true) {
            timeFound += (float)(clock() - start) / CLOCKS_PER_SEC;
        } else {
            timeNotFound += (float)(clock() - start) / CLOCKS_PER_SEC;
        }
    }
}
