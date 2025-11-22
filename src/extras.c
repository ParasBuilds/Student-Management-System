#include <stdio.h>
#include <stdlib.h>

#include "../include/extras.h"
#include "../include/utility.h"

/*
   extras.c
   ---------
   Small extra functions to show recursion, pointers and 2D arrays.
   These are included to cover syllabus points from Unit III/IV.
*/

/* Recursive factorial function */
long factorial(long n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

/* Simple pointer swap demonstration */
void pointer_demo(void) {

    int a = 10, b = 20;

    printf("Before swap: a=%d b=%d\n", a, b);

    int *pa = &a;
    int *pb = &b;

    int temp = *pa;
    *pa = *pb;
    *pb = temp;

    printf("After swap: a=%d b=%d\n", a, b);
}

/* Calls both recursion + pointer demos */
void extras_demo(void) {

    int n = read_int("Enter a number for factorial: ");
    printf("Factorial = %ld\n", factorial(n));
    pointer_demo();
}

/* 2D array demo using dynamic memory */
void marks_matrix_demo(void) {

    int rows = read_int("Enter number of students: ");
    int cols = read_int("Enter subjects per student: ");

    if (rows <= 0 || cols <= 0)
        return;

    int *matrix = malloc(sizeof(int) * rows * cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            char msg[64];
            sprintf(msg, "Marks of Student %d Subject %d: ", i + 1, j + 1);
            matrix[i * cols + j] = read_int(msg);
        }

    printf("\nMatrix:\n");
    for (int i = 0; i < rows; i++) {
        printf("Student %d: ", i + 1);
        for (int j = 0; j < cols; j++)
            printf("%d ", matrix[i * cols + j]);
        printf("\n");
    }

    free(matrix);
}
