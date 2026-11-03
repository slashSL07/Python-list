#include "list.h"

list initlist(BYTES *bytes_arr, size_t *b_sizes, int elements)
{
  list l;
  int total_size = 0;
  for (int i = 0; i < elements; i++)
  {
    total_size += b_sizes[i];
  }

  l.len = total_size;
  BYTES t_bytes = malloc(total_size);
  size_t *b_offset = malloc((elements + 1) * sizeof(size_t));
  memset(b_offset, 0, (elements + 1) * sizeof(size_t));
  for (int k = 1; k <= elements; k++)
  {
    b_offset[k] = b_offset[k - 1] + b_sizes[k - 1];
  }

  int j = 0;

  while (j < elements)
  {
    memcpy(t_bytes + b_offset[j], bytes_arr[j], b_sizes[j]);
    j++;
  }

  l.offset = elements;
  l.max_len = total_size;
  l.bytes = t_bytes;
  l.byte_offset = b_offset;
  l.maxoffset = elements;
  return l;
}
bool push(list *lis, BYTES *bytes_arr, size_t *b_sizes, int elements)
{
  // checks if the list is destroyed
  if (lis->len == -1)
    return false;

  // code
  size_t total_size = lis->len;
  for (int i = 0; i < elements; i++)
  {
    total_size += b_sizes[i];
  }
  if (lis->max_len <= total_size && lis->maxoffset <= lis->offset + elements)
  {

    lis->len = total_size;
    lis->max_len = 2 * total_size;
    BYTES t_bytes = realloc(lis->bytes, 2 * total_size);
    size_t *b_offset = realloc(
        lis->byte_offset, 2 * ((elements + 1) * sizeof(size_t) + lis->offset * sizeof(size_t)));
    memset(b_offset + lis->offset + 1, 0,
           (2 * (elements + 1) * sizeof(size_t) + (lis->offset - 1) * sizeof(size_t)));
    for (int k = lis->offset + 1; k <= (lis->offset + elements); k++)
    {
      int j = (k - (lis->offset + 1));
      b_offset[k] = b_offset[k - 1] + b_sizes[j];
    }
    int i = 0;
    while (i < elements)
    {
      memcpy(t_bytes + b_offset[i + lis->offset], bytes_arr[i], b_sizes[i]);
      i++;
    }
    lis->maxoffset = 2 * (elements + 1) + lis->offset;
    lis->offset += elements;
    lis->bytes = t_bytes;
    lis->byte_offset = b_offset;
  }
  else
  {

    lis->len = total_size;
    for (int k = lis->offset + 1; k <= (lis->offset + elements); k++)
    {
      int j = (k - (lis->offset + 1));
      lis->byte_offset[k] = lis->byte_offset[k - 1] + b_sizes[j];
    }
    int i = 0;
    while (i < elements)
    {
      memcpy(lis->bytes + lis->byte_offset[i + lis->offset], bytes_arr[i], b_sizes[i]);
      i++;
    }
    lis->offset += elements;
  }
  return true;
}
bool pop(list *lis, void *store)
{
  // checks if the list is destroyed
  if (lis->len == -1)
    return false;

  // code
  memcpy(store, lis->bytes + lis->byte_offset[lis->offset - 1],
         (lis->byte_offset[lis->offset] - lis->byte_offset[lis->offset - 1]));
  lis->len -= (lis->byte_offset[lis->offset] - lis->byte_offset[lis->offset - 1]);
  lis->offset--;
  return true;
}
bool get(list *lis, int index, void *store)
{
  // checks if the list is destroyed
  if (lis->len == -1)
    return false;

  // out of index check
  if (index >= lis->offset || index < 0)
  {
    store = NULL;
    return false;
  }
  // code
  memcpy(store, lis->bytes + lis->byte_offset[index],
         (lis->byte_offset[index + 1] - lis->byte_offset[index]));

  return true;
}

