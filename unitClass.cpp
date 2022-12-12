/*
unitClass.cpp
The unit class creates units in the game. This includes the player, enemies, pets, and any future
unit I may include. For now the subclasses are not made.
*/

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include "unitClass.h"
#include "abilityClass.h"
#include "coreFunctions.h"
#include "itemClass.h"
#include "constants.h"
#include "battleClass.h"

// Base constructor
Unit::Unit(std::string name, int baseHealth, int baseAttack, int baseMagic, int baseDefense,
    int baseResist, int basePiercing, int basePenetration, int baseDexterity,
    double xLocation, double yLocation, double zLocation) {
    this->name = name;
    this->baseHealth = baseHealth;
    this->missingHealth = 0;
    this->baseAttack = baseAttack;
    this->baseMagic = baseMagic;
    this->baseDefense = baseDefense;
    this->baseResist = baseResist;
    this->basePiercing = basePiercing;
    this->basePenetration = basePenetration;
    this->baseDexterity = baseDexterity;
    if (baseHealth > 0) {
        this->status_alive = true;
    }
    else {
        this->status_alive = false;
    }
    this->xLocation = xLocation;
    this->yLocation = yLocation;
    this->zLocation = zLocation;
    this->addBattleAbility(Ability("nothing")); // only ability every unit must have
}

std::string Unit::getUnitColorString() {
    if (this->isColorless()) {
        return "colorless";
    }
    else if (this->isBlue()) {
        return "blue - water";
    }
    else if (this->isRed()) {
        return "red - fire";
    }
    else if (this->isBrown()) {
        return "brown - earth";
    }
    else if (this->isCyan()) {
        return "cyan - ice";
    }
    else if (this->isOrange()) {
        return "orange - air";
    }
    else if (this->isPurple()) {
        return "purple - gravity";
    }
    else if (this->isYellow()) {
        return "yellow - electricity";
    }
    else if (this->isMagenta()) {
        return "magenta - nuclear";
    }
    else if (this->isBlack()) {
        return "black - darkness";
    }
    else if (this->isWhite()) {
        return "white - light";
    }
    else if (this->isGreen()) {
        return "green - balance";
    }
    else {
        return "ERROR: unit color not found";
    }
}

// When player chooses a new color
void Unit::setUnitColorFromChoice(int x) {
    switch (x) {
        case 0:
            this->setUnitColor(static_cast<int>('c'));
            break;
        case 1:
            this->setUnitColor(static_cast<int>('w'));
            break;
        case 2:
            this->setUnitColor(static_cast<int>('f'));
            break;
        case 3:
            this->setUnitColor(static_cast<int>('e'));
            break;
        case 4:
            this->setUnitColor(static_cast<int>('i'));
            break;
        case 5:
            this->setUnitColor(static_cast<int>('a'));
            break;
        case 6:
            this->setUnitColor(static_cast<int>('g'));
            break;
        case 7:
            this->setUnitColor(static_cast<int>('z'));
            break;
        case 8:
            this->setUnitColor(static_cast<int>('n'));
            break;
        case 9:
            this->setUnitColor(static_cast<int>('d'));
            break;
        case 10:
            this->setUnitColor(static_cast<int>('l'));
            break;
        case 11:
            this->setUnitColor(static_cast<int>('b'));
            break;
        default:
            std::cout << "ERROR: Unit color from choice ID " << x << " not found.\n";
            break;
    }
}

double Unit::getLocation(int component) {
    if (component == 0) {
        return this->xLocation;
    }
    else if (component == 1) {
        return this->yLocation;
    }
    else if (component == 2) {
        return this->zLocation;
    }
    else {
        std::cout << "ERROR: unit " << this->name << " location component " << component << " not found.\n";
        return -1;
    }
}

// Set statuses that affect maxHealth since need to recalculate currHealth in these cases
void Unit::setStatusGrow(bool x) {
    if (x && !this->status_grow) {
        if (this->getMaxHealth() == 0) {
            std::cout << "ERROR: maxHealth is 0 for " << this->name << ".\n";
            return;
        }
        double healthRatio{ this->missingHealth / static_cast<double>(this->getMaxHealth()) };
        this->status_grow = true;
        this->setMissingHealth(static_cast<int>(std::round(healthRatio * this->getMaxHealth())));
    }
    else if (!x && this->status_grow) {
        int currHealth{ this->getCurrHealth() };
        this->status_grow = false;
        this->setMissingHealth(std::min(this->getMaxHealth() - 1, this->getMaxHealth() - currHealth));
    }
}
void Unit::setStatusEnlarge(bool x) {
    if (x && !this->status_enlarge) {
        if (this->getMaxHealth() == 0) {
            std::cout << "ERROR: maxHealth is 0 for " << this->name << ".\n";
            return;
        }
        double healthRatio{ this->missingHealth / static_cast<double>(this->getMaxHealth()) };
        this->status_enlarge = true;
        this->setMissingHealth(static_cast<int>(std::round(healthRatio * this->getMaxHealth())));
    }
    else if (!x && this->status_enlarge) {
        int currHealth{ this->getCurrHealth() };
        this->status_enlarge = false;
        this->setMissingHealth(std::min(this->getMaxHealth() - 1, this->getMaxHealth() - currHealth));
    }
}
void Unit::setStatusWilt(bool x) {
    if (x && !this->status_wilt) {
        if (this->getMaxHealth() == 0) {
            std::cout << "ERROR: maxHealth is 0 for " << this->name << ".\n";
            return;
        }
        double healthRatio{ this->missingHealth / static_cast<double>(this->getMaxHealth()) };
        this->status_wilt = true;
        this->setMissingHealth(std::min(this->getMaxHealth() - 1, static_cast<int>(std::round(healthRatio * this->getMaxHealth()))));
    }
    else if (!x && this->status_wilt) {
        int currHealth{ this->getCurrHealth() };
        this->status_wilt = false;
        this->setMissingHealth(this->getMaxHealth() - currHealth);
    }
}
void Unit::setStatusWither(bool x) {
    if (x && !this->status_wither) {
        if (this->getMaxHealth() == 0) {
            std::cout << "ERROR: maxHealth is 0 for " << this->name << ".\n";
            return;
        }
        double healthRatio{ this->missingHealth / static_cast<double>(this->getMaxHealth()) };
        this->status_wither = true;
        this->setMissingHealth(std::min(this->getMaxHealth() - 1, static_cast<int>(std::round(healthRatio * this->getMaxHealth()))));
    }
    else if (!x && this->status_wither) {
        int currHealth{ this->getCurrHealth() };
        this->status_wither = false;
        this->setMissingHealth(this->getMaxHealth() - currHealth);
    }
}

// Max health calculation
int Unit::getMaxHealth() {
    double result{ static_cast<double>(this->baseHealth) };
    if (this->status_grow) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->status_enlarge) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->status_wilt) {
        result *= constants::wiltConstant;
    }
    if (this->status_wither) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}

// Curr health calculation
int Unit::getCurrHealth() {
    int result{ this->getMaxHealth() - this->missingHealth };
    if (result < 0) {
        std::cout << "Unit Function\n"; // *****************
        std::cout << "ERROR: Negative " << result << " health for " << this->name << ". Set to 0.\n";
        this->missingHealth = this->getMaxHealth();
        result = 0;
    }
    return result;
}

// Current attack calculation
int Unit::getAttack() {
    double result{ static_cast<double>(this->baseAttack) };
    if (this->status_strength) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->status_beserk) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->status_weak) {
        result *= constants::minorStatusEffectNerf;
    }
    if (this->status_feeble) {
        result *= constants::majorStatusEffectNerf;
    }
    if (this->status_wilt) {
        result *= constants::wiltConstant;
    }
    if (this->status_wither) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}

// Current magic power calculation
int Unit::getMagic() {
    double result{ static_cast<double>(this->baseMagic) };
    if (this->status_cogent) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->status_potent) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->status_inept) {
        result *= constants::minorStatusEffectNerf;
    }
    if (this->status_impotent) {
        result *= constants::majorStatusEffectNerf;
    }
    if (this->status_wilt) {
        result *= constants::wiltConstant;
    }
    if (this->status_wither) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}

// Current defense calculation
int Unit::getDefense() {
    double result{ static_cast<double>(this->baseDefense) };
    if (this->status_defend) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->status_bulwark) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->status_broken) {
        result *= constants::minorStatusEffectNerf;
    }
    if (this->status_smashed) {
        result *= constants::majorStatusEffectNerf;
    }
    if (this->status_wilt) {
        result *= constants::wiltConstant;
    }
    if (this->status_wither) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}

// Current resistance calculation
int Unit::getResist() {
    double result{ static_cast<double>(this->baseResist) };
    if (this->status_resolve) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->status_dauntless) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->status_outwilled) {
        result *= constants::minorStatusEffectNerf;
    }
    if (this->status_shattered) {
        result *= constants::majorStatusEffectNerf;
    }
    if (this->status_wilt) {
        result *= constants::wiltConstant;
    }
    if (this->status_wither) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}

// Current defense piercing calculation
int Unit::getPiercing() {
    double result{ static_cast<double>(this->basePiercing) };
    if (this->status_wilt) {
        result *= constants::wiltConstant;
    }
    if (this->status_wither) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}

// Current magic penetration calculation
int Unit::getPenetration() {
    double result{ static_cast<double>(this->basePenetration) };
    if (this->status_wilt) {
        result *= constants::wiltConstant;
    }
    if (this->status_wither) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}

// Current dexterity calculation
int Unit::getDexterity() {
    double result{ static_cast<double>(this->baseDexterity) };
    if (this->status_swiftness) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->status_deftness) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->status_slow) {
        result *= constants::minorStatusEffectNerf;
    }
    if (this->status_lethargic) {
        result *= constants::majorStatusEffectNerf;
    }
    if (this->status_wilt) {
        result *= constants::wiltConstant;
    }
    if (this->status_wither) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}

// Reset status effects after battle
void Unit::resetStatusEffects() {
    this->setStatusGrow(false);
    this->setStatusEnlarge(false);
    this->status_strength = false;
    this->status_beserk = false;
    this->status_cogent = false;
    this->status_potent = false;
    this->status_defend = false;
    this->status_bulwark = false;
    this->status_resolve = false;
    this->status_dauntless = false;
    this->status_swiftness = false;
    this->status_deftness = false;
    // debuffs
    this->status_weak = false;
    this->status_feeble = false;
    this->status_inept = false;
    this->status_impotent = false;
    this->status_broken = false;
    this->status_smashed = false;
    this->status_outwilled = false;
    this->status_shattered = false;
    this->status_slow = false;
    this->status_lethargic = false;
    // colors
    this->status_bleed = false;
    this->status_hemorrhage = false;
    this->setStatusWilt(false);
    this->setStatusWither(false);
    this->status_drowning = false;
    this->status_drowned = false;
    this->status_burn = false;
    this->status_char = false;
    this->status_rot = false;
    this->status_decay = false;
    this->status_chill = false;
    this->status_freeze = false;
    this->status_infect = false;
    this->status_disease = false;
    this->status_shake = false;
    this->status_fall = false;
    this->status_shock = false;
    this->status_paralyze = false;
    this->status_unstable = false;
    this->status_radioactive = false;
    this->status_obscure = false;
    this->status_hide = false;
    this->status_bright = false;
    this->status_illuminate = false;
    //this->status_??? = false;
    //this->status_??? = false;
}

// Stat setter
void Unit::setUnitStats(int baseHealth, int baseAttack, int baseMagic, int baseDefense,
    int baseResist, int basePiercing, int basePenetration, int baseDexterity) {
    this->baseHealth = baseHealth;
    this->missingHealth = 0;
    this->baseAttack = baseAttack;
    this->baseMagic = baseMagic;
    this->baseDefense = baseDefense;
    this->baseResist = baseResist;
    this->basePiercing = basePiercing;
    this->basePenetration = basePenetration;
    this->baseDexterity = baseDexterity;
    if (baseHealth > 0) {
        this->status_alive = true;
    }
    else {
        this->status_alive = false;
    }
}
void Unit::setUnitStats(double lM, int baseHealth, int baseAttack, int baseMagic, int baseDefense,
    int baseResist, int basePiercing, int basePenetration, int baseDexterity) {
    this->baseHealth = static_cast<int>(std::floor(lM * baseHealth));
    this->missingHealth = 0;
    this->baseAttack = static_cast<int>(std::floor(lM * baseAttack));
    this->baseMagic = static_cast<int>(std::floor(lM * baseMagic));
    this->baseDefense = static_cast<int>(std::floor(lM * baseDefense));
    this->baseResist = static_cast<int>(std::floor(lM * baseResist));
    this->basePiercing = static_cast<int>(std::floor(lM * basePiercing));
    this->basePenetration = static_cast<int>(std::floor(lM * basePenetration));
    this->baseDexterity = static_cast<int>(std::floor(lM * baseDexterity));
    if (baseHealth > 0) {
        this->status_alive = true;
    }
    else {
        this->status_alive = false;
    }
}

// Manually set location of the unit
void Unit::setLocation(double xLoc, double yLoc, double zLoc) {
    this->xLocation = xLoc;
    this->yLocation = yLoc;
    this->zLocation = zLoc;
}
void Unit::setLocationComponent(double loc, int component) {
    if (component == 0) {
        this->xLocation = loc;
    }
    else if (component == 1) {
        this->yLocation = loc;
    }
    else if (component == 2) {
        this->zLocation = loc;
    }
    else {
        std::cout << "ERROR: component not valid for setting location for " << this->name << "\n";
    }
}

// Unit in an environment
void Unit::moveUnit(double dX, double dY, double dZ, double xLimit, double yLimit, double zLimit) {
    this->xLocation += dX;
    if (this->xLocation < 0) {
        this->xLocation = constants::smallDistance;
    }
    else if (this->xLocation > xLimit) {
        this->xLocation = xLimit - constants::smallDistance;
    }
    this->yLocation += dY;
    if (this->yLocation < 0) {
        this->yLocation = constants::smallDistance;
    }
    else if (this->yLocation > yLimit) {
        this->yLocation = yLimit - constants::smallDistance;
    }
    this->zLocation += dZ;
    if (this->zLocation < 0) {
        this->zLocation = constants::smallDistance;
    }
    else if (this->zLocation > zLimit) {
        this->zLocation = zLimit - constants::smallDistance;
    }
}

// Returns distance between to some another unit / item using distance formula
double Unit::distanceToUnit(Unit otherUnit) {
    return std::sqrt((this->xLocation - otherUnit.getXLocation()) * (this->xLocation - otherUnit.getXLocation()) +
        (this->yLocation - otherUnit.getYLocation()) * (this->yLocation - otherUnit.getYLocation()) +
        (this->zLocation - otherUnit.getZLocation()) * (this->zLocation - otherUnit.getZLocation()));
}
double Unit::distanceToItem(Item someItem) {
    return std::sqrt((this->xLocation - someItem.getXLocation()) * (this->xLocation - someItem.getXLocation()) +
        (this->yLocation - someItem.getYLocation()) * (this->yLocation - someItem.getYLocation()) +
        (this->zLocation - someItem.getZLocation()) * (this->zLocation - someItem.getZLocation()));
}

// Adds to battle ability unless it is already there
void Unit::addBattleAbility(Ability newAbility) {
    bool addAbility = true;
    for (size_t i = 0; i < this->battleAbilities.size(); i++) {
        if (this->battleAbilities.at(i).getName().compare(newAbility.getName()) == 0) {
            addAbility = false;
            break;
        }
    }
    if (addAbility) {
        this->battleAbilities.push_back(newAbility);
    }
}
void Unit::addBattleAbilities(std::vector<Ability> newAbilities) {
    for (size_t i = 0; i < newAbilities.size(); i++) {
        this->addBattleAbility(newAbilities.at(i));
    }
}
void Unit::addBattleAbilities(std::vector<std::string> newAbilities) {
    for (size_t i = 0; i < newAbilities.size(); i++) {
        this->addBattleAbility(Ability(newAbilities.at(i)));
    }
}

// Returns whether the unit has the specified ability
bool Unit::hasBattleAbility(std::string abilityName) {
    bool hasAbility = false;
    for (size_t i = 0; i < this->battleAbilities.size(); i++) {
        if (this->battleAbilities.at(i).getName().compare(abilityName) == 0) {
            hasAbility = true;
            break;
        }
    }
    return hasAbility;
}

// Returns energy cost of the specified battle ability
int Unit::battleAbilityEnergyCost(std::string abilityName) {
    int abilityCost = 0;
    bool hasAbility = false;
    for (size_t i = 0; i < this->battleAbilities.size(); i++) {
        if (this->battleAbilities.at(i).getName().compare(abilityName) == 0) {
            abilityCost = this->battleAbilities.at(i).getEnergyCost();
            hasAbility = true;
            break;
        }
    }
    if (!(hasAbility)) {
        std::cout << "ERROR: Battle ability " << abilityName << " not found for " << this->name << ".\n";
    }
    return abilityCost;
}

// Use when taking damage / regenerating health by any means
void Unit::takeDamage(int damage) {
    // take damage
    this->missingHealth = std::min(this->getMaxHealth(), this->missingHealth + damage);
    if (this->missingHealth == this->getMaxHealth()) { // unit died
        this->setStatusAlive(false);
    }
}
void Unit::regenerateHealth(int amount, bool maxout) {
    this->missingHealth -= amount;
    if ((maxout) && (this->missingHealth < 0)) {
        this->missingHealth = 0;
    }
    if ((this->missingHealth < this->getMaxHealth()) && !this->status_alive) {
        this->status_alive = true;
    }
}

// Bonus attack / magic multiplier based on color of ability / unit color
double Unit::abilityColorOffensiveMultiplier(Ability abilityUsed) {
    double multiplier{ 1.0 };
    if (this->isBlue() && abilityUsed.isBlue()) {
        multiplier *= constants::abilityColorOffensiveMultiplierBlue;
        std::cout << this->name << " is versed in water!\n";
    }
    else if (this->isRed() && abilityUsed.isRed()) {
        multiplier *= constants::abilityColorOffensiveMultiplierRed;
        std::cout << this->name << " is versed in red!\n";
    }
    else if (this->isBrown() && abilityUsed.isBrown()) {
        multiplier *= constants::abilityColorOffensiveMultiplierBrown;
        std::cout << this->name << " is versed in earth!\n";
    }
    else if (this->isCyan() && abilityUsed.isCyan()) {
        multiplier *= constants::abilityColorOffensiveMultiplierCyan;
        std::cout << this->name << " is versed in ice!\n";
    }
    else if (this->isOrange() && abilityUsed.isOrange()) {
        multiplier *= constants::abilityColorOffensiveMultiplierOrange;
        std::cout << this->name << " is versed in air!\n";
    }
    else if (this->isPurple() && abilityUsed.isPurple()) {
        multiplier *= constants::abilityColorOffensiveMultiplierPurple;
        std::cout << this->name << " is versed in gravity!\n";
    }
    else if (this->isYellow() && abilityUsed.isYellow()) {
        multiplier *= constants::abilityColorOffensiveMultiplierYellow;
        std::cout << this->name << " is versed in electricity!\n";
    }
    else if (this->isMagenta() && abilityUsed.isMagenta()) {
        multiplier *= constants::abilityColorOffensiveMultiplierMagenta;
        std::cout << this->name << " is versed in nuclear forces!\n";
    }
    else if (this->isBlack() && abilityUsed.isBlack()) {
        multiplier *= constants::abilityColorOffensiveMultiplierBlack;
        std::cout << this->name << " is versed in darkness!\n";
    }
    else if (this->isWhite() && abilityUsed.isWhite()) {
        multiplier *= constants::abilityColorOffensiveMultiplierWhite;
        std::cout << this->name << " is versed in light!\n";
    }
    else if (this->isGreen() && abilityUsed.isGreen()) {
        multiplier *= constants::abilityColorOffensiveMultiplierGreen;
        std::cout << this->name << " is versed in balance!\n";
    }
    return multiplier;
}
double Unit::abilityColorDefensiveMultiplier(Ability abilityUsed) {
    double multiplier{ 1.0 };
    if (this->isBlue() && abilityUsed.isBlue()) {
        multiplier *= constants::abilityColorDefensiveMultiplierBlue;
        std::cout << this->name << " is resistant to water.\n";
    }
    else if (this->isRed() && abilityUsed.isRed()) {
        multiplier *= constants::abilityColorDefensiveMultiplierRed;
        std::cout << this->name << " is resistant to fire.\n";
    }
    else if (this->isBrown() && abilityUsed.isBrown()) {
        multiplier *= constants::abilityColorDefensiveMultiplierBrown;
        std::cout << this->name << " is resistant to earth.\n";
    }
    else if (this->isCyan() && abilityUsed.isCyan()) {
        multiplier *= constants::abilityColorDefensiveMultiplierCyan;
        std::cout << this->name << " is resistant to ice.\n";
    }
    else if (this->isOrange() && abilityUsed.isOrange()) {
        multiplier *= constants::abilityColorDefensiveMultiplierOrange;
        std::cout << this->name << " is resistant to air.\n";
    }
    else if (this->isPurple() && abilityUsed.isPurple()) {
        multiplier *= constants::abilityColorDefensiveMultiplierPurple;
        std::cout << this->name << " is resistant to gravity.\n";
    }
    else if (this->isYellow() && abilityUsed.isYellow()) {
        multiplier *= constants::abilityColorDefensiveMultiplierYellow;
        std::cout << this->name << " is resistant to electricity.\n";
    }
    else if (this->isMagenta() && abilityUsed.isMagenta()) {
        multiplier *= constants::abilityColorDefensiveMultiplierMagenta;
        std::cout << this->name << " is resistant to nuclear forces.\n";
    }
    else if (this->isBlack() && abilityUsed.isBlack()) {
        multiplier *= constants::abilityColorDefensiveMultiplierBlack;
        std::cout << this->name << " is resistant to darkness.\n";
    }
    else if (this->isWhite() && abilityUsed.isWhite()) {
        multiplier *= constants::abilityColorDefensiveMultiplierWhite;
        std::cout << this->name << " is resistant to light.\n";
    }
    else if (this->isGreen() && abilityUsed.isGreen()) {
        multiplier *= constants::abilityColorDefensiveMultiplierGreen;
        std::cout << this->name << " is resistant to balance.\n";
    }
    if (this->isBlue() && abilityUsed.isBrown()) { // earth counters water
        multiplier *= constants::abilityColorDefensiveWeaknessMultiplier;
        std::cout << this->name << " is susceptible to earth.\n";
    }
    else if (this->isRed() && abilityUsed.isBlue()) { // water counters fire
        multiplier *= constants::abilityColorDefensiveWeaknessMultiplier;
        std::cout << this->name << " is susceptible to water.\n";
    }
    else if (this->isBrown() && abilityUsed.isOrange()) { // air counters earth
        multiplier *= constants::abilityColorDefensiveWeaknessMultiplier;
        std::cout << this->name << " is susceptible to air.\n";
    }
    else if (this->isCyan() && abilityUsed.isRed()) { // fire counters ice
        multiplier *= constants::abilityColorDefensiveWeaknessMultiplier;
        std::cout << this->name << " is susceptible to fire.\n";
    }
    else if (this->isOrange() && abilityUsed.isCyan()) { // ice counters air
        multiplier *= constants::abilityColorDefensiveWeaknessMultiplier;
        std::cout << this->name << " is susceptible to ice.\n";
    }
    else if (this->isPurple() && abilityUsed.isMagenta()) { // nuclear counters gravity
        multiplier *= constants::abilityColorDefensiveWeaknessMultiplier;
        std::cout << this->name << " is susceptible to nuclear forces.\n";
    }
    else if (this->isYellow() && abilityUsed.isPurple()) { // gravity counters electricity
        multiplier *= constants::abilityColorDefensiveWeaknessMultiplier;
        std::cout << this->name << " is susceptible to gravity.\n";
    }
    else if (this->isMagenta() && abilityUsed.isYellow()) { // electricity counters nuclear
        multiplier *= constants::abilityColorDefensiveWeaknessMultiplier;
        std::cout << this->name << " is susceptible to electricity.\n";
    }
    else if (this->isBlack() && abilityUsed.isWhite()) { // white counters black
        multiplier *= constants::abilityColorDefensiveWeaknessMultiplier;
        std::cout << this->name << " is susceptible to light.\n";
    }
    else if (this->isWhite() && abilityUsed.isBlack()) { // black counters white
        multiplier *= constants::abilityColorDefensiveWeaknessMultiplier;
        std::cout << this->name << " is susceptible to darkness.\n";
    }
    else if (this->isColorless() && abilityUsed.isGreen()) { // green counters colorless
        multiplier *= constants::abilityColorDefensiveWeaknessMultiplier;
        std::cout << this->name << " is susceptible to balance.\n";
    }
    return multiplier;
}

// Initialize battle stats
void Unit::initializeBattleStats(Player unit) {
    this->name = unit.getName();
    this->baseHealth = unit.getMaxHealth();
    this->missingHealth = unit.getMissingHealth();
    this->baseAttack = unit.getAttack();
    this->baseMagic = unit.getMagic();
    this->baseDefense = unit.getDefense();
    this->baseResist = unit.getResist();
    this->basePiercing = unit.getPiercing();
    this->basePenetration = unit.getPenetration();
    this->baseDexterity = unit.getDexterity();
    this->baseLifesteal = unit.getLifeSteal();
}
void Unit::initializeBattleStats(aiUnit unit) {
    this->name = unit.getName();
    this->baseHealth = unit.getMaxHealth();
    this->missingHealth = unit.getMissingHealth();
    this->baseAttack = unit.getAttack();
    this->baseMagic = unit.getMagic();
    this->baseDefense = unit.getDefense();
    this->baseResist = unit.getResist();
    this->basePiercing = unit.getPiercing();
    this->basePenetration = unit.getPenetration();
    this->baseDexterity = unit.getDexterity();
    this->baseLifesteal = unit.getLifeSteal();
}

// Add status effect info to the inputted vector
void Unit::getStatusEffectInfo(std::vector<std::string>& unitInfo) {
    if (!this->status_alive) {
        unitInfo.push_back("--- Dead ---");
    }
    if (this->status_enlarge) {
        unitInfo.push_back("HP ++");
    }
    if (this->status_grow) {
        unitInfo.push_back("HP +");
    }
    if (this->status_beserk) {
        unitInfo.push_back("Att++");
    }
    if (this->status_strength) {
        unitInfo.push_back("Att+");
    }
    if (this->status_feeble) {
        unitInfo.push_back("Att--");
    }
    if (this->status_weak) {
        unitInfo.push_back("Att-");
    }
    if (this->status_potent) {
        unitInfo.push_back("Mag++");
    }
    if (this->status_cogent) {
        unitInfo.push_back("Mag+");
    }
    if (this->status_impotent) {
        unitInfo.push_back("Mag--");
    }
    if (this->status_inept) {
        unitInfo.push_back("Mag-");
    }
    if (this->status_bulwark) {
        unitInfo.push_back("Def++");
    }
    if (this->status_defend) {
        unitInfo.push_back("Def+");
    }
    if (this->status_smashed) {
        unitInfo.push_back("Def--");
    }
    if (this->status_broken) {
        unitInfo.push_back("Def-");
    }
    if (this->status_dauntless) {
        unitInfo.push_back("Res++");
    }
    if (this->status_resolve) {
        unitInfo.push_back("Res+");
    }
    if (this->status_shattered) {
        unitInfo.push_back("Res--");
    }
    if (this->status_outwilled) {
        unitInfo.push_back("Res-");
    }
    if (this->status_deftness) {
        unitInfo.push_back("Dex++");
    }
    if (this->status_swiftness) {
        unitInfo.push_back("Dex+");
    }
    if (this->status_lethargic) {
        unitInfo.push_back("Dex--");
    }
    if (this->status_slow) {
        unitInfo.push_back("Dex-");
    }
    if (this->status_bleed) {
        unitInfo.push_back("--- Bleeding ---");
    }
    if (this->status_hemorrhage) {
        unitInfo.push_back("--- Hemorrhaged ---");
    }
    if (this->status_wilt) {
        unitInfo.push_back("--- Wilting ---");
    }
    if (this->status_wither) {
        unitInfo.push_back("--- Withered ---");
    }
    if (this->status_drowning) {
        unitInfo.push_back("--- Drowning ---");
    }
    if (this->status_drowned) {
        unitInfo.push_back("--- Drowned ---");
    }
    if (this->status_burn) {
        unitInfo.push_back("--- Burning ---");
    }
    if (this->status_char) {
        unitInfo.push_back("--- Charred ---");
    }
    if (this->status_rot) {
        unitInfo.push_back("--- Rotting ---");
    }
    if (this->status_decay) {
        unitInfo.push_back("--- Decayed ---");
    }
    if (this->status_chill) {
        unitInfo.push_back("--- Chilled ---");
    }
    if (this->status_freeze) {
        unitInfo.push_back("--- Frozen ---");
    }
    if (this->status_infect) {
        unitInfo.push_back("--- Infected ---");
    }
    if (this->status_disease) {
        unitInfo.push_back("--- Diseased ---");
    }
    if (this->status_shake) {
        unitInfo.push_back("--- Shaken ---");
    }
    if (this->status_fall) {
        unitInfo.push_back("--- Fell ---");
    }
    if (this->status_shock) {
        unitInfo.push_back("--- Shocked ---");
    }
    if (this->status_paralyze) {
        unitInfo.push_back("--- Paralyzed ---");
    }
    if (this->status_unstable) {
        unitInfo.push_back("--- Unstable ---");
    }
    if (this->status_radioactive) {
        unitInfo.push_back("--- Radioactive ---");
    }
    if (this->status_obscure) {
        unitInfo.push_back("--- Obscured ---");
    }
    if (this->status_hide) {
        unitInfo.push_back("--- Hidden ---");
    }
    if (this->status_bright) {
        unitInfo.push_back("--- Bright ---");
    }
    if (this->status_illuminate) {
        unitInfo.push_back("--- Illuminated ---");
    }
}

// Print unit information.
void Unit::printUnitInfo() {
    std::cout << this->name;
    std::cout << "\nHealth:      " << this->getCurrHealth() << "/" << this->getMaxHealth();
    std::cout << "\nAttack:      " << this->getAttack();
    std::cout << "\nMagic:       " << this->getMagic();
    std::cout << "\nDefense:     " << this->getDefense();
    std::cout << "\nResist:      " << this->getResist();
    std::cout << "\nPiercing:    " << this->getPiercing();
    std::cout << "\nPenetration: " << this->getPenetration();
    std::cout << "\nDexterity:   " << this->getDexterity() << "\n\n";
}

