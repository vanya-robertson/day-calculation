#include <stdio.h>
#include <stdlib.h>

const struct dateCoords stringToStruct(char inputstring[10]); // returns struct of century, year, month and day
const int isJulian(struct dateCoords input, struct dateCoords endJulian, struct dateCoords startGregorian); // returns 0 if Gregorian, 1 if Julian, 2 if invalid
const int isLeapYear(int input_year, int isjulian); // returns 0 if is leap year, 1 if is not
const char* getMonthName(int month);

struct dateCoords {
  unsigned int s_century: 7, s_year: 7, s_month: 7, s_day: 7; // reducing month and day to 3 and 5 did not work: this caused overflows, preventing error detection
};

struct dateCoords const stringToStruct (char inputstring[10] ) {
  unsigned int day = 10 * (inputstring[8] - '0') + (inputstring[9] - '0');
  unsigned int month = 10 * (inputstring[5] - '0') + (inputstring[6] - '0');
  unsigned int century = 10 * (inputstring[0] - '0') + (inputstring[1] - '0');
  unsigned int year = 10 * (inputstring[2] - '0') + (inputstring[3] - '0');
  struct dateCoords inputDate = {century, year, month, day};
  return inputDate;
};


const int isJulian(struct dateCoords input, struct dateCoords endJulian, struct dateCoords startGregorian)
{
// "2024-01-23", "1752-09-02", "1752-09-14" // for England
    if (input.s_century > startGregorian.s_century)
      return(0);
    else if (input.s_century < endJulian.s_century)
      return(1);
    else if (input.s_year > startGregorian.s_year)
      return(0);
    else if (input.s_year < endJulian.s_year)
      return(1);
    else if (input.s_month > startGregorian.s_month)
      return(0);
    else if (input.s_month < endJulian.s_month)
      return(1);
    else if (input.s_day  >= startGregorian.s_day)
      return(0);
    else if (input.s_day  <= endJulian.s_day)
      return(1);
    return(2);
}

const int isLeapYear(int input, int isjulian)
{
  switch (isjulian){
    case 0:
      if (input % 400 == 0)
	return(1);
      else if (input % 100 == 0)
	return(0);
      else if (input % 4 == 0)
	return(1);
      else
	return(0);
    case 1:
      if (input % 4 == 0)
	return(1);
      else
	return(0);
    default:
      return(2);
  }
}

const char* getMonthName(int month)
{
  switch (month){
    case 1:
	return "January";
    case 2:
	return "February";
    case 3:
	return "March";
    case 4:
	return "April";
    case 5:
	return "May";
    case 6:
	return "June";
    case 7:
	return "July";
    case 8:
	return "August";
    case 9:
	return "September";
    case 10:
	return "October";
    case 11:
	return "November";
    case 12:
	return "December";
    default:
	printf("The invalid month number\n");
	exit(1);
  }
}

