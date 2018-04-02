/*
Author: Jan Polzer
File:   OpenHash.cpp
Date:   1/28/2018
*/

#include "LinkedList.h"
#include "Node.h"
#include "OpenHash.h"

OpenHash::OpenHash(int tableSize) {
        m_size = 0;
        m_tableSize = tableSize;
        m_table = new LinkedList* [tableSize];
        for (int i = 0; i < tableSize; i++) {
                m_table[i] = new LinkedList();
        }
}
OpenHash::~OpenHash() {
        for (int i = 0; i< m_tableSize; i++) {
                delete m_table[i];
                m_table[i] = nullptr;
        }
        delete[] m_table;
        m_table = nullptr;
}

int OpenHash::hash(int value) {
        return (value % m_tableSize);
}

bool OpenHash::insert(int value) {
    bool inserted = false;
    int key = hash(value);
    if (!find(value)) {
        m_table[key]->insertFront(value);
        m_size++;
        inserted = true;
    }
    return inserted;
}

bool OpenHash::isEmpty() {
        return (m_size = 0);
}

void OpenHash::remove(int value) {
        int key = hash(value);
                m_table[key]->erase(value);
                m_size--;
}

void OpenHash::print() {
    std::cout << "\nHash table with chaining:\n";
        for (int i=0; i<m_tableSize; i++) {
            if (!m_table[i]->isEmpty()) {
                std::cout << "Bucket " << i << ":";
                m_table[i]->print();
            }
        }
}

bool OpenHash::find(int value) {
        int key = hash(value);
        return (m_table[key]->find(value) != nullptr) ;
}
