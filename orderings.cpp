//
// Created by Blake Gebhardt on 20.04.23.
//
#include <iostream>
#include <algorithm>
#include "orderings.h"
#include "graph.h"


void Orderings::smallestLastVertexOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    Graph::Node **adjList = graph.getAdjList();

    Graph::Node *vertices = new Graph::Node[N];
    for (int i = 0; i < N; ++i) {
        vertices[i].value = i;
        vertices[i].next = nullptr;
    }

    Graph::Node *degreeLists[N];
    for (int i = 0; i < N; ++i) {
        degreeLists[i] = nullptr;
    }

    int degree[N];
    for (int i = 0; i < N; ++i) {
        degree[i] = graph.getDegree(i);
        Graph::Node *newNode = new Graph::Node();
        newNode->value = i;
        newNode->next = degreeLists[degree[i]];
        degreeLists[degree[i]] = newNode;
    }

    int degreeWhenDeleted[N];

    Graph::Node *deletedOrder = nullptr;
    for (int i = 0; i < N; ++i) {
        int smallestDegree = 0;
        while (!degreeLists[smallestDegree]) {
            smallestDegree++;
        }

        Graph::Node *vertexToDeleteNode = degreeLists[smallestDegree];
        degreeLists[smallestDegree] = vertexToDeleteNode->next;

        int vertexToDelete = vertexToDeleteNode->value;
        vertexToDeleteNode->next = deletedOrder;
        deletedOrder = vertexToDeleteNode;

        Graph::Node *current = adjList[vertexToDelete];
        while (current != nullptr) {
            int j = current->value;
            if (degree[j] != -1) {
                int oldDegree = degree[j];
                int newDegree = --degree[j];

                Graph::Node **oldDegreeList = &degreeLists[oldDegree];
                while (*oldDegreeList && (*oldDegreeList)->value != j) {
                    oldDegreeList = &((*oldDegreeList)->next);
                }

                if (*oldDegreeList) {
                    Graph::Node *nodeToMove = *oldDegreeList;
                    *oldDegreeList = nodeToMove->next;

                    nodeToMove->next = degreeLists[newDegree];
                    degreeLists[newDegree] = nodeToMove;
                }
            }
            current = current->next;
        }

        degreeWhenDeleted[vertexToDelete] = smallestDegree;
        degree[vertexToDelete] = -1;
    }

    int *sortedVertices = new int[N];
    Graph::Node *cur = deletedOrder;
    for (int i = 0; i < N; ++i) {
        sortedVertices[i] = cur->value;
        cur = cur->next;
    }

    int color[N];
    for (int i = 0; i < N; ++i) {
        int vertex = sortedVertices[i];
        SimpleSet usedColors;

        Graph::Node *neighbor = adjList[vertex];
        while (neighbor != nullptr) {
            int j = neighbor->value;
            if (degree[j] == -1) {
                usedColors.insert(color[j]);
            }
            neighbor = neighbor->next;
        }
        int assignedColor = 0;
        while (usedColors.contains(assignedColor)) {
            assignedColor++;
        }
        color[vertex] = assignedColor;
    }

    printSummary(graph, color, degreeWhenDeleted, N, "Smallest Last Vertex Ordering");

    // Cleanup
    for (int i = 0; i < N; ++i) {
        Graph::Node *cur2 = degreeLists[i];
        while (cur2) {
            Graph::Node *next = cur2->next;
            delete cur2;
            cur2 = next;
        }
    }

    Graph::Node *curDeletedOrder = deletedOrder;
    while (curDeletedOrder) {
        Graph::Node *next = curDeletedOrder->next;
        delete curDeletedOrder;
        curDeletedOrder = next;
    }

    // Delete sortedVertices array
    delete[] sortedVertices;

    // Delete vertices array
    delete[] vertices;
}




