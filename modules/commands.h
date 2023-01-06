#pragma once
#include "archive.h"

struct cmd
{
    string shortName;
    string longName;
    int isSame(string command) const;
};

class Command
{
    private:
        const static int amountCmds = 6;
        string *args;
        unsigned short int countArgs;
        const cmd commands[amountCmds] = {
                                            {"-a", "--add"},
                                            {"-d", "--delete"}, 
                                            {"-o", "--output"},
                                            {"-f", "--first"},
                                            {"-u", "--update"},
                                            {"-s", "--sort"}
                                        };
        bool executed;

    public:
        int runExecution(cmd command, Archive *archive);
        Command(char *argv[], int args);
        string getArg();
        int execute(string command, Archive *archive);
};
