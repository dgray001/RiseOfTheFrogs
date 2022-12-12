/*
itemClass.cpp
The item class includes any non-unit found in environments (like items or small features of the
environment). Like units, items are points.
*/

#include <iostream>
#include <string>
#include "itemClass.h"
#include "coreFunctions.h"

Item::Item(int itemID) : Item(itemID, constants::defaultLuckFactor, 0, 0, 0) {
}
Item::Item(int itemID, double playerLuckFactor, double xLocation, double yLocation, double zLocation, bool forceNormalQuality) {
    this->itemID = itemID;
    this->xLocation = xLocation;
    this->yLocation = yLocation;
    this->zLocation = zLocation;
    switch (itemID) {
        // NULL item
        case -1:
            break;

        // Consumable
        case 1:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 1;
            this->name = "Food Bit";
            this->currEnergy = core_functions::randomInt(2, 6);
            this->currHealth = core_functions::randomInt(0, 1);
            if (forceNormalQuality) {
                this->currEnergy = 4;
                this->currHealth = 1;
            }
            break;
        case 2:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 1;
            this->name = "Food Pellet";
            this->currEnergy = core_functions::randomInt(5, 15);
            this->currHealth = core_functions::randomInt(1, 3);
            if (forceNormalQuality) {
                this->currEnergy = 10;
                this->currHealth = 2;
            }
            break;
        case 3:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 1;
            this->name = "Reptomin";
            this->currEnergy = core_functions::randomInt(15, 25);
            this->currHealth = core_functions::randomInt(3, 6);
            if (forceNormalQuality) {
                this->currEnergy = 20;
                this->currHealth = 4;
            }
            break;
        case 4:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 1;
            this->name = "Small Experience Potion";
            this->experience = 200;
            break;
        case 5:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 2;
            this->name = "Medium Experience Potion";
            this->experience = 2000;
            break;
        case 6:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Large Experience Potion";
            this->experience = 50000;
            break;
        case 7:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 4;
            this->name = "Super Experience Potion";
            this->experience = 1000000;
            break;
        case 8:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 5;
            this->name = "Ultra Experience Potion";
            this->experience = 10000000;
            break;
        case 9:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 1;
            this->name = "Small Health Potion";
            this->currHealth = 10;
            break;
        case 10:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 2;
            this->name = "Medium Health Potion";
            this->currHealth = 50;
            break;
        case 11:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Large Health Potion";
            this->currHealth = 250;
            break;
        case 12:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 4;
            this->name = "Super Health Potion";
            this->currHealth = 1000;
            break;
        case 13:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 5;
            this->name = "Ultra Health Potion";
            this->currHealth = 5000;
            break;
        case 14:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 1;
            this->name = "Small Mana Potion";
            this->currMana = 10;
            break;
        case 15:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 2;
            this->name = "Medium Mana Potion";
            this->currMana = 50;
            break;
        case 16:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Large Mana Potion";
            this->currMana = 250;
            break;
        case 17:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 4;
            this->name = "Super Mana Potion";
            this->currMana = 1000;
            break;
        case 18:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 5;
            this->name = "Ultra Mana Potion";
            this->currMana = 5000;
            break;
        case 19:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 1;
            this->name = "Small Energy Potion";
            this->currEnergy = 20;
            break;
        case 20:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 2;
            this->name = "Medium Energy Potion";
            this->currEnergy = 100;
            break;
        case 21:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Large Energy Potion";
            this->currEnergy = 500;
            break;
        case 22:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 4;
            this->name = "Super Energy Potion";
            this->currEnergy = 2000;
            break;
        case 23:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 5;
            this->name = "Ultra Energy Potion";
            this->currEnergy = 5000;
            break;
        case 24:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Lucky Coin";
            this->creditBonus = true;
            break;
        case 25:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Foul Reaper";
            this->foulBonus = true;
            break;
        case 26:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Clarity Potion";
            this->xpBonus = true;
            break;
        case 27:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 2;
            this->name = "Organic Remains";
            this->currEnergy = core_functions::randomInt(10, 30);
            this->currHealth = core_functions::randomInt(5, 20);
            if (forceNormalQuality) {
                this->currEnergy = 20;
                this->currHealth = 10;
            }
            break;
        case 28:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 2;
            this->name = "Flesh";
            this->currEnergy = core_functions::randomInt(25, 60);
            this->currHealth = core_functions::randomInt(15, 35);
            if (forceNormalQuality) {
                this->currEnergy = 45;
                this->currHealth = 25;
            }
            break;
        case 29:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 2;
            this->name = "Turtle Leg";
            this->currEnergy = core_functions::randomInt(50, 80);
            this->currHealth = core_functions::randomInt(30, 50);
            if (forceNormalQuality) {
                this->currEnergy = 75;
                this->currHealth = 40;
            }
            break;
        case 30:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 1;
            this->name = "Small Credit Potion";
            this->credits = 100;
            break;
        case 31:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 2;
            this->name = "Medium Credit Potion";
            this->credits = 1000;
            break;
        case 32:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Large Credit Potion";
            this->credits = 10000;
            break;
        case 33:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 4;
            this->name = "Super Credit Potion";
            this->credits = 100000;
            break;
        case 34:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 5;
            this->name = "Ultra Credit Potion";
            this->credits = 1000000;
            break;
        case 35:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 1;
            this->name = "Small Foul Potion";
            this->fouls = 5;
            break;
        case 36:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 2;
            this->name = "Medium Foul Potion";
            this->fouls = 20;
            break;
        case 37:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Large Foul Potion";
            this->fouls = 40;
            break;
        case 38:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 4;
            this->name = "Super Foul Potion";
            this->fouls = 100;
            break;
        case 39:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 5;
            this->name = "Ultra Foul Potion";
            this->fouls = 250;
            break;
        case 40:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 2;
            this->name = "Pizza";
            this->currHealth = 250;
            this->currMana = 250;
            this->currEnergy = 250;
            this->experience = 250;
            break;
        case 41:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Moth Soul";
            this->foulBonus = true;
            this->fouls = 25;
            break;
        case 42:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Acorn";
            this->currHealth = 40;
            this->cureChill = true;
            this->cureFrozen = true;
            break;
        case 43:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Mink Oil";
            this->currHealth = 10;
            this->cureInfect = true;
            this->cureDisease = true;
            this->cureRot = true;
            this->cureDecay = true;
            break;
        case 44:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Swan Elixir";
            this->cureWilt = true;
            this->cureWither = true;
            this->cureDrowning = true;
            this->cureDrowned = true;
            break;
        case 45:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Salamander Oil";
            this->currHealth = -10;
            this->currEnergy = 20;
            this->currMana = 20;
            this->cureWilt = true;
            this->cureWither = true;
            break;
        case 46:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Zazamushi";
            this->currHealth = 10;
            this->cureBleed = true;
            this->cureHemorrhage = true;
            break;
        case 47:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Cà Cuống";
            this->currHealth = 10;
            this->cureBreak = true;
            this->cureOutwill = true;
            break;
        case 48:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Cybister";
            this->currHealth = 20;
            this->causeGrow = true;
            break;
        case 49:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Ladybug Oil";
            this->currHealth = 20;
            this->luckBonus = true;
            break;
        case 50:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Fire Oil";
            this->cureBurnt = true;
            this->cureCharred = true;
            break;
        case 51:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Caviar";
            this->cureWeak = true;
            this->cureInept = true;
            break;
        case 52:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Electric Detritus";
            this->currHealth = 10;
            this->cureShocked = true;
            this->cureParalyzed = true;
            break;
        case 53:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Radioactive Detritus";
            this->currHealth = 10;
            this->cureUnstable = true;
            this->cureRadioactive = true;
            break;
        case 54:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Fallen Detritus";
            this->currHealth = 10;
            this->cureShaken = true;
            this->cureFallen = true;
            break;
        case 55:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Rabbit Soup";
            this->currHealth = 20;
            this->causeEnlarge = true;
            break;
        case 56:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Eel Oil";
            this->currEnergy = 20;
            this->currMana = 20;
            this->causeWilt = true;
            break;
        case 57:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Turtle Soup";
            this->currHealth = 30;
            this->currEnergy = 20;
            this->currMana = 20;
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 58:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Venison";
            this->currHealth = 100;
            this->currEnergy = 100;
            break;
        case 59:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Steak";
            this->currHealth = 150;
            this->currEnergy = 150;
            this->currMana = 150;
            break;
        case 60:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Snake Oil";
            this->currEnergy = 30;
            this->currMana = 30;
            this->cureInfect = true;
            this->cureDisease = true;
            break;
        case 61:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Spider Venom";
            this->currEnergy = 30;
            this->currMana = 30;
            this->causeWilt = true;
            this->causeWither = true;
            this->causeInfect = true;
            this->causeRot = true;
            this->selfWilt = true;
            this->selfWither = true;
            this->selfInfect = true;
            this->selfRot = true;
            break;
        case 62:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Bovine Tongue";
            this->cureBleed = true;
            this->cureWilt = true;
            this->cureDrowning = true;
            this->cureBurnt = true;
            this->cureRot = true;
            this->cureChill = true;
            this->cureInfect = true;
            break;
        case 63:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "White Acorn";
            this->cureBright = true;
            this->cureIlluminated = true;
            break;
        case 64:
            this->thisItemType = itemType::consumable;
            this->itemDimension = 3;
            this->name = "Black Acorn";
            this->cureObscure = true;
            this->cureHidden = true;
            break;
        
        // Weapon
        case 1001:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 1;
            this->name = "Aquarium Pebble";
            this->attack = 1;
            this->materials = { 9001 };
            break;
        case 1002:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 1;
            this->name = "Hermit Crab Claw";
            this->attack = 2;
            this->dexterity = -10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            this->causeBleed = true;
            this->causeInfect = true;
            break;
        case 1003:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 1;
            this->name = "Swordtail Fish Tooth";
            this->attack = 3;
            this->dexterity = -10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003 };
            this->causeBleed = true;
            break;
        case 1004:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 1;
            this->name = "Rainbow Shark Tooth";
            this->attack = 5;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003 };
            this->causeBleed = true;
            break;
        case 1005:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Water Spider Fang";
            this->attack = 3;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::blue;
            this->causeInfect = true;
            this->materials = { 9003 };
            break;
        case 1006:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Bass Tooth";
            this->attack = 5;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003 };
            this->causeBleed = true;
            break;
        case 1007:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Carp Tooth";
            this->attack = 5;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003 };
            this->causeBleed = true;
            break;
        case 1008:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Shell Fragment";
            this->attack = 4;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 1009:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Toxic Eel Tail";
            this->attack = 6;
            this->dexterity = 8;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004 };
            this->causeRot = true;
            break;
        case 1010:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Catfish Tooth";
            this->attack = 8;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003 };
            this->causeBleed = true;
            break;
        case 1011:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Rat Tooth";
            this->attack = 10;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9003 };
            this->causeBleed = true;
            break;
        case 1012:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Baby Crocodile Tooth";
            this->attack = 15;
            this->magic = 10;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003, 9102 };
            this->causeBleed = true;
            break;
        case 1013:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Baby Alligator Tooth";
            this->attack = 10;
            this->magic = 15;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003, 9102 };
            this->causeBleed = true;
            break;
        case 1014:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Snake Fang";
            this->attack = 8;
            this->lifesteal = 0.2;
            this->thisItemColor = itemColor::blue;
            this->causeInfect = true;
            this->materials = { 9003 };
            break;
        case 1015:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 1;
            this->name = "Worm Chief Stone";
            this->attack = 2;
            this->magic = 2;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9001, 9006 };
            this->causeDrowning = true;
            break;
        case 1016:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 1;
            this->name = "Dwarf Frog Claw";
            this->attack = 4;
            this->materials = { 9002, 9007 };
            this->causeBleed = true;
            break;
        case 1017:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 1;
            this->name = "Magic Aquarium Stone";
            this->magic = 2;
            this->materials = { 9001, 9006 };
            this->causeWilt = true;
            break;
        case 1018:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Magic Stone";
            this->magic = 5;
            this->materials = { 9101, 9006 };
            this->causeWilt = true;
            break;
        case 1019:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 2;
            this->name = "Cold Stone";
            this->attack = 3;
            this->magic = 3;
            this->thisItemColor = itemColor::cyan;
            this->materials = { 9101, 9105 };
            this->causeChill = true;
            break;
        case 1020:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Perch Tooth";
            this->attack = 14;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003 };
            this->causeBleed = true;
            break;
        case 1021:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Radula";
            this->attack = 12;
            this->magic = 12;
            this->thisItemColor = itemColor::brown;
            this->causeInfect = true;
            this->lifesteal = 0.1;
            this->materials = { 9003, 9004 };
            break;
        case 1022:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Rodent Incisors";
            this->attack = 17;
            this->thisItemColor = itemColor::brown;
            this->causeInfect = true;
            this->lifesteal = 0.1;
            this->materials = { 9003 };
            break;
        case 1023:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Water Wand";
            this->magic = 20;
            this->thisItemColor = itemColor::blue;
            this->causeDrowning = true;
            this->materials = { 9102 };
            break;
        case 1024:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Fire Wand";
            this->magic = 20;
            this->thisItemColor = itemColor::red;
            this->causeBurnt = true;
            this->materials = { 9103 };
            break;
        case 1025:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Earth Wand";
            this->magic = 20;
            this->thisItemColor = itemColor::brown;
            this->causeRot = true;
            this->materials = { 9104 };
            break;
        case 1026:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Ice Wand";
            this->magic = 20;
            this->thisItemColor = itemColor::cyan;
            this->causeChill = true;
            this->materials = { 9105 };
            break;
        case 1027:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Air Wand";
            this->magic = 20;
            this->thisItemColor = itemColor::orange;
            this->causeInfect = true;
            this->materials = { 9106 };
            break;
        case 1028:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Proboscis";
            this->attack = 10;
            this->piercing = 30;
            this->lifesteal = 0.4;
            this->materials = { 9004, 9005 };
            this->causeInfect = true;
            break;
        case 1029:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Eel Tail";
            this->attack = 17;
            this->dexterity = 10;
            this->materials = { 9004 };
            break;
        case 1030:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Gnathosoma";
            this->attack = 15;
            this->lifesteal = 0.2;
            this->materials = { 9004 };
            this->causeInfect = true;
            break;
        case 1031:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Beaver Claw";
            this->attack = 20;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002, 9004 };
            this->causeBleed = true;
            break;
        case 1032:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Muskrat Claw";
            this->attack = 18;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002, 9004 };
            this->causeBleed = true;
            break;
        case 1033:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Bass Teeth";
            this->attack = 17;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003 };
            this->causeBleed = true;
            break;
        case 1034:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Carp Teeth";
            this->attack = 17;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003 };
            this->causeBleed = true;
            break;
        case 1035:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Catfish Teeth";
            this->attack = 16;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003 };
            this->causeBleed = true;
            break;
        case 1036:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Duck Bill";
            this->attack = 15;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003 };
            break;
        case 1037:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Goose Bill";
            this->magic = 15;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003 };
            break;
        case 1038:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Crayfish Right Claw";
            this->attack = 20;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            this->causeBleed = true;
            this->causeInfect = true;
            break;
        case 1039:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Rostrum";
            this->attack = 18;
            this->viewDistance = 0.05;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004, 9005 };
            break;
        case 1040:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Spider Fangs";
            this->attack = 18;
            this->lifesteal = 0.1;
            this->causeWilt = true;
            this->materials = { 9003 };
            break;
        case 1041:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Water Fangs";
            this->attack = 18;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::blue;
            this->causeDrowning = true;
            this->materials = { 9003, 9102 };
            break;
        case 1042:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Fire Fangs";
            this->attack = 18;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::red;
            this->causeBurnt = true;
            this->materials = { 9003, 9103 };
            break;
        case 1043:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Earth Fangs";
            this->attack = 18;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::brown;
            this->causeRot = true;
            this->materials = { 9003, 9104 };
            break;
        case 1044:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Ice Fangs";
            this->attack = 18;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::cyan;
            this->causeChill = true;
            this->materials = { 9003, 9105 };
            break;
        case 1045:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Air Fangs";
            this->attack = 18;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::orange;
            this->causeInfect = true;
            this->materials = { 9003, 9106 };
            break;
        case 1046:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Electric Tooth";
            this->attack = 22;
            this->thisItemColor = itemColor::yellow;
            this->materials = { 9003, 9204 };
            this->causeShocked = true;
            break;
        case 1047:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Radioactive Tooth";
            this->attack = 22;
            this->thisItemColor = itemColor::magenta;
            this->materials = { 9003, 9203 };
            this->causeUnstable = true;
            break;
        case 1048:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Fallen Tooth";
            this->attack = 22;
            this->thisItemColor = itemColor::purple;
            this->materials = { 9003, 9202 };
            this->causeShaken = true;
            break;
        case 1049:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Charango";
            this->magic = 22;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9108, 9206 };
            break;
        case 1050:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Buteo Beak";
            this->attack = 25;
            this->piercing = 10;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9005 };
            this->causeBleed = true;
            break;
        case 1051:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Woodpecker Beak";
            this->attack = 18;
            this->piercing = 40;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9005 };
            this->causeBleed = true;
            break;
        case 1052:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Electric Eel Tail";
            this->magic = 25;
            this->thisItemColor = itemColor::yellow;
            this->materials = { 9004, 9204 };
            this->causeShocked = true;
            break;
        case 1053:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Radioactive Eel Tail";
            this->magic = 25;
            this->thisItemColor = itemColor::magenta;
            this->materials = { 9004, 9203 };
            this->causeUnstable = true;
            break;
        case 1054:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Fallen Eel Tail";
            this->magic = 25;
            this->thisItemColor = itemColor::purple;
            this->materials = { 9004, 9202 };
            this->causeShaken = true;
            break;
        case 1055:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Snapping Turtle Beak";
            this->attack = 25;
            this->piercing = 25;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005, 9201 };
            this->causeBleed = true;
            break;
        case 1056:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Heron Claw";
            this->attack = 26;
            this->piercing = 15;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9002 };
            this->causeBleed = true;
            break;
        case 1057:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Bear Claw";
            this->attack = 40;
            this->piercing = 5;
            this->materials = { 9002, 9002 };
            this->thisItemColor = itemColor::brown;
            this->causeBleed = true;
            break;
        case 1058:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Baby Bear Claw";
            this->attack = 30;
            this->piercing = 5;
            this->materials = { 9002 };
            this->thisItemColor = itemColor::brown;
            this->causeBleed = true;
            break;
        case 1059:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Fae Cowbell";
            this->magic = 30;
            this->materials = { 9006, 9201 };
            this->cureWilt = true;
            this->cureWither = true;
            break;
        case 1060:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Banhu";
            this->magic = 22;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9108 };
            break;
        case 1061:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Eagle Claw";
            this->attack = 35;
            this->piercing = 10;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9002 };
            this->causeBleed = true;
            this->causeInfect = true;
            break;
        case 1062:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Falcon Claw";
            this->attack = 33;
            this->piercing = 10;
            this->dexterity = 5;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9002 };
            this->causeBleed = true;
            this->causeInfect = true;
            break;
        case 1063:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Merlin Staff";
            this->magic = 30;
            this->dexterity = 5;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9101, 9201 };
            this->causeWilt = true;
            this->cureInfect = true;
            this->cureWilt = true;
            break;
        case 1064:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Icy Claw";
            this->attack = 25;
            this->magic = 10;
            this->piercing = 5;
            this->penetration = 5;
            this->thisItemColor = itemColor::cyan;
            this->materials = { 9002, 9105 };
            this->causeBleed = true;
            this->causeChill = true;
            break;
        case 1065:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Kingfisher Bill";
            this->attack = 35;
            this->piercing = 10;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9003, 9201 };
            this->causeBleed = true;
            break;
        case 1066:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Black Widow Fangs";
            this->attack = 35;
            this->piercing = 8;
            this->thisItemColor = itemColor::red;
            this->materials = { 9004, 9103 };
            this->causeBleed = true;
            this->causeWither = true;
            this->causeBurnt = true;
            this->causeRot = true;
            this->causeInfect = true;
            break;
        case 1067:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Brown Recluse Fangs";
            this->attack = 35;
            this->piercing = 8;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9004, 9104 };
            this->causeBleed = true;
            this->causeWither = true;
            this->causeRot = true;
            this->causeDecay = true;
            this->causeInfect = true;
            break;
        case 1068:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Tarantula Fangs";
            this->attack = 35;
            this->piercing = 8;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9004, 9106 };
            this->causeBleed = true;
            this->causeWither = true;
            this->causeRot = true;
            this->causeInfect = true;
            this->causeDisease = true;
            break;
        case 1069:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Crocodile Tooth";
            this->attack = 45;
            this->magic = 20;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003, 9102 };
            this->causeBleed = true;
            break;
        case 1070:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Alligator Tooth";
            this->attack = 20;
            this->magic = 45;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9003, 9102 };
            this->causeBleed = true;
            break;
        case 1071:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Electric Stinger";
            this->attack = 50;
            this->magic = 25;
            this->thisItemColor = itemColor::yellow;
            this->materials = { 9004, 9204 };
            this->causeShocked = true;
            this->causeParalyzed = true;
            break;
        case 1072:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Radioactive Stinger";
            this->attack = 50;
            this->magic = 25;
            this->thisItemColor = itemColor::magenta;
            this->materials = { 9004, 9203 };
            this->causeUnstable = true;
            this->causeRadioactive = true;
            break;
        case 1073:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Fallen Stinger";
            this->attack = 50;
            this->magic = 25;
            this->thisItemColor = itemColor::purple;
            this->materials = { 9004, 9202 };
            this->causeShaken = true;
            this->causeFallen = true;
            break;
        case 1074:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Bald Eagle Claw";
            this->attack = 45;
            this->piercing = 10;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9002 };
            this->causeBleed = true;
            this->causeInfect = true;
            break;
        case 1075:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Wolf Tooth";
            this->attack = 40;
            this->piercing = 10;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9003 };
            this->causeBleed = true;
            this->causeInfect = true;
            break;
        case 1076:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Alpha Wolf Tooth";
            this->attack = 50;
            this->piercing = 12;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9003 };
            this->causeHemorrhage = true;
            this->causeInfect = true;
            break;
        case 1077:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Fiery Hoof";
            this->attack = 50;
            this->piercing = -10;
            this->thisItemColor = itemColor::red;
            this->materials = { 9005 };
            this->causeBurnt = true;
            break;
        case 1078:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Dirty Hoof";
            this->attack = 50;
            this->piercing = -10;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9005 };
            this->causeInfect = true;
            break;
        case 1079:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Cat Tooth";
            this->attack = 30;
            this->magic = 30;
            this->piercing = 15;
            this->penetration = 15;
            this->materials = { 9003 };
            this->causeBleed = true;
            this->causeWilt = true;
            break;
        case 1080:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Lemming Claw";
            this->attack = 18;
            this->thisItemColor = itemColor::cyan;
            this->materials = { 9002, 9004 };
            this->causeBleed = true;
            break;
        case 1081:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Polar Tooth";
            this->attack = 40;
            this->magic = 30;
            this->thisItemColor = itemColor::cyan;
            this->materials = { 9003, 9105 };
            this->causeBleed = true;
            this->causeChill = true;
            this->causeFrozen = true;
            this->cureChill = true;
            this->cureFrozen = true;
            break;
        case 1082:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Light Wand";
            this->magic = 20;
            this->thisItemColor = itemColor::white;
            this->causeBright = true;
            this->materials = { 9303 };
            break;
        case 1083:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Dark Wand";
            this->magic = 20;
            this->thisItemColor = itemColor::black;
            this->causeObscure = true;
            this->materials = { 9302 };
            break;
        case 1084:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Electricity Wand";
            this->magic = 20;
            this->thisItemColor = itemColor::yellow;
            this->causeShocked = true;
            this->materials = { 9204 };
            break;
        case 1085:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Nuclear Wand";
            this->magic = 20;
            this->thisItemColor = itemColor::magenta;
            this->causeUnstable = true;
            this->materials = { 9203 };
            break;
        case 1086:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Gravity Wand";
            this->magic = 20;
            this->thisItemColor = itemColor::purple;
            this->causeShaken = true;
            this->materials = { 9202 };
            break;
        case 1087:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Light Fangs";
            this->attack = 18;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::white;
            this->causeBright = true;
            this->materials = { 9003, 9303 };
            break;
        case 1088:
            this->thisItemType = itemType::weapon;
            this->itemDimension = 3;
            this->name = "Dark Fangs";
            this->attack = 18;
            this->lifesteal = 0.1;
            this->thisItemColor = itemColor::black;
            this->causeObscure = true;
            this->materials = { 9003, 9302 };
            break;
        
        // Offhand
        case 2001:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 1;
            this->name = "Exoskeleton Shield";
            this->defense = 1;
            this->resist = 1;
            this->materials = { 9005 };
            break;
        case 2002:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 2;
            this->name = "Turtle Shield";
            this->defense = 3;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 2003:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 2;
            this->name = "Rat Claw";
            this->attack = 5;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9002 };
            break;
        case 2004:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 2;
            this->name = "Baby Crocodile Claw";
            this->attack = 6;
            this->magic = 2;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            this->causeBleed = true;
            break;
        case 2005:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 2;
            this->name = "Baby Alligator Claw";
            this->attack = 2;
            this->magic = 6;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            this->causeBleed = true;
            break;
        case 2006:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 2;
            this->name = "Stone Shield";
            this->defense = 3;
            this->dexterity = -5;
            this->materials = { 9101 };
            break;
        case 2007:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Calcite Shield";
            this->defense = 6;
            this->resist = 2;
            this->materials = { 9201 };
            break;
        case 2008:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Silica Shield";
            this->defense = 4;
            this->resist = 4;
            this->materials = { 9205 };
            break;
        case 2009:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Gopher Claw";
            this->attack = 8;
            this->materials = { 9002 };
            this->thisItemColor = itemColor::brown;
            this->causeInfect = true;
            break;
        case 2010:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Crayfish Left Claw";
            this->attack = 6;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            this->causeBleed = true;
            this->causeInfect = true;
            break;
        case 2011:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Shell Shield";
            this->defense = 9;
            this->resist = 7;
            this->dexterity = -5;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005, 9201 };
            break;
        case 2012:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Buteo Claw";
            this->attack = 10;
            this->piercing = 8;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9002 };
            this->causeBleed = true;
            break;
        case 2013:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Turtle Claw";
            this->attack = 7;
            this->piercing = 15;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005, 9201 };
            this->causeBleed = true;
            break;
        case 2014:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Treefrog Foot";
            this->magic = 6;
            this->penetration = 5;
            this->moveSpeed = 0.02;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9004, 9007 };
            this->causeWilt = true;
            break;
        case 2015:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Kingfisher Claw";
            this->attack = 8;
            this->piercing = 5;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9002, 9201 };
            this->causeBleed = true;
            this->causeInfect = true;
            break;
        case 2016:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Crocodile Claw";
            this->attack = 9;
            this->magic = 4;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            this->causeBleed = true;
            break;
        case 2017:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Alligator Claw";
            this->attack = 4;
            this->magic = 9;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            this->causeBleed = true;
            break;
        case 2018:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Eagle Talon";
            this->attack = 8;
            this->piercing = 5;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9002 };
            this->causeBleed = true;
            break;
        case 2019:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Bald Eagle Talon";
            this->attack = 12;
            this->magic = 5;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9002 };
            this->causeBleed = true;
            break;
        case 2020:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Wolf Claw";
            this->attack = 10;
            this->piercing = 5;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9002 };
            this->causeBleed = true;
            break;
        case 2021:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Alpha Wolf Claw";
            this->attack = 15;
            this->piercing = 5;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9002 };
            this->causeHemorrhage = true;
            break;
        case 2022:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Cat Claw";
            this->attack = 10;
            this->magic = 10;
            this->piercing = 5;
            this->penetration = 5;
            this->materials = { 9002 };
            this->causeBleed = true;
            this->causeWilt = true;
            break;
        case 2023:
            this->thisItemType = itemType::offhand;
            this->itemDimension = 3;
            this->name = "Polar Claw";
            this->attack = 12;
            this->magic = 12;
            this->piercing = 5;
            this->penetration = 5;
            this->thisItemColor = itemColor::cyan;
            this->materials = { 9002, 9105 };
            this->causeBleed = true;
            this->causeChill = true;
            this->causeFrozen = true;
            break;

        // Twohand
        case 2501:
            this->thisItemType = itemType::twohand;
            this->itemDimension = 2;
            this->name = "Large Stone";
            this->attack = 12;
            this->dexterity = -5;
            this->materials = { 9101 };
            break;
        case 2502:
            this->thisItemType = itemType::twohand;
            this->itemDimension = 2;
            this->name = "Leo's Swords";
            this->attack = 16;
            this->magic = 16;
            this->piercing = 10;
            this->penetration = 10;
            this->maxEnergy = 30;
            this->maxMana = 30;
            this->thisItemColor = itemColor::blue;
            this->causeDrowning = true;
            this->cureDrowning = true;
            this->materials = { 9101, 9102 };
            break;
        case 2503:
            this->thisItemType = itemType::twohand;
            this->itemDimension = 2;
            this->name = "Raph's Sai";
            this->attack = 20;
            this->magic = 20;
            this->lifesteal = 0.2;
            this->thisItemColor = itemColor::red;
            this->causeBurnt = true;
            this->cureBurnt = true;
            this->materials = { 9101, 9103 };
            break;
        case 2504:
            this->thisItemType = itemType::twohand;
            this->itemDimension = 2;
            this->name = "Don's Bo Staff";
            this->attack = 16;
            this->magic = 16;
            this->defense = 5;
            this->resist = 5;
            this->maxHealth = 30;
            this->thisItemColor = itemColor::purple;
            this->causeShaken = true;
            this->cureShaken = true;
            this->materials = { 9101, 9202 };
            break;
        case 2505:
            this->thisItemType = itemType::twohand;
            this->itemDimension = 2;
            this->name = "Mike's Nunchaku";
            this->attack = 16;
            this->magic = 16;
            this->dexterity = 5;
            this->moveSpeed = 0.05;
            this->thisItemColor = itemColor::orange;
            this->causeInfect = true;
            this->cureInfect = true;
            this->materials = { 9101, 9106 };
            break;
        case 2506:
            this->thisItemType = itemType::twohand;
            this->itemDimension = 3;
            this->name = "Beaver Tail";
            this->attack = 23;
            this->thisItemColor = itemColor::blue;
            this->causeDrowning = true;
            this->cureDrowning = true;
            this->cureDrowned = true;
            this->materials = { 9004, 9004 };
            break;
        case 2507:
            this->thisItemType = itemType::twohand;
            this->itemDimension = 3;
            this->name = "Muskrat Tail";
            this->attack = 20;
            this->thisItemColor = itemColor::blue;
            this->causeDrowning = true;
            this->cureDrowning = true;
            this->cureDrowned = true;
            this->materials = { 9004 };
            break;
        case 2508:
            this->thisItemType = itemType::twohand;
            this->itemDimension = 3;
            this->name = "Peregrine Claws";
            this->attack = 45;
            this->dexterity = 15;
            this->moveSpeed = 0.03;
            this->thisItemColor = itemColor::orange;
            this->causeBleed = true;
            this->causeInfect = true;
            this->materials = { 9002 };
            break;
        case 2509:
            this->thisItemType = itemType::twohand;
            this->itemDimension = 3;
            this->name = "Icy Wisdom";
            this->attack = 38;
            this->magic = 38;
            this->piercing = 10;
            this->penetration = 10;
            this->thisItemColor = itemColor::cyan;
            this->causeChill = true;
            this->materials = { 9105 };
            break;
        case 2510:
            this->thisItemType = itemType::twohand;
            this->itemDimension = 3;
            this->name = "Crayfish King Claws";
            this->attack = 50;
            this->piercing = 10;
            this->thisItemColor = itemColor::blue;
            this->causeBleed = true;
            this->causeInfect = true;
            this->materials = { 9002, 9002 };
            break;
        case 2511:
            this->thisItemType = itemType::twohand;
            this->itemDimension = 3;
            this->name = "Boar Tusk";
            this->attack = 60;
            this->piercing = 10;
            this->thisItemColor = itemColor::brown;
            this->causeBleed = true;
            this->causeRot = true;
            this->materials = { 9005 };
            break;
        
        // Headgear
        case 3001:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 2;
            this->name = "Slime Hat";
            this->defense = 2;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9107 };
            break;
        case 3002:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 2;
            this->name = "Turtle Hat";
            this->defense = 4;
            this->dexterity = -10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 3003:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 2;
            this->name = "Rat Hair Hat";
            this->defense = 2;
            this->dexterity = 5;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9002 };
            break;
        case 3004:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 2;
            this->name = "Croc Hide Hat";
            this->defense = 3;
            this->resist = 1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9108 };
            break;
        case 3005:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 2;
            this->name = "Gator Hide Hat";
            this->defense = 1;
            this->resist = 3;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9108 };
            break;
        case 3006:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 2;
            this->name = "Blue Mask";
            this->resist = 3;
            this->thisItemColor = itemColor::blue;
            this->causeDrowning = true;
            this->materials = { 9102 };
            break;
        case 3007:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 2;
            this->name = "Red Mask";
            this->resist = 3;
            this->thisItemColor = itemColor::red;
            this->causeBurnt = true;
            this->materials = { 9103 };
            break;
        case 3008:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 2;
            this->name = "Purple Mask";
            this->resist = 3;
            this->thisItemColor = itemColor::purple;
            this->causeUnstable = true;
            this->materials = { 9202 };
            break;
        case 3009:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 2;
            this->name = "Orange Mask";
            this->resist = 3;
            this->thisItemColor = itemColor::orange;
            this->causeInfect = true;
            this->materials = { 9106 };
            break;
        case 3010:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 1;
            this->name = "Exoskeleton Helmet";
            this->defense = 1;
            this->resist = 1;
            this->materials = { 9005 };
            break;
        case 3011:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 2;
            this->name = "Stone Helmet";
            this->defense = 3;
            this->dexterity = -5;
            this->materials = { 9101 };
            break;
        case 3012:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Stonefly Head";
            this->defense = 3;
            this->resist = 3;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9005 };
            break;
        case 3013:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Damselfly Antennae";
            this->dexterity = 3;
            this->viewDistance = 0.05;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9004 };
            break;
        case 3014:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Calcite Helmet";
            this->defense = 6;
            this->resist = 2;
            this->materials = { 9201 };
            break;
        case 3015:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Silica Helmet";
            this->defense = 4;
            this->resist = 4;
            this->materials = { 9205 };
            break;
        case 3016:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Rat Hide Hat";
            this->defense = 7;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9108 };
            break;
        case 3017:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Antlers";
            this->defense = 7;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9005, 9201 };
            break;
        case 3018:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Ant Helmet";
            this->defense = 3;
            this->resist = 3;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 3019:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Crayfish Helmet";
            this->defense = 8;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 3020:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Fire Ant Helmet";
            this->defense = 3;
            this->resist = 3;
            this->thisItemColor = itemColor::red;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 3021:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Shell Hat";
            this->defense = 7;
            this->resist = 5;
            this->dexterity = -5;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005, 9201 };
            break;
        case 3022:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Snood";
            this->dexterity = 10;
            this->monsterSpawn = 1.5;
            this->thisItemColor = itemColor::brown;
            this->cureInfect = true;
            this->cureRot = true;
            this->materials = { 9004 };
            break;
        case 3023:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Armadillo Helmet";
            this->defense = 6;
            this->resist = 6;
            this->thisItemColor = itemColor::brown;
            this->causeDefend = true;
            this->materials = { 9002, 9108 };
            break;
        case 3024:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Vulture Crown";
            this->defense = 10;
            this->resist = 10;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9101, 9201 };
            break;
        case 3025:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Wart Helmet";
            this->defense = 12;
            this->resist = 8;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9108, 9007 };
            this->selfInfect = true;
            break;
        case 3026:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Ant Queen Helmet";
            this->defense = 7;
            this->resist = 7;
            this->thisItemColor = itemColor::red;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 3027:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Croc Scale Hat";
            this->defense = 9;
            this->resist = 3;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002, 9201 };
            break;
        case 3028:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Gator Scale Hat";
            this->defense = 3;
            this->resist = 9;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002, 9201 };
            break;
        case 3029:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Crayfish King Helmet";
            this->defense = 14;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 3030:
            this->thisItemType = itemType::headgear;
            this->itemDimension = 3;
            this->name = "Great Antlers";
            this->defense = 12;
            this->resist = 2;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9005, 9201 };
            break;
        
        // Armor
        case 4001:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 1;
            this->name = "Housefly Wings";
            this->dexterity = 6;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9004 };
            break;
        case 4002:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 1;
            this->name = "Baby Snail Shell";
            this->defense = 2;
            this->dexterity = -10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 4003:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 1;
            this->name = "Snail Shell";
            this->defense = 3;
            this->dexterity = -10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 4004:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Slime Shirt";
            this->defense = 2;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9107 };
            break;
        case 4005:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Flea Wings";
            this->dexterity = 5;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9004 };
            break;
        case 4006:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Gnat Wings";
            this->dexterity = 8;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9004 };
            break;
        case 4007:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Fly Wings";
            this->dexterity = 10;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9004 };
            break;
        case 4008:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Baby Turtle Shell";
            this->defense = 6;
            this->dexterity = -15;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 4009:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Turtle Shell";
            this->defense = 10;
            this->dexterity = -20;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 4010:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Rat Hair Coat";
            this->defense = 2;
            this->dexterity = 5;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9002 };
            break;
        case 4011:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Rat Skin Coat";
            this->defense = 4;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9108 };
            break;
        case 4012:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Croc Hide Coat";
            this->defense = 4;
            this->resist = 2;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9108 };
            break;
        case 4013:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Gator Hide Coat";
            this->defense = 2;
            this->resist = 4;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9108 };
            break;
        case 4014:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Leo's Shell";
            this->defense = 5;
            this->resist = 5;
            this->piercing = 8;
            this->penetration = 8;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9101, 9102 };
            break;
        case 4015:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Raph's Shell";
            this->defense = 5;
            this->resist = 5;
            this->attack = 3;
            this->magic = 3;
            this->thisItemColor = itemColor::red;
            this->materials = { 9101, 9103 };
            break;
        case 4016:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Don's Shell";
            this->defense = 8;
            this->resist = 8;
            this->thisItemColor = itemColor::purple;
            this->materials = { 9101, 9202 };
            break;
        case 4017:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Mike's Shell";
            this->defense = 5;
            this->resist = 5;
            this->dexterity = 10;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9101, 9106 };
            break;
        case 4018:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 1;
            this->name = "Exoskeleton Armor";
            this->defense = 1;
            this->resist = 1;
            this->materials = { 9005 };
            break;
        case 4019:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 2;
            this->name = "Stone Armor";
            this->defense = 3;
            this->dexterity = -5;
            this->materials = { 9101 };
            break;
        case 4020:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Dragonfly Wings";
            this->dexterity = 20;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9004 };
            break;
        case 4021:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Midges Wings";
            this->dexterity = 10;
            this->magic = 5;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9004 };
            break;
        case 4022:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Stonefly Thorax";
            this->defense = 4;
            this->resist = 4;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9005 };
            break;
        case 4023:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Butterfly Wings";
            this->dexterity = 10;
            this->luckFactor = 1.1;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9005 };
            break;
        case 4024:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Pond Snail Shell";
            this->defense = 8;
            this->dexterity = -15;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 4025:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Calcite Armor";
            this->defense = 7;
            this->resist = 3;
            this->materials = { 9201 };
            break;
        case 4026:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Silica Armor";
            this->defense = 5;
            this->resist = 5;
            this->materials = { 9205 };
            break;
        case 4027:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Rat Hide Coat";
            this->defense = 8;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9108 };
            break;
        case 4028:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Ant Armor";
            this->defense = 4;
            this->resist = 4;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 4029:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Monarch Wings";
            this->dexterity = 12;
            this->luckFactor = 1.3;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9005 };
            break;
        case 4030:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Crayfish Armor";
            this->defense = 10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 4031:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Fire Ant Armor";
            this->defense = 4;
            this->resist = 4;
            this->thisItemColor = itemColor::red;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 4032:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Shell Armor";
            this->defense = 9;
            this->resist = 7;
            this->dexterity = -5;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005, 9201 };
            break;
        case 4033:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Armadillo Armor";
            this->defense = 6;
            this->resist = 6;
            this->thisItemColor = itemColor::brown;
            this->causeDefend = true;
            this->materials = { 9002, 9108 };
            break;
        case 4034:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Falcon Wings";
            this->dexterity = 20;
            this->moveSpeed = 0.05;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9002, 9004 };
            break;
        case 4035:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Bear Hide";
            this->defense = 12;
            this->resist = 4;
            this->materials = { 9108, 9108, 9002 };
            break;
        case 4036:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Wart Armor";
            this->defense = 12;
            this->resist = 8;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9108, 9007 };
            this->selfInfect = true;
            break;
        case 4037:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Eagle Wings";
            this->defense = 4;
            this->resist = 3;
            this->dexterity = 15;
            this->moveSpeed = 0.05;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9002, 9004 };
            break;
        case 4038:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Ant Queen Armor";
            this->defense = 9;
            this->resist = 9;
            this->thisItemColor = itemColor::red;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 4039:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Croc Scale Coat";
            this->defense = 12;
            this->resist = 4;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002, 9201 };
            break;
        case 4040:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Gator Scale Coat";
            this->defense = 4;
            this->resist = 12;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002, 9201 };
            break;
        case 4041:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Crayfish Armor";
            this->defense = 15;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 4042:
            this->thisItemType = itemType::chestgear;
            this->itemDimension = 3;
            this->name = "Yeti Coat";
            this->defense = 15;
            this->resist = 15;
            this->thisItemColor = itemColor::cyan;
            this->materials = { 9108, 9102, 9105 };
            this->cureChill = true;
            this->cureDrowning = true;
            this->cureBleed = true;
            this->cureWilt = true;
            this->cureChill = true;
            this->cureFrozen = true;
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        
        // Leggear
        case 5001:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 2;
            this->name = "Slime Pants";
            this->defense = 2;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9107 };
            break;
        case 5002:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 2;
            this->name = "Shell Pants";
            this->defense = 4;
            this->dexterity = -10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 5003:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 2;
            this->name = "Rat Hair Pants";
            this->defense = 2;
            this->dexterity = 5;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9002 };
            break;
        case 5004:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 2;
            this->name = "Croc Hide Pants";
            this->defense = 3;
            this->dexterity = 1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9108 };
            break;
        case 5005:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 2;
            this->name = "Gator Hide Pants";
            this->defense = 1;
            this->resist = 3;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9108 };
            break;
        case 5006:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 2;
            this->name = "Leo's Pants";
            this->defense = 3;
            this->resist = 3;
            this->piercing = 4;
            this->penetration = 4;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9101, 9102 };
            break;
        case 5007:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 2;
            this->name = "Raph's Pants";
            this->defense = 3;
            this->resist = 3;
            this->attack = 2;
            this->magic = 2;
            this->thisItemColor = itemColor::red;
            this->materials = { 9101, 9103 };
            break;
        case 5008:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 2;
            this->name = "Don's Pants";
            this->defense = 5;
            this->resist = 5;
            this->thisItemColor = itemColor::purple;
            this->materials = { 9101, 9202 };
            break;
        case 5009:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 2;
            this->name = "Mike's Pants";
            this->defense = 3;
            this->resist = 3;
            this->dexterity = 6;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9101, 9106 };
            break;
        case 5010:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 1;
            this->name = "Exoskeleton Pants";
            this->defense = 1;
            this->resist = 1;
            this->materials = { 9005 };
            break;
        case 5011:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 2;
            this->name = "Stone Pants";
            this->defense = 3;
            this->dexterity = -5;
            this->materials = { 9101 };
            break;
        case 5012:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 3;
            this->name = "Stonefly Abdomen";
            this->defense = 3;
            this->resist = 3;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9005 };
            break;
        case 5013:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 3;
            this->name = "Calcite Leggings";
            this->defense = 6;
            this->resist = 2;
            this->materials = { 9201 };
            break;
        case 5014:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 3;
            this->name = "Silica Leggins";
            this->defense = 4;
            this->resist = 4;
            this->materials = { 9205 };
            break;
        case 5015:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 3;
            this->name = "Rat Hide Pants";
            this->defense = 7;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9108 };
            break;
        case 5016:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 3;
            this->name = "Ant Leggings";
            this->defense = 3;
            this->resist = 3;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 5017:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 3;
            this->name = "Fire Ant Leggings";
            this->defense = 3;
            this->resist = 3;
            this->thisItemColor = itemColor::red;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 5018:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 3;
            this->name = "Shell Leggings";
            this->defense = 8;
            this->resist = 6;
            this->dexterity = -5;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005, 9201 };
            break;
        case 5019:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 3;
            this->name = "Armadillo Leggings";
            this->defense = 6;
            this->resist = 6;
            this->thisItemColor = itemColor::brown;
            this->causeDefend = true;
            this->materials = { 9002, 9108 };
            break;
        case 5020:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 3;
            this->name = "Ant Queen Leggings";
            this->defense = 7;
            this->resist = 7;
            this->thisItemColor = itemColor::red;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 5021:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 3;
            this->name = "Croc Scale Pants";
            this->defense = 9;
            this->dexterity = 3;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002, 9201 };
            break;
        case 5022:
            this->thisItemType = itemType::leggear;
            this->itemDimension = 3;
            this->name = "Gator Scale Pants";
            this->defense = 3;
            this->resist = 9;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002, 9201 };
            break;

        // Footgear
        case 6001:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 2;
            this->name = "Slime Shoes";
            this->defense = 2;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9107 };
            break;
        case 6002:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 2;
            this->name = "Shell Shoes";
            this->defense = 4;
            this->dexterity = -10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9005 };
            break;
        case 6003:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 2;
            this->name = "Rat Hair Shoes";
            this->defense = 2;
            this->dexterity = 5;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9002 };
            break;
        case 6004:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 2;
            this->name = "Croc Hide Shoes";
            this->defense = 3;
            this->resist = 1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9105 };
            break;
        case 6005:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 2;
            this->name = "Gator Hide Shoes";
            this->defense = 1;
            this->resist = 3;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9105 };
            break;
        case 6006:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 2;
            this->name = "Leo's Shoes";
            this->defense = 3;
            this->resist = 3;
            this->piercing = 4;
            this->penetration = 4;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9101, 9102 };
            break;
        case 6007:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 2;
            this->name = "Raph's Shoes";
            this->defense = 3;
            this->resist = 3;
            this->attack = 2;
            this->magic = 2;
            this->thisItemColor = itemColor::red;
            this->materials = { 9101, 9103 };
            break;
        case 6008:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 2;
            this->name = "Don's Shoes";
            this->defense = 5;
            this->resist = 5;
            this->thisItemColor = itemColor::purple;
            this->materials = { 9101, 9202 };
            break;
        case 6009:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 2;
            this->name = "Mike's Shoes";
            this->defense = 3;
            this->resist = 3;
            this->dexterity = 6;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9101, 9106 };
            break;
        case 6010:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 1;
            this->name = "Exoskeleton Shoes";
            this->defense = 1;
            this->resist = 1;
            this->materials = { 9005 };
            break;
        case 6011:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 2;
            this->name = "Stone Shoes";
            this->defense = 3;
            this->dexterity = -5;
            this->materials = { 9101 };
            break;
        case 6012:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Damselfly Claw";
            this->defense = 3;
            this->attack = 3;
            this->materials = { 9002 };
            break;
        case 6013:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Calcite Boots";
            this->defense = 6;
            this->resist = 2;
            this->materials = { 9201 };
            break;
        case 6014:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Silica Boots";
            this->defense = 4;
            this->resist = 4;
            this->materials = { 9205 };
            break;
        case 6015:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Rat Hide Shoes";
            this->defense = 3;
            this->dexterity = 10;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9108 };
            break;
        case 6016:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Jackalope Foot";
            this->resist = 4;
            this->dexterity = 10;
            this->thisItemColor = itemColor::brown;
            this->causeSwiftness = true;
            this->materials = { 9004 };
            break;
        case 6017:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Ant Boots";
            this->defense = 3;
            this->resist = 3;
            this->thisItemColor = itemColor::brown;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 6018:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Salamander Toes";
            this->defense = 2;
            this->resist = 2;
            this->moveSpeed = 0.03;
            this->materials = { 9109 };
            this->causeWilt = true;
            break;
        case 6019:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Fire Ant Boots";
            this->defense = 3;
            this->resist = 3;
            this->thisItemColor = itemColor::red;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 6020:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Armadillo Boots";
            this->defense = 6;
            this->resist = 6;
            this->thisItemColor = itemColor::brown;
            this->causeDefend = true;
            this->materials = { 9002, 9108 };
            break;
        case 6021:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Zygodactyl Claws";
            this->attack = 6;
            this->piercing = 10;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9002 };
            break;
        case 6022:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Rabbit Foot";
            this->defense = 4;
            this->dexterity = 10;
            this->thisItemColor = itemColor::brown;
            this->causeSwiftness = true;
            this->materials = { 9004 };
            break;
        case 6023:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Snakeskin Shoes";
            this->defense = 4;
            this->resist = 4;
            this->thisItemColor = itemColor::brown;
            this->causeSwiftness = true;
            this->materials = { 9108 };
            break;
        case 6024:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Ant Queen Boots";
            this->defense = 7;
            this->resist = 7;
            this->thisItemColor = itemColor::red;
            this->materials = { 9005 };
            this->causeDefend = true;
            this->causeResolve = true;
            break;
        case 6025:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Croc Scale Shoes";
            this->defense = 9;
            this->resist = 3;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002, 9201 };
            break;
        case 6026:
            this->thisItemType = itemType::footgear;
            this->itemDimension = 3;
            this->name = "Gator Scale Shoes";
            this->defense = 3;
            this->resist = 9;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002, 9201 };
            break;

        // Accessory
        case 7001:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Soft Fish Scale";
            this->defense = 1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            break;
        case 7002:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Soft Fish Fin";
            this->dexterity = 3;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004 };
            break;
        case 7003:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Fish Scale";
            this->defense = 2;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            break;
        case 7004:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Hermit Crab Scale";
            this->attack = 1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            break;
        case 7005:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Housefly Wing";
            this->dexterity = 6;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9004 };
            break;
        case 7006:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Betta Fin";
            this->dexterity = 3;
            this->attack = 1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004 };
            break;
        case 7007:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Betta Scale";
            this->defense = 1;
            this->attack = 1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            break;
        case 7008:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Dwarf Frog Eye";
            this->viewDistance = 0.03;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004, 9007 };
            break;
        case 7009:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Dwarf Frog Vocal Chord";
            this->monsterSpawn = 1.1;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004, 9007 };
            break;
        case 7010:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Lily Pad Fragment";
            this->luckFactor = 1.05;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004 };
            break;
        case 7011:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Rainbow Shark Fin";
            this->dexterity = 4;
            this->piercing = 5;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004 };
            break;
        case 7012:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Rainbow Shark Scale";
            this->defense = 2;
            this->piercing = 5;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            break;
        case 7013:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Toxic Fish Fin";
            this->dexterity = 10;
            this->piercing = 5;
            this->maxHealth = -10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9109 };
            break;
        case 7014:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Toxic Fish Scale";
            this->defense = 3;
            this->piercing = 5;
            this->maxHealth = -10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9110 };
            break;
        case 7015:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Insect Leg";
            this->moveSpeed = 0.02;
            this->materials = { 9004 };
            break;
        case 7016:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Insect Legs";
            this->moveSpeed = 0.04;
            this->materials = { 9004 };
            break;
        case 7017:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Catfish Barbel";
            this->viewDistance = 0.05;
            this->moveSpeed = 0.01;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004 };
            break;
        case 7018:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Reptile Scale";
            this->attack = 3;
            this->piercing = 5;
            this->materials = { 9002 };
            break;
        case 7019:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Reptile Pendant";
            this->magic = 3;
            this->penetration = 5;
            this->materials = { 9006 };
            break;
        case 7020:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Turtle Pendant";
            this->resist = 5;
            this->thisItemColor = itemColor::blue;
            break;
        case 7021:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Algae Pendant";
            this->luckFactor = 1.1;
            this->monsterSpawn = 1.1;
            this->materials = { 9107 };
            break;
        case 7022:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Worm Chief Pendant";
            this->maxEnergy = 10;
            this->maxMana = 10;
            this->materials = { 9006 };
            break;
        case 7023:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Growth Pendant";
            this->causeGrow = true;
            break;
        case 7024:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Strength Pendant";
            this->causeStrength = true;
            break;
        case 7025:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Cogent Pendant";
            this->causeCogent = true;
            break;
        case 7026:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Defense Pendant";
            this->causeDefend = true;
            break;
        case 7027:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Resolve Pendant";
            this->causeResolve = true;
            break;
        case 7028:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Swiftness Pendant";
            this->causeSwiftness = true;
            break;
        case 7029:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Weakness Pendant";
            this->causeWeak = true;
            break;
        case 7030:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Inept Pendant";
            this->causeInept = true;
            break;
        case 7031:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Break Pendant";
            this->causeBreak = true;
            break;
        case 7032:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Outwill Pendant";
            this->causeOutwill = true;
            break;
        case 7033:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 2;
            this->name = "Slowness Pendant";
            this->causeSlowness = true;
            break;
        case 7034:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Bluegill Fin";
            this->dexterity = 15;
            this->monsterSpawn = 1.1;
            this->materials = { 9004 };
            break;
        case 7035:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Pond Algae Pendant";
            this->luckFactor = 1.2;
            this->monsterSpawn = 1.2;
            this->materials = { 9107 };
            break;
        case 7036:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Blue Feather";
            this->dexterity = 10;
            this->thisItemColor = itemColor::blue;
            this->causeDrowning = true;
            this->materials = { 9002 };
            break;
        case 7037:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Red Feather";
            this->dexterity = 10;
            this->thisItemColor = itemColor::red;
            this->causeBurnt = true;
            this->materials = { 9002 };
            break;
        case 7038:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Brown Feather";
            this->dexterity = 10;
            this->thisItemColor = itemColor::brown;
            this->causeRot = true;
            this->materials = { 9002 };
            break;
        case 7039:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Cyan Feather";
            this->dexterity = 10;
            this->thisItemColor = itemColor::cyan;
            this->causeChill = true;
            this->materials = { 9002 };
            break;
        case 7040:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Orange Feather";
            this->dexterity = 10;
            this->thisItemColor = itemColor::orange;
            this->causeInfect = true;
            this->materials = { 9002 };
            break;
        case 7041:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Purple Feather";
            this->dexterity = 10;
            this->thisItemColor = itemColor::purple;
            this->causeShaken = true;
            this->materials = { 9002 };
            break;
        case 7042:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Yellow Feather";
            this->dexterity = 10;
            this->thisItemColor = itemColor::yellow;
            this->causeShocked = true;
            this->materials = { 9002 };
            break;
        case 7043:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Magenta Feather";
            this->dexterity = 10;
            this->thisItemColor = itemColor::magenta;
            this->causeUnstable = true;
            this->materials = { 9002 };
            break;
        case 7044:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Black Feather";
            this->dexterity = 10;
            this->thisItemColor = itemColor::black;
            this->causeHidden = true;
            this->materials = { 9002 };
            break;
        case 7045:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "White Feather";
            this->dexterity = 10;
            this->thisItemColor = itemColor::white;
            this->causeBright = true;
            this->materials = { 9002 };
            break;
        case 7046:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Green Feather";
            this->dexterity = 10;
            this->thisItemColor = itemColor::green;
            //this->causeBalance = true;
            this->materials = { 9002 };
            break;
        case 7047:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Bullfrog Eye";
            this->viewDistance = 0.06;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004, 9007 };
            break;
        case 7048:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 1;
            this->name = "Bullfrog Vocal Chord";
            this->monsterSpawn = 1.5;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004, 9007 };
            break;
        case 7049:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Lily Pad Piece";
            this->luckFactor = 1.3;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004 };
            break;
        case 7050:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Ant Pheromones";
            this->monsterSpawn = 1.5;
            break;
        case 7051:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Catfish Barbels";
            this->viewDistance = 0.1;
            this->moveSpeed = 0.03;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004 };
            break;
        case 7052:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Fish Fins";
            this->dexterity = 12;
            this->piercing = 10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9109 };
            break;
        case 7053:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Fish Scales";
            this->defense = 8;
            this->piercing = 10;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9110 };
            break;
        case 7054:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Ancient Fin";
            this->dexterity = 12;
            this->penetration = 12;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9004 };
            break;
        case 7055:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Ancient Scale";
            this->defense = 8;
            this->penetration = 12;
            this->thisItemColor = itemColor::blue;
            this->materials = { 9002 };
            break;
        case 7056:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Ladybug Pendant";
            this->luckFactor = 1.5;
            break;
        case 7057:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Electric Fin";
            this->dexterity = 10;
            this->piercing = 10;
            this->penetration = 10;
            this->thisItemColor = itemColor::yellow;
            this->causeShocked = true;
            this->materials = { 9004, 9204 };
            break;
        case 7058:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Electric Scale";
            this->defense = 7;
            this->resist = 7;
            this->piercing = 10;
            this->penetration = 10;
            this->thisItemColor = itemColor::yellow;
            this->cureShocked = true;
            this->materials = { 9002, 9204 };
            break;
        case 7059:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Radioactive Fin";
            this->dexterity = 10;
            this->piercing = 10;
            this->penetration = 10;
            this->thisItemColor = itemColor::magenta;
            this->causeUnstable = true;
            this->materials = { 9004, 9203 };
            break;
        case 7060:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Radioactive Scale";
            this->defense = 7;
            this->resist = 7;
            this->piercing = 10;
            this->penetration = 10;
            this->thisItemColor = itemColor::magenta;
            this->cureUnstable = true;
            this->materials = { 9002, 9203 };
            break;
        case 7061:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Fallen Fin";
            this->dexterity = 10;
            this->piercing = 10;
            this->penetration = 10;
            this->thisItemColor = itemColor::purple;
            this->causeShaken = true;
            this->materials = { 9004, 9202 };
            break;
        case 7062:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Fallen Scale";
            this->defense = 7;
            this->resist = 7;
            this->piercing = 10;
            this->penetration = 10;
            this->thisItemColor = itemColor::purple;
            this->cureShaken = true;
            this->materials = { 9002, 9204 };
            break;
        case 7063:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Falcon Eye";
            this->viewDistance = 0.2;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9204 };
            break;
        case 7064:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Peacock Pendant";
            this->monsterSpawn = 2.0;
            break;
        case 7065:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Deer Tail";
            this->monsterSpawn = 0.2;
            this->moveSpeed = 0.02;
            break;
        case 7066:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Snakeskin Belt";
            this->defense = 3;
            this->resist = 3;
            this->thisItemColor = itemColor::brown;
            this->cureInfect = true;
            this->causeInfect = true;
            break;
        case 7067:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Chucked Wood";
            this->causeBreak = true;
            break;
        case 7077:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Wart";
            this->causeInfect = true;
            break;
        case 7078:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Treefrog Vocal Chord";
            this->monsterSpawn = 1.6;
            break;
        case 7079:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Eagle Eye";
            this->viewDistance = 0.18;
            this->thisItemColor = itemColor::orange;
            this->materials = { 9204 };
            break;
        case 7080:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Reptilian Scale";
            this->attack = 7;
            this->piercing = 5;
            this->materials = { 9002 };
            break;
        case 7081:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Reptilian Pendant";
            this->magic = 7;
            this->penetration = 5;
            this->materials = { 9006 };
            break;
        case 7082:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Wolf Charm";
            this->resist = 10;
            this->materials = { 9206 };
            this->cureBleed = true;
            this->cureHemorrhage = true;
            this->cureWilt = true;
            this->cureWither = true;
            break;
        case 7083:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Lucky Horseshoe";
            this->luckFactor = 2.0;
            this->moveSpeed = -0.03;
            break;
        case 7085:
            this->thisItemType = itemType::accessory;
            this->itemDimension = 3;
            this->name = "Rattle";
            this->monsterSpawn = 0.5;
            this->causeRot = true;
            this->cureRot = true;
            break;
        
        // material
        case 9001:
            this->thisItemType = itemType::material;
            this->itemDimension = 1;
            this->name = "Talc";
            break;
        case 9002:
            this->thisItemType = itemType::material;
            this->itemDimension = 1;
            this->name = "Keratin";
            break;
        case 9003:
            this->thisItemType = itemType::material;
            this->itemDimension = 1;
            this->name = "Enamel";
            break;
        case 9004:
            this->thisItemType = itemType::material;
            this->itemDimension = 1;
            this->name = "Tissue";
            break;
        case 9005:
            this->thisItemType = itemType::material;
            this->itemDimension = 1;
            this->name = "Bone";
            break;
        case 9006:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Fae Stone";
            break;
        case 9007:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Frog Stone";
            break;
        case 9101:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Gypsum";
            break;
        case 9102:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Water Stone";
            this->thisItemColor = itemColor::blue;
            break;
        case 9103:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Fire Stone";
            this->thisItemColor = itemColor::red;
            break;
        case 9104:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Earth Stone";
            this->thisItemColor = itemColor::brown;
            break;
        case 9105:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Ice Stone";
            this->thisItemColor = itemColor::cyan;
            break;
        case 9106:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Air Stone";
            this->thisItemColor = itemColor::orange;
            break;
        case 9107:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Slime Stone";
            break;
        case 9108:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Leather";
            break;
        case 9109:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Toxic Tissue";
            break;
        case 9110:
            this->thisItemType = itemType::material;
            this->itemDimension = 2;
            this->name = "Toxic Keratin";
            break;
        case 9201:
            this->thisItemType = itemType::material;
            this->itemDimension = 3;
            this->name = "Calcite";
            break;
        case 9202:
            this->thisItemType = itemType::material;
            this->itemDimension = 3;
            this->name = "Gravity Stone";
            this->thisItemColor = itemColor::purple;
            break;
        case 9203:
            this->thisItemType = itemType::material;
            this->itemDimension = 3;
            this->name = "Nuclear Stone";
            this->thisItemColor = itemColor::magenta;
            break;
        case 9204:
            this->thisItemType = itemType::material;
            this->itemDimension = 3;
            this->name = "Electricity Stone";
            this->thisItemColor = itemColor::yellow;
            break;
        case 9205:
            this->thisItemType = itemType::material;
            this->itemDimension = 3;
            this->name = "Silica";
            break;
        case 9206:
            this->thisItemType = itemType::material;
            this->itemDimension = 3;
            this->name = "Wood";
            break;
        case 9301:
            this->thisItemType = itemType::material;
            this->itemDimension = 4;
            this->name = "Fluorite";
            break;
        case 9302:
            this->thisItemType = itemType::material;
            this->itemDimension = 4;
            this->name = "Darkstone";
            this->thisItemColor = itemColor::black;
            break;
        case 9303:
            this->thisItemType = itemType::material;
            this->itemDimension = 4;
            this->name = "Lightstone";
            this->thisItemColor = itemColor::white;
            break;
        case 9401:
            this->thisItemType = itemType::material;
            this->itemDimension = 5;
            this->name = "Apatite";
            break;
        case 9501:
            this->thisItemType = itemType::material;
            this->itemDimension = 6;
            this->name = "Orthoclase";
            break;
        case 9601:
            this->thisItemType = itemType::material;
            this->itemDimension = 7;
            this->name = "Quartz";
            break;
        case 9701:
            this->thisItemType = itemType::material;
            this->itemDimension = 8;
            this->name = "Topaz";
            break;
        case 9801:
            this->thisItemType = itemType::material;
            this->itemDimension = 9;
            this->name = "Corundum";
            break;
        case 9901:
            this->thisItemType = itemType::material;
            this->itemDimension = 10;
            this->name = "Diamond";
            break;
        
        default:
            std::cout << "ERROR: item ID " << itemID << " not found.\n";
            break;
    }
    if ((this->thisItemType != itemType::consumable) && (this->thisItemType != itemType::none) && (this->thisItemType != itemType::material) && (!forceNormalQuality)) {
        this->randomizeQuality(playerLuckFactor);
    }
}

