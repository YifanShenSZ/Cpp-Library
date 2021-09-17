#include <iostream>
#include <unordered_set>
#include <numeric>

#include <CppLibrary/utility/heap.hpp>

// Given `n` nodes and edges in `edges` as (node1, node2, distance),
// return the shortest pathes from node 0 to others
std::vector<int> dijkstra(const int & n, const std::vector<std::vector<int>> & edges) {
    // reshape `edges` into an adjacency list for easier look up
    std::vector<std::vector<std::pair<int, int>>> adj_list(n);
    for (const auto & edge : edges) {
        adj_list[edge[0]].push_back({edge[1], edge[2]});
        // the graph is undirected, so double the edges to convert it to directed
        adj_list[edge[1]].push_back({edge[0], edge[2]});
    }
    // use a heap to keep track on possible distance
    // (key, value) = (possible distance, node)
    CL::utility::Heap<int, int> heap;
    heap.push({0, 0});
    for (int i = 1; i < n; i++) heap.push({1000000 + i, i});
    // keep the shortest distance to each node in a vector
    std::vector<int> results(n);
    results[0] = 0;
    for (int i = 1; i < n; i++) {
        results[i] = 1000000 + i;
    }
    // Dijkstra loop
    while (heap.size() > 0) {
        int distance, node;
        std::tie(distance, node) = heap.pop();
        results[node] = distance;
        for (const auto & edge : adj_list[node]) {
            int new_distance = distance + edge.second;
            if (new_distance < results[edge.first]) {
                heap.decrease_key(results[edge.first], new_distance);
                results[edge.first] = new_distance;
            }
        }
    }
    return results;
}

int main() {
    std::vector<int> case1 = dijkstra(3, {{0, 1, 10}, {0, 2, 1}, {1, 2, 2}});
    case1[1] -= 3;
    case1[2] -= 1;
    std::cerr << std::accumulate(case1.begin() + 1, case1.end(), 0) << '\n';

    std::vector<int> case2 = dijkstra(4, {{0, 1, 4}, {1, 2, 6}, {0, 2, 8}, {1, 3, 1}});
    case2[1] -= 4;
    case2[2] -= 8;
    case2[3] -= 5;
    std::cerr << std::accumulate(case2.begin() + 1, case2.end(), 0) << '\n';
}