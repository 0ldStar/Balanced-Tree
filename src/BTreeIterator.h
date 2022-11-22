//
// Created by loki on 06.11.22.
//

#ifndef ASD_2_BTREEITERATOR_H
#define ASD_2_BTREEITERATOR_H

#include <vector>
#include <list>
#include "Node.h"

template<typename T>
class BTreeIterator {
public:
    using value_type = T;
    using pointer = Node<T> *;
    using reference = BTreeIterator<T> &;

    BTreeIterator(pointer _root, unsigned _elementCount, int _ind) {
        root = _root;
        ind = _ind;
        elementCount = _elementCount;
        if (root) {
            nodeVector = *new std::vector<pointer>();
            fillList();
        }
    }

    value_type &operator*() const { return nodeVector[ind]->data; }

    Node<T>* operator->() { return &nodeVector[ind]; }

    int getInd() { return ind; }

    friend bool operator==(const BTreeIterator &a, const BTreeIterator &b) { return a.ind == b.ind; };

    friend bool operator!=(const BTreeIterator &a, const BTreeIterator &b) { return a.ind != b.ind; };

    int getKey() { return nodeVector[ind]->key; }

protected:

    void fillList() {
        pointer top = root;
        auto nodeList = new std::list<pointer>();
        while (top != nullptr || !nodeList->empty()) {
            if (!nodeList->empty()) {
                top = nodeList->front();
                nodeList->pop_front();
                nodeVector.push_back(top);
                if (top->right != nullptr) top = top->right;
                else top = nullptr;
            }
            while (top != nullptr) {
                nodeList->push_front(top);
                top = top->left;
            }
        }
    }

    std::vector<pointer> nodeVector;
    int ind;
    unsigned elementCount;
    pointer root;
};


#endif //ASD_2_BTREEITERATOR_H
