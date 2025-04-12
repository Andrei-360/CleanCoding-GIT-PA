#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

// Utils
Node *create_node(int v) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(int vertices, int edges, Graph *graph) {
    int src, dest;
    printf("Adauga %d muchii (nodurile de la 0 la %d):\n", edges, vertices - 1);
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

int is_empty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int data) {
    Node *new_node = create_node(data);
    if (*queue == NULL) {
        *queue = new_node;
    } else {
        Node *temp = *queue;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

int dequeue(Node **queue) {
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void wipe_visited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

void DFS(Graph *graph, int vertex) {
    Node *adj_list = graph->adjacency_lists[vertex];
    Node *temp = adj_list;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0)
            DFS(graph, connected_vertex);
        temp = temp->next;
    }
}

void BFS(Graph *graph, int start) {
    Node *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node *temp = graph->adjacency_lists[current];
        while (temp) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int vertices, edges, start;

    printf("Cate noduri are graful? ");
    scanf("%d", &vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &edges);

    Graph *graph = create_graph(vertices);
    insert_edges(vertices, edges, graph);

    printf("Nod start DFS: ");
    scanf("%d", &start);
    printf("DFS: ");
    DFS(graph, start);

    wipe_visited(graph);

    printf("\nNod start BFS: ");
    scanf("%d", &start);
    printf("BFS: ");
    BFS(graph, start);

    printf("\n");
    return 0;
}
