#include "graphe.hpp"
#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <stack>
#include <queue>


int main () {
    Graph::WeightedGraph graph2;
    
    graph2.add_vertex({0,0});
    graph2.add_vertex({0,2});
    graph2.add_vertex({2,2});
    graph2.add_vertex({2,3});
    graph2.add_vertex({4,3});
    
    graph2.add_directed_edge({0,0},{0,2});
    graph2.add_directed_edge({0,2}, {2,2});
    graph2.add_directed_edge({2,2}, {2,3});
    graph2.add_directed_edge({2,3}, {2,3});

}