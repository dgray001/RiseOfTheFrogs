/*
game.cpp
Game class contains everything needed for one saved game.
*/

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <math.h>
#include <vector>
#include <unordered_map>
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

// Create a new game
Game::Game(std::string playerName) {
    this->initializeCommands();
    this->initializeAchievements();
    this->currEnvironment.setPlayer(Player(playerName, 0));
    this->nextLevel();
}
void Game::initializeCommands() {
    this->addCommands({ "quit", "options", "help", "commands", "achievements", "credits" }); // credits must be last
}
void Game::initializeAchievements() {
    this->addAchievements({ "Monster Slayer I", "Traveler I", "Consumer I", "Reckless" });
}

void Game::nextLevel() {
    int dimension{ this->currEnvironment.getPlayer().getLevel() / constants::dimensionLevels + 1 };
    //this->nextMainStoryChapter(dimension - 1);
    std::string environmentName{};
    Player player = this->currEnvironment.getPlayer();
    core_functions::flushScreen();
    switch (dimension) {
        case 1:
            std::cout << "+++++ Daniel's Aquarium +++++\n\n";
            environmentName = "DanielsAquarium";
            break;
        case 2:
            std::cout << "+++++ Toxic Sewers +++++\n\n";
            environmentName = "Sewers";
            break;
        case 3:
            std::cout << "+++++ Lake +++++\n\n";
            environmentName = "Lake";
            break;
        default:
            std::cout << "Dimension " << dimension << " not found.\n";
            break;
    }
    core_functions::pauseProgram(constants::shortPauseTime);
    this->exitEnvironment();
    this->currEnvironment = Environment(player, environmentName);
    this->enterEnvironment();
    this->firstCall = true;
}

// Set environment commands
void Game::enterEnvironment() {
    this->inEnvironment = true;
    this->addCommands({ "status", "quests", "look", "turn", "move", "fight", "consume", "talk" });
    if (this->currEnvironment.getPlayer().getMaxInventorySlots() > 0) {
        this->addCommands({ "pickup", "drop", "use", "inventory", "equip", "unequip" });
    }
    if (this->currEnvironment.getPlayer().getUpgradeCoordination1()) {
        this->addCommands({ "moveto", "turnto", "ignore" });
    }
    if (this->currEnvironment.getPlayer().getUpgradeCoordination2()) {
        this->addCommand( "face" );
    }
    if (this->currEnvironment.getPlayer().getUpgradeMemory1()) {
        this->addCommand( "inquire" );
    }
    if (this->currEnvironment.getPlayer().getDismantleItems()) {
        this->addCommand( "dismantle" );
    }
    if (constants::TESTMODE) {
        this->addCommand( "levelup" );
    }
    this->currEnvironment.playerLook();
}

// Returns whether enemy fights you
bool Game::timedEvents(double timeElapsed) {
    if (this->currEnvironment.timeEvents(timeElapsed)) { // enemy fight you in environment
        this->currBattle = Battle(this->currEnvironment.getPlayer(),
            this->currEnvironment.getOtherUnits().at(this->currEnvironment.getCurrKey()), false);
        this->exitEnvironment();
        std::cout << this->currBattle.getEnemy().getName() << " fought you!\n\n";
        this->enterBattle();
        this->currBattle.printBattleInfo();
        if (currBattle.getBattleOver()) {
            this->exitBattle();
        }
        return true;
    }
    return false;
}

// Remove environment commands
void Game::exitEnvironment() {
    this->inEnvironment = false;
    std::vector<std::string> environmentCommands{ "look", "turn", "move", "fight", "status", "face",
        "quests", "consume", "pickup", "moveto", "turnto", "inquire", "equip", "unequip", "drop",
        "use", "inventory", "ascend", "levelup", "talk", "dismantle" };
    for (size_t i = 0; i < environmentCommands.size(); i++) {
        std::string currCommand = environmentCommands.at(i);
        std::vector<Command>::iterator iter =
            std::find_if(this->currCommands.begin(), this->currCommands.end(),
                [currCommand](Command j) { return (j.getName().compare(currCommand) == 0); });
        if (iter != this->currCommands.end()) { // command in list
            this->currCommands.erase(iter);
        }
    }
}
// Set battle commands
void Game::enterBattle() {
    // update current possible commands
    for (size_t i = 0; i < this->currBattle.getPlayer().getBattleAbilities().size(); i++) {
        std::string abilityName = this->currBattle.getPlayer().getBattleAbilities().at(i).getName();
        this->addCommand(Command(abilityName, this->currBattle.getPlayer()));
    }
    if (this->currBattle.getPlayer().getItemsInBattle()) {
        this->addCommand("item");
    }
    this->currBattle.startTurn();
}
// Remove battle commands, enter environment, and receive rewards/etc.
void Game::exitBattle() {
    // update current possible commands
    for (size_t i = 0; i < this->currBattle.getPlayer().getBattleAbilities().size(); i++) {
        std::string abilityName = this->currBattle.getPlayer().getBattleAbilities().at(i).getName();
        std::vector<Command>::iterator iter =
            std::find_if(this->currCommands.begin(), this->currCommands.end(),
                [abilityName](Command j) { return (j.getName().compare(abilityName) == 0); });
        if (iter != this->currCommands.end()) { // command in list
           this->currCommands.erase(iter);
        }
    }
    if (this->currBattle.getPlayer().getItemsInBattle()) {
        std::vector<Command>::iterator iter =
            std::find_if(this->currCommands.begin(), this->currCommands.end(),
                [](Command i) { return (i.getName().compare("item") == 0); });
        if (iter != this->currCommands.end()) { // command in list
           this->currCommands.erase(iter);
        }
    }

    // Update environment independent of who won the battle
    Player thePlayer = this->currBattle.getPlayer(); // update player
    thePlayer.resetStatusEffects();
    this->currEnvironment.setPlayer(thePlayer);
    if (this->currBattle.getEnemy().getStatusAlive()) { // other unit still alive
        aiUnit theEnemy = this->currBattle.getEnemy();
        theEnemy.resetStatusEffects();
        theEnemy.setCoolDown(constants::fightCooldown);
        this->currEnvironment.updateCurrUnit(theEnemy);
    }

    // Calculate rewards / etc. based on win/loss, etc.
    if (!(this->currBattle.getEnemy().getStatusAlive())) { // player wins if enemy dies
        // Check excel for details on coefficients, curves, etc.
        int enemyLevel{ this->currBattle.getEnemy().getLevel() };
        int xpReward{ static_cast<int>(std::ceil(constants::xpRewardCoefficient *
            std::pow(constants::xpRewardDimension, enemyLevel / constants::dimensionLevels) *
            std::pow(constants::xpRewardIntersection, enemyLevel / constants::intersectionLevels) * (enemyLevel + 1.0))) };
        int creditReward{ static_cast<int>(std::ceil(constants::creditRewardCoefficient *
            std::pow(constants::creditRewardDimension, enemyLevel / constants::dimensionLevels) * enemyLevel)) };
        int foulReward{ static_cast<int>(std::ceil(constants::foulRewardCoefficient * enemyLevel)) };
        int energyAdded = this->currEnvironment.addPlayerEnergy(this->currBattle.getEnemy().getEnergyValue());
        std::cout << "\nYou won the battle!\n";
        core_functions::pauseProgram(constants::shortPauseTime);
        std::cout << "\nYou ate " << this->currBattle.getEnemy().getName() << " to gain " << energyAdded << " energy.\n";
        this->currEnvironment.addMonsterSlain();
        this->playerRewards(xpReward, creditReward, foulReward);
        this->currEnvironment.removeCurrUnit(); // remove enemy unit
    }
    else if (!(this->currBattle.getPlayer().getStatusAlive())) {
        std::cout << "\nYou lost the battle!\n";
        core_functions::pauseProgram(constants::shortPauseTime);
    }
    else {
        // someone fled
    }
    std::cout << "\n";
    core_functions::requireEnter();
    std::cout << "\n";
    this->enterEnvironment();
}