// Return string for save game files
std::string Unit::saveGame() {
    std::string fileString{};
    fileString += "*STRING=name\n" + this->name + "\n*END\n";
    fileString += "baseHealth=" + std::to_string(this->baseHealth) + "\n";
    fileString += "missingHealth=" + std::to_string(this->missingHealth) + "\n";
    fileString += "baseAttack=" + std::to_string(this->baseAttack) + "\n";
    fileString += "baseMagic=" + std::to_string(this->baseMagic) + "\n";
    fileString += "baseDefense=" + std::to_string(this->baseDefense) + "\n";
    fileString += "baseResist=" + std::to_string(this->baseResist) + "\n";
    fileString += "basePiercing=" + std::to_string(this->basePiercing) + "\n";
    fileString += "basePenetration=" + std::to_string(this->basePenetration) + "\n";
    fileString += "baseDexterity=" + std::to_string(this->baseDexterity) + "\n";
    fileString += "thisUnitColor=" + std::to_string(this->getUnitColorInt()) + "\n";
    fileString += "status_alive=" + core_functions::boolToString(this->status_alive) + "\n";
    fileString += "status_grow=" + core_functions::boolToString(this->status_grow) + "\n";
    fileString += "status_enlarge=" + core_functions::boolToString(this->status_enlarge) + "\n";
    fileString += "status_strength=" + core_functions::boolToString(this->status_strength) + "\n";
    fileString += "status_beserk=" + core_functions::boolToString(this->status_beserk) + "\n";
    fileString += "status_cogent=" + core_functions::boolToString(this->status_cogent) + "\n";
    fileString += "status_potent=" + core_functions::boolToString(this->status_potent) + "\n";
    fileString += "status_defend=" + core_functions::boolToString(this->status_defend) + "\n";
    fileString += "status_bulwark=" + core_functions::boolToString(this->status_bulwark) + "\n";
    fileString += "status_resolve=" + core_functions::boolToString(this->status_resolve) + "\n";
    fileString += "status_dauntless=" + core_functions::boolToString(this->status_dauntless) + "\n";
    fileString += "status_swiftness=" + core_functions::boolToString(this->status_swiftness) + "\n";
    fileString += "status_deftness=" + core_functions::boolToString(this->status_deftness) + "\n";
    fileString += "status_weak=" + core_functions::boolToString(this->status_weak) + "\n";
    fileString += "status_feeble=" + core_functions::boolToString(this->status_feeble) + "\n";
    fileString += "status_inept=" + core_functions::boolToString(this->status_inept) + "\n";
    fileString += "status_impotent=" + core_functions::boolToString(this->status_impotent) + "\n";
    fileString += "status_broken=" + core_functions::boolToString(this->status_broken) + "\n";
    fileString += "status_smashed=" + core_functions::boolToString(this->status_smashed) + "\n";
    fileString += "status_outwilled=" + core_functions::boolToString(this->status_outwilled) + "\n";
    fileString += "status_shattered=" + core_functions::boolToString(this->status_shattered) + "\n";
    fileString += "status_slow=" + core_functions::boolToString(this->status_slow) + "\n";
    fileString += "status_lethargic=" + core_functions::boolToString(this->status_lethargic) + "\n";
    fileString += "status_bleed=" + core_functions::boolToString(this->status_bleed) + "\n";
    fileString += "status_hemorrhage=" + core_functions::boolToString(this->status_hemorrhage) + "\n";
    fileString += "status_wilt=" + core_functions::boolToString(this->status_wilt) + "\n";
    fileString += "status_wither=" + core_functions::boolToString(this->status_wither) + "\n";
    fileString += "status_drowning=" + core_functions::boolToString(this->status_drowning) + "\n";
    fileString += "status_drowned=" + core_functions::boolToString(this->status_drowned) + "\n";
    fileString += "status_burn=" + core_functions::boolToString(this->status_burn) + "\n";
    fileString += "status_char=" + core_functions::boolToString(this->status_char) + "\n";
    fileString += "status_rot=" + core_functions::boolToString(this->status_rot) + "\n";
    fileString += "status_decay=" + core_functions::boolToString(this->status_decay) + "\n";
    fileString += "status_chill=" + core_functions::boolToString(this->status_chill) + "\n";
    fileString += "status_freeze=" + core_functions::boolToString(this->status_freeze) + "\n";
    fileString += "status_infect=" + core_functions::boolToString(this->status_infect) + "\n";
    fileString += "status_disease=" + core_functions::boolToString(this->status_disease) + "\n";
    fileString += "status_shake=" + core_functions::boolToString(this->status_shake) + "\n";
    fileString += "status_fall=" + core_functions::boolToString(this->status_fall) + "\n";
    fileString += "turnsShaken=" + std::to_string(this->turnsShaken) + "\n";
    fileString += "status_shock=" + core_functions::boolToString(this->status_shock) + "\n";
    fileString += "status_paralyze=" + core_functions::boolToString(this->status_paralyze) + "\n";
    fileString += "status_unstable=" + core_functions::boolToString(this->status_unstable) + "\n";
    fileString += "status_radioactive=" + core_functions::boolToString(this->status_radioactive) + "\n";
    fileString += "turnsUnstable=" + std::to_string(this->turnsUnstable) + "\n";
    fileString += "status_obscure=" + core_functions::boolToString(this->status_obscure) + "\n";
    fileString += "status_hide=" + core_functions::boolToString(this->status_hide) + "\n";
    fileString += "status_bright=" + core_functions::boolToString(this->status_bright) + "\n";
    fileString += "status_illuminate=" + core_functions::boolToString(this->status_illuminate) + "\n";
    fileString += "xLocation=" + std::to_string(this->xLocation) + "\n";
    fileString += "yLocation=" + std::to_string(this->yLocation) + "\n";
    fileString += "zLocation=" + std::to_string(this->zLocation) + "\n";
    fileString += "view_distance=" + std::to_string(this->view_distance) + "\n";
    fileString += "view_dot=" + std::to_string(this->view_dot) + "\n";
    fileString += "view_clock=" + std::to_string(this->view_clock) + "\n";
    fileString += "baseLifesteal=" + std::to_string(this->baseLifesteal) + "\n";
    fileString += "*VECTOR=battleAbilities\n";
    for (Ability i : this->battleAbilities) {
        fileString += i.saveGame();
    }
    fileString += "*END\n";
    return fileString;
}


// Player subclass
Player::Player(std::string name, int baseHealth, int baseAttack, int baseMagic, int baseDefense,
    int baseResist, int basePiercing, int basePenetration, int baseDexterity, double healthRegen,
    double energyRegen, double manaRegen, double xLocation, double yLocation, double zLocation,
    int level, int experience, int baseEnergy, int baseMana, double theta, double phi, double
    maxMoveDistance, double viewDistance) : Unit({ name, baseHealth, baseAttack, baseMagic,
        baseDefense, baseResist, basePiercing, basePenetration, baseDexterity, xLocation,
        yLocation, zLocation }) {
    this->level = level;
    this->experience = experience;
    this->baseEnergy = baseEnergy;
    this->missingEnergy = 0;
    this->baseMana = baseMana;
    this->missingMana = 0;
    this->healthRegenerationSpeed = healthRegen;
    this->energyRegenerationSpeed = energyRegen;
    this->manaRegenerationSpeed = manaRegen;
    this->setFacingSpherical(theta, phi);
    this->maxMoveDistance = maxMoveDistance;
    this->viewDistance = viewDistance;
    this->maxTurnAngle = constants::defaultMaxTurnAngle; // 30 degrees
    this->viewAngle = constants::defaultMaxViewAngle; // cos(45 degrees)
    this->viewAngleThreshold = constants::defaultViewAngleThreshold; // ~22.5 degrees
    this->addBattleAbility(Ability("flee"));
    this->addBattleAbility(Ability("attack"));
}
Player::Player(std::string name, int startingLevel) {
    this->setName(name);
    this->level = startingLevel;
    this->updateBaseStats();
    this->experience = 0;
    this->setFacingSpherical(0, 0);
    this->addBattleAbilities({ "nothing", "flee", "attack" });
    this->setStatusAlive(true);
}

void Player::setVelocityComponent(double vel, int component) {
    if ((component >= 0) && (component < sizeof(velocity))) {
        this->velocity[component] = vel;
    }
    else {
        std::cout << "Velocity component " << component << " out of range.\n";
    }
}

// current stat calculations
int Player::getMaxHealth() {
    double result{ static_cast<double>(this->getBaseHealth()) };
    if (this->weapon.getID() != -1) {
        result += this->weapon.getMaxHealth();
    }
    if (this->offhand.getID() != -1) {
        result += this->offhand.getMaxHealth();
    }
    if (this->twohand.getID() != -1) {
        result += this->twohand.getMaxHealth();
    }
    if (this->headgear.getID() != -1) {
        result += this->headgear.getMaxHealth();
    }
    if (this->chestgear.getID() != -1) {
        result += this->chestgear.getMaxHealth();
    }
    if (this->leggear.getID() != -1) {
        result += this->leggear.getMaxHealth();
    }
    if (this->footgear.getID() != -1) {
        result += this->footgear.getMaxHealth();
    }
    if (this->accessory1.getID() != -1) {
        result += this->accessory1.getMaxHealth();
    }
    if (this->accessory2.getID() != -1) {
        result += this->accessory2.getMaxHealth();
    }
    if (this->accessory3.getID() != -1) {
        result += this->accessory3.getMaxHealth();
    }
    if (this->accessory4.getID() != -1) {
        result += this->accessory4.getMaxHealth();
    }
    if (this->getStatusGrow()) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->getStatusEnlarge()) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->getStatusWilt()) {
        result *= constants::wiltConstant;
    }
    if (this->getStatusWither()) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}
int Player::getCurrHealth() {
    int result{ this->getMaxHealth() - this->getMissingHealth() };
    if (result < 0) {
        std::cout << "Player Function\n"; // *************************
        std::cout << "ERROR: Negative " << result << " health for " << this->getName() << ". Set to 0.\n";
        this->setMissingHealth(this->getMaxHealth());
        result = 0;
    }
    return result;
}
int Player::getAttack() {
    double result{ static_cast<double>(this->getBaseAttack()) };
    double itemMultiplier{ 1.0 };
    if (this->weapon.getID() != -1) {
        result += this->weapon.getAttack();
        itemMultiplier *= this->offensiveItemMultiplier(this->weapon);
    }
    if (this->offhand.getID() != -1) {
        result += this->offhand.getAttack();
        itemMultiplier *= this->offensiveItemMultiplier(this->offhand);
    }
    if (this->twohand.getID() != -1) {
        result += this->twohand.getAttack();
        itemMultiplier *= this->offensiveItemMultiplier(this->twohand);
    }
    if (this->headgear.getID() != -1) {
        result += this->headgear.getAttack();
        itemMultiplier *= this->offensiveItemMultiplier(this->headgear);
    }
    if (this->chestgear.getID() != -1) {
        result += this->chestgear.getAttack();
        itemMultiplier *= this->offensiveItemMultiplier(this->chestgear);
    }
    if (this->leggear.getID() != -1) {
        result += this->leggear.getAttack();
        itemMultiplier *= this->offensiveItemMultiplier(this->leggear);
    }
    if (this->footgear.getID() != -1) {
        result += this->footgear.getAttack();
        itemMultiplier *= this->offensiveItemMultiplier(this->footgear);
    }
    if (this->accessory1.getID() != -1) {
        result += this->accessory1.getAttack();
        itemMultiplier *= this->offensiveItemMultiplier(this->accessory1);
    }
    if (this->accessory2.getID() != -1) {
        result += this->accessory2.getAttack();
        itemMultiplier *= this->offensiveItemMultiplier(this->accessory2);
    }
    if (this->accessory3.getID() != -1) {
        result += this->accessory3.getAttack();
        itemMultiplier *= this->offensiveItemMultiplier(this->accessory3);
    }
    if (this->accessory4.getID() != -1) {
        result += this->accessory4.getAttack();
        itemMultiplier *= this->offensiveItemMultiplier(this->accessory4);
    }
    if (this->upgrade_aggression1) {
        result += constants::aggression1attack;
    }
    if (this->upgrade_aggression2) {
        result += constants::aggression2attack;
    }
    if (this->upgrade_aggression3) {
        result += constants::aggression3attack;
    }
    if (this->getStatusStrength()) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->getStatusBeserk()) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->getStatusWeak()) {
        result *= constants::minorStatusEffectNerf;
    }
    if (this->getStatusFeeble()) {
        result *= constants::majorStatusEffectNerf;
    }
    if (this->getStatusWilt()) {
        result *= constants::wiltConstant;
    }
    if (this->getStatusWither()) {
        result *= constants::witherConstant;
    }
    result *= itemMultiplier;
    return static_cast<int>(std::round(result));
}
int Player::getMagic() {
    double result{ static_cast<double>(this->getBaseMagic()) };
    double itemMultiplier{ 1.0 };
    if (this->weapon.getID() != -1) {
        result += this->weapon.getMagic();
        itemMultiplier *= this->offensiveItemMultiplier(this->weapon);
    }
    if (this->offhand.getID() != -1) {
        result += this->offhand.getMagic();
        itemMultiplier *= this->offensiveItemMultiplier(this->offhand);
    }
    if (this->twohand.getID() != -1) {
        result += this->twohand.getMagic();
        itemMultiplier *= this->offensiveItemMultiplier(this->twohand);
    }
    if (this->headgear.getID() != -1) {
        result += this->headgear.getMagic();
        itemMultiplier *= this->offensiveItemMultiplier(this->headgear);
    }
    if (this->chestgear.getID() != -1) {
        result += this->chestgear.getMagic();
        itemMultiplier *= this->offensiveItemMultiplier(this->chestgear);
    }
    if (this->leggear.getID() != -1) {
        result += this->leggear.getMagic();
        itemMultiplier *= this->offensiveItemMultiplier(this->leggear);
    }
    if (this->footgear.getID() != -1) {
        result += this->footgear.getMagic();
        itemMultiplier *= this->offensiveItemMultiplier(this->footgear);
    }
    if (this->accessory1.getID() != -1) {
        result += this->accessory1.getMagic();
        itemMultiplier *= this->offensiveItemMultiplier(this->accessory1);
    }
    if (this->accessory2.getID() != -1) {
        result += this->accessory2.getMagic();
        itemMultiplier *= this->offensiveItemMultiplier(this->accessory2);
    }
    if (this->accessory3.getID() != -1) {
        result += this->accessory3.getMagic();
        itemMultiplier *= this->offensiveItemMultiplier(this->accessory3);
    }
    if (this->accessory4.getID() != -1) {
        result += this->accessory4.getMagic();
        itemMultiplier *= this->offensiveItemMultiplier(this->accessory4);
    }
    if (this->upgrade_magic1) {
        result += constants::magic1magic;
    }
    if (this->upgrade_magic2) {
        result += constants::magic2magic;
    }
    if (this->upgrade_magic3) {
        result += constants::magic3magic;
    }
    if (this->getStatusCogent()) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->getStatusPotent()) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->getStatusInept()) {
        result *= constants::minorStatusEffectNerf;
    }
    if (this->getStatusImpotent()) {
        result *= constants::majorStatusEffectNerf;
    }
    if (this->getStatusWilt()) {
        result *= constants::wiltConstant;
    }
    if (this->getStatusWither()) {
        result *= constants::witherConstant;
    }
    result *= itemMultiplier;
    return static_cast<int>(std::round(result));
}
int Player::getDefense() {
    double result{ static_cast<double>(this->getBaseDefense()) };
    double itemMultiplier{ 1.0 };
    if (this->weapon.getID() != -1) {
        result += this->weapon.getDefense();
        itemMultiplier *= this->defensiveItemMultiplier(this->weapon);
    }
    if (this->offhand.getID() != -1) {
        result += this->offhand.getDefense();
        itemMultiplier *= this->defensiveItemMultiplier(this->offhand);
    }
    if (this->twohand.getID() != -1) {
        result += this->twohand.getDefense();
        itemMultiplier *= this->defensiveItemMultiplier(this->twohand);
    }
    if (this->headgear.getID() != -1) {
        result += this->headgear.getDefense();
        itemMultiplier *= this->defensiveItemMultiplier(this->headgear);
    }
    if (this->chestgear.getID() != -1) {
        result += this->chestgear.getDefense();
        itemMultiplier *= this->defensiveItemMultiplier(this->chestgear);
    }
    if (this->leggear.getID() != -1) {
        result += this->leggear.getDefense();
        itemMultiplier *= this->defensiveItemMultiplier(this->leggear);
    }
    if (this->footgear.getID() != -1) {
        result += this->footgear.getDefense();
        itemMultiplier *= this->defensiveItemMultiplier(this->footgear);
    }
    if (this->accessory1.getID() != -1) {
        result += this->accessory1.getDefense();
        itemMultiplier *= this->defensiveItemMultiplier(this->accessory1);
    }
    if (this->accessory2.getID() != -1) {
        result += this->accessory2.getDefense();
        itemMultiplier *= this->defensiveItemMultiplier(this->accessory2);
    }
    if (this->accessory3.getID() != -1) {
        result += this->accessory3.getDefense();
        itemMultiplier *= this->defensiveItemMultiplier(this->accessory3);
    }
    if (this->accessory4.getID() != -1) {
        result += this->accessory4.getDefense();
        itemMultiplier *= this->defensiveItemMultiplier(this->accessory4);
    }
    if (this->upgrade_protection1) {
        result += constants::protection1defense;
    }
    if (this->upgrade_protection2) {
        result += constants::protection2defense;
    }
    if (this->upgrade_protection3) {
        result += constants::protection3defense;
    }
    if (this->getStatusDefend()) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->getStatusBulwark()) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->getStatusBreak()) {
        result *= constants::minorStatusEffectNerf;
    }
    if (this->getStatusSmash()) {
        result *= constants::majorStatusEffectNerf;
    }
    if (this->getStatusWilt()) {
        result *= constants::wiltConstant;
    }
    if (this->getStatusWither()) {
        result *= constants::witherConstant;
    }
    result *= itemMultiplier;
    return static_cast<int>(std::round(result));
}
int Player::getResist() {
    double result{ static_cast<double>(this->getBaseResist()) };
    double itemMultiplier{ 1.0 };
    if (this->weapon.getID() != -1) {
        result += this->weapon.getResist();
        itemMultiplier *= this->defensiveItemMultiplier(this->weapon);
    }
    if (this->offhand.getID() != -1) {
        result += this->offhand.getResist();
        itemMultiplier *= this->defensiveItemMultiplier(this->offhand);
    }
    if (this->twohand.getID() != -1) {
        result += this->twohand.getResist();
        itemMultiplier *= this->defensiveItemMultiplier(this->twohand);
    }
    if (this->headgear.getID() != -1) {
        result += this->headgear.getResist();
        itemMultiplier *= this->defensiveItemMultiplier(this->headgear);
    }
    if (this->chestgear.getID() != -1) {
        result += this->chestgear.getResist();
        itemMultiplier *= this->defensiveItemMultiplier(this->chestgear);
    }
    if (this->leggear.getID() != -1) {
        result += this->leggear.getResist();
        itemMultiplier *= this->defensiveItemMultiplier(this->leggear);
    }
    if (this->footgear.getID() != -1) {
        result += this->footgear.getResist();
        itemMultiplier *= this->defensiveItemMultiplier(this->footgear);
    }
    if (this->accessory1.getID() != -1) {
        result += this->accessory1.getResist();
        itemMultiplier *= this->defensiveItemMultiplier(this->accessory1);
    }
    if (this->accessory2.getID() != -1) {
        result += this->accessory2.getResist();
        itemMultiplier *= this->defensiveItemMultiplier(this->accessory2);
    }
    if (this->accessory3.getID() != -1) {
        result += this->accessory3.getResist();
        itemMultiplier *= this->defensiveItemMultiplier(this->accessory3);
    }
    if (this->accessory4.getID() != -1) {
        result += this->accessory4.getResist();
        itemMultiplier *= this->defensiveItemMultiplier(this->accessory4);
    }
    if (this->upgrade_protection1) {
        result += constants::protection1resist;
    }
    if (this->upgrade_protection2) {
        result += constants::protection2resist;
    }
    if (this->upgrade_protection3) {
        result += constants::protection3resist;
    }
    if (this->getStatusResolve()) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->getStatusDauntless()) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->getStatusOutwill()) {
        result *= constants::minorStatusEffectNerf;
    }
    if (this->getStatusShatter()) {
        result *= constants::majorStatusEffectNerf;
    }
    if (this->getStatusWilt()) {
        result *= constants::wiltConstant;
    }
    if (this->getStatusWither()) {
        result *= constants::witherConstant;
    }
    result *= itemMultiplier;
    return static_cast<int>(std::round(result));
}
int Player::getPiercing() {
    double result{ static_cast<double>(this->getBasePiercing()) };
    if (this->weapon.getID() != -1) {
        result += this->weapon.getPiercing();
    }
    if (this->offhand.getID() != -1) {
        result += this->offhand.getPiercing();
    }
    if (this->offhand.getID() != -1) {
        result += this->twohand.getPiercing();
    }
    if (this->headgear.getID() != -1) {
        result += this->headgear.getPiercing();
    }
    if (this->chestgear.getID() != -1) {
        result += this->chestgear.getPiercing();
    }
    if (this->leggear.getID() != -1) {
        result += this->leggear.getPiercing();
    }
    if (this->footgear.getID() != -1) {
        result += this->footgear.getPiercing();
    }
    if (this->accessory1.getID() != -1) {
        result += this->accessory1.getPiercing();
    }
    if (this->accessory2.getID() != -1) {
        result += this->accessory2.getPiercing();
    }
    if (this->accessory3.getID() != -1) {
        result += this->accessory3.getPiercing();
    }
    if (this->accessory4.getID() != -1) {
        result += this->accessory4.getPiercing();
    }
    if (this->upgrade_aggression1) {
        result += constants::aggression1piercing;
    }
    if (this->upgrade_aggression2) {
        result += constants::aggression2piercing;
    }
    if (this->upgrade_aggression3) {
        result += constants::aggression3piercing;
    }
    if (this->getStatusWilt()) {
        result *= constants::wiltConstant;
    }
    if (this->getStatusWither()) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}
int Player::getPenetration() {
    double result{ static_cast<double>(this->getBasePenetration()) };
    if (this->weapon.getID() != -1) {
        result += this->weapon.getPenetration();
    }
    if (this->offhand.getID() != -1) {
        result += this->offhand.getPenetration();
    }
    if (this->offhand.getID() != -1) {
        result += this->twohand.getPenetration();
    }
    if (this->headgear.getID() != -1) {
        result += this->headgear.getPenetration();
    }
    if (this->chestgear.getID() != -1) {
        result += this->chestgear.getPenetration();
    }
    if (this->leggear.getID() != -1) {
        result += this->leggear.getPenetration();
    }
    if (this->footgear.getID() != -1) {
        result += this->footgear.getPenetration();
    }
    if (this->accessory1.getID() != -1) {
        result += this->accessory1.getPenetration();
    }
    if (this->accessory2.getID() != -1) {
        result += this->accessory2.getPenetration();
    }
    if (this->accessory3.getID() != -1) {
        result += this->accessory3.getPenetration();
    }
    if (this->accessory4.getID() != -1) {
        result += this->accessory4.getPenetration();
    }
    if (this->upgrade_magic1) {
        result += constants::magic1penetration;
    }
    if (this->upgrade_magic2) {
        result += constants::magic2penetration;
    }
    if (this->upgrade_magic3) {
        result += constants::magic3penetration;
    }
    if (this->getStatusWilt()) {
        result *= constants::wiltConstant;
    }
    if (this->getStatusWither()) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}
int Player::getDexterity() {
    double result{ static_cast<double>(this->getBaseDexterity()) };
    if (this->weapon.getID() != -1) {
        result += this->weapon.getDexterity();
    }
    if (this->offhand.getID() != -1) {
        result += this->offhand.getDexterity();
    }
    if (this->offhand.getID() != -1) {
        result += this->twohand.getDexterity();
    }
    if (this->headgear.getID() != -1) {
        result += this->headgear.getDexterity();
    }
    if (this->chestgear.getID() != -1) {
        result += this->chestgear.getDexterity();
    }
    if (this->leggear.getID() != -1) {
        result += this->leggear.getDexterity();
    }
    if (this->footgear.getID() != -1) {
        result += this->footgear.getDexterity();
    }
    if (this->accessory1.getID() != -1) {
        result += this->accessory1.getDexterity();
    }
    if (this->accessory2.getID() != -1) {
        result += this->accessory2.getDexterity();
    }
    if (this->accessory3.getID() != -1) {
        result += this->accessory3.getDexterity();
    }
    if (this->accessory4.getID() != -1) {
        result += this->accessory4.getDexterity();
    }
    if (this->upgrade_ninja1) {
        result += constants::ninja1dexterity;
    }
    if (this->upgrade_ninja2) {
        result += constants::ninja2dexterity;
    }
    if (this->upgrade_ninja3) {
        result += constants::ninja2dexterity;
    }
    if (this->getStatusSwiftness()) {
        result *= constants::minorStatusEffectBuff;
    }
    if (this->getStatusDeftness()) {
        result *= constants::majorStatusEffectBuff;
    }
    if (this->getStatusSlow()) {
        result *= constants::minorStatusEffectNerf;
    }
    if (this->getStatusLethargic()) {
        result *= constants::majorStatusEffectNerf;
    }
    if (this->getStatusChill()) {
        result *= constants::chillNerf;
    }
    if (this->getStatusFrozen()) {
        result *= constants::freezeNerf;
    }
    if (this->getStatusWilt()) {
        result *= constants::wiltConstant;
    }
    if (this->getStatusWither()) {
        result *= constants::witherConstant;
    }
    return static_cast<int>(std::round(result));
}
double Player::getLifeSteal() {
    double result{ this->Unit::getLifeSteal() };
    if (this->weapon.getID() != -1) {
        result += this->weapon.getLifeSteal();
    }
    if (this->offhand.getID() != -1) {
        result += this->offhand.getLifeSteal();
    }
    if (this->offhand.getID() != -1) {
        result += this->twohand.getLifeSteal();
    }
    if (this->headgear.getID() != -1) {
        result += this->headgear.getLifeSteal();
    }
    if (this->chestgear.getID() != -1) {
        result += this->chestgear.getLifeSteal();
    }
    if (this->leggear.getID() != -1) {
        result += this->leggear.getLifeSteal();
    }
    if (this->footgear.getID() != -1) {
        result += this->footgear.getLifeSteal();
    }
    if (this->accessory1.getID() != -1) {
        result += this->accessory1.getLifeSteal();
    }
    if (this->accessory2.getID() != -1) {
        result += this->accessory2.getLifeSteal();
    }
    if (this->accessory3.getID() != -1) {
        result += this->accessory3.getLifeSteal();
    }
    if (this->accessory4.getID() != -1) {
        result += this->accessory4.getLifeSteal();
    }
    return result;
}
double Player::getViewDistance() {
    double result{ this->viewDistance };
    if (this->weapon.getID() != -1) {
        result += this->weapon.getViewDistance();
    }
    if (this->offhand.getID() != -1) {
        result += this->offhand.getViewDistance();
    }
    if (this->offhand.getID() != -1) {
        result += this->twohand.getViewDistance();
    }
    if (this->headgear.getID() != -1) {
        result += this->headgear.getViewDistance();
    }
    if (this->chestgear.getID() != -1) {
        result += this->chestgear.getViewDistance();
    }
    if (this->leggear.getID() != -1) {
        result += this->leggear.getViewDistance();
    }
    if (this->footgear.getID() != -1) {
        result += this->footgear.getViewDistance();
    }
    if (this->accessory1.getID() != -1) {
        result += this->accessory1.getViewDistance();
    }
    if (this->accessory2.getID() != -1) {
        result += this->accessory2.getViewDistance();
    }
    if (this->accessory3.getID() != -1) {
        result += this->accessory3.getViewDistance();
    }
    if (this->accessory4.getID() != -1) {
        result += this->accessory4.getViewDistance();
    }
    return result;
}
double Player::getMaxMoveDistance() {
    double result{ this->maxMoveDistance };
    if (this->weapon.getID() != -1) {
        result += this->weapon.getMoveSpeed();
    }
    if (this->offhand.getID() != -1) {
        result += this->offhand.getMoveSpeed();
    }
    if (this->offhand.getID() != -1) {
        result += this->twohand.getMoveSpeed();
    }
    if (this->headgear.getID() != -1) {
        result += this->headgear.getMoveSpeed();
    }
    if (this->chestgear.getID() != -1) {
        result += this->chestgear.getMoveSpeed();
    }
    if (this->leggear.getID() != -1) {
        result += this->leggear.getMoveSpeed();
    }
    if (this->footgear.getID() != -1) {
        result += this->footgear.getMoveSpeed();
    }
    if (this->accessory1.getID() != -1) {
        result += this->accessory1.getMoveSpeed();
    }
    if (this->accessory2.getID() != -1) {
        result += this->accessory2.getMoveSpeed();
    }
    if (this->accessory3.getID() != -1) {
        result += this->accessory3.getMoveSpeed();
    }
    if (this->accessory4.getID() != -1) {
        result += this->accessory4.getMoveSpeed();
    }
    return result;
}
double Player::getMonsterSpawn() {
    double result{ this->monsterSpawn };
    if (this->weapon.getID() != -1) {
        result *= this->weapon.getMonsterSpawn();
    }
    if (this->offhand.getID() != -1) {
        result *= this->offhand.getMonsterSpawn();
    }
    if (this->offhand.getID() != -1) {
        result *= this->twohand.getMonsterSpawn();
    }
    if (this->headgear.getID() != -1) {
        result *= this->headgear.getMonsterSpawn();
    }
    if (this->chestgear.getID() != -1) {
        result *= this->chestgear.getMonsterSpawn();
    }
    if (this->leggear.getID() != -1) {
        result *= this->leggear.getMonsterSpawn();
    }
    if (this->footgear.getID() != -1) {
        result *= this->footgear.getMonsterSpawn();
    }
    if (this->accessory1.getID() != -1) {
        result *= this->accessory1.getMonsterSpawn();
    }
    if (this->accessory2.getID() != -1) {
        result *= this->accessory2.getMonsterSpawn();
    }
    if (this->accessory3.getID() != -1) {
        result *= this->accessory3.getMonsterSpawn();
    }
    if (this->accessory4.getID() != -1) {
        result *= this->accessory4.getMonsterSpawn();
    }
    return result;
}
double Player::getLuckFactor() {
    double result{ this->luckFactor };
    if (this->weapon.getID() != -1) {
        result *= this->weapon.getLuckFactor();
    }
    if (this->offhand.getID() != -1) {
        result *= this->offhand.getLuckFactor();
    }
    if (this->offhand.getID() != -1) {
        result *= this->twohand.getLuckFactor();
    }
    if (this->headgear.getID() != -1) {
        result *= this->headgear.getLuckFactor();
    }
    if (this->chestgear.getID() != -1) {
        result *= this->chestgear.getLuckFactor();
    }
    if (this->leggear.getID() != -1) {
        result *= this->leggear.getLuckFactor();
    }
    if (this->footgear.getID() != -1) {
        result *= this->footgear.getLuckFactor();
    }
    if (this->accessory1.getID() != -1) {
        result *= this->accessory1.getLuckFactor();
    }
    if (this->accessory2.getID() != -1) {
        result *= this->accessory2.getLuckFactor();
    }
    if (this->accessory3.getID() != -1) {
        result *= this->accessory3.getLuckFactor();
    }
    if (this->accessory4.getID() != -1) {
        result *= this->accessory4.getLuckFactor();
    }
    return result;
}

