/*
constants.h
inline constexpr global variable namespace.
*/

#ifndef CONSTANTS_NAMESPACE
#define CONSTANTS_NAMESPACE

#include <string>

namespace constants {
    inline constexpr bool TESTMODE{ false };

    inline constexpr double Pi{ 3.1415926535 };

    // Game constants
    inline constexpr int dimensionLevels{ 25 };
    inline constexpr int intersectionLevels{ 5 };
    inline constexpr int baseSpawnProbabilityTime{ 5 }; // number of s for one baseSpawnProb
    inline constexpr double xpLevelCoefficient{ 2.5 }; // for leveling up
    inline constexpr double xpLevelLevel{ 1.3 };
    inline constexpr double xpLevelIntersection{ 1.5 };
    inline constexpr double xpLevelDimension{ 3.0 };
    inline constexpr double shortPauseTime{ 1.0 };
    inline constexpr double normalPauseTime{ 4.0 };
    inline constexpr double longPauseTime{ 6.0 };
    inline constexpr int screenFlushLines{ 100 };
    inline constexpr std::string_view savedGameFolderName = "SavedGames";
    inline constexpr std::string_view gameFileName = "game.frog";
    inline constexpr std::string_view environmentFileName = "environment.frog";
    inline constexpr std::string_view battleFileName = "battle.frog";
    inline constexpr std::string_view achievementsFileName = "achievements.frog";
    inline constexpr std::string_view commandsFileName = "commands.frog";
    inline constexpr int saveGameEnvironmentMoves{ 10 }; // save game every 10 normal environment moves
    inline constexpr std::string_view credits =
        "  +++++++++++++++++++++++++\n"
        "  +++ Rise of the Frogs +++\n"
        "  +++++++++++++++++++++++++\n"
        "   Created by Daniel Gray\n"
        "   Version 0.30 - 20211029\n\n\n";

    // Player environment constants
    inline constexpr double defaultHealthRegenerationSpeed{ 0.0167 }; // ~1 health / minute
    inline constexpr double defaultEnergyRegenerationSpeed{ 0.0333 }; // ~2 energy / minute
    inline constexpr double defaultManaRegenerationSpeed{ 0.00833 }; // ~1 mana / 2 minutes
    inline constexpr double defaultMaxMoveDistance{ 0.04 }; // 4 cm
    inline constexpr double defaultMaxTurnAngle{ Pi / 6.0 }; // 30 degrees
    inline constexpr double defaultMaxViewDistance{ 0.1 }; // 10 cm
    inline constexpr double defaultMaxViewAngle{ 0.707107 }; // cos(45 degrees)
    inline constexpr double defaultViewAngleThreshold{ 0.39 }; // ~22.5 degrees
    inline constexpr double attentionMaxTurnAngle{ Pi / 4.0 }; // 45 degrees
    inline constexpr double attentionMaxViewDistance{ 0.15 }; // 15 cm
    inline constexpr double attentionMaxViewAngle{ 0.5 }; // cos(60 degrees)
    inline constexpr double attentionViewAngleThreshold{ 0.52 }; // ~30 degrees
    inline constexpr double legAssimilationMaxMoveDistance{ 0.06 }; // 6 cm
    inline constexpr double quadrupedal1MaxMoveDistance{ 0.08 }; // 8 cm
    inline constexpr double attention2MaxTurnAngle{ Pi / 2.0 }; // 90 degrees
    inline constexpr double attention2MaxViewDistance{ 0.25 }; // 25 cm
    inline constexpr double attention2MaxViewAngle{ 0.0 }; // cos(90 degrees)
    inline constexpr double attention2ViewAngleThreshold{ 0.785 }; // ~45 degrees
    inline constexpr double quadrupedal2MaxMoveDistance{ 0.12 }; // 12 cm
    inline constexpr double ninja1MaxMoveDistance{ 0.16 }; // 16 cm
    inline constexpr double roundAmountD{ 1000.0 }; // round to 3 decimal points
    inline constexpr int roundAmountI{ 1000 };
    inline constexpr int aggression1attack{ 15 };
    inline constexpr int aggression2attack{ 40 };
    inline constexpr int aggression3attack{ 100 };
    inline constexpr int aggression1piercing{ 5 };
    inline constexpr int aggression2piercing{ 5 };
    inline constexpr int aggression3piercing{ 5 };
    inline constexpr int protection1defense{ 8 };
    inline constexpr int protection2defense{ 20 };
    inline constexpr int protection3defense{ 50 };
    inline constexpr int protection1resist{ 8 };
    inline constexpr int protection2resist{ 20 };
    inline constexpr int protection3resist{ 50 };
    inline constexpr int magic1magic{ 15 };
    inline constexpr int magic2magic{ 40 };
    inline constexpr int magic3magic{ 100 };
    inline constexpr int magic1penetration{ 5 };
    inline constexpr int magic2penetration{ 5 };
    inline constexpr int magic3penetration{ 5 };
    inline constexpr int ninja1dexterity{ 10 };
    inline constexpr int ninja2dexterity{ 20 };
    inline constexpr int ninja3dexterity{ 30 };

