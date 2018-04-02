/*
Author: Jan Polzer
File:   Node.h
Date:   1/21/2018
*/

#ifndef NODE_H
#define NODE_H

class Node {
private:
        int m_value;
        Node* m_next;

public:
        // Sets m_value to zero and n_next to null pointer
        Node();
        
        // Gets a node value
        int value() const;

        // Assigns value to a node
        void setValue(int value);

        // Reutn the next node
        Node* next() const;

        // Set the next node
        void setNext(Node* previous);
};

#endif
