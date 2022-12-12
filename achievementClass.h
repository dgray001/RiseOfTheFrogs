/*
achievementClass.h
Achievements are unseen (until completed) objectives which are never destroyed.
*/

#ifndef ACHIEVEMENT_CLASS
#define ACHIEVEMENT_CLASS

#include <string>
#include <vector>

class Player;
class Environment;

class Achievement {
    private:
        std::string name{}; // unique identifier
        std::string description{};
        int xpReward{};
        int creditReward{};
        int foulReward{};

    public:
        Achievement() {};
        Achievement(std::string name);
        std::string getName() { return this->name; }
        bool checkCondition(Player thePlayer);
        void meetCondition(Environment& currentEnvironment, std::vector<Achievement>& currentPossibleAchievements);
        void printAchievement(int largestName);
        std::string saveGame();
};

#endif