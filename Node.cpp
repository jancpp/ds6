/*
Author: Jan Polzer
File:   Node.cpp
Date:   1/21/2018
*/
#include "Node.h"

Node::Node() {
        m_value = 0;
        m_next = nullptr;
}

int Node::value() const {
        return m_value;
}

void Node::setValue(int value) {
        m_value = value;
}

Node* Node::next() const {
        return m_next;
}

void Node::setNext(Node* previous) {
        m_next = previous;
}
