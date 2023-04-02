#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define LENGTH 13

void  exploreValidateInt(const char* buff);
bool validateInt(char* buff, int* const validInt);
void printLimits();

int main(void)
{
	char inputStr[LENGTH]; // create char arintray
	//int temp;
	//char *ptr;
	printLimits();

	puts("\nEnter an integer");
	fgets(inputStr, LENGTH, stdin);
	for (unsigned int counter = 1; counter < 6; counter++)
	{
		

			//fgets(inputStr, LENGTH, stdin);
			//temp = strtod(inputStr, &ptr);
			
			//validAnswer = validateInt(inputStr, &temp);
		
		size_t inputLength = strnlen(inputStr, LENGTH);

		if (inputLength > 0 && inputStr[inputLength - 1] == '\n')
		{
			inputStr[inputLength - 1] = '\0';
			inputLength--;
		}

	}
	exploreValidateInt(inputStr);



}



void printLimits()
{
	printf("The number of bits in a byte %d\n", CHAR_BIT);

	printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
	printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
	printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);

	printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
	printf("The maximum value of SHORT INT = %d\n", SHRT_MAX);

	printf("The minimum value of INT = %d\n", INT_MIN);
	printf("The maximum value of INT = %d\n", INT_MAX);

	printf("The minimum value of CHAR = %d\n", CHAR_MIN);
	printf("The maximum value of CHAR = %d\n", CHAR_MAX);

	printf("The minimum value of LONG = %ld\n", LONG_MIN);
	printf("The maximum value of LONG = %ld\n", LONG_MAX);
}


void  exploreValidateInt(const char* buff)
{
	// declare pointer to a char that will be passed to strotol
	char* end;
	//The errno is set to zero at program startup and set to ERANGE if out of range when  strtol tries to convert to double
	errno = 0;
	//store integer when it is valid
	int validInt = 0;
	bool test = false;
	//An int value is given with the string, derefrenced character ptr, and base
	long intTest = strtol(buff, &end, 10);
	//if end charachter is = to the passed character of buff it checks if character
	if (end == buff) {
		fprintf(stderr, "%s: not a decimal number\n", buff);
	}
	//If the value stored on before end is not a number it checks the characters 
	else if ('\0' != *end) {
		fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
	}
	//If value exceeds long data type of bytes using the range functions  will warn out of range
	else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
		fprintf(stderr, "%s out of range of type long\n", buff);
	}
	//If value exceeds the int data type of bytes using the range function will warn out of range with the value grabbed inttest
	else if (intTest > INT_MAX) {
		fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
	}
	//Sees if the values i exceeds minumumn of data type, will warn out of range.
	else if (intTest < INT_MIN) {
		fprintf(stderr, "%ld less than INT_MIN\n", intTest);
	}
	else {
		//Grabs the long value and converts to an int, 
		validInt = (int)intTest;
		test = validateInt(buff, validInt);
		printf("%d is integer value \n", validInt);
	}
}
bool validateInt(char* buff, int* const validInt)
{
	
	bool validAnswer = false;
	if (validInt > INT_MAX && validInt < INT_MIN) {
		validAnswer = true;
	}
	return validAnswer;
}

