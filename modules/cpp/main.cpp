#include "../archive.h"

using namespace std;

int main()
{
    Archive arch("../tickets/archive");

    arch.addTicket(Ticket(arch.generateId(), Time(0, 15), Date(9, 11, 2022), "Try pass the exam"));

    arch.update();

    arch.writeTickets();
}
