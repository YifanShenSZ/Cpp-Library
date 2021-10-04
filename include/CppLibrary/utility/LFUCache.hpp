#ifndef CL_utility_LFUCache_hpp
#define CL_utility_LFUCache_hpp

#include <cstdint>
#include <vector>
#include <list>
#include <unordered_map>
#include <stdexcept>

namespace CL { namespace utility {

// least frequently used cache
template <typename Tkey, typename Tval> class LFUCache {
    private:
        size_t capacity_ = 100, size_ = 0;
        // a vector of caches with different frequency (frequency = index + 1)
        // one cache itself is from new to old
        std::vector<std::list<std::pair<Tkey, Tval>>> caches_;
        // a hash map from key to list node and frequency
        std::unordered_map<Tkey, std::pair<typename std::list<std::pair<Tkey, Tval>>::iterator, size_t>> key2nodefreq_;
    public:
        LFUCache() {}
        LFUCache(const size_t & _capacity) : capacity_(_capacity) {caches_.resize(_capacity);}
        ~LFUCache() {}

        const Tval & get(const Tkey & key) {
            if (key2nodefreq_.count(key) == 0) throw std::out_of_range("CL::utility::LFUCache::get: key does not exist");
            auto & node_freq = key2nodefreq_[key];
            auto & node = node_freq.first;
            size_t & freq = node_freq.second;
            // transfer to latest
            // already highest frequency
            if (freq == capacity_) {
                auto & cache = caches_.back();
                cache.splice(cache.begin(), cache, node);
                node = cache.begin();
            }
            // frequency++
            else {
                auto & cache = caches_[freq];
                cache.splice(cache.begin(), caches_[freq - 1], node);
                node = cache.begin();
                freq++;
            }
            return node->second;
        }

        void put(const Tkey & key, const Tval & val) {
            // change value
            if (key2nodefreq_.count(key) > 0) {
                auto & node_freq = key2nodefreq_[key];
                auto & node = node_freq.first;
                size_t & freq = node_freq.second;
                node->second = val;
                // transfer to latest
                // already highest frequency
                if (freq == capacity_) {
                    auto & cache = caches_.back();
                    cache.splice(cache.begin(), cache, node);
                    node = cache.begin();
                }
                // frequency++
                else {
                    auto & cache = caches_[freq];
                    cache.splice(cache.begin(), caches_[freq - 1], node);
                    node = cache.begin();
                    freq++;
                }
            }
            // insert (key, value)
            else {
                caches_[0].push_front({key, val});
                key2nodefreq_[key] = {caches_[0].begin(), 1};
                // remove earliest
                if (size_ == capacity_) {
                    // there exists other frequency-1 old node
                    if (caches_[0].size() > 1) {
                        auto & cache = caches_[0];
                        key2nodefreq_.erase(cache.back().first);
                        cache.pop_back();
                    }
                    // try popping from frequency-2
                    else for (size_t i = 1; i < capacity_; i++) {
                        auto & cache = caches_[i];
                        if (! cache.empty()) {
                            key2nodefreq_.erase(cache.back().first);
                            cache.pop_back();
                            break;
                        }
                    }
                }
                // there is one more element in cache now
                else size_++;
            }
        }
};

} // namespace utility
} // namespace CL

#endif