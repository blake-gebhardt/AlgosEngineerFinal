//
// Created by Blake Gebhardt on 13.04.23.
//

#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <utility>
#include "graph.h"


    Graph::Graph(int V, int E, std::string type, std::string dist)
            : V(V), E(E), type(std::move(type)), dist(std::move(dist)) {
        adj = new int *[V];
        for (int i = 0; i < V; ++i) {
            adj[i] = new int[V];
            std::fill_n(adj[i], V, -1);
        }
    }

    Graph::~Graph() {
        for (int i = 0; i < V; ++i) {
            delete[] adj[i];
        }
        delete[] adj;
    }

void Graph::generateGraph() {
    if (type == "COMPLETE") {
        generateCompleteGraph();
    } else if (type == "CYCLE") {
        generateCycleGraph();
    } else if (type == "RANDOM") {
        generateRandomGraph();
    }
}

void Graph::printAdjacencyList(std::ostream &out) {
    for (int i = 0; i < V; ++i) {
        out << i << ": ";
        for (int j = 0; j < V; ++j) {
            if (adj[i][j] != -1) {
                out << adj[i][j] << " ";
            }
        }
        out << std::endl;
    }
}

/*THE CODE BELOW WAS WRITTEN WITH HELP FROM https://graphviz.org/
 * https://sketchviz.com/graphviz-examples
 * and OpenAI
*/
void Graph::visualizeGraph(const Graph &graph) {
// Create a new DOT file for the graph
    std::string fileName = graph.type + graph.dist;
    std::ofstream dotFile(fileName + ".dot");
    dotFile << "graph {\n";

    // Specify the circo layout algorithm
    dotFile << "layout=circo;\n";

    // Add nodes to the DOT file
    for (int i = 0; i < graph.V; ++i) {
        dotFile << i << ";\n";
    }

    // Add edges to the DOT file
    for (int i = 0; i < graph.V; ++i) {
        for (int j = i; j < graph.V; ++j) {
            if (graph.adj[i][j] != -1) {
                dotFile << i << " -- " << j << ";\n";
            }
        }
    }

    // Close the DOT file
    dotFile << "}\n";
    dotFile.close();

    // Call Graphviz to render the graph with the circo layout algorithm
    std::string toRender = "circo -Tpng " + fileName + ".dot -o " + fileName + ".png";
    std::system(toRender.c_str());

    // Delete the DOT file
    std::remove((fileName + ".dot").c_str());

}

int Graph::getNumberOfVertices() const {
    return V;
}

int **Graph::getAdjMatrix() {
    return adj;
}

void Graph::generateCompleteGraph() {
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            adj[i][j] = j;
            adj[j][i] = i;
        }
    }
}

void Graph::generateCycleGraph() {
    for (int i = 0; i < V; ++i) {
        adj[i][(i + 1) % V] = (i + 1) % V;
        adj[(i + 1) % V][i] = i;
    }
}

void Graph::generateRandomGraph() {
    std::default_random_engine generator(static_cast<unsigned>(std::time(0)));
    int edgesCreated = 0;
    int mean = V / 2;
    int sd = (V / 6) + 1;
    while (edgesCreated < E) {
        int u = getRandomVertex(mean, sd, generator);
        int v = getRandomVertex(mean, sd, generator);

        if (u != v && adj[u][v] == -1) {
            adj[u][v] = v;
            adj[v][u] = u;
            edgesCreated++;
        }
    }
}

int Graph::getRandomVertex(int mean, int sd, std::default_random_engine& generator) {
    std::uniform_int_distribution<int> uniform_dist(0, V - 1);
    if (dist == "UNIFORM") {
        return uniform_dist(generator);
    } else if (dist == "SKEWED") {
        int randVertex = uniform_dist(generator);
        int randVertex2 = uniform_dist(generator);
        return std::min(randVertex, randVertex2);
    } else {
        // Custom distribution logic for Gaussian distribution.
        if (dist == "GAUSSIAN") {
            std::normal_distribution<double> gaussian_dist(mean, sd);
            int generated_vertex;
            do {
                generated_vertex = static_cast<int>(std::round(gaussian_dist(generator)));
            } while (generated_vertex < 0 || generated_vertex >= V);
            return generated_vertex;
        } else {
            std::cerr << "Unknown distribution: " << dist << std::endl;
            return uniform_dist(generator);
        }
    }
}

int Graph::getDegree(int vertex) const {
    int degree = 0;
    for (int i = 0; i < V; ++i) {
        if (adj[vertex][i] != -1) {
            degree++;
        }
    }
    return degree;
}
