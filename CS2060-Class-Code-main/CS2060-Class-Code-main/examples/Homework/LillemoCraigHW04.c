/*
* Craig Lillemon 2/24/2023
* Due 2/24/2023
* HW04 
* Using multi Dimisonal arrays take inputs from multiple students in which each student contains multiple grade category assignments, get valid input
* Display the grades, then use grade categories which is an array to calculate the final grade, then store the final grades in a 1d array
* Caluclate and display class average
* Round all numbers that display to the nearest .1
* Display letter grade according to student
*/
#include <stdio.h>
#define STUDENTS 80
#define GRADE_CATEGORIES 5
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final "
//if want to change the weights in acordance with each cateogory they follow the trend above
const double GRADE_CATEGORY_WEIGHT[] = { 0.1, 0.3, 0.3, 0.15, .15 };
//Tried using const unsigned ints, to create a min max value for valid grade input
//got warnings, just curious to know how can I change that
#define MIN_GRADE  0
#define MAX_GRADE 105
//Gets a if >= 90
const double  A_LETTER = 90;
//Gets B if >= 80 while being less than A letter
const double  B_LETTER = 80;
//Repeats like above
const double  C_LETTER = 70;
const double  D_LETTER = 60;
//function prototypes

void getInfo(char test[]);

//Personal note for Craig (me), it may say prototype, does not mean optinal, always include.
double getGPA(const int setOfGrades[], size_t tests);
void enterGrades( int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests);
char getLetter( double finalGrades);
double getClassAverage(const double grades);
void printArray(const int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests);
// function main begins program execution
int main(void)

{
    //Initalize to restrict
    char example[STUDENTS];
    //char example2[STUDENTS];
    getInfo(example);
    printf("%s\n", example);
    double classAverage = 0;
    double finalGrade[GRADE_CATEGORIES] = { 0,0,0,0,0 };
    int studentGrades[STUDENTS][GRADE_CATEGORIES];
    //Prints information
    printf("%s\n", CATEGORIES);
    //Prints weights with acording information
    for (size_t activites = 0; activites < GRADE_CATEGORIES; ++activites) {
        printf("Category %d is %.2lf\n", (activites+1), GRADE_CATEGORY_WEIGHT[activites]);
    }
    //Input grades, from 0 105, can bechanged as it is const on top
    enterGrades(studentGrades, STUDENTS, GRADE_CATEGORIES);
   
    
    // output array studentGrades
    printArray(studentGrades, STUDENTS, GRADE_CATEGORIES);
  
   
    // calculate final grade for each student
    for (size_t student = 0; student < STUDENTS; ++student) {
        //Determines the weight of the grades, set the information recieved to an 1d array to store and display
        finalGrade[student] = getGPA(studentGrades[student], GRADE_CATEGORIES);
        printf("\nStudent %u:  %.1f  %c\n",
            (student + 1), finalGrade[student], getLetter(finalGrade[student]));
        //Sums up final grades to calculate average easy
        classAverage += finalGrade[student];
    }
    //Prints class average
    printf("%s %.1lf", "The class Average is", getClassAverage(classAverage));
}

// Determines the total class average final grades after weight
double getClassAverage(const double grades)
{
    double total = grades / STUDENTS;
    return total;
}
//Prints array according to student input grades
void printArray(const int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests)
{
    // output column heads


    // output grades in tabular format
    for (size_t i = 0; i < pupils; ++i) {

        // output label for row
        printf("\nstudentGrades %u: ", i);
        // output grades for one student
        for (size_t j = 0; j < tests; ++j) {
            printf("%-5d", grades[i][j]);
        }
    }
}
//Takes input from multi dimsional array, with studenty and grades categories as the sizes, 
void enterGrades(int grades[][GRADE_CATEGORIES], size_t pupils, size_t tests)
{
    printf("%s\n", CATEGORIES);
    //Student for loop 
    for (size_t row = 0; row < pupils; row++)
    {
       
        //Grade category for loop
        for (size_t column = 0; column < tests; column++)
        {
            //Ensure that grades are valid, uses a do while loop to ensure, if not clears buffer and restarts on current array, to get proper input
            do 
            {
                printf("\nEnter grade for each category  for student [%d], category [%d]:", (row+1), (column+1));
                scanf("%d", &grades[row][column]);
            } 
            while ((grades[row][column] < MIN_GRADE) || (grades[row][column] > MAX_GRADE));
        }

    }
}
//Determines the total final grade, after weights
double getGPA(const int setOfGrades[], size_t tests)
{
    double total = 0;
    for (size_t i = 0; i < tests; ++i) 
    {
        total += (setOfGrades[i] * GRADE_CATEGORY_WEIGHT[i]);
    }
    return total;
}
//Ensure that final grade asscocaties with proper, easily interchangable ontop as it is a const.
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
void getInfo(char information[] )
{
    scanf("%s", information);
}
