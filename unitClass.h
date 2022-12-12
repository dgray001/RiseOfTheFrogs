/*
unitClass.h
The unit class creates units in the game. This includes the player, enemies, pets, and any future
unit I may include. For now the subclasses are not made.
*/

#ifndef UNIT_CLASS
#define UNIT_CLASS

#include <iostream>
#include <string>
#include <vector>

class Battle;
class aiUnit;
class Player;

#include "itemClass.h"
#include "constants.h"
#include "abilityClass.h"
#include "achievementClass.h"

class Unit {
    private:
        std::string name{};

        int baseHealth{}; // base core stats
        int missingHealth{};
        int baseAttack{};
        int baseMagic{};
        int baseDefense{};
        int baseResist{};
        int basePiercing{};
        int basePenetration{};
        int baseDexterity{};

        enum class unitColor {
            colorless = 'c', // colorless
            blue = 'w', // water
            red = 'f', // fire
            brown = 'e', // earth
            cyan = 'i', // ice
            orange = 'a', // air
            purple = 'g', // gravity
            yellow = 'z', // electricity
            magenta = 'n', // nuclear
            black = 'd', // dark
            white = 'l', // light
            green = 'b' // balance / nature
        };
        unitColor thisUnitColor{ unitColor::colorless };
        
        // status booleans
        bool status_alive{};
        // buffs
        bool status_grow{ false }; // health
        bool status_enlarge{ false };
        bool status_strength{ false }; // attack
        bool status_beserk{ false };
        bool status_cogent{ false }; // magic
        bool status_potent{ false };
        bool status_defend{ false }; // defense
        bool status_bulwark{ false };
        bool status_resolve{ false }; // resist
        bool status_dauntless{ false };
        bool status_swiftness{ false }; // dexterity
        bool status_deftness{ false };
        // debuffs
        bool status_weak{ false }; // attack
        bool status_feeble{ false };
        bool status_inept{ false }; // magic
        bool status_impotent{ false };
        bool status_broken{ false }; // defense
        bool status_smashed{ false };
        bool status_outwilled{ false }; // resist
        bool status_shattered{ false };
        bool status_slow{ false }; // dexterity
        bool status_lethargic{ false };
        // colors
        bool status_bleed{ false }; // physical
        bool status_hemorrhage{ false };
        bool status_wilt{ false }; // magic
        bool status_wither{ false };
        bool status_drowning{ false }; // blue
        bool status_drowned{ false };
        bool status_burn{ false }; // red
        bool status_char{ false };
        bool status_rot{ false }; // brown
        bool status_decay{ false };
        bool status_chill{ false }; // cyan
        bool status_freeze{ false };
        bool status_infect{ false }; // orange
        bool status_disease{ false };
        bool status_shake{ false }; // purple
        bool status_fall{ false };
        int turnsShaken{ 0 };
        bool status_shock{ false }; // yellow
        bool status_paralyze{ false };
        bool status_unstable{ false }; // magenta
        bool status_radioactive{ false };
        int turnsUnstable{ 0 };
        bool status_obscure{ false }; // black
        bool status_hide{ false };
        bool status_bright{ false }; // white
        bool status_illuminate{ false };
        //bool status_???{ false }; // green
        //bool status_???{ false };

        // environment variables
        double xLocation{};
        double yLocation{};
        double zLocation{};
        double view_distance{}; // distance from player [0, oo)
        double view_dot{}; // dot product from player's view [-1, 1]
        int view_clock{}; // clock location from player's view (180 is forward and below player) [0, 2*pi)

        // battle variables
        double baseLifesteal{ 0.0 };
        std::vector<Ability> battleAbilities{};

    public:
        Unit() {} // default constructor
        Unit(std::string name, int baseHealth, int baseAttack, int baseMagic, int baseDefense,
            int baseResist, int basePiercing, int basePenetration, int baseDexterity,
            double xLocation, double yLocation, double zLocation);

