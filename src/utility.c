#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "student.h"
#include "utility.h"

/* utility.c
   Input helpers and global variables.
*/

/* Define globals here (kept in utility.c per your choice A) */
Student *arr = NULL;
int count = 0;
int capacity = 0;

/* Trim trailing newline and carriage return */
void trim_newline(char *s)
{
    if (!s) return;
    int n = (int)strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r' || s[n-1] == ' ')) {
        s[n-1] = '\0';
        n--;
    }
}

void read_line(const char *prompt, char *buf, int n)
{
    if (prompt) printf("%s", prompt);
    if (fgets(buf, n, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    trim_newline(buf);
}

int read_int(const char *prompt)
{
    char tmp[128];
    while (1) {
        read_line(prompt, tmp, sizeof(tmp));
        if (strlen(tmp) == 0) continue;
        char *end;
        long v = strtol(tmp, &end, 10);
        if (end == tmp || *end != '\0') {
            printf("Invalid integer. Try again.\n");
            continue;
        }
        return (int)v;
    }
}

float read_float(const char *prompt)
{
    char tmp[128];
    while (1) {
        read_line(prompt, tmp, sizeof(tmp));
        if (strlen(tmp) == 0) continue;
        char *end;
        float v = strtof(tmp, &end);
        if (end == tmp || *end != '\0') {
            printf("Invalid number. Try again.\n");
            continue;
        }
        return v;
    }
}

char read_gender(const char *prompt)
{
    char tmp[16];
    while (1) {
        read_line(prompt, tmp, sizeof(tmp));
        if (strlen(tmp) == 0) continue;
        char c = toupper((unsigned char)tmp[0]);
        if (c == 'M' || c == 'F' || c == 'O') return c;
        printf("Enter M/F/O only.\n");
    }
}

/* Ensure enough space in dynamic student array */
void ensure_capacity(void)
{
    if (capacity == 0) {
        capacity = 4;
        arr = malloc(sizeof(Student) * capacity);
        if (!arr) { perror("malloc"); exit(1); }
    } else if (count >= capacity) {
        capacity *= 2;
        Student *tmp = realloc(arr, sizeof(Student) * capacity);
        if (!tmp) { perror("realloc"); free(arr); exit(1); }
        arr = tmp;
    }
}

/* Free marks of one student */
void free_student_marks(Student *s)
{
    if (!s) return;
    if (s->marks) {
        free(s->marks);
        s->marks = NULL;
    }
    s->marks_count = 0;
}

/* Find index in array by id */
int find_index_by_id(int id)
{
    for (int i = 0; i < count; i++) if (arr[i].id == id) return i;
    return -1;
}

/* Next ID generator */
int get_next_id(void)
{
    int maxid = 0;
    for (int i = 0; i < count; i++) if (arr[i].id > maxid) maxid = arr[i].id;
    return maxid + 1;
}
