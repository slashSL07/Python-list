#ifndef list_h
#define list_h

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

//type BYTES: expands as unsigned char* 
typedef unsigned char *BYTES;

typedef struct
{
  BYTES bytes;
  size_t len;
  size_t max_len;
  size_t *byte_offset;
  int offset;
  int maxoffset;

} list;

 /*intializes list 
  * bytes_arr: takes the elements as an array of BYTES 
  * b_sizes: a size_t array contianing the sizes in bytes of each of those elements(should be in order)
  * elements: number of elements
  *(returns false if fails)*/
list initlist(BYTES *bytes_arr, size_t *b_sizes, int elements);

 /*adds elements to the end of list 
  * lis: takes the pointer to the list where the elements needs to be pushed
  * bytes_arr: takes the elements as an array of BYTES, 
  * b_sizes: a size_t array contianing the sizes in bytes of each of those elements(should be in order)
  * elements: number of elements
  *(returns false if fails)*/
bool push(list *lis, BYTES *bytes_arr, size_t *b_sizes, int elements);

 /*pops the last element of the list and stores the value in store
  * lis: takes the pointer to the list from where the element is poped
  * store: takes a pointer to the variable where the value is to be stored
  *(returns false if fails)*/
bool pop(list *lis, void *store);

 /*retrives the element from the index provided and stores its copy in store  
  * lis: takes the pointer to the list where the element is stored
  *index: index of the element in the list
  * store: takes a pointer to the variable where the value is to be stored
  *(returns false if fails)*/
bool get(list *lis, int index, void *store);

 /*replaces the value of the given element on the list  
  * lis: takes the pointer to the list where the element is stored
  *bytes: takes the variable that replaces the value given element as BYTES
  *b_size: takes the size of bytes provided
  *index: index of the element in the list
  *(returns false if fails)*/
bool set(list *lis, BYTES bytes, size_t b_size, int index);

 /*deletes an element from the list 
  * lis: takes the pointer to the list from where the element needs to be deleted
  *index: index of the element in the list
  *(returns false if fails)*/
bool del(list *lis, int index);

 /*adds elements to the list from the provided index
  * lis: takes the pointer to the list where the elements needs to be added
  * bytes_arr: takes the elements as an array of BYTES, 
  * b_sizes: a size_t array contianing the sizes in bytes of each of those elements(should be in order)
  * elements: number of elements
  *index: the index from which the provided elements should be added to the list
  *(returns false if fails)*/
bool add(list *lis, BYTES *bytes_arr, size_t *b_sizes, int elements, int index);

/*destroys the list
*lis: takes pointer to the list that needs to be destoyed
*(returns true if executes sucessfully)
NOTE: do not use the list after it is destoryed*/
bool destroylist(list *lis);

#endif // !list_h
