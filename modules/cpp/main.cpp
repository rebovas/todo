#include "../archive.h"
#include "../commands.h"

using namespace std;

int main(int argc, char *argv[])
{
    Archive arch("/usr/share/todo/archive");
    Command command(argv, argc);

    while(!command.execute(command.getArg(), &arch));

    arch.update();
    arch.writeTickets();
}
