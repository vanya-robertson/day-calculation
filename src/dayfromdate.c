#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const struct dateCoords stringToStruct(char inputstring[10]); // returns struct of century, year, month and day
const struct monthCoords getMonthCodeAndLength(int month,int isleapyear); // returns struct of month code and month length
const int isJulian(struct dateCoords input, struct dateCoords endJulian, struct dateCoords startGregorian); // returns 0 if Gregorian, 1 if Julian, 2 if invalid
const int isLeapYear(struct dateCoords input, int isjulian); // returns 0 if is leap year, 1 if is not
const char* getDay(int day);
const char* getMonthName(int month);

struct dateCoords {
  unsigned int s_century: 7, s_year: 7, s_month: 3, s_day: 5;
};

struct dateCoords const stringToStruct (char inputstring[10]) {
  unsigned int day = 10 * (inputstring[8] - '0') + (inputstring[9] - '0');
  unsigned int month = 10 * (inputstring[5] - '0') + (inputstring[6] - '0');
  unsigned int century = 10 * (inputstring[0] - '0') + (inputstring[1] - '0');
  unsigned int year = 10 * (inputstring[2] - '0') + (inputstring[3] - '0');
  struct dateCoords inputDate = {century, year, month, day};
  return inputDate;
}

struct monthCoords {
  unsigned int month_code: 3, month_length: 5;
};

struct monthCoords const getMonthCodeAndLength (int month, int isleapyear) {
  if (month == 1) {
    struct monthCoords inputMonth = {0, 31};
    return(inputMonth);
  } else if (month == 2) {
      if (isleapyear){
      struct monthCoords inputMonth = {3, 29};
      return(inputMonth);
      } else {
      struct monthCoords inputMonth = {3, 28};
      return(inputMonth);
      };
  } else if (month == 3) {
    struct monthCoords inputMonth = {3, 31};
    return(inputMonth);
  } else if (month == 4) {
    struct monthCoords inputMonth = {6, 30};
    return(inputMonth);
  } else if (month == 5) {
    struct monthCoords inputMonth = {1, 31};
    return(inputMonth);
  } else if (month == 6) {
    struct monthCoords inputMonth = {4, 30};
    return(inputMonth);
  } else if (month == 7) {
    struct monthCoords inputMonth = {6, 31};
    return(inputMonth);
  } else if (month == 8) {
    struct monthCoords inputMonth = {2, 31};
    return(inputMonth);
  } else if (month == 9) {
    struct monthCoords inputMonth = {5, 30};
    return(inputMonth);
  } else if (month == 10) {
    struct monthCoords inputMonth = {0, 31};
    return(inputMonth);
  } else if (month == 11) {
    struct monthCoords inputMonth = {3, 30};
    return(inputMonth);
  } else if (month == 12) {
    struct monthCoords inputMonth = {5, 31};
    return(inputMonth);
  } else if (month > 12){
    printf("Error: There are only 12 months\n");
    exit(1);
  } else {
    printf("The input format is incorrect\n");
    exit(1);
  }
}

const int isJulian(struct dateCoords input, struct dateCoords endJulian, struct dateCoords startGregorian)
{
// "2024-01-23", "1752-07-02", "1752-07-14" // for England
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

const int isLeapYear(struct dateCoords input, int isjulian)
{
  switch (isjulian){
    case 0:
      if ((input.s_century % 4 == 0) && (input.s_year == 0))
	return(1);
      else if (input.s_year == 0)
	return(0);
      else if (input.s_year % 4 == 0)
	return(1);
      else
	return(0);
    case 1:
      if (input.s_year % 4 == 0)
	return(1);
      else
	return(0);
    default:
      return(2);
  }
}

const char* getDay(int day)
{
  switch (day){
    case 0:
	return "Sunday";
    case 1:
	return "Monday";
    case 2:
	return "Tuesday";
    case 3:
	return "Wednesday";
    case 4:
	return "Thursday";
    case 5:
	return "Friday";
    case 6:
	return "Saturday";
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
  }
}

int main(int argc, char **argv){
  //printf("%s\n", argv[1]);
  char *dateStr = argv[1];

  // check input from stdin
  if (argc == 1) {
    printf("Error: There must be one argument in the format \"yyyy-MM-dd\"\n");
    exit(1);
  }
  else if (argc > 2) {
    printf("Error: There must only be one argument in the format \"yyyy-MM-dd\"\n");
    exit(1);
  }
  else if (strlen(dateStr) > 10) {
    printf("Error: There must be one argument in the format \"yyyy-MM-dd\"\n");
    exit(1);
  }
  else if ((dateStr[4] != '-') || (dateStr[7] != '-')) {
    printf("Error: There must be one argument in the format \"yyyy-MM-dd\"\n");
    exit(1);
  }

  struct dateCoords inputDate = stringToStruct(dateStr);
  struct dateCoords endJulian = stringToStruct("1752-09-02");
  struct dateCoords startGregorian = stringToStruct("1752-09-14");
  const int isjulian = isJulian(inputDate, endJulian, startGregorian);
  const int isleapyear = isLeapYear(inputDate, isjulian);

  int century_code, leap_code;

  const int day_code = inputDate.s_day;
  struct monthCoords month_coords = getMonthCodeAndLength(inputDate.s_month, isleapyear);
  if (day_code > month_coords.month_length){
    printf("Error: There are only %d days in %s\n", month_coords.month_length, getMonthName(inputDate.s_month));
    exit(1);
  }
  const int month_code = month_coords.month_code;
  const int year_code = inputDate.s_year + inputDate.s_year / 4;

  //printf("Date string is %s\n", dateStr);
  //printf("Day:\t\t\t\t%d -> %d\n", inputDate.s_day, day_code);
  //printf("Month:\t\t\t\t%d -> %d\n", inputDate.s_month, month_code);
  //printf("Year:\t\t\t\t%d -> %d\n", inputDate.s_year, year_code);
  switch (isjulian){
  case 0:
      century_code = (3 - inputDate.s_century) % 4;
      while (century_code < 0) {
	century_code += 4;
	};
      century_code *= 2;
      //printf("Century (Gregorian):\t\t%d -> %d\n", inputDate.s_century, century_code);
      break;
  case 1:
      century_code = (4 - inputDate.s_century) % 7;
      while (century_code < 0) {
	century_code += 7;
      }
      //printf("Century (Julian):\t\t%d -> %d\n", inputDate.s_century, century_code);
      break;
  case 2:
      break;
  }
  switch (isleapyear){
    case 0:
	leap_code = 0;
	//printf("Leap code (Not leap):\t\t%d\n\n", leap_code);
      break;
    case 1:
      if (inputDate.s_month == 1 || inputDate.s_month == 2) {
	leap_code = 1;
	//printf("Leap code (Leap, Jan/Feb):\t%d\n\n", leap_code);
      } else {
	leap_code = 0;
	//printf("Leap code (Leap, not Jan/Feb):\t%d\n\n", leap_code);
      break;
      }
    case 2:
      //printf("This is an impossible date!\n");
      exit(1);
  }

  const int penultimate_number = (day_code + month_code + year_code + century_code - leap_code);
  const int final_number = penultimate_number % 7;
  //printf("%d + %d + %d + %d - %d = %d\n", day_code, month_code, year_code, century_code, leap_code, penultimate_number);
  //printf("%d %% 7 = %d\n\n", penultimate_number, final_number);

  printf("%s\n", getDay(final_number));
  return(0);
}
