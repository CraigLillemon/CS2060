/*
* The program randomly generates numbers   
* between 1 and 1000 for the user to guess.
*/
//Examination done by Craig Lillemon

// Source files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Constant min
#define MIN_NUMBER 1

// Constant max
const int MAX_NUMBER = 100;

//Call for guessGame method and check if it is correct
void guessGame(void); 
bool isCorrect(int, int); 


int main(void)
{
    //Generates the random number based on time of 0
   srand(time(0));

   //This is the part that does the chek
   guessGame(); 

   //I presume this assist in ending the program
   return 0;
}

//Guess game method, void so no return value
void guessGame(void)
{
    //
   int answer = 0; 
   int guess = 0; 
   int response = 0; 

   do {

       //Make sure that the answer generates from min to max
      answer = MIN_NUMBER + rand() % MAX_NUMBER;


      //Calls for print to display the following information
      printf("Hello, I have a number between %d and %d .\n" 
          "Can you guess my number?\n"
           "Please type your first guess.", MIN_NUMBER, MAX_NUMBER);

      //Repeates the guess the number until it is determined to be true
      do
      {
          //User input from keyboard
          scanf("%d", &guess);
      } while (!isCorrect(guess, answer));
         
      //Repeats everything until user ends 
      puts("\nExcellent! You guessed the number!\n"
         "Would you like to play again?");

      printf("%s", "Please type ( 1=yes, 2=no ) ");
      scanf("%d", &response);

      puts("");
   } while (response == 1);
} 

//Checks to see when it is true that the correct guess equals the random number
bool isCorrect(int g, int a)
{
    //Sets to default to false so it keeps repeating
    bool found = false;

    //When found that they equal each other, will stop
    if (g == a){
        found = true;
    }else  if (g < a)
      printf( "%s", "Too low. Try again.\n? " );
   else
      printf( "%s", "Too high. Try again.\n? " );

    //Return the boolean status, which if false will cause a repeat
   return found;
} 

