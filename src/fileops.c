#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "fileops.h"
#include "utility.h"

/* fileops.c
   Read/write student records in a simple '|' separated text file.
   Format per line:
   id|name|age|gender|course|gpa|marks_count|m1,m2,m3
*/

extern Student *arr;
extern int count;

/* trim_newline is in utility.c */

void load_from_file(void)
{
    FILE *fp = fopen("students.txt", "r");
    if (!fp) return;

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        if (strlen(line) == 0) continue;

        Student s;
        s.marks = NULL;
        s.marks_count = 0;

        char *tok = NULL;

        tok = strtok(line, "|");
        if (!tok) continue;
        s.id = atoi(tok);

        tok = strtok(NULL, "|");
        if (!tok) continue;
        strncpy(s.name, tok, sizeof(s.name));
        s.name[sizeof(s.name)-1] = '\0';

        tok = strtok(NULL, "|");
        s.age = atoi(tok ? tok : "0");

        tok = strtok(NULL, "|");
        s.gender = tok ? tok[0] : 'O';

        tok = strtok(NULL, "|");
        if (tok) { strncpy(s.course, tok, sizeof(s.course)); s.course[sizeof(s.course)-1] = '\0'; }
        else s.course[0] = '\0';

        tok = strtok(NULL, "|");
        s.gpa = tok ? atof(tok) : 0.0f;

        tok = strtok(NULL, "|");
        s.marks_count = tok ? atoi(tok) : 0;

        tok = strtok(NULL, "|"); /* marks list as comma separated */

        if (s.marks_count > 0 && tok != NULL) {
            s.marks = malloc(sizeof(int) * s.marks_count);
            if (s.marks) {
                int i = 0;
                char *m_tok = strtok(tok, ",");
                while (m_tok != NULL && i < s.marks_count) {
                    s.marks[i++] = atoi(m_tok);
                    m_tok = strtok(NULL, ",");
                }
            } else s.marks_count = 0;
        }

        ensure_capacity();
        arr[count++] = s;
    }

    fclose(fp);
}

int save_to_file(void)
{
    FILE *fp = fopen("students.txt", "w");
    if (!fp) return -1;

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
    return 0;
}
