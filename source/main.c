#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "transmitter.h"
#include "receiver.h"

void print_array(uint8_t *arr, size_t len)
{
    for (size_t i = 0; i < len - 1; ++i)
    {
        printf("%x, ", arr[i]);
    }

    printf("%x\n", arr[len - 1]);
}

int main()
{
    return_code_t return_code = RETURN_CODE_UNINITIALIZED;

    uint8_t message[] = {0xc0, 0x01, 0xc0, 0xde};
    size_t len = LENGTH(message);

    uint8_t *encoded = NULL;
    uint8_t *decoded = NULL;

    printf("Original: ");
    print_array(message, len);

    return_code = transmitter__transmit(message, &len, &encoded);
    CLEANUP_IF_FAIL(return_code);

    printf("Encoded: ");
    print_array(encoded, len);

    return_code = receiver__receive(encoded, &len, &decoded);
    CLEANUP_IF_FAIL(return_code);

    printf("Decoded: ");
    print_array(decoded, len);

l_cleanup:
    free(encoded);
    free(decoded);

    return return_code;
}
