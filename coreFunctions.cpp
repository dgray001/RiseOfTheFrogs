/*
coreFunctions.cpp
Core functions necessary to run the game that don't fit into an existing class (at least at the
moment).
*/

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <chrono>
#include <stack>

#include "coreFunctions.h"
#include "abilityClass.h"
#include "commandClass.h"
#include "battleClass.h"
#include "environmentClass.h"
#include "unitClass.h"
#include "achievementClass.h"
#include "game.h"

// my personal string parser
std::vector<std::string> core_functions::parseString(std::string stringParsed, std::string delimiter) {
    std::vector<std::string> returnVector;
    int position = 0;
    std::string token;
    while ((position = stringParsed.find(delimiter)) != std::string::npos) {
        token = stringParsed.substr(0, position);
        returnVector.push_back(token);
        stringParsed.erase(0, position + delimiter.length());
    }
    returnVector.push_back(stringParsed);
    return returnVector;
}

// returns a random integer from [min, max] or from [0, max]
int core_functions::randomInt(int min, int max) {
    int initial = core_functions::randomInt(abs(max - min));
    if (max > min) {
        initial += min;
    }
    else { // if user put numbers in wrong order
        initial += max;
    }
    return initial;
}
int core_functions::randomInt(int max) {
    double randomNumber{ static_cast<double>(std::rand() - 1) / RAND_MAX }; // [0, 1)
    return static_cast<int>(floor(randomNumber * (max + 1.0))); // max + 1 makes it [0, max + 1) then floor [0, max]
}

// returns a random double from [min, max] or from [0, max]
double core_functions::randomDouble(double min, double max) {
    double initial = core_functions::randomDouble(abs(max - min));
    if (max > min) {
        initial += min;
    }
    else { // if user put numbers in wrong order
        initial += max;
    }
    return initial;
}
double core_functions::randomDouble(double max) {
    double randomNumber{ static_cast<double>(std::rand() - 1) / RAND_MAX }; // [0, 1)
    return randomNumber * max; // [0, max)
}

// Returns true if the string evaluates to an integer >= 0
bool core_functions::isPositiveInteger(std::string inputString) {
    bool isInteger = true;

    if (inputString.empty()) {
        isInteger = false;
    }
    else {
        isInteger = (inputString.find_first_not_of("0123456789") == std::string::npos);
    }
    /* old way of doing it
    if (inputString.empty()) {
        isInteger = false;
    }
    else if (std::find_if(inputString.begin(), inputString.end(),
        [](unsigned char c) {return std::isdigit(c); }) == inputString.end()) {
        std::cout << "found!";
        isInteger = false;
    } */
    return isInteger;
}

// Returns boolean of whether the angle between the two vectors is less than the inquiry angle
// Note: the inquiry angle is inputted as the cos(angle) since that simplifies calculation
bool core_functions::angleLessThan(double vector1[3], double vector2[3], double inquiryCosAngle) {
    double vector1Mag = std::sqrt(vector1[0] * vector1[0] + vector1[1] * vector1[1] + vector1[2] * vector1[2]);
    double vector2Mag = std::sqrt(vector2[0] * vector2[0] + vector2[1] * vector2[1] + vector2[2] * vector2[2]);
    double dotProduct = (vector1[0] * vector2[0] + vector1[1] * vector2[1] + vector1[2] * vector2[2])
        / (vector1Mag * vector2Mag);
    if (dotProduct > inquiryCosAngle) {
        return true;
    }
    else {
        return false;
    }
}

// Gives stat multiplier based on level (which is typically generated randomly)
double core_functions::getStatMultiplier(int level, int minLevel, int maxLevel) {
    double lM{};
    if (minLevel == maxLevel) {
        lM = 1;
    }
    else { // stats can be up to 130% of base stats
        lM = (1 + constants::aiStatMultiplierMax * static_cast<double>(level - minLevel) / static_cast<double>(maxLevel - minLevel));
    }
    return lM;
}

// Calculates probability and returns random result based on sigmoid curve
bool core_functions::sigmoidProbability(int baseHitProbability, int baseCenterProbability, double x) {
    bool result = false;
    if (baseHitProbability > 50) {
    }
    else if (baseHitProbability == 50) {
        std::cout << "WARNING: Base hit probability of 50 will give 50% chance no matter what.";
    }
    else if (baseHitProbability < 50) {
        x *= -1;
    }
    double sigmoidConstant = -log(100.0 / baseHitProbability - 1) / baseCenterProbability;
    double randomNumber{ static_cast<double>(std::rand()) / RAND_MAX }; // [0, 1]
    double hitProbability{ 1 / (1 + exp(sigmoidConstant * (x - baseCenterProbability))) };
    if (hitProbability >= randomNumber) {
        result = true;
    }
    return result;
}

// Calculates probability and returns random result based on liner curve
bool core_functions::linearProbability(double x) {
    bool result = false;
    double randomNumber{ static_cast<double>(std::rand()) / RAND_MAX }; // [0, 1]
    if (x >= randomNumber) {
        result = true;
    }
    return result;
}

// Reference function to calculate xp for next level (input current level)
int core_functions::xpForNextLevel(int level) {
    // see Excel for coefficients and curves
    return static_cast<int>(std::ceil(constants::xpLevelCoefficient *
        std::pow(constants::xpLevelDimension, (level) / constants::dimensionLevels) *
        std::pow(constants::xpLevelIntersection, (level + 1) / constants::intersectionLevels) *
        std::pow(level + 1, constants::xpLevelLevel)));
}

// Function returning whether a spawn will occur based on the spawn probability and time
bool core_functions::checkSpawn(double spawnProbability, double time, int spawnProbabilityTime) {
    // spawnProbabilityTime is the reference time the spawn probabilities are based on
    double spawnProb = 1 - std::pow(1.0 - spawnProbability, time / static_cast<double>(spawnProbabilityTime));
    //std::cout << spawnProb << "\n";
    return core_functions::linearProbability(spawnProb);
}

// Initializes and adds units (by ID) to the inputted unit vector
void core_functions::addUnits(std::vector<aiUnit>& unitList, std::vector<int> newUnits) {
    for (size_t i = 0; i < newUnits.size(); i++) {
        unitList.push_back(aiUnit(newUnits.at(i)));
    }
}

// Pauses the program for the specified amount of time
void core_functions::pauseProgram(double pauseTime) {
    pauseTime *= core_functions::timeLengths;
    std::chrono::steady_clock::time_point startTime{ std::chrono::steady_clock::now() };
    while (true) {
        std::chrono::duration<double> elapsedTime = std::chrono::steady_clock::now() - startTime;
        if (elapsedTime.count() > pauseTime) {
            break;
        }
    }
}

// Flush the screen
void core_functions::flushScreen() {
    for (size_t i = 0; i < constants::screenFlushLines; i++) {
        std::cout << "\n";
    }
}

// Concatenate string to itself arbitrary number of times
std::string core_functions::stringMultiply(std::string inputString, int amount) {
    std::string outputString{ "" };
    for (int i = 0; i < amount; i++) {
        outputString += inputString;
    }
    return outputString;
}

// Require player to press enter
void core_functions::requireEnter() {
    std::cout << "Press enter to continue...";
    std::cin.ignore(INT_MAX, '\n');
}

// Get and confirm an input string
std::string core_functions::getInputString(std::string message, bool confirm) {
    std::string inputString{};
    std::cout << message;
    if (confirm) {
        do {
            std::getline(std::cin >> std::ws, inputString); // receive input
            std::cout << "Confirm: " << inputString << "\nby typing 'yes'\n";
            std::string answer{};
            std::getline(std::cin >> std::ws, answer);
            if (answer.compare("yes") == 0) {
                std::cout << "Confirmed.\n\n";
                break;
            }
            else {
                std::cout << "Not confirmed.\n" << message;
            }
        } while (true);
    }
    else {
        std::getline(std::cin >> std::ws, inputString); // receive input
    }
    return inputString;
}

