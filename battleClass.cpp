/*
battleClass.cpp
The battle class creates dynamic battle instantiations. May be a subclass of some "interaction
class" in the future to include interactions with neutral or friendly units (or even non-fighting
interactions with enemies). For now I also assume "player" is controlled by the player while
"enemy" is controlled by the ai of the unit class.
*/

#include <iostream>
#include <fstream>
#include <math.h>
#include "battleClass.h"
#include "unitClass.h"
#include "abilityClass.h"
#include "coreFunctions.h"

// base constructor
Battle::Battle(Player player, aiUnit enemy) {
    this->player = player;
    this->enemy = enemy;
    this->playerTurn = true;
}
Battle::Battle(Player player, aiUnit enemy, bool turn) {
    this->player = player;
    this->enemy = enemy;
    this->playerTurn = turn;
}

// In case there's anything that needs to be calculated before the turn starts
void Battle::startTurn() {
    bool loseTurn = false;
    Unit *attacker;
    Unit *defender;
    if (this->playerTurn) {
        attacker = &this->player;
        defender = &this->enemy;
    }
    else {
        attacker = &this->enemy;
        defender = &this->player;
    }
    if (attacker->getStatusFell()) {
        if (this->displayMessages) {
            std::cout << attacker->getName() << " fell and cannot take his turn!\n";
        }
        loseTurn = true;
    }
    else if (attacker->getStatusShaken()) {
        if (this->displayMessages) {
            std::cout << attacker->getName() << " is shook and cannot take his turn!\n";
        }
        loseTurn = true;
    }
    if ((attacker->getStatusParalyze()) && (core_functions::linearProbability(constants::paralyzeConstant))) {
        if (this->displayMessages) {
            std::cout << attacker->getName() << " is too paralyzed to take his turn!\n";
        }
        loseTurn = true;
    }
    else if ((attacker->getStatusShock()) && (core_functions::linearProbability(constants::shockConstant))) {
        if (this->displayMessages) {
            std::cout << attacker->getName() << " is too shocked to take his turn!\n";
        }
        loseTurn = true;
    }
    if ((attacker->getStatusFrozen()) && (core_functions::linearProbability(constants::freezeConstant))) {
        if (this->displayMessages) {
            std::cout << attacker->getName() << " is too frozen to take his turn!\n";
        }
        loseTurn = true;
    }
    else if ((attacker->getStatusChill()) && (core_functions::linearProbability(constants::chillConstant))) {
            if (this->displayMessages) {
                std::cout << attacker->getName() << " is too chilled to take his turn!\n";
            }
        loseTurn = true;
    }
    if (loseTurn) {
        if (this->playerTurn) {
            this->playerTurn = false;
        }
        else {
            this->playerTurn = true;
        }
        this->calculateStatusEffectChanges(*attacker, *defender, Ability("nothing"));
        this->startTurn();
    }
    else {
        if (this->playerTurn) {
            // do nothing since wait for input
        }
        else {
            Battle currentBattle = Battle(this->player, this->enemy, this->playerTurn);
            this->attack(this->enemy.chooseBattleAbility(currentBattle, this->player.getLevel() / 25 + 1));
        }
    }
}

// battle turn given the name or ability used => assume no pets
void Battle::attack(std::string abilityName) { // this one just forwards to the next one
    bool abilityNameNotFound = true;
    std::vector<std::string> abilityNameParsed{ core_functions::parseString(abilityName, " ") };
    if (abilityNameParsed.at(0).compare("item") == 0) {
        this->consume(abilityName);
        return;
    }
    if (this->playerTurn) {
        for (size_t i = 0; i < this->player.getBattleAbilities().size(); i++) {
            if (this->player.getBattleAbilities().at(i).getName().compare(abilityName) == 0) {
                this->attack(this->player.getBattleAbilities().at(i));
                abilityNameNotFound = false;
                break;
            }
        }
    }
    else {
        for (size_t i = 0; i < this->enemy.getBattleAbilities().size(); i++) {
            if (this->enemy.getBattleAbilities().at(i).getName().compare(abilityName) == 0) {
                this->attack(this->enemy.getBattleAbilities().at(i));
                abilityNameNotFound = false;
                break;
            }
        }
    }
    if (abilityNameNotFound) {
        std::cout << "ERROR: Ability name " << abilityName << " not found in unit battle abilities.";
    }
}
void Battle::consume(std::string abilityName) { // player consume item
    std::vector<std::string> abilityNameParsed{ core_functions::parseString(abilityName, "=") };
    if (abilityNameParsed.size() != 2) {
        std::cout << "ERROR: abilityName " << abilityName << "invalid.\n";
        return;
    }
    if (!core_functions::isPositiveInteger(abilityNameParsed.at(1))) {
        std::cout << "ERROR: " << abilityNameParsed.at(1) << " is not an index.\n";
        return;
    }
    size_t itemIndex{ static_cast<size_t>(stoul(abilityNameParsed.at(1))) };
    if (itemIndex > this->player.getInventory().size() - 1) {
        std::cout << "ERROR: item index " << std::to_string(itemIndex) << " out of range.\n";
        return;
    }
    if (!this->player.getInventory().at(itemIndex).isConsumable()) {
        std::cout << "ERROR: Item consumed is not consumable.\n";
        return;
    }
    this->calculateItemStatusEffectChanges(this->player.getInventory().at(itemIndex));
    this->player.useItem(itemIndex);
    this->playerTurn = false;
    if ((!this->player.getStatusAlive()) || (!this->enemy.getStatusAlive())) { // someone dies
        this->battleOver = true;
    }
    else { // the show must go on
        if (!this->battleOver) {
            this->startTurn(); // next turn
        }
    }
}
void Battle::attack(Ability abilityUsed) { // this one has all the calculations
    Unit *attacker;
    Unit *defender;
    Unit attackerStats{};
    Unit defenderStats{};
    if (this->playerTurn) {
        attacker = &this->player;
        defender = &this->enemy;
        attackerStats.initializeBattleStats(this->player);
        defenderStats.initializeBattleStats(this->enemy);
        this->playerTurn = false;
    }
    else {
        attacker = &this->enemy;
        defender = &this->player;
        attackerStats.initializeBattleStats(this->enemy);
        defenderStats.initializeBattleStats(this->player);
        this->playerTurn = true;
    }
    if (this->displayMessages) {
        std::cout << attacker->getName() << " used " << abilityUsed.getName() << ":\n";
        core_functions::pauseProgram(constants::shortPauseTime);
    }
    if (!abilityUsed.isNoneDamage()) {
        int damageInflicted{ damageCalculator(attackerStats, defenderStats, abilityUsed) };
        defender->takeDamage(damageInflicted);
    }
    attacker->takeDamage(selfDamageCalculator(*attacker, *defender, abilityUsed));
    calculateStatusEffectChanges(*attacker, *defender, abilityUsed); // basic ones
    if (this->playerTurn) {
        calculatePlayerItemStatusEffectChanges(abilityUsed);
    }

    if (abilityUsed.getFlee()) {
        // NOTE: use attacker's own dexterity (instead of defender) when fleeing
        if (core_functions::sigmoidProbability(constants::defaultBaseHitProbability,
            constants::defaultBaseCenterProbability, attacker->getDexterity() -
            attacker->getDexterity() * abilityUsed.getDexterityMultiplier())) {
            if (this->displayMessages) {
                std::cout << attacker->getName() << " fled the battle.\n";
            }
            this->battleOver = true;
        }
        else {
            if (this->displayMessages) {
                std::cout << attacker->getName() << " failed to flee the battle.\n";
            }
        }
    }

    if ((!this->player.getStatusAlive()) || (!this->enemy.getStatusAlive())) { // someone dies
        this->battleOver = true;
    }
    else { // the show must go on
        if (!this->battleOver) {
            this->startTurn(); // next turn
        }
    }
}

