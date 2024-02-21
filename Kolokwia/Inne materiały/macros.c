#include <stdio.h>
#include <stdint.h>

/*
Makro CREATE_DISPLAY(TYPE, FORMAT)
Makro będzie generowało funkcję wyświetlającą zawartość danych przekazanych do niej. Wszystkie funkcje, generowane przez makro powinny przyjmować const void * jako jedyny parametr.
Makro przyjmuje:
typ danej, dla której ma zostać utworzona funkcja, oraz
tekst formatujący, zgodny ze specyfikacją printf (np. %d dla typu int), który ma zostać wykorzystany do wyświetlenia zawartości spod przekazanego wskaźnika.
Nazwa generowanej funkcji ma być budowana na podstawie wzorca display_TYP, gdzie zamiast wyrazu TYP ma się pojawiać typ danych podany w drugim argumencie makra.
W przypadku typu char* makro ma utworzyć funkcję o nazwie display_string. Wykorzystaj w tym celu słowo kluczowe typedef, które utworzy odpowiednią nazwę (string) dla typu char *.
Deklarację makra zamieść w pliku linked_list.h
 */
#define CREATE_READ_FUNCTIONS(TYPE, FORMAT)    \
int read_##TYPE(TYPE *data, int size){         \
    if(!data || size < 0) return 1;            \
    for(int i = 0; i < size; i++)              \
    {                                          \
        if(scanf(FORMAT, (data + i)))          \
        {                                      \
            return 2;                          \
        }                                      \
    }                                          \
    return 0;                                  \
}                                              \

CREATE_READ_FUNCTIONS(int, "%d")
CREATE_READ_FUNCTIONS(float , "%f")
CREATE_READ_FUNCTIONS(double , "%lf")

#define CREATE_SORT_FUNCTIONS(TYPE)            \
int sort_##TYPE(TYPE *data, int size){         \
    if(!data || size <= 0) return 1;           \
    for(int i = 0; i < size; i++)              \
    {                                          \
        for(int j = 0; j < size - 1; j++)      \
        {                                      \
            if(*(data + j) > *(data + j + 1))  \
            {                                  \
                TYPE temp = *(data + j);       \
                *(data + j) = *(data + j + 1); \
                *(data + j + 1) = temp;        \
            }                                  \
        }                                      \
    }                                          \
    return 0;                                  \
}                                              \

CREATE_SORT_FUNCTIONS(int)
CREATE_SORT_FUNCTIONS(float)
CREATE_SORT_FUNCTIONS(double)


#define CREATE_CALCULATE_BITS(TYPE)                           \
uint8_t calculate_bits_ ## TYPE (TYPE num) {                  \
    uint8_t counter = 0;                                      \
                                                              \
    for (long unsigned int i = 0; i < sizeof(num) * 8; i++)   \
    {                                                         \
        counter += !!(num & 1 << i);                          \
    }                                                         \
    return counter;                                           \
}                                                             \

CREATE_CALCULATE_BITS(uint8_t)

#define CREATE_FUNCTION_COUNT01_2(TYPE) \
TYPE count01_##TYPE(TYPE a){            \
    TYPE size = sizeof(a) * 8;          \
    TYPE count = 0;                     \
    for(TYPE i = 0; i < (size - 1); i++)\
    {                                   \
        if( (a & (1 << i) ) )           \
        {                               \
            if( !(a & (1 << (i + 1))))  \
            {                           \
                count++;                \
            }                           \
        }                               \
    }                                   \
    return count;                       \
}                                       \

#define CALCULATE_BITS(num) ( \
    ((num) & 1) + \
    (((num) >> 1) & 1) + \
    (((num) >> 2) & 1) + \
    (((num) >> 3) & 1) + \
    (((num) >> 4) & 1) + \
    (((num) >> 5) & 1) + \
    (((num) >> 6) & 1) + \
    (((num) >> 7) & 1) \
)


#define CREATE_FUNCTION_COUNT01(TYPE)        \
TYPE count01_##TYPE(TYPE arg){               \
    TYPE count = 0;                          \
    for(int i = 1; i < sizeof(TYPE) * 8; i++)\
    {                                        \
        if(((arg >> i) & 1) == 0)            \
        {                                    \
            if(((arg >> (i - 1)) & 1) == 1)  \
            {                                \
                count++;                     \
            }                                \
        }                                    \
    }                                        \
    return count;                            \
}                                            \

CREATE_FUNCTION_COUNT01(uint8_t)

#define CREATE_FUNCTION_COUNT101(TYPE)       \
TYPE count101_##TYPE(TYPE arg){              \
    TYPE count = 0;                          \
    for(int i = 2; i < sizeof(TYPE) * 8; i++)\
    {                                        \
        if(((arg >> i) & 1) == 1 &&          \
           ((arg >> (i - 1)) & 1) == 0 &&    \
           ((arg >> (i - 2)) & 1) == 1)      \
        {                                    \
            count++;                         \
        }                                    \
    }                                        \
    return count;                            \
}

