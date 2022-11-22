//
// Created by loki on 30.10.22.
//

#ifndef ASD_2_BTREESTRAIGHTITERATOR_H
#define ASD_2_BTREESTRAIGHTITERATOR_H

#include "BTreeIterator.h"

template<typename T>
class BTreeStraightIterator : public BTreeIterator<T> {
public:
    using value_type = T;
    using pointer = Node<T> *;
    using reference = BTreeStraightIterator<T> &;

    BTreeStraightIterator(pointer _root, unsigned _elementCount, int _ind) :
            BTreeIterator<T>(_root, _elementCount, _ind) {};

    const reference &operator++() {
        BTreeIterator<T>::ind++;
        if (BTreeIterator<T>::ind == BTreeIterator<T>::elementCount) BTreeIterator<T>::ind = -1;
        return *this;
    }

    const reference &operator--(int) {
        BTreeIterator<T>::ind--;
        return *this;
    }

    const reference operator++(int) {
        BTreeIterator<T>::ind++;
        if (BTreeIterator<T>::ind == BTreeIterator<T>::elementCount) BTreeIterator<T>::ind = -1;
        return *this;
    }
};


#endif //ASD_2_BTREESTRAIGHTITERATOR_H
