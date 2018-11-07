#include <stdio.h>
#include <stdlib.h>

#include "adjlist.h"

//typedef struct node Node;
struct node {
    int ref;
    int weight;
    struct node *next;
};

//typedef struct graph Graph;
struct graph    {
    int vertices;
    struct node **adjList;
};    

Node *addNode(int ref)  {
    Node *new = malloc(sizeof(Node));
    new->ref = ref;
    new->weight = 0;
    new->next = NULL;
    return new;
}

void addEdge(Graph *g, int src, int dst, int weight)    {
    Node *new = addNode(dst);
    new->weight = weight;
    new->next = g->adjList[src];
    g->adjList[src] = new;

    new = addNode(src);
    new->weight = weight;
    new->next = g->adjList[dst];
    g->adjList[dst] = new;
}   

Graph *createGraph(int vertices)    {
    Graph *g = malloc(sizeof(Graph));
    g->vertices = vertices;

    g->adjList = malloc(vertices * sizeof(Node*));
    for(int i = 0; i < vertices; i++)
        g->adjList[i] = NULL;

    return g;
}   

void printGraph(Graph *g, FILE *file)   {
    for(int i = 0; i < g->vertices; i++)    {
        Node *tmp = g->adjList[i];
        Node *base = g->adjList[i];
        while(tmp)  {
            if(tmp->ref != base->ref)
                fprintf(file, "%d %d %d\n", base->ref, tmp->ref, tmp->weight);
            tmp = tmp->next;
        }
    }
}

