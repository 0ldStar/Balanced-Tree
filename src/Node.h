//
// Created by loki on 22.11.22.
//

#ifndef ASD_3_NODE_H
#define ASD_3_NODE_H
typedef unsigned long long int INT_64;

template<typename T>
struct Node {
    Node(INT_64 _key, T _data) : key(_key), data(_data) {
        right = nullptr;
        left = nullptr;
        layer = 0;
        height = 0;
    };

    Node(INT_64 _key, T _data, unsigned _layer) : key(_key), data(_data), layer(_layer) {
        right = nullptr;
        left = nullptr;
        height = 0;
    };

    Node(T _data, INT_64 _key, Node *_parent, unsigned _layer) : data(_data), key(_key), right(nullptr), left(nullptr),
                                                                 parent(_parent), layer(_layer) {};

    Node(T _data, INT_64 _key, Node *_parent, Node *_left, Node *_right, unsigned _layer) : data(_data), key(_key),
                                                                                            right(_right), left(_left),
                                                                                            parent(_parent),
                                                                                            layer(_layer) {};
    INT_64 key;
    Node *right;
    Node *left;
    Node *parent;
    int height;
    unsigned layer;
    T data;
};

#endif //ASD_3_NODE_H
