#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    char val;
    struct TreeNode* left, * right;
} TreeNode;

TreeNode* createTree(const char* preorder);
bool findPath(TreeNode* root, char x, int path[], int* pathIndex);

int main() {
    char preorder[100];
    int x;
    int path[100];
    int pathIndex = 0;

    scanf("%s", preorder);
    scanf(" %c", &x); // 空格跳过换行

    TreeNode* root = createTree(preorder);

    if (findPath(root, x, path, &pathIndex)) {// 查找路径
        for (int i = 0; i < pathIndex; i++) // 输出路径
            printf("%c ", path[i]);
        putchar('\n');
    } else printf("404\n");
    return 0;
}

// 构建二叉树
int idx = 0;// 输入的先序序列的当前位置
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

// 递归查找路径的函数
bool findPath(TreeNode* root, char x, int path[], int* pathIndex) {
    if (root == NULL) return false;
    path[(*pathIndex)++] = root->val;// 当前节点值添加到路径
    if (root->val == x) return true;// 到达目标节点

    // 递归检查左右子树
    if (findPath(root->left, x, path, pathIndex) ||
        findPath(root->right, x, path, pathIndex)) {
        return true;
    }
    (*pathIndex)--;// 没找到，回溯
    return false;
}
