# Python List

A C library that implements a dynamic array inspired by Python's list. It can store values of different types by treating each element as raw bytes.

## Features

- Append, insert, retrieve, replace, and delete elements
- Store elements of different sizes and types
- Manage a dynamically sized list

## How it works

The library uses `BYTES` (`unsigned char *`) for element data. When adding or replacing values, provide the size of each value in bytes. The `list` type represents the list; its internal fields are managed by the library.

## API

Include `list.h` to use the library.

| Function | Description |
| --- | --- |
| `initlist(bytes_arr, b_sizes, elements)` | Initialize a list with elements |
| `push(lis, bytes_arr, b_sizes, elements)` | Append elements |
| `pop(lis, store)` | Remove the last element and copy it to `store` |
| `get(lis, index, store)` | Copy an element to `store` |
| `set(lis, bytes, b_size, index)` | Replace an element |
| `del(lis, index)` | Delete an element |
| `add(lis, bytes_arr, b_sizes, elements, index)` | Insert elements at an index |
| `destroylist(lis)` | Release the list's resources |

Functions that return `bool` indicate whether the operation succeeded.

## Example

```c
#include <stdio.h>
#include "list.h"

int main(void)
{
    int first = 10;
    int second = 20;

    BYTES values[] = {
        (BYTES)&first,
        (BYTES)&second
    };
    size_t sizes[] = {
        sizeof(first),
        sizeof(second)
    };

    list numbers = initlist(values, sizes, 2);

    int value;
    if (get(&numbers, 1, &value)) {
        printf("%d\n", value); // 20
    }

    destroylist(&numbers);
    return 0;
}
```

## Notes

- Pass the correct byte size for every element.
- `get` and `pop` copy element data into the provided `store`; make sure it has enough space.
- Do not use a list after calling `destroylist`.
  
**##Additional NOTES**
the lib file is compiled for windows but feel free to compile it for your OS using the src/list.c file

## License

See the [LICENSE](LICENSE) file.
