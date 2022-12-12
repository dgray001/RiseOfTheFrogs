/*
environmentClass.h
The environment class creates the dynamic, interactable environment around the player. This file
also includes the area class, which are distinct, rectangular parts of the environment.
*/

#ifndef ENVIRONMENT_CLASS
#define ENVIRONMENT_CLASS

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Ability;
class Battle;
class Item;
#include "questClass.h"
#include "unitClass.h"

// areas are parts to environments
class Area {
    private:
        int areaType{};
        double x1{}; // typically units of ~meters
        double y1{};
        double z1{};
        double x2{};
        double y2{};
        double z2{};
        int maxSpace{ constants::defaultAreaMaxPopulation };
        std::vector<int> unitKeys{}; // keycodes of units in this area

    public:
        Area() {} // default constructor
        Area(int areaType, double x1, double y1, double z1, double x2, double y2, double z2);
        Area(int areaType, double x1, double y1, double z1, double x2, double y2, double z2, int maxSpace);
        
        int getID() { return this->areaType; }
        double getX1() { return this->x1; }
        double getY1() { return this->y1; }
        double getZ1() { return this->z1; }
        double getX2() { return this->x2; }
        double getY2() { return this->y2; }
        double getZ2() { return this->z2; }
        double getPoint(int component);
        int getMaxSpace() { return this->maxSpace; }
        std::vector<int> getUnitKeys() { return this->unitKeys; }

        void setID(int x) { this->areaType = x; }
        void setX1(double x) { this->x1 = x; }
        void setY1(double x) { this->y1 = x; }
        void setZ1(double x) { this->z1 = x; }
        void setX2(double x) { this->x2 = x; }
        void setY2(double x) { this->y2 = x; }
        void setZ2(double x) { this->z2 = x; }
        void setMaxSpace(int x) { this->maxSpace = x; }
        void setUnitKeys(std::vector<int> x) { this->unitKeys = x; }

        std::string getName();
        bool unitIn(Unit unit);
        bool itemIn(Item item);
        bool pointIn(double point[3]);
        std::vector<aiUnit> spawnUnits(double timeElapsed, std::vector<aiUnit> currUnits);
        void randomizePositions(std::vector<aiUnit> &units);
        std::vector<aiUnit> getPossibleUnits();
        void printAreaInfo();
        void addUnitKey(int key);
        bool removeUnitKey(int key);
        std::string saveGame();
};


class Environment {
    private:
        std::string name{};
        Player thePlayer{};
        int playerIntersectionBuffer{ 0 }; // keep track of intersections needed
        std::unordered_map<int, aiUnit> otherUnits{};
        int unitKey{ 0 }; // unit index
        int currKey{ 0 }; // unit the player is interacting with
        std::unordered_map<int, Item> droppedItems{};
        int itemKey{ 0 }; // item index
        std::vector<Area> environmentAreas{};
        int currArea{}; // index of area the player is currently in
        double xLimit{}; // typically units of ~meters
        double yLimit{};
        double zLimit{};
        std::vector<int> unitsSeen{}; // units seen by the player (by key)
        std::vector<int> itemsSeen{}; // items seen by the player (by key)
        double intersectionPoint[5]{}; // coordinates/distance/index of area in front of player
        double xpBonusLength{ 0.0 }; // time in seconds
        double creditBonusLength{ 0.0 }; // time in seconds
        double foulBonusLength{ 0.0 }; // time in seconds
        double luckBonusLength{ 0.0 }; // time in seconds
        double visionBonusLength{ 0.0 }; // time in seconds
        double speedBonusLength{ 0.0 }; // time in seconds
        double spawnBonusLength{ 0.0 }; // time in seconds
        // quest variables
        // keep track of everything unit / item seen and killed / consumed in the environment
        std::vector<Quest> environmentQuests{};
        std::unordered_map<int, int> totalUnitsSeen{}; // ID : times looked at
        std::unordered_map<int, int> totalItemsSeen{}; // ID : times looked at
        std::unordered_map<int, int> totalUnitsKilled{}; // ID : times killed
        std::unordered_map<int, int> totalItemsConsumed{}; // ID : times killed
        // toggle variables
        bool ignore_items{};
        bool ignore_units{};
        bool ignore_spatial{};
        bool pickup_drops{};

