#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createLinkedList(int n) {
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = num;
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {  // 尾插法
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

void traverseLinkedList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 方法一
Node* reverseLinkedListMethod1(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;            // 反转当前节点
        prev = current, current = next;  // 两个指针前进一次
    }
    return prev;  // 反转后的链表的头节点
}

// 方法二
Node* reverseLinkedListMethod2(Node* head) {
    if (head == NULL || head->next == NULL) return head;  // 只有0或1个节点
    Node* newHead = reverseLinkedListMethod2(head->next);  // 反转剩余部分
    head->next->next = head;                               // 反转头节点
    head->next = NULL;
    return newHead;
}

void destroyLinkedList(Node* head) {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int n;
        scanf("%d", &n);
        Node* head = createLinkedList(n);
        // head = reverseLinkedListMethod1(head);  // 方法一
        head = reverseLinkedListMethod2(head);  // 方法二
        traverseLinkedList(head);
        destroyLinkedList(head);
    }
    return 0;
}
