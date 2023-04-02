

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define SIZE 80
int getDonation();
int main(void) 
{
	int x = getDonation();
	printf("%05d\n", x);
	printf("It works\n");
}
int getDonation()
{
	bool endLoop = false;
	int money = 0;
	char test2 = 'q';
	char test = 'Q';
	double temp = (double)test;
	double temp2 = (double)test2;
	do
	{
		scanf("%d", &money);
		if (money >= 0 && money<= 99999)
		{
			endLoop = true;
		}
	} while (endLoop != true);
	return money;
}