#ifndef CL_utility_UnionFind_hpp
#define CL_utility_UnionFind_hpp

#include <unordered_map>

namespace CL { namespace utility {

// Tree node for UnionFind
template <typename Tkey, typename Tval> struct UFTreeNode {
    Tval val = 0;
    size_t rank = 0;
    UFTreeNode<Tkey, Tval> * parent = nullptr;

    UFTreeNode() {}
    UFTreeNode(const Tval & _val) : val(_val) {}
    ~UFTreeNode() {}
};

// A tree-based union find
// A set is a tree and represented by its root
template <typename Tkey, typename Tval> class UnionFind {
    private:
        // a hash map from key to node
        std::unordered_map<Tkey, UFTreeNode<Tkey, Tval> *> key2node_;
    public:
        UnionFind() {}
        ~UnionFind() {}

        void make_set(const Tkey & key) {
            if (key2node_.count(key) == 0) key2node_[key] = new UFTreeNode<Tkey, Tval>;
        }

        UFTreeNode<Tkey, Tval> * find(const Tkey & key) {
            if (key2node_.count(key) == 0) return nullptr;
            // find root
            UFTreeNode<Tkey, Tval> * root = key2node_[key];
            while (root->parent) root = root->parent;
            // path compression
            UFTreeNode<Tkey, Tval> * current = key2node_[key];
            while (current->parent) {
                UFTreeNode<Tkey, Tval> * save_current = current;
                current = current->parent;
                save_current->parent = root;
            }
            // return
            return root;
        }

        void union_roots(UFTreeNode<Tkey, Tval> * root1, UFTreeNode<Tkey, Tval> * root2) {
            if (root1 != root2) {
                // union by rank
                if (root1->rank > root2->rank) {
                    root2->parent = root1;
                }
                else if (root2->rank > root1->rank) {
                    root1->parent = root2;
                }
                else {
                    root2->parent = root1;
                    root1->rank++;
                }
            }
        }

        void union_keys(const Tkey & key1, const Tkey & key2) {
            UFTreeNode<Tkey, Tval> * root1 = this->find(key1),
                                   * root2 = this->find(key2);
            this->union_roots(root1, root2);
        }
};

} // namespace utility
} // namespace CL

#endif