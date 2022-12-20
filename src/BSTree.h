//
// Created by loki on 29.10.22.
//

#ifndef ASD_2_BSTREE_H
#define ASD_2_BSTREE_H

#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include "Node.h"
#include "BTreeStraightIterator.h"
#include "BTreeBackIterator.h"

template<typename T>
class BSTree {
public:
    BSTree();

    BSTree(BSTree<T> &other);

//    ~BSTree();

    unsigned getLength();

//    virtual void clear();

    bool isEmpty();

    T &operator[](INT_64 key);

    virtual bool push(INT_64 key, T data);

    virtual bool pop(INT_64 key);

    std::string getKeysList();

    bool merge(BSTree<T> &other);

    BTreeStraightIterator<T> begin();

    BTreeStraightIterator<T> end();

    BTreeBackIterator<T> rbegin();

    BTreeBackIterator<T> rend();

    void printStructure();

    unsigned getLaboriousness();

protected:
    void putElementInStr(T data);

    void popSwapNodes(Node<T> *target);

    virtual T getDefaultValue();

    virtual void checkLayer(Node<T> *p, unsigned layer);

    unsigned laboriousness;
    std::string elementList;
    Node<T> *root;
    unsigned elementCount;
    unsigned maxLayer;
    T defaultValue;
};

#endif //ASD_2_BSTREE_H
