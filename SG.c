#include <stdio.h> 
#include <stdlib.h>

// Node structure for adjacency list
typedef struct Node
{
int vertex;
 struct Node* next;
} Node;

// Graph structure
typedef struct Graph
{
 int numVertices;
 Node** adjLists;
 int* visited;
} Graph;

// Queue structure for BFS
typedef struct Queue
{
 int* items;
 int front, rear, size, capacity;
} Queue;

// Function prototypes
Graph* createGraph(int vertices);
Node* createNode(int vertex);
void addEdge(Graph* graph, int src, int dest);
void removeEdge(Graph* graph, int src, int dest);
void DFS(Graph* graph, int startVertex);
void BFS(Graph* graph, int startVertex);
void displayGraph(Graph* graph);
Queue* createQueue(int capacity);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int isQueueEmpty(Queue* queue);

int main() 
{
int vertices, choice, src, dest, startVertex;
printf("Enter the number of vertices: ");
scanf("%d", &vertices);
Graph* graph = createGraph(vertices);
while (1) 
{
 printf("\nMenu:\n");
 printf("1. Add Edge\n");
 printf("2. Remove Edge\n");
 printf("3. Perform DFS\n");
 printf("4. Perform BFS\n");
 printf("5. Display Graph\n");
 printf("6. Exit\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
int i;
 switch (choice)
 {
 case 1:
 printf("Enter source and destination vertices to add an edge: ");
 scanf("%d %d", &src, &dest);
 addEdge(graph, src, dest);
break;
case 2:
printf("Enter source and destination vertices to remove an edge: ");
 scanf("%d %d", &src, &dest);
removeEdge(graph, src, dest);
 break;
case 3:
 printf("Enter the starting vertex for DFS: ");
scanf("%d", &startVertex);
for ( i = 0; i < vertices; i++)
 graph->visited[i] = 0; // Reset visited
 DFS(graph, startVertex);
 break;
case 4:
/* printf("Enter the starting vertex for BFS: ");
 scanf("%d", &startVertex);
 BFS(graph, startVertex);
 break;*/
 printf("Enter the starting vertex for BFS: ");
scanf("%d", &startVertex);
for (i = 0; i < graph->numVertices; i++)
graph->visited[i] = 0; // Reset visited array
BFS(graph, startVertex);
break;
case 5:
 displayGraph(graph);
 break;
 case 6:
 printf("Exiting program.\n");
 exit(0);
 default:
 printf("Invalid choice! Try again.\n");
 }
 }

return 0;
}

// Create a graph with the specified number of vertices
Graph* createGraph(int vertices)
 {
 Graph* graph = (Graph*)malloc(sizeof(Graph));
graph->numVertices = vertices;
graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
 graph->visited = (int*)malloc(vertices * sizeof(int));
int i;
for ( i = 0; i < vertices; i++)
 {
 graph->adjLists[i] = NULL;
graph->visited[i] = 0;
}

return graph;
}

// Create a new node
Node* createNode(int vertex)
{
Node* newNode = (Node*)malloc(sizeof(Node));
 newNode->vertex = vertex;
 newNode->next = NULL;
 return newNode;
}

// Add an edge to the graph
void addEdge(Graph* graph, int src, int dest) 
{
 Node* newNode = createNode(dest);
 newNode->next = graph->adjLists[src];
 graph->adjLists[src] = newNode;

newNode = createNode(src);
newNode->next = graph->adjLists[dest];
 graph->adjLists[dest] = newNode;

 printf("Edge added between %d and %d.\n", src, dest);
}

// Remove an edge from the graph
void removeEdge(Graph* graph, int src, int dest) 
{
Node* temp = graph->adjLists[src];
Node* prev = NULL;
    while (temp != NULL && temp->vertex != dest)
 {
prev = temp;
 temp = temp->next;
 }

 if (temp != NULL) 
{
 if (prev != NULL) 
        {
prev->next = temp->next;
 } 
       else 
	   {
 graph->adjLists[src] = temp->next;
 }
free(temp);
 }

 temp = graph->adjLists[dest];
 prev = NULL;

while (temp!=NULL && temp->vertex != src) 
    {
 prev = temp;
 temp = temp->next;
 }

 if (temp!= NULL) 
    {
 if (prev != NULL)
          {
prev->next = temp->next;
 } 
         else 
		 {
 graph->adjLists[dest] = temp->next;
 }
free(temp);
 }

 printf("Edge removed between %d and %d.\n", src, dest);
}

// Perform DFS on the graph
void DFS(Graph* graph, int startVertex) 
{
graph->visited[startVertex] = 1;
 printf("%d ", startVertex);

Node* temp = graph->adjLists[startVertex];
 while (temp) 
    {
 int connectedVertex = temp->vertex;
 if (!graph->visited[connectedVertex])
        {
 DFS(graph, connectedVertex);
  }
 temp = temp->next;
 }
}


// Perform BFS on the graph
void BFS(Graph* graph, int startVertex)
 {
 Queue* queue = createQueue(graph->numVertices);
 graph->visited[startVertex] = 1;
 enqueue(queue, startVertex);

 while (!isQueueEmpty(queue))
  {
 int currentVertex = dequeue(queue);
 printf("%d ", currentVertex);

 Node* temp = graph->adjLists[currentVertex];
while (temp)
   {
 int connectedVertex = temp->vertex;
 if (!graph->visited[connectedVertex]) 
  {
 graph->visited[connectedVertex] = 1;
 enqueue(queue, connectedVertex);
 }
 temp = temp->next;
 }
 }
     free(queue->items);
free(queue);
}

// Display the graph
void displayGraph(Graph* graph) 
{
int i;
 for ( i = 0; i < graph->numVertices; i++) 
{
 Node* temp = graph->adjLists[i];
 printf("Vertex %d: ", i);
while (temp) {
printf("%d -> ", temp->vertex);
temp = temp->next;
}
 printf("NULL\n");
 }
}

// Create a queue
Queue* createQueue(int capacity)
 {
 Queue* queue = (Queue*)malloc(sizeof(Queue));
 queue->items = (int*)malloc(capacity * sizeof(int));
 queue->front = 0;
queue->rear = -1;
queue->size = 0;
 queue->capacity = capacity;
return queue;
}

// Enqueue a value
void enqueue(Queue* queue, int value)
 {
if (queue->size == queue->capacity) return;
queue->rear = (queue->rear + 1) % queue->capacity;
queue->items[queue->rear] = value;
 queue->size++;
}

// Dequeue a value
int dequeue(Queue* queue) 
{
 if (isQueueEmpty(queue)) return -1;
 int item = queue->items[queue->front];
 queue->front = (queue->front + 1) % queue->capacity;
queue->size--;
 return item;
}

// Check if the queue is empty
int isQueueEmpty(Queue* queue) 
{
return queue->size == 0;
}