    public:
        Environment() {};
        Environment(Player thePlayer, std::unordered_map<int, aiUnit> otherUnits,
            std::vector<Area> environmentAreas, double xLimit, double yLimit, double zLimit);
        Environment(Player thePlayer, std::string environmentName); // reference constructor

        std::string getName() { return this->name; } // getters
        std::string& getNameAddress() { return this->name; }
        Player getPlayer() { return this->thePlayer; }
        int getPlayerIntersectionsBuffer() { // getting the buffer will also clear it
            int x{ this->playerIntersectionBuffer }; this->playerIntersectionBuffer = 0; return x;
        }
        std::unordered_map<int, aiUnit> getOtherUnits() { return this->otherUnits; }
        int getCurrKey() { return this->currKey; }
        std::unordered_map<int, Item> getDroppedItems() { return this->droppedItems; }
        std::vector<Area> getEnvironmentAreas() { return this->environmentAreas; }
        int getCurrArea() { return this->currArea; }
        double getXLimit() { return this->xLimit; }
        double getYLimit() { return this->yLimit; }
        double getZLimit() { return this->zLimit; }
        std::vector<int> getUnitsSeen() { return this->unitsSeen; }
        std::vector<int> getItemsSeen() { return this->itemsSeen; }
        std::vector<Quest> getEnvironmentQuests() { return this->environmentQuests; }
        std::unordered_map<int, int> getTotalUnitsSeen() { return this->totalUnitsSeen; }
        std::unordered_map<int, int> getTotalItemsSeen() { return this->totalItemsSeen; }
        std::unordered_map<int, int> getTotalUnitsKilled() { return this->totalUnitsKilled; }
        std::unordered_map<int, int> getTotalItemsConsumed() { return this->totalItemsConsumed; }
        int getUniqueThingsSeen(); // units plus items
        int getThingsEaten(); // killed plus consumed

        void setPlayer(Player x) { this->thePlayer = x; } // setters
        void setPlayerIntersectionBuffer(int x) { this->playerIntersectionBuffer = x; }
        void setOtherUnits(std::unordered_map<int, aiUnit> x) { this->otherUnits = x; }
        void setUnitKey(int x) { this->unitKey = x; }
        void setCurrKey(int x) { this->currKey = x; }
        void setDroppedItems(std::unordered_map<int, Item> x) { this->droppedItems = x; }
        void setItemKey(int x) { this->itemKey = x; }
        void setEnvironmentAreas(std::vector<Area> x) { this->environmentAreas = x; }
        void setCurrArea(int x) { this->currArea = x; }
        void setXLimit(double x) { this->xLimit = x; }
        void setYLimit(double x) { this->yLimit = x; }
        void setZLimit(double x) { this->zLimit = x; }
        void setUnitsSeen(std::vector<int> x) { this->unitsSeen = x; }
        void setItemsSeen(std::vector<int> x) { this->itemsSeen = x; }
        void setIntersectionPoint0(double x) { this->intersectionPoint[0] = x; }
        void setEnvironmentQuests(std::vector<Quest> x) { this->environmentQuests = x; }
        void setTotalUnitsSeen(std::unordered_map<int, int> x) { this->totalUnitsSeen = x; }
        void setTotalItemsSeen(std::unordered_map<int, int> x) { this->totalItemsSeen = x; }
        void setTotalUnitsKilled(std::unordered_map<int, int> x) { this->totalUnitsKilled = x; }
        void setTotalItemsConsumed(std::unordered_map<int, int> x) { this->totalItemsConsumed = x; }
        void setIntersectionPoint1(double x) { this->intersectionPoint[1] = x; }
        void setIntersectionPoint2(double x) { this->intersectionPoint[2] = x; }
        void setIntersectionPoint3(double x) { this->intersectionPoint[3] = x; }
        void setIntersectionPoint4(double x) { this->intersectionPoint[4] = x; }
        void setXPBonusLength(double x) { this->xpBonusLength = x; }
        void setCreditBonusLength(double x) { this->creditBonusLength = x; }
        void setFoulBonusLength(double x) { this->foulBonusLength = x; }
        void setLuckBonusLength(double x) { this->luckBonusLength = x; }
        void setVisionBonusLength(double x) { this->visionBonusLength = x; }
        void setSpeedBonusLength(double x) { this->speedBonusLength = x; }
        void setSpawnBonusLength(double x) { this->spawnBonusLength = x; }
        void setIgnoreItems(bool x) { this->ignore_items = x; }
        void setIgnoreUnits(bool x) { this->ignore_units = x; }
        void setIgnoreSpatial(bool x) { this->ignore_spatial = x; }
        void setPickupDrops(bool x) { this->pickup_drops = x; }