// Player reward functions
void Game::playerRewards(int xp, int credits, int fouls) {
    this->currEnvironment.playerRewards(xp, credits, fouls);
    this->checkIntersections();
}
// Check for intersections and give player upgrades if so
void Game::checkIntersections() {
    int i = this->currEnvironment.getPlayerIntersectionsBuffer();
    while (i > 0) {
        // Player can have upgraded any number of levels at once so must find his level at each upgrade
        int levelAtThisUpgrade = this->currEnvironment.getPlayer().getLevel() -
            (i - 1) * constants::intersectionLevels -
            this->currEnvironment.getPlayer().getLevel() % constants::intersectionLevels;
        if (levelAtThisUpgrade % constants::dimensionLevels == 0) { // new dimension
            std::cout << "\n--- New Intersection ---\n";
            core_functions::pauseProgram(constants::shortPauseTime);
            this->upgradePlayer(levelAtThisUpgrade / constants::dimensionLevels);
            core_functions::pauseProgram(constants::shortPauseTime);
            std::cout << "\n--- New Dimension ---\n";
            core_functions::pauseProgram(constants::shortPauseTime);
            std::cout << "You have found enough intersections to ascend into the next dimension.\n\n";
            core_functions::pauseProgram(constants::normalPauseTime);
            this->upgradePlayer(levelAtThisUpgrade / constants::dimensionLevels + 1);
            this->addCommand("ascend");
        }
        else { // new subtier
            std::cout << "\n--- New Intersection ---\n";
            core_functions::pauseProgram(constants::shortPauseTime);
            this->upgradePlayer(levelAtThisUpgrade / constants::dimensionLevels + 1);
        }
        i--;
    }
}
void Game::upgradePlayer(int dimension) {
    int upgradeID = this->currEnvironment.upgradePlayer(dimension);
    core_functions::pauseProgram(constants::shortPauseTime);
    // reset commands
    this->currCommands.clear();
    this->initializeCommands();
    this->enterEnvironment();
}


