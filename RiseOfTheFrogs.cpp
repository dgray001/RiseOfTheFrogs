/*
RiseOfTheFrogs.cpp
*/

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <stack>
#include <chrono>

#include "constants.h"
#include "coreFunctions.h"
#include "abilityClass.h"
#include "unitClass.h"
#include "battleClass.h"
#include "commandClass.h"
#include "environmentClass.h"
#include "unitClass.h"
#include "achievementClass.h"
#include "questClass.h"
#include "game.h"

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed random number
    rand(); // first call to rand() is not random for some reason
    const std::chrono::steady_clock::time_point programStartTime{ std::chrono::steady_clock::now() }; // start time of program
    Game currGame{};
    std::chrono::steady_clock::time_point programLastTime{ std::chrono::steady_clock::now() }; // time variable for last time call

    // Test Code
    core_functions::mainMenu(currGame);

    // core while loop
    while (true) {
        std::cout << "\n";
        if ((currGame.isInEnvironment()) && (currGame.getEnvironment().isPlayerFalling())) {
            std::cout << "Falling through " << currGame.getEnvironment().getEnvironmentAreas().at(
                currGame.getEnvironment().getCurrArea()).getName() << ".\n";
        }
        std::string input{};
        std::getline(std::cin >> std::ws, input); // receive input
        std::vector<std::string> inputVector = core_functions::parseString(input, " "); // parse
        bool invalidCommand = true;
        std::chrono::duration<double> timeElapsed = std::chrono::steady_clock::now() - programLastTime;
        programLastTime = std::chrono::steady_clock::now();
        if ((currGame.isInEnvironment()) && (!currGame.isFirstCall())) {
            if (currGame.timedEvents(static_cast<int>(std::round(timeElapsed.count())))) { // all timed events occur here
                continue;
            }
        }
        if (currGame.executeCommand(inputVector)) {
            std::cout << "Invalid command. Use 'commands' for a list of current possible commands.\n\n";
        }
        currGame.iterationChecks();
    }
    
    return 0;
}