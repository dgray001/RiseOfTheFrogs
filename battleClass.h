/*
battleClass.h
The battle class creates dynamic battle instantiations. May be a subclass of some "interaction
class" in the future to include interactions with neutral or friendly units (or even non-fighting
interactions with enemies). For now I also assume "player" is controlled by the player while
"enemy" is controlled by the ai of the unit class.
*/

#ifndef BATTLE_CLASS
#define BATTLE_CLASS

#include "unitClass.h"
class Ability;

class Battle {
    private:
        Player player{};
        aiUnit enemy{};
        bool playerTurn{}; // true if player's turn
        bool battleOver{};
        bool displayMessages{ true };

    public:
        Battle() {}; // default constructor
        Battle(Player player, aiUnit enemy); // base constructor
        Battle(Player player, aiUnit enemy, bool turn);

        Player getPlayer() { return this->player; } // getters
        aiUnit getEnemy() { return this->enemy; }
        bool getTurn() { return this->playerTurn; }
        bool getBattleOver() { return this->battleOver; }
        void setPlayer(Player x) { this->player = x; } // setters
        void setEnemy(aiUnit x) { this->enemy = x; }
        void setTurn(bool x) { this->playerTurn = x; }
        void setDisplayMessages(bool x) { this->displayMessages = x; }

        void startTurn();
        void attack(std::string abilityName);
        void consume(std::string abilityName);
        void attack(Ability abilityUsed);
        int damageCalculator(Unit attacker, Unit defender, Ability abilityUsed);
        int selfDamageCalculator(Unit attacker, Unit defender, Ability abilityUsed);
        void calculateStatusEffectChanges(Unit &attacker, Unit &defender, Ability abilityUsed);
        void calculatePlayerItemStatusEffectChanges(Ability abilityUsed);
        void calculateItemStatusEffectChanges(Item abilityUsed);
        void removePlayerEnergy(int amount);
        void printBattleInfo(); // prints current battle state
        void saveGame(std::string filePath);
};

#endif