// Execute the proper command (return true if command invalid
bool Game::executeCommand(std::vector<std::string> inputVector) {
    for (size_t i = 0; i < this->currCommands.size(); i++) { // find relevant command
        if (this->currCommands.at(i).checkNames(inputVector[0])) {
            if (inputVector.size() > 1) {
                this->takeAction(this->currCommands.at(i), inputVector[1]);
            }
            else {
                this->takeAction(this->currCommands.at(i), ""); // use empty string literal
            }
            return false;
        }
    }
    return true;
}
void Game::takeAction(Command command, std::string argument) {
    std::cout << "\n";
    // basic commands (should always be accessible)
    if (command.getName().compare("quit") == 0) {
        std::cout << "Are you sure you want to quit?\n";
        std::string answer{};
        std::cin >> answer;
        if ((answer.compare("yes") == 0) or (answer.compare("y") == 0) or
            (answer.compare("Yes") == 0) or (answer.compare("Y") == 0)) {
            std::cout << "Saving game and exiting ...\n";
            this->saveGame();
            exit(0);
        }
        else {
            std::cout << "I'll take that as a no.\n\n";
        }
        return;
    }
    else if (command.getName().compare("options") == 0) {
        std::cout << "Entering options menu\n\n";
        this->optionsMenu();
        return;
    }
    else if (command.getName().compare("commands") == 0) {
        std::cout << "+++ Current Commands +++\n";
        for (size_t i = 0; i < this->currCommands.size(); i++) {
            std::cout << " -" << this->currCommands.at(i).getName() << ": " <<
                this->currCommands.at(i).getShortDescription() << "\n";
        }
        std::cout << "\n";
        return;
    }
    else if (command.getName().compare("help") == 0) {
        bool argumentSpecified = false;
        if (argument.compare("") == 0) {
            std::cout << command.getLongDescription();
        }
        else {
            for (size_t i = 0; i < this->currCommands.size(); i++) {
                if (this->currCommands.at(i).getName().compare(argument) == 0) {
                    std::cout << this->currCommands.at(i).getLongDescription(); // print long description of argument
                    argumentSpecified = true;
                    break;
                }
            }
            if (!argumentSpecified) {
                std::cout << "No valid argument for \"help\".\n";
                std::cout << command.getLongDescription(); // print long description of help
            }
        }
        return;
    }
    else if (command.getName().compare("achievements") == 0) {
        std::cout << "+++ Achievements Completed +++\n";
        this->currEnvironment.getPlayer().printAchievements();
        std::cout << "\n";
        return;
    }
    else if (command.getName().compare("credits") == 0) {
        std::cout << constants::credits;
        return;
    }

    // Battle commands
    if (command.getName().compare("battleInfo") == 0) {
        this->currBattle.printBattleInfo();
        return;
    }
    else if (command.getName().compare("item") == 0) {
        std::vector<int> indices{};
        for (size_t i{ 0 }; i < this->currBattle.getPlayer().getInventory().size(); i++) {
            if (this->currBattle.getPlayer().getInventory().at(i).isConsumable()) {
                indices.push_back(i);
            }
        }
        if (argument.compare("") == 0) {
            std::cout << " --- Consumable Items ---\n";
            for (size_t i{ 0 }; i < indices.size(); i++) {
                std::cout << std::to_string(i + 1) << ": " << this->currBattle.getPlayer().getInventory().at(indices.at(i)).getName() << "\n";
            }
            std::cout << "\n";
            return;
        }
        if (!core_functions::isPositiveInteger(argument)) {
            std::cout << "Argument is not an index.\n\n";
            return;
        }
        int itemIndex = stoul(argument) - 1;
        if ((itemIndex < 0) || (itemIndex >= indices.size())) {
            std::cout << "No item with index " << std::to_string(itemIndex + 1) << ".\n";
            return;
        }
        this->currBattle.consume("item " + std::to_string(indices.at(itemIndex)));
        return;
    }
    else if (this->currBattle.getPlayer().hasBattleAbility(command.getName())) { // any battle ability
        int energyCost{ this->currBattle.getPlayer().battleAbilityEnergyCost(command.getName()) };
        if (this->currBattle.getPlayer().getCurrEnergy() < energyCost) {
            std::cout << "You don't have enough energy for that.\n\n";
            return;
        }
        this->currBattle.removePlayerEnergy(energyCost);
        this->currBattle.attack(command.getName());
        return;
    }

    // Environment commands
    if (command.getName().compare("status") == 0) {
        this->currEnvironment.printStatus();
        return;
    }
    else if (command.getName().compare("quests") == 0) {
        this->currEnvironment.printQuests();
        return;
    }
    else if (command.getName().compare("look") == 0) {
        this->currEnvironment.playerLook(); // update units seen
        return;
    }
    else if (command.getName().compare("turn") == 0) {
        if (this->currEnvironment.getPlayer().getCurrEnergy() < command.getEnergyCost()) {
            std::cout << "You don't have enough energy for that.\n\n";
            return;
        }
        size_t index{};
        if ((this->currEnvironment.getPlayer().getUpgradeCoordination1()) &&
            ((index = argument.find("=")) != argument.npos)) {
            if (core_functions::isPositiveInteger(argument.substr(index + 1, argument.npos))) {
                if (this->currEnvironment.turnPlayer(argument.substr(0, index),
                    stoul(argument.substr(index + 1, argument.npos)))) {
                    this->currEnvironment.removePlayerEnergy(command.getEnergyCost());
                    this->currEnvironment.playerLook(); // update units seen
                }
            }
            else {
                std::cout << "Specified turn direction not valid. Check \"help 'turn'\".\n\n";
            }
        }
        else {
            if (this->currEnvironment.turnPlayer(argument)) {
                this->currEnvironment.removePlayerEnergy(command.getEnergyCost());
                this->currEnvironment.playerLook(); // update units seen
            }
        }
        return;
    }
    else if (command.getName().compare("move") == 0) {
        if (this->currEnvironment.getPlayer().getCurrEnergy() < command.getEnergyCost()) {
            std::cout << "You don't have enough energy for that.\n\n";
            return;
        }
        if (this->currEnvironment.getPlayer().getCurrHealth() == 0) {
            std::cout << "You are too weak to move.\n\n";
            return;
        }
        if (this->currEnvironment.isPlayerFalling()) {
            std::cout << "Can't move while falling.\n\n";
            return;
        }
        this->currEnvironment.removePlayerEnergy(command.getEnergyCost());
        if ((this->currEnvironment.getPlayer().getUpgradeCoordination1()) && (core_functions::isPositiveInteger(argument))) {
            if (this->currEnvironment.movePlayer(stoi(argument) / 100.0)) {
                this->currEnvironment.playerLook(); // update units seen
            }
        }
        else {
            if (this->currEnvironment.movePlayer()) { // move max distance if nothing specified
                this->currEnvironment.playerLook(); // update units seen
            }
        }
        return;
    }
    else if (command.getName().compare("fight") == 0) {
        if (this->currEnvironment.getPlayer().getCurrEnergy() < command.getEnergyCost()) {
            std::cout << "You don't have enough energy for that.\n\n";
            return;
        }
        if (this->currEnvironment.getPlayer().getCurrHealth() == 0) {
            std::cout << "You are too weak to fight.\n\n";
            return;
        }
        if (argument.compare("") == 0) { // auto fight
            for (int key : this->currEnvironment.getUnitsSeen()) {
                if ((this->currEnvironment.getPlayer().distanceToUnit(this->currEnvironment.getOtherUnits()
                    .at(key)) < this->currEnvironment.getPlayer().getMaxMoveDistance()) &&
                    (this->currEnvironment.getPlayer().canMoveIntoArea(this->currEnvironment.getEnvironmentAreas().at(
                    this->currEnvironment.areaInNow(this->currEnvironment.getOtherUnits().at(key))).getID())) &&
                    (this->currEnvironment.getOtherUnits().at(key).getAllyState() != 0) && (this->
                    currEnvironment.getOtherUnits().at(key).getCoolDown() <= 0.0)) {
                    this->currEnvironment.setCurrKey(key);
                    std::cout << "No unit specified. Fighting " << this->currEnvironment.getOtherUnits().at(key).getName() << ".\n";
goto FIGHT;
                }
            }
            std::cout << "No unit within sight and range to auto fight.\n";
            return;
        }
        if (!core_functions::isPositiveInteger(argument)) {
            std::cout << "No unit specified. Use \"fight 'integer'\" to specify which unit to fight.\n\n";
            return;
        }
        if ((stoul(argument) <= 0) || (stoul(argument) > this->currEnvironment.getUnitsSeen().size())) {
            std::cout << "No unit with indice " << argument << ".\n\n";
            return;
        }
        this->currEnvironment.setCurrKey(this->currEnvironment.getUnitsSeen().at(stoul(argument) - 1));
        if (this->currEnvironment.getOtherUnits().at(this->currEnvironment.getCurrKey()).getAllyState() == 0) {
            std::cout << "You can't fight that unit! Try talking with it instead.\n\n";
            return;
        }
        if (this->currEnvironment.getPlayer().distanceToUnit(this->currEnvironment.getOtherUnits().at(
            this->currEnvironment.getCurrKey())) > this->currEnvironment.getPlayer().getMaxMoveDistance()) {
            std::cout << "Move closer to fight this creature.\n\n";
            return;
        }
        if (!this->currEnvironment.getPlayer().canMoveIntoArea(this->currEnvironment.getEnvironmentAreas().at(
            this->currEnvironment.areaInNow(this->currEnvironment.getOtherUnits().at(this->currEnvironment.getCurrKey()))).getID())) {
            std::cout << "You are unable to enter that area.\n\n";
            return;
        }
        if (this->currEnvironment.getOtherUnits().at(this->currEnvironment.getCurrKey()).getCoolDown() > 0) {
            std::cout << "That unit is on cooldown.\n\n";
            return;
        }
FIGHT:
        this->currEnvironment.removePlayerEnergy(command.getEnergyCost());
        this->currBattle = Battle(this->currEnvironment.getPlayer(),
            this->currEnvironment.getOtherUnits().at(this->currEnvironment.getCurrKey()));
        this->exitEnvironment();
        this->enterBattle();
        return;
    }
    else if (command.getName().compare("talk") == 0) {
        if (this->currEnvironment.getPlayer().getCurrEnergy() < command.getEnergyCost()) {
            std::cout << "You don't have enough energy for that.\n\n";
            return;
        }
        if (argument.compare("") == 0) { // auto talk
            for (int key : this->currEnvironment.getUnitsSeen()) {
                if ((this->currEnvironment.getPlayer().distanceToUnit(this->currEnvironment.getOtherUnits()
                    .at(key)) < this->currEnvironment.getPlayer().getMaxMoveDistance()) &&
                    (this->currEnvironment.getPlayer().canMoveIntoArea(this->currEnvironment.getEnvironmentAreas().at(
                    this->currEnvironment.areaInNow(this->currEnvironment.getOtherUnits().at(key))).getID())) &&
                    (this->currEnvironment.getOtherUnits().at(key).getAllyState() == 0) && (this->
                    currEnvironment.getOtherUnits().at(key).getCoolDown() <= 0.0)) {
                    this->currEnvironment.setCurrKey(key);
                    std::cout << "No unit specified. Talking with " << this->currEnvironment.getOtherUnits().at(key).getName() << ".\n";
goto TALK;
                }
            }
            std::cout << "No unit within sight and range to auto talk to.\n";
            return;
        }
        if (!core_functions::isPositiveInteger(argument)) {
            std::cout << "No unit specified. Use \"talk 'integer'\" to specify which unit to talk to.\n\n";
            return;
        }
        if ((stoul(argument) <= 0) || (stoul(argument) > this->currEnvironment.getUnitsSeen().size())) {
            std::cout << "No unit with indice " << argument << ".\n\n";
            return;
        }
        this->currEnvironment.setCurrKey(this->currEnvironment.getUnitsSeen().at(stoul(argument) - 1));
        if (this->currEnvironment.getOtherUnits().at(this->currEnvironment.getCurrKey()).getAllyState() != 0) {
            std::cout << "You can't talk to that unit. Try fighting it instead!\n\n";
            return;
        }
        if (this->currEnvironment.getPlayer().distanceToUnit(this->currEnvironment.getOtherUnits().at(
            this->currEnvironment.getCurrKey())) > this->currEnvironment.getPlayer().getMaxMoveDistance()) {
            std::cout << "Move closer to talk with this creature.\n\n";
            return;
        }
        if (!this->currEnvironment.getPlayer().canMoveIntoArea(this->currEnvironment.getEnvironmentAreas().at(
            this->currEnvironment.areaInNow(this->currEnvironment.getOtherUnits().at(this->currEnvironment.getCurrKey()))).getID())) {
            std::cout << "You are unable to enter that area.\n\n";
            return;
        }
        if (this->currEnvironment.getOtherUnits().at(this->currEnvironment.getCurrKey()).getCoolDown() > 0) {
            std::cout << "That unit is on cooldown.\n\n";
            return;
        }
TALK:
        this->currEnvironment.removePlayerEnergy(command.getEnergyCost());
        this->currEnvironment.talkToCurrUnit();
        return;
    }
    else if (command.getName().compare("pickup") == 0) {
        if ((this->currEnvironment.getPlayer().getUpgradeCoordination2()) && (argument.compare("drops") == 0)) {
            this->currEnvironment.togglePickupDrops();
            return;
        }
        if (this->currEnvironment.getPlayer().getCurrEnergy() < command.getEnergyCost()) {
            std::cout << "You don't have enough energy for that.\n\n";
            return;
        }
        if (argument.compare("") == 0) { // auto pickup
            for (int i{ 0 }; i < this->currEnvironment.getItemsSeen().size(); i++) {
                if ((this->currEnvironment.getPlayer().distanceToItem(this->currEnvironment.getDroppedItems()
                    .at(this->currEnvironment.getItemsSeen().at(i))) < this->currEnvironment.getPlayer().getMaxMoveDistance()) &&
                    (this->currEnvironment.getPlayer().canMoveIntoArea(this->currEnvironment.getEnvironmentAreas().at(
                    this->currEnvironment.areaInNow(this->currEnvironment.getDroppedItems().at(
                    this->currEnvironment.getItemsSeen().at(i)))).getID())) && (((this->currEnvironment.getPlayer().hasItem(this->currEnvironment.getDroppedItems()
                    .at(this->currEnvironment.getItemsSeen().at(i)).getID()) != -1) && (this->currEnvironment.getDroppedItems()
                    .at(this->currEnvironment.getItemsSeen().at(i)).isStackable())) || (this->currEnvironment.getPlayer().hasInventorySpace()))) {
                    argument = std::to_string(i + 1);
                    std::cout << "No item specified. Picking up " << this->currEnvironment.
                        getDroppedItems().at(this->currEnvironment.getItemsSeen().at(i)).getName() << ".\n";
goto PICKUP;
                }
            }
            std::cout << "No item within sight and range to pickup.\n";
            return;
        }
        if (!core_functions::isPositiveInteger(argument)) {
            std::cout << "No item specified. Use \"pickup 'integer'\" to specify which item to pick up.\n\n";
            return;
        }
        if ((stoul(argument) <= 0) || (stoul(argument) > this->currEnvironment.getItemsSeen().size())) {
            std::cout << "No item with indice " << argument << ".\n\n";
            return;
        }
        if (this->currEnvironment.getPlayer().distanceToItem(this->currEnvironment.getDroppedItems().at(
            this->currEnvironment.getItemsSeen().at(stoul(argument) - 1))) >
            this->currEnvironment.getPlayer().getMaxMoveDistance()) {
            std::cout << "Move closer to pick up this item.\n\n";
            return;
        }
        if (!this->currEnvironment.getPlayer().canMoveIntoArea(this->currEnvironment.
            getEnvironmentAreas().at(this->currEnvironment.areaInNow(this->currEnvironment.
            getDroppedItems().at(this->currEnvironment.getItemsSeen().at(stoul(argument) - 1)))).getID())) {
            std::cout << "You are unable to enter that area.\n\n";
            return;
        }
        if (this->currEnvironment.getPlayer().hasItem(currEnvironment.getDroppedItems().at(
            this->currEnvironment.getItemsSeen().at(stoul(argument) - 1)).getID()) == -1) {
            if (this->currEnvironment.getPlayer().getInventory().size() >= this->currEnvironment.getPlayer().getMaxInventorySlots()) {
                std::cout << "You don't have inventory space to pick up an item.\n\n";
                return;
            }
        }
PICKUP:
        this->currEnvironment.removePlayerEnergy(command.getEnergyCost());
        this->currEnvironment.pickupItem(stoul(argument) - 1);
        return;
    }
    else if (command.getName().compare("consume") == 0) { // consume the specified dropped item
        Item itemPointer{};
        int itemKey{};
        if ((this->currEnvironment.getPlayer().getUpgradeCoordination2()) && (argument.compare("all") == 0)) {
            bool noConsume = true;
            for (int key : this->currEnvironment.getItemsSeen()) {
                itemPointer = this->currEnvironment.getDroppedItems().at(key);
                if ((this->currEnvironment.getPlayer().distanceToItem(this->currEnvironment.getDroppedItems()
                    .at(key)) < this->currEnvironment.getPlayer().getMaxMoveDistance()) &&
                    this->currEnvironment.getPlayer().canMoveIntoArea(this->currEnvironment.getEnvironmentAreas().at(
                    this->currEnvironment.areaInNow(itemPointer)).getID()) && (itemPointer.isConsumable())) {
                    itemKey = key;
                    std::cout << "Consuming " << this->currEnvironment.getDroppedItems().at(key).getName() << ".\n";
                    this->currEnvironment.consumeItem(itemKey);
                    this->checkIntersections();
                    noConsume = false;
                }
            }
            if (noConsume) {
                std::cout << "No item within sight and range to consume.\n";
            }
            return;
        }
        if (argument.compare("") == 0) { // auto consume
            for (int key : this->currEnvironment.getItemsSeen()) {
                itemPointer = this->currEnvironment.getDroppedItems().at(key);
                if ((this->currEnvironment.getPlayer().distanceToItem(this->currEnvironment.getDroppedItems()
                    .at(key)) < this->currEnvironment.getPlayer().getMaxMoveDistance()) &&
                    this->currEnvironment.getPlayer().canMoveIntoArea(this->currEnvironment.getEnvironmentAreas().at(
                    this->currEnvironment.areaInNow(itemPointer)).getID()) && (itemPointer.isConsumable())) {
                    itemKey = key;
                    std::cout << "No item specified. Consuming " << this->currEnvironment.getDroppedItems().at(key).getName() << ".\n";
goto CONSUME;
                }
            }
            std::cout << "No item within sight and range to auto-consume.\n";
            return;
        }
        if (!core_functions::isPositiveInteger(argument)) {
            std::cout << "No item specified. Use \"consume 'integer'\" to specify which item to consume.\n\n";
            return;
        }
        if ((stoul(argument) <= 0) || (stoul(argument) > this->currEnvironment.getItemsSeen().size())) {
            std::cout << "No item with indice " << argument << ".\n\n";
            return;
        }
        itemPointer = this->currEnvironment.getDroppedItems().at(this->currEnvironment.getItemsSeen().at(stoul(argument) - 1));
        if (this->currEnvironment.getPlayer().distanceToItem(itemPointer) >
            this->currEnvironment.getPlayer().getMaxMoveDistance()) { // distance to item
            std::cout << "Move closer to consume this item.\n\n";
            return;
        }
        if (!this->currEnvironment.getPlayer().canMoveIntoArea(this->currEnvironment.getEnvironmentAreas().at(
            this->currEnvironment.areaInNow(itemPointer)).getID())) {
            std::cout << "You are unable to enter that area.\n\n";
            return;
        }
        if (!itemPointer.isConsumable()) {
            std::cout << "Item not consumable.\n\n";
            return;
        }
        itemKey = this->currEnvironment.getItemsSeen().at(stoul(argument) - 1);
CONSUME:
        this->currEnvironment.consumeItem(itemKey);
        this->checkIntersections();
        return;
    }
    else if (command.getName().compare("inventory") == 0) { // display the player inventory
        int inventoryDisplayKey{ 0 }; // default to show entire inventory
        if (argument.compare("gear") == 0) {
            inventoryDisplayKey = 1;
        }
        else if (argument.compare("weapon") == 0) {
            inventoryDisplayKey = 2;
        }
        else if (argument.compare("offhand") == 0) {
            inventoryDisplayKey = 3;
        }
        else if (argument.compare("twohand") == 0) {
            inventoryDisplayKey = 4;
        }
        else if (argument.compare("headgear") == 0) {
            inventoryDisplayKey = 5;
        }
        else if (argument.compare("chestgear") == 0) {
            inventoryDisplayKey = 6;
        }
        else if (argument.compare("leggear") == 0) {
            inventoryDisplayKey = 7;
        }
        else if (argument.compare("footgear") == 0) {
            inventoryDisplayKey = 8;
        }
        else if (argument.compare("accessory") == 0) {
            inventoryDisplayKey = 9;
        }
        else if (argument.compare("consumable") == 0) {
            inventoryDisplayKey = 10;
        }
        else if (argument.compare("") != 0) {
            std::cout << "Argument invalid. Displaying entire inventory.\n\n";
        }
        this->currEnvironment.getPlayer().displayInventory(inventoryDisplayKey);
        return;
    }
    else if (command.getName().compare("drop") == 0) { // drop item from inventory
        if (!core_functions::isPositiveInteger(argument)) {
            std::cout << "No item specified. Use \"drop 'integer'\" to specify which item to drop.\n\n";
            return;
        }
        if ((stoul(argument) <= 0) || (stoul(argument) > this->currEnvironment.getPlayer().getInventory().size())) {
            std::cout << "No item with indice " << argument << ".\n\n";
            return;
        }
        this->currEnvironment.dropItem(stoul(argument) - 1);
        return;
    }
    else if (command.getName().compare("use") == 0) { // use item in inventory
        if (!core_functions::isPositiveInteger(argument)) {
            std::cout << "No item specified. Use \"use 'integer'\" to specify which item to drop.\n\n";
            return;
        }
        if ((stoul(argument) <= 0) || (stoul(argument) > this->currEnvironment.getPlayer().getInventory().size())) {
            std::cout << "No item with indice " << argument << ".\n\n";
            return;
        }
        this->currEnvironment.useItem(stoul(argument) - 1);
        return;
    }
    else if (command.getName().compare("equip") == 0) { // equip item in inventory
        if (!core_functions::isPositiveInteger(argument)) {
            std::cout << "No item specified. Use \"equip 'integer'\" to specify which item to equip.\n\n";
            return;
        }
        if ((stoul(argument) <= 0) || (stoul(argument) > this->currEnvironment.getPlayer().getInventory().size())) {
            std::cout << "No item with indice " << argument << ".\n\n";
            return;
        }
        this->currEnvironment.equipItem(stoul(argument) - 1);
        return;
    }
    else if (command.getName().compare("dismantle") == 0) { // dismantle item in inventory
        if (!core_functions::isPositiveInteger(argument)) {
            std::cout << "No item specified. Use \"dismantle 'integer'\" to specify which item to equip.\n\n";
            return;
        }
        if ((stoul(argument) <= 0) || (stoul(argument) > this->currEnvironment.getPlayer().getInventory().size())) {
            std::cout << "No item with indice " << argument << ".\n\n";
            return;
        }
        int itemIndex{ static_cast<int>(stoul(argument)) - 1 };
        this->currEnvironment.dismantleItem(itemIndex);
        return;
    }
    else if (command.getName().compare("unequip") == 0) { // unequip item into inventory
        if (this->currEnvironment.getPlayer().getInventory().size() >= this->currEnvironment.getPlayer().getMaxInventorySlots()) {
            std::cout << "You don't have inventory space to unequip an item.\n\n";
            return;
        }
        this->currEnvironment.unequipItem(argument);
        return;
    }
    else if (command.getName().compare("moveto") == 0) { // move toward the specified unit
        if (this->currEnvironment.getPlayer().getCurrEnergy() < command.getEnergyCost()) {
            std::cout << "You don't have enough energy for that.\n\n";
            return;
        }
        if (!core_functions::isPositiveInteger(argument)) {
            std::cout << "No unit specified. Use \"moveto 'integer'\" to specify which unit to move toward.\n\n";
            return;
        }
        if ((stoul(argument) <= 0) || (stoul(argument) > this->currEnvironment.getUnitsSeen().size())) {
            std::cout << "No unit with indice " << argument << ".\n\n";
            return;
        }
        if (this->currEnvironment.getPlayer().getCurrHealth() == 0) {
            std::cout << "You are too weak to move.\n\n";
            return;
        }
        this->currEnvironment.setCurrKey(this->currEnvironment.getUnitsSeen().at(stoul(argument) - 1));
        // don't move more than you need to interact with the unit
        // NOTE: added a small amount to ensure player can interact with unit
        double distanceMoved{ std::min(this->currEnvironment.getPlayer().getMaxMoveDistance(),
            this->currEnvironment.getPlayer().distanceToUnit(
            this->currEnvironment.getOtherUnits().at(this->currEnvironment.getCurrKey())) -
            this->currEnvironment.getPlayer().getMaxMoveDistance() + constants::smallDistance) };
        this->currEnvironment.turnPlayerToward(this->currEnvironment.getOtherUnits().at(
            this->currEnvironment.getUnitsSeen().at(stoul(argument) - 1)));
        if (distanceMoved > 0) {
            this->currEnvironment.removePlayerEnergy(command.getEnergyCost());
            this->currEnvironment.movePlayer(distanceMoved);
            this->currEnvironment.playerLook();
        }
        else {
            std::cout << "You are already in range of " << this->currEnvironment.
                getOtherUnits().at(this->currEnvironment.getUnitsSeen().at(stoul(argument) - 1)).getName() << ".\n";
        }
        return;
    }
    else if (command.getName().compare("turnto") == 0) { // turn toward the specified unit
        if (this->currEnvironment.getPlayer().getCurrEnergy() < command.getEnergyCost()) {
            std::cout << "You don't have enough energy for that.\n\n";
            return;
        }
        if (!core_functions::isPositiveInteger(argument)) {
            std::cout << "No unit specified. Use \"turnto 'integer'\" to specify which unit to move toward.\n\n";
            return;
        }
        if ((stoul(argument) <= 0) || (stoul(argument) > this->currEnvironment.getUnitsSeen().size())) {
            std::cout << "No unit with indice " << argument << ".\n\n";
            return;
        }
        if (this->currEnvironment.getPlayer().getCurrHealth() == 0) {
            std::cout << "You are too weak to turn.\n\n";
            return;
        }
        this->currEnvironment.removePlayerEnergy(command.getEnergyCost());
        this->currEnvironment.turnPlayerToward(this->currEnvironment.getOtherUnits().at(
            this->currEnvironment.getUnitsSeen().at(stoul(argument) - 1)));
        this->currEnvironment.playerLook();
        return;
    }
    else if (command.getName().compare("ignore") == 0) {
        if (argument.compare("units") == 0) {
            this->currEnvironment.toggleIgnoreUnits();
        }
        else if (argument.compare("items") == 0) {
            this->currEnvironment.toggleIgnoreItems();
        }
        else if (argument.compare("spatial") == 0) {
            this->currEnvironment.toggleIgnoreSpatial();
        }
        else {
            std::cout << "Invalid ignore argument. Check \"help 'ignore'\" for instructions.\n\n";
        }
        return;
    }
    else if (command.getName().compare("face") == 0) {
        if (this->currEnvironment.getPlayer().getCurrEnergy() < command.getEnergyCost()) {
            std::cout << "You don't have enough energy for that.\n\n";
            return;
        }
        if (this->currEnvironment.getPlayer().getCurrHealth() == 0) {
            std::cout << "You are too weak to turn.\n\n";
            return;
        }
        if (this->currEnvironment.facePlayer(argument)) {
            this->currEnvironment.removePlayerEnergy(command.getEnergyCost());
            this->currEnvironment.playerLook(); // update units seen
        }
        return;
    }
    else if (command.getName().compare("inquire") == 0) {
        if (argument.compare("unit") == 0) {
            std::cout << "To see your current unit codex use \"inquire unit=codex.\" To inquire a "
                "specific unit use \"inquire unit='#'\" where '#' is either an integer indicating "
                "which seen unit to inquire or the name of the unit in your codex. Note incomplete "
                "information may be shown if you can't entirely remember the unit.\n\n";
            return;
        }
        else if (core_functions::parseString(argument, "=").at(0).compare("unit") == 0) {
            if (core_functions::parseString(argument, "=").size() < 2) {
                std::cout << "Invalid inquire argument. See \"help inquire.\"";
                return;
            }
            std::string parsedArgument{ core_functions::toLower(core_functions::parseString(argument, "=").at(1)) };
            if (core_functions::isPositiveInteger(parsedArgument)) {
                if (this->currEnvironment.getUnitsSeen().size() == 0) {
                    std::cout << "You don't see any units.\n\n";
                    return;
                }
                int index = static_cast<int>(stoul(parsedArgument) - 1);
                if ((index < 0) || (index >= this->currEnvironment.getUnitsSeen().size())) {
                    std::cout << "No unit seen with indice " << parsedArgument << ".\n\n";
                    return;
                }
                this->currEnvironment.setCurrKey(this->currEnvironment.getUnitsSeen().at(index));
                this->currEnvironment.getOtherUnits().at(this->currEnvironment.getCurrKey()).printUnitInfo();
                return;
            }
            else if (parsedArgument.compare("codex") == 0) {
                // display unit codex
                return;
            }
            else {
                std::cout << "Invalid inquire argument. See \"help inquire.\"\n";
                // check in unit codex
                return;
            }
        }
        else if (argument.compare("item") == 0) {
            std::cout << "To see your current item codex use \"inquire item=codex.\" To inquire a "
                "specific item use \"inquire item='#'\" where '#' is either the integer indicating "
                "which seen item to inquire or the item name from your codex. To inquire items in "
                "your inventory use \"inquire inventory.\" Note incomplete information may be "
                "shown if you can't entirely remember the item.\n\n";
            return;
        }
        else if (core_functions::parseString(argument, "=").at(0).compare("item") == 0) {
            if (core_functions::parseString(argument, "=").size() < 2) {
                std::cout << "Invalid inquire argument. See \"help inquire.\"";
                return;
            }
            std::string parsedArgument{ core_functions::toLower(core_functions::parseString(argument, "=").at(1)) };
            if (core_functions::isPositiveInteger(parsedArgument)) {
                if (this->currEnvironment.getItemsSeen().size() == 0) {
                    std::cout << "You don't see any items.\n\n";
                    return;
                }
                int index = static_cast<int>(stoul(parsedArgument) - 1);
                if ((index < 0) || (index >= this->currEnvironment.getItemsSeen().size())) {
                    std::cout << "No item seen with indice " << parsedArgument << ".\n\n";
                    return;
                }
                this->currEnvironment.setCurrKey(this->currEnvironment.getItemsSeen().at(index));
                this->currEnvironment.getDroppedItems().at(this->currEnvironment.getCurrKey()).printItemInfo();
                return;
            }
            else if (parsedArgument.compare("codex") == 0) {
                // display item codex
                return;
            }
            else {
                std::cout << "Invalid inquire argument. See \"help inquire.\"\n";
                // check in item codex
                return;
            }
        }
        else if (argument.compare("inventory") == 0) {
            std::cout << "Use \"inquire inventory='item'\" to inquire about a specific item in your "
                "inventory.\nFor example, use \"inquire inventory=weapon\" to inquire your weapon and "
                "\"inquire inventory=2\" to inquire the item in slot 2 of your inventory.\nNote for "
                "equipped gear you can drop 'inventory=' so using \"inquire weapon\" also works.\n\n";
            return;
        }
        else if (core_functions::parseString(argument, "=").at(0).compare("inventory") == 0) {
            std::vector<std::string> parsedArgument{ core_functions::parseString(argument, "=") };
            if (parsedArgument.size() < 2) {
                std::cout << "Invalid inquire argument. See \"help inquire.\"\n\n";
                return;
            }
            if (!core_functions::isPositiveInteger(parsedArgument.at(1))) {
                if (parsedArgument.at(1).compare("weapon")) {
                    if (this->currEnvironment.getPlayer().getWeapon().getID() == -1) {
                        std::cout << "No weapon equipped.\n\n";
                    }
                    else {
                        this->currEnvironment.getPlayer().getWeapon().printItemInfo();
                    }
                    return;
                }
                else if (parsedArgument.at(1).compare("offhand")) {
                    if (this->currEnvironment.getPlayer().getOffhand().getID() == -1) {
                        std::cout << "No offhand equipped.\n\n";
                    }
                    else {
                        this->currEnvironment.getPlayer().getOffhand().printItemInfo();
                    }
                    return;
                }
                else if (parsedArgument.at(1).compare("twohand")) {
                    if (this->currEnvironment.getPlayer().getTwohand().getID() == -1) {
                        std::cout << "No twohand equipped.\n\n";
                    }
                    else {
                        this->currEnvironment.getPlayer().getTwohand().printItemInfo();
                    }
                    return;
                }
                else if (parsedArgument.at(1).compare("headgear")) {
                    if (this->currEnvironment.getPlayer().getHeadgear().getID() == -1) {
                        std::cout << "No headgear equipped.\n\n";
                    }
                    else {
                        this->currEnvironment.getPlayer().getHeadgear().printItemInfo();
                    }
                    return;
                }
                else if (parsedArgument.at(1).compare("chestgear")) {
                    if (this->currEnvironment.getPlayer().getChestgear().getID() == -1) {
                        std::cout << "No chestgear equipped.\n\n";
                    }
                    else {
                        this->currEnvironment.getPlayer().getChestgear().printItemInfo();
                    }
                    return;
                }
                else if (parsedArgument.at(1).compare("leggear")) {
                    if (this->currEnvironment.getPlayer().getLeggear().getID() == -1) {
                        std::cout << "No leggear equipped.\n\n";
                    }
                    else {
                        this->currEnvironment.getPlayer().getLeggear().printItemInfo();
                    }
                    return;
                }
                else if (parsedArgument.at(1).compare("footgear")) {
                    if (this->currEnvironment.getPlayer().getFootgear().getID() == -1) {
                        std::cout << "No footgear equipped.\n\n";
                    }
                    else {
                        this->currEnvironment.getPlayer().getFootgear().printItemInfo();
                    }
                    return;
                }
                else if (parsedArgument.at(1).compare("accessory")) {
                    std::cout << "Use \"inquire accessory'#'\" to inquire a specific accessory slot.\n\n";
                    return;
                }
                else if (parsedArgument.at(1).compare("accessory1")) {
                    if (this->currEnvironment.getPlayer().getAccessory1().getID() == -1) {
                        std::cout << "No accessory equipped in slot 1.\n\n";
                    }
                    else {
                        this->currEnvironment.getPlayer().getAccessory1().printItemInfo();
                    }
                    return;
                }
                else if (parsedArgument.at(1).compare("accessory2")) {
                    if (this->currEnvironment.getPlayer().getAccessory2().getID() == -1) {
                        std::cout << "No accessory equipped in slot 2.\n\n";
                    }
                    else {
                        this->currEnvironment.getPlayer().getAccessory2().printItemInfo();
                    }
                    return;
                }
                else if (parsedArgument.at(1).compare("accessory3")) {
                    if (this->currEnvironment.getPlayer().getAccessory3().getID() == -1) {
                        std::cout << "No accessory equipped in slot 3.\n\n";
                    }
                    else {
                        this->currEnvironment.getPlayer().getAccessory3().printItemInfo();
                    }
                    return;
                }
                else if (parsedArgument.at(1).compare("accessory4")) {
                    if (this->currEnvironment.getPlayer().getAccessory4().getID() == -1) {
                        std::cout << "No accessory equipped in slot 4.\n\n";
                    }
                    else {
                        this->currEnvironment.getPlayer().getAccessory4().printItemInfo();
                    }
                    return;
                }
                else {
                    std::cout << "Invalid inquire argument. See \"help inquire.\"\n\n";
                    return;
                }
            }
            else {
                if (this->currEnvironment.getPlayer().getInventory().size() == 0) {
                    std::cout << "Inventory empty.\n\n";
                    return;
                }
                int index = static_cast<int>(stoul(parsedArgument.at(1)) - 1);
                if ((index < 0) || (index >= this->currEnvironment.getPlayer().getInventory().size())) {
                    std::cout << "No item in inventory with indice " << parsedArgument.at(1) << ".\n\n";
                    return;
                }
                this->currEnvironment.getPlayer().getInventory().at(index).printItemInfo();
                return;
            }
        }
        else if (argument.compare("weapon") == 0) {
            if (this->currEnvironment.getPlayer().getWeapon().getID() == -1) {
                std::cout << "No weapon equipped.\n\n";
            }
            else {
                this->currEnvironment.getPlayer().getWeapon().printItemInfo();
            }
            return;
        }
        else if (argument.compare("offhand") == 0) {
            if (this->currEnvironment.getPlayer().getOffhand().getID() == -1) {
                std::cout << "No offhand equipped.\n\n";
            }
            else {
                this->currEnvironment.getPlayer().getOffhand().printItemInfo();
            }
            return;
        }
        else if (argument.compare("twohand") == 0) {
            if (this->currEnvironment.getPlayer().getTwohand().getID() == -1) {
                std::cout << "No twohand equipped.\n\n";
            }
            else {
                this->currEnvironment.getPlayer().getTwohand().printItemInfo();
            }
            return;
        }
        else if (argument.compare("headgear") == 0) {
            if (this->currEnvironment.getPlayer().getHeadgear().getID() == -1) {
                std::cout << "No headgear equipped.\n\n";
            }
            else {
                this->currEnvironment.getPlayer().getHeadgear().printItemInfo();
            }
            return;
        }
        else if (argument.compare("chestgear") == 0) {
            if (this->currEnvironment.getPlayer().getChestgear().getID() == -1) {
                std::cout << "No chestgear equipped.\n\n";
            }
            else {
                this->currEnvironment.getPlayer().getChestgear().printItemInfo();
            }
            return;
        }
        else if (argument.compare("leggear") == 0) {
            if (this->currEnvironment.getPlayer().getLeggear().getID() == -1) {
                std::cout << "No leggear equipped.\n\n";
            }
            else {
                this->currEnvironment.getPlayer().getLeggear().printItemInfo();
            }
            return;
        }
        else if (argument.compare("footgear") == 0) {
            if (this->currEnvironment.getPlayer().getFootgear().getID() == -1) {
                std::cout << "No footgear equipped.\n\n";
            }
            else {
                this->currEnvironment.getPlayer().getFootgear().printItemInfo();
            }
            return;
        }
        else if (argument.compare("accessory") == 0) {
            std::cout << "Use \"inquire accessory'#'\" to inquire a specific accessory slot.\n\n";
            return;
        }
        else if (argument.compare("accessory1") == 0) {
            if (this->currEnvironment.getPlayer().getAccessory1().getID() == -1) {
                std::cout << "No accessory equipped in slot 1.\n\n";
            }
            else {
                this->currEnvironment.getPlayer().getAccessory1().printItemInfo();
            }
            return;
        }
        else if (argument.compare("accessory2") == 0) {
            if (this->currEnvironment.getPlayer().getAccessory2().getID() == -1) {
                std::cout << "No accessory equipped in slot 2.\n\n";
            }
            else {
                this->currEnvironment.getPlayer().getAccessory2().printItemInfo();
            }
            return;
        }
        else if (argument.compare("accessory3") == 0) {
            if (this->currEnvironment.getPlayer().getAccessory3().getID() == -1) {
                std::cout << "No accessory equipped in slot 3.\n\n";
            }
            else {
                this->currEnvironment.getPlayer().getAccessory3().printItemInfo();
            }
            return;
        }
        else if (argument.compare("accessory4") == 0) {
            if (this->currEnvironment.getPlayer().getAccessory4().getID() == -1) {
                std::cout << "No accessory equipped in slot 4.\n\n";
            }
            else {
                this->currEnvironment.getPlayer().getAccessory4().printItemInfo();
            }
            return;
        }
        else if (argument.compare("codex") == 0) {
            std::cout << "Your codex is where you store all your memories. To display your codex use "
                "\"inquire codex='argument'\" where 'argument' is one of 'unit,' 'item,' 'ability,' "
                "or 'status.' To inquire information on a specific use \"inquire argument=specific.\""
                " For example, \"inquire unit=Blackworm\" will inquire what you know about the "
                "Blackworm unit. Note the specific name of the unit, item, ability, or status is not "
                "case sensitive.\n\n";
            return;
        }
        else if (core_functions::parseString(argument, "=").at(0).compare("codex") == 0) {
            if (core_functions::parseString(argument, "=").size() < 2) {
                std::cout << "Invalid inquire argument. See \"help inquire.\"\n\n";
                return;
            }
            std::string parsedArgument{ core_functions::toLower(core_functions::parseString(argument, "=").at(1)) };
            if (parsedArgument.compare("unit") == 0) {
                // display unit codex
                return;
            }
            else if (parsedArgument.compare("item") == 0) {
                // display item codex
                return;
            }
            else if (parsedArgument.compare("ability") == 0) {
                // display ability codex
                return;
            }
            else if (parsedArgument.compare("status") == 0) {
                // display status codex
                return;
            }
            else {
                std::cout << "Invalid inquire argument. See \"help inquire.\"\n\n";
                return;
            }
            return;
        }
        else {
            std::cout << "Use \"inquire 'argument'\" where 'argument' is 'unit', 'item', 'inventory', "
                "or 'codex' to inquire about one of these.\n\n";
            return;
        }
        return;
    }
    else if (command.getName().compare("ascend") == 0) {
        std::cout << "You will ascend into the next dimension. Confirm by typing 'yes'\n";
        std::string answer{};
        std::getline(std::cin >> std::ws, answer);
        if (answer.compare("yes") == 0) {
            std::cout << "You are ascending into the next dimension ... ";
            core_functions::pauseProgram(constants::normalPauseTime);
            this->nextLevel();
        }
        else {
            std::cout << "Not confirmed.\n\n";
        }
        return;
    }

    // Editor commands (not in final game)
    else if (command.getName().compare("levelup") == 0) {
        int numberOfLevelUps{ 1 };
        if (core_functions::isPositiveInteger(argument)) {
            numberOfLevelUps = stoul(argument);
        }
        while (numberOfLevelUps > 0) {
            this->playerRewards(core_functions::xpForNextLevel(this->currEnvironment.getPlayer().getLevel()) -
                this->currEnvironment.getPlayer().getExperience(), 0, 0);
            numberOfLevelUps--;
        }
        return;
    }

    std::cout << "ERROR: command name " << command.getName() << " not found in command reference.\n\n";
}

