#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "utility.h"
#include "fileops.h"

/* student.c
   Implements add, display, search, modify, delete and sort functions.
*/

extern Student *arr;
extern int count;

/* print one student (simple format) */
void print_student(const Student *s)
{
    if (!s) return;
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

/* Add student */
void add_student(void)
{
    Student s;
    s.id = get_next_id();
    s.marks = NULL;
    s.marks_count = 0;

    printf("\n--- Add Student ---\n");
    printf("Assigned ID: %d\n", s.id);

    read_line("Enter name: ", s.name, sizeof(s.name));
    s.age = read_int("Enter age: ");
    s.gender = read_gender("Enter gender (M/F/O): ");
    read_line("Enter course: ", s.course, sizeof(s.course));
    s.gpa = read_float("Enter GPA: ");

    int mcount = read_int("Number of subjects: ");
    if (mcount > 0) {
        s.marks = malloc(sizeof(int) * mcount);
        if (!s.marks) {
            printf("Memory error.\n");
            s.marks_count = 0;
        } else {
            s.marks_count = mcount;
            for (int i = 0; i < mcount; i++) {
                char prompt[64];
                sprintf(prompt, "  Marks for subject %d: ", i + 1);
                s.marks[i] = read_int(prompt);
            }
        }
    }

    ensure_capacity();
    arr[count++] = s;

    if (save_to_file() == 0) printf("Saved.\n");
    else printf("Save failed.\n");
}

/* Display all students */
void display_all(void)
{
    printf("\n--- All Students (%d) ---\n", count);
    for (int i = 0; i < count; i++)
        print_student(&arr[i]);
}

/* Search by ID */
void search_student(void)
{
    int id = read_int("Enter ID: ");
    int idx = find_index_by_id(id);
    if (idx == -1) printf("Not found.\n");
    else print_student(&arr[idx]);
}

/* Modify student */
void modify_student(void)
{
    int id = read_int("Enter ID to modify: ");
    int idx = find_index_by_id(id);
    if (idx == -1) {
        printf("Not found.\n");
        return;
    }

    Student *s = &arr[idx];
    print_student(s);

    char buf[128];
    read_line("New name (blank = keep): ", buf, sizeof(buf));
    if (strlen(buf) > 0) strncpy(s->name, buf, sizeof(s->name));

    read_line("New age (blank = keep): ", buf, sizeof(buf));
    if (strlen(buf) > 0) s->age = atoi(buf);

    read_line("New gender (blank = keep): ", buf, sizeof(buf));
    if (strlen(buf) > 0) s->gender = buf[0];

    read_line("New course (blank = keep): ", buf, sizeof(buf));
    if (strlen(buf) > 0) strncpy(s->course, buf, sizeof(s->course));

    read_line("New GPA (blank = keep): ", buf, sizeof(buf));
    if (strlen(buf) > 0) s->gpa = atof(buf);

    read_line("Change marks? (y/N): ", buf, sizeof(buf));
    if (buf[0] == 'y' || buf[0] == 'Y') {
        free_student_marks(s);
        int m = read_int("New number of subjects: ");
        if (m > 0) {
            s->marks = malloc(sizeof(int) * m);
            if (s->marks) {
                s->marks_count = m;
                for (int i = 0; i < m; i++) {
                    char p[40];
                    sprintf(p, "  Marks %d: ", i + 1);
                    s->marks[i] = read_int(p);
                }
            } else s->marks_count = 0;
        }
    }

    save_to_file();
    printf("Updated.\n");
}

/* Delete student */
void delete_student(void)
{
    int id = read_int("Enter ID to delete: ");
    int idx = find_index_by_id(id);
    if (idx == -1) { printf("Not found.\n"); return; }

    print_student(&arr[idx]);
    char buf[8];
    read_line("Confirm delete (y/N): ", buf, sizeof(buf));
    if (buf[0] != 'y' && buf[0] != 'Y') return;

    free_student_marks(&arr[idx]);

    for (int i = idx; i < count - 1; i++)
        arr[i] = arr[i + 1];
    count--;
    save_to_file();
    printf("Deleted.\n");
}

/* Case-insensitive compare */
static int ci_cmp(const char *a, const char *b)
{
    while (*a && *b) {
        char ca = tolower((unsigned char)*a);
        char cb = tolower((unsigned char)*b);
        if (ca != cb) return ca - cb;
        a++; b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

/* Sort by ID */
void sort_by_id(void)
{
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
void sort_by_name(void)
{
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - 1 - i; j++)
            if (ci_cmp(arr[j].name, arr[j + 1].name) > 0) {
                Student t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
    display_all();
}
