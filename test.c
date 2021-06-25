/**
 * @file test.c
 * @author Tintu Jose (tintu.jose@yaelev.se)
 * @brief For VG, all the requirements shall be fulfilled and the module shall be tested fully.
 *        Some suggestions for testing:
  *           1) Test the initialization of the buffer
 *            2) Test the empty/full buffer case
 *            3) Test read/peek/write when the buffer is empty
 *            4) Test read/peek/write when the buffer is full (an overwritten occurres when we write to a full buffer)
 *            5) Test read/peek/write when the buffer is not empty and full
 *            6) Test avilable  after writing 8 data and reading 8 data
 * @version 0.1
 * @date 2021-03-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <unity.h>
#include "cbuffer.h"

void setUp()
{
    cbuffer_init();
}

void tearDown()
{
}

//1.Test initialization
void test_init(void)
{
    cbuffer_init();
    TEST_ASSERT_EQUAL_UINT8(0, cbuffer_available());
}

//2.Test empty/full buffer case
void test_empty_full(void)
{
    TEST_ASSERT_EQUAL_UINT8(0, cbuffer_available());
    TEST_ASSERT_FALSE(cbuffer_isfull());
    for (int i = 1; i <= BUFFER_SIZE; i++)
        cbuffer_write(i);
    TEST_ASSERT_TRUE(cbuffer_isfull());
}

//3.Test read,peek,write when the buffer is empty
void test_rpw_empty(void)
{
    TEST_ASSERT_EQUAL_UINT8(0, cbuffer_peek());
    TEST_ASSERT_EQUAL_UINT8(0, cbuffer_read());
    cbuffer_write(12);
    TEST_ASSERT_EQUAL_UINT8(1, cbuffer_available());
    TEST_ASSERT_EQUAL_UINT8(12, cbuffer_peek());
}

//4.Test read/peek/write when the buffer is full (an overwritten occurres when we write to a full buffer)
void test_rpw_full(void)
{
    for (int i = 1; i <= BUFFER_SIZE; i++)
        cbuffer_write(i);

    TEST_ASSERT_TRUE(cbuffer_isfull());

    TEST_ASSERT_EQUAL_UINT8(1, cbuffer_peek());

    cbuffer_write(119);
    TEST_ASSERT_EQUAL_UINT8(BUFFER_SIZE, cbuffer_available());
    TEST_ASSERT_EQUAL_UINT8(2, cbuffer_peek());
    TEST_ASSERT_EQUAL_UINT8(2, cbuffer_read());
}

//5.Test read/peek/write when the buffer is not empty and full
void test_rpw_notempty_notfull(void)
{
    cbuffer_write(13);
    cbuffer_write(14);
    cbuffer_write(54);
    TEST_ASSERT_EQUAL_UINT8(3, cbuffer_available());
    TEST_ASSERT_EQUAL_UINT8(13, cbuffer_peek());
    TEST_ASSERT_EQUAL_UINT8(13, cbuffer_read());
}

//6.Test avilable  after writing 8 data and reading 8 data
void test_available(void)
{
    for (int i = 1; i <= BUFFER_SIZE; i++)
        cbuffer_write(i);

    for (int i = 0; i < BUFFER_SIZE; i++)
        cbuffer_read();

    TEST_ASSERT_EQUAL_UINT8(0, cbuffer_available());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_init);
    RUN_TEST(test_empty_full);
    RUN_TEST(test_rpw_empty);
    RUN_TEST(test_rpw_full);
    RUN_TEST(test_rpw_notempty_notfull);
    RUN_TEST(test_available);
    return UNITY_END();
}
