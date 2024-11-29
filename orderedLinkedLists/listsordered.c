#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char * name;
    int age;
    char gender;
} Person;

typedef struct Node {
    Person data;
    struct Node *next;
} Node;


int insertOrdered(Node **head, Person data);
int deleteName(Node **head, char *name);
int deleteAtBeginning(Node **head);
int deleteAtEnd(Node **head);
int deleteAtPosition(Node **head, int position);
Node *searchName(Node *head, char *name);
Node *searchNameOrdered(Node *head, char *name);
void printList(Node *head);
void printNodeAtPosition(Node *head, int position);
int clearList(Node **head);

int insertOrdered(Node **head, Person data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return -1; // Memory allocation failed
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL || strcmp((*head)->data.name, data.name) > 0) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL && strcmp(current->next->data.name, data.name) < 0) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    return 0; // Success
}

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("Name: %s, Age: %d, Gender: %c\n", current->data.name, current->data.age, current->data.gender);
        current = current->next;
    }
}

int main() {
    Node *head = NULL;
    Person p1 = {"Bob", 25, 'F'};
    Person p2 = {"Alice", 30, 'M'};
    Person p3 = {"John", 35, 'M'};
    Person p4 = {"Charles", 40, 'M'};
    Person p5 = {"Eve", 45, 'F'};

    insertOrdered(&head, p1);
    insertOrdered(&head, p2); 
    insertOrdered(&head, p3);
    insertOrdered(&head, p4);
    insertOrdered(&head, p5);
    printList(head);

    return 0;
}