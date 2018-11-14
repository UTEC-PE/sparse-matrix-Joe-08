#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    int x, y;
    T data;
    Node* next;
    Node* down;
};

#endif