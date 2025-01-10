#include <stdio.h>
#include <stdlib.h>

#define MAXN 1010
#define MAXM 3030

// 边
typedef struct {
    int u, v, cost;
} Edge;

Edge edges[MAXM];
int parent[MAXN];  // 并查集 集合的父节点
int ranks[MAXN];   // 并查集 集合的树的高度
int n, m;          // 节点数，边数

// 边按成本升序
int cmp(const void *a, const void *b) {
    return ((Edge *)a)->cost - ((Edge *)b)->cost;
}

// 查找根节点
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// x和y所在集合合并
void union_set(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (ranks[rootX] < ranks[rootY]) {
            parent[rootX] = rootY;
        } else if (ranks[rootX] > ranks[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            ranks[rootX]++;
        }
    }
}

int kruskal() {
    int mst_cost = 0, edges_selected = 0;
    qsort(edges, m, sizeof(edges[0]), cmp);  // 边按成本升序
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        ranks[i] = 0;
    }
    for (int i = 0; i < m && edges_selected < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) != find(v)) {  // u v不在一个集合中
            union_set(u, v);       // 合并
            mst_cost += edges[i].cost;
            edges_selected++;
        }
    }
    if (edges_selected != n - 1) {
        return -1;  // 无法连接所有村落
    }
    return mst_cost;  // 总成本
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].cost);
        edges[i].u--;
        edges[i].v--;
    }
    int result = kruskal();
    printf("%d\n", result);
    return 0;
}