        bool hasSeenUnit(int unitCode);
        bool hasSeenItem(int itemCode);
        bool hasKilledUnit(int unitCode);
        bool hasKilledUnitKey(int unitKey);
        bool hasConsumedItem(int itemCode);

        void addMonsterSlain() { this->thePlayer.addMonsterSlain(); }
        bool turnPlayer(std::string direction, int degrees = -1);
        bool facePlayer(std::string direction);
        void turnPlayerToward(Unit targetUnit);
        bool movePlayer(double distance = -1);
        bool isPlayerFalling();
        void makePlayerFall(double timeElapsed);
        void resolveVelocity(double timeElapsed);
        void resolveVelocityComponent(double timeElapsed, int component, bool friction);
        void printVelocityComponentMovedInformation(double distanceMoved, int component);
        void updateCurrArea();
        bool inNewArea();
        int areaInNow();
        int areaInNow(Unit inputUnit);
        int areaInNow(Item inputItem);
        void updateIntersectionPoint();
        void playerLook();
        int addPlayerEnergy(int amount, bool maxout = true);
        void removePlayerEnergy(int amount);
        void printPlayerView();
        void printPlayerViewStrings(std::unordered_map<int, std::vector<std::string>> inputMap);
        void printPlayerViewStringsShort(std::unordered_map<int, std::vector<std::string>> inputMap);
        void addUnit(aiUnit newUnit, int areaIndex = -1);
        void addUnitRandomlyInArea(aiUnit newUnit, int areaIndex, int amount = 1);
        void updateCurrUnit(aiUnit currUnit);
        void removeCurrUnit();
        void addItem(Item newItem);
        void playerRewards(int xpReward, int creditReward, int foulReward);
        void playerRewards(std::vector<int> rewards);
        int upgradePlayer(int tier);
        bool timeEvents(double timeElapsed, bool reloadEnvironment = false);
        void spawnUnits(double timeElapsed);
        void printEnvironmentInfo();
        void pickupItem(int index);
        void consumeItem(int index);
        void consumeItem(Item i);
        void dropItem(int index);
        void inventoryItem(Item i);
        void useItem(int index);
        void equipItem(int index);
        void dismantleItem(int index);
        void unequipItem(std::string slot);
        void startXPBonus(double duration);
        void startCreditBonus(double duration);
        void startFoulBonus(double duration);
        void startLuckBonus(double duration);
        void startVisionBonus(double duration);
        void startSpeedBonus(double duration);
        void startSpawnBonus(double duration);
        void completedAchievement(Achievement i);
        void updateUnitsSeen();
        void updateItemsSeen();
        void addQuests(std::vector<int>);
        void updateQuests(int i);
        void checkQuestCompletion();
        void printQuests();
        void toggleIgnoreUnits();
        void toggleIgnoreItems();
        void toggleIgnoreSpatial();
        void togglePickupDrops();
        void printStatus();
        void saveGame(std::string filePath);

        void talkToCurrUnit();
        void talk_sell(double priceFactor);
        void talk_buys(double priceFactor);
        void talk_shop(double priceFactor);
        void talk_researcher();
        void talk_trainer();
        void talk_soliciter();
        void talk_handler();
        void talk_smelt(double priceFactor);
        void talk_smith(int itemLevelLimit, double priceFactor);
        void talk_forge(double luckFactor, double priceFactor);
        void talk_masterforge();
        void talk_craft(double priceFactor, double luckFactor);
};

#endif