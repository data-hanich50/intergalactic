#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "transmitter.h"

int main()
{
    return_code_t return_code = RETURN_CODE_UNINITIALIZED;
    uint8_t message[] = { 0xc0, 0x01, 0xc0, 0xde };
    uint8_t *encoded = NULL;
    size_t len = 4;

    return_code = transmitter__transmit(message, &len, &encoded);
    CLEANUP_IF_FAIL(return_code);

    ON_TRUE_SET_VALUE_AND_GOTO_CLEANUP(
        NULL == message,
        return_code,
        RETURN_CODE_SUCCESS
    );

    for (size_t i = 0; i < len; ++i)
    {
        printf("%x ", encoded[i]);
    }
    printf("\n");

l_cleanup:
    free(encoded);

    return return_code;
}