// Intersection upgrades
// Dimension I
void Player::activateUpgradeForelegs() {
    this->upgrade_forelegs = true;
    this->addBattleAbility(Ability("nibble"));
    this->maxMoveDistance = constants::legAssimilationMaxMoveDistance;
    this->increaseInventorySlots(1);
}
void Player::activateUpgradeHindlegs() {
    this->upgrade_hindlegs = true;
    this->addBattleAbility(Ability("lunge"));
    this->maxMoveDistance = constants::legAssimilationMaxMoveDistance;
    this->increaseInventorySlots(1);
}
void Player::activateUpgradeAttention1() {
    this->upgrade_attention1 = true;
    this->maxTurnAngle = constants::attentionMaxTurnAngle;
    this->viewDistance = constants::attentionMaxViewDistance;
    this->viewAngle = constants::attentionMaxViewAngle;
    this->viewAngleThreshold = constants::attentionViewAngleThreshold;
}
void Player::activateUpgradeQuadrupedal1() {
    this->upgrade_quadrupedal1 = true;
    this->addBattleAbility(Ability("flail"));
    this->maxMoveDistance = constants::quadrupedal1MaxMoveDistance;
    this->increaseInventorySlots(1);
    this->activateUpgrade(107); // equip accessory1
}
void Player::activateUpgradeCoordination1() {
    this->upgrade_coordination1 = true;
    this->increaseInventorySlots(2);
    this->activateUpgrade(108); // equip accessory2
}
void Player::activateUpgradeMemory1() {
    this->upgrade_memory1 = true;
    this->increaseInventorySlots(4);
    this->activateUpgrade(101); // equip weapon
}

// Dimension II
void Player::activateUpgradeQuadrupedal2() {
    this->upgrade_quadrupedal2 = true;
    this->maxMoveDistance = constants::quadrupedal2MaxMoveDistance;
    this->increaseInventorySlots(4);
    this->activateUpgrade(101); // equip weapon
    this->activateUpgrade(102); // equip offhand
}
void Player::activateUpgradeCoordination2() {
    this->upgrade_coordination2 = true;
    this->increaseInventorySlots(4);
    this->activateUpgrade(122); // equip accessory3
}
void Player::activateUpgradeLearning1() {
    this->upgrade_learning1 = true;
    this->addBattleAbility(Ability("wisp"));
    this->increaseInventorySlots(8);
    this->chooseColor(1);
    this->addColorSpells(1);
}
void Player::activateUpgradeAttention2() {
    this->upgrade_attention2 = true;
    this->maxTurnAngle = constants::attention2MaxTurnAngle;
    this->viewDistance = constants::attention2MaxViewDistance;
    this->viewAngle = constants::attention2MaxViewAngle;
    this->viewAngleThreshold = constants::attention2ViewAngleThreshold;
}
void Player::activateUpgradeAggression1() {
    this->upgrade_aggression1 = true;
    this->addBattleAbility(Ability("hammer"));
    this->addBattleAbility(Ability("bite"));
    this->activateUpgrade(121); // equip twohand
}
void Player::activateUpgradeProtection1() {
    this->upgrade_protection1 = true;
    this->addBattleAbility(Ability("defend"));
    this->addBattleAbility(Ability("resolve"));
    this->activateUpgrade(104); // equip chestgear
    this->activateUpgrade(105); // equip leggear
}
void Player::activateUpgradeNinja1() {
    this->upgrade_ninja1 = true;
    this->maxMoveDistance = constants::ninja1MaxMoveDistance;
    this->addBattleAbility(Ability("swiftness"));
    this->addBattleAbility(Ability("slow"));
    this->activateUpgrade(106); // equip footgear
}
void Player::activateUpgradeMagic1() {
    this->upgrade_magic1 = true;
    this->addBattleAbility(Ability("bolt"));
    this->chooseColor(1);
    this->addColorSpells(2);
    this->activateUpgrade(103); // equip headgear
}

// Dimension III
void Player::activateUpgradeAggression2() {
    this->upgrade_aggression2 = true;
    this->increaseInventorySlots(2);
}
void Player::activateUpgradeProtection2() {
    this->upgrade_protection2 = true;
    this->increaseInventorySlots(2);
}
void Player::activateUpgradeNinja2() {
    this->upgrade_ninja2 = true;
    this->increaseInventorySlots(2);
}
void Player::activateUpgradeMagic2() {
    this->upgrade_magic2 = true;
    this->increaseInventorySlots(2);
}
void Player::activateUpgradeMemory2() {
    this->upgrade_memory2 = true;
    this->increaseInventorySlots(8);
}
void Player::activateUpgradeLearning2() {
    this->upgrade_learning2 = true;
    this->increaseInventorySlots(8);
}

// Dimension IV
void Player::activateUpgradeAggression3() {
    this->upgrade_aggression3 = true;
}
void Player::activateUpgradeProtection3() {
    this->upgrade_protection3 = true;
}
void Player::activateUpgradeNinja3() {
    this->upgrade_ninja3 = true;
}
void Player::activateUpgradeMagic3() {
    this->upgrade_magic3 = true;
}

// Energy and mana functions
int Player::getMaxEnergy() {
    double result{ static_cast<double>(this->baseEnergy) };
    return static_cast<int>(std::round(result));
}
int Player::getCurrEnergy() {
    int result{ this->getMaxEnergy() - this->missingEnergy };
    if (result < 0) {
        std::cout << "ERROR: Negative " << result << "energy for " << this->getName() << ".\n";
    }
    return result;
}
int Player::getMaxMana() {
    double result{ static_cast<double>(this->baseMana) };
    return static_cast<int>(std::round(result));
}
int Player::getCurrMana() {
    int result{ this->getMaxMana() - this->missingMana };
    if (result < 0) {
        std::cout << "ERROR: Negative " << result << "mana for " << this->getName() << ".\n";
    }
    return result;
}
void Player::lowerEnergy(int amount) {
    this->missingEnergy = std::min(this->getMaxEnergy(), this->missingEnergy + amount);
}
int Player::increaseEnergy(int amount, bool maxout) {
    int energyAdded{ amount };
    this->missingEnergy -= amount;
    if ((maxout) && (this->missingEnergy < 0)) {
        energyAdded -= -this->missingEnergy;
        this->missingEnergy = 0;
    }
    return energyAdded;
}
void Player::lowerMana(int amount) {
    this->missingMana = std::min(this->getMaxMana(), this->missingMana + amount);
}
void Player::increaseMana(int amount, bool maxout) {
    this->missingMana -= amount;
    if ((maxout) && (this->missingMana < 0)) {
        this->missingMana = 0;
    }
}

double Player::getHealthRegenSpeed() {
    return this->healthRegenerationSpeed;
}
double Player::getEnergyRegenSpeed() {
    return this->energyRegenerationSpeed;
}
double Player::getManaRegenSpeed() {
    return this->manaRegenerationSpeed;
}

// Item multipliers for attack/magic/defense/resistance
double Player::offensiveItemMultiplier(Item i) {
    double multiplier{ 1.0 };
    if (this->isBlue() && i.isBlue()) {
        multiplier *= constants::itemColorOffensiveMultiplier;
    }
    else if (this->isRed() && i.isRed()) {
        multiplier *= constants::itemColorOffensiveMultiplier;
    }
    else if (this->isBrown() && i.isBrown()) {
        multiplier *= constants::itemColorOffensiveMultiplier;
    }
    else if (this->isCyan() && i.isCyan()) {
        multiplier *= constants::itemColorOffensiveMultiplier;
    }
    else if (this->isOrange() && i.isOrange()) {
        multiplier *= constants::itemColorOffensiveMultiplier;
    }
    else if (this->isPurple() && i.isPurple()) {
        multiplier *= constants::itemColorOffensiveMultiplier;
    }
    else if (this->isYellow() && i.isYellow()) {
        multiplier *= constants::itemColorOffensiveMultiplier;
    }
    else if (this->isMagenta() && i.isMagenta()) {
        multiplier *= constants::itemColorOffensiveMultiplier;
    }
    else if (this->isBlack() && i.isBlack()) {
        multiplier *= constants::itemColorOffensiveMultiplier;
    }
    else if (this->isWhite() && i.isWhite()) {
        multiplier *= constants::itemColorOffensiveMultiplier;
    }
    else if (this->isGreen() && i.isGreen()) {
        multiplier *= constants::itemColorOffensiveMultiplier;
    }
    return multiplier;
}
double Player::defensiveItemMultiplier(Item i) {
    double multiplier{ 1.0 };
    if (this->isBlue() && i.isBlue()) {
        multiplier *= constants::itemColorDefensiveMultiplier;
    }
    else if (this->isRed() && i.isRed()) {
        multiplier *= constants::itemColorDefensiveMultiplier;
    }
    else if (this->isBrown() && i.isBrown()) {
        multiplier *= constants::itemColorDefensiveMultiplier;
    }
    else if (this->isCyan() && i.isCyan()) {
        multiplier *= constants::itemColorDefensiveMultiplier;
    }
    else if (this->isOrange() && i.isOrange()) {
        multiplier *= constants::itemColorDefensiveMultiplier;
    }
    else if (this->isPurple() && i.isPurple()) {
        multiplier *= constants::itemColorDefensiveMultiplier;
    }
    else if (this->isYellow() && i.isYellow()) {
        multiplier *= constants::itemColorDefensiveMultiplier;
    }
    else if (this->isMagenta() && i.isMagenta()) {
        multiplier *= constants::itemColorDefensiveMultiplier;
    }
    else if (this->isBlack() && i.isBlack()) {
        multiplier *= constants::itemColorDefensiveMultiplier;
    }
    else if (this->isWhite() && i.isWhite()) {
        multiplier *= constants::itemColorDefensiveMultiplier;
    }
    else if (this->isGreen() && i.isGreen()) {
        multiplier *= constants::itemColorDefensiveMultiplier;
    }
    return multiplier;
}

// Move player given distance in meters
bool Player::movePlayer(double distance, double xLimit, double yLimit, double zLimit) {
    if (distance > this->getMaxMoveDistance()) {
        distance = this->getMaxMoveDistance();
    }
    else if (distance <= 0) {
        return false;
    }
    this->moveUnit(this->xFacing * distance, this->yFacing * distance, this->zFacing * distance,
        xLimit, yLimit, zLimit);
    this->distanceTraveled += distance;
    return true;
}
// When moving while falling
// NOTE: NOT CALLED (maybe if player can move in xy plane while falling)
bool Player::movePlayerWhenFalling(double distance, double xLimit, double yLimit, double zLimit) {
    if (distance > this->getMaxMoveDistance()) {
        distance = this->getMaxMoveDistance();
    }
    else if (distance <= 0) {
        return false;
    }
    if (this->zFacing < 0) {
        this->moveUnit(this->xFacing * distance, this->yFacing * distance, this->zFacing * distance,
            xLimit, yLimit, zLimit);
        this->distanceTraveled += distance;
    }
    else { // can't move up while in the air
        this->moveUnit(this->xFacing * distance, this->yFacing * distance, 0.0,
            xLimit, yLimit, zLimit);
        this->distanceTraveled += distance;
    }
    return true;
}

// Turn player the specified direction
bool Player::turnPlayer(std::string direction, int degrees) {
    bool successfulTurn = true;
    if ((abs(this->xFacing * this->xFacing + this->yFacing * this->yFacing + this->zFacing *
        this->zFacing) - 1.0) > constants::smallDistance) { // if not a unit vector
        this->setFacingCartesian(1, 0, 0); // face down x-axis
        std::cout << "ERROR: Player direction not well-specified so was reset.\n\n";
        successfulTurn = false;
    }
    else { // rotate unit vector in specified direction
        double radians{};
        if (degrees == -1) { // no direction specified
            radians = this->maxTurnAngle;
        }
        else {
            radians = degrees * constants::Pi / 180.0;
        }
        if (direction.compare("left") == 0) {
            this->setFacingSpherical(this->theta + radians, this->phi);
        }
        else if (direction.compare("right") == 0) {
            this->setFacingSpherical(this->theta - radians, this->phi);
        }
        else if ((direction.compare("up") == 0) && ((this->upgrade_forelegs) || (this->upgrade_hindlegs))) {
            if (0.0 > this->phi - radians) { // facing straight up
                radians = this->phi;
                this->setFacingSpherical(this->theta, 0.0);
            }
            else {
                this->setFacingSpherical(this->theta, this->phi - radians);
            }
        }
        else if ((direction.compare("down") == 0) && ((this->upgrade_forelegs) || (this->upgrade_hindlegs))) {
            if (constants::Pi < this->phi + radians) {
                radians = constants::Pi - this->phi;
                this->setFacingSpherical(this->theta, constants::Pi);
            }
            else {
                this->setFacingSpherical(this->theta, this->phi + radians);
            }
        }
        else if ((direction.compare("around") == 0) && (this->upgrade_attention1)) {
            radians = constants::Pi;
            this->setFacingSpherical(this->theta + radians, this->phi);
        }
        else {
            std::cout << "Specified turn direction not valid. Check \"help 'turn'\".\n\n";
            successfulTurn = false;
        }
        degrees = static_cast<int>(std::round(180.0 * radians / constants::Pi)); // in case radians changed
    }
    if (successfulTurn) {
        std::cout << "You turned " << degrees << " degrees " << direction << ".\n";
    }
    return successfulTurn;
}

// Face player the specified direction
bool Player::facePlayer(std::string direction) {
    bool successfulFace = true;
    if ((abs(this->xFacing * this->xFacing + this->yFacing * this->yFacing + this->zFacing *
        this->zFacing) - 1.0) > constants::smallDistance) { // if not a unit vector
        this->setFacingCartesian(1, 0, 0); // face down x-axis
        std::cout << "ERROR: Player direction not well-specified so was reset.\n\n";
        successfulFace = false;
    }
    else { // rotate unit vector in specified direction
        if (direction.compare("up") == 0) {
            this->setFacingSpherical(this->theta, 0);
        }
        else if (direction.compare("flat") == 0) {
            this->setFacingSpherical(this->theta, constants::Pi / 2.0);
        }
        else if (direction.compare("down") == 0) {
            this->setFacingSpherical(this->theta, constants::Pi);
        }
        else {
            std::cout << "Specified turn direction not valid. Check \"help 'face'\".\n\n";
            successfulFace = false;
        }
    }
    if (successfulFace) {
        std::cout << "You faced " << direction << ".\n";
    }
    return successfulFace;
}

// Turns the player toward the inputted unit
void Player::turnToward(Unit targetUnit) {
    double xDif = targetUnit.getXLocation() - this->getXLocation();
    double yDif = targetUnit.getYLocation() - this->getYLocation();
    double zDif = targetUnit.getZLocation() - this->getZLocation(); // vector from player to target
    this->setFacingCartesian(xDif, yDif, zDif); // this function will normalize for us
}

// Updates cartesian facing vector given theta / phi
void Player::updateCartesian() {
    this->xFacing = std::sin(this->phi) * std::cos(this->theta);
    this->yFacing = std::sin(this->phi) * std::sin(this->theta);
    this->zFacing = std::cos(this->phi);
}

// Updates theta / phi based on cartesian facing vector
void Player::updateSpherical() {
    // theta
    this->theta = core_functions::theta(this->xFacing, this->yFacing);
    // phi
    this->phi = core_functions::phi(this->zFacing);
}

// Sets cartesian facing vector based on input then updates theta / phi
void Player::setFacingCartesian(double x, double y, double z) {
    double normConstant{ std::sqrt(x * x + y * y + z * z) };
    if (normConstant == 0) {
        std::cout << "ERROR: Inputted cartesian facing vector is the zero vector.\n";
    }
    else {
        this->xFacing = x / normConstant;
        this->yFacing = y / normConstant;
        this->zFacing = z / normConstant;
        this->updateSpherical();
    }
}

// Sets theta / phi based on input then updates cartesian facing vector
void Player::setFacingSpherical(double theta, double phi) {
    // keep theta [0, 2pi)
    this->theta = std::fmod(theta, 2 * constants::Pi);
    if (this->theta < 0) {
        this->theta += 2 * constants::Pi;
    }
    // keep phi [0, pi]
    if (static_cast<int>(std::floor(std::abs(phi) / constants::Pi)) % 2 == 0) {
        this->phi = std::fmod(std::abs(phi), constants::Pi);
    }
    else {
        this->phi = constants::Pi - std::fmod(std::abs(phi), constants::Pi);
    }
    this->updateCartesian();
}

// Returns whether the player can see the inputted unit / item
bool Player::playerCanSee(Unit& otherUnit) {
    bool canSee = false;
    otherUnit.setView_Distance(this->distanceToUnit(otherUnit));
    if (otherUnit.getView_Distance() <= this->getViewDistance()) { // if units close enough
        double differenceVector[3]{ otherUnit.getXLocation() - this->getXLocation(),
            otherUnit.getYLocation() - this->getYLocation(),
            otherUnit.getZLocation() - this->getZLocation() }; // get difference vector
        // dot / magnitude = cos(angle) = this->viewAngle
        // facing vector is a unit vector
        otherUnit.setView_Dot((differenceVector[0] * this->xFacing + differenceVector[1] * this->yFacing + differenceVector[2] * this->zFacing) / otherUnit.getView_Distance());
        if (otherUnit.getView_Dot() > this->viewAngle) {
            canSee = true;
            // now calculate theta / phi of other unit
            double unitTheta{ core_functions::theta(differenceVector[0] / otherUnit.getView_Distance(), differenceVector[1] / otherUnit.getView_Distance()) };
            double unitPhi{ core_functions::phi(differenceVector[2] / otherUnit.getView_Distance()) };
            // use to calculate clock location
            int clock{ 4 }; // not left or right
            if (core_functions::thetaSubtract(this->theta, unitTheta) > this->viewAngleThreshold) { // right side
                clock = 5;
            }
            else if (core_functions::thetaSubtract(this->theta, unitTheta) < -this->viewAngleThreshold) { // left side
                clock = 3;
            }
            if (this->phi - unitPhi > this->viewAngleThreshold) { // above
                clock -= 3;
            }
            else if (unitPhi - this->phi > this->viewAngleThreshold) { // below
                clock += 3;
            }
            // (0 = top-left, 1 = top-front, 2 = top-right, 3 = left, 4 = front, ...)
            otherUnit.setView_Clock(clock);
        }
    }
    return canSee;
}
bool Player::playerCanSee(Item& someItem) {
    bool canSee = false;
    someItem.setView_Distance(this->distanceToItem(someItem));
    if (someItem.getView_Distance() <= this->getViewDistance()) { // if units close enough
        double differenceVector[3]{ someItem.getXLocation() - this->getXLocation(),
            someItem.getYLocation() - this->getYLocation(),
            someItem.getZLocation() - this->getZLocation() }; // get difference vector
        double facingVector[3]{ this->xFacing, this->yFacing, this->zFacing }; // facing vector
        someItem.setView_Dot((differenceVector[0] * this->xFacing + differenceVector[1] * this->yFacing + differenceVector[2] * this->zFacing) / someItem.getView_Distance());
        if (someItem.getView_Dot() > this->viewAngle) {
            canSee = true;
            // now calculate theta / phi of other unit
            double unitTheta{ core_functions::theta(differenceVector[0] / someItem.getView_Distance(), differenceVector[1] / someItem.getView_Distance()) };
            double unitPhi{ core_functions::phi(differenceVector[2] / someItem.getView_Distance()) };
            // use to calculate clock location
            int clock{ 4 }; // not left or right
            if (core_functions::thetaSubtract(this->theta, unitTheta) > this->viewAngleThreshold) { // right side
                clock = 5;
            }
            else if (core_functions::thetaSubtract(this->theta, unitTheta) < -this->viewAngleThreshold) { // left side
                clock = 3;
            }
            if (this->phi - unitPhi > this->viewAngleThreshold) { // above
                clock -= 3;
            }
            else if (unitPhi - this->phi > this->viewAngleThreshold) { // below
                clock += 3;
            }
            // (0 = top-left, 1 = top-front, 2 = top-right, 3 = left, 4 = front, ...)
            someItem.setView_Clock(clock);
        }
    }
    return canSee;
}

// Returns whether the current player is able to move into / through the inputted area (by ID)
bool Player::canMoveIntoArea(int areaID) {
    bool canMoveThrough = true;
    switch (areaID) {
        // Impassable areas
        case 1: // aquarium glass
        case 8: // aquarium lid
        case 11: // sewer stone
        case 20: // strong current
            canMoveThrough = false;
            break;

        // Depends
        case 2: // aquarium rock
            if (!(this->getUpgradeForelegs())) {
                canMoveThrough = false;
            }
            break;
        case 4: // aquarium water middle
            if (!(this->getUpgradeHindlegs())) {
                canMoveThrough = false;
            }
            break;
        case 5: // aquarium water top
        case 6: // aquarium water surface
            if (!(this->getUpgradeQuadrupedal1())) {
                canMoveThrough = false;
            }
            break;
        case 12: // sewer stone surface
            if (!(this->getUpgradeQuadrupedal2())) {
                canMoveThrough = false;
            }
            break;

        // Always passable
        case 3: // aquarium water bottom
        case 7: // aquarium air
        case 13: // sewer water bottom
        case 14:
        case 15: // sewer water
        case 16:
        case 17: // sewer water surface
        case 18:
        case 19: // sewer air
            break;

        default:
            std::cout << "ERROR: area ID " << areaID << " not found.\n";
            break;
    }
    return canMoveThrough;
}

// Regenerates health / energy / mana
void Player::regenerate(double timeElapsed) {
    int healthRegenerated = static_cast<int>(std::floor(timeElapsed * this->healthRegenerationSpeed));
    int energyRegenerated = static_cast<int>(std::floor(timeElapsed * this->energyRegenerationSpeed));
    int manaRegenerated = static_cast<int>(std::floor(timeElapsed * this->manaRegenerationSpeed));
    if (core_functions::linearProbability(std::fmod(timeElapsed, this->healthRegenerationSpeed))) {
        healthRegenerated++;
    }
    if (core_functions::linearProbability(std::fmod(timeElapsed, this->energyRegenerationSpeed))) {
        energyRegenerated++;
    }
    if (core_functions::linearProbability(std::fmod(timeElapsed, this->manaRegenerationSpeed))) {
        manaRegenerated++;
    }
    this->regenerateHealth(healthRegenerated);
    this->increaseEnergy(energyRegenerated);
    this->increaseMana(manaRegenerated);
}

// Consume the inputted item
int Player::consumeItem(Item item) {
    int newSubtier{ 0 };
    if (item.isConsumable()) {
        std::cout << "You consumed " << item.getName();
        bool firstReport{ false };
        if (item.getCurrHealth() != 0) {
            this->regenerateHealth(item.getCurrHealth());
            std::cout << " for " << item.getCurrHealth() << " health";
            firstReport = true;
        }
        if (item.getCurrEnergy() != 0) {
            this->increaseEnergy(item.getCurrEnergy());
            if (firstReport) {
                std::cout << ", " << item.getCurrEnergy() << " energy";
            }
            else {
                std::cout << " for " << item.getCurrEnergy() << " energy";
                firstReport = true;
            }
        }
        if (item.getCurrMana() != 0) {
            this->increaseMana(item.getCurrMana());
            if (firstReport) {
                std::cout << ", " << item.getCurrMana() << " mana";
            }
            else {
                std::cout << " for " << item.getCurrMana() << " mana";
                firstReport = true;
            }
        }
        if (item.getExperience() != 0) {
            if (firstReport) {
                std::cout << ", " << item.getExperience() << " experience";
            }
            else {
                std::cout << " for " << item.getExperience() << " experience";
                firstReport = true;
            }
        }
        if (item.getCredits() != 0) {
            this->addCredits(item.getCredits());
            if (firstReport) {
                std::cout << ", " << item.getCredits() << " experience";
            }
            else {
                std::cout << " for " << item.getCredits() << " experience";
                firstReport = true;
            }
        }
        if (item.getFouls() != 0) {
            this->addFouls(item.getFouls());
            if (firstReport) {
                std::cout << ", " << item.getFouls() << " fouls";
            }
            else {
                std::cout << " for " << item.getFouls() << " fouls";
                firstReport = true;
            }
        }
        std::cout << ".\n";
        newSubtier = this->addExperience(item.getExperience());
        this->itemsConsumed++;
    }
    return newSubtier;
}

// Functions to add / remove XP / currencies
int Player::addExperience(int x) {
    int newSubtier{ 0 };
    this->experience += x;
    while (true) { // need while loop in case player upgrades many levels at once
        if (this->experience >= core_functions::xpForNextLevel(this->level)) {
            this->experience -= core_functions::xpForNextLevel(this->level);
            this->level++;
            this->updateBaseStats();
            std::cout << "You leveled up to level " << this->level << ". Base stats increased.\n";
            if (this->level % constants::intersectionLevels == 0) { // new subtier
                newSubtier++;
            }
        }
        else {
            break;
        }
    }
    return newSubtier;
}

// Update Unit stats from level
void Player::updateBaseStats() {
    this->setBaseHealth(static_cast<int>(std::ceil(constants::healthBase + (constants::healthLevelRate * this->level * std::pow(constants::healthTierRate, this->level / constants::dimensionLevels)))));
    this->setMissingHealth(0);
    this->setBaseEnergy(static_cast<int>(std::ceil(constants::energyBase + (constants::energyLevelRate * this->level * std::pow(constants::energyTierRate, this->level / constants::dimensionLevels)))));
    this->setMissingEnergy(0);
    this->setBaseMana(static_cast<int>(std::ceil(constants::manaBase + (constants::manaLevelRate * this->level * std::pow(constants::manaTierRate, this->level / constants::dimensionLevels)))));
    this->setMissingMana(0);
    this->setBaseAttack(static_cast<int>(std::ceil(constants::attackBase + (constants::attackLevelRate * this->level * std::pow(constants::attackTierRate, this->level / constants::dimensionLevels)))));
    this->setBaseMagic(static_cast<int>(std::ceil(constants::magicBase + (constants::magicLevelRate * this->level * std::pow(constants::magicTierRate, this->level / constants::dimensionLevels)))));
    this->setBaseDefense(static_cast<int>(std::floor(constants::defenseBase + (constants::defenseLevelRate * this->level * std::pow(constants::defenseTierRate, this->level / constants::dimensionLevels)))));
    this->setBaseResist(static_cast<int>(std::floor(constants::resistBase + (constants::resistLevelRate * this->level * std::pow(constants::resistTierRate, this->level / constants::dimensionLevels)))));
    this->setBasePiercing(static_cast<int>(std::floor(constants::piercingBase + (constants::piercingLevelRate * this->level * std::pow(constants::piercingTierRate, this->level / constants::dimensionLevels)))));
    this->setBasePenetration(static_cast<int>(std::floor(constants::penetrationBase + (constants::penetrationLevelRate * this->level * std::pow(constants::penetrationTierRate, this->level / constants::dimensionLevels)))));
    this->setBaseDexterity(static_cast<int>(std::ceil(constants::dexterityBase + (constants::dexterityLevelRate * this->level * std::pow(constants::dexterityTierRate, this->level / constants::dimensionLevels)))));
}

// Forces player to choose an intersection upgrade
int Player::chooseNextUpgrade(int dimension) {
    // First scale regeneration speeds
    this->healthRegenerationSpeed += constants::defaultHealthRegenerationSpeed;
    this->energyRegenerationSpeed += constants::defaultEnergyRegenerationSpeed;
    this->manaRegenerationSpeed += constants::defaultManaRegenerationSpeed;
    int upgradeID{};
    // First make a list of the possible upgrades
    std::vector<int> possibleUpgrades{};
    // Tier I
    if (!(this->upgrade_forelegs)) {
        possibleUpgrades.push_back(1); // Foreleg Assimilation
    }
    if (!(this->upgrade_hindlegs)) {
        possibleUpgrades.push_back(2); // Hindleg Assimilation
    }
    if (!(this->upgrade_attention1)) {
        possibleUpgrades.push_back(3); // Basic Attention
    }
    if ((!(this->upgrade_quadrupedal1)) && (this->upgrade_forelegs) && (this->upgrade_hindlegs)) {
        possibleUpgrades.push_back(4); // Quadrupedal Assimilation
    }
    if ((!(this->upgrade_coordination1)) && (this->upgrade_quadrupedal1) && (this->upgrade_attention1)) {
        possibleUpgrades.push_back(5); // Basic Coordination
    }
    if ((!(this->upgrade_memory1)) && (this->upgrade_attention1)) {
        possibleUpgrades.push_back(6); // Obscure Memory
    }
    // Tier II
    if ((!(this->upgrade_quadrupedal2)) && (dimension > 1) && (this->upgrade_quadrupedal1)) {
        possibleUpgrades.push_back(11); // Quadrupedal Proficiency
    }
    if ((!(this->upgrade_coordination2)) && (dimension > 1) && (this->upgrade_coordination1)) {
        possibleUpgrades.push_back(12); // Detailed Coordination
    }
    if ((!(this->upgrade_learning1)) && (dimension > 1) && (this->upgrade_memory1)) {
        possibleUpgrades.push_back(13); // Instinctual Learning
    }
    if ((!(this->upgrade_attention2)) && (dimension > 1) && (this->upgrade_attention1)) {
        possibleUpgrades.push_back(14); // Detailed Attention
    }
    if ((!(this->upgrade_aggression1)) && (dimension > 1) && (this->upgrade_learning1) && (this->upgrade_quadrupedal2)) {
        possibleUpgrades.push_back(15); // Aggressive Instinct
    }
    if ((!(this->upgrade_protection1)) && (dimension > 1) && (this->upgrade_attention2) && (this->upgrade_coordination2)) {
        possibleUpgrades.push_back(16); // Protective Instinct
    }
    if ((!(this->upgrade_magic1)) && (dimension > 1) && (this->upgrade_learning1) && (this->upgrade_attention2)) {
        possibleUpgrades.push_back(17); // Basic Magic
    }
    if ((!(this->upgrade_ninja1)) && (dimension > 1) && (this->upgrade_quadrupedal2) && (this->upgrade_coordination2)) {
        possibleUpgrades.push_back(18); // Basic Dexterity
    }
    // Tier III
    if ((!(this->upgrade_aggression2)) && (dimension > 2) && (this->upgrade_aggression1) && (this->upgrade_attention2)) {
        possibleUpgrades.push_back(21); // Fierceness
    }
    if ((!(this->upgrade_protection2)) && (dimension > 2) && (this->upgrade_protection1) && (this->upgrade_learning1)) {
        possibleUpgrades.push_back(22); // Fortitude
    }
    if ((!(this->upgrade_magic2)) && (dimension > 2) && (this->upgrade_magic1) && (this->upgrade_coordination2)) {
        possibleUpgrades.push_back(23); // Thaumaturgy
    }
    if ((!(this->upgrade_ninja2)) && (dimension > 2) && (this->upgrade_ninja1) && (this->upgrade_quadrupedal2)) {
        possibleUpgrades.push_back(24); // Agility
    }
    if ((!(this->upgrade_memory2)) && (dimension > 2) && (this->upgrade_memory1)) {
        possibleUpgrades.push_back(25); // Lucid Memory
    }
    if ((!(this->upgrade_learning2)) && (dimension > 2) && (this->upgrade_learning1)) {
        possibleUpgrades.push_back(26); // Cognitive Learning
    }
    // Tier IV
    if ((!(this->upgrade_aggression3)) && (dimension > 3) && (this->upgrade_aggression2)) {
        possibleUpgrades.push_back(31); // Vicious Passion
    }
    if ((!(this->upgrade_protection3)) && (dimension > 3) && (this->upgrade_protection2)) {
        possibleUpgrades.push_back(32); // Tenacious Grit
    }
    if ((!(this->upgrade_magic3)) && (dimension > 3) && (this->upgrade_magic2)) {
        possibleUpgrades.push_back(33); // Magical Prowess
    }
    if ((!(this->upgrade_ninja3)) && (dimension > 3) && (this->upgrade_ninja2)) {
        possibleUpgrades.push_back(34); // Nimble Fleetness
    }
    // Then print choices
    for (size_t i = 0; i < possibleUpgrades.size(); i++) {
        std::cout << (i + 1) << ": " << this->getUpgradeName(possibleUpgrades.at(i)) << ": " <<
            this->getUpgradeDescription(possibleUpgrades.at(i)) << "\n";
    }
    // User then chooses
    while (true) {
        std::cout << "\nChoose an upgrade\n";
        std::string answer{};
        std::cin >> answer;
        if (core_functions::isPositiveInteger(answer)) {
            if ((stoul(answer) > 0) && (stoul(answer) <= possibleUpgrades.size())) {
                upgradeID = possibleUpgrades.at(stoul(answer) - 1);
                std::cout << "You chose " << this->getUpgradeName(possibleUpgrades.at(stoul(answer) - 1)) << ".\n";
                std::cout << this->getUpgradeDescription(upgradeID) << "\n\n";
                break;
            }
            else {
                std::cout << "Enter an integer between 1 and " << possibleUpgrades.size() << ".\n";
            }
        }
        else {
            std::cout << "Enter the integer corresponding to the upgrade you want.\n";
        }
    }
    this->activateUpgrade(upgradeID);
    return upgradeID;
}

