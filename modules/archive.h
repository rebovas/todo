#pragma once
#include "ticket.h"
#include <fstream>
#include <strstream>
#include <iostream>

using namespace std;

// d - date, t - time, i - id
enum sortBy {d, t, dt, i};

class Archive
{
    private:
        Ticket *tickets;    
        unsigned int countTickets;
        string filename;
                
    public:
        Archive();
        Archive(Ticket ticket);
        Archive(string filename);
        int outputTicket(unsigned short int id);
        void outputTickets();
        int writeTickets();
        int addTicket(Ticket ticket);
        int delTicket(unsigned short int id);
        int sortTickets(sortBy kindSort);
        int isEmpty();
        int update();   // Delete old and same tickets
        int sameIds(unsigned short int id);  // Return index of last same ticket, otherwise return -1
        unsigned short int generateId();    // Generate special identificator for ticket
                                            // Return 0 if fail
};
