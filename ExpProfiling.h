//
//  ExpProfiling.h
//
//  Created by Jan Polzer on 3/11/18.
//  Copyright © 2018 Jan Polzer. All rights reserved.
//

#ifndef ExpProfiling_h
#define ExpProfiling_h

#include "OpenHash.h"
#include "ClosedHashDH.h"
#include "ClosedHashQP.h"
#include <stdio.h>
#include <iostream>
#include <ctime>

class ExpProfiling {
public:
    // Measure time that take to insert @size random numbers into hash tables
    template <class T>
    static void insertTime (int m, int size, int seed, T *table, float &time);
    
    
    
    // Measure time that take to find or not find @size random numbers into hash tables
    template <class T>
    static void timeFoundNotFound (int m, int size, int seed, T *table, float &timeFound, float &timeNotFound);

};

#endif
