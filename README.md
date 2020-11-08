# cvec - partial `std::vector` implementation in C.
## Not full implementation of [std::vector](https://en.cppreference.com/w/cpp/container/vector/reserve).

Member functions table:

| Status | Name | Function |
| :---: | --- | --- |
| :heavy_check_mark: | (constructor) | new |
| :heavy_check_mark: | (destructor) | free |
| :heavy_minus_sign: | operator= |  |
| :x: | assign |  |
| :heavy_minus_sign: | get_allocator |  |
| :heavy_check_mark: | at | at |
| :heavy_check_mark: | operator[] | [] |
| :x: | front | front |
| :x: | back | back |
| :x: | data |  |
| :heavy_check_mark: | begin |  |
| :x: | cbegin |  |
| :heavy_check_mark: | end |  |
| :x: | cend |  |
| :x: | rbegin |  |
| :x: | crbegin |  |
| :x: | rend |  |
| :x: | crend |  |
| :heavy_check_mark: | empty |  |
| :heavy_check_mark: | size |  |
| :x: | max_size |  |
| :heavy_check_mark: | reserve |  |
| :heavy_check_mark: | capacity |  |
| :heavy_check_mark: | shrink_to_fit |  |
| :x: | clear |  |
| :x: | insert |  |
| :x: | emplace |  |
| :heavy_check_mark: | erase |  |
| :heavy_check_mark: | push_back |  |
| :x: | emplace_back |  |
| :heavy_check_mark: | pop_back |  |
| :x: | resize |  |
| :x: | swap |  |

## Easy to use

To use the std::vector implementation for specified type they should be declared as follows:

```C
#define CVEC_TYPE TypeOfVectorElement
#include "cvec.h"

// ...

    TypeOfVectorElement *vec = cvec_TypeOfVectorElement_new(128);
    
    cvec_TypeOfVectorElement_push_back(&vec, value);
```

Also somewhere in the project the functinos should be instantiated as follows:

```C
#define CVEC_TYPE TypeOfVectorElement
#define CVEC_INST
#include "cvec.h"
```

## Allows using of custom allocators.

```C
#define CVEC_TYPE pchar
#define CVEC_INST
#define CVEC_MALLOC custom_malloc
#define CVEC_REALLOC custom_realloc
#define CVEC_FREE custom_free
#include "cvec.h"
```

## Allows handling of exceptional cases.

```C
#define CVEC_TYPE pchar
#define CVEC_INST
// Set Out Of Bounds handler
#define CVEC_OOBH(funcname, vec, index) printf("Out of bounds in %s (vec = %p, i = %d)", funcname, vec, index); abort();
#include "cvec.h"
```

## Has no fixed dependencies

Every function it uses may be overridden. More information about dependencies in [cvec.h](cvec.h).
