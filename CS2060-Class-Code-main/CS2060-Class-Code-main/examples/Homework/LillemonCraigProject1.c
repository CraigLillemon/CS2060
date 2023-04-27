/*
* Craig Lillemon
* Due April 25 2023 at 11:59 pm
* This code will create a charity org which will then have a email and password requriment
* it will also create a url based off the org name
It will then go into donation mode to see what the donator will donate, name, and zip code ensuring that the zip is a number, and 5 digits long, with no 0 spot in the first character
when wanting to end the program the user must enter the exit condition of the letter q and ensure that password and email within 2 attempts, if fail go back to donor mode
if success display all according information of total raised, and number of people and so on
UPDATE
uses linked lists to allow more than one organization, as well as prints info to file, email and password are required now with secure measures
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
#define PROCESSINGFEE 0.031
#define ZIPDIGITS 5
#define ATTEMPTS 1
#define PASSLENGTH 7
#define FOLDERPATH "C:\\fundraiser\\"
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
	FILE *comp;
	struct company* nextPtr;
	char fileName[SIZE];
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
void createReceipt( struct company* companyPtr);
void displayReceipt(const struct company* companyPtr);

void displayTotalEarned( struct company* companyPtr);
char validateYesNo();

void insertOrganization(company** organization);
void selectOrganization(company** organization, bool* validEnd);
void displayReceiptFile (struct company* companyPtr);
void displayTotalEarnedFile(company* companyPtr);
void deallocateOrganizations(struct company* companyPtr);
int main(void)
{
	char yesOrNo;
	bool validEnd = false;
	company* org = NULL;
	puts("Please press enter");
	do
	{
		insertOrganization(&org);
		printf("%s", "\nDo you want to add another Organization? ");
		 yesOrNo = validateYesNo();
		 removeNewLine(&yesOrNo);
	} while (yesOrNo == 'y');
	do
	{
		selectOrganization(&org, &validEnd);
	} while (validEnd != true);
	displayTotalEarned(org);
	displayTotalEarnedFile(org);
	deallocateOrganizations(org);
}


//Other parts like remove new line and get number are at the bottom as it is needed for other parts

//Part 1 get orginzation information
void getInformation(struct company* organizationPtr)
{
	char temp4[SIZE];
	fgets(temp4, SIZE, stdin);
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
	removeNewLine(&*organizationPtr->organization);
	removeNewLine(&*organizationPtr->purpose);
	removeSpace(&*organizationPtr);
	strncpy(organizationPtr->fileName, organizationPtr->url, sizeof(organizationPtr->url));
	createUrl(&*organizationPtr);
	char temp[SIZE];
	char temp2[SIZE];
	strcpy(temp, FOLDERPATH);
	strcpy(temp2, ".txt");
	strncat(temp, organizationPtr->fileName, SIZE);
	strncat(temp, temp2, SIZE);
	strncpy(organizationPtr->fileName, temp, sizeof(temp));
	removeNewLine(&*organizationPtr->fileName);
	//creates the file
	organizationPtr->comp = fopen(organizationPtr->fileName, "a+");
	
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
	//two conditions to ensure that email is right, and wanted
	bool validEnd = false;
	bool validEmail = false;
	int number = 4;
	do
	{
		printf("Enter Email Address:\n");
		fgets(companyPtr, SIZE, stdin);
		removeNewLine(&*companyPtr);

		int length = strlen(companyPtr);
		
		int temp = 0;
		int temp2 = 0;
		for (int i = 0; i< length; i++)
		{
			//stores the place of the first @
			if (companyPtr[i] == '@')
			{
				temp = i;
			}
			else if (companyPtr[i] == '.')
			{
				//Will store the last place where . 
				temp2 = i;
			}
		}
		//Makes sure there is no @ in first spot
		if (temp < 1)
		{
			printf("You must have a name or text before @\n");
		}
		//Ensures domain is entered that it does not go after the last . 
		else if (temp2 < (temp + 2))
		{
			puts("You must enter a domain\n");
		}
		//ensures that characters are 3 long
		else if ((length - temp2) != number)
		{
			puts("The email extension must be 3 characters long\n");
		}
		//If everything fails from above, which is good, validEmail becomes true
		else
		{
			validEmail = true;
		}

		
		//After true
		if (validEmail == true)
		{
			//makes sure they want it
			printf("Is this email correct? \n");
			char checkEmail = validateYesNo();
			if (checkEmail == 'y')
			{
				validEnd = true;
			}
			//if not reset function
			else if (checkEmail == 'n')
			{
				puts("Enter Your Email Address: \n");//prompts for email again
				validEmail = false;
			}
			else
			{
				printf("Invalid input. Please enter y/n: \n");
			}
			while (getchar() != '\n');//clear the buffer
		}
	} while (validEnd == false);
}
void getPassword(char* companyPtr)
{

		
		bool validPass = false;

		do  {
			//Keeps current number that will reset after buffer
			int hasCap = 0;
			int hasLower = 0;
			int hasDigit = 0;
			printf("Enter password: \n");
			fgets(companyPtr, SIZE, stdin);
			removeNewLine(companyPtr);

			int length = strlen(companyPtr);

			// Making sure the password is 7 characters before checking for any other validations
			if (length >= PASSLENGTH) 
			{
				for (int i = 0; i < length; i++) {
					if (isupper(companyPtr[i])) {
						hasCap++;
					}
					else if (islower(companyPtr[i])) {
						hasLower++;
					}
					else if (isdigit(companyPtr[i])) {
						hasDigit++;
					}
				}
				if (hasCap == 0) {
					printf("Password must contain at least one uppercase letter.\n");
				}
				else if (hasLower == 0) {
					printf("Password must contain at least one lowercase letter.\n");
				}
				else if (hasDigit == 0) {
					printf("Password must contain at least one digit.\n");
				}
				//just to make sure all is valid
				else if (hasCap > 0 && hasDigit > 0 && hasLower > 0) {
					validPass = true;
				}
			}else
			{
				printf("Please enter a password longer than %d\n", PASSLENGTH);
			}
		} while (validPass != true);
		
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
void createReceipt( struct company* companyPtr)
{
	bool validChoice = false;
	char temp;
	do
	{
		puts("Do you want a receipt, (y)es or (n)o ? ");
		temp = validateYesNo();
		//Removes newLine for search
		
		//Searches for the character y/n
		if (temp == 'y')
		{
			//Displays the according information contained within the structure
			displayReceipt(companyPtr);
			validChoice = true;
			//appends info to file
			displayReceiptFile(&*companyPtr);
			
		}
		else if (temp == 'n')
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
void displayReceiptFile (struct company* companyPtr)
{
	//opens the file again at the Ptr
	companyPtr->comp = fopen(companyPtr->fileName, "a+");
	time_t curtime;
	time(&curtime);
	//prints info to file
	fprintf(companyPtr->comp, "Organization: %s\n", companyPtr->organization);
	fprintf(companyPtr->comp, "Donation Amount: $%.2lf\n", companyPtr->donations);
	fprintf(companyPtr->comp, "%s\n", ctime(&curtime));
	//closes file
	fclose(companyPtr->comp);
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
			//fclose(companyPtr->comp);
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
void displayTotalEarned( struct company* companyPtr)
{
	//makes sure that there is a linked list
	if (companyPtr != NULL)
	{

		company* currentPtr = companyPtr;

		//Goes through linked list to print info
		while (currentPtr != NULL)
		{
			printf("Organization: %s\n", currentPtr->organization);
			printf("Total amount of donations: %d\n", currentPtr->totalNumberOfDonations);
			printf( "Total amount raised: $%.2lf\n", currentPtr->totalAmountRaised);
			printf( "Total amount that paid for credit card processing: $%.2lf\n", currentPtr->totalPaidCredit);
			currentPtr = currentPtr->nextPtr;
		}
	}
	else
	{
		puts("List is empty");
	}
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
		//gets yes/no
		puts("Please enter (y)es or (n)o:");
		validYesNo = getchar();
		//while (getchar() != '\n');

		validYesNo = tolower(validYesNo);

	} while (validYesNo != 'y' && validYesNo != 'n');

	return  validYesNo;
}
void insertOrganization(company** organization)
{
	//heap
	company *org = malloc(sizeof(company));
	if (org != NULL)
	{
		//gets info
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
		while ((currentPtr != NULL) && temp > strncmp(currentPtr->organization, currentPtr->organization, SIZE))
		{
			//Sets ptrs
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
	puts("Please press enter");
	char temp2[SIZE];
	fgets(temp2, SIZE, stdin);
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
				while (currentPtr != NULL && strncmp(temp, currentPtr->organization, SIZE) !=  0)
				{
					
					currentPtr = currentPtr->nextPtr;
					
				}
				if (currentPtr != NULL)
				{
				
					getDonation(&*currentPtr, &*validEnd);
					valid = true;
					
				}
			}
			//temp, (*organization)->organization, SIZE
		} 
	} while (valid != true);
}
void displayTotalEarnedFile(struct company* companyPtr)
{
	FILE* ptr;
	//opens file
	ptr = fopen("orgs.txt", "w+");
	if (companyPtr != NULL)
	{

		company* currentPtr = companyPtr;

		//goes theourgh every itearti9on of the linked list
		while (currentPtr != NULL)
		{
			//prints to file
			fprintf(ptr, "Organization: %s\n", currentPtr->organization);
			fprintf(ptr, "Total amount of donations: %d\n", currentPtr->totalNumberOfDonations);
			fprintf(ptr, "Total amount raised: $%.2lf\n", currentPtr->totalAmountRaised);
			fprintf(ptr, "Total amount that paid for credit card processing: $%.2lf\n", currentPtr->totalPaidCredit);
			currentPtr = currentPtr->nextPtr;
		}
	}
	else
	{
		puts("List is empty");
	}
	fclose(ptr);
}
void deallocateOrganizations(struct company* companyPtr) {
	struct company* currentPtr = companyPtr;
	//Goes through current ptr to free until all is null
	while (currentPtr != NULL) {
		struct company* next = currentPtr->nextPtr;
		//deallocates
		free(currentPtr);
		//reassigns to repeat
		currentPtr = next;
	}
}

