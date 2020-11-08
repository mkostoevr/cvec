// Copyright (c) 2015 Evan Teran
// Copyright (c) 2020 Magomed Kostoev
//
// You may use, distribute and modify this code under the terms of the MIT license.
//
// You should have received a copy of the MIT license with this file. If not, please visit
// https://opensource.org/licenses/MIT for full license details.

// cvec.h - std::vector (ish) implementation in C. Based on https://github.com/eteran/c-vector/.
//
// Unlike a real std::vector this one is implemented as a fat array, so metadata is placed inside
// an allocated buffer itself.
//
// Configuration (definitions):
// CVEC_TYPE:    Type of the vector's elements, after instantiation these functions will be visible
//               as cvec_<CVEC_TYPE>_funcname, so no stars and subscripting marks allowed - named
//               types only
// CVEC_INST:    Instantiate the functions if defined
// CVEC_LOGG:    Multiply capacity by CVEC_LOGG each expansion if defined (should be >= 1)
// CVEC_ASSERT:  Replacement for assert from <assert.h>
// CVEC_MALLOC:  Replacement for malloc from <stdlib.h>
// CVEC_REALLOC: Replacement for realloc from <stdlib.h>
// CVEC_FREE:    Replacement for free from <stdlib.h>
// CVEC_OOBH:    Out-of-bounds handler (gets __func__, vector data address and index of overflow)
// CVEC_OOBVAL:  Default value to return on out of bounds access
//
// Minimal definitions for declaration: CVEC_TYPE
// Minimal definitions for instantiation: CVEC_TYPE, CVEC_INST, CVEC_OOBVAL if the type object
// can't be represented by 0 value.
//
// WARNING: All used definitions will be undefined on header exit.
//
// Dependencies:
// <stddef.h> or another source of size_t and ptrdiff_t typedefs
// <stdlib.h> or another source of malloc, calloc and realloc
// <assert.h> or another source of assert

#ifndef CVEC_H_
#define CVEC_H_

//
// Input macros
//

#ifndef CVEC_LOGG
#   define CVEC_LOGG 1.5
#endif
#ifndef CVEC_ASSERT
#   define CVEC_ASSERT(x) assert(x)
#endif
#ifndef CVEC_MALLOC
#   define CVEC_MALLOC(size) malloc(size)
#endif
#ifndef CVEC_REALLOC
#   define CVEC_REALLOC(ptr, size) realloc(ptr, size)
#endif
#ifndef CVEC_FREE
#   define CVEC_FREE(size) free(size)
#endif
#ifndef CVEC_OOBH
#   define CVEC_OOBH(funcname, vec, index)
#endif
#ifndef CVEC_OOBVAL
#   define CVEC_OOBVAL { 0 }
#endif

//
// Internal macros (part 1)
//

#define CVEC_CONCAT2_IMPL(x, y) cvec_ ## x ## _ ## y
#define CVEC_CONCAT2(x, y) CVEC_CONCAT2_IMPL(x, y)

// Creates method name according to CVEC_TYPE
#define CVEC_FUN(name) CVEC_CONCAT2(CVEC_TYPE, name)

// Declares a function
#define CVEC_DECL(type, name, args) type CVEC_FUN(name) args

//
// External declarations
//

// @brief cvec_TYPE_new - Allocates new vector of specified capacity
// @param count - the capacity
// @return a pointer to the first element of the new vector
//
CVEC_DECL(CVEC_TYPE *, new, (size_t count));

// @brief cvec_TYPE_set_capacity - For internal use, sets the capacity variable of the vector
// @param vec - the vector
// @param size - the new capacity to set
// @return void
//
CVEC_DECL(void, set_capacity, (CVEC_TYPE **vec, size_t size));

// @brief cvec_TYPE_set_size - For internal use, sets the size variable of the vector
// @param vec - the vector
// @param size - the new capacity to set
// @return void
//
CVEC_DECL(void, set_size, (CVEC_TYPE **vec, size_t size));

