/*
 Author: Jan Polzer
 File:   ClosedHashDH.cpp
 Date:   2/6/2018
 */

#include "ClosedHashDH.h"

ClosedHashDH::ClosedHashDH(int tableSize, int k_number, int p_number) {
    m_size = 0;
    m_tableSize = tableSize;
    m_k_number = k_number;
    m_p_number = p_number;
    m_table = new int[m_tableSize];
    for (int i = 0; i < m_tableSize; i++) {
        m_table[i] = -1;
    }
}
ClosedHashDH::~ClosedHashDH() {
    delete[] m_table;
}

int ClosedHashDH::hash(int value) {
    int key = (value % m_tableSize);
    return key;
}

bool ClosedHashDH::insert(int value) {
    bool inserted = false;
    int k_count = 0;
    int key = hash(value);
    if (!find(value)) {
        if (m_table[key] == -1) {
            m_table[key] = value;
            m_size++;
            inserted = true;
        } else {
            
                int h_plus = m_p_number - (value % m_p_number);
                int h_x = value % m_tableSize;
                while (k_count < m_k_number) {
                    key =  hash(k_count * h_plus + h_x);
                    if (m_table[key] == -1) {
                        m_table[key] = value;
                        m_size++;
                        inserted = true;
                        break;
                    }
                    k_count++;
                }
            }
    }
    return inserted;
}

bool ClosedHashDH::isEmpty() {
    return (m_size = 0);
}

bool ClosedHashDH::remove(int value) {
    bool removed = false;
    int k_count = 0;
    int key = hash(value);
        if (m_table[key] == value) {
            m_table[key] = -1;
            m_size--;
            removed = true;
        } else {
            
                int h_plus = m_p_number - (value % m_p_number);
                int h_x = value % m_tableSize;
                while (k_count < m_k_number) {
                    key =  hash(k_count * h_plus + h_x);
                    if (m_table[key] == value) {
                        m_table[key] = -1;
                        m_size--;
                        removed = true;
                        break;
                    }
                    k_count++;
                }
            
        }
    return removed;
}

void ClosedHashDH::print() {
    std::cout << "\nHash table with double hashing:\n";
    for (int i=0; i<m_tableSize; i++) {
        if (m_table[i] != -1) {
            std::cout << "Bucket " << i << ": ";
            std::cout << m_table[i] << "\n";
        }
    }
}

bool ClosedHashDH::find(int value) {
    int found = false;
    int k_count = 0;
    int key = hash(value);
    if (m_table[key] == value) {
        found = true;
    } else {
        
            int h_plus = m_p_number - (value % m_p_number);
            int h_x = value % m_tableSize;
            while (k_count < m_k_number) {
                key = hash(k_count * h_plus + h_x);
                if (m_table[key] == value) {
                    found = true;
                    break;
                }
                k_count++;
            }
        
    }
    return found;
}

double ClosedHashDH::loadFactor() {
    return (double(m_size) / m_tableSize);
}
