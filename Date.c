#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Date.h"



int isValidDateInput(int input)
{
	int len = 0;
	while (input > 0)
	{
		len++;
		input /= 10;
	}
	return len;
}
int newDate(Date* date, int input)
{
	int valid = isValidDateInput(input);
	if (valid !=7 && valid != 8)
	{
		printf("Input length is not valid, try again.\n");
		return 0;
	}

	splitDate(date, input, valid); // Save the date ! (Congratulations).
	if (!valiDate(date))
	{
		printf("You are cool! please enter a valid date!.\n");
		return 0;
	}
	return 1;
}

void splitDate(Date* date, int input, int inputLength) 
{
	if (inputLength == 8)
	{
		// Extract the day (first 2 digits)
		date->day = input / 1000000;

		// Extract the month (next 2 digits)
		date->month = (input / 10000) % 100;

		// Extract the year (last 4 digits)
		date->year = input % 10000;
	}
	if (inputLength == 7)
	{
		date->day = input / 100000;
		date->month = (input / 1000) % 100;
		date->year = input % 10000;
	}
}

int valiDate(const Date *date)//Did not save any of the numbers below as constants because these number will never ever change and the function will live forever.
{
	if (date->month < 1 || date->month > 12) {
		return 0;
	}

	// Check for valid day range based on month
	if (date->day < 1 || date->day > 31) {
		return 0;
	}

	// Month-specific day 
	if ((date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11) && date->month > 30) {
		return 0;
	}
	if (date->month == 2) {
		// Leap year check for February
		int leapYear = (date->year % 4 == 0 && (date->year % 100 != 0 || date->year % 400 == 0));
		if (leapYear && date->day > 29) {
			return 0;
		}
		else if (!leapYear && date->day > 28) {
			return 0;
		}
	}

	//MinMaxYear
	if (date->year > maxYear || date->year < minYear) return 0;

	return 1;
}