// The checks that must be done after each iteration of giving a command
void Game::iterationChecks() {
    if (!this->inEnvironment) {
        if (this->currBattle.getBattleOver()) { // if battle over
            this->currBattle.printBattleInfo();
            this->exitBattle();
        }
        else {
            this->currBattle.printBattleInfo();
        }
    }
    // check achievements and quests
    this->checkAchievements();
    this->checkIntersections();
    if (this->inEnvironment) {
        this->currEnvironment.checkQuestCompletion();
        this->checkIntersections();
    }
}

// Check to ensure no duplicate commands added
void Game::addCommands(std::vector<std::string> commandNames) {
    for (std::string commandName : commandNames) {
        this->addCommand(commandName);
    }
}
void Game::addCommand(std::string commandName) {
    bool addCommand = true;
    for (Command command : this->currCommands) {
        if (command.getName().compare(commandName) == 0) {
            addCommand = false;
            break;
        }
    }
    if (addCommand) {
        this->currCommands.push_back(Command(commandName));
    }
}
void Game::addCommand(Command command) {
    bool addCommand = true;
    for (Command i : this->currCommands) {
        if (i.getName().compare(command.getName()) == 0) {
            addCommand = false;
            break;
        }
    }
    if (addCommand) {
        this->currCommands.push_back(command);
    }
}

