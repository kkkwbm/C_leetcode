#include <stdio.h>
#include <math.h>
#include "tested_declarations.h"
#include "rdebug.h"

enum figure_types{
    TRIANGLE = 1,
    RECTANGLE,
    CIRCLE
};

struct point_t
{
    int x;
    int y;
};
struct rectangle_t
{
    struct point_t p;
    int width;
    int height;
};
struct circle_t
{
    struct point_t c;
    float r;
};
struct triangle_t
{
    struct point_t p1;
    struct point_t p2;
    struct point_t p3;
};

struct figure_t{
    union
    {
        struct rectangle_t rect;
        struct triangle_t triangle;
        struct circle_t circ;
    };
    enum figure_types type;
};

struct segment_t {
    struct point_t start;
    struct point_t end;
};

float area_triangle(const struct triangle_t *t)
{
    if(t == NULL) return -1;

    int x1 = t->p1.x;
    int x2 = t->p2.x;
    int x3 = t->p3.x;

    int y1 = t->p1.y;
    int y2 = t->p2.y;
    int y3 = t->p3.y;

    float a, b, c;
    float pole;

    a = sqrtf((float)pow(x1-x2,2) + (float)pow(y1-y2,2));
    b = sqrtf((float)(x2-x3)*(float)(x2-x3) + (float)(y2-y3) * (float)(y2-y3));
    c = sqrtf((float)pow(x3-x1,2) + (float)pow(y3-y1,2));

    float p = (a + b + c) / 2;
    pole = sqrtf((p-a) * (p-b) * (p-c) * p);
    if(pole <= 0) return -1;
    else return pole;
}

float area_rectangle(const struct rectangle_t *r)
{
    if(r == NULL) return -1;

    if(r->width < 0 || r->height < 0) return -1;

    return (float)(r->width * r->height);
}
float area_circle(const struct circle_t *c)
{
    if(c == NULL || c->r <= 0) return -1;

    return (float)(M_PI*c->r*c->r);
}
float area_figure(const struct figure_t *f)
{
    if(f == NULL) return -1;
    else if (f->type == 0) return -1;
    else if(f->type == 1) return area_triangle(&f->triangle);
    else if(f->type == 2) return area_rectangle(&f->rect);
    else if(f->type == 3) return area_circle(&f->circ);
    else return -1;
}

void display_rectangle(const struct rectangle_t *rect)
{
    if(rect == NULL) return;

    printf("Rectangle (%d, %d), width = %d, height = %d\n", rect->p.x, rect->p.y, rect->width, rect->height);
}
void display_triangle(const struct triangle_t *t)
{
    if(t == NULL) return;

    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)\n", t->p1.x, t->p1.y, t->p2.x, t->p2.y, t->p3.x, t->p3.y);
}
void display_circle(const struct circle_t *circ)
{
    if(circ == NULL) return;

    printf("Circle (%d, %d), radius = %f\n", circ->c.x, circ->c.y, circ->r);
}
void display_figure(struct figure_t *f)
{
    if(f == NULL) return;
    else if (f->type == 0) return;
    else if(f->type == 1) display_triangle(&f->triangle);
    else if(f->type == 2) display_rectangle(&f->rect);
    else if(f->type == 3) display_circle(&f->circ);
}

int sort_by_area(struct figure_t **figures, int size)
{
    if(figures == NULL || *figures == NULL || size <= 0) return 1;

    struct figure_t *temp;

    for (int i = 0; i < size; i++) {
        if (area_figure(*(figures + i)) == -1) return 1;
    }

    for (int i = 0; i < size; i++) {
        for (int j = i; j > 0; j--) {
            if (j == size) break;

            if (area_figure(*(figures + j)) > area_figure(*(figures + j - 1)))
            {
                temp = *(figures + j - 1);
                *(figures + j - 1) = *(figures + j);
                *(figures + j) = temp;
            }
        }
    }
    return 0;
}



int main()
{
    enum figure_types number;
    struct figure_t tab[50];
    struct figure_t *p_tabs[50];
    for (int i = 0; i < 50; i++) {
        *(p_tabs + i) = tab + i;
    }
    struct figure_t **pp_tab = p_tabs;
    int i = 0;
    int error = 0;
    int valid = 0;
    int counter = 0;
    for(i = 0 ; i < 50; i++)
    {
        printf("Enter figure's type: ");
        valid = scanf("%u", &number);
        if(valid != 1)
        {
            printf("Incorrect input");
            return 1;
        }

        if(number == 0) break;
        (tab + i)->type = number;
        if(number < 0 || number > 3)
        {
            printf("Incorrect input data");
            return 2;
        }


        (tab + i)->type = number;

        if(number == 1)
        {
            printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3): ");
            valid = scanf("%d %d %d %d %d %d", &(tab+i)->triangle.p1.x, &(tab+i)->triangle.p1.y, &(tab+i)->triangle.p2.x, &(tab+i)->triangle.p2.y, &(tab+i)->triangle.p3.x, &(tab+i)->triangle.p3.y);
            if(valid != 6)
            {
                printf("Incorrect input");
                return 1;
            }
            if(area_figure(tab+i) == -1) error++;

        }
        else if(number == 2)
        {
            printf("Enter coordinates of a rectangle along with its dimensions (x y width height): ");
            valid = scanf("%d %d %d %d", &(tab+i)->rect.p.x, &(tab+i)->rect.p.y, &(tab+i)->rect.width, &(tab+i)->rect.height);
            if(valid !=4)
            {
                printf("Incorrect input");
                return 1;
            }
            if(area_figure(tab+i) == -1) error++;

        }
        else if(number == 3)
        {
            printf("Enter coordinates and radius of a circle: ");
            valid = scanf("%d %d %f", &(tab+i)->circ.c.x, &(tab+i)->circ.c.y, &(tab+i)->circ.r);
            if(valid != 3)
            {
                printf("Incorrect input");
                return 1;
            }
            if(area_figure(tab+i) == -1) error++;
        }
        counter++;
    }


    if(error != 0)
    {
        printf("Incorrect input data");
        return 2;
    }

    valid = sort_by_area(pp_tab, i);
    if(valid == 1)
    {
        printf("Incorrect input data");
        return 2;
    }

    for (int j = 0; j < i; j++){
        display_figure(*(p_tabs+j));
    }


    return 0;
}

