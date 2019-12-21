//
// Created by 付旭炜 on 2019/12/21.
//

#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H

#include <chrono>
#include <future>
#include <mutex>
#include <thread>
#include <type_traits>
#include <unordered_map>

template <typename Src, typename Target> class Compute {
  public:
    static Target compute(const Src &src) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return Target();
    }
};

template <> class Compute<int, int> {
  public:
    static int compute(const int &src) {
        int ret = src * src;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return ret;
    }
};

template <typename Src, typename Target, typename ComputeFnType>
class cache1 final {
  public:
    explicit cache1(
        std::decay_t<decltype(ComputeFnType::compute)> * = nullptr) {}

    // an naive lock, it doesn't make full use of concurrency.
    Target compute(const Src &src) {
        cache_lock _l(lock_);
        if (cache_.contains(src)) {
            return cache_[src];
        }
        auto res = ComputeFnType::compute(src);
        cache_[src] = res;
        return res;
    }

  private:
    using cache_lock = std::lock_guard<std::mutex>;

    std::unordered_map<Src, Target> cache_;
    std::mutex lock_;
};

template <typename Src, typename Target, typename ComputeFnType>
class cache2 final {
  public:
    explicit cache2(
        std::decay_t<decltype(ComputeFnType::compute)> * = nullptr) {}

    // an naive lock, it doesn't make full use of concurrency.
    Target compute(const Src &src) {
        {
            cache_lock _l(cache_map_lock_);
            if (cache_.contains(src)) {
                return src;
            }
        }
        Target dest = ComputeFnType::compute(src);
        { cache_[src] = dest; }
        return dest;
    }

  private:
    using cache_lock = std::lock_guard<std::mutex>;

    std::unordered_map<Src, Target> cache_;
    std::mutex cache_map_lock_;
};

template <typename Src, typename Target, typename ComputeFnType>
class cache3 final {
  public:
    explicit cache3(
        std::decay_t<decltype(ComputeFnType::compute)> * = nullptr) {}

    // an naive lock, it doesn't make full use of concurrency.
    Target compute(const Src &src) {
        std::future<Target> target_fut;
        {
            cache_lock _l(cache_lock_);
            if (!cache_.contains(src)) {
                auto fut = std::async(ComputeFnType::compute, std::ref(src));
                cache_[src] = fut;
                target_fut = fut;
            } else {
                target_fut = cache_[src];
            }
        }

        return target_fut.get();
    }

  private:
    using cache_lock = std::lock_guard<std::mutex>;

    std::mutex cache_lock_;
    std::unordered_map<Src, std::future<Target>> cache_;
};

template <typename Src, typename Target, typename ComputeFnType>
using cache = cache3<Src, Target, ComputeFnType>;
// cache1<int, int, Compute<int, int>>;
// cache2<int, int, Compute<int, int>>;

#endif // CACHE_CACHE_H
