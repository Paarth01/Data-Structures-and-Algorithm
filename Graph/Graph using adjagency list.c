#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure to represent the graph
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

// Structure to represent a queue for BFS
typedef struct Queue {
    int* items;
    int front, rear, size, capacity;
} Queue;

// Function to create a node
Node* createNode(int vertex) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Function to add an edge
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to delete an edge
void deleteEdge(Graph* graph, int src, int dest) {
    Node* temp = graph->adjLists[src];
    Node* prev = NULL;

    // Find and remove dest in src's list
    while (temp != NULL && temp->vertex != dest) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL) {
        if (prev == NULL)
            graph->adjLists[src] = temp->next;
        else
            prev->next = temp->next;
        free(temp);
    }

    // Repeat for src in dest's list
    temp = graph->adjLists[dest];
    prev = NULL;
    while (temp != NULL && temp->vertex != src) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL) {
        if (prev == NULL)
            graph->adjLists[dest] = temp->next;
        else
            prev->next = temp->next;
        free(temp);
    }
}

// Function to delete a vertex
void deleteVertex(Graph* graph, int vertex) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (i != vertex) {
            deleteEdge(graph, i, vertex);
        }
    }

    Node* temp = graph->adjLists[vertex];
    while (temp != NULL) {
        Node* toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    graph->adjLists[vertex] = NULL;
}

// DFS recursive helper function
void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    Node* adjList = graph->adjLists[vertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->vertex;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        adjList = adjList->next;
    }
}

// BFS queue functions
Queue* createQueue(int capacity) {
    Queue* queue = malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->items = malloc(capacity * sizeof(int));
    return queue;
}

int isEmpty(Queue* queue) {
    return queue->size == 0;
}

void enqueue(Queue* queue, int item) {
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->items[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue* queue) {
    int item = queue->items[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

void BFS(Graph* graph, int startVertex) {
    Queue* queue = createQueue(graph->numVertices);
    graph->visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        Node* adjList = graph->adjLists[currentVertex];
        while (adjList != NULL) {
            int connectedVertex = adjList->vertex;
            if (graph->visited[connectedVertex] == 0) {
                graph->visited[connectedVertex] = 1;
                enqueue(queue, connectedVertex);
            }
            adjList = adjList->next;
        }
    }

    free(queue->items);
    free(queue);
}

// Menu-driven program
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Add Edge\n");
    printf("2. Delete Edge\n");
    printf("3. Delete Vertex\n");
    printf("4. Perform DFS\n");
    printf("5. Perform BFS\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int vertices, choice, src, dest, startVertex;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    Graph* graph = createGraph(vertices);

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter source and destination of the edge: ");
            scanf("%d %d", &src, &dest);
            addEdge(graph, src, dest);
            break;

        case 2:
            printf("Enter source and destination of the edge to delete: ");
            scanf("%d %d", &src, &dest);
            deleteEdge(graph, src, dest);
            break;

        case 3:
            printf("Enter the vertex to delete: ");
            scanf("%d", &src);
            deleteVertex(graph, src);
            break;

        case 4:
            printf("Enter the starting vertex for DFS: ");
            scanf("%d", &startVertex);
            for (int i = 0; i < vertices; i++) graph->visited[i] = 0;
            printf("DFS Traversal: ");
            DFS(graph, startVertex);
            printf("\n");
            break;

        case 5:
            printf("Enter the starting vertex for BFS: ");
            scanf("%d", &startVertex);
            for (int i = 0; i < vertices; i++) graph->visited[i] = 0;
            printf("BFS Traversal: ");
            BFS(graph, startVertex);
            printf("\n");
            break;

        case 6:
            printf("Exiting program.\n");
            for (int i = 0; i < vertices; i++) {
                Node* adjList = graph->adjLists[i];
                while (adjList != NULL) {
                    Node* temp = adjList;
                    adjList = adjList->next;
                    free(temp);
                }
            }
            free(graph->adjLists);
            free(graph->visited);
            free(graph);
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}