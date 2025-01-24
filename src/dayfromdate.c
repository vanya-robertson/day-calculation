#include <stdio.h>
#include <stdlib.h>

struct dateCoords stringToStruct(char inputstring[10]); // returns struct of century, year, month and day
int isJulian(struct dateCoords input, struct dateCoords endJulian, struct dateCoords startGregorian); // returns 0 if Gregorian, 1 if Julian, 2 if invalid
int isLeapYear(struct dateCoords input, int isjulian); // returns 0 if is leap year, 1 if is not
int dayOfWeek(struct dateCoords input, int isjulian);

struct dateCoords {
  int s_century: 24, s_year: 24, s_month: 24, s_day: 24;
};

struct dateCoords stringToStruct (char inputstring[10]) {
  int day = 10 * (inputstring[8] - '0') + (inputstring[9] - '0');
  int month = 10 * (inputstring[5] - '0') + (inputstring[6] - '0');
  int century = 10 * (inputstring[0] - '0') + (inputstring[1] - '0');
  int year = 10 * (inputstring[2] - '0') + (inputstring[3] - '0');
  struct dateCoords inputDate = {century, year, month, day};
  return inputDate;
}

int isJulian(struct dateCoords input, struct dateCoords endJulian, struct dateCoords startGregorian)
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

int isLeapYear(struct dateCoords input, int isjulian)
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

int getMonthCode(int month)
{
  switch (month){
    case 1:
      return 0;
    case 2:
      return 3;
    case 3:
      return 3;
    case 4:
      return 6;
    case 5:
      return 1;
    case 6:
      return 4;
    case 7:
      return 6;
    case 8:
      return 2;
    case 9:
      return 5;
    case 10:
      return 0;
    case 11:
      return 3;
    case 12:
      return 5;
  }
}

char* getDay(int day)
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

int main(int argc, char **argv){
  char *dateStr = argv[1];
  struct dateCoords inputDate = stringToStruct(dateStr);
  struct dateCoords endJulian = stringToStruct("1752-09-02");
  struct dateCoords startGregorian = stringToStruct("1752-09-14");
  int isjulian = isJulian(inputDate, endJulian, startGregorian);
  int isleapyear = isLeapYear(inputDate, isjulian);

  int day_code, month_code, year_code, century_code, leap_code;
  switch (isjulian){
  case 0:
      printf("The date is Gregorian\n");
      century_code = (3 - inputDate.s_century) % 4;
      while (century_code < 0) {
	century_code += 4;
	};
      century_code *= 2;
      break;
  case 1:
      printf("The date is Julian\n");
      century_code = (4 - inputDate.s_century) % 7;
      while (century_code < 0) {
	century_code += 7;
      }
      break;
  case 2:
      break;
  }

  switch (isleapyear){
    case 0:
      printf("The year is not a leap year.\n");
      leap_code = 0;
      break;
    case 1:
      printf("The year is a leap year.\n");
      if (inputDate.s_month == 1 || inputDate.s_month == 2)
	leap_code = 1;
      else
	leap_code = 0;
      break;
    case 2:
      printf("This is an impossible date!\n");
      exit(1);
  }

  day_code = inputDate.s_day;
  month_code = getMonthCode(inputDate.s_month);
  year_code = inputDate.s_year + inputDate.s_year / 4;
  int penultimate_number = (day_code + month_code + year_code + century_code - leap_code);
  int final_number = penultimate_number % 7;

  printf("Date string is %s\n", dateStr);
  printf("Day:\t\t%d -> %d\n", inputDate.s_day, day_code);
  printf("Month:\t\t%d -> %d\n", inputDate.s_month, month_code);
  printf("Year:\t\t%d -> %d\n", inputDate.s_year, year_code);
  printf("Century:\t%d -> %d\n", inputDate.s_century, century_code);
  printf("Leap code:\t%d\n\n", leap_code);
  printf("%d + %d + %d + %d - %d = %d\n", day_code, month_code, year_code, century_code, leap_code, penultimate_number);
  printf("%d %% 7 = %d\n\n", penultimate_number, final_number);

  printf("%s\n", getDay(final_number));
  return(0);
}
