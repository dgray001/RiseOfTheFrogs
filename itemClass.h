/*
itemClass.h
The item class includes any non-unit found in environments (like items or small features of the
environment). Like units, items are points.
*/

#ifndef ITEM_CLASS
#define ITEM_CLASS

#include <string>
#include <vector>

#include "constants.h"

class Item {
    private:
        int itemID{ -1 }; // unique identifier (item names can change) (default -1 is "no item" while 0 is "nothing" item)
        enum class itemType : int {
            consumable = 1, // can stack, cannot be renamed, always have "normal" quality
            weapon = 2,
            twohand = 3,
            offhand = 4,
            headgear = 5,
            chestgear = 6,
            leggear = 7,
            footgear = 8,
            accessory = 9,
            material = 10,
            none = 0
        };
        enum class itemQuality : int {
            defective = -2, // 60%
            inferior = -1, // 80%
            normal = 0, // 100% multiplier of stats
            superior = 1, // 120%
            rare = 2, // 140%
            exquisite = 3, // 160%
            legendary = 4, // 180%
            perfect = 5 // 200%
        };
        enum class itemColor : char { // can add mixed elements later
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
        itemType thisItemType{ itemType::none };
        itemQuality thisItemQuality{ itemQuality::normal };
        itemColor thisItemColor{ itemColor::colorless };
        int itemDimension{}; // 1-10 (?) cannot see an item of a higher dimension (except rarely?)
        int itemLevel{ 1 }; // 1-11 are multipliers (1 = 100%, 2 = 110%, etc.), 0 = 0% which is unfinished
        std::string name{}; // display only; player can change this
        std::vector<int> materials{};
        int baseWorth{};

        // consumable variables
        int currEnergy{};
        int currHealth{};
        int currMana{};
        int experience{};
        int credits{};
        int fouls{};
        int stack{ 1 }; // how many in inventory

        // gear variables
        int maxHealth{};
        int maxEnergy{};
        int maxMana{};
        int attack{};
        int magic{};
        int defense{};
        int resist{};
        int piercing{};
        int penetration{};
        int dexterity{};
        double lifesteal{};

        // status effects
        // buffs
        bool causeGrow{}; // small increase to health
        bool causeEnlarge{};
        bool causeStrength{}; // increase attack
        bool causeBeserk{};
        bool causeCogent{}; // increase magic
        bool causePotent{};
        bool causeDefend{}; // increase defense
        bool causeBulwark{};
        bool causeResolve{}; // increase resist
        bool causeDauntless{};
        bool causeSwiftness{}; // increase dexterity
        bool causeDeftness{};
        // debuffs
        bool causeWeak{}; // decrease attack
        bool causeFeeble{};
        bool causeInept{}; // decrease magic
        bool causeImpotent{};
        bool causeBreak{}; // decrease defense
        bool causeSmash{};
        bool causeOutwill{}; // decrease resist
        bool causeShatter{};
        bool causeSlowness{}; // decrease dexterity
        bool causeLethargy{};
        bool cureWeak{}; // decrease attack
        bool cureFeeble{};
        bool cureInept{}; // decrease magic
        bool cureImpotent{};
        bool cureBreak{}; // decrease defense
        bool cureSmash{};
        bool cureOutwill{}; // decrease resist
        bool cureShatter{};
        bool cureSlowness{}; // decrease dexterity
        bool cureLethargy{};
        bool selfWeak{}; // decrease attack
        bool selfFeeble{};
        bool selfInept{}; // decrease magic
        bool selfImpotent{};
        bool selfBreak{}; // decrease defense
        bool selfSmash{};
        bool selfOutwill{}; // decrease resist
        bool selfShatter{};
        bool selfSlowness{}; // decrease dexterity
        bool selfLethargy{};
        // color causers
        bool causeBleed{}; // physical
        bool causeHemorrhage{};
        bool causeWilt{}; // magic
        bool causeWither{};
        bool causeDrowning{}; // water
        bool causeDrowned{};
        bool causeBurnt{}; // fire
        bool causeCharred{};
        bool causeRot{}; // earth
        bool causeDecay{};
        bool causeChill{}; // ice
        bool causeFrozen{};
        bool causeInfect{}; // air
        bool causeDisease{};
        bool causeShaken{}; // gravity
        bool causeFallen{};
        bool causeShocked{}; // electricity
        bool causeParalyzed{};
        bool causeUnstable{}; // nuclear
        bool causeRadioactive{};
        bool causeObscure{}; // dark
        bool causeHidden{};
        bool causeBright{}; // light
        bool causeIlluminated{};
        //bool cause???; // nature
        //bool cause???;
        // color curers
        bool cureBleed{}; // physical
        bool cureHemorrhage{};
        bool cureWilt{}; // magic
        bool cureWither{};
        bool cureDrowning{}; // water
        bool cureDrowned{};
        bool cureBurnt{}; // fire
        bool cureCharred{};
        bool cureRot{}; // earth
        bool cureDecay{};
        bool cureChill{}; // ice
        bool cureFrozen{};
        bool cureInfect{}; // air
        bool cureDisease{};
        bool cureShaken{}; // gravity
        bool cureFallen{};
        bool cureShocked{}; // electricity
        bool cureParalyzed{};
        bool cureUnstable{}; // nuclear
        bool cureRadioactive{};
        bool cureObscure{}; // dark
        bool cureHidden{};
        bool cureBright{}; // light
        bool cureIlluminated{};
        //bool cure???; // nature
        //bool cure???;
        // color self
        bool selfBleed{}; // physical
        bool selfHemorrhage{};
        bool selfWilt{}; // magic
        bool selfWither{};
        bool selfDrowning{}; // water
        bool selfDrowned{};
        bool selfBurnt{}; // fire
        bool selfCharred{};
        bool selfRot{}; // earth
        bool selfDecay{};
        bool selfChill{}; // ice
        bool selfFrozen{};
        bool selfInfect{}; // air
        bool selfDisease{};
        bool selfShaken{}; // gravity
        bool selfFallen{};
        bool selfShocked{}; // electricity
        bool selfParalyzed{};
        bool selfUnstable{}; // nuclear
        bool selfRadioactive{};
        bool selfObscure{}; // dark
        bool selfHidden{};
        bool selfBright{}; // light
        bool selfIlluminated{};
        //bool self???; // nature
        //bool self???;
        