// @brief cvec_TYPE_capacity - gets the current capacity of the vector
// @param vec - the vector
// @return the capacity as a size_t
//
CVEC_DECL(size_t, capacity, (CVEC_TYPE **vec));

// @brief cvec_TYPE_size - gets the current size of the vector
// @param vec - the vector
// @return the size as a size_t
//
CVEC_DECL(size_t, size, (CVEC_TYPE **vec));

// @brief cvec_TYPE_empty - returns non-zero if the vector is empty
// @param vec - the vector
// @return non-zero if empty, zero if non-empty
//
CVEC_DECL(int, empty, (CVEC_TYPE **vec));

// @brief cvec_TYPE_grow - For internal use, ensures that the vector is at least <count> elements
//                         big
// @param vec - the vector
// @param count - the new capacity to set
// @return void
//
CVEC_DECL(void, grow, (CVEC_TYPE **vec, size_t count));

// @brief cvec_TYPE_pop_back - removes the last element from the vector
// @param vec - the vector
// @return void
//
CVEC_DECL(void, pop_back, (CVEC_TYPE **vec));

// @brief cvec_TYPE_erase - removes the element at index i from the vector
// @param vec - the vector
// @param i - index of element to remove
// @return void
//
CVEC_DECL(void, erase, (CVEC_TYPE **vec, size_t i));

// @brief cvec_TYPE_free - frees all memory associated with the vector
// @param vec - the vector
// @return void
//
CVEC_DECL(void, free, (CVEC_TYPE **vec));

// @brief cvec_TYPE_begin - returns an iterator to first element of the vector
// @param vec - the vector
// @return a pointer to the first element (or NULL)
//
CVEC_DECL(CVEC_TYPE *, begin, (CVEC_TYPE **vec));

// @brief cvec_TYPE_end - returns an iterator to one past the last element of the vector
// @param vec - the vector
// @return a pointer to one past the last element (or NULL)
//
CVEC_DECL(CVEC_TYPE *, end, (CVEC_TYPE **vec));

// @brief cvec_TYPE_push_back - adds an element to the end of the vector
// @param vec - the vector
// @param value - the value to add
// @return void
//
CVEC_DECL(void, push_back, (CVEC_TYPE **vec, CVEC_TYPE value));

// @brief cvec_TYPE_at - get element with bounds checking (on out of bounds calls CVEC_OOBH if is
//                       defined and returns CVEC_OOBVAL)
// @param vec - the vector
// @param i - index
// @return element's value
//
CVEC_DECL(CVEC_TYPE, at, (CVEC_TYPE **vec, size_t i));

// @brief cvec_TYPE_at - increase the capacity of the vector to a value that's equal to new_cap
// @param vec - the vector
// @param new_cap - new capacity
// @return element's value
//
CVEC_DECL(void, reserve, (CVEC_TYPE **vec, size_t new_cap));

// @brief cvec_TYPE_shrink_to_fit - requests the removal of unused capacity
// @param vec - the vector
// @return void
//
CVEC_DECL(void, shrink_to_fit, (CVEC_TYPE **vec));

// @brief cvec_TYPE_assign_fill - replaces the contents with count copies of value value
// @param vec - the vector
// @param value - the value
// @return void
//
CVEC_DECL(void, assign_fill, (CVEC_TYPE **vec, size_t count, CVEC_TYPE value));

// @brief cvec_TYPE_assign_range - replaces the contents with data from range [first, last)
// @param vec - the vector
// @param first - range start
// @param last - range end
// @return void
//
CVEC_DECL(void, assign_range, (CVEC_TYPE **vec, CVEC_TYPE *first, CVEC_TYPE *last));

// @brief cvec_TYPE_data - direct access to buffer
// @param vec - the vector
// @return pointer to buffer
//
CVEC_DECL(CVEC_TYPE *, data, (CVEC_TYPE **vec));

// @brief cvec_TYPE_resize - resizes the container to contain count elements
// @param vec - the vector
// @param count - new size
// @return pointer to buffer
//
CVEC_DECL(void, resize, (CVEC_TYPE **vec, size_t new_size));

