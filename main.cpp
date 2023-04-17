#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include "graph.cpp"



int main() {
    int V = 25;
    int E = 15;

    std::vector<std::string> graphTypes = {"COMPLETE", "CYCLE", "RANDOM"};
    std::vector<std::string> distributions = {"UNIFORM", "SKEWED", "GAUSSIAN"};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << "Graph " << i + 1 << " (Type: " << graphTypes[i] << ", Distribution: " << distributions[j]
                      << "):\n";
            Graph graph(V, E, graphTypes[i], distributions[j]);
            graph.generateGraph();
            graph.printAdjacencyList();
            graph.visualizeGraph(graph);
            std::cout << std::endl;
        }
    }

    return 0;
}
