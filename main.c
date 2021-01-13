#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma warning ( disable : 4996 )

typedef struct duration {
    int hours, mins;
} DURATION;

typedef struct departure {
    int day;
    char month[4];
    int year, Hour, Min;
} DEPARTURE;

typedef struct flight {
    const char* pStartingPoint;
    DEPARTURE Departure;
    DURATION Duration;
    int TimeZone;
} FLIGHT;

FLIGHT flights[] = {
    {"Buenos Aires", {1, "Mar", 2020, 19, 40}, {18, 0}, -3},
    {"Guatemala City", {20, "Feb", 2020, 12, 20}, {19, 15}, -6},
    {"Bangkok", {20, "Jan", 2020, 18, 30}, {10, 25}, 7},
    {"Helsinki", {27, "Dec", 2020, 23, 55}, {0, 35}, 2},
    {"Stockholm", {31, "Dec", 2020, 17, 40}, {1, 0}, 1}
};

char** Exam(FLIGHT* pFlights, int nFlights);
int Month(char month[4]);

int main() {

    char** ppCheck;
    ppCheck = Exam(flights, 5);

    for (int i = 0; i < 5; i++) {
        printf("> %s\n", *(ppCheck + i));
    }

    return 0;
}

int Month(char month[4]) {
    if (strcmp(month, "Jan") == 0) return 0;
    else if (strcmp(month, "Feb") == 0) return 1;
    else if (strcmp(month, "Mar") == 0) return 2;
    else if (strcmp(month, "Apr") == 0) return 3;
    else if (strcmp(month, "May") == 0) return 4;
    else if (strcmp(month, "Jun") == 0) return 5;
    else if (strcmp(month, "Jul") == 0) return 6;
    else if (strcmp(month, "Aug") == 0) return 7;
    else if (strcmp(month, "Sep") == 0) return 8;
    else if (strcmp(month, "Oct") == 0) return 9;
    else if (strcmp(month, "Nov") == 0) return 10;
    else if (strcmp(month, "Dec") == 0) return 11;
    else return 0;
}

char** Exam(FLIGHT* pFlights, int nFlights) {
    char** ppResults = (char**)malloc(nFlights * sizeof(char*));
    for (int i = 0; i < nFlights; i++) {
        char* pOut = (char*)malloc((strlen(pFlights[i].pStartingPoint) + 30) * sizeof(char));

        //Month can be done in different way, check at the end of the code.
        struct tm dep = {
            0,
            pFlights[i].Departure.Min,
            pFlights[i].Departure.Hour,
            pFlights[i].Departure.day,
            Month(pFlights[i].Departure.month),
            pFlights[i].Departure.year - 1900 };
        
        struct tm arr = dep;

        arr.tm_hour += pFlights[i].Duration.hours;
        arr.tm_hour -= pFlights[i].TimeZone;
        arr.tm_hour += 2;
        arr.tm_min += pFlights[i].Duration.mins;

        //check for new hour-day-month-year
        if (arr.tm_min > 59) {
            arr.tm_min -= 60;
            arr.tm_hour += 1;
        }

        if (arr.tm_hour > 23) {
            arr.tm_hour -= 24;
            arr.tm_mday += 1;
        }

        if (arr.tm_mday > 31) {
            arr.tm_mday -= 31;
            arr.tm_mon += 1;
        }

        if (arr.tm_mon > 11) {
            arr.tm_mon -= 12;
            arr.tm_year += 1;
        }


        char fres[80] = "From ";
        strcat(fres, pFlights[i].pStartingPoint);
        char res[80];

        strftime(res, 100, " arrives %H:%M %d-%m-%Y", &arr);
        strcat(fres, res);
        for (int j = 0; j < strlen(fres); j++) {
            *(pOut + j) = fres[j];
        }
        *(pOut + (strlen(pFlights[i].pStartingPoint) + 30)) = '\0';
        *(ppResults + i) = pOut;
    }
    return ppResults;
}

/* Months can be also found in another way:
const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

for (int i = 0; i < nFlights; i++) {
for (int x = 0; x < 12; x++) {
if (strcmp(months[x], pFlights[i].Departure.month) == 0) {

Then in the struct tm dep month will be 'x'*/
