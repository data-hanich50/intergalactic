#pragma once

#define LENGTH(x) (sizeof(x) / sizeof(x[0]))

#define CLEANUP_IF_FAIL(return_code)                                                     \
    do                                                                                   \
    {                                                                                    \
        if (RETURN_CODE_SUCCESS != return_code)                                          \
        {                                                                                \
            goto l_cleanup;                                                              \
        }                                                                                \
    }                                                                                    \
    while (0)

#define ON_TRUE_SET_VALUE_AND_GOTO_CLEANUP(condition, return_code, new_return_code)      \
    do                                                                                   \
    {                                                                                    \
        if (condition)                                                                   \
        {                                                                                \
            return_code = new_return_code;                                               \
            goto l_cleanup;                                                              \
        }                                                                                \
    }                                                                                    \
    while (0)

typedef enum return_code_e
{
    RETURN_CODE_UNINITIALIZED = -1,
    RETURN_CODE_SUCCESS,
    RETURN_CODE_FAILED_ALLOCATING_MEMORY
} return_code_t;