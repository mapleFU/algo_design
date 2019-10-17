//
// Created by 付旭炜 on 2017/10/11.
//

#ifndef SEQUENCE_SEQUENCE_H
#define SEQUENCE_SEQUENCE_H

using size_type = unsigned long long;

template <typename Type>
class Sequence {
protected:
    size_type _size;
public:
    Sequence() = default;
    explicit Sequence(size_type size): _size(size) {}
    virtual Type&operator[](size_type index) = 0;
//    virtual const Type&operator[](size_type index) = 0;
//    virtual explicit Sequence(size_type size) = 0;
    virtual ~Sequence() {}
    size_type size() { return _size;}
};


#endif //SEQUENCE_SEQUENCE_H
