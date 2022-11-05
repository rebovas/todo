#include "../archive.h"

using namespace std;

int main()
{
    Archive arch("../tickets/archive");

    cout << arch.isEmpty() << endl;

    arch.writeTickets();
    
}