// Calculates damage of a battle given the two units and multiplier information
int Battle::damageCalculator(Unit attacker, Unit defender, Ability abilityUsed) {
    int damage{};
    if (core_functions::sigmoidProbability(constants::defaultBaseHitProbability,
        constants::defaultBaseCenterProbability, defender.getDexterity() -
        attacker.getDexterity() * abilityUsed.getDexterityMultiplier())) {
        // a hit so calculate damage
        double effectiveDef = defender.getDefense() * std::max(0.0, (100.0 - attacker.getPiercing()
                * abilityUsed.getPiercingMultiplier()) / 100.0);
        double effectiveRes = defender.getResist() * std::max(0.0, (100.0 - attacker.getPenetration()
                * abilityUsed.getPenetrationMultiplier()) / 100.0);
        // Decrease defense / resistance if infected (no immune system)
        if (defender.getStatusDisease()) {
            double diseaseMultiplier{ core_functions::randomDouble(constants::diseaseConstant) };
            if (this->displayMessages) {
                std::cout << defender.getName() << " disease has lowered his his defense and resistance by " << std::to_string(std::round(diseaseMultiplier)) << "%!\n";
            }
            effectiveDef *= (1 - diseaseMultiplier);
            effectiveRes *= (1 - diseaseMultiplier);
        }
        if (defender.getStatusInfect()) {
            double infectMultiplier{ core_functions::randomDouble(constants::infectConstant) };
            if (this->displayMessages) {
                std::cout << defender.getName() << " infection has lowered his his defense and resistance by " << std::to_string(std::round(infectMultiplier)) << "%!\n";
            }
            effectiveDef *= (1 - infectMultiplier);
            effectiveRes *= (1 - infectMultiplier);
        }
        // Calculate effective attack and magic from unit stat and ability multiplier
        double effectiveAttack{ attacker.getAttack() * abilityUsed.getAttackMultiplier() };
        double effectiveMagic{ attacker.getMagic() * abilityUsed.getMagicMultiplier() };
        // Add attack / magic for total attacker power and color multiplier (if unit color matches ability color)
        double initialDamage{ (effectiveAttack + effectiveMagic) * attacker.abilityColorOffensiveMultiplier(abilityUsed) };
        // Subtract effective defenses/resists based on damage type and ignore if < 0
        // NOTE: if ability is "none" damage but still has damage then it can't be defended against !!
        if (abilityUsed.isPhysicalDamage()) {
            initialDamage = std::max(0.0, initialDamage - effectiveDef);
        }
        else if (abilityUsed.isMagicDamage()) {
            initialDamage = std::max(0.0, initialDamage - effectiveRes);
        }
        else if (abilityUsed.isMixedDamage()) {
            initialDamage = std::max(0.0, initialDamage - effectiveDef - effectiveRes);
        }
        // Damage mitigation/expansion based on ability color and defender color
        damage = static_cast<int>(std::round(initialDamage * defender.abilityColorDefensiveMultiplier(abilityUsed)));
        if (abilityUsed.isPhysicalDamage()) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " dealt " << damage << " physical damage!\n";
            }
        }
        else if (abilityUsed.isMagicDamage()) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " dealt " << damage << " magic damage!\n";
            }
        }
        else if (abilityUsed.isMixedDamage()) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " dealt " << damage << " mixed damage!\n";
            }
        }
        else if ((abilityUsed.isNoneDamage()) && (damage > 0)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " dealt " << damage << " none (??) damage!\n";
            }
        }
    }
    else {
        if (this->displayMessages) {
            std::cout << attacker.getName() << " missed!\n";
        }
        damage = 0;
    }
    return damage;
}

