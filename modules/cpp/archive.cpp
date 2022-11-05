#include "../archive.h"


Archive::Archive()
{
    this->tickets = new Ticket();
    this->countTickets = 0;
    this->filename = string();
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

    this->filename = string();
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

    if(flag) return -1;

    Ticket *newTickets = new Ticket[--this->countTickets]();

    for(int i = 0; i < foundIndx; i++)
    {
        newTickets[i] = this->tickets[i];                                                        
    }

    for(int i = foundIndx + 1; i < this->countTickets; i++)
    {
        newTickets[i] = this->tickets[i];
    }

    delete this->tickets;

    this->tickets = newTickets;

    return 0;
};

Archive::Archive(string filename)
{
    *this = Archive();

   ifstream file(filename);  
   string line, word;

   if(file.is_open())
   {
        this->filename = filename;

        for(getline(file, line); !file.eof(); getline(file, line))
        {
            unsigned short int id, day, month, year, minutes, hours;
            string disc;
            strstream stream;
            stream << line;

            stream >> word;

            if(stream.good())
            {
                id = stoi(word);                
            }

            for(int i = 0; stream.good() && i < 3; i++)
            {
                stream >> word;

                switch(i)
                {
                    case 0: day = stoi(word); break;
                    case 1: month = stoi(word); break;
                    case 2: year = stoi(word); break;
                }
            }

            for(int i = 0; stream.good() && i < 2; i++)
            {
                stream >> word;

                switch(i)
                {
                    case 0: minutes = stoi(word); break;
                    case 1: hours = stoi(word); break;
                }
            }

            for(stream >> word; stream.good(); stream >> word)
            {
                disc += word + ' ';
            }

            Ticket ticket = Ticket(id, Time(minutes, hours), Date(day, month, year), disc);

            if(!ticket.isEmpty() || !ticket.getDate().notCorrect() || ticket.getTime().correct() || ticket.getId() != EMPTY)
            {
                this->addTicket(ticket);
            }
        }
        file.close();
   }
   else *this = Archive();
};

int Archive::isEmpty()
{
   if (this->countTickets == 0 || this->tickets->isEmpty() || this->filename.empty()) return 1;
   else return 0;
};

int Archive::writeTickets()
{
   if(this->isEmpty()) return 1;

   ofstream file(this->filename, ios_base::in | ios_base::trunc);

   if(!file.is_open()) return 2;

   for(int i = 0; i < this->countTickets; i++)
   {
        file << this->tickets[i].toString();
        file << '\n';
   }
    
   file.close();

   return 0;
};
