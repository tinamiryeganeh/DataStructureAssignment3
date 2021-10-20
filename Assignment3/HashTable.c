// -------------------------------
// Operations supporting hash tables
// -------------------------------
#include <stdio.h>
#include"HashTable.h"

// -------------------------------
// Converts a 5 letter key into an integer
// CC###: ascii equivalent of letters and digits are simply added together.
// #####: ascii equivalent of digits are simply added together.
// -------------------------------
int convert( char key[5] )
{

 int convertedKey=0;
    
    for(int i=0; i<5; i++){
        // printf("key in convert function: %c\n", key[i]);
        // if(key[i]>='0' && key[i]<='9'){
            //convertedKey += key[i];
        // else if((key[i] >= 97 && key[i] <= 122) || (key[i] >= 65 && key[i] <= 90)){
            convertedKey += (int)key[i];
        //}
    }
    // printf("\nconverted key is: %d\n", convertedKey);
    return convertedKey;
}

// -------------------------------
// Hash function that returns an index into the hash table given a key
// use the module formula on page 263 of CLRS.
// -------------------------------
int hash( char key[5], int slots )
{

    int index;
    index = convert(key) % slots;
    return index;

}