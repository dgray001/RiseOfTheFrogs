/*
commandClass.h
The command class allows any possible command (from quitting the application to moving to
fighting) to be grouped as a common type.
*/

#ifndef COMMAND_CLASS
#define COMMAND_CLASS

#include <string>
#include <vector>

class Battle;
class Environment;
class Player;

class Command {
    private:
        std::string name{}; // has to be unique since is also the ID code
        std::string shortDescription{}; // for the commands command
        std::string longDescription{}; // for the help command
        std::vector<std::string> otherNames{}; // alternate names for the command
        int energyCost{}; // energy cost of the command

    public:
        Command() {}; // default constructor
        Command(std::string name, std::string shortDescription, std::string longDescription,
            std::vector<std::string> otherNames); // base constructor
        Command(std::string name);
        Command(std::string name, Player player); // each command has a unique name

        std::string getName() { return this->name; } // getters
        std::string getShortDescription() { return this->shortDescription; }
        std::string getLongDescription() { return this->longDescription; }
        std::vector<std::string> getOtherNames() { return this->otherNames; }
        int getEnergyCost() { return this->energyCost; }

        //void setName(std::string x) { this->name = x; } // setters
        void setShortDescription(std::string x) { this->shortDescription = x; }
        void setLongDescription(std::string x) { this->longDescription = x; }
        void setOtherNames(std::vector<std::string> x) { this->otherNames = x; }
        void setEnergyCost(int x) { this->energyCost = x; }

        bool checkNames(std::string inputName);

        std::string saveGame();
};

#endif