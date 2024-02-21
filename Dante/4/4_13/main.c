#include <stdio.h>
#include <stdlib.h>

short *concatenate_arrays_short(const short *a1, int size1, const short *a2, int size2, int *err_code){
    if(a1 == NULL || a2 == NULL || size1 <= 0 || size2 <= 0)
    {
        if(err_code != NULL) *err_code = 1;
        else return NULL;
    }
    short *k;
    k = (short*)malloc((size1 + size2) * sizeof(short));
    if(k == NULL)
    {
        if(err_code!=NULL) *err_code=2;
        else return NULL;
    }
    for(int i = 0;i < size1; i++) *(k + i) =* (a1 + i);
    int h = 0;
    for(int i = size1; i < size2; i++)
    {
        *(k+i) =* (a2 + h);
        h++;
    }
    if(err_code != NULL) *err_code=0;
    return k;
}


short *create_array_short(int N){
    if(N <= 0) return NULL;

    short *k;
    k = (short *)malloc(N * sizeof(short));

    if(k == NULL) return NULL;
    else return k;
}


void display_vector_short(const short* tab, int size){
    if(tab == NULL || size <= 0) return;
    for(int i = 0; i < size; i++) printf("%d ", *(tab + i));
}
int sort_short(short* tab, int size){
    if(tab == NULL || size <= 0) return 1;

    short k1;
    short *k = &k1;

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(*(tab+i)<*(tab+j))
            {
                *k =* (tab + i);
                *(tab + i) =* (tab + j);
                *(tab + j) =* k;
            }
        }
    }
    return 0;
}
int main(void)
{
    short *a1;
    short *a2;
    short *k;
    int size1;
    int size2;
    int a;
    int kod1;
    int *kod = &kod1;
    short b;
    short c;
    printf("Podaj wielkosc \n");
    a = scanf(" %d", &size1);
    if(!a)
    {
        printf("Incorrect input\n");
        return 1;
    }
    if(size1 <= 0)
    {
        printf("Incorrect input data\n");
        return 2;
    }
    a1 = (short*)malloc(size1 * sizeof(short));
    if(a1 == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }
    printf("Podaj ciag: \n");
    for(int i = 0; i < size1; i++)
    {
        c = scanf(" %hi", &b);
        if(!c)
        {
            printf("Incorrect input\n");
            free(a1);
            return 1;
        }
        *(a1 + i) = b;
    }
    printf("Podaj wielkosc\n");
    a = scanf(" %d", &size2);
    if(!a)
    {
        printf("Incorrect input\n");
        free(a1);
        return 1;
    }
    if(size2 <= 0){
        printf("Incorrect input data\n");
        free(a1);
        return 2;
    }
    a2 = (short*)malloc(size2 * sizeof(short));
    if(a2 == NULL)
    {
        free(a1);
        printf("Failed to allocate memory\n");
        return 8;
    }
    printf("Podaj ciag: ");
    for(int i = 0; i < size2; i++)
    {
        c = scanf("%hi", &b);
        if(!c)
        {
            printf("Incorrect input\n");
            free(a1);
            free(a2);
            return 1;
        }
        *(a2+i) = b;
    }
    k = concatenate_arrays_short(a1, size1, a2, size2,kod);
    if(*kod == 2)
    {
        printf("Failed to allocate memory");
        free(a1);
        free(a2);
        return 8;
    }
    //sort_short(k,size1+size2);
    display_vector_short(k,size1+size2);
    free(a1);
    free(a2);
    free(k);
    return 0;
}