        std::string getName() { return this->name; } // getters
        std::string& getNameAddress() { return this->name; }
        int getBaseHealth() { return this->baseHealth; }
        int getMissingHealth() { return this->missingHealth; }
        int getBaseAttack() { return this->baseAttack; }
        int getBaseMagic() { return this->baseMagic; }
        int getBaseDefense() { return this->baseDefense; }
        int getBaseResist() { return this->baseResist; }
        int getBasePiercing() { return this->basePiercing; }
        int getBasePenetration() { return this->basePenetration; }
        int getBaseDexterity() { return this->baseDexterity; }
        unitColor getUnitColor() { return this->thisUnitColor; }
        int getUnitColorInt() { return static_cast<std::underlying_type<unitColor>::type>(this->thisUnitColor); }
        std::string getUnitColorString();
        bool isColorless() { return this->thisUnitColor == unitColor::colorless; }
        bool isBlue() { return this->thisUnitColor == unitColor::blue; }
        bool isRed() { return this->thisUnitColor == unitColor::red; }
        bool isBrown() { return this->thisUnitColor == unitColor::brown; }
        bool isCyan() { return this->thisUnitColor == unitColor::cyan; }
        bool isOrange() { return this->thisUnitColor == unitColor::orange; }
        bool isPurple() { return this->thisUnitColor == unitColor::purple; }
        bool isYellow() { return this->thisUnitColor == unitColor::yellow; }
        bool isMagenta() { return this->thisUnitColor == unitColor::magenta; }
        bool isBlack() { return this->thisUnitColor == unitColor::black; }
        bool isWhite() { return this->thisUnitColor == unitColor::white ; }
        bool isGreen() { return this->thisUnitColor == unitColor::green; }
        bool getStatusAlive() { return this->status_alive; }
        bool getStatusGrow() { return this->status_grow; }
        bool getStatusEnlarge() { return this->status_enlarge; }
        bool getStatusStrength() { return this->status_strength; }
        bool getStatusBeserk() { return this->status_beserk; }
        bool getStatusCogent() { return this->status_cogent; }
        bool getStatusPotent() { return this->status_potent; }
        bool getStatusDefend() { return this->status_defend; }
        bool getStatusBulwark() { return this->status_bulwark; }
        bool getStatusResolve() { return this->status_resolve; }
        bool getStatusDauntless() { return this->status_dauntless; }
        bool getStatusSwiftness() { return this->status_swiftness; }
        bool getStatusDeftness() { return this->status_deftness; }
        bool getStatusWeak() { return this->status_weak; }
        bool getStatusFeeble() { return this->status_feeble; }
        bool getStatusInept() { return this->status_inept; }
        bool getStatusImpotent() { return this->status_impotent; }
        bool getStatusBreak() { return this->status_broken; }
        bool getStatusSmash() { return this->status_smashed; }
        bool getStatusOutwill() { return this->status_outwilled; }
        bool getStatusShatter() { return this->status_shattered; }
        bool getStatusSlow() { return this->status_slow; }
        bool getStatusLethargic() { return this->status_lethargic; }
        bool getStatusBleed() { return this->status_bleed; }
        bool getStatusHemorrhage() { return this->status_hemorrhage; }
        bool getStatusWilt() { return this->status_wilt; }
        bool getStatusWither() { return this->status_wither; }
        bool getStatusDrowning() { return this->status_drowning; }
        bool getStatusDrowned() { return this->status_drowned; }
        bool getStatusBurn() { return this->status_burn; }
        bool getStatusChar() { return this->status_char; }
        bool getStatusRot() { return this->status_rot; }
        bool getStatusDecay() { return this->status_decay; }
        bool getStatusChill() { return this->status_chill; }
        bool getStatusFrozen() { return this->status_freeze; }
        bool getStatusInfect() { return this->status_infect; }
        bool getStatusDisease() { return this->status_disease; }
        bool getStatusShaken() { return this->status_shake; }
        bool getStatusFell() { return this->status_fall; }
        int getTurnsShaken() { return this->turnsShaken; }
        bool getStatusShock() { return this->status_shock; }
        bool getStatusParalyze() { return this->status_paralyze; }
        bool getStatusUnstable() { return this->status_unstable; }
        bool getStatusRadioactive() { return this->status_radioactive; }
        int getTurnsUnstable() { return this->turnsUnstable; }
        bool getStatusObscure() { return this->status_obscure; }
        bool getStatusHide() { return this->status_hide; }
        bool getStatusBright() { return this->status_bright; }
        bool getStatusIlluminate() { return this->status_illuminate; }
        //bool getStatus????() { return this->status_????; }
        //bool getStatus????() { return this->status_????; }
        double getXLocation() { return this->xLocation; }
        double getYLocation() { return this->yLocation; }
        double getZLocation() { return this->zLocation; }
        double getLocation(int component);
        double getLifeSteal() { return this->baseLifesteal; }
        std::vector<Ability> getBattleAbilities() { return this->battleAbilities; }

