#include "graphe.hpp"
#include "ValiditeITD.hpp"
#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <stack>
#include <queue>
#include <sstream>
#include <cmath>
#include <stdexcept>



Graph::Node Graph::WeightedGraph::getNodePosition(int nodeId) {
    return adjacency_list[nodeId];
}

void Graph::WeightedGraph::addNode(int const id, int x, int y)
{
    if (adjacency_list.find(id) != adjacency_list.end()) {
        throw std::runtime_error("Le noeud que tu veux ajouter existe déjà.");
    }

    Node node;
    node.id = id;
    node.x = x;
    node.y = y;

    adjacency_list[id] = node;
    // std::cout << "Noeud ajouté: ID = " << id << ", x = " << x << ", y = " << y << std::endl; // Debug print
}

void Graph::WeightedGraph::addEdge(int from, int to, float weight)
{
    if (adjacency_list.find(from) == adjacency_list.end()) {
        throw std::runtime_error("Le noeud de départ n'existe pas.");
    }
    if (adjacency_list.find(to) == adjacency_list.end()) {
        throw std::runtime_error("Le noeud de destination n'existe pas.");
    }

    adjacency_list[from].edges.push_back({to, weight});
    // std::cout << "Arête ajoutée: de " << from << " à " << to << ", poids = " << weight << std::endl; // Debug print
}

std::string Graph::WeightedGraph::premierMotDeLaligne(const std::string& ligne) {
    std::istringstream stream(ligne);
    std::string mot;
    stream >> mot;
    return mot;
}

std::vector<std::string> Graph::WeightedGraph::split_string(const std::string& str) {
    std::istringstream stream(str);
    std::string mot;
    std::vector<std::string> mots;

    while (stream >> mot) {
        mots.push_back(mot);
    }

    return mots;
}

void Graph::WeightedGraph::creerNoeudEtArreteGrapheAPartirDeItd(std::ifstream& fichier)
{
    if (!fichier.is_open()) {
        throw std::runtime_error("Je n'arrive pas à ouvrir le fichier.");
    }

    std::string contenuLigne;
    while (std::getline(fichier, contenuLigne)) {
        std::string PremierMotaComparer = premierMotDeLaligne(contenuLigne);
        // std::cout << "Premier mot : " << PremierMotaComparer << std::endl;  // Debug print

        if (PremierMotaComparer == "#" || contenuLigne.empty()) {
            continue; // Ignorer les commentaires et les lignes vides
        }

        if (PremierMotaComparer == "node") {
            std::vector<std::string> DecoupageMot = split_string(contenuLigne);
            int const id = std::stoi(DecoupageMot[1]);
            int x = std::stoi(DecoupageMot[2]);
            int y = std::stoi(DecoupageMot[3]);

            addNode(id, x, y);
        }
    }

    // Réinitialiser le curseur du fichier au début
    fichier.clear();
    fichier.seekg(0, std::ios::beg);

    while (std::getline(fichier, contenuLigne)) {
        std::string PremierMotaComparer = premierMotDeLaligne(contenuLigne);
        // std::cout << "Premier mot : " << PremierMotaComparer << std::endl;  // Debug print

        if (PremierMotaComparer == "#" || contenuLigne.empty()) {
            continue; // Ignorer les commentaires et les lignes vides
        }

        if (PremierMotaComparer == "node") {
            std::vector<std::string> DecoupageMot = split_string(contenuLigne);
            int const from = std::stoi(DecoupageMot[1]);
            // std::cout << "From node: " << from << std::endl;  // Debug print

            if (DecoupageMot.size() > 4) { // Vérifiez s'il y a des sommets adjacents
                for (size_t i = 4; i < DecoupageMot.size(); ++i) {
                    int to = std::stoi(DecoupageMot[i]);
                    float poids = calculerPoids(from, to);
                    addEdge(from, to, poids);
                }
            }
        }
    }
}

float Graph::WeightedGraph::calculerPoids(int from, int to) {
    Node& NodeFrom = adjacency_list[from];
    Node& NodeTo = adjacency_list[to];

    return std::sqrt(std::pow(NodeTo.x - NodeFrom.x, 2) + std::pow(NodeTo.y - NodeFrom.y, 2));
}

void Graph::WeightedGraph::printGraph() {
    for (const auto& pair : adjacency_list) {
        const Node& node = pair.second;
        // std::cout << "Noeud d'indice : " << node.id << ", Position: (" << node.x << ", " << node.y << ")";
        for (const auto& edge : node.edges) {
            // std::cout << " arrete vers le sommet " << edge.to << ", de poids : " << edge.weight << "\n";
        }
    }
}


std::vector<int> Graph::WeightedGraph::dijkstra(int start, int goal) {
    std::unordered_map<int, float> distances;
    std::unordered_map<int, int> previous;
    auto cmp = [&distances](int left, int right) { return distances[left] > distances[right]; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> nodes_to_visit(cmp);

    for (const auto& pair : adjacency_list) {
        distances[pair.first] = std::numeric_limits<float>::infinity();
        previous[pair.first] = -1;
    }

    distances[start] = 0;
    nodes_to_visit.push(start);

    while (!nodes_to_visit.empty()) {
        int current = nodes_to_visit.top();
        nodes_to_visit.pop();

        if (current == goal) {
            break;
        }

        for (const auto& edge : adjacency_list[current].edges) {
            float new_dist = distances[current] + edge.weight;
            if (new_dist < distances[edge.to]) {
                distances[edge.to] = new_dist;
                previous[edge.to] = current;
                nodes_to_visit.push(edge.to);
            }
        }
    }

    std::vector<int> path;
    for (int at = goal; at != -1; at = previous[at]) {
        path.push_back(at);
    }

    std::reverse(path.begin(), path.end());

    if (path[0] == start) {
        return path;
    } else {
        return {}; 
    }
}

bool Graph::Node::operator==(const Node& other) const {
    return x == other.x && y == other.y;
}