#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Date.h"

int isValidDateInput(int input) {
    int len = 0;
    while (input > 0) {
        len++;
        input /= 10;
    }
    return len;
}

int newDate(Date* date, int input) {
    int valid = isValidDateInput(input);
    if (valid != 8) {
        printf("Invalid input length.\n");
        return 0;
    }

    splitDate(date, input, valid);
    if (!valiDate(date)) {
        printf("Invalid date.\n");
        return 0;
    }
    return 1;
}

void splitDate(Date* date, int input, int inputLength) {
    date->day = input / 1000000;
    date->month = (input / 10000) % 100;
    date->year = input % 10000;
}

int valiDate(const Date* date) {
    if (date->month < 1 || date->month > 12) return 0;
    if (date->day < 1 || date->day > 31) return 0;

    if ((date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11) && date->day > 30) {
        return 0;
    }
    if (date->month == 2) {
        int leapYear = (date->year % 4 == 0 && (date->year % 100 != 0 || date->year % 400 == 0));
        if ((leapYear && date->day > 29) || (!leapYear && date->day > 28)) {
            return 0;
        }
    }

    return date->year >= minYear && date->year <= maxYear;
}