// To add achievements to current achievements
void Game::addAchievements(std::vector<std::string> achievementNames) {
    for (std::string i : achievementNames) {
        this->addAchievement(i);
    }
}
void Game::addAchievement(std::string achievementName) {
    bool added = true;
    for (Achievement i : this->currAchievements) {
        if (i.getName().compare(achievementName) == 0) {
            added = false;
            break;
        }
    }
    if (added) {
        this->currAchievements.push_back(Achievement(achievementName));
    }
}

// Update achievements
void Game::checkAchievements() {
    if (this->inEnvironment) {
        for (size_t i = 0; i < this->currAchievements.size(); i++) {
            if (this->currAchievements.at(i).checkCondition(this->currEnvironment.getPlayer())) {
                this->currAchievements.at(i).meetCondition(this->currEnvironment, this->currAchievements);
                this->checkIntersections();
                std::cout << "\n";
                this->currEnvironment.completedAchievement(this->currAchievements.at(i));
                this->currAchievements.erase(this->currAchievements.begin() + i);
                i--;
            }
        }
    }
}

void Game::nextMainStoryChapter(int storyChapter) {
    double shortPauseTime{ constants::shortPauseTime };
    double normalPauseTime{ constants::normalPauseTime };
    double longPauseTime{ constants::longPauseTime };
    core_functions::flushScreen();

    switch (storyChapter) {
        case 0: // prologue
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "  ++++++++++++++++++++++++++++++\n";
            std::cout << "  ++++++++++ Prologue ++++++++++\n";
            std::cout << "  ++++++++++++++++++++++++++++++\n";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\nWe know our perception is limited.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nWe know our knowledge is incomplete.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nWhat is true is often not seen.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nAnd what is seen is often not true.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nPerhaps,";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " we know much less than we would like to believe.";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\n\nOur story begins with a being from another dimension.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nA dimension less limited than our fragile existence.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nOne with more possibility of growth, development, and beauty.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nBut with more possibility comes more contingency.";
            core_functions::pauseProgram(normalPauseTime);
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\nAnd with more contingency comes more opportunity for decay.";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\n\nOur being was,";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " in a sense,";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " nothing special.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nIn isolation he had no characteristics distinguishing him from the beings around him.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nAnd perhaps in the abstract another could easily take his place.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nBut we are not just the sum of our characteristics;";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << " we are the sum of our experiences.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nOne might call it fate, providence, or destiny.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nBut even we seem to know our subsistence cannot escape circumstance.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThe protagonist of our story is no exception.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nSome may call him a victim of circumstance.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nBut,";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " maybe he was the beneficiary of circumstance.";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\n\nOur friend may have been devoid of extraordinary traits in his world,";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nbut compared to us his potential was immeasurable.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nUnlike us,";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " his only limitation in our universe was his biological form.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nHis puny brain could never form the thoughts his former self understood so clearly.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThis limitation proved integral to his initial time on Earth.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nNo human would ever have a second thought regarding him or his...";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << " well,";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " destiny.";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\n\nHow did he find himself in our universe?";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThis is a question he could never answer.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nHe had no mental capacity to form the question...";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\nuntil now.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "...";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nWhere am I?";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI feel like I've been here my whole life.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nAnd yet my life does not feel like my own.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nWho am I?";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI feel like nothing more than the frog I look like.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nAnd yet my body does not feel like my own.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI've lived the life of a frog.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nWhy am I only now able to see it?";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThere must be more to see.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\n\n";
            break;

        case 1: // Dimension 1
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            std::cout << "  ++++++++++ Dimension 1 ++++++++++\n";
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\nPeople are afraid of what they don't know.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nEven our most prestigious scientists and thinkers are afraid of not knowing.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nActually,";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " them most of all.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThey want to believe everything they perceive as some kind of final truth;";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nor they claim with great confidence that knowing is simply beyond them.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nOf course the truth is somewhere in the middle.";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\n\nIt is quite elementary to demonstrate how we can know so much about our world.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nBut still know so little.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nAll we need is a simple lesson in geometry.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\n\nImagine what we know is a line on the plane of knowledge.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nWe cannot know anything this line of ours doesn't intersect.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nWe can weave this line back and forth all over the plane.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nBut it will always be just a line,";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " stuck in the first dimension of knowledge.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nOther lines may or may not intersect us.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nBut when they do it is only at a single point.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nLiterally nothing compared to the rest of the line.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nJust an irreproducible exception against the empirical weight of all science, observation, and thought.";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\n\nThis line may or may not be bound to the one plane.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nIt may be bound by some higher-order object.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nOr perhaps it is not.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nRegardless, even without constraints it is merely a line.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nHowever far it reaches will be insufficient to even fathom the higher dimension it is in.";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\n\nIf you think what we know is something like this line.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nYou would be wrong.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nWhat we know is exactly like this line.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "...";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nWhy do I keep getting these weird thoughts in my head?";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nIt's almost like someone is talking to me.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nOr I've just gone entirely mad.";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\n\nI know I'm not like these other creatures in this aquarium.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI guess this means I'm not a normal frog.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThese creatures have no thought.";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " They have no knowledge.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nWhatever my schizophrenic side tells me,";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI at least know infinitely more than these poor creatures.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nA line is still more than nothing.";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\n\nI need to get out of here.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI need to escape this aquarium.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nActually,";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " I need to escape this body.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI feel like all I can access with this body are points.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nAnd even these only come with experience and difficulty.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nBut my mind can access a whole dimension of knowledge.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI need more points.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI need more experience.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\n\n";
            break;

        case 2: // Dimension 2
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            std::cout << "  ++++++++++ Dimension 2 ++++++++++\n";
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\nRemember the analogy of the line and the plane?";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nHow the line is like the material limitation of the being's knowledge.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThe plane was bounding the line to some other, higher dimension.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThe plane doesn't have to be a plane.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nIt could be multiple dimensions higher.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nPerhaps infinite.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nRegardless,";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " whatever dimension the plane really is,";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << " we should know it is some higher limitation on what that being can know.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nIt is drawing the being to itself.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nIt is drawing the being to what that being truly is.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nIts destiny.";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\n\nWhy bore you with all this?";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI must relate quite a vital piece of information.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nOne might think a line bound by a plane can intersect with other lines easier.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nAfter all,";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << " there are many ways to make 2 lines intersect in a plane.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nWhereas 2 lines bound by some higher-dimensional object can easily pass by each other without even being parallel.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThis thought would be incorrect.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThe larger the dimensional difference between the line and the plane,";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nthe more intersections to higher dimensions of knowledge that being can find.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThen as the being is closer to the plane's dimension,";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nit requires significantly more time and experience to find these intersections.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nBut those intersections will always be there.";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "...";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nThese daydreams seem to be regular.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nIt's almost like someone,";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << " or something,";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << " is trying to instruct me.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nSomeone from a higher dimension?";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\n\nIt's funny how in such a short period of time,";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI went from being a fat, lazy frog with no dimension of knowledge,";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\na frog kept as a pet in an aquarium full of other mindless creatures...";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\n...to accessing a dimension of knowledge my owner could never experience.";
            core_functions::pauseProgram(longPauseTime);
            std::cout << "\nAnd yet,";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << " I feel compelled to experience more.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI have this conviction that even this dimension is not who I am.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nI am even greater.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\n\n";
            break;

        case 3: // Dimension 3
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            std::cout << "  ++++++++++ Dimension 3 ++++++++++\n";
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nasdf.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nasdf.";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "...";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nasdf.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\n\n";
            break;

        case 4: // Dimension 4
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            std::cout << "  ++++++++++ Dimension 4 ++++++++++\n";
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nasdf.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nasdf.";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "...";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nasdf.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\n\n";
            break;

        case 5: // Dimension 5
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            std::cout << "  ++++++++++ Dimension 5 ++++++++++\n";
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            std::cout << "  +++++++++++++++++++++++++++++++++\n";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nasdf.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nasdf.";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "\n";
            core_functions::pauseProgram(shortPauseTime);
            std::cout << "...";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\nasdf.";
            core_functions::pauseProgram(normalPauseTime);
            std::cout << "\n\n";
            break;

        default:
            std::cout << "ERROR: Story chapter " << storyChapter << " not found.\n";
            break;
    }
    
    core_functions::requireEnter();
    core_functions::flushScreen();
}

