// -------------------------------
// Dictionary ADT:
//I used some codes from Hou I Lin session.
// -------------------------------

#include <stdlib.h> // for built-in malloc that returns void *
#include <string.h>
#include <stdio.h>
#include "Dictionary.h"

// -------------------------------
// TODO: implement create
// create( *D, n ) -- creates a dictionary with n slots
// Initializes slots to n, and size to 0.
// -------------------------------

void create(dictionary *D, int n)
{
    // initialize the 'slots' and 'size' field

    // allocate memory for 'n' node_t structs and assignt to 'hash_table' field

    // loop over the 'n' elements
    // initialize 'value', 'next' , and 'prev' fields to 'NULL'
    // initialize the 'key' field of each node to a char string of size 5
    // HINT: can use something like this 'memcpy( D->hash_table[i].key, "", 5 );'
    D->slots = n;
    D->size = 0;
    D->hash_table = (node_t *)calloc(n, sizeof(node_t));
    for (int i = 0; i < n; i++)
    {
        memcpy(D->hash_table[i].key, "", 5);
        D->hash_table[i].value = NULL;
        D->hash_table[i].next = NULL;
        D->hash_table[i].prev = NULL;
    }
}

// -------------------------------
// TODO: implement insert
// insert( *D, *e ) -- inserts element e->key:e->value into the dictionary.
// First, make sure that e->key does not exist in *D yet.
// If it does, return an error code of -1.
// Otherwise, update the size of *D, and return 0.
// -------------------------------

int insert(dictionary *D, element *e)
{
    // check if element's key already in dictionary
    int index;
    // if not:
    if (!find(D, e->key))
    {
        node_t *newNode = (node_t *)malloc(sizeof(node_t));
        memcpy(newNode->key, e->key, 5);
        newNode->value = e->value;
        newNode->next = NULL;
        newNode->prev = NULL;
        index = hash(e->key, D->slots);
        // printf("index in insert function = %d\n", index);
        node_t *head = &(D->hash_table[index]);
        
        while (head->next != NULL)
        {
            head = head->next;
        }
        head->next = newNode;
        newNode->prev = head;
        // while (head->next != NULL)
        //  {
        //      insertList(&head, newNode);
        //  }
        D->size++;
        return 0;
    }
    return -1;

    //calculate the index by hash and convert with e->key
    // for (int i = 0; i < dict->len; i++) {
    //     if (!strcmp(dict->entry[i], key)) {
    //         return i;
    //     }
    // }
}

// -------------------------------
// TODO: implement delete
// delete( *D, *key ) -- deletes element with key (*key) from the dictionary.
// If *key does not exist in *D, return an error code of -1.
// Update the size of *D, and return 0.
// -------------------------------

int delete (dictionary *D, char *key)
{
    // check if node with *key is in dictionary

    // if key exists, navigate to the node that has such key
    // remove the node from the list
    // NOTE: again, this is same logic as in deleting a node
    // but do NOT use delete method from List.c
    node_t *founded = find(D, key);

    if (!founded){
         printf("This course doesn't exist\n");
        return -1;
    }else{
    
    deleteList(&D->hash_table ,founded);
        
    D->size--; 
    return 0;  
    }
}

// -------------------------------
// TODO: implement find
// find( D, k ) -- returns pointer to node whose key is *k from dictionary *D.
// If *k is not found in *D, then return NULL.
// -------------------------------

node_t *find(dictionary *D, char *k)
{
    // hash key to get index and then loop over the list at that index
    // to find node with same key
    // NOTE: you can use the findList method from List.c but need to
    // distinguish between the case when it returns the node with key
    // or just the sentinel head of the list at that index of the dict
    int index = hash(k, D->slots);

    node_t *head = &(D->hash_table[index]);
    node_t* node = findList(head,k);
    // while (head->next != NULL)
    // {
    //     if (strncmp(head->next->key, k, 5) == 0)
    //         return head->next->value;
    //     head = head->next;
    // }
    // printf("In find function No %s in the index %d\n", k, index);
    // printf("Key is in find function: %s\n", node->key);
    if(node == NULL){
        return NULL;
    } 
    return node;
}

// -------------------------------
// TODO: implement print
// print( dictionary *D ) -- prints the dictionary.
// Specifically, it looks at the non-empty slots of the hash table,
// and prints the key field of each node in the list.
// -------------------------------

void print(dictionary *D)
{
    node_t *head;
    for (int i = 0; i < D->slots; i++)
    {
        head = &(D->hash_table[i]);
        if (head->next != NULL)
        {
            printList(head->next);
        }
    }
}
