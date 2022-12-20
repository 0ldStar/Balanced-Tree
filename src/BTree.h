//
// Created by loki on 22.11.22.
//

#ifndef ASD_3_BTREE_H
#define ASD_3_BTREE_H

#include <iostream>
#include <string>
#include "BSTree.h"
#include "Node.h"
#include "BTreeStraightIterator.h"
#include "BTreeBackIterator.h"

template<typename T>
class BTree : public BSTree<T> {
public:
    BTree();

    BTree(BTree &other);

    ~BTree();

    void clear();

    bool push(INT_64 key, T data);

    bool pop(INT_64 key);


private:
    Node<T> *R(Node<T> *node);

    Node<T> *L(Node<T> *node);

    Node<T> *insert(Node<T> *p, INT_64 k, T data, int layer);

    unsigned char height(Node<T> *p);

    int bfactor(Node<T> *p);

    Node<T> *balance(Node<T> *p);

    void fixHeight(Node<T> *p);

    Node<T> *findMin(Node<T> *p);

    Node<T> *removeMin(Node<T> *p);

    Node<T> *remove(Node<T> *p, INT_64 k);

    void destruct(Node<T> *t);

};


#endif //ASD_3_BTREE_H