void Orderings::smallestOriginalVertexOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    Graph::Node **adjList = graph.getAdjList();

    Graph::Node *degreeLists[N];
    for (int i = 0; i < N; ++i) {
        degreeLists[i] = nullptr;
    }

    int degree[N];
    int degreeWhenDeleted[N];
    for (int i = 0; i < N; ++i) {
        degree[i] = 0;
        Graph::Node* temp = adjList[i];
        while(temp != nullptr) {
            degree[i]++;
            temp = temp->next;
        }
        degreeWhenDeleted[i] = degree[i]; // Store the degree when deleted
        Graph::Node *newNode = new Graph::Node();
        newNode->value = i;
        newNode->next = degreeLists[degree[i]];
        degreeLists[degree[i]] = newNode;
    }

    int color[N];
    for (int i = 0; i < N; ++i) {
        int vertex = i;
        SimpleSet usedColors;

        Graph::Node* temp = adjList[vertex];
        while(temp != nullptr) {
            usedColors.insert(color[temp->value]);
            temp = temp->next;
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

    // Update the printSummary function call to include the degreeWhenDeleted array
    //printSummary(graph, color, degreeWhenDeleted, N, "Smallest Original Degree Last");

    // Cleanup
    for (int i = 0; i < N; ++i) {
        Graph::Node *cur = degreeLists[i];
        while (cur) {
            Graph::Node *next = cur->next;
            delete cur;
            cur = next;
        }
    }
}

void Orderings::uniformRandomOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    Graph::Node **adjList = graph.getAdjList();
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

    // Initialize degreeWhenDeleted array
    int degreeWhenDeleted[N];
    for (int i = 0; i < N; ++i) {
        degreeWhenDeleted[i] = graph.getDegree(i); // Store the degree when deleted
    }

    // Assign colors
    for (int i = 0; i < N; ++i) {
        int vertex = order[i];
        SimpleSet usedColors;

        Graph::Node* temp = adjList[vertex];
        while(temp != nullptr) {
            if (color[temp->value] != -1) {
                usedColors.insert(color[temp->value]);
            }
            temp = temp->next;
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

    // Update the printSummary function call to include the degreeWhenDeleted array
    //printSummary(graph, color, degreeWhenDeleted, N, "Uniform Random Ordering");

    // Cleanup
    delete[] order;
    delete[] color;
}
void Orderings::largestDegreeFirstOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    Graph::Node **adjList = graph.getAdjList();

    int degree[N];
    for (int i = 0; i < N; ++i) {
        degree[i] = 0;
        Graph::Node *temp = adjList[i];
        while(temp) {
            degree[i]++;
            temp = temp->next;
        }
    }

    bool visited[N];
    int color[N];
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
        color[i] = 0;
    }

    // Initialize degreeWhenDeleted array
    int degreeWhenDeleted[N];

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
        degreeWhenDeleted[maxDegreeVertex] = maxDegree; // Store the degree when deleted

        SimpleSet usedColors;
        Graph::Node *temp = adjList[maxDegreeVertex];
        while(temp) {
            if (color[temp->value] != -1) {
                usedColors.insert(color[temp->value]);
            }
            temp = temp->next;
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

    // Update the printSummary function call to include the degreeWhenDeleted array
    //printSummary(graph, color, degreeWhenDeleted, N, "Largest Degree First");
}


void Orderings::depthFirstOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    Graph::Node **adjList = graph.getAdjList();

    bool visited[N];
    int color[N];
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
        color[i] = -1;
    }

    // Initialize degreeWhenDeleted array
    int degreeWhenDeleted[N];

    std::function<void(int)> dfs = [&](int v) {
        visited[v] = true;

        // Compute the degree when deleted
        int degree = 0;
        Graph::Node *temp = adjList[v];
        while(temp) {
            degree++;
            temp = temp->next;
        }
        degreeWhenDeleted[v] = degree;

        SimpleSet usedColors;
        temp = adjList[v];
        while(temp) {
            if (color[temp->value] != -1) {
                usedColors.insert(color[temp->value]);
            }
            temp = temp->next;
        }

        int assignedColor = 0;
        while (usedColors.contains(assignedColor)) {
            assignedColor++;
        }
        color[v] = assignedColor;

        temp = adjList[v];
        while(temp) {
            if (!visited[temp->value]) {
                dfs(temp->value);
            }
            temp = temp->next;
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

    // Update the printSummary function call to include the degreeWhenDeleted array
    //printSummary(graph, color, degreeWhenDeleted, N, "Depth-First Ordering");
}

void Orderings::maximalIndependentSetOrdering(Graph &graph) {
    int N = graph.getNumberOfVertices();
    Graph::Node **adjList = graph.getAdjList();

    bool *inSet = new bool[N]();
    bool *visited = new bool[N]();

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            inSet[i] = true;
            visited[i] = true;

            Graph::Node *temp = adjList[i];
            while(temp) {
                visited[temp->value] = true;
                temp = temp->next;
            }
        }
    }

    int *color = new int[N];
    int *degreeWhenDeleted = new int[N];
    for (int i = 0; i < N; ++i) {
        color[i] = -1;
    }

    for (int i = 0; i < N; ++i) {
        if (inSet[i]) {
            SimpleSet usedColors;
            Graph::Node *temp = adjList[i];
            while(temp) {
                usedColors.insert(color[temp->value]);
                temp = temp->next;
            }

            int assignedColor = 0;
            while (usedColors.contains(assignedColor)) {
                assignedColor++;
            }
            color[i] = assignedColor;
            degreeWhenDeleted[i] = graph.getDegree(i);
        }
    }

    for (int i = 0; i < N; ++i) {
        if (color[i] == -1) {
            SimpleSet usedColors;
            Graph::Node *temp = adjList[i];
            while(temp) {
                usedColors.insert(color[temp->value]);
                temp = temp->next;
            }

            int assignedColor = 0;
            while (usedColors.contains(assignedColor)) {
                assignedColor++;
            }
            color[i] = assignedColor;
            degreeWhenDeleted[i] = graph.getDegree(i);
        }
    }

    // Print the assigned colors
    for (int i = 0; i < N; ++i) {
        std::cout << "Vertex " << i << " has color " << color[i] << std::endl;
    }

    //printSummary(graph, color, degreeWhenDeleted, N, "Maximal Independent Set Ordering");

    // Cleanup
    delete[] inSet;
    delete[] visited;
    delete[] color;
    delete[] degreeWhenDeleted;
}

