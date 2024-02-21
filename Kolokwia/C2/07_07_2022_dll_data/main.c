#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(int arguments_quantity, char**argv) {
    if(arguments_quantity < 2)
    {
        printf("Wrong number of parameters");
        return 1;
    }
    for(int i = 1; i < arguments_quantity; i++)
    {
        char * file_name = *(argv + i);
        struct list_t *list;
        switch (read_file(&list,file_name))
        {
            case 1:
                return 1;
            case 2:
                printf("Failed to allocate memory");
                return 2;
            case 3:
                printf("File open error");
                return 3;
            case 4:
                printf("File corrupted");
                return 4;
            default:
                break;
        }
        display_list(list);
        char *name;
        for(unsigned int k = 0; k <list->header->size; k++)
        {
            printf("%s: ", *(list->header->names + k));
            name =* (list->header->names + k);
            int * x;
            double * y;
            char * z;
            switch (*(list->header->types+k))
            {
                case INT:
                    x = (int *)(aggregate_list(list, name, (accumulate_int)));
                    printf("%d\n", *x);
                    if(x != NULL){
                        free(x);
                    }
                    break;
                case DBL:
                    y = (double *)(aggregate_list(list, name, (accumulate_double)));
                    printf("%lf\n", *y);
                    if(y != NULL)
                    {
                        free(y);
                    }
                    break;
                case STR:
                    z = (char *)(aggregate_list(list, name, (accumulate_string)));
                    printf("%s\n", z);
                    if(z != NULL)
                    {
                        free(z);
                    }
                    break;
            }
        }
        free_list(&list);
    }
    return 0;
}
