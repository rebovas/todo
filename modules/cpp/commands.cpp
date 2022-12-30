#include "../commands.h"



Command::Command(char *argv[], int args)
{
    this->args = new string[--args];

    int indArgs = 0;
    for(int i = 1; i <= args; i++)
    {
        this->args[indArgs++] = string(argv[i]);
    };
    
    this->countArgs = args;
}

string Command::getArg()
{
    if(this->countArgs == 0) return string();

    string returnArg = this->args[0].c_str();     

    int indArgs = 0;
    string *newArgs = new string[--this->countArgs];

    for(int i = 1; i <= this->countArgs; i++)
    {
        newArgs[indArgs++] = this->args[i]; 
    }
    delete[] this->args;

    this->args = newArgs;

    return returnArg;
};

int cmd::isSame(string command) const
{
    if(command == this->shortName || command == this->longName) return 1;
    else return 0;
};

int Command::execute(string command, Archive *archive)
{
    cmd saveCommand;

    if(command == string()) return 1;
    for(int i = 0; i < this->amountCmds; i++)
    {
        if(this->commands[i].isSame(command))
        {
            this->runExecution(commands[i], archive);
            return 0;
        }
    }
    cout << "Command " << command << " not exist" << endl;
    return 1;
};

int Command::runExecution(cmd command, Archive *archive)
{
    if(command.shortName == "-a")
    {
        unsigned short int day, month, year, minutes, hours;
        char point;
        cout << "Enter date in DD.MM.YYYY format: ";
        cin >> day >> point >> month >> point >> year;
        cout << "Enter time in HH:MM format: ";
        cin >> hours >> point >> minutes;
        string discription;
        cout << "Enter discription: ";
        cin.ignore();
        getline(cin, discription);
        Ticket tick = Ticket(archive->generateId(), Time(minutes, hours), Date(day, month, year), discription);
        cout << "Input task: "<< tick.toString() << endl;
        int result = archive->addTicket(Ticket(archive->generateId(), Time(minutes, hours), Date(day, month, year), discription)); 
        if(result == 1)
        {
            cout << "Task isn't added" << endl;
            return 1;
        }
        else
        {
            cout << "Task added" << endl;
            archive->writeTickets();
            return 0;
        }
            
    }
    else if(command.shortName == "-d")
    {
        int searchId;
        cout << "Input id task to delete him: ";
        cin >> searchId;
        int result = archive->outputTicket(searchId);
        if(result == 0) 
        {
            cout << "Delete this task? [yes, no]: ";
            string response;
            cin >> response;
            if(strcasecmp(response.c_str(), "yes") == 0)
            {
                archive->delTicket(searchId); 
                archive->writeTickets();
                cout << "Task deleted" << endl;
            }
            else cout << "Task not deleted" << endl;
        }
    }
    else if(command.shortName == "-o")
    {
        archive->outputTickets();
    }
    return 0;
};
