/*
 Author: Jan Polzer
 File:   ClosedHashQP.cpp
 Date:   2/6/2018
 */

#include "ClosedHashQP.h"

ClosedHashQP::ClosedHashQP(int tableSize, int k_number, int p_number) {
    m_size = 0;
    m_tableSize = tableSize;
    m_k_number = k_number;
    m_p_number = p_number;
    m_table = new int[tableSize];
    for (int i = 0; i < tableSize; i++) {
        m_table[i] = -1;
    }
}
ClosedHashQP::~ClosedHashQP() {
    delete[] m_table;
}

int ClosedHashQP::hash(int value) {
    int key = (value % m_tableSize);
    return key;
}

bool ClosedHashQP::insert(int value) {
    bool inserted = false;
    int k_count = 0;
    int i_count = 0;
    int key = hash(value);
    if (!find(value)) {
        if (m_table[key] == -1) {
            m_table[key] = value;
            m_size++;
            inserted = true;
        } else {
                while (k_count < m_k_number) {
                    key = hash(i_count*i_count + value);
                    if (m_table[key] == -1) {
                        m_table[key] = value;
                        m_size++;
                        inserted = true;
                        break;
                    }
                    k_count++;
                    i_count++;
                }
        }
    }
    return inserted;
}

bool ClosedHashQP::isEmpty() {
    return (m_size = 0);
}

bool ClosedHashQP::remove(int value) {
    bool removed = false;
    int k_count = 0;
    int i_count = 0;
    int key = hash(value);
        if (m_table[key] == value) {
            m_table[key] = -1;
            m_size--;
            removed = true;
        } else {
                while (k_count < m_k_number) {
                    key = hash(i_count*i_count + value);
                    if (m_table[key] == value) {
                        m_table[key] = -1;
                        m_size--;
                        removed = true;
                        break;
                    }
                    k_count++;
                    i_count++;
                }
            }
    return removed;
}

void ClosedHashQP::print() {
    std::cout << "\nHash table with quadratic probing:\n";
    for (int i=0; i<m_tableSize; i++) {
        if (m_table[i] != -1) {
            std::cout << "Bucket " << i << ": ";
            std::cout << m_table[i] << "\n";
        }
    }
}

bool ClosedHashQP::find(int value) {
    int found = false;
    int k_count = 0;
    int i_count = 0;
    int key = hash(value);
    if (m_table[key] == value) {
        found = true;
    } else {
            while (k_count < m_k_number) {
                key = hash(i_count*i_count + value);
                if (m_table[key] == value) {
                    found = true;
                    break;
                }
                k_count++;
                i_count++;
            }
    }
    return found;
}

double ClosedHashQP::loadFactor() {
    return (double(m_size) / m_tableSize);
}