    // Player base stat calculation constants
    inline constexpr int healthBase{ 2 };
    inline constexpr double healthLevelRate{ 1.5 };
    inline constexpr double healthTierRate{ 1.4 };
    inline constexpr int energyBase{ 20 };
    inline constexpr double energyLevelRate{ 4 };
    inline constexpr double energyTierRate{ 1.3 };
    inline constexpr int manaBase{ 0 };
    inline constexpr double manaLevelRate{ 2 };
    inline constexpr double manaTierRate{ 1.2 };
    inline constexpr int attackBase{ 1 };
    inline constexpr double attackLevelRate{ 0.2 };
    inline constexpr double attackTierRate{ 1.2 };
    inline constexpr int magicBase{ 0 };
    inline constexpr double magicLevelRate{ 0.1 };
    inline constexpr double magicTierRate{ 1.1 };
    inline constexpr int defenseBase{ 0 };
    inline constexpr double defenseLevelRate{ 0.1 };
    inline constexpr double defenseTierRate{ 1.1 };
    inline constexpr int resistBase{ 0 };
    inline constexpr double resistLevelRate{ 0.1 };
    inline constexpr double resistTierRate{ 1.05 };
    inline constexpr int piercingBase{ 0 };
    inline constexpr double piercingLevelRate{ 0.02 };
    inline constexpr double piercingTierRate{ 1.02 };
    inline constexpr int penetrationBase{ 0 };
    inline constexpr double penetrationLevelRate{ 0.01 };
    inline constexpr double penetrationTierRate{ 1.01 };
    inline constexpr int dexterityBase{ 20 };
    inline constexpr double dexterityLevelRate{ 1.5 };
    inline constexpr double dexterityTierRate{ 1.05 };