// Calculates self-inflicted damage
int Battle::selfDamageCalculator(Unit attacker, Unit defender, Ability abilityUsed) {
    int damage{0};
    int tempDamage{};
    
    if (attacker.getStatusHemorrhage()) {
        tempDamage = std::max(1, static_cast<int>(std::round(constants::hemorrhageDoT * attacker.getCurrHealth())));
        if (this->displayMessages) {
            std::cout << attacker.getName() << " took " << tempDamage << " damage from hemorrhaging.\n";
        }
        damage += tempDamage;
    }
    if (attacker.getStatusBleed()) {
        tempDamage = std::max(1, static_cast<int>(std::round(constants::bleedDoT * attacker.getCurrHealth())));
        if (this->displayMessages) {
            std::cout << attacker.getName() << " took " << tempDamage << " damage from bleeding.\n";
        }
        damage += tempDamage;
    }

    if (attacker.getStatusDrowned()) {
        tempDamage = std::max(1, static_cast<int>(std::round(constants::drownedDoT * attacker.getMaxHealth())));
        if (this->displayMessages) {
            std::cout << attacker.getName() << " drowned and lost " << tempDamage << " health.\n";
        }
        damage += tempDamage;
    }
    if (attacker.getStatusDrowning()) {
        tempDamage = std::max(1, static_cast<int>(std::round(constants::drowningDoT * attacker.getMaxHealth())));
        if (this->displayMessages) {
            std::cout << attacker.getName() << " is drowning and lost " << tempDamage << " health.\n";
        }
        damage += tempDamage;
    }

    if (attacker.getStatusChar()) {
        tempDamage = std::max(1, static_cast<int>(std::round(constants::charDoT * attacker.getMaxHealth())));
        if (this->displayMessages) {
            std::cout << attacker.getName() << " took " << tempDamage << " damage from his charred flesh.\n";
        }
        damage += tempDamage;
    }
    if (attacker.getStatusBurn()) {
        tempDamage = std::max(1, static_cast<int>(std::round(constants::burnDoT * attacker.getMaxHealth())));
        if (this->displayMessages) {
            std::cout << attacker.getName() << " took " << tempDamage << " damage from his burns.\n";
        }
        damage += tempDamage;
    }

    if (attacker.getStatusDecay()) {
        tempDamage = std::max(1, static_cast<int>(std::round(constants::decayDoT * attacker.getMaxHealth())));
        if (this->displayMessages) {
            std::cout << attacker.getName() << " decayed " << tempDamage << " health.\n";
        }
        damage += tempDamage;
    }
    if (attacker.getStatusRot()) {
        tempDamage = std::max(1, static_cast<int>(std::round(constants::rotDoT * attacker.getMaxHealth())));
        if (this->displayMessages) {
            std::cout << attacker.getName() << " rot " << tempDamage << " health.\n";
        }
        damage += tempDamage;
    }

    if (attacker.getStatusRadioactive()) {
        tempDamage = std::max(1, static_cast<int>(std::round(constants::radioactiveDoT * attacker.getTurnsUnstable() * attacker.getMaxHealth())));
        if (this->displayMessages) {
            std::cout << attacker.getName() << "'s radioactivity caused " << tempDamage << " damage.\n";
        }
        damage += tempDamage;
        attacker.addTurnsUnstable(1);
    }
    if (attacker.getStatusUnstable()) {
        tempDamage = std::max(1, static_cast<int>(std::round(constants::unstableDoT * attacker.getTurnsUnstable() * attacker.getMaxHealth())));
        if (this->displayMessages) {
            std::cout << attacker.getName() << "'s nuclear instability caused " << tempDamage << " damage.\n";
        }
        damage += tempDamage;
        attacker.addTurnsUnstable(1);
    }

    if (abilityUsed.getRestoreHealth() > 0) {
        if (this->displayMessages) {
            std::cout << attacker.getName() << " restored " << abilityUsed.getRestoreHealth() << " health!\n";
        }
        damage -= abilityUsed.getRestoreHealth();
    }

    return damage;
}