// Activates upgrade and adds ID to player upgrade vector
void Player::activateUpgrade(int upgradeID) {
    bool realID{ true };
    switch (upgradeID) {
        // Dimension I intersections
        case 1:
            this->activateUpgradeForelegs();
            break;
        case 2:
            this->activateUpgradeHindlegs();
            break;
        case 3:
            this->activateUpgradeAttention1();
            break;
        case 4:
            this->activateUpgradeQuadrupedal1();
            break;
        case 5:
            this->activateUpgradeCoordination1();
            break;
        case 6:
            this->activateUpgradeMemory1();
            break;

        // Dimension II intersections
        case 11:
            this->activateUpgradeQuadrupedal2();
            break;
        case 12:
            this->activateUpgradeCoordination2();
            break;
        case 13:
            this->activateUpgradeLearning1();
            break;
        case 14:
            this->activateUpgradeAttention2();
            break;
        case 15:
            this->activateUpgradeAggression1();
            break;
        case 16:
            this->activateUpgradeProtection1();
            break;

        // Dimension III intersections
        case 17:
            this->activateUpgradeMagic1();
            break;
        case 18:
            this->activateUpgradeNinja1();
            break;
        case 21:
            this->activateUpgradeAggression2();
            break;
        case 22:
            this->activateUpgradeProtection2();
            break;
        case 23:
            this->activateUpgradeMagic2();
            break;
        case 24:
            this->activateUpgradeNinja2();
            break;
        case 25:
            this->activateUpgradeMemory2();
            break;
        case 26:
            this->activateUpgradeLearning2();
            break;

        // Dimension IV intersections
        case 31:
            this->activateUpgradeAggression3();
            break;
        case 32:
            this->activateUpgradeProtection3();
            break;
        case 33:
            this->activateUpgradeMagic3();
            break;
        case 34:
            this->activateUpgradeNinja3();
            break;

        // Dimension I researcher exclusive
        case 101:
            this->upgrade_equipWeapon = true;
            break;
        case 102:
            this->upgrade_equipOffhand = true;
            break;
        case 103:
            this->upgrade_equipHeadgear = true;
            break;
        case 104:
            this->upgrade_equipChestgear = true;
            break;
        case 105:
            this->upgrade_equipLeggear = true;
            break;
        case 106:
            this->upgrade_equipFootgear = true;
            break;
        case 107:
            this->upgrade_equipAccessory1 = true;
            break;
        case 108:
            this->upgrade_equipAccessory2 = true;
            break;
        case 109:
            this->maxInventorySlots += 2;
            break;

        // Dimension II researcher exclusive
        case 121:
            this->upgrade_equipTwohand = true;
            break;
        case 122:
            this->upgrade_equipAccessory3 = true;
            break;
        case 123:
            this->upgrade_equipAccessory4 = true;
            break;
        case 124:
            this->maxInventorySlots += 4;
            break;
        case 125:
            this->upgrade_itemsInBattle = true;
            break;
        case 126:
            this->upgrade_dismantleItems = true;
            break;

        default:
            std::cout << "ERROR: upgradeID not found.\n\n";
            realID = false;
            break;
    }
    if (realID) {
        this->upgradesActivated.push_back(upgradeID);
    }
}

// Return description given upgrade ID
std::string Player::getUpgradeDescription(int upgradeID) {
    std::string description{};
    switch (upgradeID) {
        case 1: // forelegs
            description = "consciously control your forelegs to shovel food into your mouth and "
                "dig through mud and rocks.\n   -Learn battle ability \"nibble\"\n   -Move in "
                "aquarium rock\n   -Inventory space +1\n   -Max move distance = 6 cm\n";
            break;
        case 2: // hindlegs
            description = "consciously control your hindlegs to push off the ground, reaching "
                "higher places and lunging at food.\n   -Learn battle ability \"lunge\"\n   -Move "
                "higher in aquarium water.\n   -Inventory space +1\n   -Max move distance = 6 cm\n";
            break;
        case 3: // attention 1
            description = "notice your surroundings and you'll see more information.\n   -See basic "
                "stats / spatial information\n   -View distance = 15 cm\n   -View angle = 60 degrees"
                "\n   -Turn angle = 45 degrees\n";
            break;
        case 4: // quadrupedal 1
            description = "use your forelegs and hindlegs in unison with your conscious.\n   -Learn "
                "battle ability \"flail\"\n   -Swim in any water\n   -Move distance = 8 cm\n   -"
                "Inventory space +1\n   -Can equip accessory 1\n";
            break;
        case 5: // coordination 1
            description = "your consciousness can control your brain to coordinate your entire "
                "body.\n   -Learn \"moveto\" and \"turnto\" commands to move and turn toward "
                "specific units\n   -Learn \"ignore\" command to ignore units, items, or the "
                "spatial dimension\n   -Can specify turn angle / move distance amount\n   -Inventory "
                "space +2\n   -Can equip accessory 2\n";
            break;
        case 6: // memory 1
            description = "begin to remember what you once knew so clearly.\n   -Remember units/"
                "items/abilities you encounter and recall these with \"inquire\"\n   -Inventory "
                "space +4\n   -Can equip weapon\n";
            break;
        case 11: // quadrupedal 2
            description = "developing proficiency with your limbs makes you much more versatile.\n"
                "   -Move on land\n   -Move distance = 12 cm\n   -Inventory space +4\n   -Can "
                "equip weapon / offhand\n";
            break;
        case 12: // coordination 2
            description = "your whole-body coordination extends to even small details.\n   -Learn "
                "\"face\" to face a specific direction\n   -Learn \"consume all\" to consume all "
                "consumable items in range\n   -Learn \"pickup drops\" to auto-pickup enemy unit "
                "drops\n   -Inventory space +4\n   -Can equip accessory 3\n";
            break;
        case 13: // learning 1
            description = "begin to relearn the extensives skills you once knew.\n   -Choose your "
                "color\n   -Learn battle ability \"wisp\" and basic abilities of your color\n   -Inventory "
                "space +8\n   -Can interact with allied units\n"
                "";
            break;
        case 14: // attention 2
            description = "attention to detail is essential to break out of your biological "
                "limitations.\n   -See advanced stats / spatial information\n   -View distance = "
                "25 cm\n   -View angle = 90 degrees\n   -Turn angle = 90 degrees\n";
            break;
        case 15: // aggression 1
            description = "tap into your aggressive instinct and learn basic aggressive tactics.\n"
                "   -Learn battle abilities \"hammer\" and \"bite\"\n   -Increase your base attack "
                "and piercing\n   -Can equip two-handed weapons\n";
            break;
        case 16: // protection 1
            description = "tap into your defensive instinct and learn basic defensive tactics.\n"
                "   -Learn battle abilities \"defend\" and \"resolve\"\n   -Increase your base "
                "defense and resist\n   -Can equip chestgear and leggear\n";
            break;
        case 17: // magic 1
            description = "learn basic magical tactics.\n   -Chance to re-choose your color.\n   "
                "-Learn battle abilities \"bolt\" more spells of your color\n   -Increase your "
                "base magic and penetration\n   -Can equip headgear\n";
            break;
        case 18: // ninja 1
            description = "Learn basic ninja frogjitsu tactics.\n   -Learn battle abilities "
                "\"swiftness\" and \"slowness\"\n   -Increase your base dexterity\n   -Move "
                "distance = 16 cm\n   -Can equip footgear\n";
            break;
        case 21: // aggression 2
            description = ".";
            break;
        case 22: // protection 2
            description = ".";
            break;
        case 23: // magic 2
            description = ".";
            break;
        case 24: // ninja 2
            description = ".";
            break;
        case 25: // memory 2
            description = ".";
            break;
        case 26: // learning 2
            description = ".";
            break;
        case 31: // aggression 3
            description = ".";
            break;
        case 32: // protection 3
            description = ".";
            break;
        case 33: // magic 3
            description = ".";
            break;
        case 34: // ninja 3
            description = ".";
            break;
        case 101: // equip weapon
            description = "Learn how to equip a weapon.\n";
            break;
        case 102: // equip offhand
            description = "Learn how to equip an offhand.\n";
            break;
        case 103: // equip headgear
            description = "Learn how to equip headgear.\n";
            break;
        case 104: // equip chestgear
            description = "Learn how to equip chestgear.\n";
            break;
        case 105: // equip leggear
            description = "Learn how to equip leggear.\n";
            break;
        case 106: // equip footgear
            description = "Learn how to equip footgear.\n";
            break;
        case 107: // equip accessory1
            description = "Learn how to use your first accessory slot.\n";
            break;
        case 108: // equip accessory2
            description = "Learn how to use your second accessory slot.\n";
            break;
        case 109: // skin flaps
            description = "Grow skin flaps to stuff more items into.\n";
            break;
        case 121: // equip twohand
            description = "Learn how to equip a two-handed weapon.\n";
            break;
        case 122: // equip accessory3
            description = "Learn how to use your third accessory slot.\n";
            break;
        case 123: // equip accessory4
            description = "Learn how to use your fourth accessory slot.\n";
            break;
        case 124: // +4 inventory slots
            description = "Develop Pockets on your back to store more items.\n";
            break;
        case 125: // items in battle
            description = "Allows you to use items in battle for your turn.\n";
            break;
        case 126: // dismantle items
            description = "Allows you to dismantle items into their respective materials.\n";
            break;
        default:
            std::cout << "ERROR: upgradeID not found.\n\n";
            break;
    }
    return description;
}

// Return name given upgrade ID
std::string Player::getUpgradeName(int upgradeID) {
    std::string upgradeName{};
    switch (upgradeID) {
        case 1: // forelegs
            upgradeName = "Foreleg Assimilation";
            break;
        case 2: // hindlegs
            upgradeName = "Hindleg Assimilation";
            break;
        case 3: // attention 1
            upgradeName = "Basic Attention";
            break;
        case 4: // quadrupedal 1
            upgradeName = "Quadrupedal Assimilation";
            break;
        case 5: // coordination 1
            upgradeName = "Basic Coordination";
            break;
        case 6: // memory 1
            upgradeName = "Obscure Memory";
            break;
        case 11: // quadrupedal 2
            upgradeName = "Quadrupedal Proficiency";
            break;
        case 12: // coordination 2
            upgradeName = "Detailed Coordination";
            break;
        case 13: // learning 1
            upgradeName = "Instinctual Learning";
            break;
        case 14: // attention 2
            upgradeName = "Detailed Attention";
            break;
        case 15: // aggression 1
            upgradeName = "Aggressive Instinct";
            break;
        case 16: // protection 1
            upgradeName = "Protective Instinct";
            break;
        case 17: // magic 1
            upgradeName = "Basic Magic";
            break;
        case 18: // ninja 1
            upgradeName = "Basic Dexterity";
            break;
        case 21: // aggression 2
            upgradeName = "Fierceness";
            break;
        case 22: // protection 2
            upgradeName = "Fortitude";
            break;
        case 23: // magic 2
            upgradeName = "Thaumaturgy";
            break;
        case 24: // ninja 2
            upgradeName = "Agility";
            break;
        case 25: // memory 2
            upgradeName = "Lucid Memory";
            break;
        case 26: // learning 2
            upgradeName = "Cognitive Learning";
            break;
        case 31: // aggression 3
            upgradeName = "Vicious Passion";
            break;
        case 32: // protection 3
            upgradeName = "Tenacious Grit";
            break;
        case 33: // magic 3
            upgradeName = "Magical Prowess";
            break;
        case 34: // ninja 3
            upgradeName = "Nimble Fleetness";
            break;
        case 101: // equip weapon
            upgradeName = "Equip Weapon";
            break;
        case 102: // equip offhand
            upgradeName = "Equip Offhand";
            break;
        case 103: // equip headgear
            upgradeName = "Equip Headgear";
            break;
        case 104: // equip chestgear
            upgradeName = "Equip Chestgear";
            break;
        case 105: // equip leggear
            upgradeName = "Equip Leggear";
            break;
        case 106: // equip footgear
            upgradeName = "Equip Footgear";
            break;
        case 107: // equip accessory1
            upgradeName = "Equip Accessory 1";
            break;
        case 108: // equip accessory2
            upgradeName = "Equip Accessory 2";
            break;
        case 109: // +2 inventory slots
            upgradeName = "Skin Flaps";
            break;
        case 121: // equip twohand
            upgradeName = "Equip Twohand";
            break;
        case 122: // equip accessory3
            upgradeName = "Equip Accessory 3";
            break;
        case 123: // equip accessory4
            upgradeName = "Equip Accessory 4";
            break;
        case 124: // +4 inventory slots
            upgradeName = "P. pipa Pockets";
            break;
        case 125: // use items in battle
            upgradeName = "Battle Snacks";
            break;
        case 126: // dismantle items
            upgradeName = "Dismantle Items";
            break;
        default:
            std::cout << "ERROR: upgradeID not found.\n\n";
            break;
    }
    return upgradeName;
}

// Returns foul cost of upgrade given upgrade ID
int Player::getUpgradeCost(int upgradeID) {
    int upgradeCost{};
    switch (upgradeID) {
        case 101: // equip weapon
            upgradeCost = 20;
            break;
        case 102: // equip offhand
            upgradeCost = 50;
            break;
        case 103: // equip headgear
            upgradeCost = 100;
            break;
        case 104: // equip chestgear
            upgradeCost = 100;
            break;
        case 105: // equip leggear
            upgradeCost = 100;
            break;
        case 106: // equip footgear
            upgradeCost = 100;
            break;
        case 107: // equip accessory1
            upgradeCost = 10;
            break;
        case 108: // equip accessory2
            upgradeCost = 20;
            break;
        case 109: // +2 inventory slots
            upgradeCost = 25;
            break;
        case 121: // equip twohand
            upgradeCost = 200;
            break;
        case 122: // equip accessory3
            upgradeCost = 50;
            break;
        case 123: // equip accessory4
            upgradeCost = 100;
            break;
        case 124: // +4 inventory slots
            upgradeCost = 100;
            break;
        case 125: // use items in battle
            upgradeCost = 150;
            break;
        case 126: // dismantle items
            upgradeCost = 150;
            break;
        default:
            std::cout << "ERROR: upgradeID not found.\n\n";
            break;
    }
    return upgradeCost;
}

// Returns whether the player has activated the inputted upgrade or not
bool Player::hasActivatedUpgrade(int upgradeID) {
    return std::find(this->upgradesActivated.begin(), upgradesActivated.end(), upgradeID) != this->upgradesActivated.end();
}

// Returns whether the player has learned the inputted ability
bool Player::hasLearnedAbility(std::string abilityName) {
    bool hasLearned{ false };
    for (Ability i : this->getBattleAbilities()) {
        if (i.getName().compare(abilityName) == 0) {
            hasLearned = true;
            break;
        }
    }
    return hasLearned;
}

// Add / remove currency
void Player::addCredits(int x) {
    this->credits += x;
}
void Player::removeCredits(int x) {
    this->credits -= x;
}
void Player::addFouls(int x) {
    this->fouls += x;
}
void Player::removeFouls(int x) {
    this->fouls -= x;
}

// Choose another player color
void Player::chooseColor(int code) {
    std::vector<std::pair<int, std::string>> choices{};
    switch (code) {
        case 1:
            choices.push_back(std::pair<int, std::string>{1, "blue - water"});
            choices.push_back(std::pair<int, std::string>{2, "red - fire"});
            choices.push_back(std::pair<int, std::string>{3, "brown - earth"});
            choices.push_back(std::pair<int, std::string>{4, "cyan - ice"});
            choices.push_back(std::pair<int, std::string>{5, "orange - air"});
            break;
        default:
            std::cout << "Color choose code " << code << " not found.\n";
            break;
    }
    if (this->isColorless()) {
        std::cout << "Choose your magic color:\n";
    }
    else {
        std::cout << "Choose your magic color (will replace your current color):\n";
    }
    for (size_t i = 0; i < choices.size(); i++) {
        std::cout << i+1 << ": " << choices.at(i).second << "\n";
    }
    while (true) {
        std::string choice{};
        std::getline(std::cin >> std::ws, choice); // receive input
        if (core_functions::isPositiveInteger(choice)) {
            if ((stoul(choice) > 0) && (stoul(choice) <= choices.size())) {
                std::cout << "Chose " << choices.at(stoul(choice) - 1).second << "\n\n";
                this->setUnitColorFromChoice(choices.at(stoul(choice) - 1).first);
                break;
            }
            else {
                std::cout << "Choose an integer corresponding to the color you want.\n";
            }
        }
        else {
            std::cout << "Choose an integer corresponding to the color you want.\n";
        }
    }
    core_functions::pauseProgram(constants::shortPauseTime);
    core_functions::requireEnter();
    std::cout << "\n";
}

// Adds colored spells of the player's color and spell class based on input code
void Player::addColorSpells(int code) {
    switch (code) {
        case 1:
            if (this->isBlue()) {
                this->addBattleAbilities({ "wisp", "dunk", "splash" });
            }
            else if (this->isRed()) {
                this->addBattleAbilities({ "wisp", "burn", "flame" });
            }
            else if (this->isBrown()) {
                this->addBattleAbilities({ "wisp", "rot", "dust" });
            }
            else if (this->isCyan()) {
                this->addBattleAbilities({ "wisp", "chill", "frost" });
            }
            else if (this->isOrange()) {
                this->addBattleAbilities({ "wisp", "infect", "breeze" });
            }
            else if (this->isPurple()) {
                this->addBattleAbilities({ "wisp", "shake", "pull" });
            }
            else if (this->isYellow()) {
                this->addBattleAbilities({ "wisp", "shock", "spark" });
            }
            else if (this->isMagenta()) {
                this->addBattleAbilities({ "wisp", "destabilize", "gammaray" });
            }
            else if (this->isBlack()) {
                this->addBattleAbilities({ "wisp", "obscure", "shadow" });
            }
            else if (this->isWhite()) {
                this->addBattleAbilities({ "wisp", "brighten", "ray" });
            }
            else if (this->isGreen()) {
                this->addBattleAbilities({ "wisp", "balance", "???" });
            }
            break;
        case 2:
            if (this->isBlue()) {
                this->addBattleAbilities({ "splash", "waterstrike", "stream" });
            }
            else if (this->isRed()) {
                this->addBattleAbilities({ "flame", "firestrike", "fire" });
            }
            else if (this->isBrown()) {
                this->addBattleAbilities({ "dust", "earthstrike", "dirt" });
            }
            else if (this->isCyan()) {
                this->addBattleAbilities({ "frost", "icestrike", "crystal" });
            }
            else if (this->isOrange()) {
                this->addBattleAbilities({ "breeze", "airstrike", "wind" });
            }
            else if (this->isPurple()) {
                this->addBattleAbilities({ "pull", "gravitystrike", "orbit" });
            }
            else if (this->isYellow()) {
                this->addBattleAbilities({ "spark", "electricstrike", "static" });
            }
            else if (this->isMagenta()) {
                this->addBattleAbilities({ "gammaray", "nuclearstrike", "betaray" });
            }
            else if (this->isBlack()) {
                this->addBattleAbilities({ "shadow", "darkstrike", "darkness" });
            }
            else if (this->isWhite()) {
                this->addBattleAbilities({ "ray", "lightstrike", "beam" });
            }
            else if (this->isGreen()) {
                this->addBattleAbilities({ "???", "naturestrike", "???" });
            }
            break;
        default:
            std::cout << "Add color spells code " << code << " not found.\n";
    }
}

// Print player information
void Player::printPlayerInfo() {
    // First the name and color
    std::cout << this->getName();
    if (this->upgrade_learning1) {
        std::cout << " (" << this->getUnitColorString() << ")";
    }
    // Then the level and experience
    std::cout << "\nLevel:      " << this->level;
    if (this->upgrade_attention1) {
        std::cout << " (dimension " << (this->level / constants::dimensionLevels) + 1 << ", intersection " <<
            (((this->level % constants::dimensionLevels) / constants::intersectionLevels) + 1) << ")";
    }
    int xpNextLevel{ core_functions::xpForNextLevel(this->level) };
    std::string experienceString{ "Experience: " + std::to_string(this->experience) + "/" + std::to_string(xpNextLevel) + " "};
    std::cout << "\n" << experienceString << core_functions::makeQuantityBar(this->experience, xpNextLevel, constants::printViewSpatialSize / 2 - experienceString.length());
    // Then print out credits and fouls
    if (this->upgrade_attention1) {
        std::string creditString{ "Credits: " + std::to_string(this->credits) };
        std::string foulString{ "Fouls: " + std::to_string(this->fouls) };
        // Put both credits and fouls on one line taking up half the console width
        std::cout << "\n" << creditString << core_functions::stringMultiply(" ", constants::printViewSpatialSize / 2 - creditString.length() - foulString.length()) << foulString;
    }
    // Then finally the health / energy / mana bars
    std::vector<std::string> barQuantities{};
    barQuantities.push_back("Health: " + std::to_string(this->getCurrHealth()) + "/" + std::to_string(this->getMaxHealth()) + " ");
    barQuantities.push_back("Energy: " + std::to_string(this->getCurrEnergy()) + "/" + std::to_string(this->getMaxEnergy()) + " ");
    if (this->upgrade_attention1) {
        barQuantities.push_back("Mana:   " + std::to_string(this->getCurrMana()) + "/" + std::to_string(this->getMaxMana()) + " ");
    }
    // Find largest string to align bars
    int largestString{ 0 };
    for (std::string i : barQuantities) {
        if (i.length() > largestString) {
            largestString = i.length();
        }
    }
    std::cout << "\n" << barQuantities.at(0) << core_functions::stringMultiply(" ", largestString - barQuantities.at(0).length()) <<
        core_functions::makeQuantityBar(this->getCurrHealth(), this->getMaxHealth(), constants::printViewSpatialSize / 2 - largestString);
    std::cout << "\n" << barQuantities.at(1) << core_functions::stringMultiply(" ", largestString - barQuantities.at(1).length()) <<
        core_functions::makeQuantityBar(this->getCurrEnergy(), this->getMaxEnergy(), constants::printViewSpatialSize / 2 - largestString);
    if (this->upgrade_attention1) {
        std::cout << "\n" << barQuantities.at(2) << core_functions::stringMultiply(" ", largestString - barQuantities.at(2).length()) <<
            core_functions::makeQuantityBar(this->getCurrMana(), this->getMaxMana(), constants::printViewSpatialSize / 2 - largestString);
    }
    if (this->upgrade_attention1) {
        std::cout << "\n\nAttack:      " << this->getAttack();
        std::cout << "\nMagic:       " << this->getMagic();
        std::cout << "\nDefense:     " << this->getDefense();
        std::cout << "\nResist:      " << this->getResist();
        std::cout << "\nPiercing:    " << this->getPiercing();
        std::cout << "\nPenetration: " << this->getPenetration();
        std::cout << "\nDexterity:   " << this->getDexterity();
    }
    if (this->upgrade_attention2) {
        std::cout << "\n\nMax Move Distance:  " << this->getMaxMoveDistance() << " m";
        std::cout << "\nMax Turn Angle:     " << std::round(180.0 * this->maxTurnAngle / constants::Pi) << " degrees";
        std::cout << "\nView Distance:      " << this->getViewDistance() << " m";
        std::cout << "\nView Angle:         " << static_cast<int>(std::round(180.0 *
            std::acos(this->viewAngle) / constants::Pi)) << " degrees";
        std::cout << "\nLocation:           " << std::round(constants::roundAmountI * this->getXLocation()) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * this->getYLocation()) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * this->getZLocation()) / constants::roundAmountD;
        std::cout << "\nVelocity:           " << std::round(constants::roundAmountI * this->getVelocity()[0]) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * this->getVelocity()[1]) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * this->getVelocity()[2]) / constants::roundAmountD;
        std::cout << "\nFacing (cartesian): " << std::round(constants::roundAmountI * this->xFacing) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * this->yFacing) / constants::roundAmountD << " " << std::round(1000 * this->zFacing) / constants::roundAmountD;
        std::cout << "\nFacing (spherical): " <<
            std::round(constants::roundAmountI * 180 * this->theta / constants::Pi) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * 180 * this->phi / constants::Pi) / constants::roundAmountD;
    }
    if (constants::TESTMODE) {
        std::cout << "\nLocation:           " << std::round(constants::roundAmountI * this->getXLocation()) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * this->getYLocation()) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * this->getZLocation()) / constants::roundAmountD;
        std::cout << "\nVelocity:           " << std::round(constants::roundAmountI * this->getVelocity()[0]) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * this->getVelocity()[1]) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * this->getVelocity()[2]) / constants::roundAmountD;
        std::cout << "\nFacing (cartesian): " << std::round(constants::roundAmountI * this->xFacing) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * this->yFacing) / constants::roundAmountD << " " << std::round(1000 * this->zFacing) / constants::roundAmountD;
        std::cout << "\nFacing (spherical): " <<
            std::round(constants::roundAmountI * 180 * this->theta / constants::Pi) / constants::roundAmountD << " " <<
            std::round(constants::roundAmountI * 180 * this->phi / constants::Pi) / constants::roundAmountD;
    }
    std::cout << "\n\n";
}

