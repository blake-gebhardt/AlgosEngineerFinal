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
    struct Node {
        int value;
        Node *next;
    };
    Graph(int V, int E, std::string type, std::string dist);
    ~Graph();

    void generateGraph();
    void printAdjacencyList(std::ostream &out);
    static void visualizeGraph(const Graph &graph);

    int getNumberOfVertices() const;
    int getDegree(int vertex) const;

    Node **getAdjList();

private:
    int V, E;
    std::string type, dist;
    Node **adj;

    void generateCompleteGraph();
    void generateCycleGraph();
    void generateRandomGraph();
    int getRandomVertex(int mean, int sd, std::default_random_engine &generator);

    void addEdge(int u, int v);

    bool edgeExists(int u, int v);
};

#endif //ALGOSENGINEERFINAL_GRAPH_H