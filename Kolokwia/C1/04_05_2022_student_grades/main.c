#include <stdio.h>
#include "defs.h"

int main() {
    struct student_t **students;

    int res = read_students_grades("student_grades.txt", &students);
    if(res == -2)
    {
        printf("Couldn't open file");
        return 4;
    }
    if(res == -3)
    {
        printf("File corrupted");
        return 6;
    }
    if(res == -4)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    display_students_grades(students);
    free_students_grades(students);

    return 0;
}
