#include <iostream>
#include <vector>

#include <CppLibrary/utility/UnionFind.hpp>

std::vector<int> findRedundantConnection(const std::vector<std::vector<int>> & edges) {
    CL::utility::UnionFind<int, int> node_collections;
    for (const auto & edge : edges) {
        node_collections.make_set(edge[0]);
        node_collections.make_set(edge[1]);
        CL::utility::UFTreeNode<int, int> * root0 = node_collections.find(edge[0]),
                                          * root1 = node_collections.find(edge[1]);
        if (root0 == root1) return edge;
        else node_collections.union_roots(root0, root1);
    }
    // dummy return
    return std::vector<int>({0, 1});
}

int main() {
    std::vector<int> case1 = findRedundantConnection({{1, 2}, {1, 3}, {2, 3}});
    std::cerr << case1[0] - 2 + case1[1] - 3 << '\n';

    std::vector<int> case2 = findRedundantConnection({{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}});
    std::cerr << case2[0] - 1 + case2[1] - 4 << '\n';
}