#include <stdio.h>
#include <stdlib.h>

#include "adjlist.h"

//typedef struct node Node;
struct node {
    int ref;
    //int weight;
    struct edge *edgeList;
    struct node *next;
};

struct edge {
    int u;
    int v;
    int weight;
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
        while(tmp)  {
                fprintf(file, "%d %d %d\n", i, tmp->ref, tmp->weight);
            tmp = tmp->next;
        }
    }
}

Graph *recvOriginGraph(FILE *file)  {
    int vertices, edges;
    fscanf(file, "%d %d\n", &vertices, &edges);

    Graph *g = createGraph(vertices);

    for(int i = 0; i < edges; i++)  {
        int src, dst, weight;
        fscanf(file, "%d %d %d\n", &src, &dst, &weight);
        addEdge(g, src, dst, weight);
    }

    return g;
}    

Graph *primAlgorithm(Graph *g)  {
    Graph *least = createGraph(g->vertices);
    for(int i = 0; i < g->vertices; i++)    {
        Node *tmp = g->adjList[i];
        Node *aux = tmp->next;
        while(tmp)  {
            if(aux->weight > tmp->weight)
                aux = tmp;
            tmp = tmp->next;
        }
        addEdge(least, i, aux->ref, aux->weight);
    }

    return least;
}

int existVertex(Graph *g, int ref)    {
    return (g->adjList[ref] != NULL);
}    

