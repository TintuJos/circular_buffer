/**
 * @file cbuffer.c
 * @author Tintu Jose (tintu.jose@yaelev.se)
 * @brief Program to implement CIRCULAR BUFFER.
 * @version 0.1
 * @date 2021-03-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "cbuffer.h"

#if ((BUFFER_SIZE < 8U) || (BUFFER_SIZE > 32U))
#error BUFFER_SIZE should be an integer between 8 and 32
#endif

static bool full = false;
static uint8_t tail = 0U;
static uint8_t head = 0U;
static uint8_t buffer[BUFFER_SIZE] = {0};

void cbuffer_init(void)
{
    full = false;
    tail = 0;
    head = 0;
}

void cbuffer_write(uint8_t value)
{
    if (full)
    {
        head++;
        if (head == BUFFER_SIZE)
        {
            head = 0;
        }
    }
    buffer[tail] = value;
    tail++;
    if (tail == BUFFER_SIZE)
    {
        tail = 0;
    }
    if (tail == head)
        full = true;
}

uint8_t cbuffer_read(void)
{
    if (cbuffer_available())
    {
        uint8_t val = buffer[head];
        if (head != tail || full)
        {
            head++;
            if (head == BUFFER_SIZE)
                head = 0;
        }
        full = false;

        return val;
    }
    else
        return 0;
}

bool cbuffer_isfull(void)
{
    return full;
}

uint8_t cbuffer_peek(void)
{
    if (cbuffer_available())
        return buffer[head];
    else
        return 0;
}

uint8_t cbuffer_available(void)
{
    uint8_t available;
    if (full)
        available = BUFFER_SIZE;
    else
    {
        if (tail >= head)
            available = tail - head;
        else
            available = (tail + BUFFER_SIZE - head);
    }
    return available;
}
