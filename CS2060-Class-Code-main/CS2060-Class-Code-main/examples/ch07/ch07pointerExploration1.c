/*******************
 Understanding pointers

 Add comments to explain the code
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
	int *houseNumPtr = NULL;
	houseNumPtr = &houseNum;
	//Prints the value stored
	printf("houseNum %d\n", houseNum);
	//Prints the address of the houseNum
	printf("&houseNum %p\n\n", &houseNum);
	//Points to the value stored in address 
	//Prints the value stored in the address of the pointer, which holds the address of house num 
	printf ("*houseNumPtr  %d\n", *houseNumPtr);
	//Prints the address of houseNum
	printf ("houseNumPtr %p\n\n", houseNumPtr);
	//Prints the address of houseNumPtr which inside the address is the address of the housenum, which holds the values 
	printf ("&houseNumPtr %p\n\n", &houseNumPtr);
	//Points to the values stored in the address, which is 13 for both
	calcHouseNum1 =  *houseNumPtr + *houseNumPtr;
	//Prints the value stored
	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1);
	//Says to 2 times the pointer value stored at the address 
	calcHouseNum2 = 2 * (*houseNumPtr);
	//Prints the value stored
	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2);
	//Prints the address stored within houseNumPtr
	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", &*houseNumPtr, *&houseNumPtr);
			
	return 0;
}
