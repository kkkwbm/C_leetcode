//
// Created by Bartosz on 13.08.2023.
//

#include "function.h"
#include "tested_declarations.h"
#include "rdebug.h"

uint64_t bits_to_number(int *error, int count, ...) {
    if (count < 1 || count > 64)
    {
        if (error) *error = 1;
        return 0;
    }

    va_list args;
    va_start(args, count);

    uint64_t result = 0;
    for (int i = 0; i < count; i++)
    {
        int bit = va_arg(args, int);
        if (bit != 0 && bit != 1)
        {
            if (error) *error = 1;
            va_end(args);
            return 0;
        }
        result = (result << 1) | bit;
    }

    va_end(args);
    if (error) *error = 0;

    return result;
}


