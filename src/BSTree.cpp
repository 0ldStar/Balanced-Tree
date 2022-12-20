//
// Created by loki on 29.10.22.
//

#include "BSTree.h"

using namespace std;

template<typename T>
BSTree<T>::BSTree() {
    root = nullptr;
    elementCount = 0;
    laboriousness = 0;
    maxLayer = 0;
}

template<typename T>
BSTree<T>::BSTree(BSTree<T> &other) {
    root = nullptr;
    elementCount = 0;
    laboriousness = 0;
    maxLayer = 0;
    auto nodeList = new list<Node<T> *>();
    auto top = other.root;
    while (top != nullptr || !nodeList->empty()) {
        if (!nodeList->empty()) {
            top = nodeList->front();
            nodeList->pop_front();
        }
        while (top != nullptr) {
            push(top->key, top->data);
            if (top->right != nullptr) nodeList->push_front(top->right);
            top = top->left;
        }
    }
}
//
//template<typename T>
//BSTree<T>::~BSTree() {
//    clear();
//}


template<typename T>
bool BSTree<T>::push(INT_64 key, T data) {
    auto nodeList = new list<Node<T> *>();
    Node<T> *top = root;
    unsigned layer = 0;
    laboriousness = 0;
    if (!top) {
        root = new Node<T>(data, key, nullptr, layer);
        elementCount++;
        laboriousness++;
        return true;
    }
    while (top != nullptr || !nodeList->empty()) {
        if (top) {
            if (key < top->key) {
                if (!top->left) {
                    top->left = new Node<T>(data, key, top, layer + 1);
                    if (layer + 1 > maxLayer) maxLayer = layer + 1;
                    elementCount++;
                    return true;
                } else {
                    nodeList->push_front(top->left);
                }
            } else if (key > top->key) {
                if (!top->right) {
                    top->right = new Node<T>(data, key, top, layer + 1);
                    if (layer + 1 > maxLayer) maxLayer = layer + 1;
                    elementCount++;
                    return true;
                } else {
                    nodeList->push_front(top->right);
                }
            } else {
                top->data = data;
                return true;
            }
            laboriousness++;
        }
        top = nodeList->back();
        nodeList->pop_back();
        layer++;
    }
    return false;
}

template<typename T>
bool BSTree<T>::pop(INT_64 key) {
    if (!root)
        return false;
    laboriousness = 0;
    auto nodeList = new list<Node<T> *>();
    Node<T> *top = root;
    while (top != nullptr || !nodeList->empty()) {
        if (key < top->key) {
            if (!top->left) {
                return false;
            } else {
                nodeList->push_front(top->left);
            }
        } else if (key > top->key) {
            if (!top->right) {
                return false;
            } else {
                nodeList->push_front(top->right);
            }
        } else {
            popSwapNodes(top);
            return true;
        }
        top = nodeList->back();
        nodeList->pop_back();
        laboriousness++;
    }
    return false;
}

template<typename T>
void BSTree<T>::popSwapNodes(Node<T> *target) {
    Node<T> *parent = target->parent;

    if (target->right && target->left) {
        if (parent) {
            if (parent->right == target) parent->right = target->right;
            else parent->left = target->right;
        }
        Node<T> *tmp = target->right;
        while (tmp->left != nullptr) {
            tmp = tmp->left;
        }
        tmp->left = target->left;
        target->left->parent = tmp;
        target->right->parent = parent;
        if (root == target) root = target->right;
    } else if (target->right) {
        target->right->parent = parent;
        if (parent) {
            if (parent->left == target) parent->left = target->right;
            else parent->right = target->right;
        }
        if (root == target) root = target->right;
    } else if (target->left) {
        target->left->parent = parent;
        if (parent) {
            if (parent->left == target) parent->left = target->left;
            else parent->right = target->left;
        }
        if (root == target) root = target->left;
    } else {
        if (parent) {
            if (parent->left == target) parent->left = nullptr;
            else parent->right = nullptr;
        }
        if (root == target) root = nullptr;
    }

    delete target;
    elementCount--;
}

