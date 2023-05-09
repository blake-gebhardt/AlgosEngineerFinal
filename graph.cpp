//
// Created by Blake Gebhardt on 13.04.23.
//

#include <iostream>
#include <random>
#include <ctime>
#include <utility>
#include "graph.h"



Graph::Graph(int V, int E, std::string type, std::string dist)
        : V(V), E(E), type(std::move(type)), dist(std::move(dist)) {
    adj = new Node *[V];
    for (int i = 0; i < V; ++i) {
        adj[i] = nullptr;
    }
}

Graph::~Graph() {
    for (int i = 0; i < V; ++i) {
        Node *cur = adj[i];
        while (cur) {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }
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
        Node *cur = adj[i];
        while (cur) {
            out << cur->value << " ";
            cur = cur->next;
        }
        out << std::endl;
    }
}

// ... (rest of the functions: visualizeGraph, getNumberOfVertices, etc.)

void Graph::generateCompleteGraph() {
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            addEdge(i, j);
        }
    }
}

void Graph::generateCycleGraph() {
    for (int i = 0; i < V; ++i) {
        addEdge(i, (i + 1) % V);
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

        if (u != v && !edgeExists(u, v)) {
            addEdge(u, v);
            edgesCreated++;
        }
    }
}

int Graph::getDegree(int vertex) const {
    int degree = 0;
    Node *cur = adj[vertex];
    while (cur) {
        degree++;
        cur = cur->next;
    }
    return degree;
}

Graph::Node** Graph::getAdjList() {
    return adj;
}


void Graph::addEdge(int u, int v) {
    Node *newNodeU = new Node();
    newNodeU->value = v;
    newNodeU->next = adj[u];
    adj[u] = newNodeU;

    Node *newNodeV = new Node();
    newNodeV->value = u;
    newNodeV->next = adj[v];
    adj[v] = newNodeV;
}

bool Graph::edgeExists(int u, int v) {
    Node *cur = adj[u];
    while (cur) {
        if (cur->value == v) {
            return true;
        }
        cur = cur->next;
    }
    return false;
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
        Node *current = graph.adj[i];
        while (current != nullptr) {
            int j = current->value;
            if (j > i) { // To avoid duplicate edges
                dotFile << i << " -- " << j << ";\n";
            }
            current = current->next;
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


