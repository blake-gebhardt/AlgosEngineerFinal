//
// Created by Blake Gebhardt on 23.04.23.
//

#ifndef ALGOSENGINEERFINAL_ORDERINGS_H
#define ALGOSENGINEERFINAL_ORDERINGS_H
#include <iostream>
#include <algorithm>
#include "graph.h"

class Orderings {
public:
    static void smallestLastVertexOrdering(Graph &graph);

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
