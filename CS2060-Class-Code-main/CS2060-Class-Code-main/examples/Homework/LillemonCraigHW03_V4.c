/*
*/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
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
    do
    {
        do
        {
            printf("%s\n", "Enter number of hours the car was parked or enter -1 to quit");
            scanf("%lf", &response);
            if (response == EXIT_CONDITION)
            {
                hourLoop = true;
                validEnd = true;
            }
            else if (response > MAX_HOURS_ALLOWED || response <= MIN_HOURS_ALLOWED)
            {
                printf("%s%d%s%d\n", "Please enter a number between ", MIN_HOURS_ALLOWED, "-", MAX_HOURS_ALLOWED);
            }
            else if (response <= MAX_HOURS_ALLOWED && response > MIN_HOURS_ALLOWED)
            {
                hourLoop = true;
            }
            
        }
        while (hourLoop != true);
        tempHours = round(response);
        //Rounds up to calculate a whole number
        if (tempHours != EXIT_CONDITION)
        {
            car += 1;
            if (tempHours < response)
            {
                tempHours = tempHours + 1;
            }
            if (tempHours > MIN_HOURS_AT_FLAT_RATE)
            {
                cost = ((tempHours - MIN_HOURS_AT_FLAT_RATE) * ADDITIONAL_HOURS_RATE) + MIN_FLAT_RATE_CHARGE;

            }
            if (tempHours <= MIN_HOURS_AT_FLAT_RATE)
            {
                cost = MIN_FLAT_RATE_CHARGE;
            }
            if (cost > MAX_CHARGE)
            {
                cost = MAX_CHARGE;
            }
            printf("%s%9s%10s\n", "Car", "Hours", "Charge");
            printf("%d  %6.1lf   %5s%-5.2lf\n", car, response, "$", cost);
            totalCost += cost;
            hourTotal += response;
            
        }

    } 
    while (validEnd != true);
    //Car total summary
    if (car > 0)
    {
        printf("%s%20s%20s\n", "Total Cars", "Total Hours", "Total Charges");
        printf("%d  %21.1lf   %14s%-14.2lf\n", car, hourTotal,"$", totalCost);
    }
    //no car
    else
    {
        printf("%s\n", "There were no cars parked today");
    }
} // end while 