std::string Item::getName() {
    std::string displayName{ this->name };
    switch (this->itemLevel) {
        case 1:
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            displayName += " (level " + std::to_string(this->itemLevel) + ")";
            break;
        case 11:
            displayName = "Masterforged " + displayName;
            break;
    }
    switch (this->thisItemQuality) {
        case itemQuality::defective:
            displayName = "Defective " + displayName;
            break;
        case itemQuality::inferior:
            displayName = "Inferior " + displayName;
            break;
        case itemQuality::normal:
            break;
        case itemQuality::superior:
            displayName = "Superior " + displayName;
            break;
        case itemQuality::rare:
            displayName = "Rare " + displayName;
            break;
        case itemQuality::exquisite:
            displayName = "Exquisite " + displayName;
            break;
        case itemQuality::legendary:
            displayName = "Legendary " + displayName;
            break;
        case itemQuality::perfect:
            displayName = "Perfect " + displayName;
            break;
        default:
            std::cout << "ERROR: item quality unknown.\n";
    }
    if (this->stack > 1) {
        displayName += " (x" + std::to_string(this->stack) + ")";
    }
    return displayName;
}

bool Item::isStackable() {
    if (this->isConsumable() || this->isMaterial()) {
        return true;
    }
    return false;
}

// Given price factor return material cost
int Item::getMatUpgradeCost(double priceFactor) {
    double baseAmount{};
    switch (this->itemLevel) {
    case 1:
        baseAmount = 2;
        break;
    case 2:
        baseAmount = 4;
        break;
    case 3:
        baseAmount = 7;
        break;
    case 4:
        baseAmount = 11;
        break;
    case 5:
        baseAmount = 16;
        break;
    case 6:
        baseAmount = 22;
        break;
    case 7:
        baseAmount = 29;
        break;
    case 8:
        baseAmount = 37;
        break;
    case 9:
        baseAmount = 46;
        break;
    case 10:
        baseAmount = 100;
        break;
    default:
        std::cout << "ERROR: Item with level " << this->itemLevel << " not upgradable.\n";
        break;
    }
    return static_cast<int>(std::round(baseAmount * priceFactor));
}

