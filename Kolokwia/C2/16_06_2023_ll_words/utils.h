//
// Created by Bartosz on 02.07.2023.
//

#ifndef KOLOKWIUM_C2___16_06_2023_UTILS_H
#define KOLOKWIUM_C2___16_06_2023_UTILS_H

#define CREATE_FUNCTION_COUNT01(TYPE) \
TYPE count01_##TYPE(TYPE arg){        \
    TYPE count=0;                     \
    for(int i=1;i<sizeof(TYPE)*8;i++){\
        if(((arg>>i)&1)==0){          \
            if(((arg>>(i-1))&1)==1){  \
                count++;              \
            }                         \
        }                             \
    }                                 \
    return count;                     \
}

/*
#define CREATE_FUNCTION_COUNT01_STRING(TYPE)                   \
    uint8_t count01_##TYPE(const char* str) {                  \
        uint8_t count = 0;                                     \
        while (*str) {                                         \
            char c = *str++;                                   \
            for (int i = 1; i < 8; i++) {                      \
                if (((c >> i) & 1) == 0) {                     \
                    if (((c >> (i - 1)) & 1) == 1) {           \
                        count++;                               \
                    }                                          \
                }                                              \
            }                                                  \
        }                                                      \
        return count;                                          \
    }
*/



#endif //KOLOKWIUM_C2___16_06_2023_UTILS_H
