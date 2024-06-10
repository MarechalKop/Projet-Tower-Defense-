#pragma once
#include <vector>
#include <unordered_map>
#include <utility>
#include <string>

namespace Graph {

    struct WeightedGraphEdge {
        int to {-50};
        float weight {500000000};
        bool operator==(WeightedGraphEdge const& other) const = default;
        bool operator!=(WeightedGraphEdge const& other) const = default;
    };

    struct Node {
        int id {0};
        float x {0};
        float y {0};
        std::vector<WeightedGraphEdge> edges;
    };

    struct WeightedGraph {
        std::unordered_map<int, Node> adjacency_list {};
        void addNode(int const id, int x, int y);
        void addEdge(int from, int to, float weight);
        void creerNoeudEtArreteGrapheAPartirDeItd(std::ifstream& fichier);
        void printGraph();
        float calculerPoids(int from, int to);
        std::vector<int> dijkstra(int start, int goal);
        std::string premierMotDeLaligne(const std::string& ligne);
        std::vector<std::string> split_string(const std::string& str);
        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;
        Node getNodePosition(int nodeId); 
    };
}