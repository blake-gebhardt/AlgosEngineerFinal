//
// Created by Blake Gebhardt on 23.04.23.
//

#ifndef ALGOSENGINEERFINAL_ORDERINGS_H
#define ALGOSENGINEERFINAL_ORDERINGS_H
#include <iostream>
#include <algorithm>
#include "graph.h"


/*
 * Implement the smallest last ordering algorithm.
 * Implement the smallest original degree last ordering algorithm.
 * Implement the uniform random ordering algorithm.
 * Implement three additional ordering algorithms of your choice.
 */
class Orderings {
public:
    static void smallestLastVertexOrdering(Graph &graph);
    static void smallestOriginalVertexOrdering(Graph &graph);
    static void uniformRandomOrdering(Graph &graph);
    static void largestDegreeFirstOrdering(Graph &graph);
    static void depthFirstOrdering(Graph &graph);
    static void maximalIndependentSetOrdering(Graph &graph);

private:
    class Node {
    public:
        int value;
        Node *next;
    };

    class SimpleSet {
    public:
        void insert(int val) {
            if (contains(val)) return;
            Node *newNode = new Node();
            newNode->value = val;
            newNode->next = head;
            head = newNode;
        }

        bool contains(int val) {
            Node *cur = head;
            while (cur) {
                if (cur->value == val) return true;
                cur = cur->next;
            }
            return false;
        }

    private:
        Node *head = nullptr;
    };
};
#endif //ALGOSENGINEERFINAL_ORDERINGS_H
