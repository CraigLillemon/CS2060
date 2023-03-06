// Passing Primitive Data Types and pointers
//Add comments to explain the code

#include <stdio.h>	
#include <stdlib.h>

int cubePass1(int number);
int cubePass2(int* numberPtr);

int main(void) {

	int numberMain = 5;
	int result = 0;
	//Prints value
	printf ("In main before cubePass1  numberMain = %d\n", numberMain);
	//Prints address
	printf("&numberMain = %p\n", &numberMain);
	//Sets result = to the function of cubepass1 with the argument being number main, which holds the value of 5
	//Cubepass1 prints all according information
	//Sets result = to return value which is 125
	result = cubePass1(numberMain);

	printf ("In main after cubePass1  numberMain = %d\n", numberMain);
	printf ("Result = %d\n", result);

	printf("\nIn main before cubePass2  numberMain = %d\n", numberMain);
	result = cubePass2(&numberMain);
	printf("\nIn main after cubePass2  numberMain = %d\n", numberMain);
	printf("result = %d\n", result);

} // main

//Parameter will become 5
int cubePass1 (int number) 
{
	int cube = 0;
	puts("\nIn cubePass1");
	//Value
	printf("number = %d\n", number);
	//Address
	printf("&number = %p\n", &number);
	//value to return
	cube = number * number * number;
	printf("cube  = %d\n", cube);
	//Both end up as 125
	number = cube;
	printf("number = %d\n", number);
	return cube;
} 
/*
void cubePass2(const int* const numberPtr) {
	printf("   *numberPtr = %d\n", *numberPtr);
	printf("   numberPtr = %p\n", numberPtr);
	int cube = (*numberPtr) * (*numberPtr) * (*numberPtr);
	*numberPtr = cube;
	numberPtr = &cube;
	printf("   *numberPtr = %d\n\n", *numberPtr);
}
*/

int cubePass2 (int * numberPtr) 
{
	int cube = 0;
	puts ("\nIn cubePass2");
	printf("numberPtr = %p\n", numberPtr);
	printf ("*numberPtr = %d\n", *numberPtr);
	printf("&numberPtr = %p\n", &numberPtr);
	cube = (* numberPtr )* (* numberPtr )* (* numberPtr); 
	*numberPtr = cube;
	printf ("*numberPtr = %d\n", *numberPtr);
	return cube;
} 


