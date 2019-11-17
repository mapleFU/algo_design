#include "common_use.h"
#include <map>
#include <unordered_map>
#include <memory>
#include <cassert>

using namespace std;


struct TrieMap {
    bool occupancy { false };
    std::unordered_map<char, std::unique_ptr<TrieMap>> sub_map;
};


class Trie {
    std::unique_ptr<TrieMap> map_;
public:
    /** Initialize your data structure here. */
    Trie()
    : map_(std::make_unique<TrieMap>())
    {

    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieMap* current = map_.get();
        for(auto c: word) {
            auto next_map = current->sub_map.find(c);
            if (next_map == current->sub_map.cend()) {
                current->sub_map[c] = std::make_unique<TrieMap>();
                next_map = current->sub_map.find(c);
            }

            current = next_map->second.get();
        }
        current->occupancy = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieMap* current = map_.get();
        for(auto c: word) {
            auto next_map = current->sub_map.find(c);
            if (next_map == current->sub_map.cend()) {
                return false;
            }

            current = (*next_map).second.get();
        }

        return current->occupancy;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieMap* current = map_.get();
        for(auto c: prefix) {
            auto next_map = current->sub_map.find(c);
            if (next_map == current->sub_map.cend()) {
                return false;
            }

            current = (*next_map).second.get();
        }

        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main() {
    Trie trie;
    trie.insert("apple");
    cout << boolalpha << trie.search("apple") << '\n';   // returns true
    cout << boolalpha << trie.search("app") << '\n';     // returns false
    cout << boolalpha << trie.startsWith("app") << '\n'; // returns true
    trie.insert("app");
    cout << boolalpha << trie.search("app") << '\n';     // returns true
}