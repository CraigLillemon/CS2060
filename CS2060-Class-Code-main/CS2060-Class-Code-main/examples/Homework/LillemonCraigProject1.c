/*
* Craig Lillemon
* Due April 5 2023 at 11:59 pm
* This code will create a charity org which will then have a email and password requriment
* it will also create a url based off the org name
It will then go into donation mode to see what the donator will donate, name, and zip code ensuring that the zip is a number, and 5 digits long, with no 0 spot in the first character
when wanting to end the program the user must enter the exit condition of the letter q and ensure that password and email within 2 attempts, if fail go back to donor mode
if success display all according information of total raised, and number of people and so on
*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#define SIZE 80
#define PROCESSINGFEE 0.029
#define ZIPDIGITS 5
#define ATTEMPTS 1
typedef struct company
{
	//org
	char organization[SIZE];
	char purpose[SIZE];
	char name[SIZE];
	char url[SIZE];
	//user info
	char email[SIZE];
	char password[SIZE];
	//summary and getting info
	double goal;
	double percentGoal;
	double donations;
	unsigned int totalNumberOfDonations;
	double totalAmountRaised;
	double totalPaidCredit;
	//Customer info
	char customer[SIZE];
	char zip[SIZE];
	char receipt[SIZE];
	double currentPercent;
	//To end program info 
	char quit[SIZE];
	bool validEnd;
	//Linked lists
	struct company* nextPtr;
} company;

void getInformation(struct company* companyPtr);
void initilzeVariables(struct company* companyPtr);
void getValidGoal(double* goal);
void removeNewLine(char *companyPtr);
void removeSpace(struct company* companyPtr);
void createUrl(struct company* companyPtr);
void displayOrganization(company* companyPtr);
void getName(char* companyPtr);
void getDonation(struct company* companyPtr, bool* validEnd);
void getAdmin(struct company* companyPtr, bool* validEnd);


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
char validateYesNo();

void insertOrganization(company** organization);
void selectOrganization(company** organization, bool* validEnd);
int main(void)
{
	char yesOrNo;
	bool validEnd = false;
	company* org = NULL;
	do
	{

		insertOrganization(&org);
		

		// why does insert node pass the address of head pointer but print list does not?

		printf("%s", "\nDo you want to add another Organization? ");
		 yesOrNo = validateYesNo();
	} while (yesOrNo == 'y');
	//Could put these in getinformation 
	do
	{
		selectOrganization(&org, &validEnd);
	} while (validEnd != true);
	//selectOrganization(&org);
	//displayTotalEarned(&org);
}


//Other parts like remove new line and get number are at the bottom as it is needed for other parts

//Part 1 get orginzation information
void getInformation(struct company* organizationPtr)
{
	puts("Please enter organization name:");
	fgets(organizationPtr->organization, SIZE, stdin);

	puts("Please enter organization purpose");
	fgets(organizationPtr->purpose, SIZE, stdin);
	//uses fgets to get name
	getName(organizationPtr->name);
	//There is no current difference in getemail or password than here, but for future requirment changes
	getEmail(organizationPtr->email);
	getPassword(organizationPtr->password);
	//gets a goal bigger than 0 and that no letter is recieved
	puts("Please enter a a valid goal");
	getValidGoal(&organizationPtr->goal);
}
void getValidGoal(double* goal)
{
	bool validAnswer = false;
	//A temperaroy hold value required for getNumber, because getNumber also works with getAdmin
	char test[SIZE];
	//Ensures a valid number was received 
	do
	{
		getNumber(&*goal, &*test);
		//Checks if a number was recieved and that if nothing was entered it does not use the null value of 0 within the code
		if (*goal != '\0')
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
	//now temps hold the corresponding information
	strcpy(temp,"https:donate.com/");
	strcpy(temp2, "?form=popup#");
	//combines the info of temp, and the value stored in url, then stores that info in temp array
	strncat(temp, companyPtr->url, SIZE);
	//combines the info of temp array and temp2 array
	strncat(temp, temp2, SIZE);
	//copies the info from temp to put in url, which will then change to it, making accessible at any time when called upon properly
	strncpy(companyPtr->url, temp, sizeof(temp));
}
void removeSpace(struct company* companyPtr)
{
	//Ensures that currentyl that url has orginzation info
	strncpy(companyPtr->url, companyPtr->organization, sizeof(companyPtr->organization));
	//Pointer
	char* bufferPtr;
	//Searches fo the first character of space
	bufferPtr = strchr(companyPtr->url, ' ');
	//repeats loop until end of string
	while (bufferPtr != NULL)
	{
		//Replaces current search of space with the character -
		*bufferPtr = '-';
		//searches the string again to see if there are other spaces
		bufferPtr = strchr(companyPtr->url, ' ');
		//loops so that after this search it will replace that space with -
	}
}
//seperate as it will require a diffent valdiation in future
void getEmail(char* companyPtr)
{
	//Standard fgets in the moment
	printf("Please enter an email: \n");
	fgets(companyPtr, SIZE, stdin);
}
void getPassword(char* companyPtr)
{
	//Standard fgets in the moment
	printf("Please enter an password: \n");
	fgets(companyPtr, SIZE, stdin);
}
void initilzeVariables(struct company* companyPtr)
{
	//Ensures that information is allocated
	companyPtr->totalAmountRaised = 0;
	companyPtr->totalPaidCredit = 0;
	companyPtr->percentGoal = 0;
	companyPtr->donations = 0;
	companyPtr->totalNumberOfDonations = 0;
	companyPtr->validEnd = false;
	companyPtr->currentPercent = 0;
}
//Part 2 get customer information and 
void displayOrganization(company* companyPtr)
{
	
	if (companyPtr != NULL)
	{
		
		company* currentPtr = companyPtr;

		
		while (currentPtr != NULL)
		{
			printf("\n%s\n", currentPtr->url);
			printf("Organization: %s\n", currentPtr->organization);
			printf("Purpose: %s\n", currentPtr->purpose);
			//Prints information that may be changed
			printf("Total amount raised: %.2lf\n", currentPtr->totalAmountRaised);
			printf("We are %.2lf%% towards our goal of $%.2lf\n", currentPtr->percentGoal, currentPtr->goal);
			currentPtr = currentPtr->nextPtr;
		}
	}
	
	else
	{
		puts("List is empty");
	}
}
void getDonation(struct company* companyPtr, bool *validEnd)
{
	//Checks to see if a valid number was entered
	bool validAnswer = false;
	do 
	{
		//Checks to see if a number or character was entered
		getNumber(&companyPtr->donations, companyPtr->quit);
		//Ensures that if character was entered it does not contain newLine
		removeNewLine(&*companyPtr->quit);
		//Searches for the the character q or Q
	if (strpbrk(companyPtr->quit, "q")||strpbrk(companyPtr->quit, "Q"))
	{
		//if entered will go admin mode, to see if email and password match, and that if fails will repeat the donor mode
		getAdmin(companyPtr, &*validEnd);
		validAnswer = true;
	}
	//Ensures that the value is proper
	else if (companyPtr->donations > 0)
	{
		validAnswer = true;
	}
	} while (validAnswer != true);
	//If number was entered and not character q will perform customer functions and additions
	if (validAnswer == true && *validEnd != true)
	{
		//gets name with standerd fgets
		getName(companyPtr->customer);
		//Goes into getZip, which also contains processing fees 
		getZip(companyPtr);
		//Creates an optional reciept 
		createReceipt(companyPtr);
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
		//Removes newLine for search
		removeNewLine(&*temp);
		//Searches for the character y/n
		if (strpbrk(temp, "y") || strpbrk(temp, "Y"))
		{
			//Displays the according information contained within the structure
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
void getZip(struct company* companyPtr)
{
	//Makes sure that is done valid
	bool valid = false;
	do
	{
		puts("Enter Zip");
		fgets(companyPtr->zip, SIZE, stdin);
		//gets zip info, with fgets and removes newLine
		removeNewLine(companyPtr->zip);
		//sends address to check if it is a digit and valid, also sends the bool valid
		validZip(companyPtr->zip, &valid);
	} while (valid != true);
	//Display total donated and processes fees
	donationSum(companyPtr);
}
void validZip(char* companyPtr, bool* valid)
{
	//Ensure that the length of it is matched by how many digits it requries
	int temp = strlen(companyPtr);
	//checks if its only digits entered
	if (isdigit(*companyPtr))
	{
		//checks length
		if (temp == ZIPDIGITS)
		{
			//checks to make sure that '0' is not entered in the first slot by requirments
			if (companyPtr[0] != '0')
			{
				//sets it too value stored in address to true which returns to getZip to validate answer
				*valid = true;
			}
		}
	}
}
void donationSum(struct company* companyPtr)
{
	double processFee = PROCESSINGFEE;
	//calcultes the cost of the process fee 
	double temp = companyPtr->donations * processFee;
	//Calculates what will actula be donated
	double temp2 = companyPtr->donations - temp;
	//shows how much of the fees are going away from total earned
	companyPtr->totalPaidCredit += temp;
	//tells how much is actually going to charity
	companyPtr->totalAmountRaised += temp2;
	//Caclulates the percent is currently at from the goal 
	companyPtr->percentGoal = (companyPtr->totalAmountRaised / companyPtr->goal) * 100;
	//adds 1 to number of people for every time in loop
	companyPtr->totalNumberOfDonations++;
	printf("\nThank you for the donation the there is a %.2lf%% credit card fee of $%.2lf. $%.2lf will be donated\n", (processFee * 100), companyPtr->donations, temp2);
}
void displayReceipt(const struct company* companyPtr)
{
	//time functions from time.h
	time_t curtime;
	time(&curtime);
	//Calls for the value stored at organization in the structure
	printf("Organization: %s\n", companyPtr->organization);
	printf("Donation Amount: $%.2lf\n", companyPtr->donations);
	printf("%s\n", ctime(&curtime));
}
//Part 3 Admin mode, and display total
void getAdmin(struct company* companyPtr, bool* validEnd)
{
	bool validEmail = false;
	bool validPassword = false;
	puts("Please enter email");
	//passes the info of email, and address of if its valid
	verify_Identity(companyPtr->email, &validEmail);
	//nested ifs to make sure that both are correct
	if (validEmail == true)
	{
		puts("Please enter Password");
		//passes password, and address of if its valid
		verify_Identity(companyPtr->password, &validPassword);
		if (validPassword == true)
		{
			//both have to be true in order for prog to end if not it goes back to donor mode
			*validEnd = true;
		}
	}
}
void verify_Identity(const char* companyPtr, bool* validThing)
{
	//2 attempts
	int counter = ATTEMPTS;
	//0 means a valid value
	int test = 0;
	char tester[SIZE];
	//if fails then nothing is changed goes back into donor mode
	do
	{
		fgets(tester, SIZE, stdin);
		//if valid the cmpr from the value of pass/email compares to the input, = 0 then it is true, else counter - 1
		if (test == strncmp(companyPtr, tester, strlen(companyPtr)))
		{
			//Sets the value to true, which then ends the loop and makes pass or email good
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
void displayTotalEarned(const struct company* companyPtr)
{
	//displays total of everything
	printf("Organization: %s\n", companyPtr->organization);
	printf("Total amount of donations: %d\n", companyPtr->totalNumberOfDonations);
	printf("Total amount raised: $%.2lf\n", companyPtr->totalAmountRaised);
	printf("Total amount that paid for credit card processing: $%.2lf\n", companyPtr->totalPaidCredit);
}
//Needed for mulptiple parts so on bottom
void removeNewLine(char* companyPtr)
{
	//make sure that inputlength is the size of string length
	size_t inputLength = strnlen(companyPtr, SIZE);

	if (inputLength > 0 && companyPtr[inputLength - 1] == '\n')
	{
		//makes sure that it is one slot away from null character
		companyPtr[inputLength - 1] = '\0';
		//removes indexr that stores \n
		inputLength--;
	}
}
void getName(char* companyPtr)
{
	//standard fgets to prevent repeat code
	puts("Please enter name: ");
	fgets(companyPtr, SIZE, stdin);
}
void getNumber(double* companyPtr, char* quit)
{
	char temp[SIZE];
	char* ptr;
	puts("Please enter number");
	fgets(temp, SIZE, stdin);
	//splits the characters and numbers into two different datat types, assigns the temp which hols the numbers to the pointer, and &ptr holds letters
	*companyPtr = strtod(temp, &ptr);
	//makes sure that quit stores the characters
	strncpy(quit, ptr, sizeof(&ptr));
}
char validateYesNo() {
	char validYesNo;

	do {
		puts("Please enter (y)es or (n)o:");
		validYesNo = getchar();
		while (getchar() != '\n');

		validYesNo = tolower(validYesNo);

	} while (validYesNo != 'y' && validYesNo != 'n');

	return  validYesNo;
}
void insertOrganization(company** organization)
{
	company *org = malloc(sizeof(company));
	if (org != NULL)
	{
		getInformation(&*org);
		initilzeVariables(&*org);
		removeNewLine(org->organization);
		removeNewLine(org->purpose);
		removeSpace(&*org);
		createUrl(&*org);
		org->nextPtr = NULL;
		company *currentPtr = *organization;
		company *previousPtr = NULL;
		int temp = 0;
		while ((currentPtr != NULL) && temp < strncmp(currentPtr->organization, currentPtr->organization, SIZE))
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
		if (previousPtr == NULL)
		{
			*organization = org;
		}
		else
		{
			previousPtr->nextPtr = org;
		}
		org->nextPtr = currentPtr;
	}
}
void selectOrganization(company** organization, bool *validEnd)
{
	company* previousPtr = NULL;
	company* currentPtr = *organization;
	char temp[SIZE];
	bool valid = false;
	displayOrganization(&**organization);
	do 
	{
		puts("Please chose organization");
		fgets(temp, SIZE, stdin);
		removeNewLine(&*temp);
		if (*organization != NULL)
		{
			if (strncmp(temp, (*organization)->organization, SIZE) == 0)
			{
				
				getDonation(&*currentPtr, &*validEnd);
				valid = true;
				
			}
			else
			{
				while (currentPtr != NULL && strncmp(temp, (*organization)->organization, SIZE) != 1)
				{
					previousPtr = currentPtr;
					currentPtr = currentPtr->nextPtr;
					
				}
				if (currentPtr != NULL)
				{
					previousPtr->nextPtr = currentPtr->nextPtr;
					getDonation(&*currentPtr, &*validEnd);
					valid = true;
					
				}
			}
			//temp, (*organization)->organization, SIZE
		} 
	} while (valid != true);
}