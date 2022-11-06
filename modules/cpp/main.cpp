#include "../archive.h"

using namespace std;

int main()
{
    Archive arch("../tickets/archive");

    cout << arch.isEmpty() << endl;

    cout << arch.delTicket(2) << endl;

    arch.writeTickets();
    
}
