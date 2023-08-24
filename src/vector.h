#include <stddef.h>
#include <stdint.h>
typedef void *vector_t;

#define DATA_OFFSET (offsetof(struct vector_metadata, data))
#define HEAD_SIZE   DATA_OFFSET

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

vector_t vector_create();
vector_t prv_vector_insert(vector_t vec, uint64_t pos, void *data, size_t size);
void prv_vector_rm(vector_t vec, uint64_t pos, size_t size);
size_t vector_size(vector_t vec);
size_t vector_len(vector_t vec);
vector_t vector_shrink_to_fit(vector_t vec);
void vector_destroy(vector_t vec);
