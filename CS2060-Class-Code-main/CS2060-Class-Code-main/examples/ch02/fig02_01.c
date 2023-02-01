// Fig. 2.1: fig02_01.c
// A first program in C 
#include <stdio.h>

// function main begins program execution 
int main( void )
{
	//Initialize variable
	double length = 0;
	double width = 0;
	double area = 0;
   printf( "Welcome to C!\n" );
   //Length ask, and input
   printf("%s", "Enter length\n");
   scanf("%lf", &length);
   //Width ask and input
   printf("%s", "Enter width\n");
   scanf("%lf", &width);
   //Area calculation 
   area = length * width;
   printf("%s%.1f%s%.1f%s%.1f\n", "Length: ", length,  " Width : ", width,  " Area : ", area );
   //calculate average difference 
   double average = length / width;
   //Print difference, up to the .1 decimal spot, should there be decimals 
   printf("%s%.1f", "Average value is ", average);
} // end function main 


/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