        void setName(std::string x) { this->name = x; } // setters
        void setBaseHealth(int x) { this->baseHealth = x; }
        void setMissingHealth(int x) { this->missingHealth = x; }
        void setBaseAttack(int x) { this->baseAttack = x; }
        void setBaseMagic(int x) { this->baseMagic = x; }
        void setBaseDefense(int x) { this->baseDefense = x; }
        void setBaseResist(int x) { this->baseResist = x; }
        void setBasePiercing(int x) { this->basePiercing = x; }
        void setBasePenetration(int x) { this->basePenetration = x; }
        void setBaseDexterity(int x) { this->baseDexterity = x; }
        void setUnitColor(unitColor x) { this->thisUnitColor = x; }
        void setUnitColor(int x) { this->thisUnitColor = static_cast<Unit::unitColor>(x); }
        void setUnitColorFromChoice(int x); // When player chooses a new color
        void setStatusAlive(bool x) { this->status_alive = x; }
        void setStatusGrow(bool x);
        void setStatusEnlarge(bool x);
        void setStatusStrength(bool x) { this->status_strength = x; }
        void setStatusBeserk(bool x) { this->status_beserk = x; }
        void setStatusCogent(bool x) { this->status_cogent = x; }
        void setStatusPotent(bool x) { this->status_potent = x; }
        void setStatusDefend(bool x) { this->status_defend = x; }
        void setStatusBulwark(bool x) { this->status_bulwark = x; }
        void setStatusResolve(bool x) { this->status_resolve = x; }
        void setStatusDauntless(bool x) { this->status_dauntless = x; }
        void setStatusSwiftness(bool x) { this->status_swiftness = x; }
        void setStatusDeftness(bool x) { this->status_deftness = x; }
        void setStatusWeak(bool x) { this->status_weak = x; }
        void setStatusFeeble(bool x) { this->status_feeble = x; }
        void setStatusInept(bool x) { this->status_inept = x; }
        void setStatusImpotent(bool x) { this->status_impotent = x; }
        void setStatusBreak(bool x) { this->status_broken = x; }
        void setStatusSmash(bool x) { this->status_smashed = x; }
        void setStatusOutwill(bool x) { this->status_outwilled = x; }
        void setStatusShatter(bool x) { this->status_shattered = x; }
        void setStatusSlow(bool x) { this->status_slow = x; }
        void setStatusLethargic(bool x) { this->status_lethargic = x; }
        void setStatusBleed(bool x) { this->status_bleed = x; }
        void setStatusHemorrhage(bool x) { this->status_hemorrhage = x; }
        void setStatusWilt(bool x);
        void setStatusWither(bool x);
        void setStatusDrowning(bool x) { this->status_drowning = x; }
        void setStatusDrowned(bool x) { this->status_drowned = x; }
        void setStatusBurn(bool x) { this->status_burn = x; }
        void setStatusChar(bool x) { this->status_char = x; }
        void setStatusRot(bool x) { this->status_rot = x; }
        void setStatusDecay(bool x) { this->status_decay = x; }
        void setStatusChill(bool x) { this->status_chill = x; }
        void setStatusFrozen(bool x) { this->status_freeze = x; }
        void setStatusInfect(bool x) { this->status_infect = x; }
        void setStatusDisease(bool x) { this->status_disease = x; }
        void setStatusShaken(bool x) { this->status_shake = x; }
        void setStatusFell(bool x) { this->status_fall = x; }
        void resetTurnsShaken() { this->turnsShaken = 0; }
        void addTurnsShaken(int x) { this->turnsShaken += x; }
        void subtractTurnsShaken(int x) { this->turnsShaken -= x; }
        void setStatusShock(bool x) { this->status_shock = x; }
        void setStatusParalyze(bool x) { this->status_paralyze = x; }
        void setStatusUnstable(bool x) { this->status_unstable = x; }
        void resetTurnsUnstable() { this->turnsUnstable = 0; }
        void addTurnsUnstable(int x) { this->turnsUnstable += x; }
        void setStatusRadioactive(bool x) { this->status_radioactive = x; }
        void setStatusObscure(bool x) { this->status_obscure = x; }
        void setStatusHide(bool x) { this->status_hide = x; }
        void setStatusBright(bool x) { this->status_bright = x; }
        void setStatusIlluminate(bool x) { this->status_illuminate = x; }
        //void setStatus????(bool x) { this->status_???? = x; }
        //void setStatus????(bool x) { this->status_???? = x; }
        void setXLocation(double x) { this->xLocation = x; }
        void setYLocation(double x) { this->yLocation = x; }
        void setZLocation(double x) { this->zLocation = x; }
        void setBaseLifesteal(double x) { this->baseLifesteal = x; }
        void setBattleAbilities(std::vector<Ability> x) { this->battleAbilities = x; }

        int getMaxHealth(); // current stat calculations
        int getCurrHealth();
        int getAttack();
        int getMagic();
        int getDefense();
        int getResist();
        int getPiercing();
        int getPenetration();
        int getDexterity();

        void setUnitStats(int health, int attack, int magic, int defense, int resist,
            int piercing, int penetration, int dexterity);
        void setUnitStats(double lM, int health, int attack, int magic, int defense, int resist,
            int piercing, int penetration, int dexterity);

        void setLocation(double xLoc, double yLoc, double zLoc);
        void setLocationComponent(double loc, int component);
        void moveUnit(double dX, double dY, double dZ, double xLimit, double yLimit, double zLimit);
        double distanceToUnit(Unit otherUnit);
        double distanceToItem(Item someItem);
        double getView_Distance() { return this->view_distance; }
        double getView_Dot() { return this->view_dot; }
        int getView_Clock() { return this->view_clock; }
        void setView_Distance(double x) { this->view_distance = x; }
        void setView_Dot(double x) { this->view_dot = x; }
        void setView_Clock(int x) { this->view_clock = x; }
        
