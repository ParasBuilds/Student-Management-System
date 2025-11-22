#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/student.h"
#include "../include/fileops.h"
#include "../include/utilility.h"

/*
   fileops.c
   ---------
   This file handles reading from and writing to the text file
   (students.txt). This keeps data persistent between program runs.
*/

extern Student *arr;
extern int count;
extern int capacity;

/* Load student records from the text file */
void load_from_file(void) {

    FILE *fp = fopen("students.txt", "r");
    if (!fp)
        return; // file may not exist on first run

    char line[512];

    while (fgets(line, sizeof(line), fp)) {

        trim_newline(line);
        if (strlen(line) == 0) continue;

        Student s;
        s.marks = NULL;
        s.marks_count = 0;

        char *tok, *save;
        tok = strtok_r(line, "|", &save);
        if (!tok) continue;
        s.id = atoi(tok);

        tok = strtok_r(NULL, "|", &save);
        strcpy(s.name, tok);

        tok = strtok_r(NULL, "|", &save);
        s.age = atoi(tok);

        tok = strtok_r(NULL, "|", &save);
        s.gender = tok[0];

        tok = strtok_r(NULL, "|", &save);
        strcpy(s.course, tok);

        tok = strtok_r(NULL, "|", &save);
        s.gpa = atof(tok);

        tok = strtok_r(NULL, "|", &save);
        s.marks_count = atoi(tok);

        if (s.marks_count > 0) {
            s.marks = malloc(sizeof(int) * s.marks_count);

            char *marks_str = strtok_r(NULL, "|", &save);
            char *m_tok, *m_save;
            int i = 0;

            m_tok = strtok_r(marks_str, ",", &m_save);
            while (m_tok && i < s.marks_count) {
                s.marks[i++] = atoi(m_tok);
                m_tok = strtok_r(NULL, ",", &m_save);
            }
        }

        ensure_capacity();
        arr[count++] = s;
    }

    fclose(fp);
}

/* Save all student records into the file */
int save_to_file(void) {

    FILE *fp = fopen("students.txt", "w");
    if (!fp) return ERR;

    for (int i = 0; i < count; i++) {
        Student *s = &arr[i];

        fprintf(fp, "%d|%s|%d|%c|%s|%.2f|%d|",
                s->id, s->name, s->age, s->gender,
                s->course, s->gpa, s->marks_count);

        for (int j = 0; j < s->marks_count; j++) {
            fprintf(fp, "%d", s->marks[j]);
            if (j < s->marks_count - 1) fprintf(fp, ",");
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
    return OK;
}
