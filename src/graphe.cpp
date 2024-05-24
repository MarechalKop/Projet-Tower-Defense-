#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <stack>
#include <queue>



namespace Graph {
    struct WeightedGraphEdge {
        int to {};
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
        std::unordered_map<int, std::vector<WeightedGraphEdge>> adjacency_list {};

        // E1 Q1 ///////////
        
        void add_vertex(int const id)
        {
            std::unordered_map<int, std::vector<WeightedGraphEdge>>::const_iterator got = adjacency_list.find (id);
            if (got == adjacency_list.end() )
                {
                    adjacency_list[id];
                }
            
        }
        ////////////////////////

         // E1 Q2 ///////////
        void add_directed_edge(int const from, int const to, float const weight = 1.0f)
        {   std::unordered_map<int, std::vector<WeightedGraphEdge>>::const_iterator chercherto = adjacency_list.find (to);
            add_vertex(to);
            WeightedGraphEdge destinationetpoids = {to,weight};
            adjacency_list[from].push_back(destinationetpoids); 
        }
        ///////////////////////////
        
         // E1 Q3 ///////////
        void add_undirected_edge(int const from, int const to, float const weight = 1.0f)
        {
            add_directed_edge(from,to,weight);
            add_directed_edge(to,from,weight);
        }
        ///////////////////////////

        // Même fonctionnement que pour WeightedGraphEdge
        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;

        void print_DFS(int const start) const;
        void print_BFS(int const start) const;
    };

         // E1 Q4 ///////////
    WeightedGraph build_from_adjacency_matrix(std::vector<std::vector<float>> const& adjacency_matrix)
    {
        WeightedGraph nouveauGraph;
        for (int i {}; i < adjacency_matrix.size(); i++)
        {
            nouveauGraph.add_vertex(i);
            for (int a {}; a < adjacency_matrix[i].size(); a++)
            {
                if (adjacency_matrix[i][a] != 0)
                {
                    nouveauGraph.add_directed_edge(i,a,adjacency_matrix[i][a]);
                }
            }
        }

        return nouveauGraph;
    }
    ////////////////////////////////

} // namespace

// E2 Q1 ////////////////////////////
void print_DFS (int const id,  Graph::WeightedGraph graph)
{   

    std::stack<int> pile;
    std::vector<int> sommetsVisites;
    pile.push(id);
    
    
    while (pile.size() != 0) 
    {
        
        int sommetActuel = pile.top();
        pile.pop();

        if (std::find(sommetsVisites.begin(), sommetsVisites.end(), sommetActuel) == sommetsVisites.end())
        {
            std::cout << sommetActuel << " " << std::endl;
            sommetsVisites.push_back(sommetActuel);

            for (int i {}; i < graph.adjacency_list[sommetActuel].size(); i++)
        {
            if (std::find(sommetsVisites.begin(), sommetsVisites.end(), graph.adjacency_list[sommetActuel][i].to) == sommetsVisites.end())
            { 
                pile.push(graph.adjacency_list[sommetActuel][i].to);
                sommetsVisites.push_back(graph.adjacency_list[sommetActuel][i].to);
            }
            
        }
        }
  
    }

}
///////////////////////////////////

// E2 Q1 ////////////////////////////
void print_BFS (int const id,  Graph::WeightedGraph graph)
{   

    std::queue<int> file;
    std::vector<int> sommetsVisites;
    file.push(id);
    
    
    while (file.size() != 0) 
    {
        
        int sommetActuel = file.front();
        file.pop();

        if (std::find(sommetsVisites.begin(), sommetsVisites.end(), sommetActuel) == sommetsVisites.end())
        {
            std::cout << sommetActuel << " " << std::endl;
            sommetsVisites.push_back(sommetActuel);

            for (int i {}; i < graph.adjacency_list[sommetActuel].size(); i++)
        {
            if (std::find(sommetsVisites.begin(), sommetsVisites.end(), graph.adjacency_list[sommetActuel][i].to) == sommetsVisites.end())
            { 
                file.push(graph.adjacency_list[sommetActuel][i].to);
                sommetsVisites.push_back(graph.adjacency_list[sommetActuel][i].to);
            }
            
        }
        }

    }
}
//////////////////////////////////////////////

int main() {
     // E1 Q5 ///////////
    std::vector<std::vector<float>> matriceTest = {
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {0, 1, 1, 0}
    };

   
    Graph::WeightedGraph graph1 = Graph::build_from_adjacency_matrix(matriceTest);

   
    Graph::WeightedGraph graph2;
    for (int i = 0; i < 4; i++) {
        graph2.add_vertex(i);
    }
    graph2.add_undirected_edge(0, 1);
    graph2.add_undirected_edge(1, 2);
    graph2.add_undirected_edge(1, 3);
    graph2.add_undirected_edge(2, 3);

    
    if (graph1 == graph2) {
        std::cout << "WAAAAAAAAAAAAAAAAAAAAAAAAAH ce sont bien les memes" << std::endl;
    } else {
        std::cout << "Les deux graphes ne sont pas égaux et en plus tu es moche" << std::endl;
    }
    ////////////////////////////////////

    
}