    // Environment constants
    inline constexpr int defaultAreaMaxPopulation{ 50 };
    inline constexpr double defaultEnemyAttackDistance{ 0.06 };
    inline constexpr double smallDistance{ 0.00001 }; // for virtual points / etc. (10 um)
    inline constexpr double smallVelocity{ 0.0001 }; // for min non-zero velocity (0.1 mm / s)
    inline constexpr double defaultLuckFactor{ 1.0 };
    inline constexpr double aiStatMultiplierMax{ 0.3 }; // ai stats go from 100-130%
    inline constexpr double gravitationalPull{ 0.01 }; // fall constant (g)
    inline constexpr double landDamageCoefficient{ 100.0 }; // damage / (m / s)
    inline constexpr double frictionCoefficient{ 2.0 }; // for landing on "soft" ground (i.e. ground you can move through)
    inline constexpr double baseDropProbability{ 0.6 }; // prob for first drop
    inline constexpr double largeDropProbability{ 0.85 };
    inline constexpr double smallDropProbability{ 0.3 };
    inline constexpr double tinyDropProbability{ 0.1 };
    inline constexpr double materialDropRate{ 0.1 };
    inline constexpr double subsequentDropMultiplier{ 0.8 }; // drop prob = base / (1 + multiplier * numDropped)
    inline constexpr int printViewSpatialSize{ 135 }; // width of console window
    inline constexpr double badPriceConstant{ 1.5 }; // sells items for itemValue * constant
    inline constexpr double normalPriceConstant{ 1.25 }; // sells items for itemValue * constant
    inline constexpr double goodPriceConstant{ 1.0 }; // sells items for itemValue * constant
    inline constexpr int ploverLimit{ 4 }; // max level of item
    inline constexpr int smithLimit{ 7 }; // max level of item
    inline constexpr int blacksmithLimit{ 10 }; // max level of item
    inline constexpr double lowLuck{ 1.0 }; // item forging/crafting
    inline constexpr double normalLuck{ 3.0 }; // item forging/crafting
    inline constexpr double goodLuck{ 10.0 }; // item forging/crafting
    inline constexpr double itemDropWorseLuck{ 0.3 }; // for item drop from unit
    inline constexpr double itemDropBadLuck{ 0.6 }; // for item drop from unit
    inline constexpr double itemDropGoodLuck{ 2.5 }; // for item drop from unit
    inline constexpr double itemDropBetterLuck{ 7.5 }; // for item drop from unit
    inline constexpr double itemWorthBase{ 1.5 };
    inline constexpr double itemWorthDimensionConstant{ 3.0 }; // raise this to the power of the dimension
    inline constexpr double itemWorthStatConstant{ 4.0 };
    inline constexpr double itemWorthConsumableConstant{ 0.8 };
    inline constexpr double itemWorthEnvironmentConstant{ 100.0 };
    inline constexpr double upgradeConstant{ 0.5 }; // itemWorth * dimension * constant * priceFactor
    inline constexpr double smeltConstant{ 0.5 }; // itemWorth * dimension * constant / priceFactor
    inline constexpr int shopRestockTime{ 3600 }; // 1h to restock shop
    inline constexpr int maxConsumableStock{ 6 };
    inline constexpr int maxRestStock{ 1 };
    inline constexpr int upgradeRestockTime{ 86400 }; // 24h to restock upgrades
    inline constexpr int abilityRestockTime{ 86400 }; // 24h to restock abilities
    inline constexpr int petRestockTime{ 86400 }; // 24h to restock pets
    inline constexpr double fightCooldown{ 60.0 }; // player has to wait 1 minute to refight something
    inline constexpr double autofightCooldown{ -60.0 }; // 2 minutes until enemy can autofight again
    inline constexpr double talkCooldown{ 900.0 }; // player has to wait 15 minutes to talk again
    inline constexpr int defaultSmelterEnergy{ 4 };
    inline constexpr int defaultSmithEnergy{ 10 };

    // Battle constants
    inline constexpr int defaultBaseHitProbability{ 95 };
    inline constexpr int defaultBaseCenterProbability{ 50 };
    inline constexpr int baseStatusRemovalProbability{ 15 };
    inline constexpr int centerStatusRemovalProbability{ 100 };
    inline constexpr double minorStatusEffectBuff{ 1.3 };
    inline constexpr double majorStatusEffectBuff{ 1.6 };
    inline constexpr double minorStatusEffectNerf{ 0.8 };
    inline constexpr double majorStatusEffectNerf{ 0.65 };
    inline constexpr double smallProbabilityStatusEffect{ 0.1 };
    inline constexpr double mediumProbabilityStatusEffect{ 0.35 };
    inline constexpr double largeProbabilityStatusEffect{ 0.85 };
    inline constexpr double bleedDoT{ 0.04 };
    inline constexpr double hemorrhageDoT{ 0.08 };
    inline constexpr double drowningDoT{ 0.02 };
    inline constexpr double drownedDoT{ 0.2 };
    inline constexpr double burnDoT{ 0.05 };
    inline constexpr double charDoT{ 0.1 };
    inline constexpr double rotDoT{ 0.05 };
    inline constexpr double decayDoT{ 0.1 };
    inline constexpr double unstableDoT{ 0.02 };
    inline constexpr double radioactiveDoT{ 0.04 };
    inline constexpr double wiltConstant{ 0.9 };
    inline constexpr double witherConstant{ 0.8 };
    inline constexpr double chillNerf{ 0.9 };
    inline constexpr double freezeNerf{ 0.8 };
    inline constexpr double chillConstant{ 0.3 };
    inline constexpr double freezeConstant{ 0.6 };
    inline constexpr double infectConstant{ 0.4 }; // lower defense/resist by up to 40%
    inline constexpr double diseaseConstant{ 0.8 }; // lower defense/resist by up to 80%
    inline constexpr double shockConstant{ 0.6 };
    inline constexpr double paralyzeConstant{ 0.9 };
    inline constexpr double abilityColorOffensiveMultiplierBlue{ 1.2 };
    inline constexpr double abilityColorOffensiveMultiplierRed{ 1.2 };
    inline constexpr double abilityColorOffensiveMultiplierBrown{ 1.2 };
    inline constexpr double abilityColorOffensiveMultiplierCyan{ 1.2 };
    inline constexpr double abilityColorOffensiveMultiplierOrange{ 1.2 };
    inline constexpr double abilityColorOffensiveMultiplierPurple{ 1.2 };
    inline constexpr double abilityColorOffensiveMultiplierYellow{ 1.2 };
    inline constexpr double abilityColorOffensiveMultiplierMagenta{ 1.2 };
    inline constexpr double abilityColorOffensiveMultiplierBlack{ 1.2 };
    inline constexpr double abilityColorOffensiveMultiplierWhite{ 1.2 };
    inline constexpr double abilityColorOffensiveMultiplierGreen{ 1.2 };
    inline constexpr double abilityColorDefensiveMultiplierBlue{ 0.7 };
    inline constexpr double abilityColorDefensiveMultiplierRed{ 0.7 };
    inline constexpr double abilityColorDefensiveMultiplierBrown{ 0.7 };
    inline constexpr double abilityColorDefensiveMultiplierCyan{ 0.7 };
    inline constexpr double abilityColorDefensiveMultiplierOrange{ 0.7 };
    inline constexpr double abilityColorDefensiveMultiplierPurple{ 0.7 };
    inline constexpr double abilityColorDefensiveMultiplierYellow{ 0.7 };
    inline constexpr double abilityColorDefensiveMultiplierMagenta{ 0.7 };
    inline constexpr double abilityColorDefensiveMultiplierBlack{ 0.7 };
    inline constexpr double abilityColorDefensiveMultiplierWhite{ 0.7 };
    inline constexpr double abilityColorDefensiveMultiplierGreen{ 0.7 };
    inline constexpr double abilityColorDefensiveWeaknessMultiplier{ 1.3 };
    inline constexpr double itemColorDefensiveMultiplier{ 1.1 };
    inline constexpr double itemColorOffensiveMultiplier{ 1.1 };

