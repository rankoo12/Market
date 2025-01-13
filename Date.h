#ifndef DATE_H
#define DATE_H

#define maxYear 2030
#define minYear 2024

typedef struct {
    int day;
    int month;
    int year;
} Date;

int isValidDateInput(int input);
int newDate(Date* date, int input);
void splitDate(Date* date, int input, int inputLength);
int valiDate(const Date* date);

#endif // DATE_H