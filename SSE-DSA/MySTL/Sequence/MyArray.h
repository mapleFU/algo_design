//
// Created by 付旭炜 on 2017/10/11.
//

#ifndef SEQUENCE_MYARRAY_H
#define SEQUENCE_MYARRAY_H

#include "Sequence.h"

/*
 * 定长数组
 */
template <typename Type>
class MyArray: public Sequence<Type> {
private:
    Type* _array;
public:
    explicit MyArray(size_type length): Sequence<Type>(length)  { _array = new Type[Sequence<Type>::_size]; }
    Type&operator[](size_type index) override final { return _array[index];}
//    const Type&operator[](size_type index) override final { return _array[index];}
    ~MyArray() {delete [] _array;}
};


#endif //SEQUENCE_MYARRAY_H
