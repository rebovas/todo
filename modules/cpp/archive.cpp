#include "../archive.h"


Archive::Archive()
{
    this->tickets = new Ticket();
    this->countTickets = 0;
};

Archive::Archive(Ticket ticket)
{
    if(!ticket.isEmpty())
    {
        *this->tickets = ticket; 
        this->countTickets = 1;
    }
    else
    {
        this->tickets = new Ticket();
        this->countTickets = 0;
    }
};

int Archive::addTicket(Ticket ticket)
{
    if(!ticket.isEmpty())
    {
        Ticket *newTickets = new Ticket[++this->countTickets]();

        for(int i = 0; i < this->countTickets - 1; i++)
        {
            newTickets[i] = this->tickets[i];
        }
        newTickets[this->countTickets - 1] = ticket;

        delete this->tickets;
        this->tickets = newTickets;

        return 0;
    }
    else
    {
        return 1;
    }
};

int Archive::delTicket(unsigned short int id)
{
    int flag = 1, foundIndx; 

    for(int i = 0; i < this->countTickets && flag; i++)
    {
        if(this->tickets[i].getId() != EMPTY && this->tickets[i].getId() == id)
        {
            foundIndx = i;
            flag = 0;
        }
    }

    if(flag == 1) return -1;

    Ticket *newTickets = new Ticket[--this->countTickets]();

    for(int i = 0; i < foundIndx; i++)
    {
                        
    }
};
