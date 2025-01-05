#ifndef DATE_H
#define DATE_H

//constant declerations - input rules
#define maxYear 2030
#define minYear 2024

//constant declerations - type of product


//struct
typedef struct {
	int day;
	int month;
	int year;
} Date;

//functions declerations
int isValidDateInput(int input);
int newDate(Date* date, int input);
void splitDate(Date* date, int input, int inputLength);
int valiDate(const Date* date);



#endif // DATE_H
