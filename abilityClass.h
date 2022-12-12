/*
abilityClass.h
The ability class creates ability specs for any action relevant in the interaction class (for
now just the battle class).
*/

#ifndef ABILITY_CLASS
#define ABILITY_CLASS

#include <string>

class Ability {
    private:
        std::string name{}; // unique identifier for each ability
        bool abilityValid{ false }; // internal bool to keep track of whether ability is valid
        int energyCost{ 0 }; // how much energy does it take for player to use this ability
        int manaCost{ 0 }; // how much mana does it take for player to use this ability
        int foulCost{ 0 }; // foul cost to purchase this ability

        double attackMultiplier{};
        double magicMultiplier{};
        double piercingMultiplier{};
        double penetrationMultiplier{};
        double dexterityMultiplier{};

        enum class colorType : char { // can add mixed elements later
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
        enum class damageType : int {
            none = 0,
            physical = 1,
            magic = 2,
            mixed = 3
        };
        colorType abilityColor{'c'};
        damageType abilityDamage{0};
        double lifesteal{ 0.0 }; // %
        double effectProbability{ 0.0 }; // probability to cause the status effect
        int attackTimes{ 1 }; // number of times this ability attacks
        int restoreHealth{ 0 };
        int restoreMana{ 0 };
        int restoreEnergy{ 0 };

        bool fleeAttempt{}; // attempt to run from battle

        // NOTE: Every status effect has a stronger version paired with it
        
        // Stat effects
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

        // Colored offensive effects
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

        // Colored self-inflicted effects
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

    public:
        Ability() {}; // default constructor
        Ability(std::string name, int energyCost, double attackM, double magicM, double piercingM,
            double penetrationM, double dexterityM); // base constructor
        Ability(std::string name); // constructor from unique name

        std::string getName() { return this->name; } // getters
        std::string& getNameAddress() { return this->name; }
        int getEnergyCost() { return this->energyCost; }
        int getManaCost() { return this->manaCost; }
        int getFoulCost() { return this->foulCost; }
        double getAttackMultiplier() { return this->attackMultiplier; }
        double getMagicMultiplier() { return this->magicMultiplier; }
        double getPiercingMultiplier() { return this->piercingMultiplier; }
        double getPenetrationMultiplier() { return this->penetrationMultiplier; }
        double getDexterityMultiplier() { return this->dexterityMultiplier; }
        bool getFlee() { return this->fleeAttempt; }
        colorType getColor() { return this->abilityColor; }
        int getColorInt() { return static_cast<std::underlying_type<colorType>::type>(this->abilityColor); }
        bool isBlue() { return this->abilityColor == colorType::blue; }
        bool isRed() { return this->abilityColor == colorType::red; }
        bool isBrown() { return this->abilityColor == colorType::brown; }
        bool isCyan() { return this->abilityColor == colorType::cyan; }
        bool isOrange() { return this->abilityColor == colorType::orange; }
        bool isPurple() { return this->abilityColor == colorType::purple; }
        bool isYellow() { return this->abilityColor == colorType::yellow; }
        bool isMagenta() { return this->abilityColor == colorType::magenta; }
        bool isBlack() { return this->abilityColor == colorType::black; }
        bool isWhite() { return this->abilityColor == colorType::white; }
        bool isGreen() { return this->abilityColor == colorType::green; }
        damageType getDamageType() { return this->abilityDamage; }
        int getDamageTypeInt() { return static_cast<std::underlying_type<damageType>::type>(this->abilityDamage); }
        bool isNoneDamage() { return this->abilityDamage == damageType::none; }
        bool isPhysicalDamage() { return this->abilityDamage == damageType::physical; }
        bool isMagicDamage() { return this->abilityDamage == damageType::magic; }
        bool isMixedDamage() { return this->abilityDamage == damageType::mixed; }
        double getLifeSteal() { return this->lifesteal; }
        double getEffectProbability() { return this->effectProbability; }
        int getAttackTimes() { return this->attackTimes; }
        int getRestoreHealth() { return this->restoreHealth; }
        int getRestoreMana() { return this->restoreMana; }
        int getRestoreEnergy() { return this->restoreEnergy; }

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

        void setName(std::string x) { this->name = x; } // setters
        void setAbilityValid(bool x) { this->abilityValid = x; }
        void setEnergyCost(int x) { this->energyCost = x; }
        void setManaCost(int x) { this->manaCost = x; }
        void setFoulCost(int x) { this->foulCost = x; }
        void setAttackMultiplier(double x) { this->attackMultiplier = x; }
        void setMagicMultiplier(double x) { this->magicMultiplier = x; }
        void setPiercingMultiplier(double x) { this->piercingMultiplier = x; }
        void setPenetrationMultiplier(double x) { this->penetrationMultiplier = x; }
        void setDexterityMultiplier(double x) { this->dexterityMultiplier = x; }
        void setMultipliers(double attack, double magic, double piercing, double penetration,
            double dexterity);
        void setLifeSteal(double x) { this->lifesteal = x; }
        void setEffectProbability(double x) { this->effectProbability = x; }
        void setInfo(double attack, double magic, double piercing, double penetration,
            double dexterity, int energy, int mana, colorType color, damageType damage,
            double lifeSteal, double probability);
        void setColorType(int x) { this->abilityColor = static_cast<Ability::colorType>(x); }
        void setDamageType(int x) { this->abilityDamage = static_cast<Ability::damageType>(x); }
        void setRestoreHealth(int x) { this->restoreHealth = x; }
        void setRestoreEnergy(int x) { this->restoreEnergy = x; }
        void setRestoreMana(int x) { this->restoreMana = x; }
        void setRestores(int restoreHealth, int restoreEnergy, int restoreMana);
        std::string saveGame();
        void setAttackTimes(int x) { this->attackTimes = x; }

        void setFlee(bool x) { this->fleeAttempt = x; }

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
};

#endif