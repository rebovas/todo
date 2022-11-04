#include "ticket.h"
#include <fstream>
#include <strstream>

using namespace std;

// d - date, t - time
enum sortBy {d, t};

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
        int writeTickets();
        int addTicket(Ticket ticket);
        int delTicket(unsigned short int id);
        int sortTickets(sortBy kindSort);
        int isEmpty();
};