        // environment variables
        double viewDistance{}; // in m
        double moveSpeed{}; // in m
        double monsterSpawn{ 1.0 };
        double luckFactor{ 1.0 };
        bool creditBonus{};
        bool foulBonus{};
        bool xpBonus{};
        bool luckBonus{};
        bool spawnBonus{};
        bool visionBonus{};
        bool speedBonus{};

        double xLocation{}; // relevant when dropped
        double yLocation{};
        double zLocation{};
        double view_distance{}; // distance from player [0, oo)
        double view_dot{}; // dot product from player's view [-1, 1]
        int view_clock{}; // clock location from player's view (180 is forward and below player) [0, 2*pi)

    public:
        Item() {}; // default constructor
        Item(int itemID);
        Item(int itemID, double playerLuckFactor, double xLocation, double yLocation, double zLocation, bool forceNormalQuality = false);

        int getID() { return this->itemID; } // getters
        std::string& getNameAddress() { return this->name; }
        itemType getItemType() { return this->thisItemType; }
        int getItemTypeInt() { return static_cast<std::underlying_type<itemType>::type>(this->thisItemType); }
        bool isConsumable() { return this->thisItemType == itemType::consumable; }
        bool isWeapon() { return this->thisItemType == itemType::weapon; }
        bool isTwohand() { return this->thisItemType == itemType::twohand; }
        bool isOffhand() { return this->thisItemType == itemType::offhand; }
        bool isHeadgear() { return this->thisItemType == itemType::headgear; }
        bool isChestgear() { return this->thisItemType == itemType::chestgear; }
        bool isLeggear() { return this->thisItemType == itemType::leggear; }
        bool isFootgear() { return this->thisItemType == itemType::footgear; }
        bool isAccessory() { return this->thisItemType == itemType::accessory; }
        bool isMaterial() { return this->thisItemType == itemType::material; }
        bool isNone() { return this->thisItemType == itemType::none; }
        bool isStackable();
        itemQuality getItemQuality() { return this->thisItemQuality; }
        int getItemQualityInt() { return static_cast<std::underlying_type<itemQuality>::type>(this->thisItemQuality); }
        bool isDefective() { return this->thisItemQuality == itemQuality::defective; }
        bool isInferior() { return this->thisItemQuality == itemQuality::inferior; }
        bool isNormal() { return this->thisItemQuality == itemQuality::normal; }
        bool isSuperior() { return this->thisItemQuality == itemQuality::superior; }
        bool isRare() { return this->thisItemQuality == itemQuality::rare; }
        bool isExquisite() { return this->thisItemQuality == itemQuality::exquisite; }
        bool isLegendary() { return this->thisItemQuality == itemQuality::legendary; }
        bool isPerfect() { return this->thisItemQuality == itemQuality::perfect; }
        itemColor getItemColor() { return this->thisItemColor; }
        int getItemColorInt() { return static_cast<int>(static_cast<std::underlying_type<itemColor>::type>(this->thisItemColor)); }
        bool isColorless() { return this->thisItemColor == itemColor::colorless; }
        bool isBlue() { return this->thisItemColor == itemColor::blue; }
        bool isRed() { return this->thisItemColor == itemColor::red; }
        bool isBrown() { return this->thisItemColor == itemColor::brown; }
        bool isCyan() { return this->thisItemColor == itemColor::cyan; }
        bool isOrange() { return this->thisItemColor == itemColor::orange; }
        bool isPurple() { return this->thisItemColor == itemColor::purple; }
        bool isYellow() { return this->thisItemColor == itemColor::yellow; }
        bool isMagenta() { return this->thisItemColor == itemColor::magenta; }
        bool isBlack() { return this->thisItemColor == itemColor::black; }
        bool isWhite() { return this->thisItemColor == itemColor::white ; }
        bool isGreen() { return this->thisItemColor == itemColor::green; }
        int getDimension() { return this->itemDimension; }
        int getLevel() { return this->itemLevel; }
        std::string getBaseName() { return this->name; }
        std::vector<int> getItemMaterials() { return this->materials; }
        int getMatUpgradeCost(double priceFactor);
        int getCurrEnergy() {return this->currEnergy; }
        int getCurrHealth() { return this->currHealth; }
        int getCurrMana() { return this->currMana; }
        int getExperience() { return this->experience; }
        int getCredits() { return this->credits; }
        int getFouls() { return this->fouls; }
        int getStack() { return this->stack; }
        int getMaxHealth() { return this->maxHealth; }
        int getMaxEnergy() { return this->maxEnergy; }
        int getMaxMana() { return this->maxMana; }
        int getAttack() { return this->attack; }
        int getMagic() { return this->magic; }
        int getDefense() { return this->defense; }
        int getResist() { return this->resist; }
        int getPiercing() { return this->piercing; }
        int getPenetration() { return this->penetration; }
        int getDexterity() { return this->dexterity; }
        double getLifeSteal() { return this->lifesteal; }
        bool getGrow() { return this->causeGrow; }
        bool getEnlarge() { return this->causeEnlarge; }
        bool getStrength() { return this->causeStrength; }
        bool getBeserk() { return this->causeBeserk; }
        bool getCogent() { return this->causeCogent; }
        bool getPotent() { return this->causePotent; }
        bool getDefend() { return this->causeDefend; }
        bool getBulwark() { return this->causeBulwark; }
        bool getResolve() { return this->causeResolve; }
        bool getDauntless() { return this->causeDauntless; }
        bool getSwiftness() { return this->causeSwiftness; }
        bool getDeftness() { return this->causeDeftness; }
        bool getWeak() { return this->causeWeak; }
        bool getFeeble() { return this->causeFeeble; }
        bool getInept() { return this->causeInept; }
        bool getImpotent() { return this->causeImpotent; }
        bool getBreak() { return this->causeBreak; }
        bool getSmash() { return this->causeSmash; }
        bool getOutwill() { return this->causeOutwill; }
        bool getShatter() { return this->causeShatter; }
        bool getSlowness() { return this->causeSlowness; }
        bool getLethargy() { return this->causeLethargy; }
        bool getBleed() { return this->causeBleed; }
        bool getHemorrhage() { return this->causeHemorrhage; }
        bool getWilt() { return this->causeWilt; }
        bool getWither() { return this->causeWither; }
        bool getDrowning() { return this->causeDrowning; }
        bool getDrowned() { return this->causeDrowned; }
        bool getBurnt() { return this->causeBurnt; }
        bool getCharred() { return this->causeCharred; }
        bool getRot() { return this->causeRot; }
        bool getDecay() { return this->causeDecay; }
        bool getChill() { return this->causeChill; }
        bool getFrozen() { return this->causeFrozen; }
        bool getInfect() { return this->causeInfect; }
        bool getDisease() { return this->causeDisease; }
        bool getShaken() { return this->causeShaken; }
        bool getFallen() { return this->causeFallen; }
        bool getShocked() { return this->causeShocked; }
        bool getParalyzed() { return this->causeParalyzed; }
        bool getUnstable() { return this->causeUnstable; }
        bool getRadioactive() { return this->causeRadioactive; }
        bool getObscured() { return this->causeObscure; }
        bool getHidden() { return this->causeHidden; }
        bool getBright() { return this->causeBright; }
        bool getIlluminate() { return this->causeIlluminated; }
        bool getCureWeak() { return this->cureWeak; }
        bool getCureFeeble() { return this->cureFeeble; }
        bool getCureInept() { return this->cureInept; }
        bool getCureImpotent() { return this->cureImpotent; }
        bool getCureBreak() { return this->cureBreak; }
        bool getCureSmash() { return this->cureSmash; }
        bool getCureOutwill() { return this->cureOutwill; }
        bool getCureShatter() { return this->cureShatter; }
        bool getCureSlowness() { return this->cureSlowness; }
        bool getCureLethargy() { return this->cureLethargy; }
        bool getCureBleed() { return this->cureBleed; }
        bool getCureHemorrhage() { return this->cureHemorrhage; }
        bool getCureWilt() { return this->cureWilt; }
        bool getCureWither() { return this->cureWither; }
        bool getCureDrowning() { return this->cureDrowning; }
        bool getCureDrowned() { return this->cureDrowned; }
        bool getCureBurnt() { return this->cureBurnt; }
        bool getCureCharred() { return this->cureCharred; }
        bool getCureRot() { return this->cureRot; }
        bool getCureDecay() { return this->cureDecay; }
        bool getCureChill() { return this->cureChill; }
        bool getCureFrozen() { return this->cureFrozen; }
        bool getCureInfect() { return this->cureInfect; }
        bool getCureDisease() { return this->cureDisease; }
        bool getCureShaken() { return this->cureShaken; }
        bool getCureFallen() { return this->cureFallen; }
        bool getCureShocked() { return this->cureShocked; }
        bool getCureParalyzed() { return this->cureParalyzed; }
        bool getCureUnstable() { return this->cureUnstable; }
        bool getCureRadioactive() { return this->cureRadioactive; }
        bool getCureObscured() { return this->cureObscure; }
        bool getCureHidden() { return this->cureHidden; }
        bool getCureBright() { return this->cureBright; }
        bool getCureIlluminate() { return this->cureIlluminated; }
        bool getSelfWeak() { return this->selfWeak; }
        bool getSelfFeeble() { return this->selfFeeble; }
        bool getSelfInept() { return this->selfInept; }
        bool getSelfImpotent() { return this->selfImpotent; }
        bool getSelfBreak() { return this->selfBreak; }
        bool getSelfSmash() { return this->selfSmash; }
        bool getSelfOutwill() { return this->selfOutwill; }
        bool getSelfShatter() { return this->selfShatter; }
        bool getSelfSlowness() { return this->selfSlowness; }
        bool getSelfLethargy() { return this->selfLethargy; }
        bool getSelfBleed() { return this->selfBleed; }
        bool getSelfHemorrhage() { return this->selfHemorrhage; }
        bool getSelfWilt() { return this->selfWilt; }
        bool getSelfWither() { return this->selfWither; }
        bool getSelfDrowning() { return this->selfDrowning; }
        bool getSelfDrowned() { return this->selfDrowned; }
        bool getSelfBurnt() { return this->selfBurnt; }
        bool getSelfCharred() { return this->selfCharred; }
        bool getSelfRot() { return this->selfRot; }
        bool getSelfDecay() { return this->selfDecay; }
        bool getSelfChill() { return this->selfChill; }
        bool getSelfFrozen() { return this->selfFrozen; }
        bool getSelfInfect() { return this->selfInfect; }
        bool getSelfDisease() { return this->selfDisease; }
        bool getSelfShaken() { return this->selfShaken; }
        bool getSelfFallen() { return this->selfFallen; }
        bool getSelfShocked() { return this->selfShocked; }
        bool getSelfParalyzed() { return this->selfParalyzed; }
        bool getSelfUnstable() { return this->selfUnstable; }
        bool getSelfRadioactive() { return this->selfRadioactive; }
        bool getSelfObscured() { return this->selfObscure; }
        bool getSelfHidden() { return this->selfHidden; }
        bool getSelfBright() { return this->selfBright; }
        bool getSelfIlluminate() { return this->selfIlluminated; }
        double getViewDistance() { return this->viewDistance; }
        double getMoveSpeed() { return this->moveSpeed; }
        double getMonsterSpawn() { return this->monsterSpawn; }
        double getLuckFactor() { return this->luckFactor; }
        bool getCreditBonus() { return this->creditBonus; }
        bool getFoulBonus() { return this->foulBonus; }
        bool getXPBonus() { return this->xpBonus; }
        double getXLocation() { return this->xLocation; }
        double getYLocation() { return this->yLocation; }
        double getZLocation() { return this->zLocation; }
        double getView_Distance() { return this->view_distance; }
        double getView_Dot() { return this->view_dot; }
        int getView_Clock() { return this->view_clock; }

