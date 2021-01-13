# c-exam
 Taltech Fundamentals of Programming 2020 Autumn Exam

Let us have
~~~
typedef struct duration {
    int hours, mins;
} DURATION;
~~~
~~~
typedef struct departure {
    int day;
    char month[4];
    int year, Hour, Min;
} DEPARTURE;
~~~
~~~
typedef struct flight {
    const char* pStartingPoint;
    DEPARTURE Departure;
    DURATION Duration;
    int TimeZone;
} FLIGHT;
~~~
Write a function with prototype:
~~~
char** Exam(FLIGHT* pFlights, int nFlights);
~~~
where pFlights points to an array of nFlights elements. Example:
~~~
FLIGHT flights[] = {
    {"Buenos Aires", {1, "Mar", 2020, 19, 40}, {18, 0}, -3},
    {"Guatemala City", {20, "Feb", 2020, 12, 20}, {19, 15}, -6},
    {"Bangkok", {20, "Jan", 2020, 18, 30}, {10, 25}, 7},
    {"Helsinki", {27, "Dec", 2020, 23, 55}, {0, 35}, 2},
    {"Stockholm", {31, "Dec", 2020, 17, 40}, {1, 0}, 1}
};
~~~
The output value is an array of pointers to strings (see slide Pointers (28)) presenting the arrival date and time to Tallinn. Example illustrating the format: "From Buenos Aires arrives 02-12-2020 15:30". The order of flights in result may be any.
You need to use C time handling functions like mktime. About time zones see https://www.worldtimezone.com and https://www.timeanddate.com/worldclock/converter-classic.html. Consider tnat daylight saving time in starting point countries is not used. 
The input values may not be zero. If those conditions are not satisfried, the function must return zero. However, if those conditions are satisfied, we may be sure that the input is 100% correct. Write also main to test the code and print the result.