// Function randomizing drop quality of item
// NOTE: move magic numbers to global variables namespace (?)
void Item::randomizeQuality(double luckFactor) {
    if (luckFactor == 0) {
        std::cout << "ERROR: Luck factor is 0. Will set to 1.0.\n";
        luckFactor = constants::defaultLuckFactor;
    }
    if (core_functions::linearProbability(0.001 * luckFactor)) {
        this->thisItemQuality = itemQuality::perfect;
        this->multiplyStats(core_functions::randomDouble(1.81, 2.0));
    }
    else if (core_functions::linearProbability(0.004 * luckFactor)) {
        this->thisItemQuality = itemQuality::legendary;
        this->multiplyStats(core_functions::randomDouble(1.61, 1.8));
    }
    else if (core_functions::linearProbability(0.015 * luckFactor)) {
        this->thisItemQuality = itemQuality::exquisite;
        this->multiplyStats(core_functions::randomDouble(1.41, 1.6));
    }
    else if (core_functions::linearProbability(0.05 * luckFactor)) {
        this->thisItemQuality = itemQuality::rare;
        this->multiplyStats(core_functions::randomDouble(1.21, 1.4));
    }
    else if (core_functions::linearProbability(0.15 * luckFactor)) {
        this->thisItemQuality = itemQuality::superior;
        this->multiplyStats(core_functions::randomDouble(1.01, 1.2));
    }
    else if (core_functions::linearProbability(0.15 / luckFactor)) {
        this->thisItemQuality = itemQuality::inferior;
        this->multiplyStats(core_functions::randomDouble(0.8, 0.99));
    }
    else if (core_functions::linearProbability(0.05 / luckFactor)) {
        this->thisItemQuality = itemQuality::defective;
        this->multiplyStats(core_functions::randomDouble(0.6, 0.79));
    }
    else {
        this->thisItemQuality = itemQuality::normal;
    }
}