// Return spherical coordinates of (unit) vector
double core_functions::theta(double x, double y) {
    double returnValue{};
    if (x == 0) {
        if (y > 0) { // facing toward y
            returnValue = constants::Pi / 2.0;
        }
        else if (y < 0) { // facing toward - y
            returnValue = 3 * constants::Pi / 2.0;
        }
        else { // facing either straight up or straight down (don't change last theta value)
        }
    }
    else {
        returnValue = std::atan(y / x);
        if ((x > 0) && (y < 0)) { // fourth quadrant
            returnValue += 2 * constants::Pi;
        }
        else if (((x < 0) && (y >= 0)) || // second quadrant
            ((x < 0) && (y <= 0))) { // third quadrant
            returnValue += constants::Pi;
        }
    }
    if ((returnValue < 0) || (returnValue > 2 * constants::Pi)) {
        std::cout << "ERROR: theta value " << returnValue << " out of range.\n";
    }
    return returnValue;
}
double core_functions::phi(double z) {
    return std::acos(z);
}
double core_functions::thetaSubtract(double t1, double t2) { // return t1 - t2 from t1 perspective
    double dif = t1 - t2;
    if (std::abs(dif) > constants::Pi) {
        dif -= constants::Pi * dif / std::abs(dif);
    }
    return dif;
}

// Return index given vector of weights
int core_functions::randomFromWeights(std::vector<int> weights) {
    int returnIndex{};
    int weightSum{};
    for (int i : weights) {
        weightSum += i;
    }
    int randomInt = core_functions::randomInt(weightSum - 1);
    for (size_t i = 0; i < weights.size(); i++) {
        if (randomInt < weights.at(i)) {
            returnIndex = i;
            break;
        }
        randomInt -= weights.at(i);
    }
    return returnIndex;
}

// Convert string to all lower or upper case
std::string core_functions::toLower(std::string input) {
    for (int i = 0; i < input.size(); i++) {
        input[i] = std::tolower(input[i]);
    }
    return input;
}
std::string core_functions::toUpper(std::string input) {
    for (int i = 0; i < input.size(); i++) {
        input[i] = std::toupper(input[i]);
    }
    return input;
}