// Displays achievements this player has accomplished
void Player::printAchievements() {
    int largestName{ 0 };
    for (Achievement i : this->achievementsCompleted) {
        if (i.getName().size() > largestName) {
            largestName = i.getName().size();
        }
    }
    for (Achievement i : this->achievementsCompleted) {
        i.printAchievement(largestName);
    }
}
// Add achievement
void Player::addAchievement(Achievement i) {
    this->achievementsCompleted.push_back(i);
    if (i.getName().compare("Monster Slayer II") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Monster Slayer I") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
    else if (i.getName().compare("Monster Slayer III") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Monster Slayer II") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
    else if (i.getName().compare("Monster Slayer IV") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Monster Slayer III") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
    else if (i.getName().compare("Monster Slayer V") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Monster Slayer IV") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
    else if (i.getName().compare("Traveler II") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Traveler I") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
    else if (i.getName().compare("Traveler III") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Traveler II") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
    else if (i.getName().compare("Traveler IV") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Traveler III") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
    else if (i.getName().compare("Traveler V") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Traveler IV") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
    else if (i.getName().compare("Consumer II") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Consumer I") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
    else if (i.getName().compare("Consumer III") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Consumer II") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
    else if (i.getName().compare("Consumer IV") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Consumer III") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
    else if (i.getName().compare("Consumer V") == 0) {
        for (size_t j = 0; j < this->achievementsCompleted.size(); j++) {
            if (this->achievementsCompleted.at(j).getName().compare("Consumer IV") == 0) {
                this->achievementsCompleted.erase(this->achievementsCompleted.begin() + j);
                break;
            }
        }
    }
}

// Inventory Functions
// Display inventory
void Player::displayInventory(int itemType) {
 // NOTE: Below is key for the itemType variable (default is 0)
 // (0 = all, 1 = gear, 2 = weapon, 3 = offhand, 4 = twohand, 5 = headgear, 6 = chestgear, 7 = leggear, 8 = footgear, 9 = accessory, 10 = consumables)
    if ((itemType == 0) || (itemType == 1) || (itemType == 5)) {
        if (this->canEquipHeadgear()) {
            std::cout << "Headgear: ";
            if (this->headgear.getID() != -1) {
               this->headgear.printItemInfoBrief();
            }
            else {
                std::cout << "--";
            }
            std::cout << "\n";
        }
    }
    if ((itemType == 0) || (itemType == 1) || (itemType == 2)) {
        if (this->canEquipWeapon()) {
            std::cout << "Weapon: ";
            if (this->weapon.getID() != -1) {
                this->weapon.printItemInfoBrief();
            }
            else {
                std::cout << "--";
            }
            std::cout << "\n";
        }
    }
    if ((itemType == 0) || (itemType == 1) || (itemType == 3)) {
        if (this->canEquipOffhand()) {
            std::cout << "Offhand: ";
            if (this->offhand.getID() != -1) {
                this->offhand.printItemInfoBrief();
            }
            else {
                std::cout << "--";
            }
            std::cout << "\n";
        }
    }
    if ((itemType == 0) || (itemType == 1) || (itemType == 4)) {
        if (this->canEquipTwohand()) {
            std::cout << "Twohand: ";
            if (this->twohand.getID() != -1) {
                this->twohand.printItemInfoBrief();
            }
            else {
                std::cout << "--";
            }
            std::cout << "\n";
        }
    }
    if ((itemType == 0) || (itemType == 1) || (itemType == 6)) {
        if (this->canEquipChestgear()) {
            std::cout << "Chestgear: ";
            if (this->chestgear.getID() != -1) {
                this->chestgear.printItemInfoBrief();
            }
            else {
                std::cout << "--";
            }
            std::cout << "\n";
        }
    }
    if ((itemType == 0) || (itemType == 1) || (itemType == 7)) {
        if (this->canEquipLeggear()) {
            std::cout << "Leggear: ";
            if (this->leggear.getID() != -1) {
                this->leggear.printItemInfoBrief();
            }
            else {
                std::cout << "--";
            }
            std::cout << "\n";
        }
    }
    if ((itemType == 0) || (itemType == 1) || (itemType == 8)) {
        if (this->canEquipFootgear()) {
            std::cout << "Footgear: ";
            if (this->footgear.getID() != -1) {
                this->footgear.printItemInfoBrief();
            }
            else {
                std::cout << "--";
            }
            std::cout << "\n";
        }
    }
    if ((itemType == 0) || (itemType == 1) || (itemType == 9)) {
        if (this->canEquipAccessory1()) {
            std::cout << "Accessory1: ";
            if (this->accessory1.getID() != -1) {
                this->accessory1.printItemInfoBrief();
            }
            else {
                std::cout << "--";
            }
            std::cout << "\n";
        }
        if (this->canEquipAccessory2()) {
            std::cout << "Accessory2: ";
            if (this->accessory2.getID() != -1) {
                this->accessory2.printItemInfoBrief();
            }
            else {
                std::cout << "--";
            }
            std::cout << "\n";
        }
        if (this->canEquipAccessory3()) {
            std::cout << "Accesssory3: ";
            if (this->accessory3.getID() != -1) {
                this->accessory3.printItemInfoBrief();
            }
            else {
                std::cout << "--";
            }
            std::cout << "\n";
        }
        if (this->canEquipAccessory4()) {
            std::cout << "Accessory4: ";
            if (this->accessory4.getID() != -1) {
                this->accessory4.printItemInfoBrief();
            }
            else {
                std::cout << "--";
            }
            std::cout << "\n";
        }
    }
    if (itemType != 1) {
 // (0 = all, 1 = gear, 2 = weapon, 3 = offhand, 4 = twohand, 5 = headgear, 6 = chestgear, 7 = leggear, 8 = footgear, 9 = accessory, 10 = consumables)
        std::cout << this->getName() << "'s inventory: " << this->playerInventory.size() << "/" <<
            this->maxInventorySlots << " slots full.\n";
        for (size_t i{ 0 }; i < this->playerInventory.size(); i++) {
            bool displayItem{ true };
            if ((itemType == 2) && (!this->playerInventory.at(i).isWeapon())) {
                displayItem = false;
            }
            if ((itemType == 3) && (!this->playerInventory.at(i).isOffhand())) {
                displayItem = false;
            }
            if ((itemType == 4) && (!this->playerInventory.at(i).isTwohand())) {
                displayItem = false;
            }
            if ((itemType == 5) && (!this->playerInventory.at(i).isHeadgear())) {
                displayItem = false;
            }
            if ((itemType == 6) && (!this->playerInventory.at(i).isChestgear())) {
                displayItem = false;
            }
            if ((itemType == 7) && (!this->playerInventory.at(i).isLeggear())) {
                displayItem = false;
            }
            if ((itemType == 8) && (!this->playerInventory.at(i).isFootgear())) {
                displayItem = false;
            }
            if ((itemType == 9) && (!this->playerInventory.at(i).isAccessory())) {
                displayItem = false;
            }
            if ((itemType == 10) && (!this->playerInventory.at(i).isConsumable())) {
                displayItem = false;
            }
            if (displayItem) {
                if (itemType != 0) {
                    std::cout << (i + 1) << ": ";
                    this->playerInventory.at(i).printItemInfoBrief();
                }
                std::cout << (i + 1) << ": " << this->playerInventory.at(i).getName() << "\n";
            }
        }
        std::cout << "\n";
    }
}
// Increase slots
void Player::increaseInventorySlots(int amount) {
    this->maxInventorySlots += amount;
}
// Add item to inventory
void Player::inventoryItem(Item newItem) {
    // Stack consumables / materials
    if ((newItem.isConsumable()) || (newItem.isMaterial())) {
        int i{ this->hasItem(newItem.getID()) };
        if (i != -1) {
            this->playerInventory.at(i).addStack();
            return;
        }
    }
    // Push back all others
    if (this->hasInventorySpace()) {
        this->playerInventory.push_back(newItem);
    }
    // No space left
    else {
        std::cout << "ERROR: no room in inventory.\n";
    }
}
// Checks if empty inventory slots exist
bool Player::hasInventorySpace() {
    if (this->maxInventorySlots > this->playerInventory.size()) {
        return true;
    }
    else {
        return false;
    }
}
// Use item from inventory
void Player::useItem(int index) {
    if ((index >= 0) && (index < this->playerInventory.size())) {
        if (this->playerInventory.at(index).isConsumable()) {
            this->consumeItem(this->playerInventory.at(index));
            this->removeItem(index, 1);
        }
        else {
            std::cout << this->playerInventory.at(index).getName() << " not consumable.\n";
        }
    }
    else {
        std::cout << "ERROR: Inventory index out of range.\n";
    }
}
// Upgrade item from inventory
void Player::upgradeItem(int index) {
    if ((index >= 0) && (index < this->playerInventory.size())) {
        this->playerInventory.at(index).upgradeItem();
    }
    else {
        std::cout << "ERROR: Inventory index out of range.\n";
    }
}
// Returns index of inputted itemID (or -1 if not found)
int Player::hasItem(int itemID) {
    for (int i{ 0 }; i < this->playerInventory.size(); i++) {
        if (this->playerInventory.at(i).getID() == itemID) {
            return i;
        }
    }
    return -1;
}
// Remove item from inventory
void Player::removeItem(int index, int removeStack) {
    if ((index >= 0) && (index < this->playerInventory.size())) {
        if (removeStack > this->playerInventory.at(index).getStack()) {
            std::cout << "ERROR: attempted to remove more stack than exists. Item deleted\n";
            this->playerInventory.erase(this->playerInventory.begin() + index);
        }
        else if ((removeStack == 0) || (this->playerInventory.at(index).getStack() == removeStack)) {
            this->playerInventory.erase(this->playerInventory.begin() + index);
        }
        else {
            this->playerInventory.at(index).removeStack(removeStack);
        }
    }
    else {
        std::cout << "ERROR: Inventory index out of range.\n";
    }
}
// Equip item from inventory
void Player::equipItem(int index) {
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (this->playerInventory.at(index).isWeapon()) {
        this->equipWeapon(index);
    }
    else if (this->playerInventory.at(index).isOffhand()) {
        this->equipOffhand(index);
    }
    else if (this->playerInventory.at(index).isTwohand()) {
        this->equipTwohand(index);
    }
    else if (this->playerInventory.at(index).isHeadgear()) {
        this->equipHeadgear(index);
    }
    else if (this->playerInventory.at(index).isChestgear()) {
        this->equipChestgear(index);
    }
    else if (this->playerInventory.at(index).isLeggear()) {
        this->equipLeggear(index);
    }
    else if (this->playerInventory.at(index).isFootgear()) {
        this->equipFootgear(index);
    }
    else if (this->playerInventory.at(index).isAccessory()) {
        if ((this->accessory1.getID() == -1) && (this->canEquipAccessory1())) {
            this->equipAccessory1(index);
        }
        else if ((this->accessory2.getID() == -1) && (this->canEquipAccessory2())) {
            this->equipAccessory2(index);
        }
        else if ((this->accessory3.getID() == -1) && (this->canEquipAccessory3())) {
            this->equipAccessory3(index);
        }
        else if ((this->accessory4.getID() == -1) && (this->canEquipAccessory4())) {
            this->equipAccessory4(index);
        }
        else if (this->canEquipAccessory1()) {
            this->equipAccessory1(index);
        }
        else {
            std::cout << "You do not have the ability to use an accessory.\n";
        }
    }
    else {
        std::cout << "Item cannot be equipped.\n";
    }
}
void Player::equipWeapon(int index) {
    if (!this->canEquipWeapon()) {
        std::cout << "You don't have the ability to wield a weapon.\n";
        return;
    }
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (!this->playerInventory.at(index).isWeapon()) {
        std::cout << "ERROR: " << this->playerInventory.at(index).getName() << " is not a weapon.\n";
        return;
    }
    std::cout << "Equipped " << this->playerInventory.at(index).getName() << " as your weapon.\n";
    if (this->weapon.getID() != -1) { // unequip first
        this->playerInventory.push_back(this->weapon);
    }
    this->weapon = this->playerInventory.at(index);
    this->playerInventory.erase(this->playerInventory.begin() + index);
}
void Player::equipOffhand(int index) {
    if (!this->canEquipOffhand()) {
        std::cout << "You don't have the ability to carry an offhand.\n";
        return;
    }
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (!this->playerInventory.at(index).isOffhand()) {
        std::cout << "ERROR: " << this->playerInventory.at(index).getName() << " is not an offhand.\n";
        return;
    }
    std::cout << "Equipped " << this->playerInventory.at(index).getName() << " as your offhand.\n";
    if (this->offhand.getID() != -1) { // unequip first
        this->playerInventory.push_back(this->offhand);
    }
    this->offhand = this->playerInventory.at(index);
    this->playerInventory.erase(this->playerInventory.begin() + index);
}
void Player::equipTwohand(int index) {
    if (!this->canEquipTwohand()) {
        std::cout << "You don't have the ability to carry a twohand.\n";
        return;
    }
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (!this->playerInventory.at(index).isTwohand()) {
        std::cout << "ERROR: " << this->playerInventory.at(index).getName() << " is not a twohand.\n";
        return;
    }
    std::cout << "Equipped " << this->playerInventory.at(index).getName() << " as your twohand.\n";
    if (this->weapon.getID() != -1) { // unequip first
        this->playerInventory.push_back(this->weapon);
    }
    if (this->offhand.getID() != -1) {
        this->playerInventory.push_back(this->offhand);
    }
    this->twohand = this->playerInventory.at(index);
    this->playerInventory.erase(this->playerInventory.begin() + index);
}
void Player::equipHeadgear(int index) {
    if (!this->canEquipHeadgear()) {
        std::cout << "You don't have the ability to equip headgear.\n";
        return;
    }
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (!this->playerInventory.at(index).isHeadgear()) {
        std::cout << "ERROR: " << this->playerInventory.at(index).getName() << " is not headgear.\n";
        return;
    }
    std::cout << "Equipped " << this->playerInventory.at(index).getName() << " as your headgear.\n";
    if (this->headgear.getID() != -1) { // unequip first
        this->playerInventory.push_back(this->headgear);
    }
    this->headgear = this->playerInventory.at(index);
    this->playerInventory.erase(this->playerInventory.begin() + index);
}
void Player::equipChestgear(int index) {
    if (!this->canEquipChestgear()) {
        std::cout << "You don't have the ability to equip chestgear.\n";
        return;
    }
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (!this->playerInventory.at(index).isChestgear()) {
        std::cout << "ERROR: " << this->playerInventory.at(index).getName() << " is not chestgear.\n";
        return;
    }
    std::cout << "Equipped " << this->playerInventory.at(index).getName() << " as your chestgear.\n";
    if (this->chestgear.getID() != -1) { // unequip first
        this->playerInventory.push_back(this->chestgear);
    }
    this->chestgear = this->playerInventory.at(index);
    this->playerInventory.erase(this->playerInventory.begin() + index);
}
void Player::equipLeggear(int index) {
    if (!this->canEquipLeggear()) {
        std::cout << "You don't have the ability to equip leggear.\n";
        return;
    }
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (!this->playerInventory.at(index).isLeggear()) {
        std::cout << "ERROR: " << this->playerInventory.at(index).getName() << " is not leggear.\n";
        return;
    }
    std::cout << "Equipped " << this->playerInventory.at(index).getName() << " as your leggear.\n";
    if (this->leggear.getID() != -1) { // unequip first
        this->playerInventory.push_back(this->leggear);
    }
    this->leggear = this->playerInventory.at(index);
    this->playerInventory.erase(this->playerInventory.begin() + index);
}
void Player::equipFootgear(int index) {
    if (!this->canEquipLeggear()) {
        std::cout << "You don't have the ability to equip footgear.\n";
        return;
    }
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (!this->playerInventory.at(index).isFootgear()) {
        std::cout << "ERROR: " << this->playerInventory.at(index).getName() << " is not footgear.\n";
        return;
    }
    std::cout << "Equipped " << this->playerInventory.at(index).getName() << " as your footgear.\n";
    if (this->footgear.getID() != -1) { // unequip first
        this->playerInventory.push_back(this->footgear);
    }
    this->footgear = this->playerInventory.at(index);
    this->playerInventory.erase(this->playerInventory.begin() + index);
}
void Player::equipAccessory1(int index) {
    if (!this->canEquipAccessory1()) {
        std::cout << "You don't have the ability to use this accessory slot.\n";
        return;
    }
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (!this->playerInventory.at(index).isAccessory()) {
        std::cout << "ERROR: " << this->playerInventory.at(index).getName() << " is not an accessory.\n";
        return;
    }
    std::cout << "Equipped " << this->playerInventory.at(index).getName() << " in accessory slot 1.\n";
    if (this->accessory1.getID() != -1) { // unequip first
        this->playerInventory.push_back(this->accessory1);
    }
    this->accessory1 = this->playerInventory.at(index);
    this->playerInventory.erase(this->playerInventory.begin() + index);
}
void Player::equipAccessory2(int index) {
    if (!this->canEquipAccessory2()) {
        std::cout << "You don't have the ability to use this accessory slot.\n";
        return;
    }
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (!this->playerInventory.at(index).isAccessory()) {
        std::cout << "ERROR: " << this->playerInventory.at(index).getName() << " is not an accessory.\n";
        return;
    }
    std::cout << "Equipped " << this->playerInventory.at(index).getName() << " in accessory slot 2.\n";
    if (this->accessory2.getID() != -1) { // unequip first
        this->playerInventory.push_back(this->accessory2);
    }
    this->accessory2 = this->playerInventory.at(index);
    this->playerInventory.erase(this->playerInventory.begin() + index);
}
void Player::equipAccessory3(int index) {
    if (!this->canEquipAccessory3()) {
        std::cout << "You don't have the ability to use this accessory slot.\n";
        return;
    }
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (!this->playerInventory.at(index).isAccessory()) {
        std::cout << "ERROR: " << this->playerInventory.at(index).getName() << " is not an accessory.\n";
        return;
    }
    std::cout << "Equipped " << this->playerInventory.at(index).getName() << " in accessory slot 3.\n";
    if (this->accessory3.getID() != -1) { // unequip first
        this->playerInventory.push_back(this->accessory3);
    }
    this->accessory3 = this->playerInventory.at(index);
    this->playerInventory.erase(this->playerInventory.begin() + index);
}
void Player::equipAccessory4(int index) {
    if (!canEquipAccessory4()) {
        std::cout << "You don't have the ability to use this accessory slot.\n";
        return;
    }
    if ((index < 0) || (index >= this->playerInventory.size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (!this->playerInventory.at(index).isAccessory()) {
        std::cout << "ERROR: " << this->playerInventory.at(index).getName() << " is not an accessory.\n";
        return;
    }
    std::cout << "Equipped " << this->playerInventory.at(index).getName() << " in accessory slot 4.\n";
    if (this->accessory4.getID() != -1) { // unequip first
        this->playerInventory.push_back(this->accessory4);
    }
    this->accessory4 = this->playerInventory.at(index);
    this->playerInventory.erase(this->playerInventory.begin() + index);
}
// Unequip item from inventory
void Player::unequipItem(std::string slot) {
    if (slot.compare("weapon") == 0) {
        this->unequipWeapon();
    }
    else if (slot.compare("offhand") == 0) {
        this->unequipOffhand();
    }
    else if (slot.compare("twohand") == 0) {
        this->unequipTwohand();
    }
    else if (slot.compare("headgear") == 0) {
        this->unequipHeadgear();
    }
    else if (slot.compare("chestgear") == 0) {
        this->unequipChestgear();
    }
    else if (slot.compare("leggear") == 0) {
        this->unequipLeggear();
    }
    else if (slot.compare("footgear") == 0) {
        this->unequipFootgear();
    }
    else if (slot.compare("accessory1") == 0) {
        this->unequipAccessory1();
    }
    else if (slot.compare("accessory2") == 0) {
        this->unequipAccessory2();
    }
    else if (slot.compare("accessory3") == 0) {
        this->unequipAccessory3();
    }
    else if (slot.compare("accessory4") == 0) {
        this->unequipAccessory4();
    }
    else {
        std::cout << "No valid slot specified to unequip.\n";
    }
}
void Player::unequipWeapon() {
    if (this->weapon.getID() != -1) {
        std::cout << "Unequipped " << this->weapon.getName() << " as your weapon.\n";
        this->playerInventory.push_back(this->weapon);
        this->weapon = Item(-1);
    }
    else {
        std::cout << "No weapon to unequip.\n";
    }
}
void Player::unequipOffhand() {
    if (this->offhand.getID() != -1) {
        std::cout << "Unequipped " << this->offhand.getName() << " as your offhand.\n";
        this->playerInventory.push_back(this->offhand);
        this->offhand = Item(-1);
    }
    else {
        std::cout << "No offhand to unequip.\n";
    }
}
void Player::unequipTwohand() {
    if (this->twohand.getID() != -1) {
        std::cout << "Unequipped " << this->twohand.getName() << " as your twohand.\n";
        this->playerInventory.push_back(this->twohand);
        this->twohand = Item(-1);
    }
    else {
        std::cout << "No twohand to unequip.\n";
    }
}
void Player::unequipHeadgear() {
    if (this->headgear.getID() != -1) {
        std::cout << "Unequipped " << this->headgear.getName() << " as your headgear.\n";
        this->playerInventory.push_back(this->headgear);
        this->headgear = Item(-1);
    }
    else {
        std::cout << "No headgear to unequip.\n";
    }
}
void Player::unequipChestgear() {
    if (this->chestgear.getID() != -1) {
        std::cout << "Unequipped " << this->chestgear.getName() << " as your chestgear.\n";
        this->playerInventory.push_back(this->chestgear);
        this->chestgear = Item(-1);
    }
    else {
        std::cout << "No chestgear to unequip.\n";
    }
}
void Player::unequipLeggear() {
    if (this->leggear.getID() != -1) {
        std::cout << "Unequipped " << this->leggear.getName() << " as your leggear.\n";
        this->playerInventory.push_back(this->leggear);
        this->leggear = Item(-1);
    }
    else {
        std::cout << "No leggear to unequip.\n";
    }
}
void Player::unequipFootgear() {
    if (this->footgear.getID() != -1) {
        std::cout << "Unequipped " << this->footgear.getName() << " as your footgear.\n";
        this->playerInventory.push_back(this->footgear);
        this->footgear = Item(-1);
    }
    else {
        std::cout << "No footgear to unequip.\n";
    }
}
void Player::unequipAccessory1() {
    if (this->accessory1.getID() != -1) {
        std::cout << "Unequipped " << this->accessory1.getName() << " from accessory slot 1.\n";
        this->playerInventory.push_back(this->accessory1);
        this->accessory1 = Item(-1);
    }
    else {
        std::cout << "No accessory in slot 1 to unequip.\n";
    }
}
void Player::unequipAccessory2() {
    if (this->accessory2.getID() != -1) {
        std::cout << "Unequipped " << this->accessory2.getName() << " from accessory slot 2.\n";
        this->playerInventory.push_back(this->accessory2);
        this->accessory2 = Item(-1);
    }
    else {
        std::cout << "No accessory in slot 2 to unequip.\n";
    }
}
void Player::unequipAccessory3() {
    if (this->accessory3.getID() != -1) {
        std::cout << "Unequipped " << this->accessory3.getName() << " from accessory slot 3.\n";
        this->playerInventory.push_back(this->accessory3);
        this->accessory3 = Item(-1);
    }
    else {
        std::cout << "No accessory in slot 3 to unequip.\n";
    }
}
void Player::unequipAccessory4() {
    if (this->accessory4.getID() != -1) {
        std::cout << "Unequipped " << this->accessory4.getName() << " from accessory slot 4.\n";
        this->playerInventory.push_back(this->accessory4);
        this->accessory4 = Item(-1);
    }
    else {
        std::cout << "No accessory in slot 4 to unequip.\n";
    }
}

std::string Player::saveGame() {
    std::string fileString{};
    fileString += "*DEFINE=Player\n";
    fileString += Unit::saveGame();
    fileString += "monstersSlain=" + std::to_string(monstersSlain) + "\n";
    fileString += "distanceTraveled=" + std::to_string(distanceTraveled) + "\n";
    fileString += "itemsConsumed=" + std::to_string(itemsConsumed) + "\n";
    fileString += "level=" + std::to_string(level) + "\n";
    fileString += "experience=" + std::to_string(experience) + "\n";
    fileString += "credits=" + std::to_string(credits) + "\n";
    fileString += "fouls=" + std::to_string(fouls) + "\n";
    fileString += "baseEnergy=" + std::to_string(baseEnergy) + "\n";
    fileString += "missingEnergy=" + std::to_string(missingEnergy) + "\n";
    fileString += "baseMana=" + std::to_string(baseMana) + "\n";
    fileString += "missingMana=" + std::to_string(missingMana) + "\n";
    fileString += "maxInventorySlots=" + std::to_string(maxInventorySlots) + "\n";
    fileString += "*VECTOR=playerInventory\n";
    for (Item i : this->playerInventory) {
        fileString += "*ITEM\n" + i.saveGame() + "*END\n";
    }
    fileString += "*END\n";
    fileString += "*ITEM=weapon\n" + this->weapon.saveGame() + "*END\n";
    fileString += "*ITEM=offhand\n" + this->offhand.saveGame() + "*END\n";
    fileString += "*ITEM=twohand\n" + this->twohand.saveGame() + "*END\n";
    fileString += "*ITEM=headgear\n" + this->headgear.saveGame() + "*END\n";
    fileString += "*ITEM=chestgear\n" + this->chestgear.saveGame() + "*END\n";
    fileString += "*ITEM=leggear\n" + this->leggear.saveGame() + "*END\n";
    fileString += "*ITEM=footgear\n" + this->footgear.saveGame() + "*END\n";
    fileString += "*ITEM=accessory1\n" + this->accessory1.saveGame() + "*END\n";
    fileString += "*ITEM=accessory2\n" + this->accessory2.saveGame() + "*END\n";
    fileString += "*ITEM=accessory3\n" + this->accessory3.saveGame() + "*END\n";
    fileString += "*ITEM=accessory4\n" + this->accessory4.saveGame() + "*END\n";
    fileString += "healthRegenerationSpeed=" + std::to_string(healthRegenerationSpeed) + "\n";
    fileString += "energyRegenerationSpeed=" + std::to_string(energyRegenerationSpeed) + "\n";
    fileString += "manaRegenerationSpeed=" + std::to_string(manaRegenerationSpeed) + "\n";
    fileString += "xFacing=" + std::to_string(xFacing) + "\n";
    fileString += "yFacing=" + std::to_string(yFacing) + "\n";
    fileString += "zFacing=" + std::to_string(zFacing) + "\n";
    fileString += "theta=" + std::to_string(theta) + "\n";
    fileString += "phi=" + std::to_string(phi) + "\n";
    fileString += "maxMoveDistance=" + std::to_string(maxMoveDistance) + "\n";
    fileString += "maxTurnAngle=" + std::to_string(maxTurnAngle) + "\n";
    fileString += "viewDistance=" + std::to_string(viewDistance) + "\n";
    fileString += "viewAngle=" + std::to_string(viewAngle) + "\n";
    fileString += "xVelocity=" + std::to_string(velocity[0]) + "\n";
    fileString += "yVelocity=" + std::to_string(velocity[1]) + "\n";
    fileString += "zVelocity=" + std::to_string(velocity[2]) + "\n";
    fileString += "monsterSpawn=" + std::to_string(monsterSpawn) + "\n";
    fileString += "luckFactor=" + std::to_string(luckFactor) + "\n";
    fileString += "*VECTOR=upgradesActivated\n";
    for (int i : this->upgradesActivated) {
        fileString += std::to_string(i) + "\n";
    }
    fileString += "*END\n";
    fileString += "upgrade_forelegs=" + core_functions::boolToString(this->upgrade_forelegs) + "\n";
    fileString += "upgrade_hindlegs=" + core_functions::boolToString(this->upgrade_hindlegs) + "\n";
    fileString += "upgrade_attention1=" + core_functions::boolToString(this->upgrade_attention1) + "\n";
    fileString += "upgrade_quadrupedal1=" + core_functions::boolToString(this->upgrade_quadrupedal1) + "\n";
    fileString += "upgrade_coordination1=" + core_functions::boolToString(this->upgrade_coordination1) + "\n";
    fileString += "upgrade_memory1=" + core_functions::boolToString(this->upgrade_memory1) + "\n";
    fileString += "upgrade_quadrupedal2=" + core_functions::boolToString(this->upgrade_quadrupedal2) + "\n";
    fileString += "upgrade_coordination2=" + core_functions::boolToString(this->upgrade_coordination2) + "\n";
    fileString += "upgrade_learning1=" + core_functions::boolToString(this->upgrade_learning1) + "\n";
    fileString += "upgrade_attention2=" + core_functions::boolToString(this->upgrade_attention2) + "\n";
    fileString += "upgrade_aggression1=" + core_functions::boolToString(this->upgrade_aggression1) + "\n";
    fileString += "upgrade_protection1=" + core_functions::boolToString(this->upgrade_protection1) + "\n";
    fileString += "upgrade_magic1=" + core_functions::boolToString(this->upgrade_magic1) + "\n";
    fileString += "upgrade_ninja1=" + core_functions::boolToString(this->upgrade_ninja1) + "\n";
    fileString += "upgrade_aggression2=" + core_functions::boolToString(this->upgrade_aggression2) + "\n";
    fileString += "upgrade_protection2=" + core_functions::boolToString(this->upgrade_protection2) + "\n";
    fileString += "upgrade_magic2=" + core_functions::boolToString(this->upgrade_magic2) + "\n";
    fileString += "upgrade_ninja2=" + core_functions::boolToString(this->upgrade_ninja2) + "\n";
    fileString += "upgrade_learning2=" + core_functions::boolToString(this->upgrade_learning2) + "\n";
    fileString += "upgrade_memory2=" + core_functions::boolToString(this->upgrade_memory2) + "\n";
    fileString += "upgrade_aggression3=" + core_functions::boolToString(this->upgrade_aggression3) + "\n";
    fileString += "upgrade_protection3=" + core_functions::boolToString(this->upgrade_protection3) + "\n";
    fileString += "upgrade_magic3=" + core_functions::boolToString(this->upgrade_magic3) + "\n";
    fileString += "upgrade_ninja3=" + core_functions::boolToString(this->upgrade_ninja3) + "\n";
    fileString += "upgrade_equipWeapon=" + core_functions::boolToString(this->upgrade_equipWeapon) + "\n";
    fileString += "upgrade_equipOffhand=" + core_functions::boolToString(this->upgrade_equipOffhand) + "\n";
    fileString += "upgrade_equipTwohand=" + core_functions::boolToString(this->upgrade_equipTwohand) + "\n";
    fileString += "upgrade_equipHeadgear=" + core_functions::boolToString(this->upgrade_equipHeadgear) + "\n";
    fileString += "upgrade_equipChestgear=" + core_functions::boolToString(this->upgrade_equipChestgear) + "\n";
    fileString += "upgrade_equipLeggear=" + core_functions::boolToString(this->upgrade_equipLeggear) + "\n";
    fileString += "upgrade_equipFootgear=" + core_functions::boolToString(this->upgrade_equipFootgear) + "\n";
    fileString += "upgrade_equipAccessory1=" + core_functions::boolToString(this->upgrade_equipAccessory1) + "\n";
    fileString += "upgrade_equipAccessory2=" + core_functions::boolToString(this->upgrade_equipAccessory2) + "\n";
    fileString += "upgrade_equipAccessory3=" + core_functions::boolToString(this->upgrade_equipAccessory3) + "\n";
    fileString += "upgrade_equipAccessory4=" + core_functions::boolToString(this->upgrade_equipAccessory4) + "\n";
    fileString += "upgrade_itemsInBattle=" + core_functions::boolToString(this->upgrade_itemsInBattle) + "\n";
    fileString += "upgrade_dismantleItems=" + core_functions::boolToString(this->upgrade_dismantleItems) + "\n";
    fileString += "*END\n";
    return fileString;
}


// base constructor
aiUnit::aiUnit(std::string name, int baseHealth, int baseAttack, int baseMagic, int baseDefense,
    int baseResist, int basePiercing, int basePenetration, int baseDexterity, double xLocation,
    double yLocation, double zLocation, int unitID, int level, int energyValue, int maxHerd,
    int spaceTaken, int allyState, double attackProbability, double spawnProbability) :
    Unit({ name, baseHealth, baseAttack, baseMagic, baseDefense, baseResist, basePiercing,
        basePenetration, baseDexterity, xLocation, yLocation, zLocation }) {
    this->unitID = unitID;
    this->level = level;
    this->energyValue = energyValue;
    this->maxHerd = maxHerd;
    this->spaceTaken = spaceTaken;
    this->allyState = allyState;
    this->attackProbability = attackProbability;
    this->spawnProbability = spawnProbability;
}

// Unit ID constructor
aiUnit::aiUnit(int unitID, int specifiedLevel) : aiUnit(unitID, 0, 0, 0, specifiedLevel) { // if location not yet specified
}
aiUnit::aiUnit(int unitID, double xLocation, double yLocation, double zLocation, int specifiedLevel) {
    this->unitID = unitID;
    this->setLocation(xLocation, yLocation, zLocation);
    int minLevel{};
    int maxLevel{};
    double lM{ 1.0 }; // level multiplier for unit (and some ai) stats

    switch (unitID) {
        case 0: // empty unit
            break;
        // Tier 1 : Subtier 1 : Levels 0-4
        case 1:
            this->setName("Dead Aquatic Insect Larva");
            minLevel = 0;
            maxLevel = 2;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(5, 3, 1, 1, 0, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "selfrot", "nothing" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1} });
            break;
        case 2:
            this->setName("Drowning Bloodworm");
            minLevel = 1;
            maxLevel = 4;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 2, 1, 0, 0, 0, 0, 0, 10);
            this->setAIStats(10, 2, 1, 2, 0.1, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "attack", "drowning", "nothing" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1} });
            break;
        case 3:
            this->setName("Drowning Waxworm");
            minLevel = 0;
            maxLevel = 3;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 2, 0, 0, 1, 0, 0, 0, 5);
            this->setAIStats(10, 2, 2, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "drowning" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1} });
            break;
        case 4:
            this->setName("Drowning Grub");
            minLevel = 1;
            maxLevel = 4;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 3, 1, 0, 0, 0, 0, 0, 15);
            this->setAIStats(20, 1, 3, 2, 0.05, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "attack", "drowning", "bite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1} });
            break;
        case 5:
            this->setName("Baby Feeder Fish");
            minLevel = 0;
            maxLevel = 3;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 2, 1, 0, 0, 0, 0, 0, 40);
            this->setAIStats(20, 6, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "swimaway", "nibble", "grow" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1} });
            break;
        case 6:
            this->setName("Baby Feeder Fish");
            minLevel = 0;
            maxLevel = 3;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 2, 1, 0, 0, 0, 0, 0, 40);
            this->setAIStats(20, 6, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "swimaway", "nibble", "grow" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1} });
            break;
        case 7:
            this->setName("Baby Aquatic Snail");
            minLevel = 0;
            maxLevel = 4;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 2, 1, 0, 2, 0, 0, 0, 15);
            this->setAIStats(10, 3, 1, 1, 0, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "nibble", "excrete", "defend" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {4002, 1} });
            break;
        case 8:
            this->setName("Dead Floating Insect");
            minLevel = 0;
            maxLevel = 2;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 10);
            this->setAIStats(5, 2, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "selfrot", "rotting", "nothing" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1} });
            break;

        // Tier 1 : Subtier 2 : Levels 5-9
        case 11:
            this->setName("Drowning Earthworm");
            minLevel = 5;
            maxLevel = 9;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 3, 1, 0, 1, 0, 0, 0, 20);
            this->setAIStats(12, 1, 3, 2, 0.1, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "drowning", "floataway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1} });
            break;
        case 12:
            this->setName("Blackworm");
            minLevel = 5;
            maxLevel = 9;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 3, 2, 0, 1, 0, 0, 0, 35);
            this->setAIStats(12, 1, 3, 2, 0.2, 0);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "floataway", "flail" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1} });
            break;
        case 13:
            this->setName("Moving Food");
            minLevel = 5;
            maxLevel = 7;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 3, 1, 0, 0, 0, 0, 0, 25);
            this->setAIStats(20, 4, 1, 1, 0, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "attack", "nothing" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1} });
            break;
        case 14:
            this->setName("Baby Guppy");
            minLevel = 5;
            maxLevel = 9;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 3, 1, 0, 0, 0, 0, 0, 50);
            this->setAIStats(20, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "flail", "nibble", "grow", "swimaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1} });
            break;
        case 15:
            this->setName("Baby Guppy");
            minLevel = 5;
            maxLevel = 9;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 3, 1, 0, 0, 0, 0, 0, 50);
            this->setAIStats(20, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "flail", "nibble", "grow", "swimaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1} });
            break;
        case 16:
            this->setName("Rotting Insect");
            minLevel = 5;
            maxLevel = 9;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 15);
            this->setAIStats(5, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "selfrot", "rotting", "floataway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {7015, 1} });
            break;
        case 17:
            this->setName("Rotting Insect");
            minLevel = 5;
            maxLevel = 9;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 15);
            this->setAIStats(5, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "selfrot", "rotting", "floataway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {7015, 1} });
            break;
        case 18:
            this->setName("Baby Tadpole");
            minLevel = 5;
            maxLevel = 9;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 3, 1, 0, 0, 0, 0, 0, 45);
            this->setAIStats(12, 2, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "grow", "nibble" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 2}, {2, 1} });
            break;
        case 19:
            this->setName("Waxworm");
            minLevel = 7;
            maxLevel = 9;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 5, 2, 0, 1, 0, 0, 0, 35);
            this->setAIStats(12, 2, 2, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "swimaway", "recoil", "floataway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1} });
            break;
        case 20:
            this->setName("Aquatic Insect Larva");
            minLevel = 7;
            maxLevel = 9;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 2, 1, 0, 0, 0, 0, 0, 20);
            this->setAIStats(10, 2, 2, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "bite", "grow", "floataway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 2}, {2, 2}, {3, 1} });
            break;

        // Tier 1 : Subtier 3 : Levels 10-14
        case 21:
            this->setName("Aquatic Snail");
            minLevel = 10;
            maxLevel = 14;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 5, 1, 0, 3, 0, 0, 0, 20);
            this->setAIStats(20, 2, 1, 1, 0, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "excrete", "bite", "defend" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1}, {4003, 1} });
            break;
        case 22:
            this->setName("Bloodworm");
            minLevel = 10;
            maxLevel = 14;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 6, 2, 0, 0, 0, 0, 0, 35);
            this->setAIStats(15, 2, 1, 2, 0.3, 0);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "recoil", "bite", "flail" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1} });
            break;
        case 23:
            this->setName("Grub");
            minLevel = 10;
            maxLevel = 14;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 8, 1, 0, 0, 0, 0, 0, 35);
            this->setAIStats(40, 1, 3, 2, 0.1, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "nibble", "bite", "grow" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 2}, {2, 2}, {3, 2} });
            break;
        case 24:
            this->setName("Feeder Fish");
            minLevel = 10;
            maxLevel = 14;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 5, 1, 0, 0, 0, 0, 0, 70);
            this->setAIStats(40, 6, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "swimaway", "recoil", "nibble" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 2}, {2, 2}, {3, 2} });
            break;
        case 25:
            this->setName("Feeder Fish");
            minLevel = 10;
            maxLevel = 14;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 5, 1, 0, 0, 0, 0, 0, 70);
            this->setAIStats(40, 6, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "swimaway", "recoil", "nibble" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 2}, {2, 2}, {3, 2} });
            break;
        case 26:
            this->setName("Earthworm");
            minLevel = 12;
            maxLevel = 14;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 7, 2, 0, 1, 0, 0, 0, 40);
            this->setAIStats(20, 1, 3, 2, 0.2, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "flail", "nibble" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1} });
            break;
        case 27:
            this->setName("Guppy");
            minLevel = 10;
            maxLevel = 14;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 6, 2, 0, 1, 0, 0, 0, 80);
            this->setAIStats(25, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "swimaway", "recoil", "flail" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1}, {7001, 1} });
            break;
        case 28:
            this->setName("Guppy");
            minLevel = 11;
            maxLevel = 14;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 7, 2, 0, 1, 0, 0, 0, 80);
            this->setAIStats(25, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "swimaway", "recoil", "flail" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1}, {7001, 1} });
            break;

        // Tier 1 : Subtier 4 : Levels 15-19
        case 31:
            this->setName("Drowning Hermit Crab");
            minLevel = 16;
            maxLevel = 19;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 8, 2, 0, 2, 0, 0, 0, 45);
            this->setAIStats(20, 1, 3, 2, 0.1, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "defend", "drowning", "pinch" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1}, {1002, 1} });
            break;
        case 32:
            this->setName("Baby Goldfish");
            minLevel = 15;
            maxLevel = 19;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 6, 0, 0, 0, 0, 0, 0, 80);
            this->setAIStats(30, 2, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "swimaway", "grow" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1}, {7001, 1}, {7002, 1} });
            break;
        case 33:
            this->setName("Drowning Cricket");
            minLevel = 0;
            maxLevel = 2;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 4, 1, 0, 1, 0, 0, 0, 40);
            this->setAIStats(25, 2, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "nibble", "bite", "drowning", "floataway" });
            break;
        case 34:
            this->setName("Floating Cricket");
            minLevel = 0;
            maxLevel = 2;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 10, 2, 0, 1, 0, 5, 0, 60);
            this->setAIStats(25, 2, 1, 2, 0.05, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "recoil", "nibble", "bite" });
            break;
        case 35:
            this->setName("Angelfish");
            minLevel = 15;
            maxLevel = 19;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 14, 4, 0, 0, 0, 0, 0, 80);
            this->setAIStats(40, 1, 3, 2, 0.4, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "charge", "recoil", "flail" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1}, {7001, 1}, {7002, 1}, {7003, 1} });
            break;
        case 36:
            this->setName("Mollie");
            minLevel = 15;
            maxLevel = 19;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 10, 4, 0, 0, 0, 0, 0, 90);
            this->setAIStats(40, 4, 2, 2, 0.4, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "charge", "recoil", "flail" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1}, {7001, 1}, {7002, 1}, {7003, 1} });
            break;
        case 37:
            this->setName("Swordtail Fish");
            minLevel = 15;
            maxLevel = 19;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 10, 4, 0, 0, 0, 0, 0, 70);
            this->setAIStats(40, 2, 2, 2, 0.4, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "charge", "recoil", "flail" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1}, {1003, 1}, {7001, 1}, {7002, 1}, {7003, 1} });
            break;

        // Tier 1 : Subtier 5 : Levels 20-24
        case 41:
            this->setName("Hermit Crab");
            minLevel = 20;
            maxLevel = 24;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 10, 4, 0, 2, 0, 15, 0, 55);
            this->setAIStats(40, 1, 3, 2, 0.2, 0.03);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "pinch", "defend" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1}, {1002, 1}, {7004, 1} });
            break;
        case 42:
            this->setName("Goldfish");
            minLevel = 20;
            maxLevel = 24;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 10, 4, 0, 0, 0, 0, 0, 90);
            this->setAIStats(50, 2, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "swimaway", "recoil" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {3, 1}, {7001, 1}, {7002, 1}, {7003, 1} });
            break;
        case 43:
            this->setName("Feeder Cricket");
            minLevel = 20;
            maxLevel = 24;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 12, 3, 0, 1, 0, 10, 0, 70);
            this->setAIStats(50, 2, 1, 2, 0.1, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "bite", "flee" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 2}, {2, 2}, {3, 2} });
            break;
        case 44:
            this->setName("Baby Housefly");
            minLevel = 22;
            maxLevel = 24;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 3, 2, 0, 1, 0, 5, 0, 110);
            this->setAIStats(30, 2, 1, 2, 0.1, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "dive", "flee", "flyaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {35, 2}, {4001, -4}, {7005, -4}, {7015, -4} });
            break;
        case 45:
            this->setName("Housefly");
            minLevel = 22;
            maxLevel = 24;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 5, 3, 0, 1, 0, 10, 0, 130);
            this->setAIStats(50, 2, 1, 2, 0.2, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "dive", "flee", "flyaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {35, 3}, {4001, 1}, {7005, 1}, {7015, 1} });
            break;
        case 46:
            this->setName("Betta Fish");
            minLevel = 20;
            maxLevel = 24;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 10, 5, 0, 1, 0, 10, 0, 90);
            this->setAIStats(50, 2, 3, 2, 0.9, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "charge", "flail", "recoil" });
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 1}, {2, 1}, {7006, 1}, {7007, 1} });
            break;
        case 47:
            this->setName("African Dwarf Frog (boss)");
            minLevel = 22;
            maxLevel = 22;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 24, 6, 0, 2, 0, 10, 0, 60);
            this->setAIStats(80, 1, 3, 1, 0.0, 0.04);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "nibble", "lunge", "flee" });
            this->setDrops(std::vector<std::pair<int, int>>{ {3, 3}, {4, 2}, {9, 3}, {10, 1}, {19, 1}, {24, 1}, {26, 1}, {1016, -1}, {7008, -1}, {7009, -1}, {7010, -1} });
            break;
        case 48:
            this->setName("Rainbow Shark (boss)");
            minLevel = 24;
            maxLevel = 24;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 28, 7, 0, 2, 0, 10, 0, 90);
            this->setAIStats(80, 1, 3, 2, 0.5, 0.01);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "charge", "flail", "dive" });
            this->setDrops(std::vector<std::pair<int, int>>{ {3, 3}, {4, 3}, {5, 1}, {9, 3}, {10, 1}, {19, 1}, {24, 1}, {26, 1}, {7011, -1}, {7012, -1}, {1004, -1} });
            break;
        case 49:
            this->setName("Worm Chief (boss)");
            minLevel = 20;
            maxLevel = 20;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 18, 7, 5, 1, 0, 10, 0, 50);
            this->setAIStats(80, 1, 3, 2, 0.5, 0.01);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "nibble", "bite", "splash", "drown" });
            this->setDrops(std::vector<std::pair<int, int>>{ {3, 3}, {4, 2}, {9, 3}, {10, 1}, {19, 1}, {7022, -1}, {1015, -1} });
            break;
            
        // Tier 2 : Subtier 1 : Levels 25-29
        case 51:
            this->setName("Mayfly Larva");
            minLevel = 25;
            maxLevel = 29;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 12, 4, 0, 0, 0, 5, 0, 50);
            this->setAIStats(80, 5, 1, 1, 0, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "nibble", "bite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 3} });
            break;
        case 52:
            this->setName("Slug");
            minLevel = 25;
            maxLevel = 39;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 25, 6, 0, 1, 0, 0, 0, 40);
            this->setAIStats(40, 5, 1, 1, 0, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "ooze", "excrete", "infect" });
            this->setDrops(std::vector<std::pair<int, int>>{ {3001, 1}, {4004, 1}, {5001, 1}, {6001, 1} });
            break;
        case 53:
            this->setName("Water Strider");
            minLevel = 25;
            maxLevel = 32;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 10, 4, 0, 1, 0, 0, 0, 75);
            this->setAIStats(40, 12, 0, 1, 0, 0.6);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "jump", "jumpaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {7015, 1} });
            break;
        case 54:
            this->setName("Flea");
            minLevel = 25;
            maxLevel = 29;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 10, 4, 0, 0, 0, 0, 0, 85);
            this->setAIStats(20, 20, 0, 2, 0.2, 0.8);
            this->addBattleAbilities(std::vector<std::string>{ "bite", "jumpaway", "infect", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {35, 2}, {36, 1}, {4005, 1}, {7015, 1} });
            break;
        case 55:
            this->setName("Toxic Minnow");
            minLevel = 25;
            maxLevel = 34;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 10, 5, 0, 0, 0, 0, 0, 80);
            this->setAIStats(20, 10, 0, 2, 0.2, 0.5);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "nibble", "toxicbite", "recoil", "swimaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {7013, 1}, {7014, 1} });
            break;
        case 56:
            this->setName("Stonefly Larva");
            minLevel = 25;
            maxLevel = 29;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 10, 4, 0, 0, 0, 0, 0, 50);
            this->setAIStats(20, 4, 0, 2, 0.2, 0.5);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "nibble", "bite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 3} });
            break;

        // Tier 2 : Subtier 2 : Levels 30-34
        case 61:
            this->setName("Dragonfly Larva");
            minLevel = 30;
            maxLevel = 34;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 16, 5, 0, 0, 0, 5, 0, 50);
            this->setAIStats(90, 5, 1, 1, 0, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "nibble", "bite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 3} });
            break;
        case 62:
            this->setName("Backswimmer");
            minLevel = 28;
            maxLevel = 34;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 14, 5, 0, 1, 0, 5, 0, 65);
            this->setAIStats(40, 8, 0, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "swimaway", "defend", "recoil" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {7015, -1}, {7016, 1} });
            break;
        case 63:
            this->setName("Gnat");
            minLevel = 27;
            maxLevel = 34;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 12, 6, 0, 1, 0, 5, 0, 100);
            this->setAIStats(30, 12, 0, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "airstrike", "bite", "flyaway", "disease" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {35, 3}, {36, 1}, {4006, 1}, {7015, -1}, {7016, 1} });
            break;
        case 64:
            this->setName("Toxic Glob");
            minLevel = 30;
            maxLevel = 34;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 12, 10, 0, 1, 0, 5, 0, 45);
            this->setAIStats(30, 4, 1, 2, 0.3, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "ooze", "excrete", "infect", "disease", "rot", "decay", "wilt" });
            this->setDrops(std::vector<std::pair<int, int>>{ {3001, 1}, {4004, 1}, {5001, 1}, {6001, 1}, {9, 1}, {10, 1}, {19, 1}, {20, 1}, {4, 1}, {5, 1} });
            break;

        // Tier 2 : Subtier 3 : Levels 35-39
        case 71:
            this->setName("Waterbug");
            minLevel = 35;
            maxLevel = 44;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 25, 7, 0, 3, 0, 10, 0, 65);
            this->setAIStats(60, 5, 1, 2, 0.4, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "waterstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {7015, 1}, {7016, 1} });
            break;
        case 72:
            this->setName("Fishing Spider");
            minLevel = 35;
            maxLevel = 44;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 25, 7, 0, 3, 0, 10, 0, 70);
            this->setAIStats(30, 5, 1, 2, 0.4, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "waterstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {61, -4}, {7015, 1}, {7016, 1}, {1005, 1} });
            break;
        case 73:
            this->setName("Sewer Fly");
            minLevel = 32;
            maxLevel = 44;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 15, 7, 0, 1, 0, 5, 0, 120);
            this->setAIStats(30, 8, 1, 2, 0.4, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "flyaway", "airstrike", "disease" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {35, 3}, {36, 1}, {4007, 1}, {7015, 1}, {7016, 1} });
            break;
        case 74:
            this->setName("Toxic Blob");
            minLevel = 35;
            maxLevel = 39;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 14, 14, 0, 1, 0, 5, 0, 60);
            this->setAIStats(30, 3, 1, 2, 0.3, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "ooze", "excrete", "disease", "decay", "wilt" });
            this->setDrops(std::vector<std::pair<int, int>>{ {3001, 1}, {4004, 1}, {5001, 1}, {6001, 1}, {9, -1}, {10, 1}, {19, -1}, {20, 1}, {4, -1}, {5, 1} });
            break;
        case 75:
            this->setName("Toxic Goop");
            minLevel = 35;
            maxLevel = 39;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 20, 10, 0, 3, 0, 5, 0, 60);
            this->setAIStats(30, 3, 1, 2, 0.3, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "ooze", "disease", "wilt", "defend" });
            this->setDrops(std::vector<std::pair<int, int>>{ {3001, 1}, {4004, 1}, {5001, 1}, {6001, 1}, {9, -1}, {10, 1}, {19, -1}, {20, 1}, {4, -1}, {5, 1} });
            break;
        case 76:
            this->setName("Toxic Bass");
            minLevel = 35;
            maxLevel = 42;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 35, 12, 0, 3, 0, 5, 0, 90);
            this->setAIStats(60, 3, 2, 2, 0.5, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "disease", "recoil", "toxicbite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7013, 1}, {7014, 1}, {1006, -1} });
            break;
        case 77:
            this->setName("Toxic Carp");
            minLevel = 35;
            maxLevel = 43;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 45, 9, 0, 4, 0, 5, 0, 90);
            this->setAIStats(60, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "disease", "recoil", "toxicbite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7013, 1}, {7014, 1}, {1007, -1} });
            break;

        // Tier 2 : Subtier 4 : Levels 40-44
        case 81:
            this->setName("Baby Lost Turtle");
            minLevel = 40;
            maxLevel = 44;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 50, 10, 0, 8, 0, 5, 0, 75);
            this->setAIStats(70, 2, 2, 1, 0, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "bite", "waterstrike", "swimaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {29, 2}, {1008, 1}, {2002, 1}, {3002, 1}, {4008, -1}, {5002, 1}, {6002, 1} });
            break;
        case 82:
            this->setName("Toxic Eel");
            minLevel = 40;
            maxLevel = 44;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 35, 15, 0, 3, 0, 0, 0, 80);
            this->setAIStats(70, 2, 2, 2, 0.8, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "disease", "bite", "toxicbite", "flail", "recoil" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {56, 1}, {1009, 1} });
            break;
        case 83:
            this->setName("Floating Algae");
            minLevel = 40;
            maxLevel = 49;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 60, 13, 0, 0, 0, 0, 0, 55);
            this->setAIStats(20, 6, 1, 2, 0.3, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "disease", "infect", "rot", "decay", "floataway", "ooze", "excrete" });
            this->setDrops(std::vector<std::pair<int, int>>{ {4, 2}, {5, 2}, {7021, 1} });
            break;
        case 84:
            this->setName("Algae");
            minLevel = 40;
            maxLevel = 49;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 60, 13, 0, 0, 0, 0, 0, 55);
            this->setAIStats(20, 6, 1, 2, 0.3, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "disease", "infect", "rot", "decay", "floataway", "ooze", "excrete" });
            this->setDrops(std::vector<std::pair<int, int>>{ {4, 2}, {5, 2}, {7021, 1} });
            break;
        case 85:
            this->setName("Water Snake");
            minLevel = 40;
            maxLevel = 49;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 15, 0, 8, 0, 15, 0, 70);
            this->setAIStats(20, 1, 3, 2, 0.3, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "earthstrike", "bite", "recoil" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1014, 1}, {7018, 1}, {7019, 1} });
            break;
        case 86:
            this->setName("Toxic Catfish");
            minLevel = 40;
            maxLevel = 44;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 50, 14, 0, 5, 0, 5, 0, 100);
            this->setAIStats(70, 3, 2, 2, 0.2, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "disease", "recoil", "toxicbite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7013, 1}, {7014, 1}, {7017, 1}, {1010, -1} });
            break;
        case 87:
            this->setName("Baby Crocodile (boss)");
            minLevel = 45;
            maxLevel = 45;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 16, 0, 7, 0, 15, 0, 75);
            this->setAIStats(200, 1, 20, 2, 1.0, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "hammer", "waterstrike", "bite", "flail", "chomp", "slash" });
            this->setDrops(std::vector<std::pair<int, int>>{ {10, 2}, {15, 2}, {20, 2}, {28, -1}, {28, 5}, {1012, -1},
                {2004, -1}, {3004, 1}, {4012, 1}, {5004, 1}, {6004, 1}, {7018, 1}, {7019, 1} });
            break;
        case 88:
            this->setName("Baby Alligator (boss)");
            minLevel = 45;
            maxLevel = 45;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 16, 0, 7, 0, 15, 0, 75);
            this->setAIStats(200, 1, 20, 2, 1.0, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "hammer", "waterstrike", "bite", "flail", "chomp", "slash" });
            this->setDrops(std::vector<std::pair<int, int>>{ {10, 2}, {15, 2}, {20, 2}, {28, -1}, {28, 5}, {1013, -1},
                {2005, -1}, {3004, 1}, {4013, 1}, {5005, 1}, {6005, 1}, {7018, 1}, {7019, 1} });
            break;

        // Tier 2 : Subtier 5 : Levels 45-49
        case 91:
            this->setName("Lost Turtle");
            minLevel = 45;
            maxLevel = 49;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 15, 0, 12, 0, 10, 0, 75);
            this->setAIStats(80, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "bite", "waterstrike", "swimaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {29, 3}, {1008, 1}, {2002, 1}, {3002, 1}, {4009, -1}, {5002, 1}, {6002, 1} });
            break;
        case 92:
            this->setName("Swimming Rat");
            minLevel = 45;
            maxLevel = 49;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 20, 0, 10, 0, 10, 0, 80);
            this->setAIStats(80, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "earthstrike", "attack", "bite", "disease" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, -1}, {28, 2}, {1011, 1}, {1022, -5}, {2003, 1}, {3003, 1}, {4010, 1}, {4011, 1}, {5003, 1}, {6003, 1} });
            break;
        case 93:
            this->setName("Toxic Algae");
            minLevel = 45;
            maxLevel = 49;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 16, 0, 0, 0, 0, 0, 75);
            this->setAIStats(20, 3, 1, 2, 0.3, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "disease", "decay", "floataway", "ooze" });
            this->setDrops(std::vector<std::pair<int, int>>{ {4, 2}, {5, 2}, {7021, 1} });
            break;
        case 94:
            this->setName("Leonardo (boss)");
            minLevel = 49;
            maxLevel = 49;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 160, 25, 25, 8, 8, 5, 5, 90);
            this->setAIStats(200, 1, 2, 2, 0.3, 0);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "attack", "hammer", "dunk", "drown", "splash", "stream", "magicattack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {24, 1}, {25, 1}, {26, 1}, {40, 3}, {2502, -1}, {3006, -1}, {4014, 1}, {5006, 1}, {6006, 1}, {7020, 1} });
            break;
        case 95:
            this->setName("Raphael (boss)");
            minLevel = 49;
            maxLevel = 49;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 160, 35, 20, 8, 6, 10, 3, 90);
            this->setAIStats(200, 1, 2, 2, 0.8, 0);
            this->addBattleAbilities(std::vector<std::string>{ "firestrike", "attack", "hammer", "burn", "char", "flame", "fire", "magicattack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {24, 1}, {25, 1}, {26, 1}, {40, 3}, {2503, -1}, {3007, -1}, {4015, 1}, {5007, 1}, {6007, 1}, {7020, 1} });
            break;
        case 96:
            this->setName("Donatello (boss)");
            minLevel = 49;
            maxLevel = 49;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 160, 20, 20, 12, 12, 3, 3, 90);
            this->setAIStats(200, 1, 2, 2, 0.1, 0);
            this->addBattleAbilities(std::vector<std::string>{ "gravitystrike", "attack", "hammer", "shake", "fell", "pull", "orbit", "magicattack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {24, 1}, {25, 1}, {26, 1}, {40, 3}, {2504, -1}, {3008, -1}, {4016, 1}, {5008, 1}, {6008, 1}, {7020, 1} });
            break;
        case 97:
            this->setName("Michaelangelo (boss)");
            minLevel = 49;
            maxLevel = 49;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 160, 25, 25, 8, 8, 5, 5, 110);
            this->setAIStats(200, 1, 2, 2, 0.3, 0);
            this->addBattleAbilities(std::vector<std::string>{ "airstrike", "attack", "hammer", "infect", "disease", "breeze", "wind", "magicattack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {40, 6}, {2505, -1}, {3009, -1}, {4017, 1}, {5009, 1}, {6009, 1}, {7020, 1} });
            break;
            
        // Tier 3 : Subtier 1 : Levels 50-54
        case 101:
            this->setName("Dragonfly");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 40, 15, 0, 6, 3, 5, 0, 140);
            this->setAIStats(150, 8, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "airstrike", "attack", "dive" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {4020, 1}, {7016, 1}, {7028, 1} });
            break;
        case 102:
            this->setName("Midges");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 40, 0, 15, 3, 6, 5, 0, 140);
            this->setAIStats(100, 8, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "infect", "breeze", "magicstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {4021, 1}, {7016, 1}, {7028, 1} });
            break;
        case 103:
            this->setName("Damselfly");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 35, 10, 0, 5, 3, 5, 0, 140);
            this->setAIStats(100, 8, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "airstrike", "attack", "dive" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {3013, 1}, {6012, 1}, {7028, 1} });
            break;
        case 104:
            this->setName("Stonefly");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 40, 12, 0, 8, 8, 5, 0, 140);
            this->setAIStats(100, 8, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "airstrike", "attack", "dive" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {3012, 1}, {4022, 1}, {5012, 1} });
            break;
        case 105:
            this->setName("Butterfly");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 25, 8, 12, 3, 5, 0, 0, 130);
            this->setAIStats(90, 2, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "wisp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {4023, 1}, {7016, 1} });
            break;
        case 106:
            this->setName("Moth");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 25, 12, 8, 5, 3, 0, 0, 130);
            this->setAIStats(90, 2, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "wisp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {41, 2}, {7016, 1} });
            break;
        case 107:
            this->setName("Bluegill");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 30, 12, 0, 4, 2, 0, 0, 130);
            this->setAIStats(90, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "flail", "swimaway", "grow" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {7023, 1}, {7034, 1} });
            break;
        case 108:
            this->setName("Perch");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 25, 12, 0, 5, 3, 0, 0, 130);
            this->setAIStats(90, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "flail", "swimaway", "defend" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {7026, 1}, {1020, 1} });
            break;
        case 109:
            this->setName("Flatworm");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 25, 12, 0, 4, 2, 0, 0, 100);
            this->setAIStats(90, 6, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "flail", "nibble", "excrete" });
            this->setDrops(std::vector<std::pair<int, int>>{ {26, 1}, {28, 1} });
            break;
        case 110:
            this->setName("Leech");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 15, 16, 0, 4, 2, 0, 0, 80);
            this->setAIStats(90, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "bite", "suck" });
            this->setDrops(std::vector<std::pair<int, int>>{ {24, 1}, {28, 1} });
            break;
        case 111:
            this->setName("Pond Snail");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 15, 12, 0, 20, 10, 0, 0, 80);
            this->setAIStats(90, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "nibble", "attack", "defend", "resolve" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {1008, 1}, {4024, 1} });
            break;
        case 112:
            this->setName("Pond Slug");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 15, 15, 15, 4, 2, 0, 0, 80);
            this->setAIStats(90, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "nibble", "excrete", "ooze", "wisp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {10, 1}, {27, 1}, {1021, 1} });
            break;
        case 113:
            this->setName("Living Detritus");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 15, 10, 0, 4, 2, 0, 0, 80);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "attack", "excrete" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 6} });
            break;
        case 114:
            this->setName("Macroscopic Diatom");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 15, 0, 10, 4, 2, 0, 0, 80);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "wisp", "wilt" });
            this->setDrops(std::vector<std::pair<int, int>>{ {3015, 1}, {4026, 1}, {5014, 1}, {6014, 1} });
            break;
        case 115:
            this->setName("Aufwuchs");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 25, 0, 0, 6, 3, 0, 0, 80);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "wilt", "infect", "wither", "disease", "rot", "decay" });
            this->setDrops(std::vector<std::pair<int, int>>{ {3014, 1}, {4025, 1}, {5013, 1}, {6013, 1} });
            break;
        case 116:
            this->setName("Cladophora Ball");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 0, 20, 0, 0, 0, 0, 100);
            this->setAIStats(120, 4, 1, 2, 0.3, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "weak", "feeble", "inept", "impotent", "slow", "lethargy", "wisp", "bolt" });
            this->setDrops(std::vector<std::pair<int, int>>{ {7029, 1}, {7030, 1}, {7031, 1}, {7032, 1}, {7033, 1} });
            break;
        case 117:
            this->setName("Pond Algae");
            minLevel = 50;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 20, 0, 0, 0, 0, 0, 100);
            this->setAIStats(120, 4, 1, 2, 0.3, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "disease", "infect", "rot", "decay", "floataway", "ooze", "excrete" });
            this->setDrops(std::vector<std::pair<int, int>>{ {7021, 1}, {7035, 1} });
            break;
        case 118:
            this->setName("Rat");
            minLevel = 52;
            maxLevel = 57;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 20, 0, 10, 5, 10, 0, 110);
            this->setAIStats(120, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "earthstrike", "attack", "bite", "disease" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 3}, {1011, -4}, {1022, -5}, {2003, -4}, {3003, -4}, {3016, -4}, {4010, -4}, {4011, -4}, {4027, -4}, {5003, -4}, {5015, -4}, {6003, -4}, {6015, -4} });
            break;
        case 119:
            this->setName("Gopher");
            minLevel = 52;
            maxLevel = 57;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 20, 0, 10, 5, 10, 0, 110);
            this->setAIStats(120, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "earthstrike", "attack", "hammer", "magicattack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 3}, {1022, -4}, {2009, 1} });
            break;
        case 120:
            this->setName("Jackalope");
            minLevel = 52;
            maxLevel = 57;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 0, 20, 5, 12, 10, 0, 110);
            this->setAIStats(120, 2, 2, 2, 0.4, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "dust", "dirt", "magicstrike", "decay", "swiftness" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 3}, {1025, 1}, {3017, 1}, {6016, 1} });
            break;
        case 121:
            this->setName("Water Mite");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 20, 9, 0, 6, 4, 5, 0, 100);
            this->setAIStats(60, 8, 0, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "nibble" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {7023, -4} });
            break;
        case 122:
            this->setName("Dace");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 25, 10, 10, 4, 2, 0, 0, 130);
            this->setAIStats(120, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "splash", "swimaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 3}, {1023, 1}, {7052, 1}, {7053, 1} });
            break;
        case 123:
            this->setName("Chubs");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 25, 0, 12, 4, 2, 0, 0, 130);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dunk", "splash", "swimaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 3}, {1023, -2}, {7052, 1}, {7053, 1} });
            break;
        case 124:
            this->setName("Pigeon");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 30, 12, 0, 4, 2, 0, 0, 160);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7036, 1}, {7038, 1} });
            break;
        case 125:
            this->setName("Guinea");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 30, 12, 0, 4, 2, 0, 0, 140);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "flail", "peck", "attack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7038, 2} });
            break;
        case 126:
            this->setName("Robin");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 30, 12, 0, 4, 2, 0, 0, 160);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7037, 1}, {7040, 1} });
            break;
        case 127:
            this->setName("Sparrow");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 30, 12, 0, 4, 2, 0, 0, 160);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7039, 1}, {7045, 1} });
            break;
        case 128:
            this->setName("Finch");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 30, 12, 0, 4, 2, 0, 0, 160);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7042, 1}, {7044, 1} });
            break;
        case 129:
            this->setName("Chickadee");
            minLevel = 50;
            maxLevel = 54;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 30, 12, 0, 4, 2, 0, 0, 160);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7044, 1}, {7045, 1} });
            break;
        case 130:
            this->setName("Chipmunk");
            minLevel = 52;
            maxLevel = 57;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 60, 15, 0, 10, 5, 10, 0, 110);
            this->setAIStats(120, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "nibble", "bite", "claw" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {42, 2}, {1022, -4} });
            break;
            
        // Tier 3 : Subtier 2 : Levels 55-59
        case 131:
            this->setName("Mosquito");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 50, 18, 0, 6, 4, 5, 0, 160);
            this->setAIStats(80, 8, 1, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "infect", "disease", "airstrike", "attack", "bite", "suck" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {1028, 1}, {7029, 1} });
            break;
        case 132:
            this->setName("Cranefly");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 50, 15, 15, 7, 7, 5, 5, 160);
            this->setAIStats(120, 8, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "airstrike", "attack", "dive", "breeze", "magicattack", "magicstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {1027, 1} });
            break;
        case 133:
            this->setName("Water Strider");
            minLevel = 50;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 30, 8, 0, 2, 0, 5, 0, 120);
            this->setAIStats(100, 8, 0, 1, 0, 0.6);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "jump", "jumpaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {7016, 1}, {7033, 1} });
            break;
        case 134:
            this->setName("Toxic Bullfrog");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 45, 10, 0, 3, 0, 10, 0, 120);
            this->setAIStats(100, 5, 1, 2, 0.2, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "hammer", "excrete" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7047, 1}, {7048, 1}, {7049, 1} });
            break;
        case 135:
            this->setName("Whirligig Beetle");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 50, 10, 0, 6, 6, 5, 0, 120);
            this->setAIStats(100, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "bite", "defend", "break" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {7026, 1}, {7031, 1} });
            break;
        case 136:
            this->setName("Scout Ant");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 30, 8, 0, 6, 4, 5, 0, 120);
            this->setAIStats(100, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "bite", "charge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {3018, -4}, {4028, -4}, {5016, -4}, {6017, -4}, {7050, -4} });
            break;
        case 137:
            this->setName("Monarch Butterfly");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 35, 4, 16, 5, 9, 0, 0, 140);
            this->setAIStats(100, 2, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "breeze", "wisp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {4029, 1}, {7016, 1} });
            break;
        case 138:
            this->setName("Eel");
            minLevel = 55;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 45, 15, 0, 7, 5, 5, 0, 120);
            this->setAIStats(120, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "flail", "lunge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {56, 2}, {1029, 1} });
            break;
        case 139:
            this->setName("Mite");
            minLevel = 55;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 40, 14, 0, 7, 0, 5, 0, 120);
            this->setAIStats(100, 4, 1, 2, 0.05, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "bite", "chomp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {1030, 1} });
            break;
        case 140:
            this->setName("Bullfrog");
            minLevel = 55;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 20, 0, 8, 5, 5, 0, 120);
            this->setAIStats(100, 4, 1, 2, 0.05, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "earthstrike", "jump" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7047, 1}, {7048, 1}, {7049, 1} });
            break;
        case 141:
            this->setName("Mink");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 25, 0, 12, 7, 10, 0, 120);
            this->setAIStats(150, 2, 2, 1, 0, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "attack", "slash", "claw" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {43, 2} });
            break;
        case 142:
            this->setName("Beaver");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 25, 0, 12, 7, 10, 0, 120);
            this->setAIStats(150, 2, 2, 1, 0, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "bite", "attack", "claw" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1022, -4}, {1031, 1}, {2506, 1} });
            break;
        case 143:
            this->setName("Muskrat");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 25, 0, 12, 7, 10, 0, 120);
            this->setAIStats(150, 2, 2, 1, 0, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "attack", "hammer", "claw" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1022, -4}, {1032, 1}, {2507, 1} });
            break;
        case 144:
            this->setName("Bass");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 22, 0, 6, 0, 5, 0, 140);
            this->setAIStats(120, 3, 2, 2, 0.5, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "attack", "recoil", "flail" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1033, 1}, {7052, 1}, {7053, 1} });
            break;
        case 145:
            this->setName("Carp");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 110, 18, 0, 8, 0, 5, 0, 140);
            this->setAIStats(120, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "attack", "recoil", "flail" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1034, 1}, {7052, 1}, {7053, 1} });
            break;
        case 146:
            this->setName("Catfish");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 110, 22, 0, 8, 0, 5, 0, 140);
            this->setAIStats(120, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "attack", "recoil", "flail" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1035, 1}, {7052, 1}, {7053, 1}, {7051, 1} });
            break;
        case 147:
            this->setName("Pike");
            minLevel = 56;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 110, 20, 20, 8, 0, 5, 0, 140);
            this->setAIStats(120, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "splash", "flail", "frost", "bite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1026, 1}, {7052, 1}, {7053, 1} });
            break;
        case 148:
            this->setName("Trout");
            minLevel = 57;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 110, 0, 25, 8, 0, 5, 0, 140);
            this->setAIStats(120, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "splash", "dunk", "wisp", "stream" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1023, 1}, {7052, 1}, {7053, 1} });
            break;
        case 149:
            this->setName("Duck");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 110, 15, 0, 7, 7, 40, 0, 120);
            this->setAIStats(120, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dunk", "attack", "waterstrike", "peck" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1036, 1}, {7036, -4}, {7037, -4}, {7038, -4}, {7039, -4}, {7040, -4} });
            break;
        case 150:
            this->setName("Goose");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 110, 0, 15, 7, 12, 0, 50, 120);
            this->setAIStats(120, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "splash", "dunk", "swimaway", "wisp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1037, 1}, {7036, -4}, {7037, -4}, {7038, -4}, {7039, -4}, {7040, -4} });
            break;
        case 151:
            this->setName("Swan");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 110, 0, 25, 7, 7, 0, 50, 120);
            this->setAIStats(120, 2, 3, 2, 0.2, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "splash", "stream", "drown", "wisp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {44, -1}, {44, 1}, {7036, -4}, {7037, -4}, {7038, -4}, {7039, -4}, {7040, -4}, {7041, -4}, {7042, -4}, {7043, -4}, {7044, -4}, {7045, -4} });
            break;
        case 152:
            this->setName("Crayfish");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 20, 0, 12, 12, 10, 0, 120);
            this->setAIStats(100, 5, 1, 2, 0.2, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "pinch", "charge", "attack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1038, 1}, {2010, 1}, {3019, 1}, {4030, 1} });
            break;
        case 153:
            this->setName("Paddlefish");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 20, 20, 8, 0, 5, 0, 140);
            this->setAIStats(100, 5, 1, 1, 0, 0.5);
            this->addBattleAbilities(std::vector<std::string>{ "waterstrike", "attack", "wisp", "stream" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1039, 1}, {7054, 1}, {7055, 1} });
            break;
        case 154:
            this->setName("Salamander");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 15, 18, 7, 7, 0, 10, 120);
            this->setAIStats(120, 2, 3, 2, 0.2, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "wisp", "drain", "attack", "bite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {45, 2}, {6018, 1} });
            break;
        case 155:
            this->setName("Crow");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 50, 14, 14, 5, 5, 5, 5, 170);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike", "breeze", "wind", "infect" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7044, -1}, {7038, 1}, {7044, 1} });
            break;
        case 156:
            this->setName("Bluebird");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 50, 16, 0, 5, 5, 15, 0, 170);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7036, -1}, {7040, 1}, {7042, 1} });
            break;
        case 157:
            this->setName("Bluejay");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 50, 16, 0, 5, 5, 15, 0, 170);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7036, -1}, {7036, 1}, {7045, 1} });
            break;
        case 158:
            this->setName("Warbler");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 50, 0, 16, 5, 5, 0, 5, 170);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "breeze", "wind", "wilt", "wisp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7039, -1}, {7040, 1}, {7041, 1} });
            break;
        case 159:
            this->setName("Quail");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 60, 16, 0, 5, 5, 5, 0, 150);
            this->setAIStats(170, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "flail", "peck", "attack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7038, -1}, {7039, 1}, {7043, 1} });
            break;
        case 160:
            this->setName("Squirrel");
            minLevel = 58;
            maxLevel = 62;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 18, 0, 12, 12, 10, 0, 130);
            this->setAIStats(120, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "nibble", "bite", "claw" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {42, 3}, {1022, -4} });
            break;
            
        // Tier 3 : Subtier 3 : Levels 60-64
        case 161:
            this->setName("Caddisfly");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 60, 18, 18, 8, 8, 5, 5, 160);
            this->setAIStats(140, 8, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "airstrike", "attack", "dive", "breeze", "magicattack", "magicstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {46, 2} });
            break;
        case 162:
            this->setName("Giant Water Bug");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 15, 0, 10, 10, 5, 0, 130);
            this->setAIStats(100, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "bite", "defend", "resolve" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {47, 2} });
            break;
        case 163:
            this->setName("Diving Beetle");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 60, 18, 0, 8, 8, 5, 0, 130);
            this->setAIStats(100, 4, 1, 2, 0.1, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "dive", "waterstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {48, 2} });
            break;
        case 164:
            this->setName("Water Spider");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 65, 15, 0, 4, 4, 10, 0, 130);
            this->setAIStats(100, 5, 1, 2, 0.2, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "bite", "waterstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {61, 1}, {1041, 1} });
            break;
        case 165:
            this->setName("Ants");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 60, 10, 0, 7, 7, 10, 0, 130);
            this->setAIStats(100, 4, 1, 2, 0.4, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "bite", "charge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 3}, {3018, 1}, {4028, 1}, {5016, 1}, {6017, 1}, {7050, 1} });
            break;
        case 166:
            this->setName("Fire Ant Scout");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 40, 10, 0, 7, 7, 10, 0, 130);
            this->setAIStats(100, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "firestrike", "bite", "charge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {50, 1}, {3020, -4}, {4031, -4}, {5017, -4}, {6019, -4}, {7050, -4} });
            break;
        case 167:
            this->setName("Tick");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 40, 10, 0, 15, 5, 10, 0, 120);
            this->setAIStats(100, 4, 1, 2, 0.2, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "bite", "suck", "defend" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {1030, 1} });
            break;
        case 168:
            this->setName("Ladybug");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 40, 12, 0, 10, 5, 5, 0, 130);
            this->setAIStats(100, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "defend", "nibble" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {49, 1}, {7056, 1} });
            break;
        case 169:
            this->setName("Garden Spider");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 60, 15, 0, 3, 3, 10, 0, 130);
            this->setAIStats(100, 5, 1, 2, 0.2, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "poison", "earthstrike", "hammer" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {61, 1}, {1043, 1} });
            break;
        case 170:
            this->setName("Jumping Spider");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 60, 15, 0, 3, 3, 10, 0, 130);
            this->setAIStats(100, 5, 1, 2, 0.2, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "poison", "airstrike", "jump" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {61, 1}, {1045, 1} });
            break;
        case 171:
            this->setName("Fire Spider");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 60, 15, 0, 3, 3, 10, 0, 130);
            this->setAIStats(100, 5, 1, 2, 0.2, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "poison", "firestrike", "bite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {50, 1}, {61, 1}, {1042, 1} });
            break;
        case 172:
            this->setName("Turtle");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 140, 20, 0, 20, 10, 10, 0, 120);
            this->setAIStats(150, 2, 2, 2, 0.2, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "bite", "waterstrike", "defend", "resolve", "swimaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {29, 2}, {57, 1}, {1055, -4}, {2013, -4}, {2011, 1}, {3021, 1}, {4032, 1}, {5018, 1} });
            break;
        case 173:
            this->setName("Sturgeon");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 140, 35, 0, 8, 6, 5, 0, 150);
            this->setAIStats(150, 2, 1, 2, 0.1, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "icestrike", "attack", "chill", "flail" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {51, 2} });
            break;
        case 174:
            this->setName("Electric Catfish");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 140, 35, 0, 8, 8, 5, 0, 150);
            this->setAIStats(150, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "electricitystrike", "shock", "attack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1046, 1}, {7057, 1}, {7058, 1} });
            break;
        case 175:
            this->setName("Radioactive Catfish");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 140, 35, 0, 8, 8, 5, 0, 150);
            this->setAIStats(150, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "nuclearstrike", "shock", "attack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1047, 1}, {7059, 1}, {7060, 1} });
            break;
        case 176:
            this->setName("Fallen Catfish");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 140, 35, 0, 8, 8, 5, 0, 150);
            this->setAIStats(150, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "gravitystrike", "shock", "attack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1048, 1}, {7061, 1}, {7062, 1} });
            break;
        case 177:
            this->setName("Electric Detritus");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 45, 25, 25, 6, 6, 0, 0, 120);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "electricitystrike", "shock", "shock" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 3}, {52, 2}, {1084, 1} });
            break;
        case 178:
            this->setName("Radioactive Detritus");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 45, 25, 25, 6, 6, 0, 0, 120);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "nuclearstrike", "destabilize", "gammaray" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 3}, {53, 2}, {1085, 1} });
            break;
        case 179:
            this->setName("Fallen Detritus");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 45, 25, 25, 6, 6, 0, 0, 120);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "floataway", "gravitystrike", "shake", "pull" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 3}, {54, 2}, {1086, 1} });
            break;
        case 180:
            this->setName("Turkey");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 22, 0, 7, 7, 8, 0, 160);
            this->setAIStats(185, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "flail", "peck", "attack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {3022, 1}, {7037, 1}, {7038, 2}, {7039, 1}, {7042, 1} });
            break;
        case 181:
            this->setName("Armadillo");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 25, 0, 17, 17, 10, 0, 140);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "claw", "defend", "bulwark", "disease" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1049, -4}, {3023, 1}, {4033, 1}, {5019, 1}, {6020, 1} });
            break;
        case 182:
            this->setName("Prairie Dog");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 30, 0, 12, 12, 10, 0, 140);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "claw", "jump-yip", "bite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1022, -4} });
            break;
        case 183:
            this->setName("Buzzard");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 22, 0, 7, 7, 5, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1050, 1}, {2012, 1}, {7036, -4}, {7037, -4}, {7038, -4},
                {7039, -4}, {7040, -4}, {7041, -4}, {7042, -4}, {7043, -4}, {7044, 2}, {7045, 2} });
            break;
        case 184:
            this->setName("Falcon");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 22, 0, 7, 7, 5, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1062, 1}, {4034, 1}, {7063, 1}, {7036, -4}, {7037, -4}, {7038, -4},
                {7039, -4}, {7040, -4}, {7041, -4}, {7042, -4}, {7043, -4}, {7044, -4}, {7045, -4} });
            break;
        case 185:
            this->setName("Vulture");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 22, 0, 7, 7, 5, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {3024, -5}, {7038, 1}, {7044, 1}, {7045, 3} });
            break;
        case 186:
            this->setName("Barn Owl");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 22, 0, 7, 7, 5, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7038, 1}, {7044, 3}, {7045, 1} });
            break;
        case 187:
            this->setName("Hawk");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 22, 0, 7, 7, 5, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1050, 1}, {2012, 1}, {7036, -4}, {7037, -4}, {7038, 2},
                {7039, -4}, {7040, -4}, {7041, -4}, {7042, -4}, {7043, -4} });
            break;
        case 188:
            this->setName("Woodpecker");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 20, 0, 5, 5, 60, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "hammer", "peck" });
            this->setDrops(std::vector<std::pair<int, int>>{ {38, 2}, {1051, 1}, {6021, -4}, {7036, -4}, {7037, -4}, {7038, -4},
                {7039, -4}, {7040, -4}, {7041, -4}, {7042, -4}, {7043, -4}, {7044, -4}, {7045, -4} });
            break;
        case 189:
            this->setName("Lovebird");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 50, 0, 20, 5, 5, 5, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "flyaway", "breeze" });
            this->setDrops(std::vector<std::pair<int, int>>{ {38, 1}, {1027, 1}, {7036, -4}, {7037, -4}, {7038, -4},
                {7039, -4}, {7040, -4}, {7041, -4}, {7042, -4}, {7043, -4}, {7044, -4}, {7045, -4}, {7046, 1} });
            break;
        case 190:
            this->setName("Rabbit");
            minLevel = 52;
            maxLevel = 57;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 20, 0, 10, 10, 10, 0, 110);
            this->setAIStats(120, 2, 2, 2, 0.4, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "earthstrike", "attack", "nibble", "jump" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 3}, {55, 2}, {6022, 1} });
            break;
            
        // Tier 3 : Subtier 4 : Levels 65-69
        case 191:
            this->setName("Fire Ants");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 75, 20, 0, 10, 10, 10, 0, 140);
            this->setAIStats(100, 4, 1, 2, 0.4, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "firestrike", "bite", "charge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {50, 1}, {3020, 1}, {4031, 1}, {5017, 1}, {6019, 1}, {7050, 1} });
            break;
        case 192:
            this->setName("Orbweaver");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 0, 20, 5, 5, 10, 0, 140);
            this->setAIStats(110, 5, 1, 2, 0.2, 0.3);
            this->addBattleAbilities(std::vector<std::string>{ "poison", "wisp", "magicstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {1040, 1} });
            break;
        case 193:
            this->setName("Electric Eel");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 0, 25, 10, 10, 0, 5, 140);
            this->setAIStats(140, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "wisp", "shock", "spark" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {56, 2}, {1052, 1} });
            break;
        case 194:
            this->setName("Radioactive Eel");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 0, 25, 10, 10, 0, 5, 140);
            this->setAIStats(140, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "wisp", "destabilize", "gammaray" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {56, 2}, {1053, 1} });
            break;
        case 195:
            this->setName("Fallen Eel");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 0, 25, 10, 10, 0, 5, 140);
            this->setAIStats(140, 4, 1, 1, 0, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "wisp", "shake", "pull" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {56, 2}, {1054, 1} });
            break;
        case 196:
            this->setName("Snapping Turtle");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 160, 30, 0, 25, 15, 30, 0, 140);
            this->setAIStats(200, 2, 2, 2, 0.3, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "bite", "waterstrike", "swimaway" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {29, 2}, {57, 2}, {1055, 1}, {2013, 1}, {2011, 1}, {3021, 1}, {4032, 1}, {5018, 1} });
            break;
        case 197:
            this->setName("Peacock (boss)");
            minLevel = 69;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 140, 30, 0, 10, 10, 12, 0, 160);
            this->setAIStats(250, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "flail", "peck", "attack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {5, 2}, {6, 2}, {10, 2}, {11, 2}, {15, 2},
                {16, 2}, {38, 2}, {7036, 1}, {7037, 1}, {7038, 1}, {7039, 1}, {7040, 1}, {7041, 1},
                {7042, 1}, {7043, 1}, {7044, 1}, {7045, 1}, {7046, 1}, {7064, -1} });
            break;
        case 198:
            this->setName("Hare");
            minLevel = 52;
            maxLevel = 57;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 20, 0, 10, 10, 10, 0, 110);
            this->setAIStats(120, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "earthstrike", "attack", "nibble", "jump" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 3}, {55, 2}, {6022, 1} });
            break;
        case 199:
            this->setName("Waterthrush");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 22, 0, 7, 7, 5, 0, 180);
            this->setAIStats(180, 3, 2, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike", "icestrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {7036, 1}, {7044, 1}, {7045, 1} });
            break;
        case 200:
            this->setName("Blue Heron");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 28, 0, 10, 10, 8, 0, 190);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1056, 1}, {7036, 1}, {7045, 1} });
            break;
        case 201:
            this->setName("Brown Bear");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 30, 0, 12, 12, 10, 0, 140);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "claw", "charge", "maul", "chomp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {38, 3}, {1057, -4}, {4035, -11} });
            break;
        case 202:
            this->setName("Swimming Brown Bear");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 30, 0, 12, 12, 10, 0, 140);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "claw", "charge", "maul", "chomp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {38, 3}, {1057, 1}, {4035, 1} });
            break;
        case 203:
            this->setName("Deer");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 20, 0, 12, 12, 10, 0, 150);
            this->setAIStats(150, 4, 2, 1, 0, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "jump", "charge", "bandage" });
            this->setDrops(std::vector<std::pair<int, int>>{ {58, 3}, {3017, 1}, {7065, 1} });
            break;
        case 204:
            this->setName("Coyote");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 32, 0, 12, 12, 10, 0, 140);
            this->setAIStats(150, 5, 2, 2, 0.4, 0.25);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "claw", "charge", "bite" });
            this->setDrops(std::vector<std::pair<int, int>>{});
            break;
        case 205:
            this->setName("Cow");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 140, 30, 0, 15, 15, 10, 0, 150);
            this->setAIStats(200, 4, 2, 1, 0, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "charge", "bandage", "defend", "resolve", "heal", "grow", "enlarge", "bulwark", "dauntless" });
            this->setDrops(std::vector<std::pair<int, int>>{ {59, 3}, {62, 1}, {1059, -4} });
            break;
        case 206:
            this->setName("Baby Bear");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 20, 0, 10, 10, 8, 0, 130);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "claw", "charge", "maul", "chomp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {37, 2}, {1058, 1}, {4035, 1} });
            break;
        case 207:
            this->setName("Garter Snake");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 25, 0, 10, 10, 8, 0, 130);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "earthstrike", "flail", "lunge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {60, 2}, {1043, 1}, {1060, -5}, {6023, 1}, {7066, 1} });
            break;
        case 208:
            this->setName("Milk Snake");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 25, 0, 10, 10, 8, 0, 130);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "earthstrike", "flail", "lunge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {60, 2}, {1043, 1}, {1060, -5}, {6023, 1}, {7066, 1} });
            break;
        case 209:
            this->setName("Viper");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 25, 0, 10, 10, 8, 0, 130);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "earthstrike", "flail", "lunge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {60, 2}, {1043, 1}, {1060, -5}, {6023, 1}, {7066, 1} });
            break;
        case 210:
            this->setName("Tree Snake");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 30, 0, 12, 12, 8, 0, 130);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "airstrike", "flail", "lunge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {60, 2}, {1045, 1}, {1060, -5}, {6023, 1}, {7066, 1} });
            break;
        case 211:
            this->setName("Groundhog");
            minLevel = 52;
            maxLevel = 57;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 20, 0, 10, 10, 10, 0, 110);
            this->setAIStats(120, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "earthstrike", "attack", "nibble", "bite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1022, -4}, {7067, -4} });
            break;
        case 212:
            this->setName("Toad");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 80, 20, 0, 12, 12, 10, 0, 110);
            this->setAIStats(120, 3, 2, 2, 0.4, 0.25);
            this->addBattleAbilities(std::vector<std::string>{ "jump", "attack", "nibble" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {3025, 1}, {4036, 1}, {7077, 1} });
            break;
        case 213:
            this->setName("Tree Frog");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 0, 25, 5, 15, 0, 10, 130);
            this->setAIStats(120, 3, 2, 2, 0.4, 0.25);
            this->addBattleAbilities(std::vector<std::string>{ "drain", "siphon", "wisp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1027, 1}, {2014, 1}, {7078, 1} });
            break;
        case 214:
            this->setName("Whitetailed Eagle");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 26, 0, 9, 9, 8, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "claw", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1061, 1}, {2018, 1}, {4037, 1},
                {7079, 1}, {7036, -4}, {7037, -4}, {7038, -4}, {7039, -4}, {7040, -4}, {7041, -4},
                {7042, -4}, {7043, -4}, {7044, -4}, {7045, -4} });
            break;
        case 215:
            this->setName("Peregrine Falcon");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 26, 0, 9, 9, 8, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "claw", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1062, 1}, {2508, 1}, {4034, 1}, {7063, 1}, {7036, -4}, {7037, -4}, {7038, -4},
                {7039, -4}, {7040, -4}, {7041, -4}, {7042, -4}, {7043, -4}, {7044, -4}, {7045, -4} });
            break;
        case 216:
            this->setName("Merlin");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 0, 26, 9, 9, 0, 8, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "breeze", "wind", "swiftness", "slowness", "bolt" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1062, 1}, {1063, 1}, {4034, 1}, {7063, 1}, {7036, -4}, {7037, -4}, {7038, -4},
                {7039, -4}, {7040, -4}, {7041, -4}, {7042, -4}, {7043, -4}, {7044, -4}, {7045, -4} });
            break;
        case 217:
            this->setName("Goshawk");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 26, 0, 9, 9, 8, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "icestrike", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1050, 1}, {1064, 1}, {2012, 1}, {7036, -4}, {7037, -4}, {7038, -4},
                {7039, 1}, {7040, -4}, {7041, -4}, {7042, -4}, {7043, -4} });
            break;
        case 218:
            this->setName("Snow Owl");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 20, 20, 9, 9, 8, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "frost", "chill", "peck", "airstrike", "icestrike", "crystal" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {2509, 1}, {7036, -4}, {7037, -4}, {7038, -4},
                {7039, 1}, {7040, -4}, {7041, -4}, {7042, -4}, {7043, -4} });
            break;
        case 219:
            this->setName("Snow Bunting");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 16, 0, 7, 7, 5, 0, 180);
            this->setAIStats(180, 3, 2, 2, 0.2, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike", "icestrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {7038, 1}, {7039, 1}, {7040, 1} });
            break;
        case 220:
            this->setName("King Fisher (boss)");
            minLevel = 68;
            maxLevel = 68;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 110, 30, 0, 11, 11, 10, 0, 180);
            this->setAIStats(200, 1, 3, 2, 0.3, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {5, 2}, {6, 2}, {10, 2}, {11, 2}, {15, 2},
                {16, 2}, {28, 2}, {1065, 1}, {2015, 1}, {7036, -4}, {7037, -4}, {7038, -4}, {7039, -4}, {7040, -4},
                {7041, -4}, {7042, -4}, {7043, -4} });
            break;
            
        // Tier 3 : Subtier 5 : Levels 70-74
        case 221:
            this->setName("Black Widow (boss)");
            minLevel = 70;
            maxLevel = 70;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 30, 0, 8, 8, 10, 0, 150);
            this->setAIStats(200, 3, 1, 2, 0.2, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "poison", "wither", "firestrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {5, 2}, {6, 2}, {10, 2}, {11, 2}, {15, 2},
                {16, 2}, {28, 1}, {50, 2}, {61, 2}, {1042, 1}, {1066, 1} });
            break;
        case 222:
            this->setName("Brown Recluse (boss)");
            minLevel = 70;
            maxLevel = 70;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 30, 0, 8, 8, 10, 0, 150);
            this->setAIStats(200, 3, 1, 2, 0.2, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "poison", "wither", "earthstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {5, 2}, {6, 2}, {10, 2}, {11, 2}, {15, 2},
                {16, 2}, {28, 1}, {61, 2}, {1043, 1}, {1067, 1} });
            break;
        case 223:
            this->setName("Tarantula (boss)");
            minLevel = 70;
            maxLevel = 70;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 30, 0, 8, 8, 10, 0, 150);
            this->setAIStats(200, 3, 1, 2, 0.2, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "poison", "wither", "airstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {5, 2}, {6, 2}, {10, 2}, {11, 2}, {15, 2},
                {16, 2}, {28, 1}, {61, 2}, {1045, 1}, {1068, 1} });
            break;
        case 224:
            this->setName("Snow Spider");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 25, 0, 7, 7, 8, 0, 150);
            this->setAIStats(150, 5, 1, 2, 0.2, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "poison", "wither", "icestrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 1}, {61, 1}, {1044, 1} });
            break;
        case 225:
            this->setName("Fire Ant Queen (boss)");
            minLevel = 70;
            maxLevel = 70;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 30, 30, 10, 10, 5, 5, 150);
            this->setAIStats(200, 4, 1, 2, 0.4, 0);
            this->addBattleAbilities(std::vector<std::string>{ "firestrike", "fireseal", "flame", "fire" });
            this->setDrops(std::vector<std::pair<int, int>>{ {5, 2}, {6, 2}, {10, 2}, {11, 2}, {15, 2},
                {16, 2}, {27, 2}, {50, 2}, {3026, 1}, {4038, 1}, {5020, 1}, {6024, 1}, {7050, 1} });
            break;
        case 226:
            this->setName("Crocodile (boss)");
            minLevel = 71;
            maxLevel = 71;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 300, 35, 0, 10, 0, 20, 0, 150);
            this->setAIStats(400, 1, 5, 2, 0.3, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "hammer", "waterstrike", "bite", "flail", "chomp", "slash" });
            this->setDrops(std::vector<std::pair<int, int>>{ {11, 2}, {16, 2}, {21, 2}, {28, 8}, {1069, -1},
                {2016, -1}, {3027, 1}, {4039, 1}, {5021, 1}, {6025, 1}, {7080, 1}, {7081, 1} });
            break;
        case 227:
            this->setName("Alligator (boss)");
            minLevel = 71;
            maxLevel = 71;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 300, 35, 0, 10, 0, 20, 0, 150);
            this->setAIStats(400, 1, 5, 2, 0.3, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "hammer", "waterstrike", "bite", "flail", "chomp", "slash" });
            this->setDrops(std::vector<std::pair<int, int>>{ {11, 2}, {16, 2}, {21, 2}, {28, 8}, {1070, -1},
                {2017, -1}, {3028, 1}, {4040, 1}, {5022, 1}, {6026, 1}, {7080, 1}, {7081, 1} });
            break;
        case 228:
            this->setName("Sting Ray (boss)");
            minLevel = 72;
            maxLevel = 72;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 180, 60, 0, 10, 10, 5, 0, 140);
            this->setAIStats(140, 1, 5, 2, 0.2, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "electricityseal", "electricitystrike", "shock", "paralyze" });
            this->setDrops(std::vector<std::pair<int, int>>{ {11, 2}, {16, 2}, {21, 2}, {28, 2}, {1071, 1} });
            break;
        case 229:
            this->setName("Nuclear Ray (boss)");
            minLevel = 72;
            maxLevel = 72;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 180, 60, 0, 10, 10, 5, 0, 140);
            this->setAIStats(140, 1, 5, 2, 0.2, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "nuclearseal", "nuclearstrike", "destabilize", "radiate" });
            this->setDrops(std::vector<std::pair<int, int>>{ {11, 2}, {16, 2}, {21, 2}, {28, 2}, {1072, 1} });
            break;
        case 230:
            this->setName("Great Ray (boss)");
            minLevel = 72;
            maxLevel = 72;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 180, 60, 0, 10, 10, 5, 0, 140);
            this->setAIStats(140, 1, 5, 2, 0.2, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "gravityseal", "gravitystrike", "shake", "fell" });
            this->setDrops(std::vector<std::pair<int, int>>{ {11, 2}, {16, 2}, {21, 2}, {28, 2}, {1073, 1} });
            break;
        case 231:
            this->setName("Crayfish King (boss)");
            minLevel = 71;
            maxLevel = 71;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 160, 30, 0, 15, 8, 25, 0, 130);
            this->setAIStats(130, 1, 3, 2, 0.2, 0.2);
            this->addBattleAbilities(std::vector<std::string>{ "pinch", "charge", "attack" });
            this->setDrops(std::vector<std::pair<int, int>>{ {11, 2}, {16, 2}, {21, 2}, {28, 1},
                {2510, 1}, {3029, 1}, {4041, 1} });
            break;
        case 232:
            this->setName("Bald Eagle (boss)");
            minLevel = 73;
            maxLevel = 73;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 180, 40, 0, 15, 15, 12, 0, 180);
            this->setAIStats(200, 1, 5, 2, 0.3, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "airseal", "airstrike", "claw" });
            this->setDrops(std::vector<std::pair<int, int>>{ {11, 4}, {16, 2}, {21, 2}, {28, 2}, {1074, 1},
                {2019, 1}, {4037, 1}, {7079, 1}, {7036, -4}, {7037, -4}, {7038, -4}, {7039, -4}, {7040, -4},
                {7041, -4}, {7042, -4}, {7043, -4}, {7044, -4}, {7045, -4} });
            break;
        case 233:
            this->setName("Wolf");
            minLevel = 70;
            maxLevel = 73;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 110, 45, 0, 12, 12, 10, 0, 140);
            this->setAIStats(200, 5, 2, 2, 0.4, 0.25);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "claw", "charge", "bite" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 3}, {1075, 1}, {2020, 1}, {7082, -4} });
            break;
        case 234:
            this->setName("Alpha Wolf (boss)");
            minLevel = 74;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 280, 52, 0, 12, 12, 20, 0, 140);
            this->setAIStats(200, 1, 5, 2, 0.4, 0.25);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "claw", "charge", "bite", "chomp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {11, 4}, {16, 2}, {21, 2}, {28, 3}, {1076, 1}, {2021, 1}, {7082, 1} });
            break;
        case 235:
            this->setName("Black Bear");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 130, 40, 0, 15, 15, 10, 0, 140);
            this->setAIStats(200, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "claw", "charge", "maul", "chomp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {38, 3}, {1057, 1}, {4035, 1} });
            break;
        case 236:
            this->setName("Mama Bear (boss)");
            minLevel = 74;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 230, 55, 0, 18, 18, 15, 0, 140);
            this->setAIStats(200, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "earthstrike", "claw", "charge", "maul", "chomp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {11, 4}, {16, 2}, {21, 2}, {38, 3}, {1057, -11}, {4035, -11} });
            break;
        case 237:
            this->setName("Bison");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 160, 40, 0, 20, 20, 10, 0, 150);
            this->setAIStats(250, 4, 2, 1, 0, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "charge", "bandage", "defend", "resolve", "heal", "grow", "enlarge", "bulwark", "dauntless" });
            this->setDrops(std::vector<std::pair<int, int>>{ {59, 8}, {62, 1}, {3017, -4} });
            break;
        case 238:
            this->setName("Raging Bull (boss)");
            minLevel = 74;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 120, 60, 0, 18, 18, 10, 0, 150);
            this->setAIStats(250, 4, 2, 1, 0, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "charge", "firestrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {11, 4}, {16, 2}, {21, 2}, {59, 4}, {62, 2}, {1077, 1}, {3017, 1}, {7083, -4} });
            break;
        case 239:
            this->setName("Wild Horse");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 130, 35, 30, 15, 15, 10, 0, 140);
            this->setAIStats(200, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "charge", "dauntless", "bulwark", "dust", "dirt" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 3}, {1077, -4}, {1078, -4}, {7083, -4} });
            break;
        case 240:
            this->setName("Ocelot");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 130, 0, 40, 15, 15, 0, 10, 150);
            this->setAIStats(200, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "magicattack", "wisp", "lethargy", "deftness" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1079, 1}, {1022, 1} });
            break;
        case 241:
            this->setName("Jaguar");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 130, 0, 40, 15, 15, 0, 10, 150);
            this->setAIStats(200, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "magicattack", "wisp", "lethargy", "deftness" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {1079, 1}, {1022, 1} });
            break;
        case 242:
            this->setName("Copperhead");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 120, 35, 35, 12, 12, 10, 10, 140);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "flame", "fire", "venom", "revive" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {60, 2}, {1042, 1}, {1060, -5}, {6023, 1}, {7066, 1} });
            break;
        case 243:
            this->setName("Rattlesnake");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 120, 35, 35, 12, 12, 10, 10, 140);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "dirt", "dust", "venom", "revive" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {60, 2}, {1043, 1}, {1060, -5}, {6023, 1}, {7066, 1}, {7085, 1} });
            break;
        case 244:
            this->setName("Mountain Goat");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 130, 55, 0, 12, 12, 5, 0, 150);
            this->setAIStats(250, 4, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "bite", "chomp", "nibble", "charge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {62, 2}, {3017, -4} });
            break;
        case 245:
            this->setName("Wild Boar (boss)");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 160, 55, 0, 12, 12, 10, 0, 150);
            this->setAIStats(250, 4, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "charge", "lunge", "beserk", "swiftness" });
            this->setDrops(std::vector<std::pair<int, int>>{ {11, 4}, {16, 2}, {21, 2}, {28, 3}, {2511, 1} });
            break;
        case 246:
            this->setName("Arctic Hare");
            minLevel = 58;
            maxLevel = 63;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 110, 30, 0, 12, 12, 12, 0, 130);
            this->setAIStats(120, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "icestrike", "attack", "nibble", "jump" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 3}, {55, 2}, {6022, 1} });
            break;
        case 247:
            this->setName("Grizzly Bear");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 160, 45, 0, 15, 15, 15, 0, 140);
            this->setAIStats(200, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "attack", "claw", "charge", "maul", "chomp" });
            this->setDrops(std::vector<std::pair<int, int>>{ {38, 3}, {1057, 1}, {4035, 1} });
            break;
        case 248:
            this->setName("Lemming");
            minLevel = 62;
            maxLevel = 67;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 120, 30, 0, 12, 12, 15, 0, 110);
            this->setAIStats(180, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "icestrike", "attack", "bite", "disease" });
            this->setDrops(std::vector<std::pair<int, int>>{ {38, 2}, {1022, -4}, {1080, 1} });
            break;
        case 249:
            this->setName("Moose");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 140, 0, 40, 12, 12, 0, 10, 150);
            this->setAIStats(150, 4, 2, 1, 0, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "frost", "crystal", "chill", "bandage" });
            this->setDrops(std::vector<std::pair<int, int>>{ {58, 4}, {1026, 1}, {3030, 1}, {7083, -4} });
            break;
        case 250:
            this->setName("Snow Leopard");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 130, 45, 0, 15, 15, 10, 0, 150);
            this->setAIStats(200, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "iceseal", "icestrike", "lethargy", "deftness" });
            this->setDrops(std::vector<std::pair<int, int>>{ {38, 2}, {1064, 1}, {1079, -4}, {2022, -4} });
            break;
        case 251:
            this->setName("Polar Bear (boss)");
            minLevel = 74;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 200, 60, 45, 15, 15, 15, 15, 150);
            this->setAIStats(250, 1, 6, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "icestrike", "iceseal", "frost", "crystal", "enlarge", "beserk" });
            this->setDrops(std::vector<std::pair<int, int>>{ {6, 5}, {16, 4}, {21, 4}, {38, 4}, {1081, 1}, {2023, 1}, {4035, 1} });
            break;
        case 252:
            this->setName("Yeti (boss)");
            minLevel = 74;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 400, 65, 65, 35, 35, 15, 15, 150);
            this->setAIStats(250, 1, 6, 2, 0.4, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "icestrike", "iceseal", "frost", "crystal", "chill", "freeze", "grow", "enlarge", "resolve", "dauntless", "defend", "bulwark" });
            this->setDrops(std::vector<std::pair<int, int>>{ {6, 5}, {16, 4}, {21, 4}, {38, 6}, {4042, 1} });
            break;
        case 253:
            this->setName("Great Horned Owl (boss)");
            minLevel = 73;
            maxLevel = 73;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 180, 35, 0, 15, 15, 40, 0, 180);
            this->setAIStats(200, 1, 5, 2, 0.3, 0.1);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "airseal", "airstrike", "claw" });
            this->setDrops(std::vector<std::pair<int, int>>{ {6, 5}, {16, 4}, {21, 4}, {38, 3}, {3017, 1} });
            break;
        case 254:
            this->setName("Whitejay");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 20, 0, 7, 7, 7, 0, 180);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "lightstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {38, 1}, {7045, 2} });
            break;
        case 255:
            this->setName("Blackjay");
            minLevel = 60;
            maxLevel = 64;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 70, 20, 0, 7, 7, 7, 0, 180);
            this->setAIStats(150, 4, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "darkstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {38, 1}, {7044, 2} });
            break;
        case 256:
            this->setName("White Hawk");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 26, 0, 9, 9, 9, 0, 180);
            this->setAIStats(200, 2, 2, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "claw", "lightstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1050, 1}, {2012, 1}, {7045, 2} });
            break;
        case 257:
            this->setName("Black Hawk");
            minLevel = 65;
            maxLevel = 69;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 90, 26, 0, 9, 9, 9, 0, 180);
            this->setAIStats(200, 2, 2, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "dive", "peck", "claw", "darkstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1050, 1}, {2012, 1}, {7044, 2} });
            break;
        case 258:
            this->setName("White Moth");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 35, 16, 12, 5, 5, 0, 0, 130);
            this->setAIStats(120, 2, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "brighten", "ray", "lightstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {41, 2}, {1082, 1}, {7016, 1} });
            break;
        case 259:
            this->setName("Black Moth");
            minLevel = 55;
            maxLevel = 59;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 35, 16, 12, 5, 5, 0, 0, 130);
            this->setAIStats(120, 2, 1, 1, 0, 0.4);
            this->addBattleAbilities(std::vector<std::string>{ "obscure", "shadow", "darkstrike" });
            this->setDrops(std::vector<std::pair<int, int>>{ {27, 2}, {36, 1}, {37, 1}, {41, 2}, {1083, 1}, {7016, 1} });
            break;
        case 260:
            this->setName("Light's Treefrog");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 120, 0, 35, 8, 18, 0, 15, 140);
            this->setAIStats(150, 3, 2, 2, 0.4, 0.25);
            this->addBattleAbilities(std::vector<std::string>{ "drain", "siphon", "ray" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1082, 1}, {2014, 1}, {7078, 1} });
            break;
        case 261:
            this->setName("Dark's Treefrog");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 120, 0, 35, 8, 18, 0, 15, 140);
            this->setAIStats(150, 3, 2, 2, 0.4, 0.25);
            this->addBattleAbilities(std::vector<std::string>{ "drain", "siphon", "shadow" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {1083, 1}, {2014, 1}, {7078, 1} });
            break;
        case 262:
            this->setName("White Squirrel");
            minLevel = 63;
            maxLevel = 68;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 25, 0, 14, 14, 12, 0, 130);
            this->setAIStats(120, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "brighten", "bite", "claw" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {42, 2}, {63, 2}, {1022, -4} });
            break;
        case 263:
            this->setName("Black Squirrel");
            minLevel = 63;
            maxLevel = 68;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 100, 25, 0, 14, 14, 12, 0, 130);
            this->setAIStats(120, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "obscure", "bite", "claw" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 2}, {42, 2}, {64, 2}, {1022, -4} });
            break;
        case 264:
            this->setName("Light Viper");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 130, 40, 0, 12, 12, 8, 0, 140);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "lightstrike", "flail", "lunge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {60, 2}, {1087, 1}, {1060, -5}, {6023, 1}, {7066, 1} });
            break;
        case 265:
            this->setName("Dark Viper");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 130, 40, 0, 12, 12, 8, 0, 140);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.15);
            this->addBattleAbilities(std::vector<std::string>{ "darkstrike", "flail", "lunge" });
            this->setDrops(std::vector<std::pair<int, int>>{ {28, 1}, {60, 2}, {1088, 1}, {1060, -5}, {6023, 1}, {7066, 1} });
            break;
        case 266:
            this->setName("Light Elf");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 140, 0, 45, 12, 12, 0, 20, 140);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "bright", "illuminate", "ray", "beam", "bolt" });
            this->setDrops(std::vector<std::pair<int, int>>{});
            break;
        case 267:
            this->setName("Dark Elf");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 140, 0, 45, 12, 12, 0, 20, 140);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "obscure", "hide", "shadow", "darkness", "bolt" });
            this->setDrops(std::vector<std::pair<int, int>>{});
            break;
        /*case 268:
            this->setName("Green Elf");
            minLevel = 70;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 140, 0, 45, 12, 12, 0, 20, 140);
            this->setAIStats(150, 2, 2, 2, 0.4, 0.05);
            this->addBattleAbilities(std::vector<std::string>{ "???", "???", "???", "???", "bolt" });
            this->setDrops(std::vector<std::pair<int, int>>{});
            break;*/
        case 269:
            this->setName("Light Elvin King (boss)");
            minLevel = 74;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 240, 0, 65, 20, 20, 0, 30, 150);
            this->setAIStats(200, 2, 2, 2, 0.4, 0);
            this->addBattleAbilities(std::vector<std::string>{ "bright", "illuminate", "ray", "beam", "bolt" });
            this->setDrops(std::vector<std::pair<int, int>>{});
            break;
        case 270:
            this->setName("Dark Elvin King (boss)");
            minLevel = 74;
            maxLevel = 74;
            this->level = core_functions::randomInt(minLevel, maxLevel);
            lM = core_functions::getStatMultiplier(level, minLevel, maxLevel);
            this->setUnitStats(lM, 240, 0, 65, 20, 20, 0, 30, 150);
            this->setAIStats(200, 2, 2, 2, 0.4, 0);
            this->addBattleAbilities(std::vector<std::string>{ "obscure", "hide", "shadow", "darkness", "bolt" });
            this->setDrops(std::vector<std::pair<int, int>>{});
            break;
            
        // Tier 4 : Subtier 1 : Levels 75-79
        case 301:
            break;

        // Ally units
        // Dimension I
        case 501: // sells food bit and pebble
            this->setName("Conscious Drowning Insect (peddler)");
            this->level = 4;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(2, -1, 2, 0, 0, 0);
            this->setDrops(std::vector<std::pair<int, int>>{ {1, 3}, {1001, 1} });
            break;
        case 502: // sells subtier 2/3 stuff 
            this->setName("Conscious Snail (peddler)");
            this->level = 9;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(4, -1, 0, 0, 0, 0);
            break;
        case 503: // sells subtier 2/3 stuff
            this->setName("Conscious Guppy (peddler)");
            this->level = 9;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(4, -1, 0, 0, 0, 0);
            break;
        case 504: // Buys stuff
            this->setName("Conscious Slug (scavenger)");
            this->level = 9;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(4, -4, 0, 0, 0, 0);
            break;
        case 505: // Sells subtier 1-5 stuff
            this->setName("Conscious Goldfish (peddler)");
            this->level = 14;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(6, -1, 0, 0, 0, 0);
            break;
        case 506: // Buys stuff
            this->setName("Conscious Cricket (scavenger)");
            this->level = 14;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(8, -4, 0, 0, 0, 0);
            break;
        case 507: // Sells D1 upgrades
            this->setName("GloFish (researcher)");
            this->level = 24;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(2, -11, 0, 0, 0, 0);
            break;
        case 508: // Sells D1 abilities
            this->setName("Cichlid (trainer)");
            this->level = 24;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(2, -12, 0, 0, 0, 0);
            break;
        case 509: // Provides quests
            this->setName("Bottom Feeder (solicitor)");
            this->level = 9;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(1, -13, 0, 0, 0, 0);
            break;
        case 510: // Provides quests
            this->setName("Conscious Housefly (solicitor)");
            this->level = 19;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(2, -13, 0, 0, 0, 0);
            break;
        case 511: // Smelts items
            this->setName("Conscious Crab (smelter)");
            this->level = 19;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(2, -15, 0, 0, 0, 0);
            break;
        case 512: // Smelts items
            this->setName("Conscious Otocinclus (smelter)");
            this->level = 19;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(4, -15, 0, 0, 0, 0);
            break;
        case 513: // Upgrades items
            this->setName("Conscious Platy (plover)");
            this->level = 24;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(6, -16, 0, 0, 0, 0);
            break;

        // Dimension II
        case 521: // several in air
            this->setName("Conscious Gnat (scavenger)");
            this->level = 29;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(8, -4, 0, 0, 0, 0);
            break;
        case 522: // several in air
            this->setName("Conscious Fly (collector)");
            this->level = 34;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(12, -5, 0, 0, 0, 0);
            break;
        case 523: // several at bottom
            this->setName("Conscious Grub (scavenger)");
            this->level = 29;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(10, -4, 0, 0, 0, 0);
            break;
        case 524: // several at bottom
            this->setName("Conscious Grub (collector)");
            this->level = 34;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(15, -5, 0, 0, 0, 0);
            break;
        case 525: // several in air
            this->setName("Conscious Flee (peddler)");
            this->level = 29;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(6, -1, 0, 0, 0, 0);
            break;
        case 526: // several in air
            this->setName("Conscious Fly (vendor)");
            this->level = 34;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(6, -2, 0, 0, 0, 0);
            break;
        case 527: // several at bottom
            this->setName("Conscious Larva (peddler)");
            this->level = 29;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(6, -1, 0, 0, 0, 0);
            break;
        case 528: // several at bottom
            this->setName("Conscious Larva (vendor)");
            this->level = 34;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(6, -2, 0, 0, 0, 0);
            break;
        case 529: // several in water
            this->setName("Conscious Toxic Minnow (broker)");
            this->level = 39;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(4, -7, 0, 0, 0, 0);
            break;
        case 530:
            this->setName("Toxic GloFish (researcher)");
            this->level = 44;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(4, -11, 0, 0, 0, 0);
            break;
        case 531:
            this->setName("Toxic Cichlid (trainer)");
            this->level = 44;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(4, -12, 0, 0, 0, 0);
            break;
        case 532:
            this->setName("Toxic Bottom Feeder (solicitor)");
            this->level = 49;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(2, -13, 0, 0, 0, 0);
            break;
        case 533:
            this->setName("Pilot Fish (handler)");
            this->level = 49;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(2, -14, 0, 0, 0, 0);
            break;
        case 534: // several in water
            this->setName("Conscious Carp (smelter)");
            this->level = 44;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(10, -15, 0, 0, 0, 0);
            break;
        case 535: // several in water
            this->setName("Conscious Bass (plover)");
            this->level = 44;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(6, -16, 0, 0, 0, 0);
            break;
        case 536: // couple at end
            this->setName("Conscious Turtle (smith)");
            this->level = 49;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(6, -17, 0, 0, 0, 0);
            break;
        case 537: // several in various places at end
            this->setName("Conscious Catfish (forger)");
            this->level = 44;
            this->setUnitStats(lM, 1, 0, 0, 0, 0, 0, 0, 0);
            this->setAIStats(8, -19, 0, 0, 0, 0);
            break;

        default:
            std::cout << "ERROR: Unit ID " << unitID << " not found in unit reference.\n";
            break;
    }

    if (specifiedLevel != -1) { // level is specified
        this->level = specifiedLevel;
    }
}

