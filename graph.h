//
// Created by Blake Gebhardt on 23.04.23.
//

#ifndef ALGOSENGINEERFINAL_GRAPH_H
#define ALGOSENGINEERFINAL_GRAPH_H

#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <fstream>

class Graph {
public:
    Graph(int V, int E, std::string type, std::string dist);
    ~Graph();

    void generateGraph();
    void printAdjacencyList(std::ostream &out);
    static void visualizeGraph(const Graph &graph);

    int getNumberOfVertices() const;
    int **getAdjMatrix();

private:
    int V, E;
    std::string type, dist;
    int **adj;

    void generateCompleteGraph();
    void generateCycleGraph();
    void generateRandomGraph();
    int getRandomVertex(int mean, int sd);
};







#endif //ALGOSENGINEERFINAL_GRAPH_H
