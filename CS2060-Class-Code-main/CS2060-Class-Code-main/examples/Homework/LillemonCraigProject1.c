#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define SIZE 80

typedef struct company
{
	char organization[SIZE];
	char purpose[SIZE];
	char name[SIZE];
	char url[SIZE];
	unsigned int goal;
	int totalNumberOfDonations;
	int totalAmountRaised;
	int totalPaidCredit;
} company;
struct user
{
	char email[SIZE];
	char password[SIZE];
};

void  exploreValidateInt(const char* buff);
bool validateInt(char* buff, int* const validInt);
void printLimits();
void getInformation(char* companyPtr);
void getInformation2(struct company* companyPtr);
int getValidGoal();
void getValidGoal2(int* test);
int main(void)
{
	company org;
	//getInformation(&org.organization);
	//getInformation(&org.purpose);
	//getInformation(&org.name);
	getInformation2(&org);
	printf("Test 1 %s\n", org.organization);
	printf("Test 2 %d\n", org.goal);
}



void printLimits()
{

}


void  exploreValidateInt(const char* buff)
{

}
void getInformation2(struct company* organizationPtr)
{
	puts("Please enter organization name:");
	fgets(organizationPtr->organization, SIZE, stdin);
	puts("Please enter organization purpose");
	fgets(organizationPtr->purpose, SIZE, stdin);
	puts("Please enter name");
	fgets(organizationPtr->name, SIZE, stdin);
	puts("Please enter a a valid goal");
	organizationPtr->goal = getValidGoal();
	//getValidGoal2(&organizationPtr->goal);
}
void getInformation(char* companyPtr)
{
	fgets(companyPtr, SIZE, stdin);
}
int getValidGoal()
{
	bool validAnswer = false;
	int temp = 0;
	do
	{
		scanf("%d", &temp);
		if (temp > 0)
		{
			validAnswer = true;
		}
		else
		{
			puts("Please enter a valid goal that is greater than 0 ");
		}
	} while (validAnswer != true);
	return temp;
}
void getValidGoal2(int* test)
{
	bool validAnswer = false;
	do
	{
		scanf("%d", &test);
		if (test > 0)
		{
			validAnswer = true;
		}
		else
		{
			puts("Please enter a valid goal that is greater than 0 ");
		}
	} while (validAnswer != true);
}
void createUrl(char* organizationPtr)
{

}
void removeNewLine(char* pointer)
{
	for (unsigned int counter = 1; counter < 6; counter++)
	{


		//fgets(inputStr, LENGTH, stdin);
		//temp = strtod(inputStr, &ptr);

		//validAnswer = validateInt(inputStr, &temp);

		size_t inputLength = strnlen(pointer, SIZE);

		if (inputLength > 0 && pointer[inputLength - 1] == '\n')
		{
			pointer[inputLength - 1] = '\0';
			inputLength--;
		}

	}
}
