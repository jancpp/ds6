/*
Author: Jan Polzer
File:   ClosedHashQP.h
Date:   2/6/2018

*/

#ifndef ClosedHashQP_H
#define ClosedHashQP_H

#include <iostream>
#include <iomanip>

class ClosedHashQP {
private:
        int m_size;
        int m_tableSize; // m number
        int m_k_number;  //  number of hashing
        int m_p_number;  //  prime number
        int* m_table;
    
public:
        // @pre:    None
        // @post:   Initialized hash table
        // @return: None
        ClosedHashQP(int tableSize, int k_number, int p_number);

        // @pre:    Hash table
        // @post:   Freed memory
        // @return: None
        ~ClosedHashQP();

        // @pre:    Hash table
        // @post:   none
        // @return: A bucket index based on hashed value, -1 if bucket in not empty
        int hash(int key);

        // @pre:    Hash table
        // @post:   A number inserted in the hash table
        //          A message displayed if failed to insert
        //          Displayed load factor
        // @return: True if succesfully inserted, false otherwise
        bool insert(int key);

        // @pre:    Hash table
        // @post:   None
        // @return: True if table is empty, false otherwise
        bool isEmpty();

        // @pre:    Hash table
        // @post:   A number removed from the hash table if found
        //          Prints a message if deleted or if not found
        //          Display load factor
        // @return: True if number removed, false otherwise
        bool remove(int key);

        // @pre:    Hash table
        // @post:   Printed all elements in the hash table
        // @return: none
        void print();
    
        // @pre:    Hash table
        // @post:   None
        // @return: True if value is found in hash table, false otherwise
        bool find(int value);
    
        // @pre:    Hash table
        // @post:   None
        // @return: Calculated load factor
        double loadFactor();
};

#endif
