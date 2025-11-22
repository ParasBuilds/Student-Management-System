#ifndef UTILITY_H
#define UTILITY_H

/* utility.h
   Helpers for input, dynamic array and global variables.
*/

#include "student.h"

/* globals (defined in utility.c) */
extern Student *arr;
extern int count;
extern int capacity;

/* Input helpers */
void trim_newline(char *s);
void read_line(const char *prompt, char *buf, int n);
int read_int(const char *prompt);
float read_float(const char *prompt);
char read_gender(const char *prompt);

/* Dynamic array helpers */
void ensure_capacity(void);
int find_index_by_id(int id);
int get_next_id(void);
void free_student_marks(Student *s);

#endif /* UTILITY_H */
