//
// Created by loki on 22.11.22.
//

#include "BTree.h"

template<typename T>
BTree<T>::BTree() : BSTree<T>() {
}

template<typename T>
BTree<T>::BTree(BTree &other) : BSTree<T>(other) {}

template<typename T>
BTree<T>::~BTree() {
    destruct(BSTree<T>::root);
}

template<typename T>
void BTree<T>::clear() {
    destruct(BSTree<T>::root);
    BSTree<T>::elementCount = 0;
    BSTree<T>::laboriousness = 0;
    BSTree<T>::maxLayer = 0;
}

template<typename T>
void BTree<T>::destruct(Node<T> *t) {
    if (t) {
        Node<T> *tmp = t->right;
        destruct(t->left);
        delete t;
        destruct(tmp);
    }
}


template<typename T>
bool BTree<T>::push(INT_64 key, T data) {
    BSTree<T>::laboriousness = 0;
    BSTree<T>::root = insert(BSTree<T>::root, key, data, 0);
    BSTree<T>::elementCount++;
    return true;
}

template<typename T>
bool BTree<T>::pop(INT_64 key) {
    BSTree<T>::laboriousness = 0;
    BSTree<T>::root = remove(BSTree<T>::root, key);
    BSTree<T>::elementCount--;
    return false;
}

template<typename T>
Node<T> *BTree<T>::findMin(Node<T> *p) {
    return p->left ? findMin(p->left) : p;
}

template<typename T>
Node<T> *BTree<T>::removeMin(Node<T> *p) {
    if (p->left == nullptr)
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

template<typename T>
Node<T> *BTree<T>::remove(Node<T> *p, INT_64 k) {
    BSTree<T>::laboriousness++;
    if (!p) return nullptr;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else {
        Node<T> *q = p->left;
        Node<T> *r = p->right;
        delete p;
        if (!r) return q;
        Node<T> *min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

template<typename T>
unsigned char BTree<T>::height(Node<T> *p) {
    return p ? p->height : 0;
}

template<typename T>
int BTree<T>::bfactor(Node<T> *p) {
    return height(p->right) - height(p->left);
}

template<typename T>
void BTree<T>::fixHeight(Node<T> *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

template<typename T>
Node<T> *BTree<T>::insert(Node<T> *p, INT_64 k, T data, int layer) {
    BSTree<T>::laboriousness++;
    if (!p) return new Node<T>(k, data, layer);
    if (k < p->key)
        p->left = insert(p->left, k, data, layer + 1);
    else
        p->right = insert(p->right, k, data, layer + 1);
    return balance(p);
}

template<typename T>
Node<T> *BTree<T>::balance(Node<T> *p) {
    BSTree<T>::laboriousness++;
    fixHeight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = R(p->right);
        return L(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = L(p->left);
        return R(p);
    }
    return p;
}

template<typename T>
Node<T> *BTree<T>::R(Node<T> *p) {
    Node<T> *q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

template<typename T>
Node<T> *BTree<T>::L(Node<T> *q) {
    Node<T> *p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

template
class BTree<int>;

template
class BTree<char>;

template
class BTree<float>;

template
class BTree<INT_64>;
