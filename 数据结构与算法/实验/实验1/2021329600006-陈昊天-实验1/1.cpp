#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createLinkedList() {
    Node* head = NULL;
    int num;
    scanf("%d", &num);
    while (num != -1) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = num;
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
        } else {  // 头插法
            newNode->next = head;
            head = newNode;
        }
        scanf("%d", &num);
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
    Node* head = createLinkedList();
    traverseLinkedList(head);
    destroyLinkedList(head);
    return 0;
}
