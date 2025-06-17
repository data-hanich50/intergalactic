#include <stdint.h>
#include "common.h"

/**
 * @brief Transmits a given message
 *
 * @param[in] message list of bytes that contains data to transmit
 * @param[in, out] len length of the message list.
 * will be returned the encoded message length
 * @param[out] encoded list of bytes that contains the encoded message
 *
 * @return return code of function
 */
return_code_t transmitter__transmit(uint8_t *message, size_t *len, uint8_t **encoded);
