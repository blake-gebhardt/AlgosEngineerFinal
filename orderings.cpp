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

    // Sort deleted order based on degree
    int *sortedVertices = new int[N];
    Node *cur = deletedOrder;
    for (int i = 0; i < N; ++i) {
        sortedVertices[i] = cur->value;
        cur = cur->next;
    }
    std::sort(sortedVertices, sortedVertices + N, [&degree](int a, int b) {
        return degree[a] < degree[b];
    });

    int color[N];
    for (int i = 0; i < N; ++i) {
        int vertex = sortedVertices[i];
        SimpleSet usedColors;

        for (int j = 0; j < N; ++j) {
            if (adjMatrix[vertex][j] != -1 && degree[j] == -1) {
                usedColors.insert(color[j]);
            }
        }
        int assignedColor = 0;
        while (usedColors.contains(assignedColor)) {
            assignedColor++;
        }
        color[vertex] = assignedColor;
    }

    // Print the assigned colors
    for (int i = 0; i < N; ++i) {
        std::cout << "Vertex " << i << " has color " << color[i] << std::endl;
    }

    // Cleanup
    for (int i = 0; i < N; ++i) {
        Node *cur2 = degreeLists[i];
        while (cur2) {
            Node *next = cur2->next;
            delete cur2;
            cur2 = next;
        }
    }

    Node *curDeletedOrder = deletedOrder;
    while (curDeletedOrder) {
        Node *next = curDeletedOrder->next;
        delete curDeletedOrder;
        curDeletedOrder = next;
    }

    // Delete sortedVertices array
    delete[] sortedVertices;
}


void Orderings::smallestOriginalVertexOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    int **adjMatrix = graph.getAdjMatrix();

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

    int color[N];
    for (int i = 0; i < N; ++i) {
        int vertex = i;
        SimpleSet usedColors;

        for (int j = 0; j < N; ++j) {
            if (adjMatrix[vertex][j] != -1) {
                usedColors.insert(color[j]);
            }
        }
        int assignedColor = 0;
        while (usedColors.contains(assignedColor)) {
            assignedColor++;
        }
        color[vertex] = assignedColor;
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
}

void Orderings::uniformRandomOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    int **adjMatrix = graph.getAdjMatrix();
    int *order = new int[N];

    // Initialize the order array with vertex indices
    for (int i = 0; i < N; ++i) {
        order[i] = i;
    }

    // Shuffle the order array
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(order, order + N, g);

    // Initialize color array
    int *color = new int[N];
    for (int i = 0; i < N; ++i) {
        color[i] = -1;
    }

    // Assign colors
    for (int i = 0; i < N; ++i) {
        int vertex = order[i];
        SimpleSet usedColors;

        for (int j = 0; j < N; ++j) {
            if (adjMatrix[vertex][j] != -1 && color[j] != -1) {
                usedColors.insert(color[j]);
            }
        }
        int assignedColor = 0;
        while (usedColors.contains(assignedColor)) {
            assignedColor++;
        }
        color[vertex] = assignedColor;
    }

    // Print the assigned colors
    for (int i = 0; i < N; ++i) {
        std::cout << "Vertex " << i << " has color " << color[i] << std::endl;
    }

    // Cleanup
    delete[] order;
    delete[] color;
}

void Orderings::largestDegreeFirstOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    int **adjMatrix = graph.getAdjMatrix();

    int degree[N];
    for (int i = 0; i < N; ++i) {
        degree[i] = 0;
        for (int j = 0; j < N; ++j) {
            if (adjMatrix[i][j] != -1) {
                degree[i]++;
            }
        }
    }

    bool visited[N];
    int color[N];
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
        color[i] = 0;
    }

    for (int i = 0; i < N; ++i) {
        int maxDegreeVertex = -1;
        int maxDegree = -1;
        for (int j = 0; j < N; ++j) {
            if (!visited[j] && degree[j] > maxDegree) {
                maxDegree = degree[j];
                maxDegreeVertex = j;
            }
        }

        visited[maxDegreeVertex] = true;

        SimpleSet usedColors;
        for (int j = 0; j < N; ++j) {
            if (adjMatrix[maxDegreeVertex][j] != -1) {
                usedColors.insert(color[j]);
            }
        }

        int assignedColor = 0;
        while (usedColors.contains(assignedColor)) {
            assignedColor++;
        }
        color[maxDegreeVertex] = assignedColor;
    }

    // Print the assigned colors
    for (int i = 0; i < N; ++i) {
        std::cout << "Vertex " << i << " has color " << color[i] << std::endl;
    }
}


void Orderings::depthFirstOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    int **adjMatrix = graph.getAdjMatrix();

    bool visited[N];
    int color[N];
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
        color[i] = -1;
    }

    std::function<void(int)> dfs = [&](int v) {
        visited[v] = true;
        SimpleSet usedColors;
        for (int j = 0; j < N; ++j) {
            if (adjMatrix[v][j] != -1) {
                usedColors.insert(color[j]);
            }
        }

        int assignedColor = 0;
        while (usedColors.contains(assignedColor)) {
            assignedColor++;
        }
        color[v] = assignedColor;

        for (int j = 0; j < N; ++j) {
            if (adjMatrix[v][j] != -1 && !visited[j]) {
                dfs(j);
            }
        }
    };

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    // Print the assigned colors
    for (int i = 0; i < N; ++i) {
        std::cout << "Vertex " << i << " has color " << color[i] << std::endl;
    }
}

void Orderings::maximalIndependentSetOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    int **adjMatrix = graph.getAdjMatrix();

    bool *inSet = new bool[N]();
    bool *visited = new bool[N]();

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            inSet[i] = true;
            visited[i] = true;

            for (int j = 0; j < N; ++j) {
                if (adjMatrix[i][j] != -1) {
                    visited[j] = true;
                }
            }
        }
    }

    int *color = new int[N]();
    for (int i = 0; i < N; ++i) {
        if (inSet[i]) {
            SimpleSet usedColors;
            for (int j = 0; j < N; ++j) {
                if (adjMatrix[i][j] != -1) {
                    usedColors.insert(color[j]);
                }
            }

            int assignedColor = 0;
            while (usedColors.contains(assignedColor)) {
                assignedColor++;
            }
            color[i] = assignedColor;
        }
    }

    // Print the assigned colors
    for (int i = 0; i < N; ++i) {
        std::cout << "Vertex " << i << " has color " << color[i] << std::endl;
    }

    // Cleanup
    delete[] inSet;
    delete[] visited;
    delete[] color;
}

