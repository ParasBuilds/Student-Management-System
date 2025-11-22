#ifndef STUDENT_H
#define STUDENT_H

/* student.h
   Declarations for Student struct and student-related functions.
   Kept intentionally simple and student-style commented.
*/

#include <stdio.h>

/* Student record structure
   - marks is a dynamic array allocated with malloc/calloc
   - marks_count keeps number of subjects
*/
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

#endif /* STUDENT_H */
