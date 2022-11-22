//
// Created by loki on 22.11.22.
//

#ifndef ASD_3_BTREE_H
#define ASD_3_BTREE_H

#include <iostream>
#include <string>
#include "Node.h"
#include "BTreeStraightIterator.h"
#include "BTreeBackIterator.h"

template<typename T>
class BTree {
public:
    BTree();

    BTree(BTree &other);

    ~BTree();

    unsigned getSize();

    void clear();

    T &operator[](INT_64 key);

    BTreeStraightIterator<T> begin();

    BTreeStraightIterator<T> end();

    BTreeBackIterator<T> rbegin();

    BTreeBackIterator<T> rend();

    void printStructure();

    unsigned getLaboriousness();

private:
    Node<T> *root;
    unsigned size;
    unsigned laboriousness;
    std::string elementList;
};


#endif //ASD_3_BTREE_H
