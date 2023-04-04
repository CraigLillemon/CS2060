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

	char email[SIZE];
	char password[SIZE];

	double goal;
	double percentGoal;
	double donations;
	int totalNumberOfDonations;
	double totalAmountRaised;
	double totalPaidCredit;
	char customer[SIZE];
	bool validEnd;
} company;

void getInformation(struct company* companyPtr);
void initilzeVariables(struct company* companyPtr);
double getValidGoal();
void removeNewLine(char *companyPtr);
void removeSpace(struct company* companyPtr);
void createUrl(struct company* companyPtr);
void displayOrganization(const struct company* companyPtr);
void getName(char* companyPtr);
void getDonation(struct company* companyPtr);
void getAdmin(struct company* companyPtr);


void getEmail(char* companyPtr);
void getPassword(char* companyPtr);

void Verify_Identity(const char* companyPtr, bool* validThing);

int main(void)
{
	company org;
	getInformation(&org);


	initilzeVariables(&org);
	removeNewLine(org.organization);
	removeNewLine(org.purpose);
	removeSpace(&org);
	createUrl(&org);
	displayOrganization(&org);
	getDonation(&org);


	//do
	//{
//
	//} while (org.validEnd != true);
}





void getInformation(struct company* organizationPtr)
{
	puts("Please enter organization name:");
	fgets(organizationPtr->organization, SIZE, stdin);
	puts("Please enter organization purpose");
	fgets(organizationPtr->purpose, SIZE, stdin);
	//puts("Please enter name");
	getName(organizationPtr->name);
	//fgets(organizationPtr->name, SIZE, stdin);
	getEmail(organizationPtr->email);
	getPassword(organizationPtr->password);
	puts("Please enter a a valid goal");
	organizationPtr->goal = getValidGoal();
	//getValidGoal2(&organizationPtr->goal);
}
double getValidGoal()
{
	bool validAnswer = false;
	double temp = 0;
	do
	{
		scanf("%lf", &temp);
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
void createUrl(struct company* companyPtr)
{
	char temp[SIZE];
	char temp2[SIZE];
	strcpy(temp,"https:donate.com/");
	strcpy(temp2, "?form=popup#");
	strncat(temp, companyPtr->url, SIZE);
	strncat(temp, temp2, SIZE);
	strncpy(companyPtr->url, temp, sizeof(temp));
}
void removeNewLine(char *companyPtr)
{
		size_t inputLength = strnlen(companyPtr, SIZE);

		if (inputLength > 0 && companyPtr[inputLength - 1] == '\n')
		{
			companyPtr[inputLength - 1] = '\0';
			inputLength--;
		}
}
void removeSpace(struct company *companyPtr)
{
	strncpy(companyPtr->url, companyPtr->organization, sizeof(companyPtr->organization));
	char* bufferPtr;
	bufferPtr = strchr(companyPtr->url, ' ');
	while (bufferPtr != NULL)
	{
		*bufferPtr = '-';
		bufferPtr = strchr(companyPtr->url, ' ');
	}
}
void getEmail(char* companyPtr)
{
	printf("Please enter an email: \n");
	fgets(companyPtr, SIZE, stdin);
}
void getPassword(char* companyPtr)
{
	printf("Please enter an password: \n");
	fgets(companyPtr, SIZE, stdin);
}
void displayOrganization(const struct company* companyPtr)
{
	printf("%s\n", companyPtr->url);
	printf("Organization: %s\n", companyPtr->organization);
	printf("Purpose: %s\n", companyPtr->purpose);
	printf("Total amount raised: %.2lf\n", companyPtr->totalAmountRaised);
	printf("We are %.2lf%% towards our goal of $%.2lf\n", companyPtr->percentGoal, companyPtr->goal);
}
void getDonation(struct company* companyPtr)
{
	char valid_Quit = 'Q';
	char valid_Lower_Quit = 'q';
	bool validAnswer = false;
	double try = 0;
	puts("Please enter a number greater than 0 for a donation");
	do 
	{
		puts("Test");

	scanf("%lf", &companyPtr->donations);
	double temp = companyPtr->donations;
	if (temp == 1 || temp == 'Q')
	{


		getAdmin(companyPtr);
		validAnswer = true;

	}
	else if (companyPtr->donations > 0)
	{
		validAnswer = true;
		//puts("Test2");
	}
	} 
	while (validAnswer != true);
	if (validAnswer == true && companyPtr->validEnd != true)
	{
		companyPtr->totalAmountRaised += companyPtr->donations;
		companyPtr->totalNumberOfDonations++;
	}
}
void getName(char* companyPtr)
{
	puts("Please enter name: ");
	fgets(companyPtr, SIZE, stdin);
}
void initilzeVariables(struct company* companyPtr)
{
	companyPtr->totalAmountRaised = 0;
	companyPtr->percentGoal = 0;
	companyPtr->donations = 0;
	companyPtr->totalNumberOfDonations = 0;
	companyPtr->validEnd = false;
}
void getAdmin(struct company* companyPtr)
{
	bool validEmail = false;
	bool validPassword = false;
	Verify_Identity(companyPtr->email, &validEmail);
	if (validEmail == true)
	{
		puts("It works");
	}
}
void Verify_Identity(const char* companyPtr, bool* validThing)
{
	int counter = 0;
	int test = 0;
	char tester[SIZE];
	do
	{
		fgets(tester, SIZE, stdin);
		if (test == strncmp(companyPtr, tester, strlen(companyPtr)))
		{
			*validThing = true;
			counter = 3;
		}else
		{
			puts("what?");
		}
	
		counter++;
	} while (counter < 3);
}