#include "unity.h"
#include "vector.h"

typedef void(test_runner_t)(void);

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

test_runner_t *test_runners[] = {
    test_simple_pushback,
    test_pop_back,
    test_vector_remove,
};

size_t test_runners_len = sizeof(test_runners) / sizeof(test_runners[0]);

int main()
{
    UNITY_BEGIN();
    for (size_t i = 0; i < test_runners_len; i++) {
        RUN_TEST(test_runners[i]);
    }

    return UNITY_END();
}

void setUp(void)
{
}

void tearDown()
{
}
