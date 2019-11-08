//
// Created by 付旭炜 on 2019/11/8.
//

#include <list>
#include <unordered_map>
#include <utility>

class LRUCache {
private:
    std::list<std::pair<int, int>> container_;
    int capacity_;

    auto find_iter(int key) const {
        return std::find_if(container_.begin(), container_.end(), [=](const std::pair<int, int>& kv_pair) {
            return kv_pair.first == key;
        });
    }

    bool full() const {
        return capacity_ == container_.size();
    }

    void evict() {
        container_.pop_back();
    }
public:
    LRUCache(int capacity): capacity_(capacity) {}

    int get(int key) {
        int to_return { -1 };
        auto iter = find_iter(key);
        if (container_.end() != iter) {
            to_return = iter->second;
            std::pair<int, int> kv_pair = *iter;
            container_.erase(iter);
            container_.push_front(kv_pair);
        }
        return to_return;
    }

    void put(int key, int value) {
        auto iter = find_iter(key);
        if (container_.end() != iter) {
            container_.erase(iter);
        }
        if (this->full()) this->evict();
        container_.push_front(std::make_pair(key, value));
    }
};

class LRUCacheMap {
    using container_type = std::list<std::pair<int, int>>;
    using container_iter_type = typename std::list<std::pair<int, int>>::iterator;
    using container_const_iter_type = typename std::list<std::pair<int, int>>::const_iterator;

    const int capacity_;
    // list kv pair
    container_type container_;
    std::unordered_map<int, container_iter_type> container_mapper_;

    void add_front_kv(int key, int value) {
        this->container_.push_front(std::make_pair(key, value));
        this->container_mapper_[key] = this->container_.begin();
    }

    void evict() {
        auto back_val = this->container_.back();
        container_mapper_.erase(back_val.first);
        this->container_.pop_back();
    }
public:
    LRUCacheMap(int capacity): capacity_(capacity) {}

    int get(int key) {
        auto const c_iter = container_mapper_.find(key);
        if (c_iter == container_mapper_.cend()) {
            return -1;
        } else {
            int val = c_iter->second->second;
            auto kv_pair = *c_iter->second;

            this->container_.erase(c_iter->second);
            add_front_kv(key, kv_pair.second);
            return val;
        }
    }

    void put(int key, int value) {
        auto iter = container_mapper_.find(key);
        if (iter == container_mapper_.cend()) {
            if (container_.size() == capacity_) {
                evict();
            }
            add_front_kv(key, value);
        } else {
            this->container_.erase(iter->second);
            add_front_kv(key, value);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
#include <iostream>

template <typename Cacher>
void testing_cacher() {
    using namespace std;
    {
        Cacher cache = Cacher(2 /* capacity */);

        cache.put(1, 1);
        cache.put(2, 2);
        cout << cache.get(1) << '\n'; // returns 1
        cache.put(3, 3);              // evicts key 2
        cout << cache.get(2) << '\n'; // returns -1 (not found)
        cache.put(4, 4);              // evicts key 1
        cout << cache.get(1) << '\n'; // returns -1 (not found)
        cout << cache.get(3) << '\n'; // returns 3
        cout << cache.get(4) << '\n'; // returns 4
    }

    auto print_digit = [](const int& v ) {
        cout << v << endl;
    };
    /**
     * ["LRUCache","put","put","put","put","get","get"]
     * [[2],[2,1],[1,1],[2,3],[4,1],[1],[2]]
     */
    {
        Cacher cache = Cacher(2 /* capacity */);
        print_digit(cache.get(2));
        cache.put(2, 1);     // (2, 1)
        cache.put(1, 1);     // (1, 1) -> (2, 1)
        cache.put(2, 3);     // (2, 3) -> (1, 1)
        cache.put(4, 1);     // (4, 1) -> (2, 3)
        print_digit(cache.get(1));  // -1
        print_digit(cache.get(2));
    }
}

int main() {
    testing_cacher<LRUCacheMap>();
}