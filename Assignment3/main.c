#include <stdlib.h> // for built-in malloc that returns void *
#include <string.h>
#include <stdio.h>
#include "Dictionary.h"

typedef struct main
{
    char key[5];
    int *value;
} course_element;

int main(){

int number[3] = {1, 2, 3};
dictionary D;
create(&D, 10);
printf("slots= %d\n\n", D.slots);

char key0[6] = "11111\0";
char key1[6] = "22222\0";
char key2[6] = "33333\0";
course_element* ce = (course_element*) malloc(sizeof(course_element));


memcpy(ce ->key, key0, 5);
ce->value = &number[0];
insert(&D, (element*)ce);

int* a = find(&D, ce->key);
printf("The number is %d\n", *a);
a = find(&D, key1);
if(a != NULL)
    printf("the number is %d\n", *a);
course_element* ce2 = (course_element*) malloc(sizeof(course_element));
memcpy(ce2 ->key, key1, 5);
ce2 -> value = &number[1];
insert(&D, (element*) ce2);

a= find(&D, key1);
if(a != NULL)
    printf("The number id %d\n", *a);

// test: changing the value in the dictionary
*a = 3;
int* b = find(&D, key1);
if(b != NULL)
    printf("The number is %d\n", *b);

return 0;

}
