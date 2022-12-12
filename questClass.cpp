/*
questClass.h
Quests are objectives with rewards the player can see. When the player achieves a quest it gets destroyed.
*/

#include <vector>

#include "questClass.h"
#include "environmentClass.h"
#include "unitClass.h"
#include "coreFunctions.h"

Quest::Quest(int ID) {
    this->ID = ID;
    switch (ID) {
        // Dimension I
        case 1:
            this->name = "There must be more to see I";
            this->description = "See 5 unique units or items.";
            this->rewards(8, 20, 1);
            break;
        case 2:
            this->name = "Hungry as a frog I";
            this->description = "Eat 5 units or items.";
            this->rewards(12, 25, 2);
            break;
        case 3:
            this->name = "There must be more to see II";
            this->description = "See 20 unique units or items.";
            this->rewards(25, 35, 3);
            break;
        case 4:
            this->name = "Find others I";
            this->description = "Find a conscious snail.";
            this->rewards(40, 50, 5);
            break;
        case 5:
            this->name = "Hungry as a frog II";
            this->description = "Eat 25 units or items.";
            this->rewards(45, 50, 5);
            break;
        case 6:
            this->name = "Hungry as a frog III";
            this->description = "Eat 75 units or items.";
            this->rewards(150, 120, 10);
            break;
        case 7:
            this->name = "There must be more to see III";
            this->description = "See 50 unique units or items.";
            this->rewards(150, 120, 10);
            break;
        case 8:
            this->name = "Find others II";
            this->description = "Find a conscious guppy.";
            this->rewards(75, 55, 8);
            break;
        case 9:
            this->name = "Kill enemies I";
            this->description = "Kill Blackworm.";
            this->rewards(50, 50, 5);
            break;
        case 10:
            this->name = "Find others III";
            this->description = "Find an African Dwarf Frog.";
            this->rewards(250, 200, 25);
            break;
        case 11:
            this->name = "Kill enemies II";
            this->description = "Kill Bloodworm.";
            this->rewards(200, 180, 20);
            break;
        case 12:
            this->name = "Kill enemies III";
            this->description = "Kill Worm Chief.";
            this->rewards(500, 300, 40);
            break;
        case 13:
            this->name = "Kill enemies IV";
            this->description = "Kill Rainbow Shark.";
            this->rewards(1500, 750, 60);
            break;

        // Dimension II
        case 101:
            this->name = "Find exit I";
            this->description = "Find the exit to this sewer.";
            this->rewards(6000, 2000, 100);
            break;
        case 102:
            this->name = "Find exit II";
            this->description = "Kill the creature guarding the sewer tunnel.";
            this->rewards(12000, 3500, 120);
            break;
        case 103:
            this->name = "Find exit III";
            this->description = "Find the exit to this sewer.";
            this->rewards(25000, 5000, 150);
            break;
        case 104:
            this->name = "Find exit IV";
            this->description = "Kill the ninja turtle guarding the exit.";
            this->rewards(50000, 7500, 200);
            break;

        default:
            std::cout << "ERROR: Quest ID " << ID << " not found.\n";
            break;
    }
}

// set rewards
void Quest::rewards(int xp, int credit, int foul) {
    this->xpReward = xp;
    this->creditReward = credit;
    this->foulReward = foul;
}

 // return true/false
