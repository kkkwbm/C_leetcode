#include <stdio.h>
#include "vector.h"

int main() {
    struct vector_t* buff;
    int number, mode, value, return_value, valid;
   // struct vector_t buff;
   // struct vector_t *ptr_buff =  &buff;
   // struct vector_t **ptr_ptr_buff = &ptr_buff;

    printf("Enter the number of elements: ");
    valid = scanf("%d", &number);
    if (valid == 0)
    {
        printf( "Incorrect input\n");
        return 1;
    }
    if (number <= 0)
    {
        printf( "Incorrect input data\n");
        return 2;
    }


    if (vector_create_struct(&buff, number) != 0)
    {
        printf( "Failed to allocate memory\n");
        return 8;
    }


    do
    {
        int once_again = 0;
        while (getchar() != '\n');
        printf("Podaj tryb: ");
        valid = scanf("%d", &mode);
        if (valid == 0)
        {
            printf("Incorrect input\n");
            vector_destroy_struct(&buff);
            return 1;
        }
        if ((mode < 0 || mode > 2))
        {
            printf("Incorrect input data\n");
            once_again = 1;
        }

        if(once_again == 0)
        {
            switch (mode)
            {
                case 0:
                    printf("Exiting program...\n");
                    break;
                case 1:
                    printf("Enter values to add (0 to end):\n");
                    do {
                        valid = scanf("%d", &value);
                        if (valid == 0)
                        {
                            printf("Incorrect input\n");
                            vector_destroy_struct(&buff);
                            return 1;
                        }

                        if (value == 0) break;
                        /*
                        counter ++;
                        if(counter > number){
                            printf("Failed to allocate memory\n");
                            break;
                        }
                         */

                        return_value = vector_push_back(buff, value);
                        if (return_value == 2)
                        {
                            printf("Failed to allocate memory\n");
                            break;
                        }
                        else if (return_value == 1)
                        {
                            printf("Error\n");
                            vector_destroy_struct(&buff);
                            return 1;
                        }
                    } while (1);
                    break;
                case 2:
                    printf("Enter values to remove (0 to end):\n");
                    do {
                        valid = scanf("%d", &value);
                        if (valid == 0)
                        {
                            printf("Incorrect input\n");
                            vector_destroy_struct(&buff);
                            return 1;
                        }

                        if (value == 0) break;

                        return_value = vector_erase(buff, value);
                        if (return_value == -1)
                        {
                            printf( "Error\n");
                        }
                    } while (1);
                    break;
                default:
                    printf("Incorrect input data\n");
                    vector_destroy_struct(&buff);
                    return 2;
            }
            if (buff->size == 0) printf("Buffer is empty\n");
            else vector_display(buff);
        }

    } while (mode != 0);

    vector_destroy_struct(&buff);

    return 0;
}

