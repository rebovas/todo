#include "../archive.h"
#include "../commands.h"

using namespace std;

int main(int argc, char *argv[])
{
    Archive arch("../tickets/archive");
    Command command(argv, argc);

    while(!command.execute(command.getArg(), &arch));
}
