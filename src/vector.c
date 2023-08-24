#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "unity.h"

typedef void *vector_t;

#define DATA_OFFSET        (offsetof(struct vector_metadata, data))
#define HEAD_SIZE          DATA_OFFSET
#define DATA_TO_META(data) ((struct vector_metadata *)((char *)data - DATA_OFFSET))

struct vector_metadata {
    uint64_t allocated;
    uint64_t used;
    char data[];
};

static inline struct vector_metadata *prv_realloc(struct vector_metadata *meta, int new_size)
{
    // Assumes size checking is done by the caller
    return (struct vector_metadata *)realloc(meta, new_size);
}

vector_t vector_create()
{
    struct vector_metadata *meta = malloc(sizeof(struct vector_metadata));

    meta->allocated = 0;
    meta->used      = 0;

    return meta->data;
}

#define vector_push_back(vec, data) \
    ({ \
        __typeof__(*vec) temp = data; \
        (__typeof__(*vec) *)prv_vector_insert(vec, vector_len(vec), &temp, sizeof(temp)); \
    })

#define vector_insert(vec, pos, data) \
    ({ \
        __typeof__(*vec) temp = data; \
        (__typeof__(*vec) *)prv_vector_insert(vec, pos, &temp, sizeof(temp)); \
    })

#define vector_pop_back(vec) \
    ({ \
        __typeof__(*vec) temp = vec[vector_len(vec) - 1]; \
        vector_rm(vec, vector_len(vec) - 1) \
    })

#define vector_rm(vec, pos) prv_vector_rm(vec, pos, sizeof(*vec))

vector_t prv_vector_insert(vector_t vec, uint64_t pos, void *data, size_t size)
{
    struct vector_metadata *meta = DATA_TO_META(vec);
    struct vector_metadata *temp = NULL;
    if (meta->allocated == meta->used) {
        uint64_t allocd = meta->allocated++;
        temp            = prv_realloc(meta, HEAD_SIZE + meta->allocated * size);
        assert(temp != NULL);
        meta = temp;
    }
    memmove(
        meta->data + (pos + 1) * size, // Destination address: the next data
        meta->data + (pos)*size,       // Source address: the data@(pos)
        (meta->used - pos) * size);    // Number of data being moved: total data - position
    memmove(meta->data + size * pos, data, size);
    meta->used++;
    return (vector_t)meta->data;
}

void prv_vector_rm(vector_t vec, uint64_t pos, size_t size)
{
    struct vector_metadata *meta = DATA_TO_META(vec);
    assert(meta->used - pos >= 0);
    memmove(
        meta->data + (pos)*size,        // Destination address
        meta->data + (pos + 1) * size,  // Source address: the next data
        (meta->used - pos - 1) * size); // Number of data being moved: total data - position - missing data
    meta->used--;
}

size_t vector_size(vector_t vec)
{
    struct vector_metadata *meta = DATA_TO_META(vec);
    return meta->allocated;
}

size_t vector_len(vector_t vec)
{
    struct vector_metadata *meta = DATA_TO_META(vec);
    return meta->used;
}

vector_t vector_shrink_to_fit(vector_t vec)
{
    struct vector_metadata *meta = DATA_TO_META(vec);
    meta                         = prv_realloc(meta, HEAD_SIZE + meta->used);
    meta->allocated              = meta->used;
    return meta;
}

void vector_destroy(vector_t vec)
{
    struct vector_metadata *meta = DATA_TO_META(vec);
    free(meta);
}

#include <stdio.h>
#include <time.h>
#define STRESS_TEST 0
struct point {
    int x;
    int y;
};
int main()
{
#if STRESS_TEST == 0
    int *vector = vector_create();
    vector      = vector_push_back(vector, 00);
    vector      = vector_push_back(vector, 10);
    vector      = vector_push_back(vector, 20);
    vector      = vector_push_back(vector, 40);
    vector      = vector_push_back(vector, 50);

    printf("Original vector\n");
    printf("vector_len: %ld\n", vector_len(vector));
    for (size_t i = 0; i < vector_len(vector); i++) {
        printf("%d ", vector[i]);
    }
    putchar('\n');
    putchar('\n');

    printf("Insert 30 at pos-3\n");
    vector = vector_insert(vector, 3, 30);
    for (size_t i = 0; i < vector_len(vector); i++) {
        printf("%d ", vector[i]);
    }
    putchar('\n');
    putchar('\n');

    printf("Deleting vector[0]\n");
    vector_rm(vector, 0);
    for (size_t i = 0; i < vector_len(vector); i++) {
        printf("%d ", vector[i]);
    }
    putchar('\n');
    putchar('\n');

    printf("Deleting vector[1]\n");
    vector_rm(vector, 1);
    for (size_t i = 0; i < vector_len(vector); i++) {
        printf("%d ", vector[i]);
    }
    putchar('\n');
    putchar('\n');

    printf("vector size: %lu \n", vector_size(vector));
    vector_shrink_to_fit(vector);
    printf("vector size after shrink: %lu \n", vector_size(vector));

    vector_destroy(vector);
#else
    int tgt_size = INT32_MAX / 8;
    int *pointv  = vector_create();

    {
        clock_t begin = clock();
        for (unsigned int i = 0; i < tgt_size; i++)
            pointv = vector_push_back(pointv, 1);
        clock_t end       = clock();
        double time_spent = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
        printf("Time spent vector_push_back: %f ms\n", time_spent);
    }

    {
        printf("point vector_len: %ld\n", vector_len(pointv));
        clock_t begin = clock();
        vector_rm(pointv, 0);
        clock_t end       = clock();
        double time_spent = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
        printf("Time spent vector_rm: %f ms\n", time_spent);
        printf(
            "point vector_len after deletion: %ld (%s)\n",
            vector_len(pointv),
            vector_len(pointv) == tgt_size - 1 ? "PASS" : "FAIL");
    }
    printf("vector size: %lu \n", vector_size(pointv));
    vector_shrink_to_fit(pointv);
    printf("vector size after shrink: %lu \n", vector_size(pointv));

    vector_destroy(pointv);
#endif
}
