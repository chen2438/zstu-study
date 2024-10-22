#include <stdio.h>
#include <stdlib.h>

// 邻接表节点定义
typedef struct AdjListNode {
    int vertex;  // 顶点编号
    struct AdjListNode* next;
} AdjListNode;

// 邻接表定义
typedef struct AdjList {
    AdjListNode* head;  // 链表头节点
} AdjList;

// 图的定义
typedef struct Graph {
    int n;           // 顶点数
    AdjList* array;  // 邻接表数组
} Graph;

// 创建邻接表节点
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->vertex = dest;
    newNode->next = NULL;
    return newNode;
}

// 创建图
Graph* createGraph(int n) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->n = n;
    // 创建邻接表
    graph->array = (AdjList*)malloc(n * sizeof(AdjList));
    // 初始化邻接表表项的头节点
    for (int i = 0; i < n; i++) graph->array[i].head = NULL;
    return graph;
}

// 添加边到无向图
void addEdge(Graph* graph, int src, int dest) {
    // src->dest，头插法
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // dest->src
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// 顶点的度
void printDegrees(Graph* graph, int n) {
    for (int v = 0; v < n; v++) {  // 遍历邻接表
        AdjListNode* temp = graph->array[v].head;
        int degree = 0;
        while (temp) {
            degree++;
            temp = temp->next;
        }
        printf("%d", degree);
        if (v < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char vertices[n];
    scanf("%s", vertices);

    Graph* graph = createGraph(n);

    for (int i = 0; i < m; i++) {
        char src, dest;
        scanf(" %c %c", &src, &dest);
        addEdge(graph, src - 'A', dest - 'A');
    }

    printDegrees(graph, n);

    // 清理内存
    for (int i = 0; i < n; i++) {
        AdjListNode* current = graph->array[i].head;
        while (current != NULL) {
            AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}
