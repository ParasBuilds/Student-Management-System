#ifndef STUDENT_H
#define STUDENT_H

/* student.h
   Student struct and student-related function declarations.
*/

#include <stdio.h>

typedef struct {
    int id;
    char name[64];
    int age;
    char gender;
    char course[48];
    float gpa;

    int marks_count;
    int *marks;
} Student;

/* student.c functions */
void add_student(void);
void display_all(void);
void search_student(void);
void modify_student(void);
void delete_student(void);
void sort_by_id(void);
void sort_by_name(void);
void print_student(const Student *s);

#endif /* STUDENT_H */
