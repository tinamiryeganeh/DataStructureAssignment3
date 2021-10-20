#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// -----------------------------
// Returns ptr to node with matching key, else returns NULL
// -----------------------------
node_t *findList(node_t *head, char *key)
{
    node_t *ptr;

    ptr = head;
    while (ptr != NULL)
    {
        if (strcmp(ptr->key, key) == 0)
            break;
        else
            ptr = ptr->next;
    }
    return (ptr);
}

// -----------------------------
// Returns ptr to node with matching key, else returns NULL
// -----------------------------
void insertList(node_t **head, node_t *new)
{
    // insert new node as head of list
    if (*head == NULL)
    {
        *head = new;
        (*head)->next = NULL;
        (*head)->prev = NULL;
    }
    else
    {
        new->next = *head;
        (*head)->prev = new;
        new->prev = NULL;
        *head = new;
    }
}

// -----------------------------
// Deletes node pointed to by del from the list.
// You can assume that del points to a node in the list.
// -----------------------------
void deleteList(node_t **head, node_t *del)
{
    node_t* traveler = *head;
    if (traveler == NULL || del == NULL)
    {
        printf("List Error: calling deleteList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    while(traveler != NULL && traveler != del){
        traveler = (traveler)->next; 
    }
    if (traveler == del)
    {
        (traveler)->next = del->next;
        del->next->prev = traveler;
        free(del);
        del = NULL;
    }
    else
    {
        del->prev->next = del->next;
        if (del->next != NULL)
        {
            del->next->prev = del->prev;
       }
    }
    
    return;
}

// -----------------------------
// Prints key field of each node in the list starting at head.
// -----------------------------
void printList(node_t *head)
{

    // if (head->key >= 48 || head->key <= 57)
    // {
    //     while (head != NULL)
    //     {
    //         printf("%d", head->key);
    //         head = head->next;
    //     }
    // }
    // else
    // {
    while (head != NULL)
    {
        printf("       >>Printing List>>     ");
        printf("%s\n", head->key);
        head = head->next;
    }
    // }
    printf("\n");
}