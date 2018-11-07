#ifndef ADJLIST_H
    #define ADJLIST_H

    typedef struct node Node;
    typedef struct graph Graph;

    Node *addNode(int ref);
    void addEdge(Graph *g, int src, int dst, int weight);
    void rmEdge(Graph *g, int src, int dst);
    Graph *createGraph(int vertices);
    void printGraph(Graph *g, FILE *file);

#endif
