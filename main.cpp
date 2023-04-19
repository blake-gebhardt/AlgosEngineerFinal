#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include "graph.cpp"



int main() {
    // Define the number of vertices and edges for the graphs
    int V = 20;
    int E = 25;

    // Generate the complete graph
    Graph complete(V, E, "COMPLETE", "UNIFORM");
    complete.generateGraph();
    std::cout << "COMPLETE Graph" << std::endl;
    std::cout << "-----------------" << std::endl;
    complete.printAdjacencyList();
    complete.visualizeGraph(complete);

    // Generate the cycle graph
    Graph cycle(V, E, "CYCLE", "UNIFORM");
    cycle.generateGraph();
    std::cout << "\nCYCLE Graph" << std::endl;
    std::cout << "-----------------" << std::endl;
    cycle.printAdjacencyList();
    cycle.visualizeGraph(cycle);

    // Generate the random uniform graph
    Graph randUniform(V, E, "RANDOM", "UNIFORM");
    randUniform.generateGraph();
    std::cout << "\nRANDOM (Uniform) Graph" << std::endl;
    std::cout << "-----------------" << std::endl;
    randUniform.printAdjacencyList();
    randUniform.visualizeGraph(randUniform);

    // Generate the random skewed graph
    Graph randSkewed(V, E, "RANDOM", "SKEWED");
    randSkewed.generateGraph();
    std::cout << "\nRANDOM (Skewed) Graph" << std::endl;
    std::cout << "-----------------" << std::endl;
    randSkewed.printAdjacencyList();
    randSkewed.visualizeGraph(randSkewed);

    // Generate the random Gaussian graph
    Graph randGaussian(V, E, "RANDOM", "GAUSSIAN");
    randGaussian.generateGraph();
    std::cout << "\nRANDOM (Gaussian) Graph" << std::endl;
    std::cout << "-----------------" << std::endl;
    randGaussian.printAdjacencyList();
    randGaussian.visualizeGraph(randGaussian);

    return 0;
}
