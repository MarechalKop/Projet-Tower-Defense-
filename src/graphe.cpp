#include "graphe.hpp"
#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <stack>
#include <queue>


        void Graph::WeightedGraph::add_vertex(int const id)
        {
            std::unordered_map<int, std::vector<WeightedGraphEdge>>::const_iterator got = adjacency_list.find (id);
            if (got == adjacency_list.end() )
                {
                    adjacency_list[id];
                }
            else {
                throw std::runtime_error("Le noeud que tu veux ajouter existe déjà LOL");
            }
            
        }
       

 
        void Graph::WeightedGraph::add_directed_edge(int const from, int const to, int const poids)
        {   std::unordered_map<int, std::vector<WeightedGraphEdge>>::const_iterator chercherTo = adjacency_list.find (to);
        std::unordered_map<int, std::vector<WeightedGraphEdge>>::const_iterator chercherFrom = adjacency_list.find (from);
            if (chercherTo == adjacency_list.end()) {
                  add_vertex(to);
            }
            else if (chercherFrom == adjacency_list.end()) {
                  add_vertex(from);
            }
            WeightedGraphEdge destinationetpoids = {to,poids};
            adjacency_list[from].push_back(destinationetpoids); 
        };
 
        


std::unordered_map<int, std::pair<float, int>> Graph::WeightedGraph::dijkstra(Graph::WeightedGraph const& graph, int start, int end) {
    std::unordered_map<int, std::pair<float, int>> distances {};
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> aVisiter {};

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
};



    