bool Quest::checkCondition(Environment* currentEnvironment) {
    bool conditionMet{ false };
    switch (this->ID) {
        case 1:
            if (currentEnvironment->getUniqueThingsSeen() >= 5) {
                conditionMet = true;
            }
            break;
        case 2:
            if (currentEnvironment->getThingsEaten() >= 5) {
                conditionMet = true;
            }
            break;
        case 3:
            if (currentEnvironment->getUniqueThingsSeen() >= 20) {
                conditionMet = true;
            }
            break;
        case 4:
            if (currentEnvironment->hasSeenUnit(502)) {
                conditionMet = true;
            }
            break;
        case 5:
            if (currentEnvironment->getThingsEaten() >= 25) {
                conditionMet = true;
            }
            break;
        case 6:
            if (currentEnvironment->getThingsEaten() >= 75) {
                conditionMet = true;
            }
            break;
        case 7:
            if (currentEnvironment->getUniqueThingsSeen() >= 50) {
                conditionMet = true;
            }
            break;
        case 8:
            if (currentEnvironment->hasSeenUnit(503)) {
                conditionMet = true;
            }
            break;
        case 9:
            if (currentEnvironment->hasKilledUnit(12)) {
                conditionMet = true;
            }
            break;
        case 10:
            if (currentEnvironment->hasSeenUnit(47)) {
                conditionMet = true;
            }
            break;
        case 11:
            if (currentEnvironment->hasKilledUnit(22)) {
                conditionMet = true;
            }
            break;
        case 12:
            if (currentEnvironment->hasKilledUnit(49)) {
                conditionMet = true;
            }
            break;
        case 13:
            if (currentEnvironment->hasKilledUnit(48)) {
                conditionMet = true;
            }
            break;

        // Dimension II
        case 101:
            if ((currentEnvironment->getCurrArea() > 20) && (currentEnvironment->getCurrArea() < 28)) {
                conditionMet = true;
            }
            break;
        case 102:
            if ((currentEnvironment->hasKilledUnit(87)) || (currentEnvironment->hasKilledUnit(88))) {
                conditionMet = true;
            }
            break;
        case 103:
            if (currentEnvironment->getCurrArea() >= 45) {
                conditionMet = true;
            }
            break;
        case 104:
            if (currentEnvironment->hasKilledUnitKey(2)) {
                conditionMet = true;
            }
            break;
        
        default:
            std::cout << "ERROR: Quest ID " << this->ID << " not found in condition reference.\n";
            break;
    }
    return conditionMet;
}

 // return rewards for environment
std::vector<int> Quest::meetCondition() {
    std::cout << "\nQuest Complete!";
    core_functions::pauseProgram(constants::shortPauseTime);
    std::cout << "\n" << this->name << ": " << this->description << "\n";
    return { this->xpReward, this->creditReward, this->foulReward };
}

// print quest information
void Quest::printQuest() {
    std::cout << this->name << ": " << this->description << "\n";
}
void Quest::printQuestProgress(Environment* currentEnvironment, int largestName) {
    std::cout << this->name << ": " << core_functions::stringMultiply(" ", largestName - this->name.size());
    switch (this->ID) {
        // Dimension I
        case 1:
            std::cout << "See " << currentEnvironment->getUniqueThingsSeen() << "/5 unique units or items.";
            break;
        case 2:
            std::cout << "Eat " << currentEnvironment->getThingsEaten() << "/5 units or items.";
            break;
        case 3:
            std::cout << "See " << currentEnvironment->getUniqueThingsSeen() << "/20 unique units or items.";
            break;
        case 4:
            std::cout << "Find a conscious snail.";
            break;
        case 5:
            std::cout << "Eat " << currentEnvironment->getThingsEaten() << "/25 units or items.";
            break;
        case 6:
            std::cout << "Eat " << currentEnvironment->getThingsEaten() << "/75 units or items.";
            break;
        case 7:
            std::cout << "See " << currentEnvironment->getUniqueThingsSeen() << "/50 unique units or items.";
            break;
        case 8:
            std::cout << "Find a conscious guppy.";
            break;
        case 9:
            std::cout << "Kill Blackworm.";
            break;
        case 10:
            std::cout << "Find an African Dwarf Frog.";
            break;
        case 11:
            std::cout << "Kill Bloodworm.";
            break;
        case 12:
            std::cout << "Kill Worm Chief.";
            break;
        case 13:
            std::cout << "Kill Rainbow Shark.";
            break;

        // Dimension II
        case 101:
            std::cout << "Find the exit to this sewer.";
            break;
        case 102:
            std::cout << "Kill the creature guarding the sewer tunnel.";
            break;
        case 103:
            std::cout << "Find the exit to this sewer.";
            break;
        case 104:
            std::cout << "Kill the ninja turtle guarding the exit.";
            break;

        default:
            std::cout << "ERROR: Quest ID " << ID << " not found.\n";
            break;
    }
    std::cout << "\n";
}

// Return string for saved game files
std::string Quest::saveGame() {
    std::string fileString{};
    fileString += "*DEFINE=Quest\n";
    fileString += "ID=" + std::to_string(this->ID) + "\n";
    fileString += "*END\n";
    return fileString;
}