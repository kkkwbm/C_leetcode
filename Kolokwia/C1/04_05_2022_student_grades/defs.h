
#ifndef INC_2022_DEFS_H
#define INC_2022_DEFS_H
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


struct course_grades_t {
    char course[43];
    size_t number_of_grades;
    int* grades;
};



struct student_t {
    char name[21];
    char last_name[41];
    size_t number_of_courses;
    struct course_grades_t* courses;
};


void free_students_grades(struct student_t **students);
int read_students_grades(const char *filename, struct student_t ***students);
void display_students_grades(struct student_t **students);
int write_student_grades(const char *filename, struct student_t** students, const char* name, const char* last_name);
int write_course_grades(const char *filename, struct student_t** students, const char* course);
int sort_students_grades(struct student_t*** students);
int add_grade(struct student_t*** students, const char* name, const char* last_name, const char* course, int grade);
int read_students_grades_bin(const char *filename, struct student_t ***students);

#endif //INC_2022_DEFS_H
