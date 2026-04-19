#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*
 * USAGE: just write VECTOR_DEFINE(type)
 *      and type must be your type
 *      then u`ll get vector as in c++
 *
 * vec_init_empty() initialise vec empty
 * vec_init_with_capacity(size_t capacity) initialise vec with some capacity
 * vec_free(vec* vector) free the vec
 *
 * vec_reserve(vec* vector, size_t new_cap) reserve new memory for vec
 * vec_shrink_to_fir(vec* vector) resize capacity to real size of vec
 *
 * vec_push(vec* vector, element) push to the end of the array your element, see example to understand
 * vec_pop(vec* vector) remove element from the end of vec and return it
 *
 * vec_get_checked\unchecked(vec* vector, size_t index) i think understandable what is it functions do
 *
 * vec_set(vec* vector, size_t index, element) set the element on position of index without check capacity
 * vec_insert(vec* vector, size_t index, element) do vec_set but check capacity and resize vec
 *
 * vec_erase(vec* vector, size_t index) remove the element on position of index
 *
 * vec_begin(vec* vector) pointer to the start of vec
 * vec_end(vec* vector) pointer to the end of vec
 *
 * vec_print(vec* vector) prints the vec as array in python
 *
 * vec_sort(vec* vector, int cmp) wrapper on qsort
 * vec_search(vec* vector, *key, int cmp) wrapper on bsearch
 */

#define PRINT_FMT(T) _Generic( (T){0},  \
    int: "%d",                          \
    char: "%c",                         \
    float: "%f",                        \
    double: "%lf",                      \
    default: "%p"                       \
)

#define VECTOR_DEFINE(T)                                                                                \
    typedef struct {                                                                                    \
        T* data;                                                                                        \
        size_t capacity;                                                                                \
        size_t size;                                                                                    \
    } vec_##T;                                                                                          \
                                                                                                        \
    vec_##T vec_##T##_init_empty(void) {                                                                \
        return (vec_##T){NULL, 0, 0};                                                                   \
    }                                                                                                   \
                                                                                                        \
    vec_##T vec_##T##_init_with_capacity(size_t cap) {                                                  \
        vec_##T v;                                                                                      \
        v.capacity = cap;                                                                               \
        v.size = 0;                                                                                     \
        if (cap == 0) {                                                                                 \
            v.data = NULL;                                                                              \
        } else {                                                                                        \
            v.data = malloc(cap * sizeof(T));                                                           \
            if (v.data == NULL) {                                                                       \
                perror("malloc failed in init_with_capacity");                                          \
                exit(5);                                                                                \
            }                                                                                           \
        }                                                                                               \
        return v;                                                                                       \
    }                                                                                                   \
                                                                                                        \
    void vec_##T##_free(vec_##T* vec) {                                                                 \
        free(vec->data);                                                                                \
        vec->data = NULL;                                                                               \
        vec->capacity = 0;                                                                              \
        vec->size = 0;                                                                                  \
    }                                                                                                   \
                                                                                                        \
    void vec_##T##_reserve(vec_##T* vec, size_t new_cap) {                                              \
        if (new_cap <= vec->capacity) return;                                                           \
        T* new_data = realloc(vec->data, new_cap * sizeof(T));                                          \
        if (new_data == NULL) {                                                                         \
            perror("realloc failed in reserve");                                                        \
            exit(5);                                                                                    \
        }                                                                                               \
        vec->data = new_data;                                                                           \
        vec->capacity = new_cap;                                                                        \
    }                                                                                                   \
                                                                                                        \
    void vec_##T##_shrink_to_fit(vec_##T* vec) {                                                        \
        if (vec->size == vec->capacity) return;                                                         \
        if (vec->size == 0) {                                                                           \
            free(vec->data);                                                                            \
            vec->data = NULL;                                                                           \
            vec->capacity = 0;                                                                          \
            return;                                                                                     \
        }                                                                                               \
        T* new_data = realloc(vec->data, vec->size * sizeof(T));                                        \
        if (new_data == NULL) {                                                                         \
            perror("realloc failed in shrink_to_fit");                                                  \
            exit(5);                                                                                    \
        }                                                                                               \
        vec->data = new_data;                                                                           \
        vec->capacity = vec->size;                                                                      \
    }                                                                                                   \
                                                                                                        \
    void vec_##T##_push(vec_##T* vec, T val) {                                                          \
        if (vec->capacity == 0) {                                                                       \
            vec_##T##_reserve(vec, 2);                                                                  \
        } else if (vec->size == vec->capacity) {                                                        \
            vec_##T##_reserve(vec, vec->capacity * 2);                                                  \
        }                                                                                               \
        vec->data[vec->size++] = val;                                                                   \
    }                                                                                                   \
                                                                                                        \
    T vec_##T##_pop(vec_##T* vec) {                                                                     \
        assert(vec->size > 0 && "pop from empty vector");                                               \
        return vec->data[--vec->size];                                                                  \
    }                                                                                                   \
                                                                                                        \
    T vec_##T##_get_unchecked(vec_##T* vec, size_t idx) {                                               \
        return vec->data[idx];                                                                          \
    }                                                                                                   \
                                                                                                        \
    T vec_##T##_get(vec_##T* vec, size_t idx) {                                                         \
        assert(idx < vec->size && "index out of range");                                                \
        return vec->data[idx];                                                                          \
    }                                                                                                                                                                               \
                                                                                                        \
    void vec_##T##_set(vec_##T* vec, size_t idx, T val) {                                               \
        assert(idx < vec->size && "index out of range in set");                                         \
        vec->data[idx] = val;                                                                           \
    }                                                                                                   \
                                                                                                        \
    void vec_##T##_insert(vec_##T* vec, size_t index, T val) {                                          \
        assert(index <= vec->size && "insert index out of range");                                      \
        if (vec->size == vec->capacity) {                                                               \
            vec_##T##_reserve(vec, vec->capacity == 0 ? 2 : vec->capacity * 2);                         \
        }                                                                                               \
        memmove(vec->data + index + 1, vec->data + index, (vec->size - index) * sizeof(T));             \
        vec->data[index] = val;                                                                         \
        vec->size++;                                                                                    \
    }                                                                                                   \
                                                                                                        \
    void vec_##T##_erase(vec_##T* vec, size_t index) {                                                  \
        assert(index < vec->size && "erase index out of range");                                        \
        memmove(vec->data + index, vec->data + index + 1, (vec->size - index - 1) * sizeof(T));         \
        vec->size--;                                                                                    \
    }                                                                                                   \
                                                                                                        \
    T* vec_##T##_begin(vec_##T* vec) { return vec->data; }                                              \
    T* vec_##T##_end(vec_##T* vec)   { return vec->data + vec->size; }                                  \
                                                                                                        \
    void vec_##T##_print(vec_##T* vec) {                                                                \
        printf("[ ");                                                                                   \
        for (size_t i = 0; i < vec->size; ++i) {                                                        \
            printf(PRINT_FMT(T), vec->data[i]);                                                         \
            if (i != vec->size - 1) printf(", ");                                                       \
        }                                                                                               \
        printf(" ]\n");                                                                                 \
    }                                                                                                   \
                                                                                                        \
    void vec_##T##_sort(vec_##T* vec, int (*cmp)(const void*, const void*)) {                           \
        qsort(vec->data, vec->size, sizeof(T), cmp);                                                    \
    }                                                                                                   \
                                                                                                        \
    T* vec_##T##_binary_search(vec_##T* vec, const T* key, int (*cmp)(const void*, const void*)) {      \
        return bsearch(key, vec->data, vec->size, sizeof(T), cmp);                                      \
    }
