#include <iostream>
#include <ctime>
#include <climits>
#define EMPTY USHRT_MAX


using namespace std;


class Time
{
    private:
        unsigned short int minutes;
        unsigned short int hours;

    public:
        Time();
        Time(unsigned short int minutes, unsigned short int hours);
        int isEmpty();
        int setMinutes(unsigned short int minutes);
        int setHours(unsigned short int hours);
        int correct();
        string toString();
};

class Date
{
    private:
        unsigned short int day;
        unsigned short int month;
        unsigned short int year;

    public:
        Date();
        Date(unsigned short int day, unsigned short int month, unsigned short int year);
        int notCorrect();
        int isEmpty();
        int setDay(unsigned short int day);
        int setMonth(unsigned short int month);
        int setYear(unsigned short int year);
        string toString();
};

class Ticket
{

    private:
        unsigned short int id;
        Date date;
        Time time;
        string discription;

    public:
        Ticket();
        Ticket(unsigned short int id, Time time, Date date, string discription);
        int isEmpty();
        unsigned short int getId();
        int addDiscription(string partDisctn);
        int setId(unsigned short int &id);
        Date& getDate();
        Time& getTime();
        string toString();
};
