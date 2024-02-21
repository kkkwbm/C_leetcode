#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define ARRAY(type) \
    struct array_##type{ \
      type* array; \
      int capacity; \
      int size;\
    };              \
                    \
    struct array_##type* array_create_##type(int size){ \
      struct array_##type* ptr = malloc(sizeof(struct array_##type)); \
      ptr->capacity=size;                                             \
      ptr->size=0;                                                    \
      ptr->array=calloc(sizeof(type),size);                           \
      return ptr;                                                     \
    }

ARRAY(int);

// breaks
// ARRAY(unsigned long long);

// works
typedef unsigned long long ull;
ARRAY(ull);

#define SHOW_BITS(a) { \
        for(int i=(sizeof(typeof (a))*8)-1; i>=0;i--){ \
            printf("%d ",(a>>i)&1);              \
        }             \
        printf("\n");\
}

#define dupaaa a+b

void dupa() {
    int a = 12;
    int b = 10;
    printf("%d\n", dupaaa);
}

int bity() {
    puts("Przesuniecia");
    unsigned char n = 5;
    SHOW_BITS(n);
    n <<= 2;
    SHOW_BITS(n);
    n >>= 1;
    SHOW_BITS(n);
    puts("xory");
    unsigned char b = UCHAR_MAX;
    n = 12;
    SHOW_BITS(n);
    SHOW_BITS(b);
    n ^= b;
    SHOW_BITS(n);
    b = 32 + 128;
    SHOW_BITS(b);
    n ^= b;
    SHOW_BITS(n);
    puts("andy");
    b = 32 + 128 + 8;
    SHOW_BITS(b);
    n = 12;
    SHOW_BITS(n);
    n &= b;
    SHOW_BITS(n);
    puts("ory");
    n = 12;
    SHOW_BITS(n);
    SHOW_BITS(b);
    n |= b;
    SHOW_BITS(n);
    return 0;
}

int main() {
    bity();
    return 0;
}