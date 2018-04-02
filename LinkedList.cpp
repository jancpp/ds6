/*
Author: Jan Polzer
File:   LinkedList.cpp
Date:   1/21/2018
*/

#include "LinkedList.h"
#include "Node.h"

LinkedList::LinkedList() {
        m_size = 0;
        m_front = nullptr;
}

LinkedList::~LinkedList() {
        Node *temp = m_front;
        while(temp != nullptr) {
                Node *toDelete = temp;
                temp = temp->next();;
                delete toDelete;
        }
}

void LinkedList::insertFront(int value) {
        if (isEmpty()) { // insert in empty list
                m_front = new Node();
                m_front->setValue(value);
                m_front->setNext(nullptr);
        } else {
                Node* newNode = new Node();
                newNode->setValue(value);
                newNode->setNext(m_front);
                m_front = newNode;
        }
        m_size++;
}

bool LinkedList::isEmpty() {
        return(m_size == 0);
}

void LinkedList::erase(int value) {
        Node* curr = find(value);
        if (curr == m_front) { // first node in the list
                if (m_front->next() == nullptr) { // the only node in List
                        delete m_front;
                        m_front = nullptr;
                } else { // more nodes after m_front node
                        m_front = curr->next();
                        delete curr;
                }
                m_size--;
        } else { // two or more nodes in the list
                eraseHelper(value, m_front);
                m_size--;
        }
}

void LinkedList::eraseHelper(int value, Node* prev) {
        Node* curr = prev->next();
        if (prev->next()->value() == value) {
                prev->setNext(curr->next());
                delete curr;
        } else {
                eraseHelper(value, prev->next());
        }
}

void LinkedList::print() {
        Node* curr = m_front;
        if (!isEmpty()) {
                while (curr != nullptr) {
                        std::cout << " " << curr->value();
                        curr = curr->next();
                }
        }
        std::cout << "\n";
}

Node* LinkedList::find(int value) {
        Node* result = nullptr;
        if (!isEmpty()) {
                Node* curr = m_front;
                while ((curr->value() != value) && (curr->next() != nullptr)) {
                        curr = curr->next();
                }
                if (curr->value() == value) {
                        result = curr;
                }
        }
        return result;
}
