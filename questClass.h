/*
questClass.h
Quests are objectives with rewards the player can see. When the player achieves a quest it gets destroyed.
*/

#ifndef QUEST_CLASS
#define QUEST_CLASS

#include <string>
#include <vector>

class Environment;

class Quest {
    private:
        int ID{}; // unique identifier
        std::string name{};
        std::string description{};
        int xpReward{};
        int creditReward{};
        int foulReward{};

    public:
        Quest() {};
        Quest(int ID);
        int getID() { return this->ID; }
        std::string getName() { return this->name; }
        void rewards(int xp, int credit, int foul);
        bool checkCondition(Environment* currentEnvironment); // return true/false
        std::vector<int> meetCondition(); // return rewards to environment
        void printQuest();
        void printQuestProgress(Environment* currentEnvironment, int largestName);
        std::string saveGame();
};

#endif