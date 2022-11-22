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

    bool isEmpty();

    void clear();

    T &operator[](INT_64 key);

    bool push(INT_64 key, T data);

    bool pop(INT_64 key);

    BTreeStraightIterator<T> begin();

    BTreeStraightIterator<T> end();

    BTreeBackIterator<T> rbegin();

    BTreeBackIterator<T> rend();

    void printStructure();

    unsigned getLaboriousness();

private:
    Node<T> *R(Node<T> *node);

    Node<T> *LR(Node<T> *node);

    Node<T> *L(Node<T> *node);

    Node<T> *RL(Node<T> *node);

    Node<T> *insert(Node<T> *p, INT_64 k, T data, int layer);

    unsigned char height(Node<T> *p);

    int bfactor(Node<T> *p);

    Node<T> *balance(Node<T> *p);

    void fixHeight(Node<T> *p);

    Node<T> *findMin(Node<T> *p);

    Node<T> *removeMin(Node<T> *p);

    Node<T> *remove(Node<T> *p, INT_64 k);

    void destruct(Node<T> *t);

    void checkLayer(Node<T> *p, unsigned layer);

    T getDefaultValue();

    Node<T> *root;
    unsigned size;
    unsigned laboriousness;
    T defaultValue;
    unsigned maxLayer;
};


#endif //ASD_3_BTREE_H
