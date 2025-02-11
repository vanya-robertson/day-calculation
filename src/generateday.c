#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "commonfunctions.h"

int getJulianNumber(struct dateCoords, int isjulian); // algorithm from https://tondering.dk/claus/cal/julperiod.php
const int getMonthLength(int month,int isleapyear); // returns int of month length
char* getISODate(int input);
int randominrange(int min, int max); // algorithm from https://tondering.dk/claus/cal/julperiod.php

int getJulianNumber(struct dateCoords input, int isjulian) {
  int a = (14 - input.s_month) / 12;
  int y = 100*input.s_century + input.s_year + 4800 - a;
  int m = input.s_month + 12 * a - 3;
  switch (isjulian){
    case 0:
      return(input.s_day + (153*m+2)/5 + y*365 + y/4 - y/100 + y/400 - 32045);
    case 1:
      return(input.s_day + (153*m+2)/5 + y*365 + y/4 - 32083);
    default:
      printf("This is an impossible date!\n");
      exit(1);
  }
};

const int getMonthLength (int month, int isleapyear) {
  switch (month){
    case 1:
      return(31);
    case 2:
      if (isleapyear){
	return(29);
      } else {
	return(28);
      };
    case 3:
      return(31);
    case 4:
      return(30);
    case 5:
      return(31);
    case 6:
      return(30);
    case 7:
      return(31);
    case 8:
      return(31);
    case 9:
      return(30);
    case 10:
      return(31);
    case 11:
      return(30);
    case 12:
      return(31);
    default:
      if (month > 12){
	printf("Error: There are only 12 months\n");
	exit(1);
      } else {
	printf("The input format is incorrect\n");
	exit(1);
      }
   }
}

char* getISODate(int input) {
  int b;
  int c;
  int isjulian;
  if (input <= 2361221){
    isjulian = 1;
  } else if (input >= 2361222){
    isjulian = 0;
  }

  if (isjulian == 0) {
    int a = input + 32044;
    b = (4*a+3)/146097;
    c = a - (b*146097)/4;
  }
  else if (isjulian == 1) {
    b = 0;
    c = input + 32082;
  }
  else if (isjulian == 2) {
      printf("This is an impossible date!\n");
      exit(1);
  }
  int d = (4*c+3)/1461;
  int e = c - (1461*d)/4;
  int m = (5*e+2)/153;
  int day   = e - (153*m+2)/5 + 1;
  int month = m + 3 - 12*(m/10);
  int year  = b*100 + d - 4800 + m/10;

  char *answer = malloc(14);
  sprintf(answer,"%04d-%02d-%02d",year,month,day);
  return(answer);
};

int randominrange(int min, int max){
  int fd = open("/dev/urandom", O_RDONLY);
  int rd_num;
  read(fd, &rd_num, sizeof(rd_num));
  unsigned int seed = rd_num;
  return (rand_r(&seed) % (max - min + 1) + min);
  close(fd);
}

int main(int argc, char **argv){

  char *minDateString = argv[1];
  char *maxDateString = argv[2];

  if (argc == 1) {
    printf("Error: There must be two arguments in the format \"yyyy-MM-dd\"\n");
    exit(1);
  }
  else if (argc > 3) {
    printf("Error: There must only be two arguments in the format \"yyyy-MM-dd\"\n");
    exit(1);
  }
  else if ((strlen(minDateString) != 10) || (strlen(maxDateString) != 10)) {
    printf("Error: There must be two arguments in the format \"yyyy-MM-dd\"\n");
    exit(1);
  }
  else if ((minDateString[4] != '-') || (minDateString[7] != '-') || (maxDateString[4] != '-') || (maxDateString[7] != '-')) {
    printf("Error: There must be two arguments in the format \"yyyy-MM-dd\"\n");
    exit(1);
  }

  struct dateCoords latestJulian = stringToStruct("1752-09-02");
  struct dateCoords earliestGregorian = stringToStruct("1752-09-14");

  struct dateCoords firstArgStruct = stringToStruct(argv[1]);
  int minIsJulian = isJulian(firstArgStruct, latestJulian, earliestGregorian);
  if (firstArgStruct.s_day > getMonthLength(firstArgStruct.s_month, minIsJulian)){
    printf("Error: There are only %d days in %s\n", getMonthLength(firstArgStruct.s_month, minIsJulian), getMonthName(firstArgStruct.s_month));
    exit(1);
  }

  struct dateCoords secondArgStruct = stringToStruct(argv[2]);
  int maxIsJulian = isJulian(secondArgStruct, latestJulian, earliestGregorian);
  if (secondArgStruct.s_day > getMonthLength(secondArgStruct.s_month, minIsJulian)){
    printf("Error: There are only %d days in %s\n", getMonthLength(secondArgStruct.s_month, maxIsJulian), getMonthName(secondArgStruct.s_month));
    exit(1);
  }

  int minJulianNum = getJulianNumber(firstArgStruct,minIsJulian);
  int maxJulianNum = getJulianNumber(secondArgStruct,maxIsJulian);

  printf("%s\n", (getISODate(randominrange(minJulianNum, maxJulianNum))));
  return(0);
}