// @brief cvec_TYPE_resize - resizes the container to contain count elements, initializes new
//                           elements by value
// @param vec - the vector
// @param count - new size
// @param value - value to initialize new elements with
// @return pointer to buffer
//
CVEC_DECL(void, resize_v, (CVEC_TYPE **vec, size_t new_size, CVEC_TYPE value));

//
// Internal macros (part 2)
//

// Defines a function, __VA_ARGS__ is the function's body
#ifdef CVEC_INST
#   define CVEC_DEF(type, name, args, ...) type CVEC_FUN(name) args __VA_ARGS__
#else
#   define CVEC_DEF(type, name, args, ...)
#endif

// Calls a method
#define CVEC_CALL(name, ...) CVEC_FUN(name)(__VA_ARGS__)

//
// Function definitions
//

CVEC_DEF(CVEC_TYPE *, new, (size_t count), {
    const size_t cv_sz = count * sizeof(CVEC_TYPE) + sizeof(size_t) * 2;
    size_t *cv_p = CVEC_MALLOC(cv_sz);
    CVEC_ASSERT(cv_p);
    CVEC_TYPE *vec = (void *)(&cv_p[2]);
    CVEC_CALL(set_capacity, &vec, count);
    CVEC_CALL(set_size, &vec, 0);
    return vec;
})

CVEC_DEF(void, set_capacity, (CVEC_TYPE **vec, size_t size), {
    CVEC_ASSERT(vec);
    if (*vec) {
        ((size_t *)*vec)[-1] = size;
    }
})

CVEC_DEF(void, set_size, (CVEC_TYPE **vec, size_t size), {
    CVEC_ASSERT(vec);
    if (*vec) {
        ((size_t *)*vec)[-2] = size;
    }
})

CVEC_DEF(size_t, capacity, (CVEC_TYPE **vec), {
    CVEC_ASSERT(vec);
    return *vec ? ((size_t *)*vec)[-1] : (size_t)0;
})

CVEC_DEF(size_t, size, (CVEC_TYPE **vec), {
    CVEC_ASSERT(vec);
    return *vec ? ((size_t *)*vec)[-2] : (size_t)0;
})

CVEC_DEF(int, empty, (CVEC_TYPE **vec), {
    return CVEC_CALL(size, vec) == 0;
})

CVEC_DEF(void, grow, (CVEC_TYPE **vec, size_t count), {
    CVEC_ASSERT(vec);
    const size_t cv_sz = count * sizeof(**vec) + sizeof(size_t) * 2;
    size_t *cv_p1 = &((size_t *)*vec)[-2];
    size_t *cv_p2 = CVEC_REALLOC(cv_p1, (cv_sz));
    CVEC_ASSERT(cv_p2);
    *vec = (void *)(&cv_p2[2]);
    CVEC_CALL(set_capacity, vec, count);
})

CVEC_DEF(void, pop_back, (CVEC_TYPE **vec), {
    CVEC_CALL(set_size, vec, CVEC_CALL(size, vec) - 1);
})

CVEC_DEF(void, erase, (CVEC_TYPE **vec, size_t i), {
    CVEC_ASSERT(vec);
    if (*vec) {
        const size_t cv_sz = CVEC_CALL(size, vec);
        if (i < cv_sz) {
            CVEC_CALL(set_size, vec, cv_sz - 1);
            for (size_t cv_x = i; cv_x < (cv_sz - 1); ++cv_x) {
                (*vec)[cv_x] = (*vec)[cv_x + 1];
            }
        }
    }
})

CVEC_DEF(void, free, (CVEC_TYPE **vec), {
    CVEC_ASSERT(vec);
    if (*vec) {
        size_t *p1 = &((size_t *)*vec)[-2];
        CVEC_FREE(p1);
    }
})

CVEC_DEF(CVEC_TYPE *, begin, (CVEC_TYPE **vec), {
    CVEC_ASSERT(vec);
    return *vec;
})

CVEC_DEF(CVEC_TYPE *, end, (CVEC_TYPE **vec), {
    CVEC_ASSERT(vec);
    return *vec ? &((*vec)[CVEC_CALL(size, vec)]) : NULL;
})

