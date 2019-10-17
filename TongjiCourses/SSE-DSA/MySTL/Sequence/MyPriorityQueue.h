//
// Created by 付旭炜 on 2017/10/19.
//

#ifndef SEQUENCE_MYPRIORITYQUEUE_H
#define SEQUENCE_MYPRIORITYQUEUE_H

#include "Queue.h"
#include "MyVector.h"

#include <functional>
/*
 * priority_queue using < to compare
 */

#define PQ_DEBUG
#undef PQ_DEBUG

template <typename Type, typename Comparer = std::less<Type>>
class MyPriorityQueue: public Queue<Type> {
public:
    Type pop() override ;
    void push(const Type& value) override ;
    Type& front() override ;
    size_type size() override ;

#ifdef PQ_DEBUG
    void show_pq() {
        for (int i = 0; i < _elements.size(); ++i) {
            std::cout << _elements[i] << ' ';
        }
        std::cout << '\n';
    }
#endif

private:
    MyVector<Type> _elements;
    inline size_type to_element_index(const size_type origin) {
        if (origin == 0) {
            std::cerr << "Invaild index\n";
            exit(-1);
        }
        return origin - 1;
    }
    Comparer comparer = Comparer();
};


template <typename Type, typename Comparer>
Type MyPriorityQueue<Type, Comparer>::pop() {
#ifdef PQ_DEBUG
    std::cout << "Before pop\n";
    show_pq();
#endif
    size_type next_size = size() - 1;
    std::swap(_elements[0], _elements[next_size]);
    const Type end = _elements.back();

    // 下滤
    for (size_type i = 1; i <= next_size / 2; i *= 2) {
        size_type next_pos;
        if (i * 2 + 1 > next_size) {
            // ONLY ONE
            next_pos = i * 2;
        } else {
            if (comparer(_elements[to_element_index(i * 2)], _elements[to_element_index(i * 2 + 1)]))
                next_pos = i * 2;
            else
                next_pos = i * 2 + 1;
        }

        if (!comparer(_elements[to_element_index(i)], _elements[to_element_index(next_pos)])) {
            std::swap(_elements[to_element_index(i)], _elements[to_element_index(next_pos)]);
        } else {
            break;
        }
    }
    _elements.pop_back();
#ifdef PQ_DEBUG
    std::cout << "After pop\n";
    show_pq();
#endif
    return end;
}

template <typename Type, typename Comparer>
Type &MyPriorityQueue<Type, Comparer>::front() {
    return _elements[0];
}

template <typename Type, typename Comparer>
size_type MyPriorityQueue<Type, Comparer>::size() {
    return _elements.size();
}

template <typename Type, typename Comparer>
void MyPriorityQueue<Type, Comparer>::push(const Type &value) {
    _elements.push_back(value);
    size_type push_heap_index = _elements.size();

    for (size_type i = push_heap_index; i > 1; i /= 2) {
        size_type real_i = to_element_index(i);
        size_type real_half_i = to_element_index(i / 2);

        if (comparer(_elements[real_i], _elements[real_half_i])) {
            std::swap(_elements[real_i], _elements[real_half_i]);
        } else {
            break;
        }
    }
#ifdef PQ_DEBUG
//    std::cout << "After input: ";
//    show_pq();
#endif
}


#endif //SEQUENCE_MYPRIORITYQUEUE_H
