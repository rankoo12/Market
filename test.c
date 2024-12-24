#include <stdio.h>
#include <stdlib.h>
#include "Date.h"


int test()
{
	// ** TEST NUMBER 1 : DATE --> PASSED **
	int input;
	Date date;


	// Get the integer input from the user
	printf("Enter a date in format DDMMYYYY: ");
	scanf_s("%d", &input);
	newDate(&date, input);
	printf_s("Day: %02d\n", date.day);
	printf_s("Month: %02d\n", date.month);
	printf_s("Year: %04d\n", date.year);
	return 0;
	// ** END TEST NUMBER 1 : DATE --> PASSED **
}