// Calculates status effect changes
void Battle::calculateStatusEffectChanges(Unit &attacker, Unit &defender, Ability abilityUsed) {
    double sigmoidInput = defender.getDexterity() - attacker.getDexterity() * abilityUsed.getDexterityMultiplier();

    // attacker status effect removals / small ones leading to big ones
    if (attacker.getStatusHemorrhage()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer hemorrhaging!\n";
            }
            attacker.setStatusHemorrhage(false);
            attacker.setStatusBleed(true);
        }
    }
    else if (attacker.getStatusBleed()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer bleeding!\n";
            }
            attacker.setStatusBleed(false);
        }
        else if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, -sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " bleeding has led to hemorrhaging!\n";
            }
            attacker.setStatusBleed(false);
            attacker.setStatusHemorrhage(true);
        }
    }
    if (attacker.getStatusWither()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer withered!\n";
            }
            attacker.setStatusWither(false);
            attacker.setStatusWilt(true);
        }
    }
    else if (attacker.getStatusWilt()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer wilted!\n";
            }
            attacker.setStatusWilt(false);
        }
        else if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, -sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " wilt has led to wither!\n";
            }
            attacker.setStatusWilt(false);
            attacker.setStatusWither(true);
        }
    }
    if (attacker.getStatusDrowned()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer drowned!\n";
            }
            attacker.setStatusDrowned(false);
            attacker.setStatusDrowning(true);
        }
    }
    else if (attacker.getStatusDrowning()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer drowning!\n";
            }
            attacker.setStatusDrowning(false);
        }
        // More likely for drowning to lead to drowned
        else if (core_functions::sigmoidProbability(2 * constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, -sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " has drowned!\n";
            }
            attacker.setStatusDrowning(false);
            attacker.setStatusDrowned(true);
        }
    }
    if (attacker.getStatusChar()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer charred!\n";
            }
            attacker.setStatusChar(false);
            attacker.setStatusBurn(true);
        }
    }
    else if (attacker.getStatusBurn()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer burning!\n";
            }
            attacker.setStatusBurn(false);
        }
        else if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, -sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is charred from his burning!\n";
            }
            attacker.setStatusBurn(false);
            attacker.setStatusChar(true);
        }
    }
    if (attacker.getStatusDecay()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer decayed!\n";
            }
            attacker.setStatusDecay(false);
            attacker.setStatusRot(true);
        }
    }
    else if (attacker.getStatusRot()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer rotting!\n";
            }
            attacker.setStatusRot(false);
        }
        else if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, -sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " rotting has led to decay!\n";
            }
            attacker.setStatusRot(false);
            attacker.setStatusDecay(true);
        }
    }
    if (attacker.getStatusFrozen()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer frozen!\n";
            }
            attacker.setStatusFrozen(false);
            attacker.setStatusChill(true);
        }
    }
    else if (attacker.getStatusChill()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer chilling!\n";
            }
            attacker.setStatusChill(false);
        }
        else if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, -sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " froze from his chilling!\n";
            }
            attacker.setStatusChill(false);
            attacker.setStatusFrozen(true);
        }
    }
    if (attacker.getStatusDisease()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer diseased!\n";
            }
            attacker.setStatusDisease(false);
            attacker.setStatusInfect(true);
        }
    }
    else if (attacker.getStatusInfect()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer infected!\n";
            }
            attacker.setStatusInfect(false);
        }
        else if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, -sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << "'s infection has led to disease!\n";
            }
            attacker.setStatusInfect(false);
            attacker.setStatusDisease(true);
        }
    }
    if (attacker.getStatusFell()) {
        attacker.subtractTurnsShaken(2);
        if (attacker.getTurnsShaken() <= 0) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " got up!\n";
            }
            attacker.setStatusFell(false);
            attacker.setStatusShaken(false);
            attacker.resetTurnsShaken();
        }
    }
    else if (attacker.getStatusShaken()) {
        attacker.subtractTurnsShaken(3);
        if (attacker.getTurnsShaken() <= 0) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " found his balance!\n";
            }
            attacker.setStatusShaken(false);
            attacker.resetTurnsShaken();
        }
        else if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, -sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " fell over!\n";
            }
            attacker.setStatusShaken(false);
            attacker.setStatusFell(true);
            attacker.addTurnsShaken(2);
        }
    }
    if (attacker.getStatusParalyze()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer paralyzed!\n";
            }
            attacker.setStatusParalyze(false);
            attacker.setStatusShock(true);
        }
    }
    else if (attacker.getStatusShock()) {
        if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is no longer shocked!\n";
            }
            attacker.setStatusShock(false);
        }
        else if (core_functions::sigmoidProbability(constants::baseStatusRemovalProbability, constants::centerStatusRemovalProbability, -sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is paralyzed from his shock!\n";
            }
            attacker.setStatusShock(false);
            attacker.setStatusParalyze(true);
        }
    }
    if (attacker.getStatusUnstable()) {
        // Less likely for nuclear instability to change
        if (core_functions::sigmoidProbability(static_cast<int>(std::round(0.5 *constants::baseStatusRemovalProbability)),
            constants::centerStatusRemovalProbability, sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << "'s nuclei are no longer unstable!\n";
            }
            attacker.setStatusUnstable(false);
            attacker.resetTurnsUnstable();
        }
        else if (core_functions::sigmoidProbability(static_cast<int>(std::round(0.5 * constants::baseStatusRemovalProbability)),
            constants::centerStatusRemovalProbability, -sigmoidInput)) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << "'s unstable nuclei have become radioactive!\n";
            }
            attacker.setStatusUnstable(false);
            attacker.setStatusRadioactive(true);
        }
    }

    // Attacker stat buffs
    if (abilityUsed.getGrow()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " grew!\n";
            }
            attacker.setStatusGrow(true);
        }
    }
    if (abilityUsed.getEnlarge()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is greatly enlarged!\n";
            }
            attacker.setStatusEnlarge(true);
        }
    }
    if (abilityUsed.getStrength()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " has increased strength!\n";
            }
            attacker.setStatusStrength(true);
        }
    }
    if (abilityUsed.getBeserk()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is beserk!\n";
            }
            attacker.setStatusBeserk(true);
        }
    }
    if (abilityUsed.getCogent()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is cogent!\n";
            }
            attacker.setStatusCogent(true);
        }
    }
    if (abilityUsed.getPotent()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is greatly potent!\n";
            }
            attacker.setStatusPotent(true);
        }
    }
    if (abilityUsed.getDefend()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is defending!\n";
            }
            attacker.setStatusDefend(true);
        }
    }
    if (abilityUsed.getBulwark()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is a bulwark!\n";
            }
            attacker.setStatusBulwark(true);
        }
    }
    if (abilityUsed.getResolve()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " has resolve!\n";
            }
            attacker.setStatusResolve(true);
        }
    }
    if (abilityUsed.getDauntless()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is dauntless!\n";
            }
            attacker.setStatusDauntless(true);
        }
    }
    if (abilityUsed.getSwiftness()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " has increased swiftness!\n";
            }
            attacker.setStatusSwiftness(true);
        }
    }
    if (abilityUsed.getDeftness()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is deft!\n";
            }
            attacker.setStatusDeftness(true);
        }
    }

    // Defender stat nerfs
    if (abilityUsed.getWeak()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is weak!\n";
            }
            defender.setStatusWeak(true);
        }
    }
    if (abilityUsed.getFeeble()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is feeble!\n";
            }
            defender.setStatusFeeble(true);
        }
    }
    if (abilityUsed.getInept()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is inept!\n";
            }
            defender.setStatusInept(true);
        }
    }
    if (abilityUsed.getImpotent()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is impotent!\n";
            }
            defender.setStatusImpotent(true);
        }
    }
    if (abilityUsed.getBreak()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << "'s defenses are broken!\n";
            }
            defender.setStatusBreak(true);
        }
    }
    if (abilityUsed.getSmash()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << "'s defenses are smashed!\n";
            }
            defender.setStatusSmash(true);
        }
    }
    if (abilityUsed.getOutwill()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is outwilled!\n";
            }
            defender.setStatusOutwill(true);
        }
    }
    if (abilityUsed.getShatter()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " will is shattered!\n";
            }
            defender.setStatusShatter(true);
        }
    }
    if (abilityUsed.getSlowness()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is slow!\n";
            }
            defender.setStatusSlow(true);
        }
    }
    if (abilityUsed.getLethargy()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is lethargic!\n";
            }
            defender.setStatusLethargic(true);
        }
    }

    // Defender status effect adders
    if (abilityUsed.getBleed()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is bleeding!\n";
            }
            defender.setStatusBleed(true);
        }
    }
    if (abilityUsed.getHemorrhage()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is hemorrhaging!\n";
            }
            defender.setStatusHemorrhage(true);
        }
    }
    if (abilityUsed.getWilt()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is wilting!\n";
            }
            defender.setStatusWilt(true);
        }
    }
    if (abilityUsed.getWither()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is withered!\n";
            }
            defender.setStatusWither(true);
        }
    }
    if (abilityUsed.getDrowning()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is drowning!\n";
            }
            defender.setStatusDrowning(true);
        }
    }
    if (abilityUsed.getDrowned()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is drowned!\n";
            }
            defender.setStatusDrowned(true);
        }
    }
    if (abilityUsed.getBurnt()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is burning!\n";
            }
            defender.setStatusBurn(true);
        }
    }
    if (abilityUsed.getCharred()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is charred!\n";
            }
            defender.setStatusChar(true);
        }
    }
    if (abilityUsed.getRot()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is rotting!\n";
            }
            defender.setStatusRot(true);
        }
    }
    if (abilityUsed.getDecay()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is decayed!\n";
            }
            defender.setStatusDecay(true);
        }
    }
    if (abilityUsed.getChill()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is chilling!\n";
            }
            defender.setStatusChill(true);
        }
    }
    if (abilityUsed.getFrozen()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is frozen!\n";
            }
            defender.setStatusFrozen(true);
        }
    }
    if (abilityUsed.getInfect()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is infected!\n";
            }
            defender.setStatusInfect(true);
        }
    }
    if (abilityUsed.getDisease()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is diseased!\n";
            }
            defender.setStatusDisease(true);
        }
    }
    if (abilityUsed.getShaken()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is shaking!\n";
            }
            defender.setStatusShaken(true);
            defender.addTurnsShaken(5);
        }
    }
    if (abilityUsed.getFallen()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " fell!\n";
            }
            defender.setStatusFell(true);
            defender.addTurnsShaken(9);
        }
    }
    if (abilityUsed.getShocked()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is shocked!\n";
            }
            defender.setStatusShock(true);
        }
    }
    if (abilityUsed.getParalyzed()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is paralyzed!\n";
            }
            defender.setStatusParalyze(true);
        }
    }
    if (abilityUsed.getUnstable()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << "'s nuclei are unstable!\n";
            }
            defender.setStatusUnstable(true);
        }
    }
    if (abilityUsed.getRadioactive()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << " is radioactive!\n";
            }
            defender.setStatusRadioactive(true);
        }
    }
    if (abilityUsed.getObscured()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << "Events are obscured from " << defender.getName() << "!\n";
            }
            defender.setStatusObscure(true);
        }
    }
    if (abilityUsed.getHidden()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << "Events are hidden from " << defender.getName() << "!\n";
            }
            defender.setStatusHide(true);
        }
    }
    if (abilityUsed.getBright()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << "'s future is brightened!\n";
            }
            defender.setStatusBright(true);
        }
    }
    if (abilityUsed.getIlluminate()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << defender.getName() << "'s future is illuminated!\n";
            }
            defender.setStatusIlluminate(true);
        }
    }

    // Attacker status effect selfadders
    if (abilityUsed.getSelfBleed()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is bleeding!\n";
            }
            attacker.setStatusBleed(true);
        }
    }
    if (abilityUsed.getSelfHemorrhage()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is hemorrhaging!\n";
            }
            attacker.setStatusHemorrhage(true);
        }
    }
    if (abilityUsed.getSelfWilt()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is wilting!\n";
            }
            attacker.setStatusWilt(true);
        }
    }
    if (abilityUsed.getSelfWither()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is withered!\n";
            }
            attacker.setStatusWither(true);
        }
    }
    if (abilityUsed.getSelfDrowning()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is drowning!\n";
            }
            attacker.setStatusDrowning(true);
        }
    }
    if (abilityUsed.getSelfDrowned()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is drowned!\n";
            }
            attacker.setStatusDrowned(true);
        }
    }
    if (abilityUsed.getSelfBurnt()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is burning!\n";
            }
            attacker.setStatusBurn(true);
        }
    }
    if (abilityUsed.getSelfCharred()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is charred!\n";
            }
            attacker.setStatusChar(true);
        }
    }
    if (abilityUsed.getSelfRot()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is rotting!\n";
            }
            attacker.setStatusRot(true);
        }
    }
    if (abilityUsed.getSelfDecay()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is decayed!\n";
            }
            attacker.setStatusDecay(true);
        }
    }
    if (abilityUsed.getSelfChill()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is chilling!\n";
            }
            attacker.setStatusChill(true);
        }
    }
    if (abilityUsed.getSelfFrozen()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is frozen!\n";
            }
            attacker.setStatusFrozen(true);
        }
    }
    if (abilityUsed.getSelfInfect()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is infected!\n";
            }
            attacker.setStatusInfect(true);
        }
    }
    if (abilityUsed.getSelfDisease()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is diseased!\n";
            }
            attacker.setStatusDisease(true);
        }
    }
    if (abilityUsed.getSelfShaken()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is shaking!\n";
            }
            attacker.setStatusShaken(true);
            attacker.addTurnsShaken(5);
        }
    }
    if (abilityUsed.getSelfFallen()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " fell!\n";
            }
            attacker.setStatusFell(true);
            attacker.addTurnsShaken(9);
        }
    }
    if (abilityUsed.getSelfShocked()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is shocked!\n";
            }
            attacker.setStatusShock(true);
        }
    }
    if (abilityUsed.getSelfParalyzed()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is paralyzed!\n";
            }
            attacker.setStatusParalyze(true);
        }
    }
    if (abilityUsed.getSelfUnstable()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << "'s nuclei are unstable!\n";
            }
            attacker.setStatusUnstable(true);
        }
    }
    if (abilityUsed.getSelfRadioactive()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << " is radioactive!\n";
            }
            attacker.setStatusRadioactive(true);
        }
    }
    if (abilityUsed.getSelfObscured()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << "Events are obscured from " << attacker.getName() << "!\n";
            }
            attacker.setStatusObscure(true);
        }
    }
    if (abilityUsed.getSelfHidden()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << "Events are hidden from " << attacker.getName() << "!\n";
            }
            attacker.setStatusHide(true);
        }
    }
    if (abilityUsed.getSelfBright()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << "'f future is brightened!\n";
            }
            attacker.setStatusBright(true);
        }
    }
    if (abilityUsed.getSelfIlluminate()) {
        if (core_functions::linearProbability(abilityUsed.getEffectProbability())) {
            if (this->displayMessages) {
                std::cout << attacker.getName() << "'s future is illuminated!\n";
            }
            attacker.setStatusIlluminate(true);
        }
    }
}

