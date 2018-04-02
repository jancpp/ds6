/*
Author: Jan Polzer
File:   LinkedList.h
Date:   1/21/2018

*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

class LinkedList {
private:
        int m_size;
        Node* m_front;

public:
        // Sets m_front to null pointer and m_front to zero
        LinkedList();

        // Deletes all nodes in the linked list
        ~LinkedList();

        // Inserts a node at the beginig of LinkedList
        void insertFront(int value);

        // Returns true if LinkedList is empty
        bool isEmpty();

        // Removes a value from list if found using the eraseHelper method
        void erase(int value);

        // Removes a value that is currently pointed to from list
        void eraseHelper(int value, Node* curr);

        // Print all elements in list
        void print();

        // Returns a pointer to the node containing the value we searched for
        Node* find(int value);
};

#endif