// Multiply weapon stats given the multiplicative factor
void Item::multiplyStats(double factor) {
    this->maxEnergy = static_cast<int>(std::round(factor * this->maxEnergy));
    this->maxMana = static_cast<int>(std::round(factor * this->maxMana));
    this->maxHealth = static_cast<int>(std::round(factor * this->maxHealth));
    this->attack = static_cast<int>(std::round(factor * this->attack));
    this->magic = static_cast<int>(std::round(factor * this->magic));
    this->defense = static_cast<int>(std::round(factor * this->defense));
    this->resist = static_cast<int>(std::round(factor * this->resist));
    this->piercing = static_cast<int>(std::round(factor * this->piercing));
    this->penetration = static_cast<int>(std::round(factor * this->penetration));
    this->dexterity = static_cast<int>(std::round(factor * this->dexterity));
    this->viewDistance *= factor;
    this->moveSpeed *= factor;
    this->monsterSpawn = (this->monsterSpawn - 1.0) * factor + 1.0;
    this->luckFactor *= (this->luckFactor - 1.0) * factor + 1.0;
}

// Upgrades item to the next level
void Item::upgradeItem() {
    if (this->itemLevel > 10) {
        std::cout << "ERROR: " << this->getName() << " cannot be upgraded.\n";
    }
    else {
        this->itemLevel++;
    }
}

