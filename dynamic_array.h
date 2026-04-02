//
// Created by kucer on 02.04.2026.
//

#pragma once

#include <stdio.h>
#include <stdlib.h>

// to understand how it works, watch: https://www.youtube.com/watch?v=gtk3RZHwJUA

typedef struct {
    size_t size;
    size_t capacity;
} Header;


#define arr_push(arr, x)                                                                \
    do {                                                                                \
        if (arr == NULL) {                                                              \
            Header *header = malloc(sizeof(*(arr)) * 1 + sizeof(Header));               \
                                                                                        \
            header->size = 0;                                                           \
            header->capacity = 1;                                                       \
                                                                                        \
            arr = (void*) (header + 1);                                                 \
        }                                                                               \
                                                                                        \
        Header *header = (Header *) (arr) - 1;                                          \
        if (header->size >= header->capacity) {                                         \
            header->capacity *= 2;                                                      \
                                                                                        \
            header = realloc(header, sizeof(*arr) * header->capacity + sizeof(Header)); \
                                                                                        \
            if (header == NULL) {                                                       \
                printf("Error: can`t realloc");                                         \
                break;                                                                  \
            }                                                                           \
                                                                                        \
            arr = (void*) (header + 1);                                                 \
        }                                                                               \
        (arr)[header->size++] = x;                                                      \
    } while(0)


#define arr_pop(arr, out)                                                      \
    do {                                                                       \
        if (arr == NULL) {                                                     \
            fprintf(stderr, "arr_pop: array is NULL\n");                       \
            break;                                                             \
        }                                                                      \
        Header *header = (Header*)(arr) - 1;                                   \
        if (header->size == 0) {                                               \
            fprintf(stderr, "arr_pop: array is empty\n");                      \
            break;                                                             \
        }                                                                      \
        header->size--;                                                        \
        (out) = (arr)[header->size];                                           \
    } while(0)


#define arr_len(arr) ((Header *) (arr) - 1)->size


#define arr_capacity(arr) ((Header *) (arr) - 1)->capacity


#define arr_free(arr) free((Header*)(arr) - 1)


#define arr_insert(arr, idx, val)                                                 \
    do {                                                                          \
        size_t len = arr_len(arr);                                                \
        if ((idx) > len) {                                                        \
            fprintf(stderr, "arr_insert: index out of range\n");                  \
            break;                                                                \
        }                                                                         \
        if (len + 1 > arr_capacity(arr)) {                                        \
            Header *header = (Header*)(arr) - 1;                                  \
            size_t new_cap = header->capacity ? header->capacity * 2 : 1;         \
            header = realloc(header, sizeof(*(arr)) * new_cap + sizeof(Header));  \
            if (header == NULL) {                                                 \
                fprintf(stderr, "arr_insert: realloc failed\n");                  \
                break;                                                            \
            }                                                                     \
            header->capacity = new_cap;                                           \
            arr = (void*)(header + 1);                                            \
        }                                                                         \
        Header *header = (Header*)(arr) - 1;                                      \
        for (size_t i = header->size; i > (idx); i--)                             \
            (arr)[i] = (arr)[i-1];                                                \
        (arr)[idx] = (val);                                                       \
        header->size++;                                                           \
    } while(0)


#if __STDC_VERSION__ >= 202311L
    #define arr_foreach(arr, var, block)                            \
        for (size_t i_ = 0; i_ < arr_len(arr); ++i_) {              \
            typeof(*(arr)) var = (arr)[i_];                         \
            block;                                                  \
        }
#else
    #define arr_foreach(arr, idx_var) \
        for (size_t idx_var = 0; idx_var < arr_len(arr); ++idx_var)
#endif