/*
game.h
Game class contains everything needed for one saved game.
*/

#ifndef CLASS_GAME
#define CLASS_GAME

#include <vector>
#include <string>

class Command;
class Achievement;
#include "environmentClass.h"
#include "battleClass.h"

class Game {
    private:
        Environment currEnvironment{};
        Battle currBattle{};
        std::vector<Command> currCommands{};
        std::vector<Achievement> currAchievements{};
        bool inEnvironment{ false };
        bool firstCall{ true };
        int saveGameMoves{ 0 };
        int autoSave{ 0 };
        double timeLengths{ 1.0 };
    public:
        Game() {};
        Game(std::string playerName);
        void setEnvironment(Environment x) { this->currEnvironment = x; }
        void setBattle(Battle x) { this->currBattle = x; }
        void setCommands(std::vector<Command> x) { this->currCommands = x; }
        void setAchievements(std::vector<Achievement> x) { this->currAchievements = x; }
        void setInEnvironment(bool x) { this->inEnvironment = x; }
        void setInEnvironment(int x) { this->inEnvironment = x; }
        void setSaveGameMoves(int x) { this->saveGameMoves = x; }
        void setAutoSave(int x) { this->autoSave = x; }
        void setTimeLengths(double x) { this->timeLengths = x; }
        Environment getEnvironment() { return this->currEnvironment; }
        bool isInEnvironment() { return this->inEnvironment; }
        bool isFirstCall() { bool isIt = this->firstCall; this->firstCall = false; return isIt; }
        void initializeCommands();
        void initializeAchievements();
        void nextLevel();
        void enterEnvironment();
        bool timedEvents(double timeElapsed); // return true if enemy fight you
        void exitEnvironment();
        void enterBattle();
        void exitBattle();
        void playerRewards(int xp, int credits, int fouls);
        void checkIntersections();
        void upgradePlayer(int dimension);
        bool executeCommand(std::vector<std::string> inputVector); // return true if invalid command
        void takeAction(Command command, std::string argument);
        void iterationChecks();
        void addCommands(std::vector<std::string> commandNames);
        void addCommand(std::string commandName);
        void addCommand(Command command);
        void addAchievements(std::vector<std::string> achievementNames);
        void addAchievement(std::string achievementName);
        void checkAchievements();
        void nextMainStoryChapter(int storyChapter);
        void optionsMenu();
        void saveGame();
        void saveGame(std::string saveGameFolderName);
};

#endif