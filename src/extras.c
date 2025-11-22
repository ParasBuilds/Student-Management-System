#include <stdio.h>
#include <stdlib.h>

#include "extras.h"
#include "utility.h"

/* extras.c - small demos for recursion, pointers and 2D arrays */

long factorial(long n)
{
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

void pointer_demo(void)
{
    int a = 10, b = 20;
    printf("Before swap: a=%d b=%d\n", a, b);
    int *pa = &a, *pb = &b;
    int tmp = *pa;
    *pa = *pb;
    *pb = tmp;
    printf("After swap: a=%d b=%d\n", a, b);
}

void extras_demo(void)
{
    int n = read_int("Enter number for factorial: ");
    printf("Factorial = %ld\n", factorial(n));
    pointer_demo();
}

void marks_matrix_demo(void)
{
    int rows = read_int("Number of students: ");
    int cols = read_int("Subjects per student: ");
    if (rows <= 0 || cols <= 0) return;

    int *matrix = malloc(sizeof(int) * rows * cols);
    if (!matrix) { printf("Memory error\n"); return; }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            char prompt[64];
            sprintf(prompt, "Marks of Student %d Subject %d: ", i + 1, j + 1);
            matrix[i * cols + j] = read_int(prompt);
        }

    printf("\nMatrix:\n");
    for (int i = 0; i < rows; i++) {
        printf("Student %d: ", i + 1);
        for (int j = 0; j < cols; j++) printf("%d ", matrix[i * cols + j]);
        printf("\n");
    }

    free(matrix);
}