// Player item status effect changes (only on player turn)
void Battle::calculatePlayerItemStatusEffectChanges(Ability abilityUsed) {
    this->calculateItemStatusEffectChanges(this->player.getWeapon());
    this->calculateItemStatusEffectChanges(this->player.getOffhand());
    this->calculateItemStatusEffectChanges(this->player.getTwohand());
    this->calculateItemStatusEffectChanges(this->player.getHeadgear());
    this->calculateItemStatusEffectChanges(this->player.getChestgear());
    this->calculateItemStatusEffectChanges(this->player.getLeggear());
    this->calculateItemStatusEffectChanges(this->player.getFootgear());
    this->calculateItemStatusEffectChanges(this->player.getAccessory1());
    this->calculateItemStatusEffectChanges(this->player.getAccessory2());
    this->calculateItemStatusEffectChanges(this->player.getAccessory3());
    this->calculateItemStatusEffectChanges(this->player.getAccessory4());
}
void Battle::calculateItemStatusEffectChanges(Item it) {
    // Stat buffs
    if (it.getGrow()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusGrow(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " grow!\n";
            }
        }
    }
    if (it.getEnlarge()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusEnlarge(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " enlarge!\n";
            }
        }
    }
    if (it.getStrength()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusStrength(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " strength!\n";
            }
        }
    }
    if (it.getBeserk()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusBeserk(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " beserk!\n";
            }
        }
    }
    if (it.getCogent()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusCogent(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " cogent!\n";
            }
        }
    }
    if (it.getPotent()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusPotent(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " potent!\n";
            }
        }
    }
    if (it.getDefend()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusDefend(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " defend!\n";
            }
        }
    }
    if (it.getBulwark()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusBulwark(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " bulwark!\n";
            }
        }
    }
    if (it.getResolve()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusResolve(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " resolve!\n";
            }
        }
    }
    if (it.getDauntless()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusDauntless(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " dauntless!\n";
            }
        }
    }
    if (it.getSwiftness()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusSwiftness(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " swiftness!\n";
            }
        }
    }
    if (it.getDeftness()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusDeftness(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->player.getName() << " deftness!\n";
            }
        }
    }
    // Stat debuffs
    if (it.getWeak()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusWeak(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->enemy.getName() << " weakness!\n";
            }
        }
    }
    if (it.getFeeble()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusFeeble(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->enemy.getName() << " weakness!\n";
            }
        }
    }
    if (it.getInept()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusInept(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->enemy.getName() << " inept!\n";
            }
        }
    }
    if (it.getImpotent()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusImpotent(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->enemy.getName() << " impotent!\n";
            }
        }
    }
    if (it.getBreak()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusBreak(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " broke " << this->enemy.getName() << "'s defense!\n";
            }
        }
    }
    if (it.getSmash()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusSmash(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " smashed " << this->enemy.getName() << "'s defense!\n";
            }
        }
    }
    if (it.getOutwill()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusOutwill(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->enemy.getName() << " outwilled!\n";
            }
        }
    }
    if (it.getShatter()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusShatter(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " shattered " << this->enemy.getName() << "'s will!\n";
            }
        }
    }
    if (it.getSlowness()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusSlow(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->enemy.getName() << " slow!\n";
            }
        }
    }
    if (it.getLethargy()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusLethargic(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->enemy.getName() << " lethargic!\n";
            }
        }
    }
    // Color debuffs
    if (it.getBleed()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusBleed(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->enemy.getName() << " bleed!\n";
            }
        }
    }
    if (it.getHemorrhage()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusHemorrhage(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->enemy.getName() << " hemorrhage!\n";
            }
        }
    }
    if (it.getWilt()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusWilt(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->enemy.getName() << " wilt!\n";
            }
        }
    }
    if (it.getWither()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusWither(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->enemy.getName() << " wither!\n";
            }
        }
    }
    if (it.getDrowning()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusDrowning(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->enemy.getName() << " drowning!\n";
            }
        }
    }
    if (it.getDrowned()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusDrowned(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " drowned " << this->enemy.getName() << "!\n";
            }
        }
    }
    if (it.getBurnt()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusBurn(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " burnt " << this->enemy.getName() << "!\n";
            }
        }
    }
    if (it.getCharred()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusChar(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " charred " << this->enemy.getName() << "!\n";
            }
        }
    }
    if (it.getRot()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusRot(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->enemy.getName() << " rot!\n";
            }
        }
    }
    if (it.getDecay()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusDecay(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->enemy.getName() << " decay!\n";
            }
        }
    }
    if (it.getChill()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusChill(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " chilled " << this->enemy.getName() << "!\n";
            }
        }
    }
    if (it.getFrozen()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusFrozen(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " froze " << this->enemy.getName() << "!\n";
            }
        }
    }
    if (it.getInfect()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusInfect(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->enemy.getName() << " an infection!\n";
            }
        }
    }
    if (it.getDisease()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusDisease(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " gave " << this->enemy.getName() << " disease!\n";
            }
        }
    }
    if (it.getShaken()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusShaken(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " shook " << this->enemy.getName() << "!\n";
            }
        }
    }
    if (it.getFallen()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusFell(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->enemy.getName() << " fall!\n";
            }
        }
    }
    if (it.getShocked()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusShock(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " shocked " << this->enemy.getName() << "!\n";
            }
        }
    }
    if (it.getParalyzed()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusParalyze(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " paralyzed " << this->enemy.getName() << "!\n";
            }
        }
    }
    if (it.getUnstable()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusUnstable(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->enemy.getName() << "'s nuclei unstable!\n";
            }
        }
    }
    if (it.getRadioactive()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusRadioactive(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->enemy.getName() << " radioactive!\n";
            }
        }
    }
    if (it.getObscured()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusObscure(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " obscured events from " << this->enemy.getName() << "!\n";
            }
        }
    }
    if (it.getHidden()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusHide(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " hid events from " << this->enemy.getName() << "!\n";
            }
        }
    }
    if (it.getBright()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusBright(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " brightened " << this->enemy.getName() << "'s future!\n";
            }
        }
    }
    if (it.getIlluminate()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->enemy.setStatusIlluminate(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " illuminated " << this->enemy.getName() << "'s future!\n";
            }
        }
    }
    // Color cures
    if (it.getCureBleed()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusBleed(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s bleeding!\n";
            }
        }
    }
    if (it.getCureHemorrhage()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusHemorrhage(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s hemorrhage!\n";
            }
        }
    }
    if (it.getCureWilt()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusWilt(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s wilt!\n";
            }
        }
    }
    if (it.getCureWither()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusWither(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s wither!\n";
            }
        }
    }
    if (it.getCureDrowning()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusDrowning(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s drowning!\n";
            }
        }
    }
    if (it.getCureDrowned()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusDrowned(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s drowned!\n";
            }
        }
    }
    if (it.getCureBurnt()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusBurn(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s burns!\n";
            }
        }
    }
    if (it.getCureCharred()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusChar(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s charred!\n";
            }
        }
    }
    if (it.getCureRot()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusRot(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s rot!\n";
            }
        }
    }
    if (it.getCureDecay()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusDecay(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s decay!\n";
            }
        }
    }
    if (it.getCureChill()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusChill(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s chills!\n";
            }
        }
    }
    if (it.getCureFrozen()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusFrozen(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " thawed " << this->player.getName() << "!\n";
            }
        }
    }
    if (it.getCureInfect()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusInfect(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s infection!\n";
            }
        }
    }
    if (it.getCureDisease()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusDisease(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s disease!\n";
            }
        }
    }
    if (it.getCureShaken()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusShaken(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " stopped " << this->player.getName() << "'s shaking!\n";
            }
        }
    }
    if (it.getCureFallen()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusFell(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " helped " << this->player.getName() << " up!\n";
            }
        }
    }
    if (it.getCureShocked()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusShock(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s shock!\n";
            }
        }
    }
    if (it.getCureParalyzed()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusParalyze(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s paralysis!\n";
            }
        }
    }
    if (it.getCureUnstable()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusUnstable(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s nuclear instability!\n";
            }
        }
    }
    if (it.getCureRadioactive()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusRadioactive(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s radioactivity!\n";
            }
        }
    }
    if (it.getCureObscured()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusObscure(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s obscured!\n";
            }
        }
    }
    if (it.getCureHidden()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusHide(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s hidden!\n";
            }
        }
    }
    if (it.getCureBright()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusBright(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s brightened!\n";
            }
        }
    }
    if (it.getCureIlluminate()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusIlluminate(false);
            if (this->displayMessages) {
                std::cout << it.getName() << " cured " << this->player.getName() << "'s illuminated!\n";
            }
        }
    }
    // Color selfs
    if (it.getSelfBleed()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusBleed(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to bleed!\n";
            }
        }
    }
    if (it.getSelfHemorrhage()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusHemorrhage(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to hemorrhage!\n";
            }
        }
    }
    if (it.getSelfWilt()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusWilt(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to wilt!\n";
            }
        }
    }
    if (it.getSelfWither()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusWither(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to wither!\n";
            }
        }
    }
    if (it.getSelfDrowning()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusDrowning(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to be drowning!\n";
            }
        }
    }
    if (it.getSelfDrowned()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusDrowned(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to drown!\n";
            }
        }
    }
    if (it.getSelfBurnt()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusBurn(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to burn!\n";
            }
        }
    }
    if (it.getSelfCharred()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusChar(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to char!\n";
            }
        }
    }
    if (it.getSelfRot()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusRot(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to rot!\n";
            }
        }
    }
    if (it.getSelfDecay()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusDecay(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to decay!\n";
            }
        }
    }
    if (it.getSelfChill()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusChill(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to chill!\n";
            }
        }
    }
    if (it.getSelfFrozen()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusFrozen(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to freeze!\n";
            }
        }
    }
    if (it.getSelfInfect()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusInfect(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " an infection!\n";
            }
        }
    }
    if (it.getSelfDisease()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusDisease(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " disease!\n";
            }
        }
    }
    if (it.getSelfShaken()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusShaken(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to shake!\n";
            }
        }
    }
    if (it.getSelfFallen()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusFell(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " to fall!\n";
            }
        }
    }
    if (it.getSelfShocked()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusShock(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " shock!\n";
            }
        }
    }
    if (it.getSelfParalyzed()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusParalyze(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << " paralysis!\n";
            }
        }
    }
    if (it.getSelfUnstable()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusUnstable(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->player.getName() << "'s nuclei unstable!\n";
            }
        }
    }
    if (it.getSelfRadioactive()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusRadioactive(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " made " << this->player.getName() << " radioactivity!\n";
            }
        }
    }
    if (it.getSelfObscured()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusObscure(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused events to be obscured from " << this->player.getName() << "!\n";
            }
        }
    }
    if (it.getSelfHidden()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusHide(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused events to be hidden from " << this->player.getName() << "!\n";
            }
        }
    }
    if (it.getSelfBright()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusBright(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << "'s future to be brightened!\n";
            }
        }
    }
    if (it.getSelfIlluminate()) {
        if ((it.isConsumable()) || (core_functions::linearProbability(constants::smallProbabilityStatusEffect))) {
            this->player.setStatusIlluminate(true);
            if (this->displayMessages) {
                std::cout << it.getName() << " caused " << this->player.getName() << "'s future to be illuminated!\n";
            }
        }
    }
}

