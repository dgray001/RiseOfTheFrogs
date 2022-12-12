/*
coreFunctions.h
Core functions necessary to run the game that don't fit into an existing class (at least at the
moment).
*/

#ifndef CORE_FUNCTIONS
#define CORE_FUNCTIONS

#include <string>
#include <vector>
#include <filesystem>

#include "constants.h"

class Command;
class Achievement;
class Battle;
class Environment;
class aiUnit;
class Game;

namespace core_functions {
    std::vector<std::string> parseString(std::string stringParsed, std::string delimiter);
    int randomInt(int min, int max);
    int randomInt(int max);
    double randomDouble(double min, double max);
    double randomDouble(double max);
    bool isPositiveInteger(std::string inputString);
    //bool isNumber(std::string inputString);
    bool angleLessThan(double vector1[3], double vector2[3], double inquiryCosAngle);
    double getStatMultiplier(int level, int minLevel, int maxLevel);
    bool sigmoidProbability(int baseHitProbability, int baseCenterProbability, double x);
    bool linearProbability(double x);
    int xpForNextLevel(int level);
    bool checkSpawn(double spawnProbability, double time, int spawnProbabilityTime = constants::baseSpawnProbabilityTime);
    void addUnits(std::vector<aiUnit>& unitList, std::vector<int> newUnits);
    void pauseProgram(double pauseTime);
    inline double timeLengths{ 1.0 }; // only non-constant variable
    void flushScreen();
    std::string stringMultiply(std::string inputString, int amount);
    void requireEnter();
    std::string getInputString(std::string message, bool confirm = true);
    double theta(double x, double y);
    double phi(double z);
    double thetaSubtract(double t1, double t2);
    int randomFromWeights(std::vector<int> weights);
    std::string toLower(std::string input);
    std::string toUpper(std::string input);
    void mainMenu(Game& currGame);
    void createNewGame(Game& currGame);
    void loadSavedGame(Game& currGame);
    void openSavedGame(Game& currGame, std::filesystem::path folderPath, bool evaluateTimedEvents = true);
    bool validFileName(std::string filename);
    std::string boolToString(bool b);
    std::string makeQuantityBar(int amount, int max, int barLength);
    std::string secondsToTimeString(double seconds, int numberLimit = -1);
}

#endif