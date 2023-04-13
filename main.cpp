#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include "graph.cpp"

// ... Graph class definition as before ...

int main() {
    int V = 50;
    int E = 45;

    std::vector<std::string> graphTypes = {"COMPLETE", "CYCLE", "RANDOM"};
    std::vector<std::string> distributions = {"UNIFORM", "SKEWED", "MINE"};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << "Graph " << i + 1 << " (Type: " << graphTypes[i] << ", Distribution: " << distributions[j]
                      << "):\n";
            Graph graph(V, E, graphTypes[i], distributions[j]);
            graph.generateGraph();
            graph.printAdjacencyList();
            std::cout << std::endl;
        }
    }

    return 0;
}