        void addBattleAbility(Ability newAbility);
        void addBattleAbilities(std::vector<Ability> newAbilities);
        void addBattleAbilities(std::vector<std::string> newAbilities);
        bool hasBattleAbility(std::string abilityName);
        int battleAbilityEnergyCost(std::string abilityName);
        void takeDamage(int damage); // when damaged
        void regenerateHealth(int amount, bool maxout = true);
        void resetStatusEffects();
        double abilityColorOffensiveMultiplier(Ability abilityUsed);
        double abilityColorDefensiveMultiplier(Ability abilityUsed);
        void initializeBattleStats(Player unit);
        void initializeBattleStats(aiUnit unit);
        void getStatusEffectInfo(std::vector<std::string>& unitInfo);

        void printUnitInfo(); // prints unit information to the screen
        std::string saveGame();
};

class Player : public Unit {
    private:
        // player-specific stats
        int monstersSlain{ 0 };
        double distanceTraveled{ 0 };
        std::vector<Achievement> achievementsCompleted{};
        int itemsConsumed{ 0 };
        int level{};
        int experience{};
        int credits{};
        int fouls{};
        int baseEnergy{};
        int missingEnergy{};
        int baseMana{};
        int missingMana{};
        int maxInventorySlots{ 0 };
        std::vector<Item> playerInventory{};
        Item weapon{};
        Item offhand{};
        Item twohand{};
        Item headgear{};
        Item chestgear{};
        Item leggear{};
        Item footgear{};
        Item accessory1{};
        Item accessory2{};
        Item accessory3{};
        Item accessory4{};
        double healthRegenerationSpeed{ constants::defaultHealthRegenerationSpeed }; // health regenerated / s
        double energyRegenerationSpeed{ constants::defaultEnergyRegenerationSpeed }; // energy regenerated / s
        double manaRegenerationSpeed{ constants::defaultManaRegenerationSpeed }; // mana regenerated / s
        double xFacing{}; // cartesian coordinates
        double yFacing{};
        double zFacing{};
        double theta{}; // spherical coordinates
        double phi{};
        double maxMoveDistance{ constants::defaultMaxMoveDistance }; // max move distance for one move command
        double maxTurnAngle{ constants::defaultMaxTurnAngle }; // max (and default) turn angle player can make
        double viewDistance{ constants::defaultMaxViewDistance }; // distance player can see
        double viewAngle{ constants::defaultMaxViewAngle }; // cos(angle) player can see from facing direction
        double viewAngleThreshold{ constants::defaultViewAngleThreshold }; // angle (radians) difference until something "to the side" of player
        double velocity[3]{}; // velocity vector
        double monsterSpawn{ 1.0 }; // multiplier of time
        double luckFactor{ constants::defaultLuckFactor }; // for item drop quality
        std::vector<int> upgradesActivated{}; // upgrades player has activated

        // Intersection upgrade booleans
        bool upgrade_forelegs{}; // Dimension I
        bool upgrade_hindlegs{};
        bool upgrade_attention1{};
        bool upgrade_quadrupedal1{};
        bool upgrade_coordination1{};
        bool upgrade_memory1{};
        bool upgrade_quadrupedal2{}; // Dimension II
        bool upgrade_coordination2{};
        bool upgrade_learning1{};
        bool upgrade_attention2{};
        bool upgrade_aggression1{};
        bool upgrade_protection1{};
        bool upgrade_magic1{};
        bool upgrade_ninja1{};
        bool upgrade_aggression2{}; // Dimension III
        bool upgrade_protection2{};
        bool upgrade_magic2{};
        bool upgrade_ninja2{};
        bool upgrade_learning2{};
        bool upgrade_memory2{};
        bool upgrade_aggression3{}; // Dimension IV
        bool upgrade_protection3{};
        bool upgrade_magic3{};
        bool upgrade_ninja3{};
        
        // Other upgrade booleans
        bool upgrade_equipWeapon{};
        bool upgrade_equipOffhand{};
        bool upgrade_equipTwohand{};
        bool upgrade_equipHeadgear{};
        bool upgrade_equipChestgear{};
        bool upgrade_equipLeggear{};
        bool upgrade_equipFootgear{};
        bool upgrade_equipAccessory1{};
        bool upgrade_equipAccessory2{};
        bool upgrade_equipAccessory3{};
        bool upgrade_equipAccessory4{};
        bool upgrade_itemsInBattle{};
        bool upgrade_dismantleItems{};

    public:
        Player() {}; // default constructor
        Player(std::string name, int baseHealth, int baseAttack, int baseMagic, int baseDefense,
            int baseResist, int basePiercing, int basePenetration, int baseDexterity, double
            heatlhRegen, double energyRegen, double manaRegen, double xLocation, double yLocation,
            double zLocation, int level, int experience, int baseEnergy, int baseMana, double
            theta, double phi, double maxMoveDistance, double viewDistance); // base constructor
        Player(std::string name, int startingLevel); // in-game constructor

