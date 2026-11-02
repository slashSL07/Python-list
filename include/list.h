#ifndef list_h
#define list_h

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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

list initlist(BYTES *bytes_arr, size_t *b_sizes, int elements);
bool push(list *lis, BYTES *bytes_arr, size_t *b_sizes, int elements);
bool pop(list *lis, void *store);
bool get(list *lis, int index, void *store);
bool set(list *lis, BYTES bytes, size_t b_size, int index);
bool add(list *lis, BYTES *bytes_arr, size_t *b_sizes, int elements, int index);
bool del(list *lis, int index);
bool destroylist(list *lis);
#endif // !list_h
