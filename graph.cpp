//
// Created by Blake Gebhardt on 13.04.23.
//

#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <fstream>

class Graph {
public:
    Graph(int V, int E, const std::string &type, const std::string &dist)
            : V(V), E(E), type(type), dist(dist) {
        adj = new int *[V];
        for (int i = 0; i < V; ++i) {
            adj[i] = new int[V];
            std::fill_n(adj[i], V, -1);
        }
    }

    ~Graph() {
        for (int i = 0; i < V; ++i) {
            delete[] adj[i];
        }
        delete[] adj;
    }

    void generateGraph() {
        if (type == "COMPLETE") {
            generateCompleteGraph();
        } else if (type == "CYCLE") {
            generateCycleGraph();
        } else if (type == "RANDOM") {
            generateRandomGraph();
        }
    }

    void printAdjacencyList() {
        for (int i = 0; i < V; ++i) {
            std::cout << i << ": ";
            for (int j = 0; j < V; ++j) {
                if (adj[i][j] != -1) {
                    std::cout << adj[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    void visualizeGraph(const Graph& graph) {
        // Create a new DOT file for the graph
        std::string fileName =  graph.type + graph.dist;
        std::ofstream dotFile(fileName + ".dot");
        dotFile << "digraph {\n";

        // Add nodes to the DOT file
        for (int i = 0; i < graph.V; ++i) {
            dotFile << i << ";\n";
        }

        // Add edges to the DOT file
        for (int i = 0; i < graph.V; ++i) {
            for (int j = 0; j < graph.V; ++j) {
                if (graph.adj[i][j] != -1) {
                    dotFile << i << " -> " << j << ";\n";
                }
            }
        }

        // Close the DOT file
        dotFile << "}\n";
        dotFile.close();

        // Call Graphviz to render the graph
        std::string toRender = "dot -Tpng " + fileName + ".dot -o " + fileName + ".png";
        std::system(toRender.c_str());
    }








private:
    int V, E;
    std::string type, dist;
    int **adj;

    void generateCompleteGraph() {
        for (int i = 0; i < V; ++i) {
            for (int j = i + 1; j < V; ++j) {
                adj[i][j] = j;
                adj[j][i] = i;
            }
        }
    }

    void generateCycleGraph() {
        for (int i = 0; i < V; ++i) {
            adj[i][(i + 1) % V] = (i + 1) % V;
            adj[(i + 1) % V][i] = i;
        }
    }

    void generateRandomGraph() {
        std::srand(static_cast<unsigned>(std::time(0)));
        int edgesCreated = 0;
        int mean = V / 2;
        int sd = (V / 6) + 1;
        while (edgesCreated < E) {
            int u = getRandomVertex(mean, sd);
            int v = getRandomVertex(mean, sd);

            if (u != v && adj[u][v] == -1) {
                adj[u][v] = v;
                adj[v][u] = u;
                edgesCreated++;
            }
        }
    }

    int getRandomVertex(int mean, int sd) {
        int randVertex = std::rand() % V;
        if (dist == "UNIFORM") {
            return randVertex;
        } else if (dist == "SKEWED") {
            return static_cast<int>(V * (1 - std::sqrt(1 - randVertex / static_cast<double>(V))));
        } else {
            // Custom distribution logic for Gaussian distribution.
            if (dist == "GAUSSIAN") {
                static std::default_random_engine generator(static_cast<unsigned>(std::time(0)));
                std::normal_distribution<double> gaussian_dist(mean, sd);
                int generated_vertex;
                do {
                    generated_vertex = static_cast<int>(std::round(gaussian_dist(generator)));
                } while (generated_vertex < 0 || generated_vertex >= V);
                return generated_vertex;
            } else {
                std::cerr << "Unknown distribution: " << dist << std::endl;
                return randVertex;
            }
        }
    };

};