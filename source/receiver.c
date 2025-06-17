#include <stdlib.h>
#include <math.h>
#include "receiver.h"

#define BITS_IN_BYTE (8)
#define DATA_SIZE_IN_BITS (7)

/**
 * @brief Get the n-th bit (from left to right).
 * @example For the list: [10101010, 11110000] and n=10
 * will be returned                   ^
 * 
 * @param[in] list a list of bytes
 * @param[in] n the index of desired bit (from left to right)
 * 
 * @return the value of the n-th bit
 */
static uint8_t receiver__get_nth_bit(uint8_t list[], size_t n);


return_code_t receiver__receive(uint8_t *data, size_t *len, uint8_t **decoded)
{
    return_code_t return_code = RETURN_CODE_UNINITIALIZED;
    uint8_t *decoded_message = NULL;

    uint8_t temp = 0;
    size_t temp_len = 0;
    size_t next_index = 0;

    decoded_message = (uint8_t *)malloc(
        floor(*len * DATA_SIZE_IN_BITS / BITS_IN_BYTE)
    );

    ON_TRUE_SET_VALUE_AND_GOTO_CLEANUP(
        NULL == decoded_message,
        return_code,
        RETURN_CODE_FAILED_ALLOCATING_MEMORY
    );

    for (size_t i = 0; i < *len * BITS_IN_BYTE; ++i)
    {
        if (i % BITS_IN_BYTE != DATA_SIZE_IN_BITS)
        {
            temp <<= 1;
            temp += receiver__get_nth_bit(data, i);
            ++temp_len;

            if (BITS_IN_BYTE == temp_len)
            {
                decoded_message[next_index] = temp;
                ++next_index;

                temp = 0;
                temp_len = 0;
            }
        }
    }

    if (BITS_IN_BYTE == temp_len)
    {
        decoded_message[next_index] = temp;
        ++next_index;
    }

    *decoded = decoded_message;
    *len = next_index;

    return_code = RETURN_CODE_SUCCESS;
    
l_cleanup:
    return return_code;
}

static uint8_t receiver__get_nth_bit(uint8_t list[], size_t n)
{
    size_t byte_index = n / BITS_IN_BYTE;
    size_t relative_bit_index = n % BITS_IN_BYTE;
    size_t bit_index_from_end = BITS_IN_BYTE - relative_bit_index - 1;

    return (list[byte_index] & (1 << bit_index_from_end)) >> bit_index_from_end;
}
