#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "transmitter.h"

#define BITS_IN_BYTE (8)
#define DATA_SIZE_IN_BITS (7)

/**
 * @brief Encodes a single byte from the message
 *
 * @param[in] data 7 bits from the original message to encode
 * @param[out] encoded the encoded given data
 *
 * @return return code of function
 */
static return_code_t transmitter__encode_byte(uint8_t data, uint8_t *encoded);

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
static uint8_t transmitter__get_nth_bit(uint8_t list[], size_t n);


return_code_t transmitter__transmit(uint8_t *message, size_t *len, uint8_t **encoded)
{
    return_code_t return_code = RETURN_CODE_UNINITIALIZED;
    uint8_t *encoded_message = NULL;

    uint8_t temp = 0;
    size_t temp_len = 0;
    size_t next_index = 0;

    uint8_t curr_bit = 0;
    uint8_t encoded_byte = 0;

    encoded_message = (uint8_t *)malloc(
        ceil(*len * BITS_IN_BYTE / DATA_SIZE_IN_BITS)
    );

    ON_TRUE_SET_VALUE_AND_GOTO_CLEANUP(
        NULL == encoded_message,
        return_code,
        RETURN_CODE_FAILED_ALLOCATING_MEMORY
    );

    for (size_t i = 0; i < *len * BITS_IN_BYTE; ++i)
    {
        curr_bit = transmitter__get_nth_bit(message, i);

        if (DATA_SIZE_IN_BITS == temp_len)
        {
            return_code = transmitter__encode_byte(temp, &encoded_byte);
            CLEANUP_IF_FAIL(return_code);

            encoded_message[next_index] = encoded_byte;
            ++next_index;

            temp = 0;
            temp_len = 0;
        }

        temp <<= 1;
        temp += curr_bit;
        ++temp_len;
    }

    if (temp_len)
    {
        temp <<= (DATA_SIZE_IN_BITS - temp_len);

        return_code = transmitter__encode_byte(temp, &encoded_byte);
        CLEANUP_IF_FAIL(return_code);

        encoded_message[next_index] = encoded_byte;
        ++next_index;
    }

    *encoded = encoded_message;
    *len = next_index;

    return_code = RETURN_CODE_SUCCESS;

l_cleanup:
    return return_code;
}

static uint8_t transmitter__get_nth_bit(uint8_t list[], size_t n)
{

    size_t byte_index = n / BITS_IN_BYTE;
    size_t relative_bit_index = n % BITS_IN_BYTE;
    size_t bit_index_from_end = BITS_IN_BYTE - relative_bit_index - 1;

    return (list[byte_index] & (1 << bit_index_from_end)) >> bit_index_from_end;
}

static return_code_t transmitter__encode_byte(uint8_t data, uint8_t *encoded)
{
    uint8_t temp = data;
    uint8_t lsb = 0;
    size_t count = 0;

    for (size_t i = 0; i < BITS_IN_BYTE; ++i)
    {
        lsb = temp & 1;
        count += lsb;

        temp >>= 1;
    }

    data <<= 1;
    data += (count % 2 != 0);

    *encoded = data;

    return RETURN_CODE_SUCCESS;
}