#define CREATE_FUNCTION_COUNT_EVERY_SECOND_BIT(TYPE) \
TYPE countEverySecondBit_##TYPE(TYPE arg){           \
    TYPE count = 0;                                  \
    for(int i = 0; i < sizeof(TYPE) * 8; i += 2)     \
    {                                                \
        if((arg >> i) & 1)                           \
        {                                            \
            count++;                                 \
        }                                            \
    }                                                \
    return count;                                    \
}



/*
CREATE_FUNCTION_COUNT01
CREATE_FUNCTION_COUNT_DIFF(type) - makrodefinicję, która tworzy funkcję
count_diff_##type, która zlicza ilość zer i jedynek w binarnej reprezentacji liczby
typu type. Funkcja powinna przyjmować jeden argument value typu type i zwracać
liczbę jako różnicę pomiędzy policzoną ilością 1 a 0.
*/

#define CREATE_FUNCTION_COUNT_DIFF(type)    \
int count_diff_##type(type value) {         \
        int count_ones = 0;                 \
        int count_zeros = 0;                \
        type mask = 1;                      \
        while (value != 0)                  \
        {                                   \
            if (value & mask) count_ones++; \
            else count_zeros++;             \
            value >>= 1;                    \
        }                                   \
        return count_ones - count_zeros;    \
    }                                       \

CREATE_FUNCTION_COUNT_DIFF(uint8_t);

#define CREATE_FUNCTION_COUNT_ZEROS(type)\
int count_zeros_##type(type value) {     \
        int count_zeros = 0;             \
        type mask = 1;                   \
        while (value != 0)               \
        {                                \
            if (!(value & mask))         \
            {                            \
                 count_zeros++;          \
            }                            \
            value >>= 1;                 \
        }                                \
        return count_zeros;              \
    }                                    \

CREATE_FUNCTION_COUNT_ZEROS(uint8_t);


#define CREATE_FUNCTION_COUNT_ONES(type)\
int count_ones_##type(type value) {     \
        int count_ones = 0;             \
        type mask = 1;                  \
        while (value != 0)              \
        {                               \
            if (value & mask)           \
            {                           \
                count_ones++;           \
            }                           \
            value >>= 1;                \
        }                               \
        return count_ones;              \
        }                               \

CREATE_FUNCTION_COUNT_ONES(uint8_t);

#define SHOW_BITS(a) {                                        \
        for(int i = (sizeof(typeof(a)) * 8) - 1; i >= 0; i--) \
        {                                                     \
            printf("%d ",(a>>i)&1);                           \
        }                                                     \
        printf("\n");                                         \
}                                                             \

//SHOW_BITS((int) value);


typedef char* string;
#define CREATE_DISPLAY(TYPE, FORMAT)                  \
void display_##TYPE(const void *data){                \
    printf(#FORMAT,*((TYPE*)data));                   \
    }                                                 \

CREATE_DISPLAY(uint32_t, %u)
CREATE_DISPLAY(float,%f)
CREATE_DISPLAY(double,%lf)
CREATE_DISPLAY(string,%s)

#define CREATE_FUNCTION_COUNT10(TYPE)         \
TYPE count10_##TYPE(TYPE arg){                \
    TYPE count = 0;                           \
    for(int i = 1; i < sizeof(TYPE) * 8; i++) \
    {                                         \
        if(((arg >> i) & 1) == 1)             \
        {                                     \
            if(((arg >> (i - 1)) & 1) == 0)   \
            {                                 \
                count++;                      \
            }                                 \
        }                                     \
    }                                         \
    return count;                             \
}                                             \

CREATE_FUNCTION_COUNT10(uint8_t);

#define COUNT_BITS(value, set_counter_ptr, cleared_counter_ptr)  \
do{                                                              \
    unsigned long mask = 1ULL << ((sizeof(value) * 8ULL) - 1ULL);\
    int set_counter = 0;                                         \
    int cleared_counter = 0;                                     \
    while(mask)                                                  \
    {                                                            \
        if(value & mask) ++set_counter;                          \
        else ++cleared_counter ;                                 \
        mask >>= 1ULL;                                           \
    }                                                            \
    *(set_counter_ptr) = set_counter;                            \
    *(cleared_counter_ptr) = cleared_counter;                    \
} while(0)                                                       \

// COUNT_BITS( (unsigned int) value, (int) &bits_set ,(int) &bits_cleared);

#define DISPLAY_BITS(value)                                      \
do{                                                              \
    unsigned long mask = 1ULL << ((sizeof(value) * 8ULL) - 1ULL);\
    while(mask)                                                  \
    {                                                            \
        printf((value & mask) ? "1" : "0");                      \
        mask >>= 1ULL;                                           \
    }                                                            \
    printf("\n");                                                \
} while(0)                                                       \

// DISPLAY_BITS( (unsigned int) value);

