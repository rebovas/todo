#pragma once
#include "archive.h"
#include <cstring>

struct cmd
{
    string shortName;
    string longName;
    int isSame(string command) const;
};

class Command
{
    private:
        const static int amountCmds = 3;
        string *args;
        unsigned short int countArgs;
        const cmd commands[amountCmds] = {
                                            {"-a", "--add"},
                                            {"-d", "--delete"}, 
                                            {"-o", "--output"}
                                        };
        int runExecution(cmd command, Archive *archive);

    public:
        Command(char *argv[], int args);
        string getArg();
        int execute(string command, Archive *archive);
};
