#include "ticket.h"

using namespace std;

// d - date, t - time
enum sortBy {d, t};

class Archive
{
    private:
        Ticket *tickets;    
        unsigned int countTickets;
                
    public:
        Archive();
        Archive(Ticket ticket);
        Archive();
        int addTicket(Ticket ticket);
        int delTicket(unsigned short int id);
        int sortTickets(sortBy kindSort);
};
