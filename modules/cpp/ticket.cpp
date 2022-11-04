#include "../ticket.h"


int countDayMonth(unsigned short int month, unsigned short int year);


// Empty time and date don't using in processing. Need recreate type with parametrs or use method.
// Just create an empty Time
Time::Time()
{
    this->minutes = EMPTY;
    this->hours = EMPTY;
};

Time::Time(unsigned short int minutes, unsigned short int hours)
{
    if(hours > 24 || minutes > 59)
    {
        *this = Time();
    }
    else
    {
        this->minutes = minutes;
        this->hours = hours;
    }
};

int Time::isEmpty()
{
    if(this->minutes == EMPTY || this->hours == EMPTY)
    {
        return 1;
    }
    else return 0;
};

// Just create an empty Date
Date::Date()
{
    this->day = EMPTY;
    this->month = EMPTY;
    this->year = EMPTY;
};

Date::Date(unsigned short int day, unsigned short int month, unsigned short int year)
{
    this->day = day;
    this->month = month;
    this->year = year;

    if(!this->correct())
    {
        *this = Date();
    }
};

// Code 0 - correct date
// Error code 1 - out of date 
// Error code 2 - incorrect amount of days and less than 32
int Date::correct()
{
    time_t now = time(0); 
    tm *ltm = localtime(&now);

    if(this->month == 0 || this->month > 12)
    {
        return 1;
    }
    else if(this->day == 0 || this->day > 31)
    {
        return 1;
    }
    else if(this->year < 1970 + ltm->tm_year)
    {
        return 1;
    }
    
    if(this->day > countDayMonth(this->month, this->year))
    {
        return 2;
    }

    return 0;
};

int Date::isEmpty()
{
    if(this->day == EMPTY || this->month == EMPTY || this->year == EMPTY)
    {
        return 1;
    }
    else return 0;
}

Ticket::Ticket()
{
    this->id = EMPTY;
    this->date = Date();
    this->time = Time();
    this->discription = string();
};

Ticket::Ticket(unsigned short int id, Time time, Date date, string discription)
{

    if(time.isEmpty() || date.isEmpty() || discription.empty() || id == EMPTY)
    {
        *this = Ticket();
    }
    else
    {
        this->id = id;
        this->time = time;
        this->date = date;
        this->discription = discription;
    }
};

int Ticket::isEmpty()
{
    if(this->date.isEmpty() || this->time.isEmpty() || this->id == EMPTY || this->discription.empty())
    {
        return 1;
    }
    else return 0;
};

int Ticket::changeProperty(string newDiscription)
{
    // If ticket empty, don't change discription
    if(newDiscription.empty() || this->isEmpty())
    {
        return 1;
    }
    else 
    {
        this->discription = newDiscription;
    }

    return 0;
};

int Ticket::changeProperty(Date date)
{
    if(date.isEmpty() || this->isEmpty())
    {
        return 1;
    }
    else
    {
        this->date = date;
    }

    return 0;
};

int Ticket::changeProperty(Time time)
{
    if(time.isEmpty() || this->isEmpty())
    {
        return 1;
    }
    else 
    {
        this->time = time;
    }

    return 0;
};

int Ticket::getId()
{
    if(this->isEmpty())
    {
        return EMPTY;
    }
    else
    {
        return this->id;
    }
}

int isBissextile(unsigned short int year)
{
    int res = (1 - ((year % 4) + 2) % ((year % 4) + 1));
    res *= ((year % 100) + 2) % ((year % 100) + 1);
    res += (1 - ((year % 400) + 2) % ((year % 400) + 1));

    return res;
};

int countDayMonth(unsigned short int month, unsigned short int year)
{
    int res = 28 + ((0x3bbeecc >> (month * 2)) & 3);
    if(isBissextile(year)) res += !((2 - month) / 1); 

    return res;
};

int Date::setDay(unsigned short int day)
{
    this->day = day;
    return 0;
};

int Date::setMonth(unsigned short int month)
{
    this->month = month;
    return 0;
};

int Date::setYear(unsigned short int year)
{
    this->year = year;
    return 0;
};

int Time::correct()
{
    if(this->minutes < 60 || this->hours < 24) return 1;
    else return 0;
};

int Time::setMinutes(unsigned short int minutes)
{
    this->minutes = minutes;
    return 0;
};

int Time::setHours(unsigned short int hours)
{
    this->hours = hours;
    return 0;
};

Time Ticket::getTime()
{
    return this->time;
}

int Ticket::addDiscription(string partDisctn)
{
    this->discription += " " + partDisctn;
    return 0;
};

string Time::toString()
{
    if(this->isEmpty()) return string();

    return to_string(this->minutes) + ' ' + to_string(this->hours);
};

string Date::toString()
{
    if(this->isEmpty()) return string();

    return to_string(this->day) + ' ' + to_string(this->month) + ' ' + to_string(this->year);
}

string Ticket::toString()
{
    if(this->isEmpty()) return string();

    string ticketStr;
    
    ticketStr += to_string(this->id) + ' ' + this->date.toString() + ' ' + this->time.toString() + ' ' + this->discription;

    return ticketStr;
}
