#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* createTree(const char* preorder);
void preorderTraversal(TreeNode* root);
void inorderTraversal(TreeNode* root);
void postorderTraversal(TreeNode* root);
int countLeaves(TreeNode* root);
void freeTree(TreeNode* root);

int main() {
    char preorder[100];
    scanf("%s", preorder);

    if (preorder[0] == '#') {
        printf("0\n");
        return 0;
    }

    TreeNode* root = createTree(preorder);

    preorderTraversal(root);
    printf("\n");
    inorderTraversal(root);
    printf("\n");
    postorderTraversal(root);
    printf("\n");

    // 叶子节点数
    printf("%d\n", countLeaves(root));

    freeTree(root);
    return 0;
}

// 构建二叉树
int idx = 0;  // 输入的先序序列的当前位置
TreeNode* createTree(const char* preorder) {
    if (preorder[idx] == '#' || preorder[idx] == '\0') {
        idx++;
        return NULL;
    }
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = preorder[idx++];
    node->left = createTree(preorder);
    node->right = createTree(preorder);
    return node;
}

// 先序
void preorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    printf("%c", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// 中序
void inorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%c", root->data);
    inorderTraversal(root->right);
}

// 后序
void postorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%c", root->data);
}

// 叶子节点数
int countLeaves(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

// 释放二叉树
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
