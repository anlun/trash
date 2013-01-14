#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <langinfo.h>
#include <time.h>

#define MONTH_NUMBER		12
#define DAY_IN_WEEK_NUMBER	7

#define COLOR_RED	"\x1b[31m"
#define COLOR_GREEN	"\x1b[32m"
#define COLOR_BLUE	"\x1b[34m"
#define COLOR_CYAN	"\x1b[36m"
#define COLOR_RESET	"\x1b[0m"

int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int* daysBeforeMonth;

char* monthNames[MONTH_NUMBER + 1];
char* weekDayNames[DAY_IN_WEEK_NUMBER];

void weekDayNamesInit() {
	weekDayNames[0] = nl_langinfo(ABDAY_1);
	weekDayNames[1] = nl_langinfo(ABDAY_2);
	weekDayNames[2] = nl_langinfo(ABDAY_3);
	weekDayNames[3] = nl_langinfo(ABDAY_4);
	weekDayNames[4] = nl_langinfo(ABDAY_5);
	weekDayNames[5] = nl_langinfo(ABDAY_6);
	weekDayNames[6] = nl_langinfo(ABDAY_7);
}

void monthNamesInit() {
	monthNames[1] = nl_langinfo(MON_1);
	monthNames[2] = nl_langinfo(MON_2);
	monthNames[3] = nl_langinfo(MON_3);
	monthNames[4] = nl_langinfo(MON_4);
	monthNames[5] = nl_langinfo(MON_5);
	monthNames[6] = nl_langinfo(MON_6);
	monthNames[7] = nl_langinfo(MON_7);
	monthNames[8] = nl_langinfo(MON_8);
	monthNames[9] = nl_langinfo(MON_9);
	monthNames[10] = nl_langinfo(MON_10);
	monthNames[11] = nl_langinfo(MON_11);
	monthNames[12] = nl_langinfo(MON_12);
}

int getMonthAndYear(int argc, char *argv[], int* month, int *year) {
	char* date = argv[1];

	if (argc != 2) {
		printf("Uncorrect number of parameters! Use program with \"mm.yyyy\", ex \"2.2012\".\n");
		return 1;
	}

	if (sscanf(date, "%d.%d", month, year) != 2) {
		printf("Uncorrect parameter! Use program with \"mm.yyyy\", ex \"2.2012\".\n");
		return 1;
	}

	// month, year validation
	if (*month <= 0 || *month > MONTH_NUMBER) {
		printf("Uncorrect month parameter! Must be whole number between 1 and 12.\n");
		return 1;
	}

	if (*year <= 0) {
		printf("Uncorrect year parameter! Must be natural number.\n");
		return 1;
	}

	return 0;
}

int isLeapYear(int year) {
	if (
		( (year % 4 == 0) && (year % 100 != 0) )
		|| 
		(year % 400 == 0)
	) {
		return 1;
	} else {
		return 0;
	}
}

void prepareDaysBeforeMonth() {
	int i = 0;
	for (i = 1; i < MONTH_NUMBER + 1; i++) {
		daysBeforeMonth[i] = daysBeforeMonth[i - 1] + daysInMonth[i - 1];
	}
}

void printMonth(int year, int month, int startDayCode, int markedDay) {
	int day;
	int d1 = (year - 1) / 4;
	int d2 = (year - 1) / 100;
	int d3 = (year - 1) / 400;
	int dayCode = (year + d1 - d2 + d3) % DAY_IN_WEEK_NUMBER; // year dayCode
	char buffer[10];

	dayCode += daysBeforeMonth[month] % DAY_IN_WEEK_NUMBER; // month dayCode

	printf(COLOR_GREEN "%s" COLOR_RESET "," COLOR_GREEN " %d" COLOR_RESET, monthNames[month], year);
	printf("\n\n ");

	printf(COLOR_GREEN);
	for (day = 1; day < DAY_IN_WEEK_NUMBER + 1; day++) {
		printf("%s  ", weekDayNames[(day + startDayCode) % DAY_IN_WEEK_NUMBER]);
	}
	printf(COLOR_RESET);
	printf("\n");

	for (day = 1; day < 2 + (((dayCode - startDayCode + 6) + 2 * DAY_IN_WEEK_NUMBER) % DAY_IN_WEEK_NUMBER) * 5; day++)
	{
		printf(" ");
	}

	for (day = 1; day <= daysInMonth[month]; day++)
	{
		if (day != markedDay) {
			printf("%3d  ", day);
		} else {
			sprintf(buffer, "[%d", day);
			printf(COLOR_RED "%3s", buffer);
			printf("] " COLOR_RESET);
		}

		if ((day + dayCode - startDayCode + 6) % DAY_IN_WEEK_NUMBER == 0) {
			printf("\n " );
		}
	}
	printf("\n");
}

int currentDay(int year, int month) {
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (timeinfo->tm_year == (year - 1900) && timeinfo->tm_mon == (month - 1)) {
		return timeinfo->tm_mday;
	}

	return -1;
}

int main(int argc, char *argv[]) {
	int month;
	int year;
	
	if (getMonthAndYear(argc, argv, &month, &year)) {
		return 1;
	}
	daysInMonth[2] += isLeapYear(year);
	
	daysBeforeMonth = (int*) calloc(MONTH_NUMBER + 1, sizeof(int));
	prepareDaysBeforeMonth();

	setlocale(LC_ALL, "");
	weekDayNamesInit();
	monthNamesInit();

	printMonth(year, month, 6 + *nl_langinfo(_NL_TIME_FIRST_WEEKDAY), currentDay(year, month));

	free(daysBeforeMonth);	
	return 0;
}