template<typename T>
std::string BSTree<T>::getKeysList() {
    elementList.clear();
    laboriousness = 0;
    if (root) {
        auto nodeList = new list<Node<T> *>();
        Node<T> *top = root;
        while (top != nullptr || !nodeList->empty()) {
            if (!nodeList->empty()) {
                top = nodeList->front();
                nodeList->pop_front();
                if (!nodeList->empty() && top->right == nodeList->front()) {
                    top = nodeList->front();
                    nodeList->pop_front();
                } else {
                    putElementInStr(top->key);
                    top = nullptr;
                }
            }
            while (top != nullptr) {
                nodeList->push_front(top);
                if (top->right != nullptr) {
                    nodeList->push_front(top->right);
                    nodeList->push_front(top);
                }
                top = top->left;
                laboriousness++;
            }
            laboriousness++;
        }
    } else {
        elementList = "BSTree is empty!";
    }
    return elementList;
}


template<typename T>
void BSTree<T>::putElementInStr(T data) {
    elementList.append(to_string(data));
    elementList.append(" ");
}

template<typename T>
unsigned BSTree<T>::getLength() { return elementCount; }

template<typename T>
bool BSTree<T>::isEmpty() { return elementCount == 0; }


//template<typename T>
//void BSTree<T>::clear() {
//    if (root) {
//        laboriousness = 0;
//        elementCount = 0;
//        auto nodeList = new list<Node<T> *>();
//        Node<T> *top = root;
//        while (top != nullptr || !nodeList->empty()) {
//            if (!nodeList->empty()) {
//                top = nodeList->front();
//                nodeList->pop_front();
//                if (!nodeList->empty() && top->right == nodeList->front()) {
//                    top = nodeList->front();
//                    nodeList->pop_front();
//                } else {
//                    if (top->parent && top->parent->left == top) {
//                        top->parent->left = nullptr;
//                    } else if (top->parent) {
//                        top->parent->right = nullptr;
//                    }
//                    delete top;
//                    top = nullptr;
//                }
//            }
//            while (top != nullptr) {
//                nodeList->push_front(top);
//                if (top->right != nullptr) {
//                    nodeList->push_front(top->right);
//                    nodeList->push_front(top);
//                }
//                top = top->left;
//                laboriousness++;
//            }
//            laboriousness++;
//        }
//        root = nullptr;
//    }
//}

template<typename T>
T &BSTree<T>::operator[](INT_64 key) {
    laboriousness = 0;
    if (root) {
        auto nodeList = new list<Node<T> *>();
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
bool BSTree<T>::merge(BSTree<T> &other) {
    if (!root)
        elementCount = 0;
    laboriousness = 0;
    auto nodeList = new list<Node<T> *>();
    auto top = other.root;
    while (top != nullptr || !nodeList->empty()) {
        if (!nodeList->empty()) {
            top = nodeList->front();
            nodeList->pop_front();
        }
        while (top != nullptr) {
            push(top->key, top->data);
            if (top->right != nullptr) nodeList->push_front(top->right);
            top = top->left;
            laboriousness++;
        }
    }
    return true;
}
template<typename T>
void BSTree<T>::checkLayer(Node<T> *p, unsigned layer) {
    if (!p) return;
    checkLayer(p->left, layer + 1);
    p->layer = layer;
    if (layer > maxLayer) maxLayer = layer;
    checkLayer(p->right, layer + 1);
}
template<typename T>
void BSTree<T>::printStructure() {
    auto nodeList = new list<Node<T> *>();
    Node<T> *top = root;
    bool flag;
    unsigned layer = -1;
    bool firstElFlag = false;

    maxLayer = 0;
    checkLayer(root, 0);
    cout << "Max layer: " << maxLayer << endl;
    string buf;
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
    cout << buf;
}

template<typename T>
unsigned BSTree<T>::getLaboriousness() { return laboriousness; }

template<typename T>
BTreeStraightIterator<T> BSTree<T>::begin() {
    return BTreeStraightIterator<T>(root, elementCount, 0);
}

template<typename T>
BTreeStraightIterator<T> BSTree<T>::end() {
    return BTreeStraightIterator<T>(root, elementCount, -1);
}

template<typename T>
BTreeBackIterator<T> BSTree<T>::rbegin() {
    return BTreeBackIterator<T>(root, elementCount, elementCount - 1);
}

template<typename T>
BTreeBackIterator<T> BSTree<T>::rend() {
    return BTreeBackIterator<T>(root, elementCount, -1);
}

template<>
int BSTree<int>::getDefaultValue() { return 0; }

template<>
char BSTree<char>::getDefaultValue() { return ' '; }

template<>
float BSTree<float>::getDefaultValue() { return 0.0; }

template<>
INT_64 BSTree<INT_64>::getDefaultValue() { return 0; }

template
class BSTree<int>;

template
class BSTree<char>;

template
class BSTree<float>;

template
class BSTree<INT_64>;