// Stat setters with and without the multiplier
void aiUnit::setAIStats(int energyValue, int maxHerd, int spaceTaken, int allyState,
    double attackProbability, double spawnProbability) {
    this->level = level;
    this->energyValue = energyValue;
    this->maxHerd = maxHerd;
    this->spaceTaken = spaceTaken;
    this->allyState = allyState;
    this->attackProbability = attackProbability;
    this->spawnProbability = spawnProbability;
}

// This is the battle ai
Ability aiUnit::chooseBattleAbility(Battle currentBattle, int aiCode) { // just have ai pick a random ability for now
    if (this->getBattleAbilities().size() == 0) {
        return Ability("nothing");
    }
    std::vector<int> weights{}; // weights
    int battleState{};
    int nextState{};
    Battle currBattle = Battle(currentBattle);
    for (size_t i = 0; i < this->getBattleAbilities().size(); i++) {
        weights.push_back(1);
    }
    /*
    switch (aiCode) {
        case 0: // random
            for (size_t i = 0; i < this->getBattleAbilities().size(); i++) {
                weights.push_back(1); // add weights
            }
            break;
        case 1: // don't use "nothing" as much
            battleState = currentBattle.getEnemy().getCurrHealth() - currentBattle.getPlayer().getCurrHealth();
            for (size_t i = 0; i < this->getBattleAbilities().size(); i++) {
                if (this->getBattleAbilities().at(i).getName().compare("nothing") == 0) {
                    weights.push_back(1); // add weights
                }
                else {
                    weights.push_back(2);
                }
            }
            break;
        case 2: // based on health difference
            battleState = currentBattle.getEnemy().getCurrHealth() - currentBattle.getPlayer().getCurrHealth();
            for (size_t i = 0; i < this->getBattleAbilities().size(); i++) {
                currBattle = Battle(currentBattle);
                currBattle.setDisplayMessages(false);
                currBattle.attack(this->getBattleAbilities().at(i));
                if (currBattle.getPlayer().getStatusAlive()) {
                    nextState = currBattle.getEnemy().getCurrHealth() - currBattle.getPlayer().getCurrHealth();
                }
                else {
                    nextState = currBattle.getPlayer().getMaxHealth(); // kill player if can
                }
                // use y = mx + b = x/2 + 10 (m = 1/2, b = 10)
                if ((nextState - battleState) <= (1 - constants::dimension2bConstant) / constants::dimension2mConstant) {
                    weights.push_back(1); // still possible to use every ability
                }
                else {
                    weights.push_back(static_cast<int>(std::round(constants::dimension2mConstant * (nextState - battleState) + constants::dimension2bConstant)));
                }
            }
            break;
        case 3: // based on state calculation ( status effects)
            battleState = this->calculateBattleState(currBattle);
            for (size_t i = 0; i < this->getBattleAbilities().size(); i++) {
                currBattle = Battle(currentBattle);
                currBattle.setDisplayMessages(false);
                currBattle.attack(this->getBattleAbilities().at(i));
                nextState = this->calculateBattleState(currBattle);
                weights.push_back(static_cast<int>(std::floor(std::exp(constants::dimension3ExponentConstant * (nextState - battleState)))) + 1); // add weights
            }
            break;
        case 4: // based on state calculation ( status effects + memory)
            battleState = this->calculateBattleState(currBattle);
            for (size_t i = 0; i < this->getBattleAbilities().size(); i++) {
                currBattle = Battle(currentBattle);
                currBattle.setDisplayMessages(false);
                currBattle.attack(this->getBattleAbilities().at(i));
                nextState = this->calculateBattleState(currBattle);
                weights.push_back(static_cast<int>(std::floor(std::exp(constants::dimension3ExponentConstant * (nextState - battleState)))) + 1); // add weights
            }
            break;
        default:
            std::cout << "ERROR: ai code " << aiCode << " not found.\n";
    }
    */
    return this->getBattleAbilities().at(core_functions::randomFromWeights(weights));
}
int aiUnit::calculateBattleState(Battle currentBattle) { // for now just calculate damage
    int battleState{ 0 };
    battleState += currentBattle.getEnemy().getCurrHealth() - currentBattle.getPlayer().getCurrHealth();
    return battleState;
}

