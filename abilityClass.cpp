/*
abilityClass.cpp
The ability class creates ability specs for any action relevant in the interaction class (for
now just the battle class).
*/

#include <iostream>
#include "abilityClass.h"
#include "coreFunctions.h"
#include "constants.h"

Ability::Ability(std::string name, int energyCost, double attackM, double magicM, double piercingM,
    double penetrationM, double dexterityM) { // base constructor
    this->name = name;
    this->energyCost = energyCost;
    this->attackMultiplier = attackM;
    this->magicMultiplier = magicM;
    this->piercingMultiplier = piercingM;
    this->penetrationMultiplier = penetrationM;
    this->dexterityMultiplier = dexterityM;
}

// constructor from unique name; this is the ability class reference
Ability::Ability(std::string name) {
    this->name = name;
    if (this->name.compare("nothing") == 0) {
        this->foulCost = 0;
        this->setInfo(0, 0, 0, 0, 0, 0, 0, colorType::colorless, damageType::none, 0.0, 0.0);
    }

    // Flee abilities
    if (this->name.compare("floataway") == 0) {
        this->foulCost = 0;
        this->setInfo(0, 0, 0, 0, 0.5, 0, 0, colorType::colorless, damageType::none, 0.0, 0.0);
        this->fleeAttempt = true;
    }
    else if (this->name.compare("flee") == 0) {
        this->foulCost = 0;
        this->setInfo(0, 0, 0, 0, 1, 0, 0, colorType::colorless, damageType::none, 0.0, 0.0);
        this->fleeAttempt = true;
    }
    else if (this->name.compare("swimaway") == 0) {
        this->foulCost = 10;
        this->setInfo(0, 0, 0, 0, 1.3, 5, 0, colorType::colorless, damageType::none, 0.0, 0.0);
        this->fleeAttempt = true;
    }
    else if (this->name.compare("jumpaway") == 0) {
        this->foulCost = 20;
        this->setInfo(0, 0, 0, 0, 1.6, 10, 0, colorType::colorless, damageType::none, 0.0, 0.0);
        this->fleeAttempt = true;
    }
    else if (this->name.compare("flyaway") == 0) {
        this->foulCost = 40;
        this->setInfo(0, 0, 0, 0, 1.9, 15, 0, colorType::colorless, damageType::none, 0.0, 0.0);
        this->fleeAttempt = true;
    }
    else if (this->name.compare("recoil") == 0) {
        this->foulCost = 40;
        this->setInfo(0.5, 0, 0.8, 0, 0.8, 6, 0, colorType::colorless, damageType::physical, 0.0, 0.0);
        this->fleeAttempt = true;
    }

    // Weak Status Effect Causer
    if (this->name.compare("bleed") == 0) {
        this->foulCost = 10;
        this->setInfo(0, 0, 0, 0, 1, 5, 0, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeBleed = true;
    }
    else if (this->name.compare("wilt") == 0) {
        this->foulCost = 20;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeWilt = true;
    }
    else if (this->name.compare("dunk") == 0) {
        this->foulCost = 20;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::blue, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeDrowning = true;
    }
    else if (this->name.compare("burn") == 0) {
        this->foulCost = 20;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::red, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeBurnt = true;
    }
    else if (this->name.compare("rot") == 0) {
        this->foulCost = 20;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::brown, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeRot = true;
    }
    else if (this->name.compare("chill") == 0) {
        this->foulCost = 20;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::cyan, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeChill = true;
    }
    else if (this->name.compare("infect") == 0) {
        this->foulCost = 20;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::orange, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeInfect = true;
    }
    else if (this->name.compare("shake") == 0) {
        this->foulCost = 40;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::purple, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeShaken = true;
    }
    else if (this->name.compare("shock") == 0) {
        this->foulCost = 40;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::yellow, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeShocked = true;
    }
    else if (this->name.compare("destabilize") == 0) {
        this->foulCost = 40;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::magenta, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeUnstable = true;
    }
    else if (this->name.compare("obscure") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::black, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeObscure = true;
    }
    else if (this->name.compare("brighten") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::white, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeBright = true;
    }
    else if (this->name.compare("balance") == 0) {
        this->foulCost = 80;
        this->setInfo(0, 0, 0, 0, 1, 0, 5, colorType::green, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        //this->causeBalance = true;
    }

    // Strong Status Effect Causer
    if (this->name.compare("hemorrhage") == 0) {
        this->foulCost = 30;
        this->setInfo(0, 0, 0, 0, 1, 20, 0, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeBleed = true;
        this->causeHemorrhage = true;
    }
    else if (this->name.compare("wither") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeWilt = true;
        this->causeWither = true;
    }
    else if (this->name.compare("drown") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::blue, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeDrowning = true;
        this->causeDrowned = true;
    }
    else if (this->name.compare("char") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::red, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeBurnt = true;
        this->causeCharred = true;
    }
    else if (this->name.compare("decay") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::brown, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeRot = true;
        this->causeDecay = true;
    }
    else if (this->name.compare("freeze") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::cyan, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeChill = true;
        this->causeFrozen = true;
    }
    else if (this->name.compare("disease") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::orange, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeInfect = true;
        this->causeDisease = true;
    }
    else if (this->name.compare("fell") == 0) {
        this->foulCost = 120;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::purple, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeShaken = true;
        this->causeFallen = true;
    }
    else if (this->name.compare("paralyze") == 0) {
        this->foulCost = 120;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::yellow, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeShocked = true;
        this->causeParalyzed = true;
    }
    else if (this->name.compare("radiate") == 0) {
        this->foulCost = 120;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::magenta, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeUnstable = true;
        this->causeRadioactive = true;
    }
    else if (this->name.compare("hide") == 0) {
        this->foulCost = 180;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::black, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeObscure = true;
        this->causeHidden = true;
    }
    else if (this->name.compare("illumiate") == 0) {
        this->foulCost = 180;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::white, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeBright = true;
        this->causeIlluminated = true;
    }
    else if (this->name.compare("equalize") == 0) {
        this->foulCost = 240;
        this->setInfo(0, 0, 0, 0, 1, 0, 20, colorType::green, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        //this->causeBalance = true;
        // this->causeEqualize = true;
    }

    // Basic Weak Attack
    if (this->name.compare("attack") == 0) {
        this->foulCost = 0;
        this->setInfo(1, 0, 1, 0, 1, 2, 0, colorType::colorless, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBleed = true;
    }
    else if (this->name.compare("nibble") == 0) {
        this->foulCost = 10;
        this->setInfo(1.2, 0, 0.5, 0, 0.8, 3, 0, colorType::colorless, damageType::physical, 0.2, constants::smallProbabilityStatusEffect);
        this->causeBleed = true;
        this->causeInfect = true;
    }
    else if (this->name.compare("lunge") == 0) {
        this->foulCost = 10;
        this->setInfo(0.7, 0, 0.5, 0, 1.5, 3, 0, colorType::colorless, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBleed = true;
    }
    else if (this->name.compare("bite") == 0) {
        this->foulCost = 30;
        this->setInfo(1, 0, 1.5, 0, 0.7, 5, 0, colorType::colorless, damageType::physical, 0.4, constants::smallProbabilityStatusEffect);
        this->causeBleed = true;
        this->causeInfect = true;
    }
    else if (this->name.compare("charge") == 0) {
        this->foulCost = 30;
        this->setInfo(1.2, 0, 0.8, 0, 0.9, 5, 0, colorType::colorless, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBleed = true;
    }
    else if (this->name.compare("pinch") == 0) {
        this->foulCost = 30;
        this->setInfo(1, 0, 1.5, 0, 0.9, 7, 0, colorType::colorless, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBleed = true;
        this->causeInfect = true;
    }
    else if (this->name.compare("flail") == 0) {
        this->foulCost = 30;
        this->setInfo(0.9, 0, 0.8, 0, 1.3, 5, 5, colorType::blue, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeDrowning = true;
    }
    else if (this->name.compare("rub") == 0) {
        this->foulCost = 50;
        this->setInfo(1.1, 0, 0.85, 0, 1, 5, 5, colorType::red, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBurnt = true;
    }
    else if (this->name.compare("excrete") == 0) {
        this->foulCost = 50;
        this->setInfo(0.5, 0, 0.5, 0, 1, 5, 5, colorType::brown, damageType::physical, 0.2, constants::largeProbabilityStatusEffect);
        this->causeRot = true;
    }
    else if (this->name.compare("coldslash") == 0) {
        this->foulCost = 50;
        this->setInfo(1.3, 0, 0.7, 0, 0.8, 5, 5, colorType::cyan, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeChill = true;
    }
    else if (this->name.compare("dive") == 0) {
        this->foulCost = 50;
        this->setInfo(1, 0, 1.4, 0, 1, 5, 5, colorType::orange, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeInfect = true;
    }
    else if (this->name.compare("magicattack") == 0) {
        this->foulCost = 50;
        this->setInfo(1, 0, 0, 1, 1, 5, 5, colorType::colorless, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeWilt = true;
    }
    else if (this->name.compare("waterstrike") == 0) {
        this->foulCost = 50;
        this->setInfo(1, 0, 1, 0, 1, 7, 3, colorType::blue, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeDrowning = true;
    }
    else if (this->name.compare("firestrike") == 0) {
        this->foulCost = 50;
        this->setInfo(1, 0, 1, 0, 1, 7, 3, colorType::red, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBurnt = true;
    }
    else if (this->name.compare("earthstrike") == 0) {
        this->foulCost = 50;
        this->setInfo(1, 0, 1, 0, 1, 7, 3, colorType::brown, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeRot = true;
    }
    else if (this->name.compare("icestrike") == 0) {
        this->foulCost = 50;
        this->setInfo(1, 0, 1, 0, 1, 7, 3, colorType::cyan, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeChill = true;
    }
    else if (this->name.compare("airstrike") == 0) {
        this->foulCost = 50;
        this->setInfo(1, 0, 1, 0, 1, 7, 3, colorType::orange, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeInfect = true;
    }
    else if (this->name.compare("gravitystrike") == 0) {
        this->foulCost = 80;
        this->setInfo(1, 0, 1, 0, 1, 10, 5, colorType::purple, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeShaken = true;
    }
    else if (this->name.compare("electricitystrike") == 0) {
        this->foulCost = 80;
        this->setInfo(1, 0, 1, 0, 1, 10, 5, colorType::yellow, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeShocked = true;
    }
    else if (this->name.compare("nuclearstrike") == 0) {
        this->foulCost = 80;
        this->setInfo(1, 0, 1, 0, 1, 10, 5, colorType::magenta, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeUnstable = true;
    }
    else if (this->name.compare("darkstrike") == 0) {
        this->foulCost = 110;
        this->setInfo(1, 0, 1, 0, 1, 10, 10, colorType::black, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeObscure = true;
    }
    else if (this->name.compare("lightstrike") == 0) {
        this->foulCost = 110;
        this->setInfo(1, 0, 1, 0, 1, 10, 10, colorType::white, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBright = true;
    }
    else if (this->name.compare("naturestrike") == 0) {
        this->foulCost = 140;
        this->setInfo(1, 0, 1, 0, 1, 12, 12, colorType::green, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        //this->causeBalance = true;
    }

    // Basic Weak Spells
    if (this->name.compare("wisp") == 0) {
        this->foulCost = 50;
        this->setInfo(0, 1, 0, 1, 1, 0, 3, colorType::colorless, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeWilt = true;
    }
    else if (this->name.compare("magicstrike") == 0) {
        this->foulCost = 50;
        this->setInfo(0, 1, 1, 0, 1, 3, 3, colorType::colorless, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBleed = true;
    }
    else if (this->name.compare("drain") == 0) {
        this->foulCost = 50;
        this->setInfo(0, 0.8, 0, 1, 1, 0, 5, colorType::colorless, damageType::physical, 0.2, 0);
    }
    else if (this->name.compare("bandage") == 0) {
        this->foulCost = 30;
        this->setInfo(0, 0, 0, 0, 0, 0, 5, colorType::colorless, damageType::none, 0.0, 0);
        this->setRestores(15, 0, 0);
    }
    else if (this->name.compare("heal") == 0) {
        this->foulCost = 50;
        this->setInfo(0, 0, 0, 0, 0, 0, 15, colorType::colorless, damageType::none, 0.0, 0);
        this->setRestores(30, 0, 0);
    }
    else if (this->name.compare("splash") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 1, 0, 1, 1, 0, 5, colorType::blue, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeDrowning = true;
    }
    else if (this->name.compare("flame") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 1, 0, 1, 1, 0, 5, colorType::red, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBurnt = true;
    }
    else if (this->name.compare("dust") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 1, 0, 1, 1, 0, 5, colorType::brown, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeRot = true;
    }
    else if (this->name.compare("frost") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 1, 0, 1, 1, 0, 5, colorType::cyan, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeChill = true;
    }
    else if (this->name.compare("breeze") == 0) {
        this->foulCost = 60;
        this->setInfo(0, 1, 0, 1, 1, 0, 5, colorType::orange, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeInfect = true;
    }
    else if (this->name.compare("pull") == 0) {
        this->foulCost = 90;
        this->setInfo(0, 1, 0, 1, 1, 0, 8, colorType::purple, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeShaken = true;
    }
    else if (this->name.compare("spark") == 0) {
        this->foulCost = 90;
        this->setInfo(0, 1, 0, 1, 1, 0, 8, colorType::yellow, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeShocked = true;
    }
    else if (this->name.compare("gammaray") == 0) {
        this->foulCost = 90;
        this->setInfo(0, 1, 0, 1, 1, 0, 8, colorType::magenta, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeUnstable = true;
    }
    else if (this->name.compare("shadow") == 0) {
        this->foulCost = 120;
        this->setInfo(0, 1, 0, 1, 1, 0, 12, colorType::black, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeObscure = true;
    }
    else if (this->name.compare("ray") == 0) {
        this->foulCost = 120;
        this->setInfo(0, 1, 0, 1, 1, 0, 12, colorType::white, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBright = true;
    }
    //else if (this->name.compare("???") == 0) {
        this->foulCost = 150;
    //    this->setInfo(0, 1, 0, 1, 1, 0, 15, colorType::green, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
    //}

    // Basic Strong Attack
    if (this->name.compare("hammer") == 0) {
        this->foulCost = 100;
        this->setInfo(1.4, 0, 1, 0, 1, 10, 0, colorType::colorless, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeHemorrhage = true;
    }
    else if (this->name.compare("jump") == 0) {
        this->foulCost = 100;
        this->setInfo(1.1, 0, 0.5, 0, 1.3, 15, 0, colorType::colorless, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBleed = true;
    }
    else if (this->name.compare("toxicbite") == 0) {
        this->foulCost = 100;
        this->setInfo(1, 0, 1, 0, 0.9, 15, 0, colorType::colorless, damageType::physical, 0.3, constants::mediumProbabilityStatusEffect);
        this->causeBleed = true;
        this->causeRot = true;
        this->causeInfect = true;
        this->causeDecay = true;
        this->causeDisease = true;
    }
    else if (this->name.compare("chomp") == 0) {
        this->foulCost = 100;
        this->setInfo(1.8, 0, 1.2, 0, 0.8, 20, 0, colorType::colorless, damageType::physical, 0.5, constants::largeProbabilityStatusEffect);
        this->causeBleed = true;
    }
    else if (this->name.compare("slash") == 0) {
        this->foulCost = 100;
        this->setInfo(1.6, 0, 1.2, 0, 1, 20, 0, colorType::colorless, damageType::physical, 0.0, constants::largeProbabilityStatusEffect);
        this->causeBleed = true;
    }
    else if (this->name.compare("suck") == 0) {
        this->foulCost = 100;
        this->setInfo(1, 0, 1, 0, 1, 25, 0, colorType::colorless, damageType::physical, 0.8, constants::smallProbabilityStatusEffect);
        this->causeBleed = true;
        this->causeInfect = true;
        this->causeDisease = true;
    }
    else if (this->name.compare("poison") == 0) {
        this->foulCost = 100;
        this->setInfo(1.4, 0, 1, 0, 1, 25, 0, colorType::colorless, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeInfect = true;
        this->causeDisease = true;
        this->causeWilt = true;
        this->causeWither = true;
    }
    else if (this->name.compare("claw") == 0) {
        this->foulCost = 100;
        this->setInfo(1.6, 0, 1, 0, 1.1, 25, 0, colorType::colorless, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBleed = true;
    }
    else if (this->name.compare("maul") == 0) {
        this->foulCost = 120;
        this->setInfo(1.8, 0, 1, 0, 1, 30, 0, colorType::colorless, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBleed = true;
        this->causeHemorrhage = true;
    }
    else if (this->name.compare("peck") == 0) {
        this->foulCost = 100;
        this->setInfo(1.2, 0, 1.5, 0, 1, 25, 0, colorType::colorless, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBleed = true;
        this->causeInfect = true;
    }
    else if (this->name.compare("thrash") == 0) {
        this->foulCost = 120;
        this->setInfo(1.2, 0, 1, 0, 1.2, 20, 10, colorType::blue, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeDrowning = true;
        this->causeDrowned = true;
    }
    else if (this->name.compare("ignite") == 0) {
        this->foulCost = 120;
        this->setInfo(1.6, 0, 0.9, 0, 1, 20, 10, colorType::red, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeBurnt = true;
        this->causeCharred = true;
    }
    else if (this->name.compare("ooze") == 0) {
        this->foulCost = 120;
        this->setInfo(0.8, 0, 0.8, 0, 1, 20, 10, colorType::brown, damageType::physical, 0.3, constants::largeProbabilityStatusEffect);
        this->causeRot = true;
        this->causeDecay = true;
    }
    else if (this->name.compare("coldmaul") == 0) {
        this->foulCost = 120;
        this->setInfo(1.7, 0, 0.9, 0, 0.9, 20, 10, colorType::cyan, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeChill = true;
        this->causeFrozen = true;
    }
    else if (this->name.compare("flurry") == 0) {
        this->foulCost = 120;
        this->setInfo(0.6, 0, 1, 0, 1, 20, 10, colorType::orange, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeInfect = true;
        this->causeDisease = true;
        this->attackTimes = 3;
    }
    else if (this->name.compare("magichammer") == 0) {
        this->foulCost = 120;
        this->setInfo(1.4, 0, 0, 1, 1, 15, 15, colorType::colorless, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeWither = true;
    }
    else if (this->name.compare("waterseal") == 0) {
        this->foulCost = 130;
        this->setInfo(1.4, 0, 1, 0, 1, 20, 10, colorType::blue, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeDrowned = true;
    }
    else if (this->name.compare("fireseal") == 0) {
        this->foulCost = 130;
        this->setInfo(1.4, 0, 1, 0, 1, 20, 10, colorType::red, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeCharred = true;
    }
    else if (this->name.compare("earthseal") == 0) {
        this->foulCost = 130;
        this->setInfo(1.4, 0, 1, 0, 1, 20, 10, colorType::brown, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeDecay = true;
    }
    else if (this->name.compare("iceseal") == 0) {
        this->foulCost = 130;
        this->setInfo(1.4, 0, 1, 0, 1, 20, 10, colorType::cyan, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeFrozen = true;
    }
    else if (this->name.compare("airseal") == 0) {
        this->foulCost = 130;
        this->setInfo(1.4, 0, 1, 0, 1, 20, 10, colorType::orange, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeDisease = true;
    }
    else if (this->name.compare("gravityseal") == 0) {
        this->foulCost = 180;
        this->setInfo(1.4, 0, 1, 0, 1, 30, 15, colorType::purple, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeFallen = true;
    }
    else if (this->name.compare("electricityseal") == 0) {
        this->foulCost = 180;
        this->setInfo(1.4, 0, 1, 0, 1, 30, 15, colorType::yellow, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeParalyzed = true;
    }
    else if (this->name.compare("nuclearseal") == 0) {
        this->foulCost = 180;
        this->setInfo(1.4, 0, 1, 0, 1, 30, 15, colorType::magenta, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeRadioactive = true;
    }
    else if (this->name.compare("darkseal") == 0) {
        this->foulCost = 230;
        this->setInfo(1.4, 0, 1, 0, 1, 30, 30, colorType::black, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeHidden = true;
    }
    else if (this->name.compare("lightseal") == 0) {
        this->foulCost = 230;
        this->setInfo(1.4, 0, 1, 0, 1, 30, 30, colorType::white, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeIlluminated = true;
    }
    else if (this->name.compare("natureseal") == 0) {
        this->foulCost = 300;
        this->setInfo(1.4, 0, 1, 0, 1, 40, 40, colorType::green, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        //this->cause = true;
    }

    // Basic Strong Spells
    if (this->name.compare("bolt") == 0) {
        this->foulCost = 150;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 10, colorType::colorless, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeWither = true;
    }
    else if (this->name.compare("magicseal") == 0) {
        this->foulCost = 150;
        this->setInfo(0, 1.5, 1, 0, 1, 8, 8, colorType::colorless, damageType::physical, 0.0, constants::smallProbabilityStatusEffect);
        this->causeHemorrhage = true;
    }
    else if (this->name.compare("siphon") == 0) {
        this->foulCost = 150;
        this->setInfo(0, 1, 0, 1, 1, 0, 15, colorType::colorless, damageType::magic, 0.4, constants::smallProbabilityStatusEffect);
    }
    else if (this->name.compare("revive") == 0) {
        this->foulCost = 150;
        this->setInfo(0, 0, 0, 0, 0, 0, 30, colorType::colorless, damageType::none, 0.0, 0);
        this->setRestores(50, 0, 0);
    }
    else if (this->name.compare("venom") == 0) {
        this->foulCost = 150;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 25, colorType::colorless, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeInfect = true;
        this->causeDisease = true;
        this->causeWilt = true;
        this->causeWither = true;
    }
    else if (this->name.compare("stream") == 0) {
        this->foulCost = 180;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 12, colorType::blue, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeDrowned = true;
    }
    else if (this->name.compare("fire") == 0) {
        this->foulCost = 180;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 12, colorType::red, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeCharred = true;
    }
    else if (this->name.compare("dirt") == 0) {
        this->foulCost = 180;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 12, colorType::brown, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeDecay = true;
    }
    else if (this->name.compare("crystal") == 0) {
        this->foulCost = 180;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 12, colorType::cyan, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeFrozen = true;
    }
    else if (this->name.compare("wind") == 0) {
        this->foulCost = 180;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 12, colorType::orange, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeDisease = true;
    }
    else if (this->name.compare("orbit") == 0) {
        this->foulCost = 210;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 15, colorType::purple, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeFallen = true;
    }
    else if (this->name.compare("static") == 0) {
        this->foulCost = 210;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 15, colorType::yellow, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeParalyzed = true;
    }
    else if (this->name.compare("betaray") == 0) {
        this->foulCost = 210;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 15, colorType::magenta, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeRadioactive = true;
    }
    else if (this->name.compare("darkness") == 0) {
        this->foulCost = 250;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 20, colorType::black, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeHidden = true;
    }
    else if (this->name.compare("beam") == 0) {
        this->foulCost = 250;
        this->setInfo(0, 1.5, 0, 1, 1, 0, 20, colorType::white, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
        this->causeIlluminated = true;
    }
    //else if (this->name.compare("???") == 0) {
        this->foulCost = 300;
    //    this->setInfo(0, 1, 0, 1, 1, 0, 25, colorType::green, damageType::magic, 0.0, constants::smallProbabilityStatusEffect);
    //}

    // Stat change abilities
    if (this->name.compare("grow") == 0) {
        this->foulCost = 150;
        this->setInfo(0, 0, 0, 0, 1, 7, 7, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeGrow = true;
    }
    else if (this->name.compare("strength") == 0) {
        this->foulCost = 150;
        this->setInfo(0, 0, 0, 0, 1, 7, 7, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeStrength = true;
    }
    else if (this->name.compare("cogent") == 0) {
        this->foulCost = 150;
        this->setInfo(0, 0, 0, 0, 1, 7, 7, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeCogent = true;
    }
    else if (this->name.compare("defend") == 0) {
        this->foulCost = 150;
        this->setInfo(0, 0, 0, 0, 1, 7, 7, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeDefend = true;
    }
    else if (this->name.compare("resolve") == 0) {
        this->foulCost = 150;
        this->setInfo(0, 0, 0, 0, 1, 7, 7, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeResolve = true;
    }
    else if (this->name.compare("swiftness") == 0) {
        this->foulCost = 150;
        this->setInfo(0, 0, 0, 0, 1, 7, 7, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeSwiftness = true;
    }
    else if (this->name.compare("enlarge") == 0) {
        this->foulCost = 300;
        this->setInfo(0, 0, 0, 0, 1, 25, 25, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeEnlarge = true;
    }
    else if (this->name.compare("beserk") == 0) {
        this->foulCost = 300;
        this->setInfo(0, 0, 0, 0, 1, 25, 25, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeBeserk = true;
    }
    else if (this->name.compare("potent") == 0) {
        this->foulCost = 300;
        this->setInfo(0, 0, 0, 0, 1, 25, 25, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causePotent = true;
    }
    else if (this->name.compare("bulwark") == 0) {
        this->foulCost = 300;
        this->setInfo(0, 0, 0, 0, 1, 25, 25, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeBulwark = true;
    }
    else if (this->name.compare("dauntless") == 0) {
        this->foulCost = 300;
        this->setInfo(0, 0, 0, 0, 1, 25, 25, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeDauntless = true;
    }
    else if (this->name.compare("deftness") == 0) {
        this->foulCost = 300;
        this->setInfo(0, 0, 0, 0, 1, 25, 25, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeDeftness = true;
    }
    else if (this->name.compare("weak") == 0) {
        this->foulCost = 200;
        this->setInfo(0, 0, 0, 0, 1, 7, 7, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeWeak = true;
    }
    else if (this->name.compare("inept") == 0) {
        this->foulCost = 200;
        this->setInfo(0, 0, 0, 0, 1, 7, 7, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeInept = true;
    }
    else if (this->name.compare("break") == 0) {
        this->foulCost = 200;
        this->setInfo(0, 0, 0, 0, 1, 7, 7, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeBreak = true;
    }
    else if (this->name.compare("outwill") == 0) {
        this->foulCost = 200;
        this->setInfo(0, 0, 0, 0, 1, 7, 7, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeOutwill = true;
    }
    else if (this->name.compare("slow") == 0) {
        this->foulCost = 200;
        this->setInfo(0, 0, 0, 0, 1, 7, 7, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeSlowness = true;
    }
    else if (this->name.compare("feeble") == 0) {
        this->foulCost = 350;
        this->setInfo(0, 0, 0, 0, 1, 25, 25, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeFeeble = true;
    }
    else if (this->name.compare("impotent") == 0) {
        this->foulCost = 350;
        this->setInfo(0, 0, 0, 0, 1, 25, 25, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeImpotent = true;
    }
    else if (this->name.compare("smash") == 0) {
        this->foulCost = 350;
        this->setInfo(0, 0, 0, 0, 1, 25, 25, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeSmash = true;
    }
    else if (this->name.compare("shatter") == 0) {
        this->foulCost = 350;
        this->setInfo(0, 0, 0, 0, 1, 25, 25, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeShatter = true;
    }
    else if (this->name.compare("lethargy") == 0) {
        this->foulCost = 350;
        this->setInfo(0, 0, 0, 0, 1, 25, 25, colorType::colorless, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeLethargy = true;
    }

    // Unstable Weak Attack
    if (this->name.compare("manicstrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 25, 0, colorType::colorless, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBleed = true;
        this->selfBleed = true;
    }
    else if (this->name.compare("magicmania") == 0) {
        this->setInfo(2, 0, 0, 0.9, 1, 35, 35, colorType::colorless, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeWilt = true;
        this->selfWilt = true;
    }
    else if (this->name.compare("aquastrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 45, 25, colorType::blue, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeDrowning = true;
        this->selfDrowning = true;
    }
    else if (this->name.compare("igniastrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 45, 25, colorType::red, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBurnt = true;
        this->selfBurnt = true;
    }
    else if (this->name.compare("terrastrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 45, 25, colorType::brown, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeRot = true;
        this->selfRot = true;
    }
    else if (this->name.compare("glaciastrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 45, 25, colorType::cyan, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeChill = true;
        this->selfChill = true;
    }
    else if (this->name.compare("aurastrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 45, 25, colorType::orange, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeInfect = true;
        this->selfInfect = true;
    }
    else if (this->name.compare("potentiatrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 50, 35, colorType::purple, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeShaken = true;
        this->selfShaken = true;
    }
    else if (this->name.compare("fulmastrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 50, 35, colorType::yellow, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeShocked = true;
        this->selfShocked = true;
    }
    else if (this->name.compare("centrastrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 50, 35, colorType::magenta, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeUnstable = true;
        this->selfUnstable = true;
    }
    else if (this->name.compare("tenebrastrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 60, 50, colorType::black, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeObscure = true;
        this->selfObscure = true;
    }
    else if (this->name.compare("lumastrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 60, 50, colorType::white, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBright = true;
        this->causeBright = true;
    }
    else if (this->name.compare("staterastrike") == 0) {
        this->setInfo(2, 0, 0.9, 0, 1, 70, 70, colorType::green, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        //this->causeBalance = true;
        //this->selfBalance = true;
    }

    // Unstable Weak Spells
    if (this->name.compare("destruction") == 0) {
        this->setInfo(0, 2, 0, 0.9, 1, 0, 25, colorType::colorless, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeWilt = true;
        this->selfWilt = true;
    }
    else if (this->name.compare("magiccudgel") == 0) {
        this->setInfo(0, 2, 0.9, 0, 1, 35, 35, colorType::colorless, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBleed = true;
        this->selfBleed = true;
    }
    else if (this->name.compare("flood") == 0) {
        this->setInfo(0, 2, 0, 0.9, 1, 0, 35, colorType::blue, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeDrowning = true;
        this->selfDrowning = true;
    }
    else if (this->name.compare("wildfire") == 0) {
        this->setInfo(0, 2, 0, 0.9, 1, 0, 35, colorType::red, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBurnt = true;
        this->selfBurnt = true;
    }
    else if (this->name.compare("tremor") == 0) {
        this->setInfo(0, 2, 0, 0.9, 1, 0, 35, colorType::brown, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeRot = true;
        this->selfRot = true;
    }
    else if (this->name.compare("frostbite") == 0) {
        this->setInfo(0, 2, 0, 0.9, 1, 0, 35, colorType::cyan, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeChill = true;
        this->selfChill = true;
    }
    else if (this->name.compare("tornado") == 0) {
        this->setInfo(0, 2, 0, 0.9, 1, 0, 35, colorType::orange, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeInfect = true;
        this->selfInfect = true;
    }
    else if (this->name.compare("forcefield") == 0) {
        this->setInfo(0, 2, 0, 0.9, 1, 0, 50, colorType::purple, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeShaken = true;
        this->selfShaken = true;
    }
    else if (this->name.compare("lightning") == 0) {
        this->setInfo(0, 2, 0, 0.9, 1, 0, 50, colorType::yellow, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeShocked = true;
        this->selfShocked = true;
    }
    else if (this->name.compare("alpharay") == 0) {
        this->setInfo(0, 2, 0, 0.9, 1, 0, 50, colorType::magenta, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeUnstable = true;
        this->selfUnstable = true;
    }
    else if (this->name.compare("phantasm") == 0) {
        this->setInfo(0, 2, 0, 0.9, 1, 0, 60, colorType::black, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeObscure = true;
        this->selfObscure = true;
    }
    else if (this->name.compare("irradiation") == 0) {
        this->setInfo(0, 2, 0, 0.9, 1, 0, 60, colorType::white, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBright = true;
        this->selfBright = true;
    }
    //else if (this->name.compare("???") == 0) {
    //    this->setInfo(0, 2, 0, 0.9, 1, 0, 75, colorType::green, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
    //  this->causeBalance = true;
    // this->selfBalance = true;
    //}

    // Unstable Strong Attack
    if (this->name.compare("maniastrike") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 50, 0, colorType::colorless, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBleed = true;
        this->selfBleed = true;
        this->causeHemorrhage = true;
        this->selfHemorrhage = true;
    }
    else if (this->name.compare("magicmania") == 0) {
        this->setInfo(3, 0, 0, 0.8, 1, 60, 60, colorType::colorless, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeWilt = true;
        this->selfWilt = true;
        this->causeWither = true;
        this->selfWither = true;
    }
    else if (this->name.compare("aquaseal") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 70, 40, colorType::blue, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeDrowning = true;
        this->selfDrowning = true;
        this->causeDrowned = true;
        this->selfDrowned = true;
    }
    else if (this->name.compare("igniaseal") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 70, 40, colorType::red, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBurnt = true;
        this->selfBurnt = true;
        this->causeCharred = true;
        this->selfCharred = true;
    }
    else if (this->name.compare("terraseal") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 70, 40, colorType::brown, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeRot = true;
        this->selfRot = true;
        this->causeDecay = true;
        this->selfDecay = true;
    }
    else if (this->name.compare("glaciaseal") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 70, 40, colorType::cyan, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeChill = true;
        this->selfChill = true;
        this->causeFrozen = true;
        this->selfFrozen = true;
    }
    else if (this->name.compare("auraseal") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 70, 40, colorType::orange, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeInfect = true;
        this->selfInfect = true;
        this->causeDisease = true;
        this->selfDisease = true;
    }
    else if (this->name.compare("potentiaseal") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 80, 60, colorType::purple, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeShaken = true;
        this->selfShaken = true;
        this->causeFallen = true;
        this->selfFallen = true;
    }
    else if (this->name.compare("fulmaseal") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 80, 60, colorType::yellow, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeShocked = true;
        this->selfShocked = true;
        this->causeParalyzed = true;
        this->selfParalyzed = true;
    }
    else if (this->name.compare("centraseal") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 80, 60, colorType::magenta, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeUnstable = true;
        this->selfUnstable = true;
        this->causeRadioactive = true;
        this->selfRadioactive = true;
    }
    else if (this->name.compare("tenebraseal") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 90, 80, colorType::black, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeObscure = true;
        this->selfObscure = true;
        this->causeHidden = true;
        this->selfHidden = true;
    }
    else if (this->name.compare("lumaseal") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 90, 80, colorType::white, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBright = true;
        this->causeBright = true;
        this->causeIlluminated = true;
        this->selfIlluminated = true;
    }
    else if (this->name.compare("stateraseal") == 0) {
        this->setInfo(3, 0, 0.8, 0, 1, 100, 100, colorType::green, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        //this->causeBalance = true;
        //this->selfBalance = true;
        //this->causeEqualize = true;
        //this->selfEqualize = true;
    }

    // Unstable Weak Spells
    if (this->name.compare("chaos") == 0) {
        this->setInfo(0, 3, 0, 0.8, 1, 0, 50, colorType::colorless, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeWilt = true;
        this->selfWilt = true;
        this->causeWither = true;
        this->selfWither = true;
    }
    else if (this->name.compare("magicpummel") == 0) {
        this->setInfo(0, 3, 0.8, 0, 1, 60, 60, colorType::colorless, damageType::physical, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBleed = true;
        this->selfBleed = true;
        this->causeHemorrhage = true;
        this->selfHemorrhage = true;
    }
    else if (this->name.compare("hurricane") == 0) {
        this->setInfo(0, 3, 0, 0.8, 1, 0, 60, colorType::blue, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeDrowning = true;
        this->selfDrowning = true;
        this->causeDrowned = true;
        this->selfDrowned = true;
    }
    else if (this->name.compare("volcano") == 0) {
        this->setInfo(0, 3, 0, 0.8, 1, 0, 60, colorType::red, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBurnt = true;
        this->selfBurnt = true;
        this->causeCharred = true;
        this->selfCharred = true;
    }
    else if (this->name.compare("seism") == 0) {
        this->setInfo(0, 3, 0, 0.8, 1, 0, 60, colorType::brown, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeRot = true;
        this->selfRot = true;
        this->causeDecay = true;
        this->selfDecay = true;
    }
    else if (this->name.compare("hypothermia") == 0) {
        this->setInfo(0, 3, 0, 0.8, 1, 0, 60, colorType::cyan, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeChill = true;
        this->selfChill = true;
        this->causeFrozen = true;
        this->selfFrozen = true;
    }
    else if (this->name.compare("cyclone") == 0) {
        this->setInfo(0, 3, 0, 0.8, 1, 0, 60, colorType::orange, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeInfect = true;
        this->selfInfect = true;
        this->causeDisease = true;
        this->selfDisease = true;
    }
    else if (this->name.compare("gravitationalcollapse") == 0) {
        this->setInfo(0, 3, 0, 0.8, 1, 0, 75, colorType::purple, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeShaken = true;
        this->selfShaken = true;
        this->causeFallen = true;
        this->selfFallen = true;
    }
    else if (this->name.compare("fulmination") == 0) {
        this->setInfo(0, 3, 0, 0.8, 1, 0, 75, colorType::yellow, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeShocked = true;
        this->selfShocked = true;
        this->causeParalyzed = true;
        this->selfParalyzed = true;
    }
    else if (this->name.compare("clusterdecay") == 0) {
        this->setInfo(0, 3, 0, 0.8, 1, 0, 75, colorType::magenta, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeUnstable = true;
        this->selfUnstable = true;
        this->causeRadioactive = true;
        this->selfRadioactive = true;
    }
    else if (this->name.compare("nightmare") == 0) {
        this->setInfo(0, 3, 0, 0.8, 1, 0, 90, colorType::black, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeObscure = true;
        this->selfObscure = true;
        this->causeHidden = true;
        this->selfHidden = true;
    }
    else if (this->name.compare("laser") == 0) {
        this->setInfo(0, 3, 0, 0.8, 1, 0, 90, colorType::white, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
        this->causeBright = true;
        this->selfBright = true;
        this->causeIlluminated = true;
        this->selfIlluminated = true;
    }
    //else if (this->name.compare("???") == 0) {
    //    this->setInfo(0, 3, 0, 0.8, 1, 0, 110, colorType::green, damageType::magic, 0.0, constants::mediumProbabilityStatusEffect);
    //  this->causeBalance = true;
    // this->selfBalance = true;
    // this->causeEqualize = true;
    // this->selfEqualize = true;
    //}

    // Monster-only abilities
    if (this->name.compare("rotting") == 0) {
        this->setInfo(0, 0, 0, 0, 1, 10, 0, colorType::brown, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->causeRot = true;
        this->selfRot = true;
    }
    else if (this->name.compare("selfrot") == 0) {
        this->setInfo(0, 0, 0, 0, 1, 10, 0, colorType::brown, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->selfRot = true;
    }
    else if (this->name.compare("drowning") == 0) {
        this->setInfo(0, 0, 0, 0, 1, 10, 0, colorType::blue, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
        this->selfDrowning = true;
        this->selfDrowned = true;
    }
    else if (this->name.compare("jump-yip") == 0) {
        this->setInfo(2, 0, 0, 0, 1.2, 20, 0, colorType::brown, damageType::none, 0.0, constants::largeProbabilityStatusEffect);
    }

    if (!abilityValid) {
        std::cout << "ERROR: Ability name " << this->name << " not found in Ability reference.\n";
        this->setInfo(0, 0, 0, 0, 0, 0, 0, colorType::colorless, damageType::none, 0.0, 0.0);
    }
}

void Ability::setMultipliers(double attack, double magic, double piercing, double penetration,
    double dexterity) {
    this->attackMultiplier = attack;
    this->magicMultiplier = magic;
    this->piercingMultiplier = piercing;
    this->penetrationMultiplier = penetration;
    this->dexterityMultiplier = dexterity;
}

void Ability::setInfo(double attack, double magic, double piercing, double penetration,
    double dexterity, int energy, int mana, colorType color, damageType damage, double lifesteal,
    double probability) {
    this->setMultipliers(attack, magic, piercing, penetration, dexterity);
    this->energyCost = energy;
    this->manaCost = mana;
    this->abilityColor = color;
    this->abilityDamage = damage;
    this->lifesteal = lifesteal;
    this->effectProbability = probability;
    this->abilityValid = true;
}

void Ability::setRestores(int restoreHealth, int restoreEnergy, int restoreMana) {
    this->restoreHealth = restoreHealth;
    this->restoreEnergy = restoreEnergy;
    this->restoreMana = restoreMana;
}

// Return file string for saved games
std::string Ability::saveGame() {
    std::string fileString{};
    fileString += "*DEFINE=Ability\n";
    fileString += "*STRING=name\n" + this->name + "\n*END\n";
    // Name is unique identifier
    /*
    fileString += "abilityValid=" + core_functions::boolToString(this->abilityValid) + "\n";
    fileString += "energyCost=" + std::to_string(this->energyCost) + "\n";
    fileString += "manaCost=" + std::to_string(this->manaCost) + "\n";
    fileString += "foulCost=" + std::to_string(this->foulCost) + "\n";
    fileString += "attackMultiplier=" + std::to_string(this->attackMultiplier) + "\n";
    fileString += "magicMultiplier=" + std::to_string(this->magicMultiplier) + "\n";
    fileString += "piercingMultiplier=" + std::to_string(this->piercingMultiplier) + "\n";
    fileString += "penetrationMultiplier=" + std::to_string(this->penetrationMultiplier) + "\n";
    fileString += "dexterityMultiplier=" + std::to_string(this->dexterityMultiplier) + "\n";
    fileString += "abilityColor=" + std::to_string(this->getColorInt()) + "\n";
    fileString += "abilityDamage=" + std::to_string(this->getDamageTypeInt()) + "\n";
    fileString += "lifesteal=" + std::to_string(this->lifesteal) + "\n";
    fileString += "effectProbability=" + std::to_string(this->effectProbability) + "\n";
    fileString += "attackTimes=" + std::to_string(this->attackTimes) + "\n";
    fileString += "restoreHealth=" + std::to_string(this->restoreHealth) + "\n";
    fileString += "restoreMana=" + std::to_string(this->restoreMana) + "\n";
    fileString += "restoreEnergy=" + std::to_string(this->restoreEnergy) + "\n";
    fileString += "fleeAttempt=" + core_functions::boolToString(this->fleeAttempt) + "\n";
    fileString += "causeGrow=" + core_functions::boolToString(this->causeGrow) + "\n";
    fileString += "causeEnlarge=" + core_functions::boolToString(this->causeEnlarge) + "\n";
    fileString += "causeStrength=" + core_functions::boolToString(this->causeStrength) + "\n";
    fileString += "causeBeserk=" + core_functions::boolToString(this->causeBeserk) + "\n";
    fileString += "causeCogent=" + core_functions::boolToString(this->causeCogent) + "\n";
    fileString += "causePotent=" + core_functions::boolToString(this->causePotent) + "\n";
    fileString += "causeDefend=" + core_functions::boolToString(this->causeDefend) + "\n";
    fileString += "causeBulwark=" + core_functions::boolToString(this->causeBulwark) + "\n";
    fileString += "causeResolve=" + core_functions::boolToString(this->causeResolve) + "\n";
    fileString += "causeDauntless=" + core_functions::boolToString(this->causeDauntless) + "\n";
    fileString += "causeSwiftness=" + core_functions::boolToString(this->causeSwiftness) + "\n";
    fileString += "causeDeftness=" + core_functions::boolToString(this->causeDeftness) + "\n";
    fileString += "causeWeak=" + core_functions::boolToString(this->causeWeak) + "\n";
    fileString += "causeFeeble=" + core_functions::boolToString(this->causeFeeble) + "\n";
    fileString += "causeInept=" + core_functions::boolToString(this->causeInept) + "\n";
    fileString += "causeImpotent=" + core_functions::boolToString(this->causeImpotent) + "\n";
    fileString += "causeBreak=" + core_functions::boolToString(this->causeBreak) + "\n";
    fileString += "causeSmash=" + core_functions::boolToString(this->causeSmash) + "\n";
    fileString += "causeOutwill=" + core_functions::boolToString(this->causeOutwill) + "\n";
    fileString += "causeShatter=" + core_functions::boolToString(this->causeShatter) + "\n";
    fileString += "causeSlowness=" + core_functions::boolToString(this->causeSlowness) + "\n";
    fileString += "causeLethargy=" + core_functions::boolToString(this->causeLethargy) + "\n";
    fileString += "causeBleed=" + core_functions::boolToString(this->causeBleed) + "\n";
    fileString += "causeHemorrhage=" + core_functions::boolToString(this->causeHemorrhage) + "\n";
    fileString += "causeWilt=" + core_functions::boolToString(this->causeWilt) + "\n";
    fileString += "causeWither=" + core_functions::boolToString(this->causeWither) + "\n";
    fileString += "causeDrowning=" + core_functions::boolToString(this->causeDrowning) + "\n";
    fileString += "causeDrowned=" + core_functions::boolToString(this->causeDrowned) + "\n";
    fileString += "causeBurnt=" + core_functions::boolToString(this->causeBurnt) + "\n";
    fileString += "causeCharred=" + core_functions::boolToString(this->causeCharred) + "\n";
    fileString += "causeRot=" + core_functions::boolToString(this->causeRot) + "\n";
    fileString += "causeDecay=" + core_functions::boolToString(this->causeDecay) + "\n";
    fileString += "causeChill=" + core_functions::boolToString(this->causeChill) + "\n";
    fileString += "causeFrozen=" + core_functions::boolToString(this->causeFrozen) + "\n";
    fileString += "causeInfect=" + core_functions::boolToString(this->causeInfect) + "\n";
    fileString += "causeDisease=" + core_functions::boolToString(this->causeDisease) + "\n";
    fileString += "causeShaken=" + core_functions::boolToString(this->causeShaken) + "\n";
    fileString += "causeFallen=" + core_functions::boolToString(this->causeFallen) + "\n";
    fileString += "causeShocked=" + core_functions::boolToString(this->causeShocked) + "\n";
    fileString += "causeParalyzed=" + core_functions::boolToString(this->causeParalyzed) + "\n";
    fileString += "causeUnstable=" + core_functions::boolToString(this->causeUnstable) + "\n";
    fileString += "causeRadioactive=" + core_functions::boolToString(this->causeRadioactive) + "\n";
    fileString += "causeObscure=" + core_functions::boolToString(this->causeObscure) + "\n";
    fileString += "causeHidden=" + core_functions::boolToString(this->causeHidden) + "\n";
    fileString += "causeBright=" + core_functions::boolToString(this->causeBright) + "\n";
    fileString += "causeIlluminated=" + core_functions::boolToString(this->causeIlluminated) + "\n";
    fileString += "selfBleed=" + core_functions::boolToString(this->selfBleed) + "\n";
    fileString += "selfHemorrhage=" + core_functions::boolToString(this->selfHemorrhage) + "\n";
    fileString += "selfWilt=" + core_functions::boolToString(this->selfWilt) + "\n";
    fileString += "selfWither=" + core_functions::boolToString(this->selfWither) + "\n";
    fileString += "selfDrowning=" + core_functions::boolToString(this->selfDrowning) + "\n";
    fileString += "selfDrowned=" + core_functions::boolToString(this->selfDrowned) + "\n";
    fileString += "selfBurnt=" + core_functions::boolToString(this->selfBurnt) + "\n";
    fileString += "selfCharred=" + core_functions::boolToString(this->selfCharred) + "\n";
    fileString += "selfRot=" + core_functions::boolToString(this->selfRot) + "\n";
    fileString += "selfDecay=" + core_functions::boolToString(this->selfDecay) + "\n";
    fileString += "selfChill=" + core_functions::boolToString(this->selfChill) + "\n";
    fileString += "selfFrozen=" + core_functions::boolToString(this->selfFrozen) + "\n";
    fileString += "selfInfect=" + core_functions::boolToString(this->selfInfect) + "\n";
    fileString += "selfDisease=" + core_functions::boolToString(this->selfDisease) + "\n";
    fileString += "selfShaken=" + core_functions::boolToString(this->selfShaken) + "\n";
    fileString += "selfFallen=" + core_functions::boolToString(this->selfFallen) + "\n";
    fileString += "selfShocked=" + core_functions::boolToString(this->selfShocked) + "\n";
    fileString += "selfParalyzed=" + core_functions::boolToString(this->selfParalyzed) + "\n";
    fileString += "selfUnstable=" + core_functions::boolToString(this->selfUnstable) + "\n";
    fileString += "selfRadioactive=" + core_functions::boolToString(this->selfRadioactive) + "\n";
    fileString += "selfObscure=" + core_functions::boolToString(this->selfObscure) + "\n";
    fileString += "selfHidden=" + core_functions::boolToString(this->selfHidden) + "\n";
    fileString += "selfBright=" + core_functions::boolToString(this->selfBright) + "\n";
    fileString += "selfIlluminated=" + core_functions::boolToString(this->selfIlluminated) + "\n";
    */
    fileString += "*END\n";
    return fileString;
}