bool set(list *lis, BYTES bytes, size_t b_size, int index)
{
  // checks if the list is destroyed
  if (lis->len == -1)
    return false;

  // index check
  if (index >= lis->offset || index < 0)
    return false;

  // code
  size_t total_size = b_size + lis->len - (lis->byte_offset[index + 1] - lis->byte_offset[index]);
  if (total_size < lis->max_len)
  {

    BYTES t_bytes = malloc(total_size);
    // copies bytes to t_bytes
    memcpy(t_bytes, lis->bytes, lis->byte_offset[index]);
    memcpy((t_bytes + lis->byte_offset[index]), bytes, b_size);

    memcpy(t_bytes + (lis->byte_offset[index] + b_size), lis->bytes + lis->byte_offset[index + 1],
           lis->len - lis->byte_offset[index + 1]);

    memcpy(lis->bytes, t_bytes, total_size);

    // modifies b_offset

    size_t *temsizes = malloc((lis->offset) * sizeof(size_t));
    for (int j = 0; j <= index; j++)
    {
      temsizes[j] = lis->byte_offset[j];
    }

    temsizes[index + 1] = b_size + temsizes[index];
    for (int i = (index + 2); i <= lis->offset; i++)
    {
      temsizes[i] = temsizes[i - 1] + (lis->byte_offset[i] - lis->byte_offset[i - 1]);
    }

    memcpy(lis->byte_offset, temsizes, (lis->offset + 1) * sizeof(size_t));

    lis->len = total_size;

    free(t_bytes);
    free(temsizes);
  }
  else
  {
    // reallocates bytes
    lis->bytes = realloc(lis->bytes, 2 * total_size);
    BYTES t_bytes = malloc(total_size);
    // copies bytes to t_bytes
    memcpy(t_bytes, lis->bytes, lis->byte_offset[index]);
    memcpy((t_bytes + lis->byte_offset[index]), bytes, b_size);

    memcpy(t_bytes + (lis->byte_offset[index] + b_size), lis->bytes + lis->byte_offset[index + 1],
           lis->len - lis->byte_offset[index + 1]);

    memcpy(lis->bytes, t_bytes, total_size);

    // modifies b_offset

    size_t *temsizes = malloc((lis->offset) * sizeof(size_t));
    for (int j = 0; j <= index; j++)
    {
      temsizes[j] = lis->byte_offset[j];
    }

    temsizes[index + 1] = b_size + temsizes[index];
    for (int i = (index + 2); i <= lis->offset; i++)
    {
      temsizes[i] = temsizes[i - 1] + (lis->byte_offset[i] - lis->byte_offset[i - 1]);
    }

    memcpy(lis->byte_offset, temsizes, (lis->offset + 1) * sizeof(size_t));

    lis->len = total_size;
    lis->max_len = 2 * total_size;

    free(t_bytes);
    free(temsizes);
  }
  return true;
}

