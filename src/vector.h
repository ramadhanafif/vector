/** @file vector.h
 * Header file for the vector implementation.
 *
 * @author ramadhanafif
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stddef.h>
#include <stdint.h>

typedef void *vector_t; ///< Type for vector, alias to generic (void) pointer.

/**
 * @def vector_push_back(vec, data)
 * Pushes data to the end of the vector.
 *
 * @warn the returned pointer is not guaranteed to be the same as the original pointer. Use the returned pointer
 * instead!
 */
#define vector_push_back(vec, data) \
    ({ \
        __typeof__(*vec) temp = data; \
        (__typeof__(*vec) *)prv_vector_insert(vec, vector_len(vec), &temp, sizeof(temp)); \
    })

/**
 * @def vector_insert(vec, pos, data)
 * Inserts data to at the \a pos of the vector, then shift the rest of the data to the end.
 * @warn this function does not check validity of the position. Caller must check it by themselves.
 * @warn the returned pointer is not guaranteed to be the same as the original pointer. Use the returned pointer
 * instead!
 */
#define vector_insert(vec, pos, data) \
    ({ \
        __typeof__(*vec) temp = data; \
        (__typeof__(*vec) *)prv_vector_insert(vec, pos, &temp, sizeof(temp)); \
    })

/**
 * @def vector_pop_back(vec)
 * Removes the last element of the vector and returns it.
 */
#define vector_pop_back(vec) \
    ({ \
        __typeof__(*vec) temp = vec[vector_len(vec) - 1]; \
        vector_remove(vec, vector_len(vec) - 1); \
        temp; \
    })

/**
 * @def vector_remove(vec, pos)
 * Removes the element at \a pos of the vector.
 * @warn this function does not check validity of the position. Caller must check it by themselves.
 */
#define vector_remove(vec, pos) (prv_vector_remove(vec, pos, sizeof(*vec)))

/**
 * @def vector_shrink_to_fit(vec)
 * Shrinks the allocated memory of the vector to fit the length.
 * @warn the returned pointer is not guaranteed to be the same as the original pointer. Use the returned pointer
 * instead!
 */
#define vector_shrink_to_fit(vec) (prv_vector_shrink_to_fit(vec, sizeof(*vec)))

/**
 * @brief Creates a new dynamically-allocated and dynamically-sized vector
 * @return pointer to the first position of the array.
 */
vector_t vector_create();

/**
 * @brief Inserts a new element to the vector at the specified position.
 * @param vec The vector to insert the element to.
 * @param pos The position to insert the element to.
 * @param data The data to insert.
 * @param size The size of the data to insert.
 * @return pointer to the first position of the array.
 *
 * @warn this function should not be called directly. Use the macro \a vector_insert instead.
 */
vector_t prv_vector_insert(vector_t vec, uint64_t pos, void *data, size_t size);

/**
 * @brief Removes an element from the vector at the specified position.
 * @param vec The vector to remove the element from.
 * @param pos The position to remove the element from.
 * @param size The size of the data to remove.
 *
 * @warn this function should not be called directly. Use the macro \a vector_remove instead.
 */
void prv_vector_remove(vector_t vec, uint64_t pos, size_t size);

/**
 * @brief Returns the allocated memory for the vector.
 * @param vec The vector to get the size of.
 * @return The allocated memory for the vector.
 */
size_t vector_size(vector_t vec);

/**
 * @brief Returns the length of the vector.
 * @param vec The vector to get the length of.
 * @return The length of the vector.
 */
size_t vector_len(vector_t vec);

/**
 * @brief Shrink vector allocated memory to fit the length.
 * @param vec The vector to shrink.
 * @param size The size of the data
 *
 * @warn this function should not be called directly. Use the macro \a vector_shrink_to_fit instead.
 * @return pointer to the first position of the vector.
 */
vector_t prv_vector_shrink_to_fit(vector_t vec, size_t size);

/**
 * @brief Destroys the vector and frees the allocated memory.
 * @param vec The vector to destroy.
 */
void vector_destroy(vector_t vec);

#endif
