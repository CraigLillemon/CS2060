#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
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
	char zip[SIZE];
	char receipt[SIZE];
	double currentPercent;
	char quit[SIZE];
	bool validEnd;
} company;

void getInformation(struct company* companyPtr);
void initilzeVariables(struct company* companyPtr);
void getValidGoal(double* goal);
void removeNewLine(char *companyPtr);
void removeSpace(struct company* companyPtr);
void createUrl(struct company* companyPtr);
void displayOrganization(const struct company* companyPtr);
void getName(char* companyPtr);
void getDonation(struct company* companyPtr);
void getAdmin(struct company* companyPtr);


void getEmail(char* companyPtr);
void getPassword(char* companyPtr);

void verify_Identity(const char* companyPtr, bool* validThing);

void getNumber(double* companyPtr, char* quit);
void donationSum(struct company* companyPtr);

void getZip(struct company* companyPtr);
void validZip( char* companyPtr, bool* valid);
void createReceipt(const struct company* companyPtr);
void displayReceipt(const struct company* companyPtr);

void displayTotalEarned(const struct company* companyPtr);

int main(void)
{
	company org;
	getInformation(&org);
	initilzeVariables(&org);
	removeNewLine(org.organization);
	removeNewLine(org.purpose);
	removeSpace(&org);
	createUrl(&org);
	do
	{
		displayOrganization(&org);
		getDonation(&org);
	} while (org.validEnd != true);
	displayTotalEarned(&org);
}





void getInformation(struct company* organizationPtr)
{
	puts("Please enter organization name:");
	fgets(organizationPtr->organization, SIZE, stdin);

	puts("Please enter organization purpose");
	fgets(organizationPtr->purpose, SIZE, stdin);

	getName(organizationPtr->name);

	getEmail(organizationPtr->email);
	getPassword(organizationPtr->password);

	puts("Please enter a a valid goal");
	getValidGoal(&organizationPtr->goal);
}
void getValidGoal(double* goal)
{
	bool validAnswer = false;
	char test[SIZE];
	do
	{
		getNumber(&*goal, &*test);
		double temp = *goal;
		if (temp != '\0')
		{
			if (*goal > 0)
			{
				validAnswer = true;
			}
			else
			{
				puts("Please enter a valid goal that is greater than 0 ");
			}
		}
	} while (validAnswer != true);
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
	printf("\n%s\n", companyPtr->url);
	printf("Organization: %s\n", companyPtr->organization);
	printf("Purpose: %s\n", companyPtr->purpose);
	printf("Total amount raised: %.2lf\n", companyPtr->totalAmountRaised);
	printf("We are %.2lf%% towards our goal of $%.2lf\n", companyPtr->percentGoal, companyPtr->goal);
}
void getDonation(struct company* companyPtr)
{
	bool validAnswer = false;
	do 
	{
		getNumber(&companyPtr->donations, companyPtr->quit);
		removeNewLine(&*companyPtr->quit);
	if (strpbrk(companyPtr->quit, "q")||strpbrk(companyPtr->quit, "Q"))
	{
		getAdmin(companyPtr);
		validAnswer = true;
	}
	else if (companyPtr->donations > 0)
	{
		validAnswer = true;
	}
	} while (validAnswer != true);

	if (validAnswer == true && companyPtr->validEnd != true)
	{
		getZip(companyPtr);
		createReceipt(companyPtr);
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
	companyPtr->totalPaidCredit = 0;
	companyPtr->percentGoal = 0;
	companyPtr->donations = 0;
	companyPtr->totalNumberOfDonations = 0;
	companyPtr->validEnd = false;
	companyPtr->currentPercent = 0;
}
void getAdmin(struct company* companyPtr)
{
	bool validEmail = false;
	bool validPassword = false;
	puts("Please enter email");
	verify_Identity(companyPtr->email, &validEmail);
	if (validEmail == true)
	{
		puts("Please enter Password");
		verify_Identity(companyPtr->password, &validPassword);
		if (validPassword == true)
		{
			companyPtr->validEnd = true;
		}
	}
}
void verify_Identity(const char* companyPtr, bool* validThing)
{
	int counter = 1;
	int test = 0;
	char tester[SIZE];
	do
	{
		fgets(tester, SIZE, stdin);
		if (test == strncmp(companyPtr, tester, strlen(companyPtr)))
		{
			*validThing = true;
			counter = 0;
		}else
		{
			printf("%d chances left\n", counter);
		}
	
		counter--;
	} while (counter >= 0);
	if (*validThing == false)
	{
		puts("Going back to donor mode");
	}
}
void getNumber(double* companyPtr, char* quit)
{
	char temp[SIZE];
	char* ptr;
	puts("Please enter number");
	fgets(temp, SIZE, stdin);
	*companyPtr = strtod(temp, &ptr);
	strncpy(quit, ptr, sizeof(&ptr));
}
void donationSum(struct company* companyPtr)
{
	double processFee = 0.029;
	double temp = companyPtr->donations * processFee;
	double temp2 = companyPtr->donations - temp;
	companyPtr->totalPaidCredit += temp;
	companyPtr->totalAmountRaised += temp2;
	companyPtr->percentGoal = (companyPtr->totalAmountRaised / companyPtr->goal)*100;
	companyPtr->totalNumberOfDonations++;
	printf("\nThank you for the donation the there is a %.2lf%% credit card fee of $%.2lf. $%.2lf will be donated\n", (processFee * 100), companyPtr->donations, temp2);
}
void getZip(struct company* companyPtr)
{
	bool valid = false;
	do
	{
		puts("Enter Zip");
		fgets(companyPtr->zip, SIZE, stdin);
		removeNewLine(companyPtr->zip);
		validZip(companyPtr->zip, &valid);
	} while (valid != true);
	donationSum(companyPtr);
}
void validZip(char* companyPtr, bool* valid)
{
	int temp = strlen(companyPtr);
	if(isdigit(*companyPtr))
	{
		if (temp == 5)
		{
			if (companyPtr[0] != '0')
			{
				*valid = true;
			}
		}
	}
}
void createReceipt(const struct company* companyPtr)
{
	bool validChoice = false;
	char temp[SIZE];
	do 
	{
		puts("Do you want a receipt, (y)es or (n)o ? ");
		fgets(temp, SIZE, stdin);
		removeNewLine(&*temp);
		if (strpbrk(temp, "y") || strpbrk(temp, "Y"))
		{
			displayReceipt(companyPtr);
			validChoice = true;
		}
		else if (strpbrk(temp, "n") || strpbrk(temp, "N"))
		{
			validChoice = true;
		}
		else
		{
			puts("Please enter y/n or Y/N");
		}
	} while (validChoice != true);
}
void displayReceipt(const struct company* companyPtr)
{
	time_t curtime;
	time(&curtime);
	printf("Organization: %s\n", companyPtr->organization);
	printf("Donation Amount: $%.2lf\n", companyPtr->donations);
	printf("%s\n", ctime(&curtime));
}
void displayTotalEarned(const struct company* companyPtr)
{
	printf("Organization: %s\n", companyPtr->organization);
	printf("Total amount of donations: %d\n", companyPtr->totalNumberOfDonations);
	printf("Total amount raised: $%.2lf\n", companyPtr->totalAmountRaised);
	printf("Total amount that paid for credit card processing: $%.2lf\n", companyPtr->totalPaidCredit);
}