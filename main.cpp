/*
Author: Jan Polzer
File:   main.cpp
Date:   2/19/2018
*/

#include "OpenHash.h"
#include "ClosedHashQP.h"
#include "ClosedHashDH.h"
#include <fstream>
#include <iostream>
#include <ctime>

// Measure time that take to insert @size random numbers into hash tables
template <class T>
void insertTime (int m, int size, int seed, T *table, double &time) {
    clock_t start = 0;
    int randomNumber = 0;
    srand(seed);
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        start = clock();
        table->insert(randomNumber);
        time += (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
    }
}

// Measure time that take to find or not find @size random numbers into hash tables
template <class T>
void timeFoundNotFound (int m, int size, int seed, T *table, double &timeFound, double &timeNotFound) {
    clock_t start = 0;
    int randomNumber = 0;
    srand(seed);
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        start = clock();
        if (table->find(randomNumber) == true) {
            timeFound += (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
//            std::cout << "\n " << timeFound;
        } else {
            timeNotFound += (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
            std::cout << "\n " << timeNotFound;
        }
    }
}
int main(int argc, char **argv) {

    OpenHash *tableCH = nullptr;
    ClosedHashQP *tableQP = nullptr;
    ClosedHashDH *tableDH = nullptr;

    int m = 11; // table size
    int k = 4;
    int p = 5;
    int key = -1;

    // User interacation
    int choice = -1;

    while (choice != 3) {
        std::cout << "\n............................................\n\n";
        std::cout << "Please choose one of the following commands:\n\n";
        std::cout << "1- Test Hash Tables\n\n";
        std::cout << "2- Peformance Comparison\n\n";
        std::cout << "3- Exit\n\n";

        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
            case 1:
            {
                std::cout << "File for testing your hash table correctness:\n";
                std::cout << "data.txt elements: 16 17 29 11 88 14 25\n";


                tableCH = new OpenHash(m);
                tableQP = new ClosedHashQP(m, k, p);
                tableDH = new ClosedHashDH(m, k, p);

                std::ifstream inputFile;
                inputFile.open(argv[1]);
                if (!inputFile) {
                    std::cout << "Error reading the input file.\n";
                    inputFile.close();
                } else {
                    tableCH  = new OpenHash(m);
                    tableQP = new ClosedHashQP(m, k, p);
                    tableDH = new ClosedHashDH(m, k, p);
                    while(inputFile >> key) {
                        tableCH->insert(key);
                        tableQP->insert(key);
                        tableDH->insert(key);
                    }
                }
                inputFile.close();

                tableCH->print();
                tableQP->print();
                tableDH->print();

                delete tableCH;
                delete tableDH;
                delete tableQP;

            }
            break;
            case 2:
            {

                int m = 1000003; // table size
                int k = 20;
                int p = 997;

                int size = 0;
                int seed = 0;
                std::cout << "Peformance Comparison: (takes a while to genetate results)\n\n";

                tableCH  = new OpenHash(m);
                tableQP = new ClosedHashQP(m, k, p);
                tableDH = new ClosedHashDH(m, k, p);

                // timeForHashTable[seed][0-buildTime, 1-foundTime, 2-notFoundTime][mult][run5times]
                double timesCH[5][3][5][5] = {};
                double timesQP[5][3][5][5] = {};
                double timesDH[5][3][5][5] = {};

                // timeAccumulatedUsingDifferentSeeds[0-buildTime, 1-foundTime, 2-notFoundTime][mult][run5times]
                double accSeedsCH[3][5][5] = {};
                double accSeedsQP[3][5][5] = {};
                double accSeedsDH[3][5][5] = {};

                // timeAverageUsingDifferentSeeds[0-buildTime, 1-foundTime, 2-notFoundTime][mult][5times]
                double aveSeedsCH[3][5][5] = {};
                double aveSeedsQP[3][5][5] = {};
                double aveSeedsDH[3][5][5] = {};

                // timeRunAll5times[0-buildTime, 1-foundTime, 2-notFoundTime][sizeMultiplier]
                double acc5timesCH[3][5] = {};
                double acc5timesQP[3][5] = {};
                double acc5timesDH[3][5] = {};

                // timeAverageUsingDifferentDataSizes[0-buildTime, 1-foundTime, 2-notFoundTime][sizeMultiplier]
                double ave5timesCH[3][5] = {};
                double ave5timesQP[3][5] = {};
                double ave5timesDH[3][5] = {};

                int times;
                for (times=0; times<5; times++) {  // run 5 tests

                    double m_mult[] = {0.1, 0.2, 0.3, 0.4, 0.6}; // size multipliers
                    int mult = 0;

                    for (mult=0; mult<5; mult++) { // run diffrent data sizes

                        for (seed=0; seed<1; seed++) { // use diffrent seeds

                            size = (int)(m * m_mult[mult]);
                            
                            // Measure insert time
                            size = m_mult[mult] * m;
                            // HT with chaining
                            insertTime(m, size, seed, tableCH, timesCH[seed][0][mult][times]);
                            // HT with quadratic probing
                            insertTime(m, size, seed, tableQP, timesQP[seed][0][mult][times]);
                            // HT with double hashing
                            insertTime(m, size, seed, tableDH, timesDH[seed][0][mult][times]);

                            // Accumulate times for diffrent seeds
                            accSeedsCH[0][mult][times] += timesCH[seed][0][mult][times];
                            accSeedsQP[0][mult][times] += timesQP[seed][0][mult][times];
                            accSeedsDH[0][mult][times] += timesDH[seed][0][mult][times];

                            size = 0.01 * m;
                            // Measure found time and not found time
                            // HT with chaining
                            timeFoundNotFound(m, size, seed, tableCH, timesCH[seed][1][mult][times], timesCH[seed][2][mult][times]);
                            // HT with quadratic probing
                            timeFoundNotFound(m, size, seed, tableCH, timesQP[seed][1][mult][times], timesQP[seed][2][mult][times]);
                            // HT with double hashing
                            timeFoundNotFound(m, size, seed, tableCH, timesDH[seed][1][mult][times], timesDH[seed][2][mult][times]);

                            // Accumulate times for diffrent seeds
                            accSeedsCH[1][mult][times] += timesCH[seed][1][mult][times];
                            accSeedsQP[1][mult][times] += timesQP[seed][1][mult][times];
                            accSeedsDH[1][mult][times] += timesDH[seed][1][mult][times];

                            accSeedsCH[2][mult][times] += timesCH[seed][2][mult][times];
                            accSeedsQP[2][mult][times] += timesQP[seed][2][mult][times];
                            accSeedsDH[2][mult][times] += timesDH[seed][2][mult][times];
                        }

                        // Averages for diffrent seeds
                        aveSeedsCH[0][mult][times] = accSeedsCH[0][mult][times] / 5.0;
                        aveSeedsQP[0][mult][times] = accSeedsQP[0][mult][times] / 5.0;
                        aveSeedsDH[0][mult][times] = accSeedsDH[0][mult][times] / 5.0;

                        aveSeedsCH[1][mult][times] = accSeedsCH[1][mult][times] / 5.0;
                        aveSeedsQP[1][mult][times] = accSeedsQP[1][mult][times] / 5.0;
                        aveSeedsDH[1][mult][times] = accSeedsDH[1][mult][times] / 5.0;

                        aveSeedsCH[2][mult][times] = accSeedsCH[2][mult][times] / 5.0;
                        aveSeedsQP[2][mult][times] = accSeedsQP[2][mult][times] / 5.0;
                        aveSeedsDH[2][mult][times] = accSeedsDH[2][mult][times] / 5.0;

                        // Accumulate data for 5 times
                        acc5timesCH[0][mult] += aveSeedsCH[0][mult][times];
                        acc5timesCH[1][mult] += aveSeedsCH[1][mult][times];
                        acc5timesCH[2][mult] += aveSeedsCH[2][mult][times];

                        acc5timesQP[0][mult] += aveSeedsQP[0][mult][times];
                        acc5timesQP[1][mult] += aveSeedsQP[1][mult][times];
                        acc5timesQP[2][mult] += aveSeedsQP[2][mult][times];

                        acc5timesDH[0][mult] += aveSeedsDH[0][mult][times];
                        acc5timesDH[1][mult] += aveSeedsDH[1][mult][times];
                        acc5timesDH[2][mult] += aveSeedsDH[2][mult][times];
                    }

                    // Average times for 5 times
                    for (int mult2=0; mult2<5; mult2++) {
                        ave5timesCH[0][mult2] = acc5timesCH[0][mult2] / 5.0;
                        ave5timesCH[1][mult2] = acc5timesCH[1][mult2] / 5.0;
                        ave5timesCH[2][mult2] = acc5timesCH[2][mult2] / 5.0;

                        ave5timesQP[0][mult2] = acc5timesQP[0][mult2] / 5.0;
                        ave5timesQP[1][mult2] = acc5timesQP[1][mult2] / 5.0;
                        ave5timesQP[2][mult2] = acc5timesQP[2][mult2] / 5.0;

                        ave5timesDH[0][mult2] = acc5timesDH[0][mult2] / 5.0;
                        ave5timesDH[1][mult2] = acc5timesDH[1][mult2] / 5.0;
                        ave5timesDH[2][mult2] = acc5timesDH[2][mult2] / 5.0;
                    }

                }
                // Print preformance tables
                std::cout << "\n\nPerformance (Open Hashing) in milliseconds:\n";
                std::cout << "         " << std::setw(9) << "100,000" << std::setw(9) <<  "200,000" << std::setw(9)
                <<  "300,000" << std::setw(9) <<  "400,000" << std::setw(9) <<  "500,000\n";
                std::cout << "Build    ";
                for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(9) << std::setprecision(2) << ave5timesCH[0][size]; }
                std::cout << "\n";
                std::cout << "Found    ";
                for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(9) << std::setprecision(2) << ave5timesCH[1][size]; }
                std::cout << "\n";
                std::cout << "Not Found";
                for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(9) << std::setprecision(2) << ave5timesCH[2][size]; }
                std::cout << "\n";

                std::cout << "\nPerformance (Quadratic Probing) in milliseconds::\n";
                std::cout << "         " << std::setw(9) << "100,000" << std::setw(9) <<  "200,000" << std::setw(9)
                <<  "300,000" << std::setw(9) <<  "400,000" << std::setw(9) <<  "500,000\n";
                std::cout << "Build    ";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesQP[0][size]; }
                std::cout << "\n";
                std::cout << "Found    ";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesQP[1][size]; }
                std::cout << "\n";
                std::cout << "Not Found";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesQP[2][size]; }
                std::cout << "\n";

                std::cout << "\nPerformance (Double Hashing) in milliseconds::\n";
                std::cout << "         " << std::setw(9) << "100,000" << std::setw(9) <<  "200,000" << std::setw(9)
                <<  "300,000" << std::setw(9) <<  "400,000" << std::setw(9) <<  "500,000\n";
                std::cout << "Build    ";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesDH[0][size]; }
                std::cout << "\n";
                std::cout << "Found    ";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesDH[1][size]; }
                std::cout << "\n";
                std::cout << "Not Found";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesDH[2][size]; }
                std::cout << "\n";
            }

            break;
            case 3:
            std::cout << "Bye bye!\n";
            break;
            default:
            std::cout << "\nError: Wrong input.\n\n";
        }
    }
    
    delete tableCH;
    delete tableDH;
    delete tableQP;
    return (0);
}
