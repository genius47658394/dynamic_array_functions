#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vec.h"

VECTOR_DEFINE(int)

int main() {
    vec_int vec = vec_int_init_empty();

    for (int i = 0; i < 10; i++)
        vec_int_push(&vec, i);

    vec_int_print(&vec);

    int a = vec_int_pop(&vec);

    printf("%d\n", a);

    vec_int_print(&vec);

    vec_int_free(&vec);

    return 0;
}
