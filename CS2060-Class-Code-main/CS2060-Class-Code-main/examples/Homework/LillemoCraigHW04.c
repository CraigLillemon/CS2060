// Fig. 6.22: fig06_22.c
// Two-dimensional array manipulations.
#include <stdio.h>
#define STUDENTS 3
#define GRADE_CATEGORIES 5
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final "
const double GRADE_CATEGORY_WEIGHT[] = { 0.1, 0.3, 0.3, 0.15, .15 };
void enterGrades( int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests);
int minimum(const int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests);
int maximum(const int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests);
double average(const int setOfGrades[], size_t tests);
void printArray(const int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests);
// function main begins program execution
int main(void)

{

    // initialize student grades for three students (rows)
    int studentGrades[STUDENTS][GRADE_CATEGORIES];
    enterGrades(studentGrades, STUDENTS, GRADE_CATEGORIES);
    // output array studentGrades
    puts("The array is:");
    printArray(studentGrades, STUDENTS, GRADE_CATEGORIES);

    // determine smallest and largest grade values
    printf("\n\nLowest grade: %d\nHighest grade: %d\n",
        minimum(studentGrades, STUDENTS, GRADE_CATEGORIES),
        maximum(studentGrades, STUDENTS, GRADE_CATEGORIES));

    // calculate average grade for each student
    for (size_t student = 0; student < STUDENTS; ++student) {
        printf("The average grade for student %u is %.2f\n",
            student, average(studentGrades[student], GRADE_CATEGORIES));
    }
}

// Find the minimum grade
int minimum(const int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests)
{
    int lowGrade = 100; // initialize to highest possible grade

    // loop through rows of grades
    for (size_t i = 0; i < pupils; ++i) {

        // loop through columns of grades
        for (size_t j = 0; j < tests; ++j) {

            if (grades[i][j] < lowGrade) {
                lowGrade = grades[i][j];
            }
        }
    }

    return lowGrade; // return minimum grade 
}

// Find the maximum grade
int maximum(const int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests)
{
    int highGrade = 0; // initialize to lowest possible grade

    // loop through rows of grades
    for (size_t i = 0; i < pupils; ++i) {

        // loop through columns of grades
        for (size_t j = 0; j < tests; ++j) {

            if (grades[i][j] > highGrade) {
                highGrade = grades[i][j];
            }
        }
    }

    return highGrade; // return maximum grade
}

// Determine the average grade for a particular student
double average(const int setOfGrades[], size_t tests)
{
    int total = 0; // sum of test grades                

    // total all grades for one student                 
    for (size_t i = 0; i < tests; ++i) {
        total += setOfGrades[i];
    }

    return (double)total / tests; // average         
}

// Print the array
void printArray(const int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests)
{
    // output column heads
    printf("%s", "                 [0]  [1]  [2]  [3]");

    // output grades in tabular format
    for (size_t i = 0; i < pupils; ++i) {

        // output label for row
        printf("\nstudentGrades[%u] ", i);
        // output grades for one student
        for (size_t j = 0; j < tests; ++j) {
            printf("%-5d", grades[i][j]);
        }
    }
}
void enterGrades(int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests)
{
    for (size_t row = 0; row < pupils; row++)
    {
        printf("%s\n", CATEGORIES);
        for (size_t column = 0; column < tests; column++)
        {
            printf("Enter value table grades [%d] [%d]\n", row, column);
            scanf("%d", &grades[row][column]);
        }

    }
    //return grades[pupils][tests];
}