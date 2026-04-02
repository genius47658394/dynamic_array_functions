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
            Header *header = malloc(sizeof(int) * 1 + sizeof(Header));                  \
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
        if (arr == nullptr) {                                                  \
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


#define arr_free(arr) free((Header*)(arr) - 1)


#define arr_foreach(arr, var, block)                            \
    for (size_t i_ = 0; i_ < arr_len(arr); ++i_) {              \
        typeof(*(arr)) var = (arr)[i_];                         \
        block;                                                  \
    }
