//
// Created by 付旭炜 on 2017/10/11.
//

#ifndef SEQUENCE_MYVECTOR_H
#define SEQUENCE_MYVECTOR_H

#include "Sequence.h"
#include <iostream>

/*
 * 对基本类型不能提供初始化
 */
template <typename Type>
class MyVector: public Sequence<Type> {
    const static size_type BASE_SIZE = 8;
private:
    Type* _vec;
    size_type capacity;
public:
    explicit MyVector(size_type size): Sequence<Type>(size) {
        capacity = BASE_SIZE;
        // expand the size of the capacity
        while (Sequence<Type>::_size > capacity) { capacity *= 2; }
        _vec = new Type[capacity];
    }
    MyVector() {

        Sequence<Type>::_size = 0;
        capacity = BASE_SIZE;
        _vec = new Type[capacity];
    }

    void push_back(const Type& value) {
        size_type value_index = Sequence<Type>::_size; // 新值的位置
        ++Sequence<Type>::_size;
        resize();
        _vec[value_index] = value;
    }

    void pop_back() {
        if (Sequence<Type>::_size == 0) {
            std::cout << "pop_back a zero size vector" << std::endl;
            return;
        }
        --Sequence<Type>::_size;
        resize();
    }

    Type& back() {
        if (Sequence<Type>::_size == 0) {
            std::cerr << "use back() at a zero size vector" << std::endl;
            exit(-1);
        }
        return _vec[Sequence<Type>::_size - 1];
    }
    virtual Type&operator[](size_type index) {
        if (index > Sequence<Type>::_size) {
            std::cerr << "[" << index << "]" << " out of range!" << std::endl;
            exit(-1);
        }
        return _vec[index];
    }
//    virtual const Type&operator[](size_type index) {
//        if (index > Sequence<Type>::_size) {
//            std::cerr << "[" << index << "]" << " out of range!" << std::endl;
//            exit(-1);
//        }
//    }
private:
    /*
     * resize according the Sequence<Type>::_size
     */
    void resize() {
        // regot the capacity
        if (capacity == Sequence<Type>::_size) {
            capacity *= 2;
        } else if (capacity > 2 * Sequence<Type>::_size && capacity > BASE_SIZE) {
            capacity /= 2;
        } else {
            return;
        }

        Type* _newvec = new Type[capacity];
        for (int i = 0; i < Sequence<Type>::_size; ++i) {
            _newvec[i] = std::move(_vec[i]);
        }
        delete [] _vec;
        _vec = _newvec;
    }
};


#endif //SEQUENCE_MYVECTOR_H
