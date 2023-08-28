#include "unity.h"
#include "unity_internals.h"
#include "vector.h"

void test_simple_pushback(void)
{
    int *vector = vector_create();
    for (int i = 0; i < 10; i++) {
        vector = vector_push_back(vector, i);
    }

    TEST_ASSERT_EQUAL(10, vector_size(vector));
    TEST_ASSERT_EQUAL(10, vector_len(vector));

    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, vector[i]);
    }

    vector_destroy(vector);
}

void test_pop_back(void)
{
    int *vector = vector_create();
    vector      = vector_push_back(vector, 0);
    vector      = vector_push_back(vector, 1);
    vector      = vector_push_back(vector, 2);

    TEST_ASSERT_EQUAL(3, vector_size(vector));
    TEST_ASSERT_EQUAL(3, vector_len(vector));

    TEST_ASSERT_EQUAL_INT(2, vector_pop_back(vector));
    TEST_ASSERT_EQUAL_INT(1, vector_pop_back(vector));
    TEST_ASSERT_EQUAL_INT(0, vector_pop_back(vector));

    TEST_ASSERT_EQUAL(0, vector_len(vector));
    TEST_ASSERT_EQUAL(3, vector_size(vector));

    vector_destroy(vector);
}

void test_vector_remove(void)
{
    int *vector = vector_create();
    vector      = vector_push_back(vector, 0);
    vector      = vector_push_back(vector, 1);
    vector      = vector_push_back(vector, 2);
    vector      = vector_push_back(vector, 3);
    vector      = vector_push_back(vector, 4);
    vector      = vector_push_back(vector, 5);
    vector      = vector_push_back(vector, 6);
    vector      = vector_push_back(vector, 7);
    vector      = vector_push_back(vector, 8);
    vector      = vector_push_back(vector, 9);

    TEST_ASSERT_EQUAL(10, vector_size(vector));
    TEST_ASSERT_EQUAL(10, vector_len(vector));

    vector_remove(vector, 0);
    TEST_ASSERT_EQUAL(10, vector_size(vector));
    TEST_ASSERT_EQUAL(9, vector_len(vector));
    int exp1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TEST_ASSERT_EQUAL_INT_ARRAY(exp1, vector, 9);

    vector_remove(vector, 4);
    TEST_ASSERT_EQUAL(10, vector_size(vector));
    TEST_ASSERT_EQUAL(8, vector_len(vector));
    int exp2[] = { 1, 2, 3, 4, 6, 7, 8, 9 };
    TEST_ASSERT_EQUAL_INT_ARRAY(exp2, vector, 8);

    vector_remove(vector, 7);
    TEST_ASSERT_EQUAL(10, vector_size(vector));
    TEST_ASSERT_EQUAL(7, vector_len(vector));
    int exp3[] = { 1, 2, 3, 4, 6, 7, 8 };
    TEST_ASSERT_EQUAL_INT_ARRAY(exp3, vector, 7);

    vector_destroy(vector);
}

void test_insert()
{
    int *vector = vector_create();
    vector      = vector_push_back(vector, 0);
    vector      = vector_push_back(vector, 1);
    vector      = vector_push_back(vector, 2);
    vector      = vector_push_back(vector, 3);
    vector      = vector_push_back(vector, 4);
    vector      = vector_push_back(vector, 5);
    vector      = vector_push_back(vector, 6);
    vector      = vector_push_back(vector, 7);
    vector      = vector_push_back(vector, 8);
    vector      = vector_push_back(vector, 9);

    TEST_ASSERT_EQUAL(10, vector_size(vector));
    TEST_ASSERT_EQUAL(10, vector_len(vector));

    vector = vector_insert(vector, 0, 10);
    TEST_ASSERT_EQUAL(11, vector_size(vector));
    TEST_ASSERT_EQUAL(11, vector_len(vector));
    int exp1[] = { 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TEST_ASSERT_EQUAL_INT_ARRAY(exp1, vector, 11);

    vector = vector_insert(vector, 4, 11);
    TEST_ASSERT_EQUAL(12, vector_size(vector));
    TEST_ASSERT_EQUAL(12, vector_len(vector));
    int exp2[] = { 10, 0, 1, 2, 11, 3, 4, 5, 6, 7, 8, 9 };
    TEST_ASSERT_EQUAL_INT_ARRAY(exp2, vector, 12);

    vector = vector_insert(vector, 7, 12);
    TEST_ASSERT_EQUAL(13, vector_size(vector));
    TEST_ASSERT_EQUAL(13, vector_len(vector));
    int exp3[] = { 10, 0, 1, 2, 11, 3, 4, 12, 5, 6, 7, 8, 9 };
    TEST_ASSERT_EQUAL_INT_ARRAY(exp3, vector, 13);

    vector_destroy(vector);
}

void test_shrink()
{
    /**
     * This test aims to test the shrink function
     * 1. Create a vector with 10 elements
     * 2. Remove 2 elements using vector_remove, assert the length and size
     * 3. Shrink the vector, assert the length and size
     * 4. Remove 2 elements using vector_pop_back, assert the length and size
     * 5. Shrink the vector, assert the length and size
     */

    int *vector = vector_create();
    vector      = vector_push_back(vector, 0);
    vector      = vector_push_back(vector, 1);
    vector      = vector_push_back(vector, 2);
    vector      = vector_push_back(vector, 3);
    vector      = vector_push_back(vector, 4);
    vector      = vector_push_back(vector, 5);
    vector      = vector_push_back(vector, 6);
    vector      = vector_push_back(vector, 7);
    vector      = vector_push_back(vector, 8);
    vector      = vector_push_back(vector, 9);

    TEST_ASSERT_EQUAL(10, vector_size(vector));
    TEST_ASSERT_EQUAL(10, vector_len(vector));
    vector = vector_shrink_to_fit(vector);
    TEST_ASSERT_EQUAL(10, vector_size(vector));
    TEST_ASSERT_EQUAL(10, vector_len(vector));

    vector_remove(vector, 0);
    vector_remove(vector, 5);
    TEST_ASSERT_EQUAL(10, vector_size(vector));
    TEST_ASSERT_EQUAL(8, vector_len(vector));
    vector = vector_shrink_to_fit(vector);
    TEST_ASSERT_EQUAL(8, vector_size(vector));
    TEST_ASSERT_EQUAL(8, vector_len(vector));

    vector_pop_back(vector);
    vector_pop_back(vector);
    TEST_ASSERT_EQUAL(8, vector_size(vector));
    TEST_ASSERT_EQUAL(6, vector_len(vector));

    vector = vector_shrink_to_fit(vector);
    TEST_ASSERT_EQUAL(6, vector_size(vector));
    TEST_ASSERT_EQUAL(6, vector_len(vector));

    vector_destroy(vector);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_simple_pushback);
    RUN_TEST(test_simple_pushback);
    RUN_TEST(test_pop_back);
    RUN_TEST(test_vector_remove);
    RUN_TEST(test_insert);
    RUN_TEST(test_shrink);

    return UNITY_END();
}

void setUp(void)
{
}

void tearDown()
{
}