// Main menu, etc.
void core_functions::mainMenu(Game& currGame) {
    std::cout << "  +++++++++++++++++++++++++++++++++++++++\n";
    std::cout << "  ++++++++++ Rise of the Frogs ++++++++++\n";
    std::cout << "  +++++++++++++++++++++++++++++++++++++++\n\n\n";
    if (std::filesystem::create_directory(constants::savedGameFolderName)) {
        core_functions::createNewGame(currGame);
        core_functions::pauseProgram(constants::shortPauseTime);
    }
    else {
        core_functions::loadSavedGame(currGame);
    }
}
void core_functions::createNewGame(Game& currGame) {
    while (true) {
        std::string name{ core_functions::getInputString("Enter your character name: ") };
        if (name.compare("exit") == 0) {
            exit(0);
        }
        else if (name.compare("load") == 0) {
            loadSavedGame(currGame);
            break;
        }
        bool alreadyExists{ false };
        for (std::filesystem::path savedGame : std::filesystem::directory_iterator(constants::savedGameFolderName)) {
            if (savedGame.filename().u8string().compare(name) == 0) {
                std::cout << "\nThat character name already exists.\n"
                    "You can load it with \"load\"\n\n";
                core_functions::pauseProgram(constants::shortPauseTime);
                alreadyExists = true;
                break;
            }
        }
        if (alreadyExists) {
            continue;
        }
        else if (core_functions::validFileName(name)) {
            if (std::filesystem::create_directory(static_cast<std::string>(constants::savedGameFolderName) + "/" + name)) {
                std::cout << "Creating new game ... \n";
                core_functions::pauseProgram(constants::shortPauseTime);
                currGame = Game(name);
                currGame.saveGame();
            }
            else {
                std::cout << "ERROR: Could not create saved game folder.\n";
                core_functions::requireEnter();
                core_functions::flushScreen();
                core_functions::mainMenu(currGame);
            }
            break;
        }
        else {
            std::cout << "That name is invalid; please choose another name.\n\n";
        core_functions::pauseProgram(constants::shortPauseTime);
            continue;
        }
    }
}
void core_functions::loadSavedGame(Game& currGame) {
    std::cout << "Enter an integer for your saved game or \"new\" to start a new game\n\n";
    std::vector<std::filesystem::path> savedGameFiles{};
    for (std::filesystem::path savedGame : std::filesystem::directory_iterator(constants::savedGameFolderName)) {
        savedGameFiles.push_back(savedGame);
        std::cout << "   " << savedGameFiles.size() << ": " << savedGame.filename().u8string() << std::endl;
    }
    if (savedGameFiles.size() == 0) {
        std::cout << "No saved games to load; create a new game.\n\n";
        core_functions::pauseProgram(constants::shortPauseTime);
        createNewGame(currGame);
    }
    else {
        while (true) {
            std::string input{ core_functions::getInputString("\n", false)};
            // Check integrity of save game / open game functions
            if (constants::TESTMODE) {
                std::vector<std::string> parsedInput{ core_functions::parseString(input, " ") };
                if (parsedInput.at(0).compare("check") == 0) {
                    if (parsedInput.size() < 2) {
                        continue;
                    }
                    if (!core_functions::isPositiveInteger(parsedInput.at(1))) {
                        std::cout << "Invalid argument\n";
                        continue;
                    }
                    if ((stoul(parsedInput.at(1)) <= 0) || (stoul(parsedInput.at(1)) > savedGameFiles.size())) {
                        std::cout << "Invalid argument\n";
                        continue;
                    }
                    core_functions::openSavedGame(currGame, savedGameFiles.at(stoul(parsedInput.at(1)) - 1), false); // open from saved game
                    if (!std::filesystem::create_directory(static_cast<std::string>(constants::savedGameFolderName) + "/DUPLICATE_" + currGame.getEnvironment().getPlayer().getName())) { // create directory
                        std::cout << "Could not create directory for duplicates\n";
                        continue;
                    }
                    std::cout << "Checking integrity of " << currGame.getEnvironment().getPlayer().getName() << " files.\n\n";
                    currGame.saveGame(static_cast<std::string>(constants::savedGameFolderName) + "/DUPLICATE_" + currGame.getEnvironment().getPlayer().getName() + "/"); // copy everything
                    // create pairs of files
                    std::vector<std::pair<std::filesystem::path, std::filesystem::path>> duplicateFiles{};
                    for (std::filesystem::path file1 : std::filesystem::directory_iterator(savedGameFiles.at(stoul(parsedInput.at(1)) - 1))) {
                        std::filesystem::path file2{ static_cast<std::string>(constants::savedGameFolderName) + "/DUPLICATE_" + savedGameFiles.at(stoul(parsedInput.at(1)) - 1).filename().u8string() + "/" + file1.filename().u8string() };
                        duplicateFiles.push_back(std::pair<std::filesystem::path, std::filesystem::path>{file1, file2});
                    }
                    bool noErrors{ true };
                    // Now check each file pair
                    for (std::pair<std::filesystem::path, std::filesystem::path> currFile : duplicateFiles) {
                        std::cout << "\nChecking " << currFile.first.filename().u8string() << "\n";
                        std::ifstream file1{ currFile.first };
                        std::ifstream file2{ currFile.second };
                        int i{ 1 }; // line number
                        int errorCount{ 0 };
                        while (true) {
                            std::string line1{};
                            std::string line2{};
                            // First check EOF
                            if (std::getline(file1, line1).fail() != std::getline(file2, line2).fail()) {
                                std::cout << "  -ERROR line " << i << ": ";
                                noErrors = false;
                                if (file1.fail()) {
                                    std::cout << currFile.first.filename().u8string() << " ended first.\n";
                                }
                                else {
                                    std::cout << currFile.second.filename().u8string() << " ended first.\n";
                                }
                                break;
                            }
                            if (file1.fail() && file2.fail()) {
                                break;
                            }
                            if (line1.compare(line2) != 0) {
                                std::cout << "  -ERROR line " << i << ": lines not equal:\n";
                                std::cout << "    -original:  " << line1 << "\n";
                                std::cout << "    -duplicate: " << line2 << "\n";
                                noErrors = false;
                                errorCount++;
                                if (errorCount >= 5) {
                                    break;
                                }
                            }
                            i++;
                        }
                        file1.close();
                        file2.close();
                    }
                    // Delete the duplicate saved game folder made
                    if (noErrors) {
                        std::filesystem::remove_all(static_cast<std::string>(constants::savedGameFolderName) + "/DUPLICATE_" + currGame.getEnvironment().getPlayer().getName());
                        std::cout << "Check passed! Duplicate files deleted.\n";
                    }
                    else {
                        std::cout << "\nDuplicate files left for analysis.\n";
                    }
                    continue;
                }
            }
            // Normal commands
            if (input.compare("exit") == 0) {
                exit(0);
            }
            else if (input.compare("new") == 0) {
                createNewGame(currGame);
                break;
            }
            else if (input.compare("help") == 0) {
                std::cout << "Use \"exit\" to exit, \"new\" to create a new game, \"#\" to load a "
                    "saved game (where # is the integer corresponding to the game to load), "
                    "\"credits\" to display the credits, and \"help\" to display this help\n";
                continue;
            }
            else if (input.compare("credits") == 0) {
                std::cout << constants::credits;
                continue;
            }
            else if (!core_functions::isPositiveInteger(input)) {
                std::cout << "Invalid input. Use \"help\" for help.\n\n";
                continue;
            }
            else if ((stoul(input) <= 0) || (stoul(input) > savedGameFiles.size())) {
                std::cout << "Invalid input. Use \"help\" for help.\n\n";
                continue;
            }
            else {
                std::cout << "\nOpening " << savedGameFiles.at(stoul(input) - 1).filename().u8string() << "\n";
                core_functions::openSavedGame(currGame, savedGameFiles.at(stoul(input) - 1));
                currGame.saveGame();
                core_functions::flushScreen();
                currGame.takeAction(Command("commands"), "");
                break;
            }
        }
    }
}
void core_functions::openSavedGame(Game& currGame, std::filesystem::path folderPath, bool evaluateTimedEvents) {
    // First open gamefile
    currGame = Game();
    int value_int{};
    bool startedFile{ false };
    double timeElapsed{}; // time elapsed (in s) since this file was saved
    std::ifstream gameFile{ folderPath.u8string() + "/game.frog" };
    int i{ 0 }; // line number
    for (std::string line{}; std::getline(gameFile, line); i++) {
        // Check for empty string
        if (line.compare("") == 0) {
            continue;
        }
        // Check if started file yet
        if (!startedFile) {
            if (line.compare("*STARTFILE") == 0) {
                startedFile = true;
            }
            continue;
        }
        // parse input
        std::vector<std::string> j{ core_functions::parseString(line, "=") };
        if (j.size() < 2) { // for gamefile there's no more * words beyond *STARTFILE
            continue;
        }
        if (j.at(0).compare("inEnvironment") == 0) {
            try {
                int arg{ std::stoi(j.at(1)) };
                currGame.setInEnvironment(arg);
            }
            catch (...) {
                std::cout << "WARNING: inEnvironment variable threw exception in game.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("autoSave") == 0) {
            try {
                int arg{ std::stoi(j.at(1)) };
                currGame.setAutoSave(arg);
            }
            catch (...) {
                std::cout << "WARNING: autoSave variable threw exception in game.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("timeLengths") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currGame.setTimeLengths(arg);
            }
            catch (...) {
                std::cout << "WARNING: timeLengths variable threw exception in game.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("epochTime") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                std::chrono::duration<double> currTime{ std::chrono::steady_clock::now().time_since_epoch() };
                timeElapsed = currTime.count() - arg;
            }
            catch (...) {
                std::cout << "WARNING: epochTime variable threw exception in game.frog (line " << i << ")\n";
            }
            continue;
        }
    }
    gameFile.close();

    // declare some variables
    int currInt{};
    double currDouble{};
    std::string* currString{ nullptr };
    Item* currItem{ nullptr };
    Player* currPlayer{ nullptr };
    aiUnit* currAIUnit{ nullptr };
    Quest* currQuest{ nullptr };
    Ability* currAbility{ nullptr };
    Achievement* currAchievement{ nullptr };
    Command* currCommand{ nullptr };
    Area* currArea{ nullptr };
    std::unordered_map<int, aiUnit>* otherUnits{ nullptr };
    std::unordered_map<int, Item>* droppedItems{ nullptr };
    std::unordered_map<int, int>* questMap{ nullptr };
    std::vector<int>* intVector{ nullptr };
    std::vector<Quest>* questVector{ nullptr };
    std::vector<Area>* areaVector{ nullptr };
    std::vector<Ability>* abilityVector{ nullptr };
    std::vector<Item>* itemVector{ nullptr };
    std::vector<std::pair<int, int>>* pairVector{ nullptr };
    // Environment file
    Environment* currEnvironment = new Environment;
    std::ifstream environmentFile{ folderPath.u8string() + "/environment.frog" };
    i = 1;
    for (std::string line{}; std::getline(environmentFile, line); i++) {
        // Check for empty string
        if (line.compare("") == 0) {
            continue;
        }
        // Check if started file yet
        if (!startedFile) {
            if (line.compare("*STARTFILE") == 0) {
                startedFile = true;
            }
            continue;
        }
        // Check if ending something
        if (line.compare("*END") == 0) {
            if (currPlayer != nullptr) {
                if (currString != nullptr) { // name or other strings
                    currString = nullptr;
                    continue;
                }
                else if (itemVector != nullptr) { // player items
                    if (currItem != nullptr) { // inventory
                        if (intVector != nullptr) {
                            currItem->setMaterials(*intVector);
                            intVector = nullptr;
                            continue;
                        }
                        itemVector->push_back(*currItem);
                        currItem = nullptr;
                        continue;
                    }
                    currPlayer->setInventory(*itemVector);
                    itemVector = nullptr;
                    continue;
                }
                else if (currItem != nullptr) { // equipped items
                    if (intVector != nullptr) {
                        currItem->setMaterials(*intVector);
                        intVector = nullptr;
                        continue;
                    }
                    switch (currInt) {
                        case 1:
                            currPlayer->setWeapon(*currItem);
                            break;
                        case 2:
                            currPlayer->setOffhand(*currItem);
                            break;
                        case 3:
                            currPlayer->setTwohand(*currItem);
                            break;
                        case 4:
                            currPlayer->setHeadgear(*currItem);
                            break;
                        case 5:
                            currPlayer->setChestgear(*currItem);
                            break;
                        case 6:
                            currPlayer->setLeggear(*currItem);
                            break;
                        case 7:
                            currPlayer->setFootgear(*currItem);
                            break;
                        case 8:
                            currPlayer->setAccessory1(*currItem);
                            break;
                        case 9:
                            currPlayer->setAccessory2(*currItem);
                            break;
                        case 10:
                            currPlayer->setAccessory3(*currItem);
                            break;
                        case 11:
                            currPlayer->setAccessory4(*currItem);
                            break;
                        default:
                            std::cout << "WARNING: Equipped item has improper currInt at END at line " << i << ".\n";
                            break;
                    }
                    currItem = nullptr;
                    continue;
                }
                else if (intVector != nullptr) { // upgrade vector
                    currPlayer->setUpgradesActivated(*intVector);
                    intVector = nullptr;
                    continue;
                }
                else if (abilityVector != nullptr) {
                    if (currAbility != nullptr) {
                        abilityVector->push_back(Ability(currAbility->getName()));
                        currAbility = nullptr;
                        continue;
                    }
                    currPlayer->setBattleAbilities(*abilityVector);
                    abilityVector = nullptr;
                    continue;
                }
                currEnvironment->setPlayer(*currPlayer);
                currPlayer = nullptr;
                continue;
            }
            else if (questMap != nullptr) {
                switch (currInt) {
                    case 1:
                        currEnvironment->setTotalUnitsSeen(*questMap);
                        break;
                    case 2:
                        currEnvironment->setTotalItemsSeen(*questMap);
                        break;
                    case 3:
                        currEnvironment->setTotalUnitsKilled(*questMap);
                        break;
                    case 4:
                        currEnvironment->setTotalItemsConsumed(*questMap);
                        break;
                    default:
                        std::cout << "WARNING: No valid currInt for questMap END on line " << i << ".\n";
                        break;
                }
                questMap = nullptr;
                continue;
            }
            else if (droppedItems != nullptr) {
                if (currItem != nullptr) { // environment items
                    if (currString != nullptr) {
                        currString = nullptr;
                        continue;
                    }
                    else if (intVector != nullptr) {
                        currItem->setMaterials(*intVector);
                        intVector = nullptr;
                        continue;
                    }
                    droppedItems->emplace(currInt, *currItem);
                    currItem = nullptr;
                    continue;
                }
                currEnvironment->setDroppedItems(*droppedItems);
                droppedItems = nullptr;
                continue;
            }
            else if (otherUnits != nullptr) {
                if (currAIUnit != nullptr) {
                    if (currString != nullptr) {
                        currString = nullptr;
                        continue;
                    }
                    else if (abilityVector != nullptr) {
                        if (currAbility != nullptr) {
                            abilityVector->push_back(Ability(currAbility->getName())); // construct new ability
                            delete currAbility;
                            currAbility = nullptr;
                            continue;
                        }
                        currAIUnit->setBattleAbilities(*abilityVector);
                        abilityVector = nullptr;
                        continue;
                    }
                    else if (pairVector != nullptr) {
                        currAIUnit->setDrops(*pairVector);
                        pairVector = nullptr;
                        continue;
                    }
                    otherUnits->emplace(currInt, *currAIUnit);
                    currAIUnit = nullptr;
                    continue;
                }
                currEnvironment->setOtherUnits(*otherUnits);
                otherUnits = nullptr;
                continue;
            }
            else if (areaVector != nullptr) {
                if (currArea != nullptr) {
                    if (intVector != nullptr) {
                        currArea->setUnitKeys(*intVector);
                        intVector = nullptr;
                        continue;
                    }
                    areaVector->push_back(*currArea);
                    currArea = nullptr;
                    continue;
                }
                currEnvironment->setEnvironmentAreas(*areaVector);
                areaVector = nullptr;
                continue;
            }
            else if (intVector != nullptr) {
                if (currInt == 1) {
                    currEnvironment->setUnitsSeen(*intVector);
                }
                else if (currInt == 2) {
                    currEnvironment->setItemsSeen(*intVector);
                }
                else {
                    std::cout << "WARNING: intVector has no valid currInt value at END on line " << i << ".\n";
                }
                intVector = nullptr;
                continue;
            }
            else if (questVector != nullptr) {
                if (currQuest != nullptr) {
                    questVector->push_back(Quest(currInt)); // construct new quest
                    delete currQuest;
                    currQuest = nullptr;
                    continue;
                }
                currEnvironment->setEnvironmentQuests(*questVector);
                questVector = nullptr;
                continue;
            }
            else if (currString != nullptr) {
                currString = nullptr;
                continue;
            }
            continue;
        }
        // Parse input if no *END
        std::vector<std::string> j{ core_functions::parseString(line, "=") };
        // Check for active pointers
        if (currString != nullptr) {
            *currString += line;
            continue;
        }
        else if (abilityVector != nullptr) {
            if (currAbility != nullptr) {
                if (line.compare("*STRING=name") == 0) {
                    currString = &(currAbility->getNameAddress());
                    continue;
                }
                continue;
            }
            if (line.compare("*DEFINE=Ability") == 0) {
                currAbility = new Ability();
                continue;
            }
            continue;
        }
        else if (questMap != nullptr) {
            if (j.at(0).compare("*KEY") == 0) {
                try {
                    int arg1{ std::stoi(j.at(1)) };
                    int arg2{ std::stoi(j.at(2)) };
                    questMap->emplace(arg1, arg2);
                }
                catch (...) {
                    std::cout << "WARNING: a questMap variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            continue;
        }
        else if (currItem != nullptr) { // items
            if (intVector != nullptr) {
                try {
                    int arg{ std::stoi(j.at(0)) };
                    intVector->push_back(arg);
                }
                catch (...) {
                    std::cout << "WARNING: materials variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            if (line.compare("*STRING=name") == 0) {
                currString = &(currItem->getNameAddress());
                continue;
            }
            else if (j.at(0).compare("itemID") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem = new Item(arg);
                    currItem->setName("");
                }
                catch (...) {
                    std::cout << "WARNING: itemID variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("thisItemType") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setItemType(arg);
                }
                catch (...) {
                    std::cout << "WARNING: thisItemType variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("thisItemQuality") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setItemQuality(arg);
                }
                catch (...) {
                    std::cout << "WARNING: thisItemQuality variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("thisItemColor") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setItemColor(arg);
                }
                catch (...) {
                    std::cout << "WARNING: thisItemColor variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("itemDimension") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setDimension(arg);
                }
                catch (...) {
                    std::cout << "WARNING: itemDimension variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("itemLevel") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setLevel(arg);
                }
                catch (...) {
                    std::cout << "WARNING: itemLevel variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("baseWorth") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setBaseWorth(arg);
                }
                catch (...) {
                    std::cout << "WARNING: baseWorth variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (line.compare("*VECTOR=materials") == 0) {
                intVector = new std::vector<int>{};
                continue;
            }
            else if (j.at(0).compare("currEnergy") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setCurrEnergy(arg);
                }
                catch (...) {
                    std::cout << "WARNING: currEnergy variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("currHealth") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setCurrHealth(arg);
                }
                catch (...) {
                    std::cout << "WARNING: currHealth variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("currMana") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setCurrMana(arg);
                }
                catch (...) {
                    std::cout << "WARNING: currMana variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("experience") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setExperience(arg);
                }
                catch (...) {
                    std::cout << "WARNING: experience variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("credits") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setCredits(arg);
                }
                catch (...) {
                    std::cout << "WARNING: credits variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("fouls") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setFouls(arg);
                }
                catch (...) {
                    std::cout << "WARNING: fouls variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("stack") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setStack(arg);
                }
                catch (...) {
                    std::cout << "WARNING: stack variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("maxHealth") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setMaxHealth(arg);
                }
                catch (...) {
                    std::cout << "WARNING: maxHealth variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("maxEnergy") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setMaxEnergy(arg);
                }
                catch (...) {
                    std::cout << "WARNING: maxEnergy variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("maxMana") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setMaxMana(arg);
                }
                catch (...) {
                    std::cout << "WARNING: maxMana variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("attack") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setAttack(arg);
                }
                catch (...) {
                    std::cout << "WARNING: attack variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("magic") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setMagic(arg);
                }
                catch (...) {
                    std::cout << "WARNING: magic variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("defense") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setDefense(arg);
                }
                catch (...) {
                    std::cout << "WARNING: defense variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("resist") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setResist(arg);
                }
                catch (...) {
                    std::cout << "WARNING: resist variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("piercing") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setPiercing(arg);
                }
                catch (...) {
                    std::cout << "WARNING: piercing variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("penetration") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setPenetration(arg);
                }
                catch (...) {
                    std::cout << "WARNING: penetration variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("dexterity") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setDexterity(arg);
                }
                catch (...) {
                    std::cout << "WARNING: dexterity variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("lifesteal") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currItem->setLifeSteal(arg);
                }
                catch (...) {
                    std::cout << "WARNING: lifesteal variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("viewDistance") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currItem->setViewDistance(arg);
                }
                catch (...) {
                    std::cout << "WARNING: viewDistance variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("moveSpeed") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currItem->setMoveSpeed(arg);
                }
                catch (...) {
                    std::cout << "WARNING: moveSpeed variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("monsterSpawn") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currItem->setMonsterSpawn(arg);
                }
                catch (...) {
                    std::cout << "WARNING: monsterSpawn variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("luckFactor") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currItem->setLuckFactor(arg);
                }
                catch (...) {
                    std::cout << "WARNING: luckFactor variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("xLocation") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currItem->setXLocation(arg);
                }
                catch (...) {
                    std::cout << "WARNING: xLocation variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("yLocation") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currItem->setYLocation(arg);
                }
                catch (...) {
                    std::cout << "WARNING: yLocation variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("zLocation") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currItem->setZLocation(arg);
                }
                catch (...) {
                    std::cout << "WARNING: zLocation variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("view_distance") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currItem->setView_Distance(arg);
                }
                catch (...) {
                    std::cout << "WARNING: view_distance variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("view_dot") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currItem->setView_Dot(arg);
                }
                catch (...) {
                    std::cout << "WARNING: view_dot variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("view_clock") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currItem->setView_Clock(arg);
                }
                catch (...) {
                    std::cout << "WARNING: view_clock variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            continue;
        }
        else if (currPlayer != nullptr) {
            if (j.at(0).compare("*ITEM") == 0) {
                if (itemVector != nullptr) {
                    currItem = new Item();
                    continue;
                }
                if (j.size() < 2) {
                    std::cout << "WARNING: No item defined on line " << i << ".\n";
                    continue;
                }
                if (j.at(1).compare("weapon") == 0) {
                    currItem = new Item();
                    currInt = 1;
                }
                else if (j.at(1).compare("offhand") == 0) {
                    currItem = new Item();
                    currInt = 2;
                }
                else if (j.at(1).compare("twohand") == 0) {
                    currItem = new Item();
                    currInt = 3;
                }
                else if (j.at(1).compare("headgear") == 0) {
                    currItem = new Item();
                    currInt = 4;
                }
                else if (j.at(1).compare("chestgear") == 0) {
                    currItem = new Item();
                    currInt = 5;
                }
                else if (j.at(1).compare("leggear") == 0) {
                    currItem = new Item();
                    currInt = 6;
                }
                else if (j.at(1).compare("footgear") == 0) {
                    currItem = new Item();
                    currInt = 7;
                }
                else if (j.at(1).compare("accessory1") == 0) {
                    currItem = new Item();
                    currInt = 8;
                }
                else if (j.at(1).compare("accessory2") == 0) {
                    currItem = new Item();
                    currInt = 9;
                }
                else if (j.at(1).compare("accessory3") == 0) {
                    currItem = new Item();
                    currInt = 10;
                }
                else if (j.at(1).compare("accessory4") == 0) {
                    currItem = new Item();
                    currInt = 11;
                }
                else {
                    std::cout << "WARNING: No item defined on line " << i << ".\n";
                }
                continue;
            }
            if (intVector != nullptr) {
                try {
                    int arg{ std::stoi(j.at(0)) };
                    intVector->push_back(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgradesActivated variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            // Start with Unit variables
            if (line.compare("*STRING=name") == 0) {
                currString = &(currPlayer->getNameAddress());
                continue;
            }
            else if (j.at(0).compare("baseHealth") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setBaseHealth(arg);
                }
                catch (...) {
                    std::cout << "WARNING: baseHealth variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("missingHealth") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setMissingHealth(arg);
                }
                catch (...) {
                    std::cout << "WARNING: missingHealth variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("baseAttack") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setBaseAttack(arg);
                }
                catch (...) {
                    std::cout << "WARNING: baseAttack variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("baseMagic") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setBaseMagic(arg);
                }
                catch (...) {
                    std::cout << "WARNING: baseMagic variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("baseDefense") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setBaseDefense(arg);
                }
                catch (...) {
                    std::cout << "WARNING: baseDefense variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("baseResist") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setBaseResist(arg);
                }
                catch (...) {
                    std::cout << "WARNING: baseResist variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("basePiercing") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setBasePiercing(arg);
                }
                catch (...) {
                    std::cout << "WARNING: basePiercing variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("basePenetration") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setBasePenetration(arg);
                }
                catch (...) {
                    std::cout << "WARNING: basePenetration variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("baseDexterity") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setBaseDexterity(arg);
                }
                catch (...) {
                    std::cout << "WARNING: baseDexterity variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("thisUnitColor") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setUnitColor(arg);
                }
                catch (...) {
                    std::cout << "WARNING: thisUnitColor variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("status_alive") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setStatusAlive(arg);
                }
                catch (...) {
                    std::cout << "WARNING: status_alive variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("xLocation") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setXLocation(arg);
                }
                catch (...) {
                    std::cout << "WARNING: xLocation variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("yLocation") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setYLocation(arg);
                }
                catch (...) {
                    std::cout << "WARNING: yLocation variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("zLocation") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setZLocation(arg);
                }
                catch (...) {
                    std::cout << "WARNING: zLocation variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("view_distance") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setView_Distance(arg);
                }
                catch (...) {
                    std::cout << "WARNING: view_distance variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("view_dot") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setView_Dot(arg);
                }
                catch (...) {
                    std::cout << "WARNING: view_dot variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("view_clock") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setView_Clock(arg);
                }
                catch (...) {
                    std::cout << "WARNING: view_clock variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("baseLifesteal") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setBaseLifesteal(arg);
                }
                catch (...) {
                    std::cout << "WARNING: baseLifesteal variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (line.compare("*VECTOR=battleAbilities") == 0) {
                abilityVector = new std::vector<Ability>;
                continue;
            }
            // Now for player-specific variables
            if (j.at(0).compare("monstersSlain") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setMonstersSlain(arg);
                }
                catch (...) {
                    std::cout << "WARNING: monstersSlain variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("distanceTraveled") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setDistanceTraveled(arg);
                }
                catch (...) {
                    std::cout << "WARNING: distanceTraveled variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("itemsConsumed") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setItemsConsumed(arg);
                }
                catch (...) {
                    std::cout << "WARNING: itemsConsumed variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("level") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setLevel(arg);
                }
                catch (...) {
                    std::cout << "WARNING: level variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("experience") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setExperience(arg);
                }
                catch (...) {
                    std::cout << "WARNING: experience variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("credits") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setCredits(arg);
                }
                catch (...) {
                    std::cout << "WARNING: credits variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("fouls") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setFouls(arg);
                }
                catch (...) {
                    std::cout << "WARNING: fouls variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("baseEnergy") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setBaseEnergy(arg);
                }
                catch (...) {
                    std::cout << "WARNING: baseEnergy variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("missingEnergy") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setMissingEnergy(arg);
                }
                catch (...) {
                    std::cout << "WARNING: missingEnergy variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("baseMana") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setBaseMana(arg);
                }
                catch (...) {
                    std::cout << "WARNING: baseMana variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("missingMana") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setMissingMana(arg);
                }
                catch (...) {
                    std::cout << "WARNING: missingMana variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("maxInventorySlots") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currPlayer->setMaxInventorySlots(arg);
                }
                catch (...) {
                    std::cout << "WARNING: maxInventorySlots variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("healthRegenerationSpeed") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setHealthRegenSpeed(arg);
                }
                catch (...) {
                    std::cout << "WARNING: healthRegenerationSpeed variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("energyRegenerationSpeed") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setEnergyRegenSpeed(arg);
                }
                catch (...) {
                    std::cout << "WARNING: energyRegenerationSpeed variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("manaRegenerationSpeed") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setManaRegenSpeed(arg);
                }
                catch (...) {
                    std::cout << "WARNING: manaRegenerationSpeed variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("xFacing") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setXFacing(arg);
                }
                catch (...) {
                    std::cout << "WARNING: xFacing variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("yFacing") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setYFacing(arg);
                }
                catch (...) {
                    std::cout << "WARNING: yFacing variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("zFacing") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setZFacing(arg);
                }
                catch (...) {
                    std::cout << "WARNING: zFacing variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("theta") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setTheta(arg);
                }
                catch (...) {
                    std::cout << "WARNING: theta variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("phi") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setPhi(arg);
                }
                catch (...) {
                    std::cout << "WARNING: phi variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("maxMoveDistance") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setMaxMoveDistance(arg);
                }
                catch (...) {
                    std::cout << "WARNING: maxMoveDistance variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("maxTurnAngle") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setMaxTurnAngle(arg);
                }
                catch (...) {
                    std::cout << "WARNING: maxTurnAngle variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("viewDistance") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setViewDistance(arg);
                }
                catch (...) {
                    std::cout << "WARNING: viewDistance variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("viewAngle") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setViewAngle(arg);
                }
                catch (...) {
                    std::cout << "WARNING: viewAngle variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("xVelocity") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setXVelocity(arg);
                }
                catch (...) {
                    std::cout << "WARNING: xVelocity variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("yVelocity") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setYVelocity(arg);
                }
                catch (...) {
                    std::cout << "WARNING: yVelocity variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("zVelocity") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setZVelocity(arg);
                }
                catch (...) {
                    std::cout << "WARNING: zVelocity variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("monsterSpawn") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setMonsterSpawn(arg);
                }
                catch (...) {
                    std::cout << "WARNING: monsterSpawn variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("luckFactor") == 0) {
                try {
                    double arg{ std::stod(j.at(1)) };
                    currPlayer->setLuckFactor(arg);
                }
                catch (...) {
                    std::cout << "WARNING: luckFactor variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (line.compare("*VECTOR=playerInventory") == 0) {
                itemVector = new std::vector<Item>();
                continue;
            }
            else if (line.compare("*VECTOR=upgradesActivated") == 0) {
                intVector = new std::vector<int>();
                continue;
            }
            if (j.at(0).compare("upgrade_forelegs") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeForelegs(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_forelegs variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_hindlegs") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeHindlegs(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_hindlegs variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_attention1") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeAttention1(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_attention1 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_quadrupedal1") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeQuadrupedal1(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_quadrupedal1 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_coordination1") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeCoordination1(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_coordination1 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_memory1") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeMemory1(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_memory1 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_quadrupedal2") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeQuadrupedal2(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_quadrupedal2 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_coordination2") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeCoordination2(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_coordination2 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_learning1") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeLearning1(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_learning1 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_attention2") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeAttention2(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_attention2 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_aggression1") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeAggression1(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_aggression1 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_protection1") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeProtection1(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_protection1 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_magic1") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeMagic1(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_magic1 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_ninja1") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeNinja1(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_ninja1 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_aggression2") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeAggression2(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_aggression2 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_protection2") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeProtection2(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_protection2 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_magic2") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeMagic2(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_magic2 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_ninja2") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeNinja2(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_ninja2 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_learning2") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeLearning2(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_learning2 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_memory2") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeMemory2(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_memory2 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_aggression3") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeAggression3(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_aggression3 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_protection3") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeProtection3(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_protection3 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_magic3") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeMagic3(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_magic3 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_ninja3") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setUpgradeNinja3(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_ninja3 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_equipWeapon") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setCanEquipWeapon(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_equipWeapon variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_equipOffhand") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setCanEquipOffhand(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_equipOffhand variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_equipTwohand") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setCanEquipTwohand(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_equipTwohand variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_equipHeadgear") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setCanEquipHeadgear(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_equipHeadgear variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_equipChestgear") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setCanEquipChestgear(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_equipChestgear variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_equipLeggear") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setCanEquipLeggear(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_equipLeggear variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_equipFootgear") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setCanEquipFootgear(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_equipFootgear variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_equipAccessory1") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setCanEquipAccessory1(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_equipAccessory1 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_equipAccessory2") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setCanEquipAccessory2(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_equipAccessory2 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_equipAccessory3") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setCanEquipAccessory3(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_equipAccessory3 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_equipAccessory4") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setCanEquipAccessory4(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_equipAccessory4 variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_itemsInBattle") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setItemsInBattle(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_itemsInBattle variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            else if (j.at(0).compare("upgrade_dismantleItems") == 0) {
                try {
                    bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                    currPlayer->setDismantleItems(arg);
                }
                catch (...) {
                    std::cout << "WARNING: upgrade_dismantleItems variable threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            continue;
        }
        else if (questVector != nullptr) {
            if (currQuest != nullptr) {
                if (j.at(0).compare("ID") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currInt = arg;
                    }
                    catch (...) {
                        std::cout << "WARNING: ID variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                continue;
            }
            if (line.compare("*DEFINE=Quest") == 0) {
                currQuest = new Quest();
                continue;
            }
            continue;
        }
        else if (droppedItems != nullptr) {
            if (line.compare("*DEFINE=Item") == 0) {
                currItem = new Item();
                continue;
            }
            else if (j.at(0).compare("*KEY") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currInt = arg;
                }
                catch (...) {
                    std::cout << "WARNING: item key threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            continue;
        }
        else if (otherUnits != nullptr) {
            if (currAIUnit != nullptr) {
                if (pairVector != nullptr) {
                    try {
                        j = core_functions::parseString(line, " ");
                        int arg1{ std::stoi(j.at(0)) };
                        int arg2{ std::stoi(j.at(1)) };
                        pairVector->push_back({ arg1, arg2 });
                    }
                    catch (...) {
                        std::cout << "WARNING: pairVector variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                // Start with Unit variables
                if (line.compare("*STRING=name") == 0) {
                    currString = &(currAIUnit->getNameAddress());
                    continue;
                }
                else if (j.at(0).compare("baseHealth") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setBaseHealth(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: baseHealth variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("missingHealth") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setMissingHealth(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: missingHealth variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("baseAttack") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setBaseAttack(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: baseAttack variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("baseMagic") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setBaseMagic(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: baseMagic variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("baseDefense") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setBaseDefense(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: baseDefense variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("baseResist") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setBaseResist(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: baseResist variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("basePiercing") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setBasePiercing(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: basePiercing variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("basePenetration") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setBasePenetration(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: basePenetration variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("baseDexterity") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setBaseDexterity(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: baseDexterity variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("thisUnitColor") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setUnitColor(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: thisUnitColor variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("status_alive") == 0) {
                    try {
                        bool arg{ static_cast<bool>(std::stoi(j.at(1))) };
                        currAIUnit->setStatusAlive(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: status_alive variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("xLocation") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currAIUnit->setXLocation(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: xLocation variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("yLocation") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currAIUnit->setYLocation(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: yLocation variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("zLocation") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currAIUnit->setZLocation(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: zLocation variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("view_distance") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currAIUnit->setView_Distance(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: view_distance variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("view_dot") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currAIUnit->setView_Dot(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: view_dot variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("view_clock") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setView_Clock(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: view_clock variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("baseLifesteal") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currAIUnit->setBaseLifesteal(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: baseLifesteal variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (line.compare("*VECTOR=battleAbilities") == 0) {
                    abilityVector = new std::vector<Ability>;
                    continue;
                }
                // Then move to aiUnit variables
                if (j.at(0).compare("unitID") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setUnitID(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: unitID variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("level") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setLevel(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: level variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("energyValue") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setEnergyValue(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: energyValue variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("maxHerd") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setMaxHerd(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: maxHerd variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("spaceTaken") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setSpaceTaken(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: spaceTaken variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("allyState") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currAIUnit->setAllyState(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: allyState variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("attackProbability") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currAIUnit->setAttackProbability(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: attackProbability variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("attackDistance") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currAIUnit->setAttackDistance(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: attackDistance variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("spawnProbability") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currAIUnit->setSpawnProbability(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: spawnProbability variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (line.compare("*VECTOR=unitDrops") == 0) {
                    pairVector = new std::vector<std::pair<int, int>>();
                    continue;
                }
                else if (j.at(0).compare("coolDown") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currAIUnit->setCoolDown(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: coolDown variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                continue;
            }
            if (line.compare("*DEFINE=aiUnit") == 0) {
                currAIUnit = new aiUnit(0);
                continue;
            }
            else if (j.at(0).compare("*KEY") == 0) {
                try {
                    int arg{ std::stoi(j.at(1)) };
                    currInt = arg;
                }
                catch (...) {
                    std::cout << "WARNING: aiUnit key  threw exception in environment.frog (line " << i << ")\n";
                }
                continue;
            }
            continue;
        }
        else if (areaVector != nullptr) {
            if (currArea != nullptr) {
                if (intVector != nullptr) {
                    try {
                        int arg{ std::stoi(line) };
                        intVector->push_back(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: intVector variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                if (j.at(0).compare("areaType") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currArea->setID(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: areaType variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("x1") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currArea->setX1(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: x1 variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("y1") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currArea->setY1(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: y1 variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("z1") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currArea->setZ1(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: z1 variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("x2") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currArea->setX2(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: x2 variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("y2") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currArea->setY2(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: y2 variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("z2") == 0) {
                    try {
                        double arg{ std::stod(j.at(1)) };
                        currArea->setZ2(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: z2 variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (j.at(0).compare("maxSpace") == 0) {
                    try {
                        int arg{ std::stoi(j.at(1)) };
                        currArea->setMaxSpace(arg);
                    }
                    catch (...) {
                        std::cout << "WARNING: maxSpace variable threw exception in environment.frog (line " << i << ")\n";
                    }
                    continue;
                }
                else if (line.compare("*VECTOR=unitKeys") == 0) {
                    intVector = new std::vector<int>{};
                    continue;
                }
            }
            if (line.compare("*DEFINE=Area") == 0) {
                currArea = new Area();
                continue;
            }
            continue;
        }
        // now for if the pointers are all null
        if (j.size() < 2) { // invalid input or blank line
            continue;
        }
        // First check other * keywords to define next object
        if (j.at(0).compare("*STRING") == 0) {
            if (j.at(1).compare("name") == 0) {
                currString = &(currEnvironment->getNameAddress());
            }
            else {
                std::cout << "WARNING: No string defined on line " << i << ".\n";
            }
            continue;
        }
        else if (j.at(0).compare("*VECTOR") == 0) {
            if (j.at(1).compare("environmentAreas") == 0) {
                areaVector = new std::vector<Area>();
            }
            else if (j.at(1).compare("unitsSeen") == 0) {
                intVector = new std::vector<int>();
                currInt = 1;
            }
            else if (j.at(1).compare("itemsSeen") == 0) {
                intVector = new std::vector<int>();
                currInt = 2;
            }
            else if (j.at(1).compare("environmentQuests") == 0) {
                questVector = new std::vector<Quest>();
            }
            else {
                std::cout << "WARNING: No vector defined on line " << i << ".\n";
            }
            continue;
        }
        else if (j.at(0).compare("*MAP") == 0) {
            if (j.at(1).compare("otherUnits") == 0) {
                otherUnits = new std::unordered_map<int, aiUnit>();
            }
            else if (j.at(1).compare("droppedItems") == 0) {
                droppedItems = new std::unordered_map<int, Item>();
            }
            else if (j.at(1).compare("totalUnitsSeen") == 0) {
                questMap = new std::unordered_map<int, int>();
                currInt = 1;
            }
            else if (j.at(1).compare("totalItemsSeen") == 0) {
                questMap = new std::unordered_map<int, int>();
                currInt = 2;
            }
            else if (j.at(1).compare("totalUnitsKilled") == 0) {
                questMap = new std::unordered_map<int, int>();
                currInt = 3;
            }
            else if (j.at(1).compare("totalItemsConsumed") == 0) {
                questMap = new std::unordered_map<int, int>();
                currInt = 4;
            }
            else {
                std::cout << "WARNING: No map defined on line " << i << ".\n";
            }
            continue;
        }
        else if (j.at(0).compare("*DEFINE") == 0) {
            if (j.at(1).compare("Player") == 0) {
                currPlayer = new Player();
            }
            else {
                std::cout << "WARNING: Nothing defined on line " << i << ".\n";
            }
            continue;
        }
        // Then check primitive types
        if (j.at(0).compare("playerIntersectionBuffer") == 0) {
            try {
                int arg{ std::stoi(j.at(1)) };
                currEnvironment->setPlayerIntersectionBuffer(arg);
            }
            catch (...) {
                std::cout << "WARNING: playerIntersectionBuffer variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("unitKey") == 0) {
            try {
                int arg{ std::stoi(j.at(1)) };
                currEnvironment->setUnitKey(arg);
            }
            catch (...) {
                std::cout << "WARNING: unitKey variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("currKey") == 0) {
            try {
                int arg{ std::stoi(j.at(1)) };
                currEnvironment->setCurrKey(arg);
            }
            catch (...) {
                std::cout << "WARNING: currKey variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("itemKey") == 0) {
            try {
                int arg{ std::stoi(j.at(1)) };
                currEnvironment->setItemKey(arg);
            }
            catch (...) {
                std::cout << "WARNING: itemKey variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("currArea") == 0) {
            try {
                int arg{ std::stoi(j.at(1)) };
                currEnvironment->setCurrArea(arg);
            }
            catch (...) {
                std::cout << "WARNING: currArea variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("xLimit") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setXLimit(arg);
            }
            catch (...) {
                std::cout << "WARNING: xLimit variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("yLimit") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setYLimit(arg);
            }
            catch (...) {
                std::cout << "WARNING: yLimit variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("zLimit") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setZLimit(arg);
            }
            catch (...) {
                std::cout << "WARNING: zLimit variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("intersectionPoint0") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setIntersectionPoint0(arg);
            }
            catch (...) {
                std::cout << "WARNING: intersectionPoint0 variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("intersectionPoint1") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setIntersectionPoint1(arg);
            }
            catch (...) {
                std::cout << "WARNING: intersectionPoint1 variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("intersectionPoint2") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setIntersectionPoint2(arg);
            }
            catch (...) {
                std::cout << "WARNING: intersectionPoint2 variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("intersectionPoint3") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setIntersectionPoint3(arg);
            }
            catch (...) {
                std::cout << "WARNING: intersectionPoint3 variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("intersectionPoint4") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setIntersectionPoint4(arg);
            }
            catch (...) {
                std::cout << "WARNING: intersectionPoint4 variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("xpBonusLength") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setXPBonusLength(arg);
            }
            catch (...) {
                std::cout << "WARNING: xpBonusLength variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("creditBonusLength") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setCreditBonusLength(arg);
            }
            catch (...) {
                std::cout << "WARNING: creditBonusLength variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("foulBonusLength") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setFoulBonusLength(arg);
            }
            catch (...) {
                std::cout << "WARNING: foulBonusLength variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("luckBonusLength") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setLuckBonusLength(arg);
            }
            catch (...) {
                std::cout << "WARNING: luckBonusLength variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("visionBonusLength") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setVisionBonusLength(arg);
            }
            catch (...) {
                std::cout << "WARNING: visionBonusLength variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("speedBonusLength") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setSpeedBonusLength(arg);
            }
            catch (...) {
                std::cout << "WARNING: speedBonusLength variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("spawnBonusLength") == 0) {
            try {
                double arg{ std::stod(j.at(1)) };
                currEnvironment->setSpawnBonusLength(arg);
            }
            catch (...) {
                std::cout << "WARNING: spawnBonusLength variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("ignore_items") == 0) {
            try {
                int arg{ std::stoi(j.at(1)) };
                currEnvironment->setIgnoreItems(arg);
            }
            catch (...) {
                std::cout << "WARNING: ignore_items variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("ignore_units") == 0) {
            try {
                int arg{ std::stoi(j.at(1)) };
                currEnvironment->setIgnoreUnits(arg);
            }
            catch (...) {
                std::cout << "WARNING: ignore_units variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("ignore_spatial") == 0) {
            try {
                int arg{ std::stoi(j.at(1)) };
                currEnvironment->setIgnoreSpatial(arg);
            }
            catch (...) {
                std::cout << "WARNING: ignore_spatial variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
        else if (j.at(0).compare("pickup_drops") == 0) {
            try {
                int arg{ std::stoi(j.at(1)) };
                currEnvironment->setPickupDrops(arg);
            }
            catch (...) {
                std::cout << "WARNING: pickup_drops variable threw exception in environment.frog (line " << i << ")\n";
            }
            continue;
        }
    }
    if (evaluateTimedEvents) {
        currEnvironment->timeEvents(timeElapsed, true);
    }
    currGame.setEnvironment(*currEnvironment);
    environmentFile.close();
    if (!currGame.isInEnvironment()) {
    // Battle file
        Battle* currBattle = new Battle();
        std::ifstream battleFile{ folderPath.u8string() + "/battle.frog" };
        i = 1;
        for (std::string line{}; std::getline(battleFile, line); i++) {
        }
        currGame.setBattle(*currBattle);
        battleFile.close();
    }

    // Achievement file
    std::vector<Achievement> currAchievements{};
    std::ifstream achievementsFile{ folderPath.u8string() + "/achievements.frog" };
    i = 1;
    startedFile = false;
    for (std::string line{}; std::getline(achievementsFile, line); i++) {
        // Check for empty string
        if (line.compare("") == 0) {
            continue;
        }
        // Check if started file yet
        if (!startedFile) {
            if (line.compare("*STARTFILE") == 0) {
                startedFile = true;
            }
            continue;
        }
        if (line.compare("*DEFINE=Achievement") == 0) {
            currAchievement = new Achievement();
            continue;
        }
        if (line.compare("*STRING=name") == 0) {
            currString = new std::string("");
            continue;
        }
        if (line.compare("*END") == 0) {
            if (currString != nullptr) {
                *currAchievement = Achievement(*currString);
                delete currString;
                currString = nullptr;
                continue;
            }
            else if (currAchievement != nullptr) {
                currAchievements.push_back(*currAchievement);
                delete currAchievement;
                currAchievement = nullptr;
                continue;
            }
            else if (startedFile) {
                startedFile = false;
                continue;
            }
            else {
                std::cout << "WARNING: *END called with nothing to end on line " << i << ".\n";
            }
        }
        if (currAchievement != nullptr) {
            if (currString != nullptr) {
                *currString += line;
                continue;
            }
        }
    }
    currGame.setAchievements(currAchievements);
    achievementsFile.close();

    // Command file
    std::vector<Command> currCommands{};
    std::ifstream commandsFile{ folderPath.u8string() + "/commands.frog" };
    i = 1;
    startedFile = false;
    for (std::string line{}; std::getline(commandsFile, line); i++) {
        // Check for empty string
        if (line.compare("") == 0) {
            continue;
        }
        // Check if started file yet
        if (!startedFile) {
            if (line.compare("*STARTFILE") == 0) {
                startedFile = true;
            }
            continue;
        }
        if (line.compare("*DEFINE=Command") == 0) {
            currCommand = new Command();
            continue;
        }
        if (line.compare("*STRING=name") == 0) {
            currString = new std::string("");
            continue;
        }
        if (line.compare("*END") == 0) {
            if (currString != nullptr) {
                *currCommand = Command(*currString);
                delete currString;
                currString = nullptr;
                continue;
            }
            else if (currCommand != nullptr) {
                currCommands.push_back(*currCommand);
                delete currCommand;
                currCommand = nullptr;
                continue;
            }
            else if (startedFile) {
                startedFile = false;
                continue;
            }
            else {
                std::cout << "WARNING: *END called with nothing to end on line " << i << ".\n";
            }
        }
        if (currCommand != nullptr) {
            if (currString != nullptr) {
                *currString += line;
                continue;
            }
        }
    }
    currGame.setCommands(currCommands);
    commandsFile.close();
}

// Returns whether the inputted string makes for a good filename
bool core_functions::validFileName(std::string filename) {
    if (filename.find_first_of("-<>:\"\\/|?*^") != std::string::npos) { // forbidden characters
        return false;
    }
    for (int i = 0; i < 32; i++) {
        if (filename.find(static_cast<char>(i)) != std::string::npos) { // control characters
            return false;
        }
    }
    std::vector<std::string> forbiddenNames{ "com1", "com2", "com3", "com4", "com5", "com6",
        "com7", "com8", "com9", "lpt1", "lpt2", "lpt3", "lpt4", "lpt5", "lpt6", "lpt7", "lpt8",
        "lpt9", "con", "nul", "prn"};
    std::vector<std::string> fileNameParsed{ core_functions::parseString(filename, ".") };
    for (std::string i : forbiddenNames) { // reserved names in windows
        if (i.compare(filename) == 0) {
            return false;
        }
        for (std::string j : fileNameParsed) {
            if (i.compare(j) == 0) {
                return false;
            }
        }
    }
    if (filename.length() > 31) { // file / folder name length limit in MacOS 9
        return false;
    }
    char firstChar{ filename.at(0) };
    char lastChar{ filename.at(filename.length() - 1) };
    // Invalid first and last characters
    if (static_cast<std::string_view>(".").find_first_of(firstChar) != std::string::npos) {
        return false;
    }
    if (static_cast<std::string_view>(" .").find_first_of(lastChar) != std::string::npos) {
        return false;
    }
    return true;
}

// Convert bool to string explicity
std::string core_functions::boolToString(bool b) {
    return b ? "1" : "0";
}

// Returns a string with a quantity "bar" to display in the inputted size
std::string core_functions::makeQuantityBar(int amount, int max, int barLength) {
    std::string barString{};
    if ((barLength > 2) && (max != 0)) { // need at least 3 characters to make a bar
        barString.push_back('|');
    }
    else {
        return barString;
    }
    double amountRatio{ static_cast<double>(amount) / max };
    bool middleBarNotAdded{ true };
    for (int i = 0; i < barLength - 2; i++) {
        if (amount == 0) {
            barString.push_back('_');
        }
        else if ((amount > max) && (middleBarNotAdded) && (static_cast<double>(i) / (barLength - 2) * amountRatio >= 1)) {
            middleBarNotAdded = false;
            barString.push_back('|');
        }
        else if (static_cast<double>(i) / (barLength - 2) <= amountRatio) {
            barString.push_back('+');
        }
        else {
            barString.push_back('_');
        }
    }
    barString.push_back('|');
    return barString;
}

// Given input of seconds return a string giving the time
std::string core_functions::secondsToTimeString(double seconds, int numberLimit) {
    int weeks{ 0 };
    int days{ 0 };
    int hours{ 0 };
    int minutes{ 0 };
    while (seconds >= 60) {
        seconds -= 60;
        minutes++;
    }
    while (minutes >= 60) {
        minutes -= 60;
        hours++;
    }
    while (hours >= 24) {
        hours -= 24;
        days++;
    }
    while (days >= 7) {
        days -= 7;
        weeks++;
    }
    std::vector<std::string> compiled{};
    if (weeks > 0) {
        if (weeks == 1) {
            compiled.push_back(std::to_string(weeks) + " week");
        }
        else {
            compiled.push_back(std::to_string(weeks) + " weeks");
        }
    }
    if (days > 0) {
        if (days == 1) {
            compiled.push_back(std::to_string(days) + " day");
        }
        else {
            compiled.push_back(std::to_string(days) + " days");
        }
    }
    if (hours > 0) {
        if (hours == 1) {
            compiled.push_back(std::to_string(hours) + " hour");
        }
        else {
            compiled.push_back(std::to_string(hours) + " hours");
        }
    }
    if (minutes > 0) {
        if (minutes == 1) {
            compiled.push_back(std::to_string(minutes) + " minute");
        }
        else {
            compiled.push_back(std::to_string(minutes) + " minutes");
        }
    }
    int intSeconds{ static_cast<int>(std::round(seconds)) };
    if (intSeconds > 0) {
        if (intSeconds == 1) {
            compiled.push_back(std::to_string(intSeconds) + " second");
        }
        else {
            compiled.push_back(std::to_string(intSeconds) + " seconds");
        }
    }
    if (compiled.size() == 0) {
        return "0 seconds";
    }
    std::string outputString{};
    if ((numberLimit == -1) || (numberLimit > compiled.size())) {
        for (size_t i{ 0 }; i < compiled.size(); i++) {
            outputString += compiled.at(i);
            if (i < compiled.size() - 1) {
                outputString += ", ";
            }
        }
    }
    else {
        for (size_t i{ 0 }; i < numberLimit; i++) {
            outputString += compiled.at(i);
            if (i < numberLimit - 1) {
                outputString += ", ";
            }
        }
    }
    return outputString;
}