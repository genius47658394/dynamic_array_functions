//
// Created by kucer on 19.04.2026.
//

#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t count;
    size_t capacity;
} Header;

#define ARR_INIT_CAPACITY 2

#define arr_header(arr)       ((Header*)(arr) - 1)
#define arr_len(arr)          (arr_header(arr)->count)
#define arr_capacity(arr)     (arr_header(arr)->capacity)

#define arr_free(arr)         free(arr_header(arr))

#define arr_free_and_null(arr) do { \
    arr_free(arr); \
    (arr) = NULL; \
} while(0)

#define arr_reserve(arr, new_cap) do { \
    if ((arr) == NULL) { \
        Header *h_ = malloc(sizeof(*(arr)) * (new_cap) + sizeof(Header)); \
        assert(h_ != NULL); \
        h_->count = 0; \
        h_->capacity = (new_cap); \
        (arr) = (void*)(h_ + 1); \
    } else { \
        Header *h_ = arr_header(arr); \
        if (h_->capacity < (new_cap)) { \
            h_ = realloc(h_, sizeof(*(arr)) * (new_cap) + sizeof(Header)); \
            assert(h_ != NULL); \
            h_->capacity = (new_cap); \
            (arr) = (void*)(h_ + 1); \
        } \
    } \
} while(0)

#define arr_push(arr, x) do { \
    if ((arr) == NULL) { \
        arr_reserve(arr, ARR_INIT_CAPACITY); \
    } else { \
        Header *h_ = arr_header(arr); \
        if (h_->count >= h_->capacity) { \
            arr_reserve(arr, h_->capacity * 2); \
        } \
    } \
    Header *h_ = arr_header(arr); \
    (arr)[h_->count++] = (x); \
} while(0)

#define arr_pop(arr) ( \
    assert((arr) != NULL && arr_len(arr) > 0), \
    (arr)[--arr_header(arr)->count] \
)

#define arr_insert(arr, index, x) do { \
    size_t len_ = (arr) ? arr_len(arr) : 0; \
    assert((index) <= len_); \
    if ((arr) == NULL || len_ >= arr_capacity(arr)) { \
        arr_reserve(arr, (arr) ? arr_capacity(arr)*2 : ARR_INIT_CAPACITY); \
    } \
    Header *h_ = arr_header(arr); \
    memmove(&(arr)[(index)+1], &(arr)[index], (len_ - (index)) * sizeof(*(arr))); \
    (arr)[index] = (x); \
    h_->count++; \
} while(0)

#define arr_erase(arr, index) do { \
    size_t len_ = arr_len(arr); \
    assert((index) < len_); \
    Header *h_ = arr_header(arr); \
    memmove(&(arr)[index], &(arr)[(index)+1], (len_ - (index) - 1) * sizeof(*(arr))); \
    h_->count--; \
} while(0)

#define arr_shrink_to_fit(arr) do { \
    if ((arr) == NULL) break; \
    Header *h_ = arr_header(arr); \
    if (h_->count == 0) { \
        free(h_); \
        (arr) = NULL; \
    } else if (h_->count < h_->capacity) { \
        h_ = realloc(h_, sizeof(*(arr)) * h_->count + sizeof(Header)); \
        assert(h_ != NULL); \
        h_->capacity = h_->count; \
        (arr) = (void*)(h_ + 1); \
    } \
} while(0)

#define arr_foreach(arr, elem) \
    for (size_t _i = 0; _i < arr_len(arr) && ((elem) = (arr)[_i], 1); ++_i)

#define arr_sort(arr, cmp) do { \
    if ((arr) != NULL) { \
        qsort((arr), arr_len(arr), sizeof(*(arr)), (cmp)); \
    } \
} while(0)

#define arr_bsearch(arr, key, cmp) \
    bsearch((key), (arr), arr_len(arr), sizeof(*(arr)), (cmp))
