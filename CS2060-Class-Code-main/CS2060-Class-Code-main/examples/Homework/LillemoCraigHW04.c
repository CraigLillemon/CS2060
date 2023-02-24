// Fig. 6.22: fig06_22.c
// Two-dimensional array manipulations.
#include <stdio.h>
#include <math.h>
#define STUDENTS 4
#define GRADE_CATEGORIES 5
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final "
const double  A_LETTER = 90;
const double  B_LETTER = 80;
const double  C_LETTER = 70;
const double  D_LETTER = 60;
const double GRADE_CATEGORY_WEIGHT[] = { 0.1, 0.3, 0.3, 0.15, .15 };
double gradeAverage[] = { 0,0,0,0,0 };
double getGPA(const int setOfGrades[], size_t tests);
void enterGrades( int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests);
char getLetter( double finalGrades);
double average(const int setOfGrades[], size_t tests);
void printArray(const int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests);
// function main begins program execution
int main(void)

{
    double classAverage = 0;
    double finalGrade[GRADE_CATEGORIES] = { 0,0,0,0,0 };
    // initialize student grades for three students (rows)
    int studentGrades[STUDENTS][GRADE_CATEGORIES];
    enterGrades(studentGrades, STUDENTS, GRADE_CATEGORIES);
   
    
    // output array studentGrades
    puts("The array is:");
    printArray(studentGrades, STUDENTS, GRADE_CATEGORIES);

    // calculate average grade for each student
    for (size_t student = 0; student < STUDENTS; ++student) {
        finalGrade[student] = getGPA(studentGrades[student], GRADE_CATEGORIES);
        printf("\nStudent %u:  %.1f  %c\n",
            (student + 1), finalGrade[student], getLetter(finalGrade[student]));
        classAverage += finalGrade[student];
    }
    printf("%s %.1lf", "The class Average is", (classAverage / STUDENTS));
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
    printf("%s\n", CATEGORIES);
    for (size_t row = 0; row < pupils; row++)
    {
       
        for (size_t column = 0; column < tests; column++)
        {
            printf("Enter value table grades [%d] [%d]\n", row, column);
            scanf("%d", &grades[row][column]);
        }

    }
}
double getGPA(const int setOfGrades[], size_t tests)
{
    double total = 0;
    for (size_t i = 0; i < tests; ++i) 
    {
        total += (setOfGrades[i] * GRADE_CATEGORY_WEIGHT[i]);
    }
    return total;
}

char getLetter(const double finalGrades)
{
    char letter = 'F';
        if (finalGrades >= A_LETTER)
        {
            letter = 'A';
        }
        else if (finalGrades < A_LETTER && finalGrades >= B_LETTER)
        {
            letter = 'B';
        }
        else if (finalGrades < B_LETTER && finalGrades >= C_LETTER)
        {
            letter = 'C';

        }
        else if (finalGrades < C_LETTER && finalGrades >= D_LETTER)
        {
            letter = 'D';
        }
    return letter;
}