// Options menu
void Game::optionsMenu() {
    std::cout << "Welcome to the options menu. To return to game use \"exit\", to restore defaults "
        "use \"defaults\", and For help use \"help\".";
    while (true) {
        std::string input{ core_functions::getInputString("\n\n", false)};
        if (input.compare("exit") == 0) {
            std::cout << "\n\n";
            return;
        }
        else if (input.compare("defaults") == 0) {
            std::cout << "Restored default options.";
            this->autoSave = 0;
            this->timeLengths = 1.0;
            core_functions::timeLengths = 1.0;
            continue;
        }
        else if (input.compare("help") == 0) {
            std::cout << "To return to the game use \"exit\".\nTo change an option use the format "
                "\"optionName=value\" where \"optionName\" is the option to change and \"value\" is"
                " the value to change it to.\nBelow is a list of options to change:\n";
            std::cout << "\"Autosave\" : 0 = manual save, 1 = save after quest completion / ascension / etc., 2 = save after each command (WARNING: likely to cause lag)";
            std::cout << "\"TimeLengths\" : none = no wait times, short = half wait times, default = normal wait times, long = increased wait times.";
        }
        else {
            std::vector<std::string> parsedInput{ core_functions::parseString(input, "=")};
            bool badInput{ false };
            if (parsedInput.at(0).compare("Autosave") == 0) {
                if (core_functions::isPositiveInteger(parsedInput.at(1))) {
                    if (static_cast<int>(stoul(parsedInput.at(1))) == 0) {
                        std::cout << "Set manual saving.";
                        this->autoSave = 0;
                        continue;
                    }
                    else if (static_cast<int>(stoul(parsedInput.at(1))) == 1) {
                        std::cout << "Set light auto saving.\nWarning: may cause lag.";
                        this->autoSave = 1;
                        continue;
                    }
                    else if (static_cast<int>(stoul(parsedInput.at(1))) == 2) {
                        std::cout << "Set heavy auto saving.\nWARNING: likely to cause lag.";
                        this->autoSave = 2;
                        continue;
                    }
                    else {
                        badInput = true;
                    }
                }
                else {
                    badInput = true;
                }
            }
            else if (parsedInput.at(0).compare("TimeLengths") == 0) {
                if (parsedInput.at(1).compare("none") == 0) {
                    std::cout << "Removed wait times.";
                    this->timeLengths = 0.0;
                    core_functions::timeLengths = 0.0;
                    continue;
                }
                else if (parsedInput.at(1).compare("short") == 0) {
                    std::cout << "Set short wait times.";
                    this->timeLengths = 0.5;
                    core_functions::timeLengths = 0.5;
                    continue;
                }
                else if (parsedInput.at(1).compare("default") == 0) {
                    std::cout << "Set default wait times.";
                    this->timeLengths = 1.0;
                    core_functions::timeLengths = 1.0;
                    continue;
                }
                else if (parsedInput.at(1).compare("long") == 0) {
                    std::cout << "Set long wait times.";
                    this->timeLengths = 1.5;
                    core_functions::timeLengths = 1.5;
                    continue;
                }
                else {
                    badInput = true;
                }
            }
            else {
                badInput = true;
            }
            if (badInput) {
                std::cout << "No valid input.";
            }
            continue;
        }
    }
}

