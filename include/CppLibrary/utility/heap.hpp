#ifndef CL_utility_heap_hpp
#define CL_utility_heap_hpp

#include <stdint.h>
#include <vector>
#include <unordered_map>

namespace CL { namespace utility {

// Standard library only offers priority queue, i.e. no support for `decrease_key`
// Here we provide a min heap with `peek`, `push`, `pop`, `decrease_key`
template <typename Tkey, typename Tval> class Heap {
    private:
        // Since a heap is a complete binary tree, we store the nodes in a vector, just like the standard library
        std::vector<std::pair<Tkey, Tval>> heap_vec_;
        // a hash map from key to node: we need it for `decrease_key`
        std::unordered_map<Tkey, size_t> key2node_;

        // parent, left child, right child of node index
        inline size_t parent_(const size_t & index) const {return (index - 1) / 2;}
        inline size_t left_  (const size_t & index) const {return (2 * index + 1);}
        inline size_t right_ (const size_t & index) const {return (2 * index + 2);}

        // swim up
        inline void swim_up_(const size_t & start_index) {
            size_t index = start_index;
            while (true) {
                if (index == 0) break; // has swum up to root
                size_t parent = parent_(index);
                Tkey this_key = heap_vec_[index ].first,
                   parent_key = heap_vec_[parent].first;
                if (parent_key < this_key) break; // reach smaller parent, done
                std::swap(heap_vec_[index], heap_vec_[parent]);
                key2node_[  this_key] = parent;
                key2node_[parent_key] = index;
                index = parent;
            }
        }

        // A recursive method to heapify a subtree with the root at given node
        // This method assumes that the subtrees are already heapified
        void heapify_(const size_t & index) {
            size_t l = left_ (index),
                   r = right_(index),
                   heap_size = heap_vec_.size(),
                   min = index;
            if (l < heap_size && heap_vec_[l].first < heap_vec_[index].first) min = l;
            if (r < heap_size && heap_vec_[r].first < heap_vec_[min  ].first) min = r;
            if (min != index) {
                Tkey this_key = heap_vec_[index].first,
                      min_key = heap_vec_[min  ].first;
                std::swap(heap_vec_[index], heap_vec_[min]);
                key2node_[this_key] = min  ;
                key2node_[ min_key] = index;
                heapify_(min);
            }
        }
    public:
        Heap() {}
        ~Heap() {}

        const std::pair<Tkey, Tval> & peek() const {return heap_vec_[0];}

        void push(const std::pair<Tkey, Tval> & key_val) {
            // insert the new key at the end
            heap_vec_.push_back(key_val);
            size_t index = heap_vec_.size() - 1;
            key2node_[key_val.first] = index;
            // swim up
            swim_up_(index);
        }

        std::pair<Tkey, Tval> pop() {
            // store the minimum value for later return
            std::pair<Tkey, Tval> result = heap_vec_[0];
            // remove it
            // simpler when there is only 1 element left
            if (heap_vec_.size() == 1) {
                key2node_.erase(heap_vec_[0].first);
                heap_vec_.pop_back();
            }
            // normal case
            else {
                key2node_.erase(heap_vec_[0].first);
                // move the last node to root, then heapify
                heap_vec_[0] = heap_vec_.back();
                key2node_[heap_vec_[0].first] = 0;
                heap_vec_.pop_back();
                heapify_(0);
            }
            return result;
        }

        void decrease_key(const Tkey & old_key, const Tkey & new_key) {
            if (new_key > old_key) throw std::invalid_argument("Heap::decrease_key: new key must be smaller");
            if (new_key == old_key) return; // no change, quick return
            // decrease key
            size_t index = key2node_[old_key];
            heap_vec_[index].first = new_key;
            key2node_.erase(old_key);
            key2node_[new_key] = index;
            // swim up
            swim_up_(index);
        }

        size_t size() const {return heap_vec_.size();}
};

} // namespace utility
} // namespace CL

#endif