// Shuffle item inventory and reset timer
void aiUnit::shuffleItemInventory() {
    std::vector<int> possibleItems{};
    int unitDimension{ this->level / constants::dimensionLevels + 1 };
    switch (unitDimension) {
        case 4:
            possibleItems.insert(possibleItems.end(), { });
            [[fallthrough]];
        case 3:
            possibleItems.insert(possibleItems.end(), { });
            [[fallthrough]];
        case 2:
            possibleItems.insert(possibleItems.end(), { 5, 10, 15, 20, 27, 28, 29, 36,
                1008, 1011, 1018, 1019, 2006, 2501, 3011, 4019, 5011, 6011, 7013, 7014, 7029, 7030, 7031, 7032, 7033 });
            [[fallthrough]];
        case 1:
            possibleItems.insert(possibleItems.end(), { 1, 2, 3, 4, 9, 14, 19, 35,
                1001, 1002, 1017, 2001, 3010, 4018, 5010, 6010,
                7001, 7002, 7003, 7004, 7005, 7015, 7023, 7024, 7025, 7026, 7027, 7028 });
            break;
        default:
            std::cout << this->getName() << " with level " << this->level << " cannot find "
                "dimension for shuffling item inventory.\n";
            break;
    }
    // Check to ensure reserved inventory exists
    if (this->unitDrops.size() < this->spaceTaken) {
        std::cout << "ERROR: " << this->getName() << " has unitDropsSize < spaceTaken. Cannot reshuffle inventory.\n";
        return;
    }
    // Remove items already reserved in inventory
    for (int i{ 0 }; i < this->spaceTaken; i++) {
        if (possibleItems.size() == 0) {
            break;
        }
        auto index = std::find(possibleItems.begin(), possibleItems.end(), this->unitDrops.at(i).first);
        if (index != possibleItems.end()) {
            possibleItems.erase(index);
        }
    }
    // Shuffle rest of existing inventory
    for (int i{ this->spaceTaken }; i < this->unitDrops.size(); i++) {
        if (possibleItems.size() == 0) {
            break;
        }
        int nextItem{ core_functions::randomInt(possibleItems.size() - 1) };
        this->unitDrops.at(i).first = possibleItems.at(nextItem);
        possibleItems.erase(possibleItems.begin() + nextItem);
    }
    // If needing to add items to make inventory larger then shuffle these as well
    for (size_t i{ this->unitDrops.size() }; i < this->energyValue; i++) {
        if (possibleItems.size() == 0) {
            break;
        }
        int nextItem{ core_functions::randomInt(possibleItems.size() - 1) };
        this->unitDrops.push_back({ possibleItems.at(nextItem), 0 });
        possibleItems.erase(possibleItems.begin() + nextItem);
    }
    // Shuffle stock quantities
    for (std::pair<int, int>& i : this->unitDrops) {
        if (Item(i.first).isConsumable()) {
            i.second = core_functions::randomInt(1, constants::maxConsumableStock * unitDimension);
        }
        else {
            i.second = core_functions::randomInt(1, constants::maxRestStock * unitDimension);
        }
    }
}