// 73939133 is the largest right-truncatable prime number and the code for the dimension 4 easter egg
void Game::saveGame() {
    this->saveGame(static_cast<std::string>(constants::savedGameFolderName) + "/" +
        this->currEnvironment.getPlayer().getName() + "/");
}
void Game::saveGame(std::string savedGameFolderName) {
    core_functions::pauseProgram(constants::shortPauseTime);
    std::string folderPath{ savedGameFolderName };
    // game file
    std::ofstream gameFile{ folderPath + static_cast<std::string>(constants::gameFileName), std::ios::trunc };
    gameFile << "The code is 7#######\n";
    gameFile << "*STARTFILE\n";
    gameFile << "inEnvironment=" << this->inEnvironment << "\n";
    std::chrono::time_point programEndTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> epochTime = programEndTime.time_since_epoch();
    gameFile << "epochTime=" << epochTime.count() << "\n";
    gameFile << "autoSave=" << std::to_string(this->autoSave) << "\n";
    gameFile << "timeLengths=" << std::to_string(this->timeLengths) << "\n";
    gameFile.close();
    // environment file
    this->currEnvironment.saveGame(folderPath + static_cast<std::string>(constants::environmentFileName));
    // battle file
    if (!inEnvironment) {
        this->currBattle.saveGame(folderPath + static_cast<std::string>(constants::battleFileName));
    }
    // achievement file
    std::ofstream achievementFile{ folderPath + static_cast<std::string>(constants::achievementsFileName), std::ios::trunc };
    achievementFile << "*STARTFILE\n";
    for (Achievement i : this->currAchievements) {
        achievementFile << i.saveGame();
    }
    achievementFile.close();
    // commands file
    std::ofstream commandFile{ folderPath + static_cast<std::string>(constants::commandsFileName), std::ios::trunc };
    commandFile << "*STARTFILE\n";
    for (Command i : this->currCommands) {
        commandFile << i.saveGame();
    }
    commandFile.close();
}