#include <iostream>
#include <algorithm>
#include "orderings.h"




int main() {
    // Define the number of vertices and edges for the graphs
    int V = 20;
    int E = 25;

    // Open the file to save adjacency lists
    std::ofstream outputFile("graphs.txt");

    // Generate the complete graph
    Graph complete(V, E, "COMPLETE", "UNIFORM");
    complete.generateGraph();
    outputFile << "COMPLETE Graph" << std::endl;
    outputFile << "-----------------" << std::endl;
    complete.printAdjacencyList(outputFile);
    complete.visualizeGraph(complete);

    // Generate the cycle graph
    Graph cycle(V, E, "CYCLE", "UNIFORM");
    cycle.generateGraph();
    outputFile << "\nCYCLE Graph" << std::endl;
    outputFile << "-----------------" << std::endl;
    cycle.printAdjacencyList(outputFile);
    cycle.visualizeGraph(cycle);

    // Generate the random uniform graph
    Graph randUniform(V, E, "RANDOM", "UNIFORM");
    randUniform.generateGraph();
    outputFile << "\nRANDOM (Uniform) Graph" << std::endl;
    outputFile << "-----------------" << std::endl;
    randUniform.printAdjacencyList(outputFile);
    randUniform.visualizeGraph(randUniform);

    // Generate the random skewed graph
    Graph randSkewed(V, E, "RANDOM", "SKEWED");
    randSkewed.generateGraph();
    outputFile << "\nRANDOM (Skewed) Graph" << std::endl;
    outputFile << "-----------------" << std::endl;
    randSkewed.printAdjacencyList(outputFile);
    randSkewed.visualizeGraph(randSkewed);

    // Generate the random Gaussian graph
    Graph randGaussian(V, E, "RANDOM", "GAUSSIAN");
    randGaussian.generateGraph();
    outputFile << "\nRANDOM (Gaussian) Graph" << std::endl;
    outputFile << "-----------------" << std::endl;
    randGaussian.printAdjacencyList(outputFile);
    randGaussian.visualizeGraph(randGaussian);

    // Close the output file
    outputFile.close();

    return 0;
}
