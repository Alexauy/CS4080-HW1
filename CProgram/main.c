//
// Created by 16194 on 2/5/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node { //using typedef lets us simply write Node instead of struct Node
    struct Node *prev;
    char *data; //this points to the string
    struct Node *next;
} Node;

Node* find(Node *head, char *data) {
    Node *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data, data) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void insert(Node **head, Node *after, char *data) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = malloc(strlen(data) + 1);
    strcpy(new_node->data, data);

    new_node->prev = NULL;
    new_node->next = NULL;

    if (after == NULL) { //inserting at the front
        Node *temp = *head;
        new_node->next = temp;
        if (temp != NULL) {
            temp->prev = new_node;
        }
        *head = new_node;
    }else {
        Node *temp = after->next;
        new_node->next = temp;
        new_node->prev = after;
        if (temp != NULL) {
            temp->prev = new_node;
        }
        after->next = new_node;
    }
}

void delete(Node **head, Node *selection){
    if (selection == NULL || head == NULL || *head == NULL) {
        return; //if node doesn't exist, just do nothing
    }

    if (selection->prev != NULL) {
        selection->prev->next = selection->next;
    }else {
        *head = selection->next;
    }

    if (selection->next != NULL) {
        selection->next->prev = selection->prev;
    }

    free(selection->data);
    free(selection);

}

void dump(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%s\n", temp->data);
        temp = temp->next;
    }
}

int main() {
    printf("Hello, World!\n");

    Node* head = NULL;

    insert(&head, NULL, "is"); //if NULL insert at the front
    insert(&head, NULL, "hi");
    insert(&head, find(head, "hi"), "it"); //insert 'it' after 'hi'
    insert(&head, find(head, "is"), "me");

    dump(head);

    printf("\n---------Deleted hi----------\n");
    delete(&head, find(head, "hi"));
    dump(head);

    return 0;
}
