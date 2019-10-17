//
// Created by 付旭炜 on 2019/10/17.
//

#pragma "once"

#include <memory>

/// 1. 对象的构造设计内存处理和 `std::uninitialized_xxx`
/// 的处理，建议用一个资源管理类
/// 2. 对象赋值比之前的复杂
template <typename T, typename Alloc = std::allocator<T>> class MVector {
  public:
    using size_type = size_t;
    constexpr static size_type DEFAULT_INIT = 8;

    // constructor
    MVector(const MVector &);
    MVector &operator=(const MVector &);
    // default constructor
    explicit MVector(size_type t = DEFAULT_INIT, const Alloc &a = Alloc());
    explicit MVector(size_type t, const T &init_val, const Alloc &a = Alloc());
    // move constructor
    MVector(MVector &&) noexcept;
    MVector &operator=(MVector &&);

    ~MVector() {
        allocator.deallocate(elem, last - elem);
    };

    [[nodiscard]] size_type size() const { return space - elem; }
    [[nodiscard]] size_type capacity() const { return last - elem; }

    void reserve(size_type);
    void resize(size_type);

    void clear() { resize(0); }

    void push_back(const T &arg);

  private:
    // tcpppl 建议用一个 类专门来分配这个
    //    elem    space      last
    //    |       |          |

    Alloc allocator;
    // 分配空间的开始区域
    T *elem;
    // 分配空间的结束区域
    T *space;
    T *last;

    void destory_elements();
};

template <typename T, typename Alloc>
MVector<T, Alloc>::MVector(const MVector &a) {
    auto v = MVector(a.size(), a.allocator);
    std::uninitialized_copy(a.elem, a.space + 1, v.elem);
    destory_elements();

    std::swap(*this, v);
    return *this;
}

template <typename T, typename Alloc>
MVector<T, Alloc>::MVector(MVector &&a) noexcept
    : allocator(a.allocator), elem(a.elem), space(a.space), last(a.last) {
    a.elem = a.space = a.last = nullptr;
}

template <typename T, typename Alloc>
MVector<T, Alloc>::MVector(MVector::size_type t, const Alloc &a)
    : allocator(a), elem(a.allocate(t)), space(elem),
      last(elem + DEFAULT_INIT) {}

template <typename T, typename Alloc>
MVector<T, Alloc>::MVector(MVector::size_type t, const T &init_val,
                           const Alloc &a): allocator(a),
                                                 elem(a.allocate(t)),
                                                 space(elem),
                                                 last(elem + t) {
    // if we use an enternal class vector_base
    // allocator 能自动析构的时候处理异常
    // we will not use deallocate
    //    try {
    //        std::uninitialized_fill_n(elem, t, init_val);
    //    } catch (...) {
    //        allocator.deallocate(elem, t);
    //        // rethrow error
    //        throw;
    //    }
    std::uninitialized_fill_n(elem, t, init_val);
}

template <typename T, typename Alloc>
void MVector<T, Alloc>::destory_elements() {
    for (auto p = elem; p <= space; ++p) {
        // deallocate
        p->~T();
    }
    this->space = elem;
}

template <typename T, typename Alloc>
MVector<T, Alloc> &MVector<T, Alloc>::operator=(MVector &&a) {
    // 似乎可以构造临时对象来析构
    std::swap(*this, a);
    return *this;
}

template <typename T, typename Alloc>
MVector<T, Alloc> &MVector<T, Alloc>::operator=(const MVector &) {}

template<typename T, typename Alloc>
void MVector<T, Alloc>::reserve(MVector::size_type t) {
    if (capacity() > t)
        return;
    auto temp_v = MVector(t, this->allocator);
    // TODO: find the diff between `uninitialized_copy` and `uninitialized_move`
    std::uninitialized_move(elem, elem + size(), temp_v.elem);
    // set space
    this->space = size();
    // 让 temp_v 默认的析构
    std::swap(*this, temp_v);
}

template<typename T, typename Alloc>
void MVector<T, Alloc>::push_back(const T &arg) {
    if (capacity() == size()) {
        reserve(2 * capacity());
    }
    allocator.construct(this->elem + size(), arg);
    ++space;
}
