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
int main()
{
    // initialize variables
    bool validEnd = false;
    bool hourLoop = false;
    double hourTotal = 0;
    unsigned int car = 0;
    double response = 0;
    int tempHours = 0;
    double cost = 0;
    double totalCost = 0;
    do
    {
        do
        {
            printf("%s\n", "Enter number of hours the car was parked or enter -1 to quit");
            scanf("%lf", &response);
            if (response > MAX_HOURS_ALLOWED || response < -1)
            {
                printf("%s%d\n", "Please enter a number between 0.1 - ", MAX_HOURS_ALLOWED);
            }
            if (response < MAX_HOURS_ALLOWED && response >  0)
            {
                hourLoop = true;
            }
            else if (response == -1)
            {
                hourLoop = true;
            }
        }//End of interior do
        while (hourLoop != true);
        if (response == -1)
        {
            validEnd = true;
        }
        tempHours = round(response);
        //Rounds up to calculate a whole number
        if (tempHours != -1)
        {
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
            totalCost += cost;
        }
        printf("%.2lf\n", cost);
        hourTotal += response;
        printf("%d\n", tempHours);

    } while (validEnd != true);
    printf("%lf", totalCost);
} // end while 