#define REVERSE_BITS(pointer_to_variable){                    \
    int size = sizeof(*pointer_to_variable) * 8ULL;           \
    long long unsigned int value = *pointer_to_variable;      \
    *pointer_to_variable = 0ULL;                              \
    for(int i = 0ULL; i < size; i++)                          \
    {                                                         \
        if(value & 1ULL << i)                                 \
        {                                                     \
            *pointer_to_variable += 1ULL << (size - i - 1ULL);\
        }                                                     \
    }                                                         \
}                                                             \

// REVERSE_BITS( (unsigned int) value_p);

#define CREATE_CALCULATE_BITS(TYPE)                \
uint8_t calculate_bits_##TYPE(TYPE value) {        \
    uint8_t count = 0;                             \
    for (size_t i = 0; i < sizeof(TYPE) * 8; i++)  \
    {                                              \
        if ((value >> i) & 1) count++;             \
    }                                              \
    return count;                                  \
}

CREATE_CALCULATE_BITS(char)



#define DEFINE_ARRAY(TYPE)\
struct array_##TYPE##_t{  \
    int size;             \
    int capacity;         \
    TYPE *data;           \
};                        \


#define CREATE_ARRAY(TYPE)\
struct array_##TYPE##_t *create_array_##TYPE (int size){\
    if (size < 1) return NULL;\
    struct array_##TYPE##_t *var = (struct array_##TYPE##_t *)malloc(sizeof(struct array_##TYPE##_t));\
    if (var == NULL) return NULL;\
    var->data = ( TYPE *) calloc(sizeof(TYPE), size);\
    if (var->data == NULL)\
    {\
        free(var);\
        return NULL;\
    }\
    var->size = 0;\
    var->capacity = size;\
    return var;\
}


#define FREE_ARRAY(TYPE)\
void free_array_##TYPE (struct array_ ##TYPE##_t *array){\
        if (array == NULL) return;\
        free(array->data);\
        free(array);\
    }\


#define SAVE_ARRAY(TYPE)\
int save_array_##TYPE (const struct array_ ##TYPE##_t *array, const char *filename){\
    if (array == NULL || !array->data || filename == NULL|| array->size > array->capacity || array->size < 1 || array->capacity < 1) return 1;\
    FILE *f = fopen(filename, "wb");\
    if (!f) return 2;\
    if (!fwrite(&(array->size), sizeof(int), 1, f))\
    {\
        fclose(f);\
        return 2;\
    }\
    if (fwrite(array->data, sizeof(TYPE), (array->size), f) != (unsigned int) (array->size))\
    {\
        fclose(f);\
        return 2;\
    }\
    fclose(f);\
    return 0;\
}\

#define LOAD_ARRAY(TYPE)\
int load_array_##TYPE (struct array_ ##TYPE##_t** array, const char* filename) {\
    if (array == NULL || filename == NULL) return 1;\
    *array = (struct array_##TYPE##_t*)malloc(sizeof(struct array_ ##TYPE##_t));\
    if (!(*array)) return 4;\
    FILE *f = fopen(filename, "rb");\
    if (!f)\
    {\
        free(*array);\
        return 2;\
    }\
    int size;\
    if (fread(&size, sizeof(int), 1, f) != 1)\
    {\
        fclose(f);\
        free(*array);\
        return 3;\
    }\
    if (size < 1)\
    {\
        fclose(f);\
        free(*array);\
        return 3;\
    }\
    TYPE *p = ( TYPE *)malloc(sizeof(TYPE) * size);\
    if (!p)\
    {\
        fclose(f);\
        free(*array);\
        return 4;\
    }\
    if (fread(p, sizeof(TYPE), size, f) != (unsigned int) size)\
    {\
        fclose(f);\
        free(*array);\
        free(p);\
        return 3;\
    }\
    (*array)->size = size;\
    (*array)->capacity = size;\
    (*array)->data = p;\
    fclose(f);\
    return 0;\
}\

#define SORT_ARRAY(TYPE)\
int sort_array_##TYPE (struct array_##TYPE##_t *array){\
    if (!array || !array->data || array->size > array->capacity || array->size < 1 || array->capacity < 1) return 1;\
    TYPE temp = 0;\
    for (int i = 0; i < (array->size - 1); i++)\
    {\
        for (int j = 0; j < (array->size - 1 - i); j++)\
        {\
            if (*(array->data + j) > *(array->data + j + 1)) \
            {\
                temp = *(array->data + j);\
                *(array->data + j) = *(array->data + j + 1);\
                *(array->data + j + 1) = temp;\
            }\
        }\
    }\
    return 0;\
}                       \
                        \
                        \
                        TO DO count biggest difference betwen spaces in 1001 or 100001\
                        #define INIT_ARRAY(TYPE) \
DEFINE_ARRAY(TYPE)\
CREATE_ARRAY(TYPE)\
FREE_ARRAY(TYPE)\
SAVE_ARRAY(TYPE)\
LOAD_ARRAY(TYPE)\
SORT_ARRAY(TYPE)\