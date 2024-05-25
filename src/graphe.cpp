#include "graphe.hpp"
#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <stack>
#include <queue>



namespace Graph {
    
    struct WeightedGraphEdge {
        std::pair<int,int> to {};
        float weight {1.0f};

        // default ici permet de définit les opérateurs de comparaison membres à membres automatiquement
        // Cela ne fonction qu'en C++20, si vous n'avez pas accès à cette version je vous donne les implémentations des opérateurs plus bas
        bool operator==(WeightedGraphEdge const& other) const = default;
        bool operator!=(WeightedGraphEdge const& other) const = default;
    };

    struct WeightedGraph {
        // L'utilisation d'un tableau associatif permet d'avoir une complexité en O(1) pour l'ajout et la recherche d'un sommet.
        // Cela permet de stocker les sommets dans un ordre quelconque (et pas avoir la contrainte d'avoir des identifiants (entiers) de sommets consécutifs lors de l'ajout de sommets).
        // Cela permet également de pouvoir utiliser des identifiants de sommets de n'importe quel type (string, char, int, ...) et pas seulement des entiers.
        std::unordered_map<std::pair<int,int>, std::vector<WeightedGraphEdge>> adjacency_list {};
        

        // E1 Q1 ///////////
        
        void add_vertex(std::pair<int,int> const id)
        {
            std::unordered_map<std::pair<int,int>, std::vector<WeightedGraphEdge>>::const_iterator got = adjacency_list.find (id);
            if (got == adjacency_list.end() )
                {
                    adjacency_list[id];
                }
            
        }
        ////////////////////////

         // E1 Q2 ///////////
        void add_directed_edge(std::pair<int,int> const from, std::pair<int,int> const to)
        {   std::unordered_map<std::pair<int,int>, std::vector<WeightedGraphEdge>>::const_iterator chercherto = adjacency_list.find (to);
            add_vertex(to);
            WeightedGraphEdge destinationetpoids = {to,(to.first - from.first) + (to.second - from.second) };
            adjacency_list[from].push_back(destinationetpoids); 
        }
        ///////////////////////////
        

        // Même fonctionnement que pour WeightedGraphEdge
        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;

        std::unordered_map<std::pair<int,int>, std::pair<float, std::pair<int,int>>> dijkstra(Graph::WeightedGraph const& graph, std::pair<int,int> const& start, std::pair<int,int> const& end) {
    std::unordered_map<std::pair<int,int>, std::pair<float, std::pair<int,int>>> distances {};
    std::priority_queue<std::pair<float, std::pair<int,int>>, std::vector<std::pair<float, std::pair<int,int>>>, std::greater<std::pair<float, std::pair<int,int>>>> aVisiter {};

    // 1. On ajoute le sommet de départ à la liste des sommets à visiter avec une distance de 0 (on est déjà sur le sommet de départ)
    aVisiter.push({0.0f, start});
    distances[start] = {0.0f, start};

    // Tant qu'il reste des sommets à visiter
    while (!aVisiter.empty()) {
        // 2. On récupère le sommet le plus proche du sommet de départ dans la liste de priorité to_visit
        auto [current_distance, current_node] = aVisiter.top();
        aVisiter.pop();

        // 3. Si on atteint le point d'arrivée, on s'arrête
        if (current_node == end) {
            return distances;
        }

        // 3. On parcoure la liste des voisins (grâce à la liste d'adjacence) du nœud courant
        for (auto const& edge : graph.adjacency_list.at(current_node)) {
            // 4. on regarde si le nœud existe dans le tableau associatif (si oui il a déjà été visité)
            auto find_node = distances.find(edge.to);
            bool const visite = find_node != distances.end();

            if (!visite) {
                // 5. Si le nœud n'a pas été visité, on l'ajoute au tableau associatif en calculant la distance pour aller jusqu'à ce nœud
                // la distance actuelle + le poids de l'arête
                float new_distance = current_distance + edge.weight;
                distances[edge.to] = {new_distance, current_node};

                // 6. On ajout également le nœud de destination à la liste des nœud à visité (avec la distance également pour prioriser les nœuds les plus proches)
                aVisiter.push({new_distance, edge.to});
            } else {
                // 7. Si il a déjà été visité, On test si la distance dans le tableau associatif est plus grande
                // Si c'est le cas on a trouvé un plus court chemin, on met à jour le tableau associatif et on ajoute de nouveau le sommet de destination dans la liste à visité
                float old_distance = find_node->second.first;
                float new_distance = current_distance + edge.weight;
                if (new_distance < old_distance) {
                    distances[edge.to] = {new_distance, current_node};
                    aVisiter.push({new_distance, edge.to});
                }
            }
        }
    }

    return distances;
}


    };

    ////////////////////////////////

} 
