//
// Created by Blake Gebhardt on 13.04.23.
//

#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

class Graph {
public:
    Graph(int V, int E, const std::string& type, const std::string& dist)
            : V(V), E(E), type(type), dist(dist) {
        adj = new int*[V];
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

private:
    int V, E;
    std::string type, dist;
    int** adj;

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

        while (edgesCreated < E) {
            int u = getRandomVertex();
            int v = getRandomVertex();

            if (u != v && adj[u][v] == -1) {
                adj[u][v] = v;
                adj[v][u] = u;
                edgesCreated++;
            }
        }
    }

    int getRandomVertex() {
        int randVertex = std::rand() % V;
        if (dist == "UNIFORM") {
            return randVertex;
        } else if (dist == "SKEWED") {
            return static_cast<int>(V * (1 - std::sqrt(1 - randVertex / static_cast<double>(V))));
        } else {
            // Custom distribution logic goes here.
            return randVertex;  // Placeholder.
        }
    }
};


