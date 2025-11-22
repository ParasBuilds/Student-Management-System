#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/student.h"
#include "../include/utility.h"

/*
   utility.c
   ----------
   This file contains input helper functions and dynamic array utilities.
   These functions are reused across all modules.
*/

extern Student *arr;
extern int count;
extern int capacity;

/* Remove newline and trailing spaces */
void trim_newline(char *s) {
    int n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r' || s[n - 1] == ' '))
    {
        s[n - 1] = '\0';
        n--;
    }
}

/* Read entire line */
void read_line(const char *prompt, char *buf, int n) {

    printf("%s", prompt);

    if (fgets(buf, n, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }

    trim_newline(buf);
}

/* Clean integer input */
int read_int(const char *prompt) {

    char tmp[64];

    while (1) {
        read_line(prompt, tmp, sizeof(tmp));

        if (strlen(tmp) == 0)
            continue;

        char *end;
        long v = strtol(tmp, &end, 10);

        if (end == tmp || *end != '\0') {
            printf("Invalid number.\n");
            continue;
        }

        return (int)v;
    }
}

/* Clean float input */
float read_float(const char *prompt) {

    char tmp[64];

    while (1) {
        read_line(prompt, tmp, sizeof(tmp));

        if (strlen(tmp) == 0)
            continue;

        char *end;
        float v = strtof(tmp, &end);

        if (end == tmp || *end != '\0') {
            printf("Invalid number.\n");
            continue;
        }

        return v;
    }
}

/* Clean gender input */
char read_gender(const char *prompt) {

    char tmp[16];

    while (1) {
        read_line(prompt, tmp, sizeof(tmp));
        char c = toupper(tmp[0]);

        if (c == 'M' || c == 'F' || c == 'O')
            return c;

        printf("Please enter M/F/O only.\n");
    }
}

/* Ensure our dynamic array has enough capacity */
void ensure_capacity(void) {

    if (capacity == 0) {
        capacity = 4;
        arr = malloc(sizeof(Student) * capacity);
    }
    else if (count >= capacity) {
        capacity *= 2;
        arr = realloc(arr, sizeof(Student) * capacity);
    }
}

/* Free marks array of one student */
void free_student_marks(Student *s) {

    if (s->marks) {
        free(s->marks);
        s->marks = NULL;
    }

    s->marks_count = 0;
}

/* Find index by student ID */
int find_index_by_id(int id) {

    for (int i = 0; i < count; i++)
        if (arr[i].id == id)
            return i;

    return -1;
}

/* Generate next student ID */
int get_next_id(void) {

    int maxid = 0;

    for (int i = 0; i < count; i++)
        if (arr[i].id > maxid)
            maxid = arr[i].id;

    return maxid + 1;
}
