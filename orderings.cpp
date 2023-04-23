//
// Created by Blake Gebhardt on 20.04.23.
//
#include <iostream>
#include <algorithm>
#include "orderings.h"


void Orderings::smallestLastVertexOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    int **adjMatrix = graph.getAdjMatrix();

    Node *vertices = new Node[N];
    for (int i = 0; i < N; ++i) {
        vertices[i].value = i;
        vertices[i].next = nullptr;
    }

    Node *degreeLists[N];
    for (int i = 0; i < N; ++i) {
        degreeLists[i] = nullptr;
    }

    int degree[N];
    for (int i = 0; i < N; ++i) {
        degree[i] = 0;
        for (int j = 0; j < N; ++j) {
            if (adjMatrix[i][j] != -1) {
                degree[i]++;
            }
        }
        Node *newNode = new Node();
        newNode->value = i;
        newNode->next = degreeLists[degree[i]];
        degreeLists[degree[i]] = newNode;
    }

    Node *deletedOrder = nullptr;
    for (int i = 0; i < N; ++i) {
        int smallestDegree = 0;
        while (!degreeLists[smallestDegree]) {
            smallestDegree++;
        }

        Node *vertexToDeleteNode = degreeLists[smallestDegree];
        degreeLists[smallestDegree] = vertexToDeleteNode->next;

        int vertexToDelete = vertexToDeleteNode->value;
        vertexToDeleteNode->next = deletedOrder;
        deletedOrder = vertexToDeleteNode;

        for (int j = 0; j < N; ++j) {
            if (adjMatrix[vertexToDelete][j] != -1 && degree[j] != -1) {
                int oldDegree = degree[j];
                int newDegree = --degree[j];

                Node **oldDegreeList = &degreeLists[oldDegree];
                while (*oldDegreeList && (*oldDegreeList)->value != j) {
                    oldDegreeList = &((*oldDegreeList)->next);
                }

                if (*oldDegreeList) {
                    Node *nodeToMove = *oldDegreeList;
                    *oldDegreeList = nodeToMove->next;

                    nodeToMove->next = degreeLists[newDegree];
                    degreeLists[newDegree] = nodeToMove;
                }
            }
        }

        degree[vertexToDelete] = -1;
    }

    int color[N];
    Node *cur = deletedOrder;
    while (cur) {
        int vertex = cur->value;
        SimpleSet usedColors;

        for (int j = 0; j < N; ++j) {
            if (adjMatrix[vertex][j] != -1 && degree[j] ==
                                              -1) {
                usedColors.insert(color[j]);
            }
        }
        int assignedColor = 0;
        while (usedColors.contains(assignedColor)) {
            assignedColor++;
        }
        color[vertex] = assignedColor;

        cur = cur->next;
    }

// Print the assigned colors
    for (int i = 0; i < N; ++i) {
        std::cout << "Vertex " << i << " has color " << color[i] << std::endl;
    }

// Cleanup
    for (int i = 0; i < N; ++i) {
        Node *cur = degreeLists[i];
        while (cur) {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }
    }

    Node *curDeletedOrder = deletedOrder;
    while (curDeletedOrder) {
        Node *next = curDeletedOrder->next;
        delete curDeletedOrder;
        curDeletedOrder = next;
    }

};



