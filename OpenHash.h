/*
Author: Jan Polzer
File:   OpenHash.h
Date:   1/28/2018

*/

#ifndef OPENHASH_H
#define OPENHASH_H

#include "Node.h"
#include "LinkedList.h"

class OpenHash {
private:
        int m_size;
        int m_tableSize;
        LinkedList** m_table;

public:
        // Constructor
        OpenHash(int tableSize);

        // Destructor
        ~OpenHash();

        // Function that uses "mod" as HashTable function
        // Returns a table index for key value
        int hash(int key);

        // Inserts a node at the at the begining of hash table
        // Duplicate numbers are rejected
        bool insert(int key);

        // Returns true if LinkedList is empty
        bool isEmpty();

        // Removes a value from the hash table
        // Outputs a message whether deleted or not found
        void remove(int key);

        // Print all elements in hash table
        void print();

        // Returns true if key is found in hash table
        bool find(int value);
};

#endif
