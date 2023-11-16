#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char val;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* createTree(const char* preorder);
bool dfs(TreeNode* root, char x, int path[], int* pathIndex);
void freeTree(TreeNode* root);

int main() {
    char preorder[100];
    int x;          // 目标节点
    int path[100];  // 路径
    int pathIndex = 0;

    scanf("%s", preorder);
    scanf(" %c", &x);  // 空格跳过换行

    TreeNode* root = createTree(preorder);

    if (dfs(root, x, path, &pathIndex)) {    // 查找路径
        for (int i = 0; i < pathIndex; i++)  // 输出路径
            printf("%c ", path[i]);
        putchar('\n');
    } else
        printf("404\n");
    freeTree(root);
    return 0;
}

// 构建二叉树
int idx = 0;  // 输入的先序序列的当前位置
TreeNode* createTree(const char* preorder) {
    if (preorder[idx] == '#') {
        idx++;
        return NULL;
    }
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = preorder[idx++];
    node->left = createTree(preorder);
    node->right = createTree(preorder);
    return node;
}

// 搜索路径
bool dfs(TreeNode* root, char x, int path[], int* pathIndex) {
    if (root == NULL) return false;
    path[(*pathIndex)++] = root->val;  // 记录当前节点值
    if (root->val == x) return true;   // 到达目标节点

    // 搜索检查左右子树
    if (dfs(root->left, x, path, pathIndex) ||
        dfs(root->right, x, path, pathIndex))
        return true;
    (*pathIndex)--;  // 没找到，回溯
    return false;
}

// 释放二叉树
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}