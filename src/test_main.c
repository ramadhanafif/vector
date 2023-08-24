#include "vector.h"

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