// Forward function to remove player energy
void Battle::removePlayerEnergy(int amount) {
    this->player.lowerEnergy(amount);
}

// Prints current battle information
void Battle::printBattleInfo() {
    std::cout << "\n";
    std::vector<std::string> playerInfo{};
    std::vector<std::string> enemyInfo{};
    std::string separationSpace{core_functions::stringMultiply(" ", 10)}; // 10 is arbitrary
    playerInfo.push_back(this->player.getName() + " (level " + std::to_string(this->player.getLevel()) + ")");
    enemyInfo.push_back(this->enemy.getName() + " (level " + std::to_string(this->enemy.getLevel()) + ")");
    std::vector<std::string> barQuantities{};
    barQuantities.push_back("Health: " + std::to_string(this->player.getCurrHealth()) + "/" + std::to_string(this->player.getMaxHealth()) + " ");
    barQuantities.push_back("Health: " + std::to_string(this->enemy.getCurrHealth()) + "/" + std::to_string(this->enemy.getMaxHealth()) + " ");
    barQuantities.push_back("Energy: " + std::to_string(this->player.getCurrEnergy()) + "/" + std::to_string(this->player.getMaxEnergy()) + " ");
    barQuantities.push_back("Mana:   " + std::to_string(this->player.getCurrMana()) + "/" + std::to_string(this->player.getMaxMana()) + " ");
    int largestString{ 0 }; // account for size of "Health: ###/###", etc
    // Find largest string length
    for (std::string i : barQuantities) {
        if (i.length() > largestString) {
            largestString = i.length();
        }
    }
    int barSize{ (constants::printViewSpatialSize / 2) - largestString - static_cast<int>(separationSpace.length()) };
    playerInfo.push_back(barQuantities.at(0) + core_functions::stringMultiply(" ", largestString - barQuantities.at(0).length()) +
        core_functions::makeQuantityBar(this->player.getCurrHealth(), this->player.getMaxHealth(), barSize));
    enemyInfo.push_back(barQuantities.at(1) + core_functions::stringMultiply(" ", largestString - barQuantities.at(1).length()) +
        core_functions::makeQuantityBar(this->enemy.getCurrHealth(), this->enemy.getMaxHealth(), barSize));
    playerInfo.push_back(barQuantities.at(2) + core_functions::stringMultiply(" ", largestString - barQuantities.at(2).length()) +
        core_functions::makeQuantityBar(this->player.getCurrEnergy(), this->player.getMaxEnergy(), barSize));
    if (player.getLevel() / constants::dimensionLevels > 0) {
        playerInfo.push_back(barQuantities.at(3) + core_functions::stringMultiply(" ", largestString - barQuantities.at(3).length()) +
            core_functions::makeQuantityBar(this->player.getCurrMana(), this->player.getMaxMana(), barSize));
    }
    if (this->player.getUpgradeAttention2()) {
        playerInfo.push_back("Attack:      " + std::to_string(this->player.getAttack()));
        enemyInfo.push_back("Attack:      " + std::to_string(this->enemy.getAttack()));
        playerInfo.push_back("Magic:       " + std::to_string(this->player.getMagic()));
        enemyInfo.push_back("Magic:       " + std::to_string(this->enemy.getMagic()));
        playerInfo.push_back("Defense:     " + std::to_string(this->player.getDefense()));
        enemyInfo.push_back("Defense:     " + std::to_string(this->enemy.getDefense()));
        playerInfo.push_back("Resist:      " + std::to_string(this->player.getResist()));
        enemyInfo.push_back("Resist:      " + std::to_string(this->enemy.getResist()));
        playerInfo.push_back("Piercing:    " + std::to_string(this->player.getPiercing()));
        enemyInfo.push_back("Piercing:    " + std::to_string(this->enemy.getPiercing()));
        playerInfo.push_back("Penetration: " + std::to_string(this->player.getPenetration()));
        enemyInfo.push_back("Penetration: " + std::to_string(this->enemy.getPenetration()));
        playerInfo.push_back("Dexterity:   " + std::to_string(this->player.getDexterity()));
        enemyInfo.push_back("Dexterity:   " + std::to_string(this->enemy.getDexterity()));
    }
    else if (this->player.getUpgradeAttention1()) {
        playerInfo.push_back("Attack:      " + std::to_string(this->player.getAttack()));
        playerInfo.push_back("Magic:       " + std::to_string(this->player.getMagic()));
        playerInfo.push_back("Defense:     " + std::to_string(this->player.getDefense()));
        playerInfo.push_back("Resist:      " + std::to_string(this->player.getResist()));
        playerInfo.push_back("Piercing:    " + std::to_string(this->player.getPiercing()));
        playerInfo.push_back("Penetration: " + std::to_string(this->player.getPenetration()));
        playerInfo.push_back("Dexterity:   " + std::to_string(this->player.getDexterity()));
    }
    player.getStatusEffectInfo(playerInfo);
    enemy.getStatusEffectInfo(enemyInfo);
    // Force both vectors to be the same length
    if (playerInfo.size() > enemyInfo.size()) {
        while (playerInfo.size() > enemyInfo.size()) {
            enemyInfo.push_back("");
        }
    }
    else {
        while (enemyInfo.size() > playerInfo.size()) {
            playerInfo.push_back("");
        }
    }
    int maxSize{0}; // max string lengths so I can properly line up the enemy information
    for (size_t i = 0; i < playerInfo.size(); i++) {
        if (playerInfo.at(i).size() > maxSize) {
            maxSize = playerInfo.at(i).size();
        }
    }
    // Actually print out the information
    if (playerInfo.size() == enemyInfo.size()) {
        for (size_t i = 0; i < playerInfo.size(); i++) {
            std::cout << playerInfo.at(i) + separationSpace + core_functions::stringMultiply(
                " ", maxSize - playerInfo.at(i).size()) + enemyInfo.at(i) + "\n";
        }
    }
    else {
        std::cout << "ERROR: player and enemy string vectors different sizes.\n";
    }
    std::cout << "\n";
}

// Returns the file string for saving the game
void Battle::saveGame(std::string filePath) {
    std::ofstream battleFile{ filePath, std::ios::trunc };
    battleFile << "*STARTFILE\n";
    battleFile << "playerTurn=" << this->playerTurn << "\n";
    battleFile << "battleOver=" << this->battleOver << "\n";
    battleFile << "displayMessages=" << this->displayMessages << "\n";
    battleFile << this->enemy.saveGame();
    battleFile << this->player.saveGame();
    battleFile.close();
}