    // AI constants
    inline constexpr double dimension2mConstant{ 0.5 };
    inline constexpr double dimension2bConstant{ 10.0 };
    inline constexpr double dimension3ExponentConstant{ 1.0 };

    // Rewards constants
    inline constexpr double xpRewardCoefficient{ 2.2 };
    inline constexpr double xpRewardIntersection{ 1.3 };
    inline constexpr double xpRewardDimension{ 2.5 };
    inline constexpr double creditRewardCoefficient{ 4.4 };
    inline constexpr double creditRewardDimension{ 3.1 };
    inline constexpr double foulRewardCoefficient{ 0.5 };

    // Achievement constants
    inline constexpr int achievementRewardExperienceI{ 20 };
    inline constexpr int achievementRewardExperienceII{ 200 };
    inline constexpr int achievementRewardExperienceIII{ 2000 };
    inline constexpr int achievementRewardExperienceIV{ 20000 };
    inline constexpr int achievementRewardExperienceV{ 200000 };
    inline constexpr int achievementRewardCreditI{ 20 };
    inline constexpr int achievementRewardCreditII{ 150 };
    inline constexpr int achievementRewardCreditIII{ 500 };
    inline constexpr int achievementRewardCreditIV{ 2500 };
    inline constexpr int achievementRewardCreditV{ 10000 };
    inline constexpr int achievementRewardFoulI{ 2 };
    inline constexpr int achievementRewardFoulII{ 5 };
    inline constexpr int achievementRewardFoulIII{ 25 };
    inline constexpr int achievementRewardFoulIV{ 100 };
    inline constexpr int achievementRewardFoulV{ 500 };
    inline constexpr int achievementMonsterSlayerI{ 5 };
    inline constexpr int achievementMonsterSlayerII{ 25 };
    inline constexpr int achievementMonsterSlayerIII{ 100 };
    inline constexpr int achievementMonsterSlayerIV{ 250 };
    inline constexpr int achievementMonsterSlayerV{ 1000 };
    inline constexpr double achievementTravelerI{ 0.25 };
    inline constexpr double achievementTravelerII{ 3.0 };
    inline constexpr double achievementTravelerIII{ 15. };
    inline constexpr double achievementTravelerIV{ 60. };
    inline constexpr double achievementTravelerV{ 250. };
    inline constexpr int achievementConsumerI{ 5 };
    inline constexpr int achievementConsumerII{ 25 };
    inline constexpr int achievementConsumerIII{ 100 };
    inline constexpr int achievementConsumerIV{ 250 };
    inline constexpr int achievementConsumerV{ 1000 };
}

#endif