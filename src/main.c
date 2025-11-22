#include <stdio.h>

/* Including headers for all modules */
#include "../include/student.h"
#include "../include/utility.h"
#include "../include/fileops.h"
#include "../include/extras.h"

/* 
   main.c
   -------
   This is the entry point of the program. It mainly loads existing data,
   then shows the menu repeatedly until the user exits.
*/

void menu(); // forward declaration

int main() {

    printf("Student Management System (Modular Version)\n");

    /* Load any previously saved student records */
    load_from_file();

    /* Start the menu loop */
    menu();

    return 0;
}

/* The main menu options */
void menu() {

    while (1) {

        printf("\n=== Student Management System ===\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Modify Student\n");
        printf("5. Delete Student\n");
        printf("6. Sort by ID\n");
        printf("7. Sort by Name\n");
        printf("8. Extras (Recursion + Pointer Demo)\n");
        printf("9. 2D Marks Matrix Demo\n");
        printf("10. Exit\n");

        int choice = read_int("Enter your choice: ");

        if (choice == 1) add_student();
        else if (choice == 2) display_all();
        else if (choice == 3) search_student();
        else if (choice == 4) modify_student();
        else if (choice == 5) delete_student();
        else if (choice == 6) sort_by_id();
        else if (choice == 7) sort_by_name();
        else if (choice == 8) extras_demo();
        else if (choice == 9) marks_matrix_demo();
        else if (choice == 10) {

            /* Free all dynamic memory before exiting */
            extern Student *arr;
            extern int count;
            for (int i = 0; i < count; i++)
                free_student_marks(&arr[i]);

            free(arr);

            printf("Exiting program...\n");
            break;
        }
        else {
            printf("Invalid choice, please try again.\n");
        }
    }
}