// Shuffle upgrade inventory and reset timer
void aiUnit::shuffleUpgradeInventory() {
    std::vector<int> possibleUpgrades{};
    int unitDimension{ this->level / constants::dimensionLevels + 1 };
    switch (unitDimension) {
        case 4:
            possibleUpgrades.insert(possibleUpgrades.end(), { });
            [[fallthrough]];
        case 3:
            possibleUpgrades.insert(possibleUpgrades.end(), { });
            [[fallthrough]];
        case 2:
            possibleUpgrades.insert(possibleUpgrades.end(), { 121, 122, 123, 124, 125, 126 });
            [[fallthrough]];
        case 1:
            possibleUpgrades.insert(possibleUpgrades.end(), { 101, 102, 103, 104, 105, 106, 107, 108, 109 });
            break;
        default:
            std::cout << this->getName() << " with level " << this->level << " cannot find "
                "dimension for shuffling upgrade inventory.\n";
            break;
    }
    // Check to ensure reserved inventory exists
    if (this->unitDrops.size() < this->spaceTaken) {
        std::cout << "ERROR: " << this->getName() << " has unitDropsSize < spaceTaken. Cannot reshuffle upgrades.\n";
        return;
    }
    // Remove items already reserved in inventory
    for (int i{ 0 }; i < this->spaceTaken; i++) {
        if (possibleUpgrades.size() == 0) {
            break;
        }
        auto index = std::find(possibleUpgrades.begin(), possibleUpgrades.end(), this->unitDrops.at(i).first);
        if (index != possibleUpgrades.end()) {
            possibleUpgrades.erase(index);
        }
    }
    // Shuffle rest of existing inventory
    for (int i{ this->spaceTaken }; i < this->unitDrops.size(); i++) {
        if (possibleUpgrades.size() == 0) {
            break;
        }
        int nextItem{ core_functions::randomInt(possibleUpgrades.size() - 1) };
        this->unitDrops.at(i).first = possibleUpgrades.at(nextItem);
        possibleUpgrades.erase(possibleUpgrades.begin() + nextItem);
    }
    // If needing to add items to make inventory larger then shuffle these as well
    for (size_t i{ this->unitDrops.size() }; i < this->energyValue; i++) {
        if (possibleUpgrades.size() == 0) {
            break;
        }
        int nextItem{ core_functions::randomInt(possibleUpgrades.size() - 1) };
        this->unitDrops.push_back({ possibleUpgrades.at(nextItem), 0 });
        possibleUpgrades.erase(possibleUpgrades.begin() + nextItem);
    }
}

// Shuffle ability inventory and reset timer
void aiUnit::shuffleAbilityInventory() {
    std::vector<std::string> possibleAbilities{};
    int unitDimension{ this->level / constants::dimensionLevels + 1 };
    switch (unitDimension) {
        case 4:
            possibleAbilities.insert(possibleAbilities.end(),
                { });
            [[fallthrough]];
        case 3:
            possibleAbilities.insert(possibleAbilities.end(),
                { });
            [[fallthrough]];
        case 2:
            possibleAbilities.insert(possibleAbilities.end(),
                { "hemorrhage", "charge", "pinch", "rub", "coldslash", "magicstrike", "wilt", "jumpaway", "recoil" });
            [[fallthrough]];
        case 1:
            possibleAbilities.insert(possibleAbilities.end(),
                { "bleed", "magicattack", "swimaway", "bite", "excrete", "dive" });
            break;
        default:
            std::cout << this->getName() << " with level " << this->level << " cannot find "
                "dimension for shuffling ability inventory.\n";
            break;
    }
    // Shuffle inventory
    this->setBattleAbilities(std::vector<Ability>{});
    for (size_t i{ 0 }; i < this->energyValue; i++) {
        if (possibleAbilities.size() == 0) {
            break;
        }
        int nextItem{ core_functions::randomInt(possibleAbilities.size() - 1) };
        this->addBattleAbility(possibleAbilities.at(i));
        possibleAbilities.erase(possibleAbilities.begin() + nextItem);
    }
}

std::string aiUnit::saveGame() {
    std::string fileString{};
    fileString += "*DEFINE=aiUnit\n";
    fileString += Unit::saveGame();
    fileString += "unitID=" + std::to_string(this->unitID) + "\n";
    fileString += "level=" + std::to_string(this->level) + "\n";
    fileString += "energyValue=" + std::to_string(this->energyValue) + "\n";
    fileString += "maxHerd=" + std::to_string(this->maxHerd) + "\n";
    fileString += "spaceTaken=" + std::to_string(this->spaceTaken) + "\n";
    fileString += "allyState=" + std::to_string(this->allyState) + "\n";
    fileString += "attackProbability=" + std::to_string(this->attackProbability) + "\n";
    fileString += "attackDistance=" + std::to_string(this->attackDistance) + "\n";
    fileString += "spawnProbability=" + std::to_string(this->spawnProbability) + "\n";
    fileString += "*VECTOR=unitDrops\n";
    for (std::pair<int, int> i : this->unitDrops) {
        fileString += std::to_string(i.first) + " " + std::to_string(i.second) + "\n";
    }
    fileString += "*END\n"; // end vector
    fileString += "coolDown=" + std::to_string(this->cooldDown) + "\n";
    fileString += "*END\n"; // end aiUnit
    return fileString;
}