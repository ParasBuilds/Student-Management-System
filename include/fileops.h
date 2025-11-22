#ifndef FILEOPS_H
#define FILEOPS_H

/* fileops.h
   File read/write operations for persistent storage.
   Functions save/load to a human-readable text file.
*/

#include "student.h"

/* File operations */
void load_from_file(void);
int save_to_file(void);

#endif /* FILEOPS_H */