// Print color
std::string Item::printColor() {
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
        return "black - dark";
    }
    else if (this->isWhite()) {
        return "white - light";
    }
    else if (this->isGreen()) {
        return "green - balance";
    }
    else {
        return "???";
    }
}

// Print type
std::string Item::printType() {
    if (this->isNone()) {
        return "none";
    }
    else if (this->isConsumable()) {
        return "consumable";
    }
    else if (this->isWeapon()) {
        return "weapon";
    }
    else if (this->isOffhand()) {
        return "offhand";
    }
    else if (this->isTwohand()) {
        return "twohand";
    }
    else if (this->isHeadgear()) {
        return "headgear";
    }
    else if (this->isChestgear()) {
        return "chestgear";
    }
    else if (this->isLeggear()) {
        return "leggear";
    }
    else if (this->isFootgear()) {
        return "footgear";
    }
    else if (this->isAccessory()) {
        return "accessory";
    }
    else if (this->isMaterial()) {
        return "material";
    }
    else {
        return "???";
    }
}

// Print item information
void Item::printItemInfo() {
    std::cout << this->getName() << ":\n";
    std::cout << "   Dimension: " << this->getDimension();
    if (!this->isColorless()) {
        std::cout << " - [" << this->printColor() << "]";
    }
    if (!this->isNone()) {
        std::cout << " - [" << this->printType() << "]";
    }
    std::cout << "\n";
    if (this->currHealth > 0) {
        std::cout << "   Health: " << this->currHealth << "\n";
    }
    if (this->currEnergy > 0) {
        std::cout << "   Energy: " << this->currEnergy << "\n";
    }
    if (this->currMana > 0) {
        std::cout << "   Mana: " << this->currMana << "\n";
    }
    if (this->experience > 0) {
        std::cout << "   Experience: " << this->experience << "\n";
    }
    if (this->credits > 0) {
        std::cout << "   Credits: " << this->credits << "\n";
    }
    if (this->fouls > 0) {
        std::cout << "   Fouls: " << this->fouls << "\n";
    }
    if (this->xpBonus) {
        std::cout << "   2x Experience Bonus\n";
    }
    if (this->creditBonus) {
        std::cout << "   2x Credit Bonus\n";
    }
    if (this->foulBonus) {
        std::cout << "   2x Foul Bonus\n";
    }
    if (this->maxHealth > 0) {
        std::cout << "   Health: " << this->maxHealth << "\n";
    }
    if (this->maxEnergy > 0) {
        std::cout << "   Energy: " << this->maxEnergy << "\n";
    }
    if (this->maxMana > 0) {
        std::cout << "   Mana: " << this->maxMana << "\n";
    }
    if (this->attack > 0) {
        std::cout << "   Attack: " << this->attack << "\n";
    }
    if (this->magic > 0) {
        std::cout << "   Magic: " << this->magic << "\n";
    }
    if (this->defense > 0) {
        std::cout << "   Defense: " << this->defense << "\n";
    }
    if (this->resist > 0) {
        std::cout << "   Resist: " << this->resist << "\n";
    }
    if (this->piercing > 0) {
        std::cout << "   Piercing: " << this->piercing << "\n";
    }
    if (this->penetration > 0) {
        std::cout << "   Penetration: " << this->penetration << "\n";
    }
    if (this->dexterity > 0) {
        std::cout << "   Dexterity: " << this->dexterity << "\n";
    }
    if (this->viewDistance > 0) {
        std::cout << "   View Distance: " << static_cast<int>(std::round(100.0 * this->viewDistance)) << " cm\n";
    }
    if (this->moveSpeed > 0) {
        std::cout << "   Move Distance: " << static_cast<int>(std::round(100.0 * this->moveSpeed)) << " cm\n";
    }
    if (this->monsterSpawn != 1.0) {
        std::cout << "   Increased Monster Spawn: +" << static_cast<int>(std::round(1000.0 * this->monsterSpawn - 100.0)) / 10.0 << "%\n";
    }
    if (this->luckFactor != 1.0) {
        std::cout << "   Item Luck Bonus: +" << static_cast<int>(std::round(1000.0 * this->luckFactor - 100.0)) / 10.0 << "%\n";
    }
}
// Shortened version
void Item::printItemInfoBrief() {
    std::cout << this->getName() << "\n";
    std::cout << "   Dimension: " << this->getDimension();
    if (!this->isColorless()) {
        std::cout << " - [" << this->printColor() << "]";
    }
    if (!this->isNone()) {
        std::cout << " - [" << this->printType() << "]";
    }
    std::cout << "\n";
    int numPrinted{ 0 };
    if (this->currHealth > 0) {
        std::cout << "   Health: " << this->currHealth << "\n";
        numPrinted++;
    }
    if (this->currEnergy > 0) {
        std::cout << "   Energy: " << this->currEnergy << "\n";
        numPrinted++;
    }
    if (this->currMana > 0) {
        std::cout << "   Mana: " << this->currMana << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
    }
    if (this->experience > 0) {
        std::cout << "   Experience: " << this->experience << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
    }
    if (this->credits > 0) {
        std::cout << "   Credits: " << this->credits << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
    }
    if (this->fouls > 0) {
        std::cout << "   Fouls: " << this->fouls << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->xpBonus) {
        std::cout << "   2x Experience Bonus\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->creditBonus) {
        std::cout << "   2x Credit Bonus\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->foulBonus) {
        std::cout << "   2x Foul Bonus\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->maxHealth > 0) {
        std::cout << "   Health: " << this->maxHealth << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->maxEnergy > 0) {
        std::cout << "   Energy: " << this->maxEnergy << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->maxMana > 0) {
        std::cout << "   Mana: " << this->maxMana << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->attack > 0) {
        std::cout << "   Attack: " << this->attack << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->magic > 0) {
        std::cout << "   Magic: " << this->magic << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->defense > 0) {
        std::cout << "   Defense: " << this->defense << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->resist > 0) {
        std::cout << "   Resist: " << this->resist << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->piercing > 0) {
        std::cout << "   Piercing: " << this->piercing << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->penetration > 0) {
        std::cout << "   Penetration: " << this->penetration << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->dexterity > 0) {
        std::cout << "   Dexterity: " << this->dexterity << "\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->viewDistance > 0) {
        std::cout << "   View Distance: " << static_cast<int>(std::round(100.0 * this->viewDistance)) << " cm\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->moveSpeed > 0) {
        std::cout << "   Move Distance: " << static_cast<int>(std::round(100.0 * this->moveSpeed)) << " cm\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->monsterSpawn != 1.0) {
        std::cout << "   Increased Monster Spawn: +" << static_cast<int>(std::round(1000.0 * this->monsterSpawn - 100.0)) / 10.0 << "%\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
    if (this->luckFactor != 1.0) {
        std::cout << "   Item Luck Bonus: +" << static_cast<int>(std::round(1000.0 * this->luckFactor - 100.0)) / 10.0 << "%\n";
        numPrinted++;
        if (numPrinted == 3) {
            std::cout << "\n";
        }
        else if (numPrinted == 6) {
            std::cout << "\n";
            return;
        }
    }
}

// Returns credit value of item
double Item::getItemWorth() {
    double worth{ constants::itemWorthBase };
    worth += constants::itemWorthStatConstant * (std::abs(this->currHealth) +
        std::abs(this->currEnergy) + std::abs(this->currMana) + std::abs(this->experience) +
        std::abs(this->credits) + std::abs(this->fouls));
    worth += constants::itemWorthStatConstant * (std::abs(this->maxHealth) + std::abs(this->maxEnergy)
        + std::abs(this->maxMana) + std::abs(this->attack) + std::abs(this->magic) +
        std::abs(this->defense) + std::abs(this->resist) + std::abs(this->piercing) +
        std::abs(this->penetration) + std::abs(this->dexterity) + 100.0 * std::abs(this->lifesteal));
    worth += constants::itemWorthStatConstant * (std::abs(this->viewDistance) +
        std::abs(this->moveSpeed) + std::abs(this->monsterSpawn) + std::abs(this->luckFactor));
    worth *= std::pow(constants::itemWorthDimensionConstant, this->itemDimension - 1);
    return worth;
}

// Return string for save game files
std::string Item::saveGame() {
    std::string fileString{};
    fileString += "itemID=" + std::to_string(this->itemID) + "\n";
    fileString += "thisItemType=" + std::to_string(this->getItemTypeInt()) + "\n";
    fileString += "thisItemQuality=" + std::to_string(this->getItemQualityInt()) + "\n";
    fileString += "thisItemColor=" + std::to_string(this->getItemColorInt()) + "\n";
    fileString += "itemDimension=" + std::to_string(itemDimension) + "\n";
    fileString += "itemLevel=" + std::to_string(this->itemLevel) + "\n";
    fileString += "*STRING=name\n" + this->name + "\n*END\n";
    fileString += "*VECTOR=materials\n";
    for (int i : this->materials) {
        fileString += std::to_string(i) + "\n";
    }
    fileString += "*END\n";
    fileString += "baseWorth=" + std::to_string(this->baseWorth) + "\n";
    fileString += "currEnergy=" + std::to_string(this->currEnergy) + "\n";
    fileString += "currHealth=" + std::to_string(this->currHealth) + "\n";
    fileString += "currMana=" + std::to_string(this->currMana) + "\n";
    fileString += "experience=" + std::to_string(this->experience) + "\n";
    fileString += "credits=" + std::to_string(this->credits) + "\n";
    fileString += "fouls=" + std::to_string(this->fouls) + "\n";
    fileString += "stack=" + std::to_string(this->stack) + "\n";
    fileString += "maxHealth=" + std::to_string(this->maxHealth) + "\n";
    fileString += "maxEnergy=" + std::to_string(this->maxEnergy) + "\n";
    fileString += "maxMana=" + std::to_string(this->maxMana) + "\n";
    fileString += "attack=" + std::to_string(this->attack) + "\n";
    fileString += "magic=" + std::to_string(this->magic) + "\n";
    fileString += "defense=" + std::to_string(this->defense) + "\n";
    fileString += "resist=" + std::to_string(this->resist) + "\n";
    fileString += "piercing=" + std::to_string(this->piercing) + "\n";
    fileString += "penetration=" + std::to_string(this->penetration) + "\n";
    fileString += "dexterity=" + std::to_string(this->dexterity) + "\n";
    fileString += "lifesteal=" + std::to_string(this->lifesteal) + "\n";
    fileString += "viewDistance=" + std::to_string(this->viewDistance) + "\n";
    fileString += "moveSpeed=" + std::to_string(this->moveSpeed) + "\n";
    fileString += "monsterSpawn=" + std::to_string(this->monsterSpawn) + "\n";
    fileString += "xLocation=" + std::to_string(this->xLocation) + "\n";
    fileString += "yLocation=" + std::to_string(this->yLocation) + "\n";
    fileString += "zLocation=" + std::to_string(this->zLocation) + "\n";
    fileString += "view_distance=" + std::to_string(this->view_distance) + "\n";
    fileString += "view_dot=" + std::to_string(this->view_dot) + "\n";
    fileString += "view_clock=" + std::to_string(this->view_clock) + "\n";
    return fileString;
}