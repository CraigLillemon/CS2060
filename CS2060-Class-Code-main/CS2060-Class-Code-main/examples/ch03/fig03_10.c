// Fig. 3.10: fig03_10.c
// Analysis of examination results 
#include <stdio.h>

// function main begins program execution 
int main( void )
{
    printf("It works");
   // initialize variables in definitions 
   unsigned int passes = 0; // number of passes   
   unsigned int failures = 0; // number of failures 
   unsigned int student = 1; // student counter    
   int result = 0; // one exam result 
   // process 10 students using counter-controlled loop 
   while ( student <= 10 ) {

      // prompt user for input and obtain value from user 
       do  {
           printf("%s", "Enter result ( 1=pass,2=fail ): ");
           scanf("%d", &result);

           // if result 1, increment passes 
           if (result == 1) {
               passes = passes + 1;
           } // end if 
           else if (result ==2){ // otherwise, increment failures 
               failures = failures + 1;
           } // end else 
       } while (result != 1 &&  result !=2);
       //Repeats unless result is 1 or 2
      student = student + 1; // increment student counter  
   } // end while 

   // termination phase; display number of passes and failures 
   printf( "Passed %u\n", passes );
   printf( "Failed %u\n", failures );

   // if more than eight students passed, print "Bonus to instructor!" 
   if ( passes > 8 ) {
      puts( "Bonus to instructor!" );
   } // end if 
} // end function main 




/**************************************************************************
 * (C) Copyright 1992-2013 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or im
 plied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/

