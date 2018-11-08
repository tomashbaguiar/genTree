#ifndef ADJLIST_H
    #define ADJLIST_H

    typedef struct node Node;
    typedef struct graph Graph;
    typedef struct edge Edge;
    typedef struct adjList AdjList;

    // A utility function to create a new adjacency list node 
    Node* newAdjListNode(int dest, int weight);

    // A utility function that creates a graph of V vertices 
    Graph* createGraph(int V); 

    // Adds an edge to an undirected graph 
    void addEdge(Graph* graph, int src, int dest, int weight); 

    Graph *recvOriginGraph(FILE *file);

    // A utility function to create a new Min Heap Node 
    struct MinHeapNode* newMinHeapNode(int v, int key); 

    // A utilit function to create a Min Heap 
    struct MinHeap* createMinHeap(int capacity); 

    // A utility function to swap two nodes of min heap. Needed for min heapify 
    void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b); 

    // A standard function to heapify at given idx 
    // This function also updates position of nodes when they are swapped. 
    // Position is needed for decreaseKey(); 
    void minHeapify(struct MinHeap* minHeap, int idx); 

    // A utility function to check if the given minHeap is ampty or not 
    int isEmpty(struct MinHeap* minHeap); 

    // Standard function to extract minimum node from heap 
    struct MinHeapNode* extractMin(struct MinHeap* minHeap); 

    // Function to decreasy key value of a given vertex v. This function 
    // uses pos[] of min heap to get the current index of node in min heap 
    void decreaseKey(struct MinHeap* minHeap, int v, int key); 

    // A utility function to check if a given vertex 'v' is in min heap or not 
    int isInMinHeap(struct MinHeap* minHeap, int v); 

    // A utility function used to print the constructed MST 
    //void printArr(int arr[], int n); 
    void printArr(Graph *g, int arr[], int n, FILE *file);

    // The main function that constructs Minimum Spanning Tree (MST) using Prim's algorithm 
    void PrimMST(Graph* graph, FILE *file); 

#endif