        void setName(std::string x) { this->name = x; } // setters
        void setID(int id) { this->itemID = id; }
        void setItemType(itemType x) { this->thisItemType = x; }
        void setItemType(int x) { this->thisItemType = static_cast<Item::itemType>(x); }
        void setItemQuality(itemQuality x) { this->thisItemQuality = x; }
        void setItemQuality(int x) { this->thisItemQuality = static_cast<Item::itemQuality>(x); }
        void setItemColor(int x) { this->thisItemColor = static_cast<Item::itemColor>(x); }
        void setDimension(int x) { this->itemDimension = x; }
        void setLevel(int x) { this->itemLevel = x; }
        void setMaterials(std::vector<int> x) { this->materials = x; }
        void setBaseWorth(int x) { this->baseWorth = x; }
        void setCurrEnergy(int x) {this->currEnergy = x; }
        void setCurrHealth(int x) { this->currHealth = x; }
        void setCurrMana(int x) { this->currMana = x; }
        void setExperience(int x) { this->experience = x; }
        void setCredits(int x) { this->credits = x; }
        void setFouls(int x) { this->fouls = x; }
        void setStack(int x) { this->stack = x; }
        void addStack() { this->stack++; }
        void removeStack(int x = 1) { this->stack -= x; }
        void setMaxHealth(int x) { this->maxHealth = x; }
        void setMaxEnergy(int x) { this->maxEnergy = x; }
        void setMaxMana(int x) { this->maxMana = x; }
        void setAttack(int x) { this->attack = x; }
        void setMagic(int x) { this->magic = x; }
        void setDefense(int x) { this->defense = x; }
        void setResist(int x) { this->resist = x; }
        void setPiercing(int x) { this->piercing = x; }
        void setPenetration(int x) { this->penetration = x; }
        void setDexterity(int x) { this->dexterity = x; }
        void setLifeSteal(double x) { this->lifesteal = x; }
        void setGrow(bool x) { this->causeGrow = x; }
        void setEnlarge(bool x) { this->causeEnlarge = x; }
        void setStrength(bool x) { this->causeStrength = x; }
        void setBeserk(bool x) { this->causeBeserk = x; }
        void setCogent(bool x) { this->causeCogent = x; }
        void setPotent(bool x) { this->causePotent = x; }
        void setDefend(bool x) { this->causeDefend = x; }
        void setBulwark(bool x) { this->causeBulwark = x; }
        void setResolve(bool x) { this->causeResolve = x; }
        void setDauntless(bool x) { this->causeDauntless = x; }
        void setSwiftness(bool x) { this->causeSwiftness = x; }
        void setDeftness(bool x) { this->causeDeftness = x; }
        void setWeak(bool x) { this->causeWeak = x; }
        void setFeeble(bool x) { this->causeFeeble = x; }
        void setInept(bool x) { this->causeInept = x; }
        void setImpotent(bool x) { this->causeImpotent = x; }
        void setBreak(bool x) { this->causeBreak = x; }
        void setSmash(bool x) { this->causeSmash = x; }
        void setOutwill(bool x) { this->causeOutwill = x; }
        void setShatter(bool x) { this->causeShatter = x; }
        void setSlowness(bool x) { this->causeSlowness = x; }
        void setLethargy(bool x) { this->causeLethargy = x; }
        void setBleed(bool x) { this->causeBleed = x; }
        void setHemorrhage(bool x) { this->causeHemorrhage = x; }
        void setWilt(bool x) { this->causeWilt = x; }
        void setWither(bool x) { this->causeWither = x; }
        void setDrowning(bool x) { this->causeDrowning = x; }
        void setDrowned(bool x) { this->causeDrowned = x; }
        void setBurnt(bool x) { this->causeBurnt = x; }
        void setCharred(bool x) { this->causeCharred = x; }
        void setRot(bool x) { this->causeRot = x; }
        void setDecay(bool x) { this->causeDecay = x; }
        void setChill(bool x) { this->causeChill = x; }
        void setFrozen(bool x) { this->causeFrozen = x; }
        void setInfect(bool x) { this->causeInfect = x; }
        void setDisease(bool x) { this->causeDisease = x; }
        void setShaken(bool x) { this->causeShaken = x; }
        void setFallen(bool x) { this->causeFallen = x; }
        void setShocked(bool x) { this->causeShocked = x; }
        void setParalyzed(bool x) { this->causeParalyzed = x; }
        void setUnstable(bool x) { this->causeUnstable = x; }
        void setRadioactive(bool x) { this->causeRadioactive = x; }
        void setObscured(bool x) { this->causeObscure = x; }
        void setHidden(bool x) { this->causeHidden = x; }
        void setBright(bool x) { this->causeBright = x; }
        void setIlluminate(bool x) { this->causeIlluminated = x; }
        void setSelfWeak(bool x) { this->selfWeak = x; }
        void setSelfFeeble(bool x) { this->selfFeeble = x; }
        void setSelfInept(bool x) { this->selfInept = x; }
        void setSelfImpotent(bool x) { this->selfImpotent = x; }
        void setSelfBreak(bool x) { this->selfBreak = x; }
        void setSelfSmash(bool x) { this->selfSmash = x; }
        void setSelfOutwill(bool x) { this->selfOutwill = x; }
        void setSelfShatter(bool x) { this->selfShatter = x; }
        void setSelfSlowness(bool x) { this->selfSlowness = x; }
        void setSelfLethargy(bool x) { this->selfLethargy = x; }
        void setSelfBleed(bool x) { this->selfBleed = x; }
        void setSelfHemorrhage(bool x) { this->selfHemorrhage = x; }
        void setSelfWilt(bool x) { this->selfWilt = x; }
        void setSelfWither(bool x) { this->selfWither = x; }
        void setSelfDrowning(bool x) { this->selfDrowning = x; }
        void setSelfDrowned(bool x) { this->selfDrowned = x; }
        void setSelfBurnt(bool x) { this->selfBurnt = x; }
        void setSelfCharred(bool x) { this->selfCharred = x; }
        void setSelfRot(bool x) { this->selfRot = x; }
        void setSelfDecay(bool x) { this->selfDecay = x; }
        void setSelfChill(bool x) { this->selfChill = x; }
        void setSelfFrozen(bool x) { this->selfFrozen = x; }
        void setSelfInfect(bool x) { this->selfInfect = x; }
        void setSelfDisease(bool x) { this->selfDisease = x; }
        void setSelfShaken(bool x) { this->selfShaken = x; }
        void setSelfFallen(bool x) { this->selfFallen = x; }
        void setSelfShocked(bool x) { this->selfShocked = x; }
        void setSelfParalyzed(bool x) { this->selfParalyzed = x; }
        void setSelfUnstable(bool x) { this->selfUnstable = x; }
        void setSelfRadioactive(bool x) { this->selfRadioactive = x; }
        void setSelfObscured(bool x) { this->selfObscure = x; }
        void setSelfHidden(bool x) { this->selfHidden = x; }
        void setSelfBright(bool x) { this->selfBright = x; }
        void setSelfIlluminate(bool x) { this->selfIlluminated = x; }
        void setViewDistance(double x) { this->viewDistance = x; }
        void setMoveSpeed(double x) { this->moveSpeed = x; }
        void setMonsterSpawn(double x) { this->monsterSpawn = x; }
        void setLuckFactor(double x) { this->luckFactor = x; }
        void setCreditBonus(bool x) { this->creditBonus = x; }
        void setFoulBonus(bool x) { this->foulBonus = x; }
        void setXPBonus(bool x) { this->xpBonus = x; }
        void setXLocation(double x) { this->xLocation = x; }
        void setYLocation(double x) { this->yLocation = x; }
        void setZLocation(double x) { this->zLocation = x; }
        void setView_Distance(double x) { this->view_distance = x; }
        void setView_Dot(double x) { this->view_dot = x; }
        void setView_Clock(int x) { this->view_clock = x; }

        std::string getName();
        std::string getNameOnly() { return this->name; }
        void randomizeQuality(double luckFactor = constants::defaultLuckFactor);
        void multiplyStats(double factor);
        void upgradeItem();
        
        std::string printColor();
        std::string printType();
        void printItemInfo();
        void printItemInfoBrief();
        double getItemWorth();
        std::string saveGame();
};

#endif