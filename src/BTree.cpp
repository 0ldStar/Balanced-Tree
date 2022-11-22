//
// Created by loki on 22.11.22.
//

#include "BTree.h"

template<typename T>
BTree<T>::BTree() {
    root = nullptr;
    size = 0;
    laboriousness = 0;
    maxLayer = 0;
}

template<typename T>
BTree<T>::~BTree() {
    destruct(root);
}

template<typename T>
void BTree<T>::clear() {
    destruct(root);
    size = 0;
    laboriousness = 0;
    maxLayer = 0;
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
    root = insert(root, key, data, 0);
    size++;
    return true;
}

template<typename T>
bool BTree<T>::pop(INT_64 key) {
    root = remove(root, key);
    size--;
    return false;
}

template<typename T>
unsigned BTree<T>::getSize() { return size; }

template<typename T>
bool BTree<T>::isEmpty() { return size == 0; }

template<typename T>
unsigned BTree<T>::getLaboriousness() { return laboriousness; }

template<typename T>
T &BTree<T>::operator[](INT_64 key) {
    laboriousness = 0;
    if (root) {
        auto nodeList = new std::list<Node<T> *>();
        Node<T> *top = root;
        while (top != nullptr || !nodeList->empty()) {
            if (top) {
                if (key < top->key && top->left) {
                    nodeList->push_front(top->left);
                } else if (key > top->key && top->right) {
                    nodeList->push_front(top->right);
                } else if (top->key == key) {
                    return top->data;
                } else {
                    break;
                }
                laboriousness++;
            }
            top = nodeList->back();
            nodeList->pop_back();
        }
    }
    defaultValue = getDefaultValue();
    laboriousness = -1;
    return defaultValue;

}

template<typename T>
void BTree<T>::checkLayer(Node<T> *p, unsigned layer) {
    if (!p) return;
    checkLayer(p->left, layer + 1);
    p->layer = layer;
    if (layer > maxLayer) maxLayer = layer;
    checkLayer(p->right, layer + 1);
}

template<typename T>
void BTree<T>::printStructure() {
    if (!root) return;
    auto nodeList = new std::list<Node<T> *>();
    Node<T> *top = root;
    bool flag;
    unsigned layer = -1;
    bool firstElFlag = false;
    maxLayer = 0;
    checkLayer(root, 0);
    std::cout << "Max layer: " << maxLayer << std::endl;
    std::string buf;
    char tmp[4];

    do {
        flag = false;
        if (layer != top->layer) {
            layer = top->layer;
            buf.append("\n");
            firstElFlag = true;
        }
        if (top->key != -1000 && firstElFlag) {
            firstElFlag = false;
            for (int i = 0; i < (1 << (maxLayer - layer)) - 1; ++i) {
                buf.append("   ");
            }
        }
        if (top->key == -1000) {
            if (top->layer <= maxLayer)
                buf.append("*  ");
        } else {
            sprintf(tmp, "%-3lld", top->key);
            buf.append(tmp);
            auto *nullNode = new Node<T>(-1000, getDefaultValue());
            nullNode->layer = top->layer + 1;
            if (top->left != nullptr) {
                nodeList->push_back(top->left);
            } else {
                nodeList->push_back(nullNode);
            }
            if (top->right != nullptr) {
                nodeList->push_back(top->right);
            } else {
                nodeList->push_back(nullNode);
            }
        }
        for (int i = 0; i < (1 << (maxLayer - layer + 1)) - 1; ++i)
            buf.append("   ");

        if (!nodeList->empty()) {
            top = nodeList->front();
            nodeList->pop_front();
            if (nodeList->empty()) flag = true;
        }
    } while (!nodeList->empty() || flag);
    std::cout << buf << std::endl;
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
    if (!p) return new Node<T>(k, data, layer);
    if (k < p->key)
        p->left = insert(p->left, k, data, layer + 1);
    else
        p->right = insert(p->right, k, data, layer + 1);
    return balance(p);
}

template<typename T>
Node<T> *BTree<T>::balance(Node<T> *p) {
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
Node<T> *BTree<T>::LR(Node<T> *node) {
    Node<T> *x = node->left;
    Node<T> *y = x->right;
    x->right = y->left;
    y->left = x;
    node->left = y->right;
    y->right = node;
    if (y->height == -1) {
        node->height = 1;
        x->height = 0;
    }
    if (y->height == 0) {
        node->height = x->height = 0;
    }
    if (y->height == 1) {
        node->height = 0;
        x->height = -1;
    }
    y->height = 0;
    return y;
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

template<typename T>
Node<T> *BTree<T>::RL(Node<T> *node) {
    Node<T> *x = node->left;
    Node<T> *y = x->right;
    x->right = y->left;
    y->left = x;
    node->left = y->right;
    y->right = node;
    if (y->height == -1) {
        node->height = 1;
        x->height = 0;
    }
    if (y->height == 0) {
        node->height = x->height = 0;
    }
    if (y->height == 1) {
        node->height = 0;
        x->height = -1;
    }
    y->height = 0;
    return y;
}

template<typename T>
BTreeStraightIterator<T> BTree<T>::begin() {
    return BTreeStraightIterator<T>(root, size, 0);
}

template<typename T>
BTreeStraightIterator<T> BTree<T>::end() {
    return BTreeStraightIterator<T>(root, size, -1);
}

template<typename T>
BTreeBackIterator<T> BTree<T>::rbegin() {
    return BTreeBackIterator<T>(root, size, size - 1);
}

template<typename T>
BTreeBackIterator<T> BTree<T>::rend() {
    return BTreeBackIterator<T>(root, size, -1);
}

template<>
int BTree<int>::getDefaultValue() { return 0; }

template<>
char BTree<char>::getDefaultValue() { return ' '; }

template<>
float BTree<float>::getDefaultValue() { return 0.0; }

template<>
INT_64 BTree<INT_64>::getDefaultValue() { return 0; }

template
class BTree<int>;

template
class BTree<char>;

template
class BTree<float>;

template
class BTree<INT_64>;
