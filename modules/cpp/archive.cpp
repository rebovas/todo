#include "../archive.h"


Archive::Archive()
{
    this->tickets = nullptr;
    this->countTickets = 0;
    this->filename = string();
};

Archive::Archive(Ticket ticket)
{
    if(!ticket.isEmpty())
    {
        this->tickets = new Ticket(ticket); 
        this->countTickets = 1;
    }
    else
    {
        *this = Archive();
    }
};

int Archive::addTicket(Ticket ticket)
{
    if(!ticket.isEmpty())
    {
        Archive arch = Archive(ticket);
        arch.update();
        if(arch.countTickets == 0) return 2;

        if(this->sameIds(ticket.getId()) != -1) return 1; 

        Ticket *newTickets = new Ticket[++this->countTickets]();
        if(this->countTickets == 1) newTickets = new Ticket();

        for(int i = 0; i < this->countTickets - 1; i++)
        {
            newTickets[i] = this->tickets[i];
        }
        newTickets[this->countTickets - 1] = ticket;

        if(this->countTickets == 2)
        {
            delete this->tickets;
        }
        else if(this->countTickets > 2) delete[] this->tickets;
        
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
    if(this->countTickets == 0) return 1;

    int flag = 1, foundIndx,  indx = 0;

    for(int i = 0; i < this->countTickets && flag; i++)
    {
        if(this->tickets[i].getId() != EMPTY && this->tickets[i].getId() == id)
        {
            foundIndx = i;
            flag = 0;
        }
    }

    if(flag) return 1;

    Ticket *newTickets = new Ticket[--this->countTickets]();
    if(this->countTickets == 1) newTickets = new Ticket();
    else if(this->countTickets == 0) newTickets = nullptr;

    for(int i = 0; i < foundIndx; i++)
    {
        newTickets[indx++] = this->tickets[i];
    }

    for(int i = foundIndx + 1; i <= this->countTickets; i++)
    {
        newTickets[indx++] = this->tickets[i];
    }

    if(this->countTickets == 0)
    {
        delete this->tickets;
    }
    else if(this->countTickets > 0)
    {
        delete[] this->tickets;
    }

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

            for(stream >> word; stream.good() || !stream.fail(); stream >> word)
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
   if (this->countTickets == 0 || this->tickets == nullptr || this->filename.empty()) return 1;
   else return 0;
};

int Archive::writeTickets()
{
   ofstream file(this->filename, ios_base::in | ios_base::trunc);

   if(!file.is_open()) return 1;

   for(int i = 0; i < this->countTickets; i++)
   {
        file << this->tickets[i].toString();
        file << '\n';
   }
    
   file.close();

   return 0;
};

int Archive::update() // Now delete tickets only with those dates that less the current
                      // Need will upgrade this method
{
    time_t now = time(0); 
    tm *ltm = localtime(&now);

    if(ltm == NULL) return 1;

    Date currDate = Date(ltm->tm_mday, ltm->tm_mon + 1, 1900 + ltm->tm_year);
    Time currTime = Time(ltm->tm_min, ltm->tm_hour);

    for(int i = 0; i < this->countTickets; i++) // Delete same id's
    {
        if(this->tickets[i].isEmpty()) return 1;
        else
        {
            if((this->tickets[i].getDate() < currDate) ||
             (this->tickets[i].getDate() == currDate && this->tickets[i].getTime() < currTime))
            {
                this->delTicket(this->tickets[i].getId()); 
                i--;
            }
        }
    }

    return 0;
};

int Archive::sameIds(unsigned short int id)
{
    int indx = -1;

    for(int i = 0; i < this->countTickets; i++)
    {
        if(this->tickets[i].getId() == id) 
        {
            indx = i;
        }
    }

    return indx;
};

unsigned short int Archive::generateId()
{
    for(unsigned short int resId = 1; resId < EMPTY; resId++)
    {
        if(this->sameIds(resId) == -1) return resId;        
    }

    return 0;
};

void Archive::outputTickets(unsigned short int specCount)
{
    if(this->countTickets == 0)
    {
        cout << "Empty" << endl;
        return;
    }

    for(int i = 0; i < this->countTickets && i < specCount; i++)
    {
        cout << this->tickets[i].toString() << endl;                        
    }
};

int Archive::outputTicket(unsigned short int id)
{
    for(int i = 0; i < this->countTickets; i++)
    {
        if(this->tickets[i].getId() == id)
        {
            cout << tickets[i].toString() << endl;
            return 0;
        }
    }
    cout << "Empty" << endl;
    return 1;
};

int Archive::sort(string kindSort)
{
   if(strcasecmp(kindSort.c_str(), "d") == 0)
   {
       this->sortDate();
       return 0;
   }
   else if(strcasecmp(kindSort.c_str(), "t") == 0)
   {
        this->sortTime();
        return 0;
   }
   else if(strcasecmp(kindSort.c_str(), "dt") == 0 || strcasecmp(kindSort.c_str(), "td") == 0)
   {
        this->sortDateTime();
        return 0;
   }

   return 1;
};

void Archive::sortDate()
{
    for(int i = 0; i < this->countTickets; i++)
    {
        for(int j = 0; j < this->countTickets - 1; j++)
        {
            if(this->tickets[j + 1].getDate() < this->tickets[j].getDate())
            {
                Ticket saveTicket = this->tickets[j];

                this->tickets[j] = this->tickets[j + 1];
                this->tickets[j + 1] = saveTicket;
            }
        }
    }
}

void Archive::sortTime()
{
    for(int i = 0; i < this->countTickets; i++)
    {
        for(int j = 0; j < this->countTickets - 1; j++)
        {
            if(this->tickets[j + 1].getTime() < this->tickets[j].getTime())
            {
                Ticket saveTicket = this->tickets[j];

                this->tickets[j] = this->tickets[j + 1];
                this->tickets[j + 1] = saveTicket;
            }
        }
    }
}

void Archive::sortId()
{
    for(int i = 0; i < this->countTickets; i++)
    {
        for(int j = 0; j < this->countTickets - 1; j++)
        {
            if(this->tickets[j + 1].getId() < this->tickets[j].getId())
            {
                Ticket saveTicket = this->tickets[j];

                this->tickets[j] = this->tickets[j + 1];
                this->tickets[j + 1] = saveTicket;
            }
        }
    }
}

void Archive::sortDateTime()
{
    for(int i = 0; i < this->countTickets; i++)
    {
        for(int j = 0; j < this->countTickets - 1; j++)
        {
            if(this->tickets[j + 1].getDate() < this->tickets[j].getDate()
                || (this->tickets[j].getDate() == this->tickets[j + 1].getDate()
                    && this->tickets[j + 1].getTime() < this->tickets[j].getTime()))
            {
                Ticket saveTicket = this->tickets[j];

                this->tickets[j] = this->tickets[j + 1];
                this->tickets[j + 1] = saveTicket;
            }
        }
    }
}

