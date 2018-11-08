#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 
  
#include "adjlist.h"

// Estrutura para representar um no na lista de adjacencia
struct node { 
    int dst;            // Referencia do no. 
    int weight;         // Peso para o no.
    struct node* next;  // Proximo no na lista.
}; 
  
// Estrutura para representar a lista de adjacencia
struct adjList { 
    struct node* head;  // Primeiro no da lista.
}; 
  
// Estrutura para representar o grafo
struct graph { 
    int V;              // Numero de vertices do grafo.
    struct adjList* list;   // Lista de adjacencias.
}; 
  
Node* newAdjListNode(int dst, int weight) 
{
    // Cria um novo no para uma lista
    Node* newNode = (Node*)malloc(sizeof(Node)); 
    newNode->dst = dst; 
    newNode->weight = weight; 
    newNode->next = NULL; 
    return newNode; 
} 
  
Graph* createGraph(int V) 
{ 
    // Cria um novo grafo com V vertices
    Graph* graph = (Graph*)malloc(sizeof(Graph)); 
    graph->V = V; 
  
    // Cria a lista de adjacencias
    graph->list = (AdjList*)malloc(V * sizeof(AdjList)); 
  
    // Inicializa cada vertice da lista como nulo
    for (int i = 0; i < V; ++i) 
        graph->list[i].head = NULL; 
  
    return graph; 
}
  
void addEdge(Graph* graph, int src, int dst, int weight) 
{ 
    // Adiciona um novo no ao inicio da adjacencia
    Node* newNode = newAdjListNode(dst, weight); 
    newNode->next = graph->list[src].head; 
    graph->list[src].head = newNode; 
  
    // Grafo bidirecional
    newNode = newAdjListNode(src, weight); 
    newNode->next = graph->list[dst].head; 
    graph->list[dst].head = newNode; 
}

Graph *recvOriginGraph(FILE *file)  {
    // Recebe os valores de vertices e arestas
    int vertices, edges;
    fscanf(file, "%d %d\n", &vertices, &edges);

    // Cria o grafo
    Graph *g = createGraph(vertices);

    // Recebe as arestas do grafo
    for(int i = 0; i < edges; i++)  {
        int src, dst, weight;
        fscanf(file, "%d %d %d\n", &src, &dst, &weight);
        addEdge(g, src, dst, weight);
    }

    return g;
}  
  
// Estrutura para representar um no de minHeap
struct MinHeapNode { 
    int v;          // Referencia.
    int key;        // Valor.
}; 
  
// Estrutura para representar um heap minimo
struct MinHeap { 
    int size;       // Numero de nos do heap.
    int capacity;   // Capacidade do heap.
    int* pos;
    struct MinHeapNode** array; 
}; 
  
struct MinHeapNode* newMinHeapNode(int v, int key) 
{ 
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode)); 
    minHeapNode->v = v; 
    minHeapNode->key = key; 
    return minHeapNode; 
} 
  
struct MinHeap* createMinHeap(int capacity) 
{ 
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
    minHeap->pos = (int*)malloc(capacity * sizeof(int)); 
    minHeap->size = 0; 
    minHeap->capacity = capacity; 
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*)); 
    return minHeap; 
} 
  
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) 
{ 
    struct MinHeapNode* t = *a; 
    *a = *b; 
    *b = t; 
} 
  
void minHeapify(struct MinHeap* minHeap, int idx) 
{ 
    int smallest, left, right; 
    smallest = idx; 
    left = 2 * idx + 1; 
    right = 2 * idx + 2; 
  
    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key) 
        smallest = left; 
  
    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key) 
        smallest = right; 
  
    if (smallest != idx) { 
        // The nodes to be swapped in min heap 
        struct MinHeapNode* smallestNode = minHeap->array[smallest]; 
        struct MinHeapNode* idxNode = minHeap->array[idx]; 
  
        // Swap posições 
        minHeap->pos[smallestNode->v] = idx; 
        minHeap->pos[idxNode->v] = smallest; 
  
        // Swap no
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 
  
        minHeapify(minHeap, smallest); 
    } 
} 
  
int isEmpty(struct MinHeap* minHeap) 
{ 
    return minHeap->size == 0; 
} 
  
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
{ 
    if (isEmpty(minHeap)) 
        return NULL; 
  
    // Guarda o pivot
    struct MinHeapNode* root = minHeap->array[0]; 
  
    // Troca o pivot com o ultimo no
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
    minHeap->array[0] = lastNode; 
  
    // Atualiza a posição do ultimo no
    minHeap->pos[root->v] = minHeap->size - 1; 
    minHeap->pos[lastNode->v] = 0; 
  
    // Reduz o tamanho do heap e o refaz
    --minHeap->size; 
    minHeapify(minHeap, 0); 
  
    return root; 
} 
  
void decreaseKey(struct MinHeap* minHeap, int v, int key) 
{ 
    // Guarda o indice de v no vetor
    int i = minHeap->pos[v]; 
  
    // Gurada o no e atualiza seu valor
    minHeap->array[i]->key = key; 
  
    // Itera enquanto a arvore nao esta em heap
    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) { 
        // Swap 
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2; 
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i; 
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); 
  
        // Move para o indice do pai
        i = (i - 1) / 2; 
    } 
} 
  
int isInMinHeap(struct MinHeap* minHeap, int v) 
{ 
    if (minHeap->pos[v] < minHeap->size) 
        return 1; 
    return 0; 
} 
  
void printArr(Graph *g, int arr[], int n, FILE *file) 
{
    fprintf(file, "%d %d\n", g->V, (n - 1));
    for (int i = 1; i < n; ++i) {
        Node *src = g->list[arr[i]].head;
        while(src->dst != i)
            src = src->next;
        fprintf(file, "%d %d %d\n", arr[i], i, src->weight);
    }
} 
  
void PrimMST(Graph* graph, FILE *file) 
{ 
    int V = graph->V;                                   // Numero de vertices no grafo.
    int parent[V];                                      // Vetor que guarda a arvore minima.
    int key[V];
  
    // minHeap representa o conjunto de arestas
    struct MinHeap* minHeap = createMinHeap(V); 
  
    // Inicializa minHeap com todos os vertices.
    for (int v = 1; v < V; ++v) { 
        parent[v] = -1; 
        key[v] = INT_MAX; 
        minHeap->array[v] = newMinHeapNode(v, key[v]); 
        minHeap->pos[v] = v; 
    } 
  
    // Força a extraçao do primeiro no
    key[0] = 0; 
    minHeap->array[0] = newMinHeapNode(0, key[0]); 
    minHeap->pos[0] = 0; 
  
    // Tamanho inicial de minHeap 
    minHeap->size = V; 
  
    // Contem todos os nos fora da arvore
    while (!isEmpty(minHeap)) { 
        // Extrai o vertice de menor valor
        struct MinHeapNode* minHeapNode = extractMin(minHeap); 
        int u = minHeapNode->v;                     // Guarda a referencia do no extraido.
  
        // Procura em todos os vertices adjacentes ao extraido e atualiza seu valores
        Node* pCrawl = graph->list[u].head; 
        while (pCrawl != NULL) { 
            int v = pCrawl->dst; 
  
            // Verifica se v esta na arvore e atualiza, se necessario o valor do pai de v
            if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v]) { 
                key[v] = pCrawl->weight; 
                parent[v] = u; 
                decreaseKey(minHeap, v, key[v]); 
            } 
            pCrawl = pCrawl->next; 
        } 
    } 
  
    // Escreve no arquivo de saida a arvore minima 
    printArr(graph, parent, V, file); 
} 

