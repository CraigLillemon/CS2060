/*
<<<<<<< HEAD
* 
=======
*CS2060
*Craig Lillemon
*HW03
*Due 2/17/2023
*This code will determine with multiple single entries the total days earned with each single entry of a cars hours, then determine the cost and earn
*The code will repeat until the exit condition -1 is entered in, hours portion will be repeated until a valid input is entered,
*When finished Code will display amount of the of cars, total hours, and total money earned if no cars parked it will display that no cars were parked
*Charges $2.5 for up to three hours, and 1.25 for every hour after till a max charge of $15, a car cannot stay for more than 24 hours 
*Ensure that cost, hours and such can be changed easily and maintainable 
>>>>>>> a0e3edb6a4a96b7234cd609a8df25e795d408e5e
*/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
//Constants
#define MIN_HOURS_AT_FLAT_RATE 2
#define MIN_FLAT_RATE_CHARGE 2.5
#define ADDITIONAL_HOURS_RATE 1.25
#define MAX_HOURS_ALLOWED 24
#define MAX_CHARGE 15
#define MIN_HOURS_ALLOWED 0
#define EXIT_CONDITION -1
int main()
{
    // initialize variables
    bool validEnd = false;
    bool hourLoop = false;
    double hourTotal = 0;
    unsigned int car = 0;
    double response = 0;
    unsigned int tempHours = 0;
    double cost = 0;
    double totalCost = 0;
    //Total loop will repeat until -1 is entered
    do
    {
        //Using boolean flags for multiple conditions determine that the input is 0 < x <= 24, repeat if not, if it fails it will clear buffer
        //Creating a secure code
        do
        {
            
            printf("%s\n", "Enter number of hours the car was parked or enter -1 to quit");
            scanf("%lf", &response);
            if (response == EXIT_CONDITION)
            {
                hourLoop = true;
                validEnd = true;
            }// If the ==-1 then it will not only end this loop by total loop, used DRY princple 
            //Ensure that response is 0-24 in current values of constant, this makes maintainable as min and max can be changed
            else if (response > MAX_HOURS_ALLOWED || response <= MIN_HOURS_ALLOWED)
            {
                printf("%s%d%s%d\n", "Please enter a number between ", MIN_HOURS_ALLOWED, "-", MAX_HOURS_ALLOWED);
            }
            //Exits this loop alone not total like other one, so that way cost, and totalcost can be calculated
            else if (response <= MAX_HOURS_ALLOWED && response > MIN_HOURS_ALLOWED)
            {
                hourLoop = true;
            }
            
        }//End of determing hours loop
        while (hourLoop != true);
        //rounds answer, to a temp hold is unsigned to secure, has to round up in this case. If not calculating cost is difficult . This uses math.h
        tempHours = round(response);
        //Rounds up to calculate a whole number
       //Ensure that -1 cannot be calculated into cost, or any other exit conditions
        if (tempHours != EXIT_CONDITION)
        {
            //Car count to see how many cars at end increments by 1
            car += 1;
            //If the answer somehow rounds down less than its orignal value it will add 1 to ensure that the value is greater, creating a whole number
            if (tempHours < response)
            {
                tempHours = tempHours + 1;
            }
            //After $2.5 for the the 2 hours it changes to flat rate
            if (tempHours > MIN_HOURS_AT_FLAT_RATE)
            {
                //Using the whole numbers it can calculate cost
                //Ensure that the hours is whole and minus the 2 hours (min hour flatrate) as there is always an inital cost of $2, you have to caluclate 
                //Cost after those hours, then times the hours from after those 2 hours, times the rate per hour
                //After that add the $2 as that is a constant cost in the beginning.
                cost = ((tempHours - MIN_HOURS_AT_FLAT_RATE) * ADDITIONAL_HOURS_RATE) + MIN_FLAT_RATE_CHARGE;

            }
            if (tempHours <= MIN_HOURS_AT_FLAT_RATE)
            {
                //always a $2 for anything less or equal to 2 hours in the current constants
                cost = MIN_FLAT_RATE_CHARGE;
            }
            if (cost > MAX_CHARGE)
            {
                //The charge cannot exceed the max charge, so it resets to maxcharge
                cost = MAX_CHARGE;
            }
            //Displays all the information that correspond to the current entry car
            printf("%s%9s%10s\n", "Car", "Hours", "Charge");
            printf("%d  %6.1lf   %5s%-5.2lf\n", car, response, "$", cost);
            //Sums cost and hours 
            totalCost += cost;
            hourTotal += response;
            
        }
        //Now the entire cost is done, however if -1 is not entered repeats loop
    } //End of total loop 
    while (validEnd != true);
    //Car total summary
    if (car > 0)
    {
        //Displays summed information in secure manor
        printf("%s%20s%20s\n", "Total Cars", "Total Hours", "Total Charges");
        printf("%d  %21.1lf   %14s%-14.2lf\n", car, hourTotal,"$", totalCost);
    }
    // if no car is entered and -1 is only entered, no cars were parked so no need to display sum information
    else
    {
        printf("%s\n", "There were no cars parked today");
    }
} // end main
