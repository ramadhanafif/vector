#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define DATA_OFFSET        (offsetof(struct vector_metadata, data))
#define HEAD_SIZE          DATA_OFFSET
#define DATA_TO_META(data) ((struct vector_metadata *)((char *)data - DATA_OFFSET))

struct vector_metadata {
    uint64_t allocated;
    uint64_t used;
    char data[];
};

// NOTE: prv_malloc and prv_realloc in preparation for future custom memory management
// TODO: should be a weak reference
static struct vector_metadata *prv_realloc(struct vector_metadata *meta, int new_size)
{
    return (struct vector_metadata *)realloc(meta, new_size);
}
static inline void *prv_malloc(int size)
{
    return malloc(size);
}
static inline void prv_free(void *meta)
{
    free(meta);
}

vector_t vector_create()
{
    struct vector_metadata *meta = prv_malloc(sizeof(struct vector_metadata));

    meta->allocated = 0;
    meta->used      = 0;

    return meta->data;
}

vector_t prv_vector_insert(vector_t vec, uint64_t pos, void *data, size_t size)
{
    struct vector_metadata *meta = DATA_TO_META(vec);
    struct vector_metadata *temp = NULL;
    if (meta->allocated == meta->used) {
        temp = prv_realloc(meta, HEAD_SIZE + (meta->allocated + 1) * size);
        if (temp != NULL) {
            meta = temp;
            meta->allocated++;
        } else
            return NULL;
    }
    memmove(
        meta->data + (pos + 1) * size, // Destination address: the next data
        meta->data + (pos)*size,       // Source address: the data@(pos)
        (meta->used - pos) * size);    // Number of data being moved: total data - position
    memmove(meta->data + size * pos, data, size);
    meta->used++;
    return (vector_t)meta->data;
}

void prv_vector_remove(vector_t vec, uint64_t pos, size_t size)
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

vector_t prv_vector_shrink_to_fit(vector_t vec, size_t size)
{
    struct vector_metadata *meta = DATA_TO_META(vec);
    struct vector_metadata *temp;

    if (meta->allocated != meta->used) {
        temp = prv_realloc(meta, HEAD_SIZE + meta->used * size);
        assert(temp != NULL);
        if (temp != NULL) {
            meta            = temp;
            meta->allocated = meta->used;
        }
    }

    return meta->data;
}

void vector_destroy(vector_t vec)
{
    struct vector_metadata *meta = DATA_TO_META(vec);
    prv_free(meta);
}