        // Getters
        int getMonstersSlain() { return this->monstersSlain; }
        double getDistanceTraveled() { return this->distanceTraveled; }
        int getItemsConsumed() { return this->itemsConsumed; }
        int getLevel() { return this->level; }
        int getExperience() { return this->experience; }
        int getCredits() { return this->credits; }
        int getFouls() { return this->fouls; }
        int getBaseEnergy() { return this->baseEnergy; }
        int getMissingEnergy() { return this->missingEnergy; }
        int getBaseMana() { return this->baseMana; }
        int getMissingMana() { return this->missingMana; }
        int getMaxInventorySlots() { return this->maxInventorySlots; }
        std::vector<Item> getInventory() { return this->playerInventory; }
        Item getWeapon() { return this->weapon; }
        Item getOffhand() { return this->offhand; }
        Item getTwohand() { return this->twohand; }
        Item getHeadgear() { return this->headgear; }
        Item getChestgear() { return this->chestgear; }
        Item getLeggear() { return this->leggear; }
        Item getFootgear() { return this->footgear; }
        Item getAccessory1() { return this->accessory1; }
        Item getAccessory2() { return this->accessory2; }
        Item getAccessory3() { return this->accessory3; }
        Item getAccessory4() { return this->accessory4; }
        double getXFacing() { return this->xFacing; }
        double getYFacing() { return this->yFacing; }
        double getZFacing() { return this->zFacing; }
        double getMaxTurnAngle() { return this->maxTurnAngle; }
        double getViewAngle() { return this->viewAngle; }
        double* getVelocity() { return this->velocity; }
        std::vector<int> getUpgradesActivated() { return this->upgradesActivated; }
        bool getUpgradeForelegs() { return this->upgrade_forelegs; }
        bool getUpgradeHindlegs() { return this->upgrade_hindlegs; }
        bool getUpgradeAttention1() { return this->upgrade_attention1; }
        bool getUpgradeQuadrupedal1() { return this->upgrade_quadrupedal1; }
        bool getUpgradeCoordination1() { return this->upgrade_coordination1; }
        bool getUpgradeMemory1() { return this->upgrade_memory1; }
        bool getUpgradeQuadrupedal2() { return this->upgrade_quadrupedal2; }
        bool getUpgradeCoordination2() { return this->upgrade_coordination2; }
        bool getUpgradeLearning1() { return this->upgrade_learning1; }
        bool getUpgradeAttention2() { return this->upgrade_attention2; }
        bool getUpgradeAggression1() { return this->upgrade_aggression1; }
        bool getUpgradeProtection1() { return this->upgrade_protection1; }
        bool getUpgradeMagic1() { return this->upgrade_magic1; }
        bool getUpgradeNinja1() { return this->upgrade_ninja1; }
        bool getUpgradeAggression2() { return this->upgrade_aggression2; }
        bool getUpgradeProtection2() { return this->upgrade_protection2; }
        bool getUpgradeMagic2() { return this->upgrade_magic2; }
        bool getUpgradeNinja2() { return this->upgrade_ninja2; }
        bool getUpgradeLearning2() { return this->upgrade_learning2; }
        bool getUpgradeMemory2() { return this->upgrade_memory2; }
        bool getUpgradeAggression3() { return this->upgrade_aggression3; }
        bool getUpgradeProtection3() { return this->upgrade_protection3; }
        bool getUpgradeMagic3() { return this->upgrade_magic3; }
        bool getUpgradeNinja3() { return this->upgrade_ninja3; }
        bool getItemsInBattle() { return this->upgrade_itemsInBattle; }
        bool getDismantleItems() { return this->upgrade_dismantleItems; }

