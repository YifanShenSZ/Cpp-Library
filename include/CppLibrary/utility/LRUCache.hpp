#ifndef CL_utility_LRUCache_hpp
#define CL_utility_LRUCache_hpp

#include <cstdint>
#include <list>
#include <unordered_map>
#include <stdexcept>

namespace CL { namespace utility {

// least recently used cache
template <typename Tkey, typename Tval> class LRUCache {
    private:
        size_t capacity_ = 100;
        // cache from new to old
        std::list<std::pair<Tkey, Tval>> cache_;
        // a hash map from key to list node
        std::unordered_map<Tkey, typename std::list<std::pair<Tkey, Tval>>::iterator> key2node_;
    public:
        LRUCache() {}
        LRUCache(const size_t & _capacity) : capacity_(_capacity) {}
        ~LRUCache() {}

        const Tval & get(const Tkey & key) {
            if (key2node_.count(key) == 0) throw std::out_of_range("CL::utility::LRUCache::get: key does not exist");
            auto node = key2node_[key];
            // transfer to latest
            cache_.splice(cache_.begin(), cache_, node);
            return node->second;
        }

        void put(const Tkey & key, const Tval & val) {
            // change value
            if (key2node_.count(key) > 0) {
                auto node = key2node_[key];
                node->second = val;
                // transfer to latest
                cache_.splice(cache_.begin(), cache_, node);
            }
            // insert (key, value)
            else {
                cache_.push_front({key, val});
                key2node_[key] = cache_.begin();
                // remove earliest
                if (cache_.size() > capacity_) {
                    key2node_.erase(cache_.back().first);
                    cache_.pop_back();
                }
            }
        }
};

} // namespace utility
} // namespace CL

#endif