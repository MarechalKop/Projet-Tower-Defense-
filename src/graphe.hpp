#pragma once
#include <vector>
#include <unordered_map>
#include <utility>

namespace Graph {
    struct WeightedGraphEdge {
        std::pair<int,int> to {};
        float weight {1.0f};
        bool operator==(WeightedGraphEdge const& other) const = default;
        bool operator!=(WeightedGraphEdge const& other) const = default;
    };

    struct WeightedGraph {
        std::unordered_map<std::pair<int,int>, std::vector<WeightedGraphEdge>> adjacency_list {};
        void add_vertex(std::pair<int,int> const id);
        void add_directed_edge(std::pair<int,int> const from, std::pair<int,int> const to);
        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;
        std::unordered_map<std::pair<int,int>, std::pair<float, std::pair<int,int>>> dijkstra(std::pair<int,int> const& start, std::pair<int,int> const& end);
    };
}