        // Setters
        void setMonstersSlain(int x) { this->monstersSlain = x; }
        void setItemsConsumed(int x) { this->itemsConsumed = x; }
        void setDistanceTraveled(double x) { this->distanceTraveled = x; }
        void addMonsterSlain() { this->monstersSlain++; }
        void addDistanceTraveled(double x) { this->distanceTraveled += x; }
        void addItemConsumed() { this->itemsConsumed++; }
        void setLevel(int x) { this->level = x; }
        void setExperience(int x) { this->experience = x; }
        void setCredits(int x) { this->credits = x; }
        void setFouls(int x) { this->fouls = x; }
        void setBaseEnergy(int x) { this->baseEnergy = x; }
        void setMissingEnergy(int x) { this->missingEnergy = x; }
        void setBaseMana(int x) { this->baseMana = x; }
        void setMissingMana(int x) { this->missingMana = x; }
        void setMaxInventorySlots(int x) { this->maxInventorySlots = x; }
        void setInventory(std::vector<Item> x) { this->playerInventory = x; }
        void setWeapon(Item x) { this->weapon = x; }
        void setOffhand(Item x) { this->offhand = x; }
        void setTwohand(Item x) { this->twohand = x; }
        void setHeadgear(Item x) { this->headgear = x; }
        void setChestgear(Item x) { this->chestgear = x; }
        void setLeggear(Item x) { this->leggear = x; }
        void setFootgear(Item x) { this->footgear = x; }
        void setAccessory1(Item x) { this->accessory1 = x; }
        void setAccessory2(Item x) { this->accessory2 = x; }
        void setAccessory3(Item x) { this->accessory3 = x; }
        void setAccessory4(Item x) { this->accessory4 = x; }
        void setHealthRegenSpeed(double x) { this->healthRegenerationSpeed = x; }
        void setEnergyRegenSpeed(double x) { this->energyRegenerationSpeed = x; }
        void setManaRegenSpeed(double x) { this->manaRegenerationSpeed = x; }
        void setXFacing(double x) { this->xFacing = x; }
        void setYFacing(double x) { this->yFacing = x; }
        void setZFacing(double x) { this->zFacing = x; }
        void setTheta(double x) { this->theta = x; }
        void setPhi(double x) { this->phi = x; }
        void setMaxMoveDistance(double x) { this->maxMoveDistance = x; }
        void setMaxTurnAngle(double x) { this->maxTurnAngle = x; }
        void setViewDistance(double x) { this->viewDistance = x; }
        void setViewAngle(double x) { this->viewAngle = x; }
        void setXVelocity(double x) { this->velocity[0] = x; }
        void setYVelocity(double x) { this->velocity[1] = x; }
        void setZVelocity(double x) { this->velocity[2] = x; }
        void setVelocityComponent(double x, int component);
        void setMonsterSpawn(double x) { this->monsterSpawn = x; }
        void setLuckFactor(double x) { this->luckFactor = x; }
        void setUpgradesActivated(std::vector<int> x) { this->upgradesActivated = x; }
        void setUpgradeForelegs(bool x) { this->upgrade_forelegs = x; }
        void setUpgradeHindlegs(bool x) { this->upgrade_hindlegs = x; }
        void setUpgradeAttention1(bool x) { this->upgrade_attention1 = x; }
        void setUpgradeQuadrupedal1(bool x) { this->upgrade_quadrupedal1 = x; }
        void setUpgradeCoordination1(bool x) { this->upgrade_coordination1 = x; }
        void setUpgradeMemory1(bool x) { this->upgrade_memory1 = x; }
        void setUpgradeQuadrupedal2(bool x) { this->upgrade_quadrupedal2 = x; }
        void setUpgradeCoordination2(bool x) { this->upgrade_coordination2 = x; }
        void setUpgradeLearning1(bool x) { this->upgrade_learning1 = x; }
        void setUpgradeAttention2(bool x) { this->upgrade_attention2 = x; }
        void setUpgradeAggression1(bool x) { this->upgrade_aggression1 = x; }
        void setUpgradeProtection1(bool x) { this->upgrade_protection1 = x; }
        void setUpgradeMagic1(bool x) { this->upgrade_magic1 = x; }
        void setUpgradeNinja1(bool x) { this->upgrade_ninja1 = x; }
        void setUpgradeAggression2(bool x) { this->upgrade_aggression2 = x; }
        void setUpgradeProtection2(bool x) { this->upgrade_protection2 = x; }
        void setUpgradeMagic2(bool x) { this->upgrade_magic2 = x; }
        void setUpgradeNinja2(bool x) { this->upgrade_ninja2 = x; }
        void setUpgradeLearning2(bool x) { this->upgrade_learning2 = x; }
        void setUpgradeMemory2(bool x) { this->upgrade_memory2 = x; }
        void setUpgradeAggression3(bool x) { this->upgrade_aggression3 = x; }
        void setUpgradeProtection3(bool x) { this->upgrade_protection3 = x; }
        void setUpgradeMagic3(bool x) { this->upgrade_magic3 = x; }
        void setUpgradeNinja3(bool x) { this->upgrade_ninja3 = x; }
        void setCanEquipWeapon(bool x) { this->upgrade_equipWeapon = x; }
        void setCanEquipOffhand(bool x) { this->upgrade_equipOffhand = x; }
        void setCanEquipTwohand(bool x) { this->upgrade_equipTwohand = x; }
        void setCanEquipHeadgear(bool x) { this->upgrade_equipHeadgear = x; }
        void setCanEquipChestgear(bool x) { this->upgrade_equipChestgear = x; }
        void setCanEquipLeggear(bool x) { this->upgrade_equipLeggear = x; }
        void setCanEquipFootgear(bool x) { this->upgrade_equipFootgear = x; }
        void setCanEquipAccessory1(bool x) { this->upgrade_equipAccessory1 = x; }
        void setCanEquipAccessory2(bool x) { this->upgrade_equipAccessory2 = x; }
        void setCanEquipAccessory3(bool x) { this->upgrade_equipAccessory3 = x; }
        void setCanEquipAccessory4(bool x) { this->upgrade_equipAccessory4 = x; }
        void setItemsInBattle(bool x) { this->upgrade_itemsInBattle = x; }
        void setDismantleItems(bool x) { this->upgrade_dismantleItems = x; }