void Orderings::printSummary(Graph &graph, int *color, int *degreeWhenDeleted, int N, const std::string &methodName) {
    int maxColor = 0;
    for (int i = 0; i < N; ++i) {
        if (color[i] > maxColor) {
            maxColor = color[i];
        }
    }
    maxColor++;

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Summary for " << methodName << std::endl;
    std::cout << "Total colors used: " << maxColor << std::endl;

    std::vector<int> colorCount(maxColor, 0);
    double sumOriginalDegree = 0;
    int maxDegreeWhenDeleted = 0;

    for (int i = 0; i < N; ++i) {
        colorCount[color[i]]++;
        int originalDegree = graph.getDegree(i);
        sumOriginalDegree += originalDegree;
        int currentDegreeWhenDeleted = degreeWhenDeleted[i];

        if (currentDegreeWhenDeleted > maxDegreeWhenDeleted) {
            maxDegreeWhenDeleted = currentDegreeWhenDeleted;
        }

        std::cout << "Vertex " << i << ": Color " << color[i] << ", Original degree " << originalDegree << ", Degree when deleted " << currentDegreeWhenDeleted << std::endl;
    }

    for (int i = 0; i < maxColor; ++i) {
        std::cout << "Color " << i << ": " << colorCount[i] << " vertices" << std::endl;
    }

    double averageOriginalDegree = sumOriginalDegree / N;
    std::cout << "Average original degree: " << averageOriginalDegree << std::endl;
    std::cout << "Maximum degree when deleted: " << maxDegreeWhenDeleted << std::endl;

    int terminalCliqueSize = 0;
    for (int i = 0; i < N; ++i) {
        int degree = graph.getDegree(i);
        if (degree >= terminalCliqueSize) {
            terminalCliqueSize = degree + 1;
        }
    }
    std::cout << "Size of the terminal clique: " << terminalCliqueSize << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}
