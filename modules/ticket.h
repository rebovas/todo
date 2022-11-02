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
        int correct();
        int isEmpty();
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
        int changeProperty(string newDiscription);
        int changeProperty(Date date);
        int changeProperty(Time time);        
        int getId();
};