        void activateUpgradeForelegs();
        void activateUpgradeHindlegs();
        void activateUpgradeAttention1();
        void activateUpgradeQuadrupedal1();
        void activateUpgradeCoordination1();
        void activateUpgradeMemory1();
        void activateUpgradeQuadrupedal2();
        void activateUpgradeCoordination2();
        void activateUpgradeLearning1();
        void activateUpgradeAttention2();
        void activateUpgradeAggression1();
        void activateUpgradeProtection1();
        void activateUpgradeNinja1();
        void activateUpgradeMagic1();
        void activateUpgradeAggression2();
        void activateUpgradeProtection2();
        void activateUpgradeNinja2();
        void activateUpgradeMagic2();
        void activateUpgradeMemory2();
        void activateUpgradeLearning2();
        void activateUpgradeAggression3();
        void activateUpgradeProtection3();
        void activateUpgradeNinja3();
        void activateUpgradeMagic3();
        
        // current stat calculations
        int getMaxHealth();
        int getCurrHealth();
        int getAttack();
        int getMagic();
        int getDefense();
        int getResist();
        int getPiercing();
        int getPenetration();
        int getDexterity();
        double getLifeSteal();
        double getViewDistance();
        double getMaxMoveDistance();
        double getMonsterSpawn();
        double getLuckFactor();

        // energy / mana functions
        int getMaxEnergy();
        int getCurrEnergy();
        int getMaxMana();
        int getCurrMana();
        double getHealthRegenSpeed();
        double getEnergyRegenSpeed();
        double getManaRegenSpeed();
        void lowerEnergy(int amount);
        int increaseEnergy(int amount, bool maxout = true);
        void lowerMana(int amount);
        void increaseMana(int amount, bool maxout = true);

        // battle functions
        double offensiveItemMultiplier(Item i);
        double defensiveItemMultiplier(Item i);

        // environment functions
        bool movePlayer(double distance, double xLimit, double yLimit, double zLimit);
        bool movePlayerWhenFalling(double distance, double xLimit, double yLimit, double zLimit);
        bool turnPlayer(std::string direction, int radians = -1);
        bool facePlayer(std::string direction);
        void turnToward(Unit targetUnit);
        void updateCartesian(); // updates cartesian unit vector based on theta / phi
        void updateSpherical(); // updates theta / phi based on cartesian unit vector
        void setFacingCartesian(double x, double y, double z);
        void setFacingSpherical(double theta, double phi);
        bool playerCanSee(Unit& otherUnit);
        bool playerCanSee(Item& someItem);
        bool canMoveIntoArea(int areaID);
        void regenerate(double timeElapsed);
        int consumeItem(Item itemConsumed);
        void printPlayerInfo(); // prints unit information
        void printAchievements();
        void addAchievement(Achievement i);

        // currency / experience functions
        int addExperience(int x);
        void updateBaseStats();
        int chooseNextUpgrade(int currentTier);
        void activateUpgrade(int upgradeID);
        std::string getUpgradeDescription(int upgradeID);
        std::string getUpgradeName(int upgradeID);
        int getUpgradeCost(int upgradeID);
        bool hasActivatedUpgrade(int upgradeID);
        bool hasLearnedAbility(std::string abilityName);
        void addCredits(int x);
        void removeCredits(int x);
        void addFouls(int x);
        void removeFouls(int x);
        void chooseColor(int code);
        void addColorSpells(int code);

