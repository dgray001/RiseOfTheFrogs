/*
achievementClass.cpp
Achievements are unseen (until completed) objectives which are never destroyed.
*/

#include <iostream>
#include <string>
#include <vector>

#include "achievementClass.h"
#include "environmentClass.h"
#include "unitClass.h"
#include "coreFunctions.h"
#include "constants.h"

Achievement::Achievement(std::string name) {
    this->name = name;
    if (name.compare("Monster Slayer I") == 0) {
        this->description = "Slay " + std::to_string(constants::achievementMonsterSlayerI) + " monsters.";
        this->xpReward = constants::achievementRewardExperienceI;
        this->creditReward = constants::achievementRewardCreditI;
        this->foulReward = constants::achievementRewardFoulI;
    }
    else if (name.compare("Monster Slayer II") == 0) {
        this->description = "Slay " + std::to_string(constants::achievementMonsterSlayerII) + " monsters.";
        this->xpReward = constants::achievementRewardExperienceII;
        this->creditReward = constants::achievementRewardCreditII;
        this->foulReward = constants::achievementRewardFoulII;
    }
    else if (name.compare("Monster Slayer III") == 0) {
        this->description = "Slay " + std::to_string(constants::achievementMonsterSlayerIII) + " monsters.";
        this->xpReward = constants::achievementRewardExperienceIII;
        this->creditReward = constants::achievementRewardCreditIII;
        this->foulReward = constants::achievementRewardFoulIII;
    }
    else if (name.compare("Monster Slayer IV") == 0) {
        this->description = "Slay " + std::to_string(constants::achievementMonsterSlayerIV) + " monsters.";
        this->xpReward = constants::achievementRewardExperienceIV;
        this->creditReward = constants::achievementRewardCreditIV;
        this->foulReward = constants::achievementRewardFoulIV;
    }
    else if (name.compare("Monster Slayer V") == 0) {
        this->description = "Slay " + std::to_string(constants::achievementMonsterSlayerV) + " monsters.";
        this->xpReward = constants::achievementRewardExperienceV;
        this->creditReward = constants::achievementRewardCreditV;
        this->foulReward = constants::achievementRewardFoulV;
    }
    else if (name.compare("Traveler I") == 0) {
        this->description = "Travel " + std::to_string(static_cast<int>(std::round(constants::achievementTravelerI * 100))) + " cm.";
        this->xpReward = constants::achievementRewardExperienceI;
        this->creditReward = constants::achievementRewardCreditI;
        this->foulReward = constants::achievementRewardFoulI;
    }
    else if (name.compare("Traveler II") == 0) {
        this->description = "Travel " + std::to_string(static_cast<int>(std::round(constants::achievementTravelerII))) + " m.";
        this->xpReward = constants::achievementRewardExperienceII;
        this->creditReward = constants::achievementRewardCreditII;
        this->foulReward = constants::achievementRewardFoulII;
    }
    else if (name.compare("Traveler III") == 0) {
        this->description = "Travel " + std::to_string(static_cast<int>(std::round(constants::achievementTravelerIII))) + " m.";
        this->xpReward = constants::achievementRewardExperienceIII;
        this->creditReward = constants::achievementRewardCreditIII;
        this->foulReward = constants::achievementRewardFoulIII;
    }
    else if (name.compare("Traveler IV") == 0) {
        this->description = "Travel " + std::to_string(static_cast<int>(std::round(constants::achievementTravelerIV))) + " m.";
        this->xpReward = constants::achievementRewardExperienceIV;
        this->creditReward = constants::achievementRewardCreditIV;
        this->foulReward = constants::achievementRewardFoulIV;
    }
    else if (name.compare("Traveler V") == 0) {
        this->description = "Travel " + std::to_string(static_cast<int>(std::round(constants::achievementTravelerV))) + " m.";
        this->xpReward = constants::achievementRewardExperienceV;
        this->creditReward = constants::achievementRewardCreditV;
        this->foulReward = constants::achievementRewardFoulV;
    }
    else if (name.compare("Consumer I") == 0) {
        this->description = "Consume " + std::to_string(constants::achievementConsumerI) + " items.";
        this->xpReward = constants::achievementRewardExperienceI;
        this->creditReward = constants::achievementRewardCreditI;
        this->foulReward = constants::achievementRewardFoulI;
    }
    else if (name.compare("Consumer II") == 0) {
        this->description = "Consume " + std::to_string(constants::achievementConsumerII) + " items.";
        this->xpReward = constants::achievementRewardExperienceII;
        this->creditReward = constants::achievementRewardCreditII;
        this->foulReward = constants::achievementRewardFoulII;
    }
    else if (name.compare("Consumer III") == 0) {
        this->description = "Consume " + std::to_string(constants::achievementConsumerIII) + " items";
        this->xpReward = constants::achievementRewardExperienceIII;
        this->creditReward = constants::achievementRewardCreditIII;
        this->foulReward = constants::achievementRewardFoulIII;
    }
    else if (name.compare("Consumer IV") == 0) {
        this->description = "Consume " + std::to_string(constants::achievementConsumerIV) + " items";
        this->xpReward = constants::achievementRewardExperienceIV;
        this->creditReward = constants::achievementRewardCreditIV;
        this->foulReward = constants::achievementRewardFoulIV;
    }
    else if (name.compare("Consumer V") == 0) {
        this->description = "Consume " + std::to_string(constants::achievementConsumerV) + " items";
        this->xpReward = constants::achievementRewardExperienceV;
        this->creditReward = constants::achievementRewardCreditV;
        this->foulReward = constants::achievementRewardFoulV;
    }
    else if (name.compare("Reckless") == 0) {
        this->description = "Run out of health or energy.";
        this->xpReward = constants::achievementRewardExperienceII;
        this->creditReward = constants::achievementRewardCreditII;
        this->foulReward = constants::achievementRewardFoulII;
    }
}
bool Achievement::checkCondition(Player thePlayer) {
    bool conditionMet{ false };
    if (name.compare("Monster Slayer I") == 0) {
        if (thePlayer.getMonstersSlain() >= constants::achievementMonsterSlayerI) {
            conditionMet = true;
        }
    }
    else if (name.compare("Monster Slayer II") == 0) {
        if (thePlayer.getMonstersSlain() >= constants::achievementMonsterSlayerII) {
            conditionMet = true;
        }
    }
    else if (name.compare("Monster Slayer III") == 0) {
        if (thePlayer.getMonstersSlain() >= constants::achievementMonsterSlayerIII) {
        }
    }
    else if (name.compare("Monster Slayer IV") == 0) {
        if (thePlayer.getMonstersSlain() >= constants::achievementMonsterSlayerIV) {
        }
    }
    else if (name.compare("Monster Slayer V") == 0) {
        if (thePlayer.getMonstersSlain() >= constants::achievementMonsterSlayerV) {
        }
    }
    else if (name.compare("Traveler I") == 0) {
        if (thePlayer.getDistanceTraveled() >= constants::achievementTravelerI) {
            conditionMet = true;
        }
    }
    else if (name.compare("Traveler II") == 0) {
        if (thePlayer.getDistanceTraveled() >= constants::achievementTravelerII) {
            conditionMet = true;
        }
    }
    else if (name.compare("Traveler III") == 0) {
        if (thePlayer.getDistanceTraveled() >= constants::achievementTravelerIII) {
            conditionMet = true;
        }
    }
    else if (name.compare("Traveler IV") == 0) {
        if (thePlayer.getDistanceTraveled() >= constants::achievementTravelerIV) {
            conditionMet = true;
        }
    }
    else if (name.compare("Traveler V") == 0) {
        if (thePlayer.getDistanceTraveled() >= constants::achievementTravelerV) {
            conditionMet = true;
        }
    }
    else if (name.compare("Consumer I") == 0) {
        if (thePlayer.getItemsConsumed() >= constants::achievementConsumerI) {
            conditionMet = true;
        }
    }
    else if (name.compare("Consumer II") == 0) {
        if (thePlayer.getItemsConsumed() >= constants::achievementConsumerII) {
            conditionMet = true;
        }
    }
    else if (name.compare("Consumer III") == 0) {
        if (thePlayer.getItemsConsumed() >= constants::achievementConsumerIII) {
            conditionMet = true;
        }
    }
    else if (name.compare("Consumer IV") == 0) {
        if (thePlayer.getItemsConsumed() >= constants::achievementConsumerIV) {
            conditionMet = true;
        }
    }
    else if (name.compare("Consumer V") == 0) {
        if (thePlayer.getItemsConsumed() >= constants::achievementConsumerV) {
            conditionMet = true;
        }
    }
    else if (name.compare("Reckless") == 0) {
        if ((thePlayer.getCurrEnergy() == 0) || (thePlayer.getCurrHealth() == 0)) {
            conditionMet = true;
        }
    }
    return conditionMet;
}
void Achievement::meetCondition(Environment& currentEnvironment, std::vector<Achievement>& currentPossibleAchievements) {
    std::cout << "\n--- Achievement Met! ---";
    core_functions::pauseProgram(constants::shortPauseTime);
    std::cout << "\n" << this->name << ": " << this->description << "\n";
    currentEnvironment.playerRewards(this->xpReward, this->creditReward, this->foulReward);
    if (name.compare("Monster Slayer I") == 0) {
        currentPossibleAchievements.push_back(Achievement("Monster Slayer II"));
    }
    else if (name.compare("Monster Slayer II") == 0) {
        currentPossibleAchievements.push_back(Achievement("Monster Slayer III"));
    }
    else if (name.compare("Monster Slayer III") == 0) {
        currentPossibleAchievements.push_back(Achievement("Monster Slayer IV"));
    }
    else if (name.compare("Monster Slayer IV") == 0) {
        currentPossibleAchievements.push_back(Achievement("Monster Slayer V"));
    }
    else if (name.compare("Traveler I") == 0) {
        currentPossibleAchievements.push_back(Achievement("Traveler II"));
    }
    else if (name.compare("Traveler II") == 0) {
        currentPossibleAchievements.push_back(Achievement("Traveler III"));
    }
    else if (name.compare("Traveler III") == 0) {
        currentPossibleAchievements.push_back(Achievement("Traveler IV"));
    }
    else if (name.compare("Traveler IV") == 0) {
        currentPossibleAchievements.push_back(Achievement("Traveler V"));
    }
    else if (name.compare("Consumer I") == 0) {
        currentPossibleAchievements.push_back(Achievement("Consumer II"));
    }
    else if (name.compare("Consumer II") == 0) {
        currentPossibleAchievements.push_back(Achievement("Consumer III"));
    }
    else if (name.compare("Consumer III") == 0) {
        currentPossibleAchievements.push_back(Achievement("Consumer IV"));
    }
    else if (name.compare("Consumer IV") == 0) {
        currentPossibleAchievements.push_back(Achievement("Consumer V"));
    }
    else if (this->name.compare("Reckless") == 0) {
        std::cout << "I remember I tucked a couple reptomin away for a situation like this.\n"
            "Just better make sure it doesn't happen again.\n";
        core_functions::pauseProgram(constants::shortPauseTime);
        currentEnvironment.addItem(Item(3, currentEnvironment.getPlayer().getLuckFactor(),
            currentEnvironment.getPlayer().getXLocation() + constants::smallDistance * currentEnvironment.getPlayer().getXFacing(),
            currentEnvironment.getPlayer().getYLocation() + constants::smallDistance * currentEnvironment.getPlayer().getYFacing(),
            currentEnvironment.getPlayer().getZLocation() + constants::smallDistance * currentEnvironment.getPlayer().getZFacing()));
        currentEnvironment.addItem(Item(3, currentEnvironment.getPlayer().getLuckFactor(),
            currentEnvironment.getPlayer().getXLocation() + constants::smallDistance * currentEnvironment.getPlayer().getXFacing(),
            currentEnvironment.getPlayer().getYLocation() + constants::smallDistance * currentEnvironment.getPlayer().getYFacing(),
            currentEnvironment.getPlayer().getZLocation() + constants::smallDistance * currentEnvironment.getPlayer().getZFacing()));
    }
    std::cout << "\n";
    core_functions::requireEnter();
}
void Achievement::printAchievement(int largestName) {
    std::cout << this->name << ": " << core_functions::stringMultiply(" ",
        largestName - this->name.size()) << this->description << "\n";
}

// Return save game string
std::string Achievement::saveGame() {
    std::string fileString{};
    fileString += "*DEFINE=Achievement\n";
    fileString += "*STRING=name\n" + this->name + "\n*END\n";
    // Name is unqiue identifier so only need that
    /*
    fileString += "*STRING=description\n" + this->description + "\n*END\n";
    fileString += "xpReward=" + std::to_string(this->xpReward) + "\n";
    fileString += "creditReward=" + std::to_string(this->creditReward) + "\n";
    fileString += "foulReward=" + std::to_string(this->foulReward) + "\n";
    */
    fileString += "*END\n";
    return fileString;
}