CVEC_DEF(void, push_back, (CVEC_TYPE **vec, CVEC_TYPE value), {
    CVEC_ASSERT(vec);
    size_t cv_cap = CVEC_CALL(capacity, vec);
    if (cv_cap <= CVEC_CALL(size, vec)) {
        CVEC_CALL(grow, vec, cv_cap * CVEC_LOGG + 1);
    }
    (*vec)[CVEC_CALL(size, vec)] = value;
    CVEC_CALL(set_size, vec, CVEC_CALL(size, vec) + 1);
})

CVEC_DEF(CVEC_TYPE, at, (CVEC_TYPE **vec, size_t i), {
    CVEC_ASSERT(vec);
    if (i >= CVEC_CALL(size, vec) || i < 0) {
        CVEC_OOBH(__func__, vec, i);
        CVEC_TYPE ret = CVEC_OOBVAL;
        return ret;
    }
    return (*vec)[i];
})

CVEC_DEF(void, reserve, (CVEC_TYPE **vec, size_t new_cap), {
    if (new_cap <= CVEC_CALL(capacity, vec)) {
        return;
    }
    CVEC_CALL(grow, vec, new_cap);
})

CVEC_DEF(void, shrink_to_fit, (CVEC_TYPE **vec), {
    if (CVEC_CALL(capacity, vec) > CVEC_CALL(size, vec)) {
        CVEC_CALL(grow, vec, CVEC_CALL(size, vec));
    }
})

CVEC_DEF(void, assign_fill, (CVEC_TYPE **vec, size_t count, CVEC_TYPE value), {
    CVEC_ASSERT(vec);
    CVEC_CALL(reserve, vec, count);
    CVEC_CALL(set_size, vec, count); // If the buffer was bigger than new_cap, set size ourselves
    for (size_t i = 0; i < count; i++) {
        (*vec)[i] = value;
    }
})

CVEC_DEF(void, assign_range, (CVEC_TYPE **vec, CVEC_TYPE *first, CVEC_TYPE *last), {
    CVEC_ASSERT(vec);
    size_t new_size = ((ptrdiff_t)(last - first)) / sizeof(*first);
    CVEC_CALL(reserve, vec, new_size);
    CVEC_CALL(set_size, vec, new_size);
    size_t i = 0;
    for (CVEC_TYPE *it = first; it < last; it++, i++) {
        (*vec)[i] = *it;
    }
})

CVEC_DEF(CVEC_TYPE *, data, (CVEC_TYPE **vec), {
    CVEC_ASSERT(vec);
    return (*vec);
})

CVEC_DEF(void, resize, (CVEC_TYPE **vec, size_t count)) {
    CVEC_TYPE value = { 0 };
    CVEC_CALL(resize_v, vec, count, value);
}

CVEC_DEF(void, resize_v, (CVEC_TYPE **vec, size_t count, CVEC_TYPE value), {
    CVEC_ASSERT(vec);
    size_t old_size = CVEC_CALL(size, vec);
    CVEC_CALL(set_size, vec, count);
    if (CVEC_CALL(capacity, vec) < count) {
        CVEC_CALL(reserve, vec, count);
        for (CVEC_TYPE *it = (*vec) + old_size; it < CVEC_CALL(end, vec); it++) {
            *it = value;
        }
    }
})

#undef CVEC_TYPE

#ifdef CVEC_INST
#   undef CVEC_INST
#   ifdef CVEC_LOGG
#       undef CVEC_LOGG
#   endif
#   ifdef CVEC_OOBH
#       undef CVEC_OOBH
#   endif
#   ifdef CVEC_OOBVAL
#       undef CVEC_OOBVAL
#   endif
#endif


#undef CVEC_ASSERT
#undef CVEC_MALLOC
#undef CVEC_REALLOC
#undef CVEC_FREE

#undef CVEC_CONCAT2_IMPL
#undef CVEC_CONCAT2

#undef CVEC_FUN
#undef CVEC_CALL
#undef CVEC_DECL
#undef CVEC_DEF

#endif // CVEC_H_
