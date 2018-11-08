#ifndef ADJLIST_H
    #define ADJLIST_H

    typedef struct node Node;
    typedef struct graph Graph;
    typedef struct adjList AdjList;

    // Função para criar novo no para lista de adjacencias
    Node* newAdjListNode(int dst, int weight);

    // Função que cria um novo grafo com V vertices
    Graph* createGraph(int V); 

    // Procedimento que adiciona arestas a um grafo
    void addEdge(Graph* graph, int src, int dest, int weight); 

    // Função que cria um grafo a partir do arquivo de entrada
    Graph *recvOriginGraph(FILE *file);

    // Função que cria um novo no de Heap
    struct MinHeapNode* newMinHeapNode(int v, int key); 

    // Função que cria um novo minHeap
    struct MinHeap* createMinHeap(int capacity); 

    // Função que troca dois nos de lugar
    void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b); 

    // Cria um heap local
    void minHeapify(struct MinHeap* minHeap, int idx); 

    // Retorna se um minHeap esta vazio
    int isEmpty(struct MinHeap* minHeap); 

    // Função que extrai o menor no de um heap
    struct MinHeapNode* extractMin(struct MinHeap* minHeap); 

    // Função para diminuir o valor de um nó no heap
    void decreaseKey(struct MinHeap* minHeap, int v, int key); 

    // Função para checar se um vertice e o menor de um heap
    int isInMinHeap(struct MinHeap* minHeap, int v); 

    // Coloca a arvore minima no arquivo de saida
    void printArr(Graph *g, int arr[], int n, FILE *file);

    // Algoritmo de Prim
    void PrimMST(Graph* graph, FILE *file); 

#endif

