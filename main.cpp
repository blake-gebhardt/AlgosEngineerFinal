#include <iostream>
#include <algorithm>
#include "orderings.h"




int main() {
    // Define the number of vertices and edges for the graphs
    int V = 100;
    int E = 100;

    // Open the file to save adjacency lists
    std::ofstream outputFile("graphs.txt");

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // Generate the complete graph
    Graph complete(V, E, "COMPLETE", "none");
    complete.generateGraph();
    outputFile << "COMPLETE Graph" << std::endl;
    outputFile << "-----------------" << std::endl;
    complete.printAdjacencyList(outputFile);
    complete.visualizeGraph(complete);

    // Generate the cycle graph
    Graph cycle(V, E, "CYCLE", "none");
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

    Orderings orderer;
    Graph* graphs[5] = {&complete, &cycle, &randUniform, &randSkewed, &randGaussian};
    std::string graphNames[5] = {"complete", "cycle", "randUniform", "randSkewed", "randGaussian"};



    for (int i = 0; i < 5; ++i) {
        std::cout << "Applying orderings on " << graphNames[i] << " graph:" << std::endl;

        std::cout << "\nSmallest last vertex ordering:" << std::endl;
        orderer.smallestLastVertexOrdering(*graphs[i]);

        std::cout << "\nSmallest original vertex ordering:" << std::endl;
        orderer.smallestOriginalVertexOrdering(*graphs[i]);

        std::cout << "\nUniform random ordering:" << std::endl;
        orderer.uniformRandomOrdering(*graphs[i]);

        std::cout << "\nLargest degree first ordering:" << std::endl;
        orderer.largestDegreeFirstOrdering(*graphs[i]);

        std::cout << "\nDepth-first search ordering:" << std::endl;
        orderer.depthFirstOrdering(*graphs[i]);

        std::cout << "\nMaximal independent set ordering:" << std::endl;
        orderer.maximalIndependentSetOrdering(*graphs[i]);

        std::cout << "\n---------------------------------------\n";
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << " seconds" << std::endl;


    return 0;
}