        // Inventory functions
        void displayInventory(int itemType = 0); // (0 = all, 1 = gear, 2 = weapon, 3 = offhand, 4 = twohand, 5 = headgear, 6 = chestgear, 7 = leggear, 8 = footgear, 9 = accessory, 10 = consumables)
        void increaseInventorySlots(int amount);
        void inventoryItem(Item newItem);
        bool hasInventorySpace();
        void useItem(int index);
        int hasItem(int itemID);
        void removeItem(int index, int removeStack = 0); // remove 0 means remove entire item
        void equipItem(int index);
        void upgradeItem(int index);
        bool canEquipWeapon() { return this->upgrade_equipWeapon; }
        bool canEquipOffhand() { return this->upgrade_equipOffhand; }
        bool canEquipTwohand() { return this->upgrade_equipTwohand; }
        bool canEquipHeadgear() { return this->upgrade_equipHeadgear; }
        bool canEquipChestgear() { return this->upgrade_equipChestgear; }
        bool canEquipLeggear() { return this->upgrade_equipLeggear; }
        bool canEquipFootgear() { return this->upgrade_equipFootgear; }
        bool canEquipAccessory1() { return this->upgrade_equipAccessory1; }
        bool canEquipAccessory2() { return this->upgrade_equipAccessory2; }
        bool canEquipAccessory3() { return this->upgrade_equipAccessory3; }
        bool canEquipAccessory4() { return this->upgrade_equipAccessory4; }
        void equipWeapon(int index);
        void equipOffhand(int index);
        void equipTwohand(int index);
        void equipHeadgear(int index);
        void equipChestgear(int index);
        void equipLeggear(int index);
        void equipFootgear(int index);
        void equipAccessory1(int index);
        void equipAccessory2(int index);
        void equipAccessory3(int index);
        void equipAccessory4(int index);
        void unequipItem(std::string slot);
        void unequipWeapon();
        void unequipOffhand();
        void unequipTwohand();
        void unequipHeadgear();
        void unequipChestgear();
        void unequipLeggear();
        void unequipFootgear();
        void unequipAccessory1();
        void unequipAccessory2();
        void unequipAccessory3();
        void unequipAccessory4();

        std::string saveGame();
};

class aiUnit : public Unit {
    private:
        int unitID{}; // unique identifier
        int level{}; // the level of the unit
        int energyValue{}; // how much energy this unit gives when eaten
        int maxHerd{}; // max number allowed in an area at once
        int spaceTaken{}; // how much the unit counts toward area max population
        int allyState{}; // (0 = ally), (1 = neutral), (2 = enemy), perhaps more in future
        double attackProbability{}; // [0,1] probability of attacking you if you see it
        double attackDistance{ constants::defaultEnemyAttackDistance }; // distance away so an enemy unit won't attack you
        double spawnProbability{}; // [0,1] likelihood of spawning per 10,000s (~ 3h) when out of game
        std::vector<std::pair<int, int>> unitDrops{}; // first integer is ID of drop and second is max amount
        double cooldDown{ 0.0 }; // time until you can talk / fight / be attacked
        
    public:
        aiUnit() {}; // default constructor
        aiUnit(std::string name, int baseHealth, int baseAttack, int baseMagic, int baseDefense,
            int baseResist, int basePiercing, int basePenetration, int baseDexterity,
            double xLocation, double yLocation, double zLocation, int unitID, int level,
            int energyValue, int allyState, int maxHerd, int spaceTaken, double attackProbability,
            double spawnProbability); // base constructor
        aiUnit(int unitID, double xLocation, double yLocation, double zLocation, int specifiedLevel = -1); // ID constructor
        aiUnit(int unitID, int specifiedLevel = -1); // ID constructor with default locations (0, 0, 0)

        int getUnitID() { return this->unitID; } // getters
        int getLevel() { return this->level; }
        int getTier() { return 1 + (this->level / constants::dimensionLevels); }
        int getSubTier() { return 1 + ((this->level % constants::dimensionLevels) / constants::intersectionLevels); }
        int getEnergyValue() { return this->energyValue; }
        int getMaxHerd() { return this->maxHerd; }
        int getSpaceTaken() { return this->spaceTaken; }
        int getAllyState() { return this->allyState; }
        double getAttackProbability() { return this->attackProbability; }
        double getAttackDistance() { return this->attackDistance; }
        double getSpawnProbability() { return this->spawnProbability; }
        std::vector<std::pair<int, int>> getDrops() { return this->unitDrops; }
        double getCoolDown() { return this->cooldDown; }

        void setUnitID(int x) { this->unitID = x; } // setters
        void setLevel(int x) { this->level = x; }
        void setEnergyValue(int x) { this->energyValue = x; }
        void setMaxHerd(int x) { this->maxHerd = x; }
        void setSpaceTaken(int x) { this->spaceTaken = x; }
        void setAllyState(int x) { this->allyState = x; }
        void setAttackProbability(double x) { this->attackProbability = x; }
        void setAttackDistance(double x) { this->attackDistance = x; }
        void setSpawnProbability(double x) { this->spawnProbability = x; }
        void setDrops(std::vector<std::pair<int, int>> x) { this->unitDrops = x; }
        void setCoolDown(double x) { this->cooldDown = x; }
        void reduceCoolDown(double x) { this->cooldDown -= x; if (this->cooldDown <
            constants::autofightCooldown) { this->cooldDown = constants::autofightCooldown; } }

        void setAIStats(int energyValue, int maxHerd, int spaceTaken, int allyState,
            double attackProbability, double spawnProbability);
        Ability chooseBattleAbility(Battle currentBattle, int aiCode); // battle ai
        int calculateBattleState(Battle currentBattle);

        void shuffleItemInventory();
        void shuffleUpgradeInventory();
        void shuffleAbilityInventory();
        
        std::string saveGame();
};

class Pet : public Unit {

};

#endif