bool del(list *lis, int index)
{
  // checks if list is destoryed
  if (lis->len == -1)
    return false;

  // index check
  if (index >= lis->offset || index < 0)
    return false;

  // code

  // seting bytes
  size_t newsize = lis->len - (lis->byte_offset[index + 1] - lis->byte_offset[index]);
  BYTES t_bytes = malloc(newsize);
  memcpy(t_bytes, lis->bytes, lis->byte_offset[index]); // working

  memcpy(t_bytes + lis->byte_offset[index], lis->bytes + lis->byte_offset[index + 1],
         (lis->len - lis->byte_offset[index + 1]));

  memcpy(lis->bytes, t_bytes, newsize);

  // seting size
  size_t *tempsize = malloc((lis->offset - 1) * sizeof(size_t));
  memcpy(tempsize, lis->byte_offset, (index + 1) * sizeof(size_t));

  for (int i = index + 1; i < lis->offset; i++)
  {
    tempsize[i] = tempsize[i - 1] + (lis->byte_offset[i + 1] - lis->byte_offset[i]);
  }
  memcpy(lis->byte_offset, tempsize, (lis->offset) * sizeof(size_t));
  lis->byte_offset[lis->offset] = 0;
  lis->offset -= 1;
  lis->len = newsize;
  free(tempsize);
  free(t_bytes);
  return true;
}
bool add(list *lis, BYTES *bytes_arr, size_t *b_sizes, int elements, int index)
{
  // checks if list is destroyed
  if (lis->len == -1)
    return false;
  // index check
  if (index >= lis->offset || index < 0)
    return false;

  size_t size_sum = 0;
  for (int i = 0; i < elements; i++)
  {
    size_sum += b_sizes[i];
  }
  if (lis->max_len > (size_sum + lis->len) && lis->maxoffset > lis->offset + elements)
  {

    // set bytes
    BYTES t_bytes = malloc(size_sum + lis->len);
    memcpy(t_bytes, lis->bytes, lis->byte_offset[index]);
    memcpy(t_bytes + lis->byte_offset[index], bytes_arr[0], b_sizes[0]);
    for (int i = 1; i < elements; i++)
    {
      memcpy(t_bytes + lis->byte_offset[index] + b_sizes[i - 1], bytes_arr[i], b_sizes[i]);
    }
    memcpy(t_bytes + lis->byte_offset[index] + size_sum, lis->bytes + lis->byte_offset[index],
           lis->len - lis->byte_offset[index]);
    memcpy(lis->bytes, t_bytes, lis->len + size_sum);

    free(t_bytes);

    // set size
    size_t *tempsize = malloc((lis->offset + elements + 1) * sizeof(size_t));
    memcpy(tempsize, lis->byte_offset, (index + 1) * sizeof(size_t));
    for (int j = 1; j <= elements; j++)
    {

      tempsize[index + j] = tempsize[(index + j - 1)] + b_sizes[j - 1];
    }
    for (int k = index + 1; k <= lis->offset; k++)
    {
      tempsize[k + elements] =
          tempsize[k + elements - 1] + (lis->byte_offset[k] - lis->byte_offset[k - 1]);
    }
    memcpy(lis->byte_offset, tempsize, (lis->offset + elements + 1) * sizeof(size_t));
    free(tempsize);
  }
  else
  {
    // set bytes
    BYTES t_bytes = malloc(size_sum + lis->len);
    memcpy(t_bytes, lis->bytes, lis->byte_offset[index]);
    memcpy(t_bytes + lis->byte_offset[index], bytes_arr[0], b_sizes[0]);
    for (int i = 1; i < elements; i++)
    {
      memcpy(t_bytes + lis->byte_offset[index] + b_sizes[i - 1], bytes_arr[i], b_sizes[i]);
    }
    memcpy(t_bytes + lis->byte_offset[index] + size_sum, lis->bytes + lis->byte_offset[index],
           lis->len - lis->byte_offset[index]);
    lis->bytes = realloc(lis->bytes, 2 * (lis->max_len + size_sum));
    memcpy(lis->bytes, t_bytes, lis->len + size_sum);

    free(t_bytes);

    // set size
    size_t *tempsize = malloc((lis->offset + elements + 1) * sizeof(size_t));
    memcpy(tempsize, lis->byte_offset, (index + 1) * sizeof(size_t));
    for (int j = 1; j <= elements; j++)
    {

      tempsize[index + j] = tempsize[(index + j - 1)] + b_sizes[j - 1];
    }
    for (int k = index + 1; k <= lis->offset; k++)
    {
      tempsize[k + elements] =
          tempsize[k + elements - 1] + (lis->byte_offset[k] - lis->byte_offset[k - 1]);
    }
    lis->byte_offset = realloc(lis->byte_offset, 2 * (lis->maxoffset + elements) * sizeof(size_t));
    memcpy(lis->byte_offset, tempsize, (lis->offset + elements + 1) * sizeof(size_t));
    free(tempsize);
    lis->max_len = 2 * (lis->max_len + size_sum);
    lis->maxoffset = 2 * (lis->maxoffset + elements);
  }
  lis->len += size_sum;
  lis->offset += elements;
  return true;
}

bool destroylist(list *lis)
{
  lis->len = -1;
  lis->offset = 0;
  lis->max_len = 0;
  free(lis->byte_offset);
  free(lis->bytes);
  lis->byte_offset = NULL;
  lis->bytes = NULL;
  return true;
}
