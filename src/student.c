#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/student.h"
#include "../include/utility.h"
#include "../include/fileops.h"

/*
   student.c
   ----------
   This file contains the core student-related operations:
   add, display, search, modify, delete, and sorting.
*/

extern Student *arr;
extern int count;
extern int capacity;

/* Printing details of one student */
void print_student(const Student *s) {

    printf("ID:%d | Name:%s | Age:%d | Gender:%c | Course:%s | GPA:%.2f\n",
           s->id, s->name, s->age, s->gender, s->course, s->gpa);

    if (s->marks_count > 0) {
        printf(" Marks: ");
        for (int i = 0; i < s->marks_count; i++) {
            printf("%d", s->marks[i]);
            if (i < s->marks_count - 1) printf(", ");
        }
        printf("\n");
    }
}

/* Add a new student to the system */
void add_student(void) {

    Student s;
    s.id = get_next_id();
    s.marks = NULL;
    s.marks_count = 0;

    printf("\n--- Add Student ---\n");
    printf("Assigned ID: %d\n", s.id);

    read_line("Enter name: ", s.name, 64);
    s.age = read_int("Enter age: ");
    s.gender = read_gender("Enter gender (M/F/O): ");
    read_line("Enter course: ", s.course, 48);
    s.gpa = read_float("Enter GPA: ");

    int mcount = read_int("How many subjects? ");
    if (mcount > 0) {
        s.marks = malloc(sizeof(int) * mcount);
        s.marks_count = mcount;

        for (int i = 0; i < mcount; i++) {
            char msg[40];
            sprintf(msg, "  Marks for subject %d: ", i + 1);
            s.marks[i] = read_int(msg);
        }
    }

    ensure_capacity();
    arr[count++] = s;

    if (save_to_file() == OK)
        printf("Saved successfully.\n");
    else
        printf("Error saving file.\n");
}

/* Display all students */
void display_all(void) {

    printf("\n--- All Students (%d) ---\n", count);
    for (int i = 0; i < count; i++)
        print_student(&arr[i]);
}

/* Search student by ID */
void search_student(void) {

    int id = read_int("Enter ID to search: ");
    int idx = find_index_by_id(id);

    if (idx == -1)
        printf("Student not found.\n");
    else
        print_student(&arr[idx]);
}

/* Modify an existing student's details */
void modify_student(void) {

    int id = read_int("Enter ID to modify: ");
    int idx = find_index_by_id(id);

    if (idx == -1) {
        printf("Student not found.\n");
        return;
    }

    Student *s = &arr[idx];
    print_student(s);

    char buf[128];

    read_line("New name (blank = keep): ", buf, sizeof(buf));
    if (strlen(buf) > 0) strcpy(s->name, buf);

    read_line("New age (blank = keep): ", buf, sizeof(buf));
    if (strlen(buf) > 0) s->age = atoi(buf);

    read_line("New gender (blank = keep): ", buf, sizeof(buf));
    if (strlen(buf) > 0) s->gender = buf[0];

    read_line("New course (blank = keep): ", buf, sizeof(buf));
    if (strlen(buf) > 0) strcpy(s->course, buf);

    read_line("New GPA (blank = keep): ", buf, sizeof(buf));
    if (strlen(buf) > 0) s->gpa = atof(buf);

    read_line("Change marks? (y/N): ", buf, sizeof(buf));
    if (buf[0] == 'y' || buf[0] == 'Y') {

        free_student_marks(s);

        int m = read_int("New number of subjects: ");
        if (m > 0) {
            s->marks = malloc(sizeof(int) * m);
            s->marks_count = m;

            for (int i = 0; i < m; i++) {
                char p[40];
                sprintf(p, "  Marks for subject %d: ", i + 1);
                s->marks[i] = read_int(p);
            }
        }
    }

    save_to_file();
    printf("Updated successfully.\n");
}

/* Delete a student from the system */
void delete_student(void) {

    int id = read_int("Enter ID to delete: ");
    int idx = find_index_by_id(id);

    if (idx == -1) {
        printf("Student not found.\n");
        return;
    }

    print_student(&arr[idx]);

    char confirm[10];
    read_line("Confirm delete (y/N): ", confirm, sizeof(confirm));

    if (confirm[0] != 'y' && confirm[0] != 'Y')
        return;

    free_student_marks(&arr[idx]);

    for (int i = idx; i < count - 1; i++)
        arr[i] = arr[i + 1];

    count--;
    save_to_file();

    printf("Deleted successfully.\n");
}

/* Case-insensitive compare */
int ci_cmp(const char *a, const char *b) {
    while (*a && *b) {
        char ca = tolower(*a);
        char cb = tolower(*b);
        if (ca != cb) return ca - cb;
        a++; b++;
    }
    return tolower(*a) - tolower(*b);
}

/* Sort by ID */
void sort_by_id(void) {

    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - 1 - i; j++)
            if (arr[j].id > arr[j + 1].id) {
                Student t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }

    display_all();
}

/* Sort by Name */
void sort_by_name(void) {

    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - 1 - i; j++)
            if (ci_cmp(arr[j].name, arr[j + 1].name) > 0) {
                Student t = arr[j];
                arr[j] = arr[j +1];
                arr[j +1] = t;
            }

    display_all();
}
