/*
environmentClass.cpp
The environment class creates the dynamic, interactable environment around the player. This file
also includes the area class, which are distinct, rectangular parts of the environment.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include "environmentClass.h"
#include "battleClass.h"
#include "unitClass.h"
#include "abilityClass.h"
#include "coreFunctions.h"
#include "itemClass.h"
#include "questClass.h"

// base constructor
Environment::Environment(Player thePlayer, std::unordered_map<int, aiUnit> otherUnits,
    std::vector<Area> environmentAreas, double xLimit, double yLimit, double zLimit) {
    this->thePlayer = thePlayer;
    this->otherUnits = otherUnits;
    this->environmentAreas = environmentAreas;
    this->xLimit = xLimit;
    this->yLimit = yLimit;
    this->zLimit = zLimit;
}

// reference constructor
Environment::Environment(Player thePlayer, std::string environmentName) {
    this->thePlayer = thePlayer;
    this->name = environmentName;
    if (environmentName.compare("DanielsAquarium") == 0) { // dimension I
        this->xLimit = 1.0; // length
        this->yLimit = 0.5; // width
        this->zLimit = 0.5; // height
        this->environmentAreas.push_back(Area(1, 0, 0, 0, 1, 0.5, 0.01)); // bottom glass
        this->environmentAreas.push_back(Area(1, 0, 0.49, 0.01, 1, 0.5, 0.47)); // front glass
        this->environmentAreas.push_back(Area(1, 0, 0, 0, 0.01, 0.5, 0.47)); // left glass
        this->environmentAreas.push_back(Area(1, 0.99, 0, 0, 1, 0.5, 0.47)); // right glass
        this->environmentAreas.push_back(Area(1, 0, 0, 0.01, 1, 0.01, 0.47)); // back glass
        this->environmentAreas.push_back(Area(2, 0.01, 0.01, 0.01, 0.99, 0.49, 0.03)); // rocky bottom
        this->environmentAreas.push_back(Area(3, 0.01, 0.01, 0.03, 0.99, 0.49, 0.10)); // bottom water
        this->environmentAreas.push_back(Area(4, 0.01, 0.01, 0.10, 0.99, 0.49, 0.28)); // middle water
        this->environmentAreas.push_back(Area(5, 0.01, 0.01, 0.28, 0.99, 0.49, 0.39)); // top water
        this->environmentAreas.push_back(Area(6, 0.01, 0.01, 0.39, 0.99, 0.49, 0.40)); // surface water
        this->environmentAreas.push_back(Area(7, 0.01, 0.01, 0.40, 0.99, 0.49, 0.47)); // air
        this->environmentAreas.push_back(Area(8, 0, 0, 0.47, 1, 0.5, 0.5)); // lid
        this->thePlayer.setXLocation(0.5); // set player start location
        this->thePlayer.setYLocation(0.48);
        this->thePlayer.setZLocation(0.05);
        this->thePlayer.setFacingCartesian(0.05, 1, 0);
        this->addItem(Item(1001, this->thePlayer.getLuckFactor(), 0.5, 0.45, 0.05)); // pebbles
        for (size_t i = 0; i < 20; i++) {
            this->addItem(Item(1001, this->thePlayer.getLuckFactor(),
                core_functions::randomDouble(0.01, 0.99), // add pebbles to rocky bottom
                core_functions::randomDouble(0.01, 0.49),
                core_functions::randomDouble(0.01, 0.03)));
        }
        for (size_t i = 0; i < 50; i++) { // food
            this->addItem(Item(1, this->thePlayer.getLuckFactor(),
                core_functions::randomDouble(0.01, 0.99),
                core_functions::randomDouble(0.01, 0.49),
                core_functions::randomDouble(0.01, 0.40)));
            this->addItem(Item(1, this->thePlayer.getLuckFactor(),
                core_functions::randomDouble(0.01, 0.99),
                core_functions::randomDouble(0.01, 0.49),
                core_functions::randomDouble(0.01, 0.40)));
            this->addItem(Item(1, this->thePlayer.getLuckFactor(),
                core_functions::randomDouble(0.01, 0.99),
                core_functions::randomDouble(0.01, 0.49),
                core_functions::randomDouble(0.01, 0.40)));
            this->addItem(Item(2, this->thePlayer.getLuckFactor(),
                core_functions::randomDouble(0.01, 0.99),
                core_functions::randomDouble(0.01, 0.49),
                core_functions::randomDouble(0.01, 0.40)));
            this->addItem(Item(3, this->thePlayer.getLuckFactor(),
                core_functions::randomDouble(0.01, 0.99),
                core_functions::randomDouble(0.01, 0.49),
                core_functions::randomDouble(0.01, 0.40)));
        }
        this->addUnit(aiUnit(1, 0.5, 0.45, 0.05, 0)); // add easy-to-find units
        this->addUnit(aiUnit(1, 0.47, 0.40, 0.05)); // dead aquatic insect larvae
        this->addUnit(aiUnit(1, 0.53, 0.40, 0.05));
        this->addUnit(aiUnit(1, 0.52, 0.48, 0.05, 0));
        this->addUnit(aiUnit(1, 0.48, 0.48, 0.05, 0));
        this->addUnit(aiUnit(1, 0.65, 0.48, 0.05));
        this->addUnit(aiUnit(1, 0.35, 0.48, 0.05));
        this->addUnit(aiUnit(2, 0.45, 0.3, 0.05)); // drowning bloodworm
        this->addUnit(aiUnit(2, 0.8, 0.4, 0.05));
        this->addUnit(aiUnit(3, 0.55, 0.3, 0.05)); // drowning waxworm
        this->addUnit(aiUnit(3, 0.2, 0.1, 0.05));
        this->addUnit(aiUnit(4, 0.75, 0.25, 0.05)); // drowning grub
        this->addUnit(aiUnit(4, 0.25, 0.25, 0.05));
        this->addUnit(aiUnit(4, 0.8, 0.1, 0.05));
        this->addUnit(aiUnit(4, 0.2, 0.4, 0.05));
        this->addUnit(aiUnit(11, 0.25, 0.45, 0.05)); // drowning earthworm
        this->addUnit(aiUnit(12, 0.75, 0.45, 0.05)); // blackworm
        this->addUnit(aiUnit(13, 0.02, 0.02, 0.05)); // reptomin
        this->addUnit(aiUnit(13, 0.98, 0.02, 0.05));
        this->addUnit(aiUnit(13, 0.98, 0.48, 0.05));
        this->addUnit(aiUnit(13, 0.02, 0.48, 0.05));
        this->addUnit(aiUnit(501, core_functions::randomDouble(0.07, 0.93), // add ally units
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.035, 0.095)));
        this->addUnit(aiUnit(501, core_functions::randomDouble(0.07, 0.93), // Conscious drowning cricket
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.035, 0.095)));
        this->addUnit(aiUnit(502, core_functions::randomDouble(0.07, 0.93), // Snail
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.011, 0.029)));
        this->addUnit(aiUnit(502, core_functions::randomDouble(0.07, 0.93),
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.011, 0.029)));
        this->addUnit(aiUnit(503, core_functions::randomDouble(0.07, 0.93), // Guppy
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.15, 0.27)));
        this->addUnit(aiUnit(503, core_functions::randomDouble(0.07, 0.93),
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.15, 0.27)));
        this->addUnit(aiUnit(504, core_functions::randomDouble(0.07, 0.93), // Slug
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.011, 0.06)));
        this->addUnit(aiUnit(504, core_functions::randomDouble(0.07, 0.93),
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.011, 0.06)));
        this->addUnit(aiUnit(504, core_functions::randomDouble(0.07, 0.93),
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.011, 0.06)));
        this->addUnit(aiUnit(504, core_functions::randomDouble(0.07, 0.93),
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.011, 0.06)));
        this->addUnit(aiUnit(505, core_functions::randomDouble(0.07, 0.93), // Goldfish
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.29, 0.38)));
        this->addUnit(aiUnit(505, core_functions::randomDouble(0.07, 0.93),
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.29, 0.38)));
        this->addUnit(aiUnit(506, core_functions::randomDouble(0.07, 0.93), // Cricket
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.391, 0.399)));
        this->addUnit(aiUnit(506, core_functions::randomDouble(0.07, 0.93),
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.391, 0.399)));
        this->addUnit(aiUnit(506, core_functions::randomDouble(0.07, 0.93),
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.391, 0.399)));
        this->addUnit(aiUnit(507, core_functions::randomDouble(0.07, 0.93), // Glofish
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.29, 0.39)));
        this->addUnit(aiUnit(508, core_functions::randomDouble(0.07, 0.93), // Cichlid
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.29, 0.39)));
        this->addUnit(aiUnit(509, core_functions::randomDouble(0.07, 0.93), // Bottom feeder
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.011, 0.02)));
        this->addUnit(aiUnit(510, core_functions::randomDouble(0.07, 0.93), // Housefly
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.43, 0.44)));
        this->addUnit(aiUnit(511, core_functions::randomDouble(0.07, 0.93), // Crab
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.02, 0.06)));
        this->addUnit(aiUnit(511, core_functions::randomDouble(0.07, 0.93),
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.02, 0.06)));
        this->addUnit(aiUnit(512, core_functions::randomDouble(0.07, 0.93), // Otocinclus
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.06, 0.25)));
        this->addUnit(aiUnit(512, core_functions::randomDouble(0.07, 0.93),
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.06, 0.25)));
        this->addUnit(aiUnit(513, core_functions::randomDouble(0.07, 0.93), // Platy
            core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.3, 0.39)));
        this->updateQuests(-1);
    }
    else if (environmentName.compare("Sewers") == 0) { // dimension II
        this->xLimit = 3.0; // length
        this->yLimit = 1.5; // width
        this->zLimit = 1.0; // height
        // Walls (0, 6)
        this->environmentAreas.push_back(Area(11, 0, 0, 0, 3, 1.5, 0.05)); // bottom wall
        this->environmentAreas.push_back(Area(11, 0, 0, 0.95, 3, 1.5, 1)); // top wall
        this->environmentAreas.push_back(Area(11, 0, 0, 0, 0.05, 1.5, 1)); // back wall
        this->environmentAreas.push_back(Area(11, 0, 1.45, 0, 3, 1.5, 1)); // left wall
        this->environmentAreas.push_back(Area(11, 0, 0, 0, 3, 0.05, 1)); // right wall
        this->environmentAreas.push_back(Area(11, 2.95, 0, 0, 3, 1.5, 1)); // front wall
        this->environmentAreas.push_back(Area(11, 1.2, 0.2, 0, 1.8, 1.3, 1)); // center wall
        // Left platform (7, 11)
        this->environmentAreas.push_back(Area(11, 0, 0.95, 0, 1, 1.5, 1)); // left tunnel wall 1
        this->environmentAreas.push_back(Area(11, 2.2, 1.0, 0, 3, 1.5, 0.65)); // left tunnel wall 2
        this->environmentAreas.push_back(Area(12, 2.2, 0.95, 0.65, 3, 1.5, 0.68)); // left surface top
        this->environmentAreas.push_back(Area(19, 2.2, 0.95, 0.68, 3, 1.5, 0.95)); // left air
        this->environmentAreas.push_back(Area(12, 2.2, 0.95, 0.05, 3, 1.0, 0.68)); // left surface wall
        // Right platform (12, 16)
        this->environmentAreas.push_back(Area(11, 0, 0, 0, 1, 0.55, 1)); // right tunnel wall 1
        this->environmentAreas.push_back(Area(11, 2.2, 0, 0, 3, 0.5, 0.56)); // right tunnel wall 2
        this->environmentAreas.push_back(Area(12, 2.2, 0, 0.65, 3, 0.55, 0.68)); // right surface top
        this->environmentAreas.push_back(Area(19, 2.2, 0, 0.68, 3, 0.55, 0.95)); // right air
        this->environmentAreas.push_back(Area(12, 2.2, 0.5, 0.05, 3, 0.55, 0.68)); // right surface wall
        // Starting Tunnel (17, 20)
        this->environmentAreas.push_back(Area(13, 0.05, 0.55, 0.05, 1.2, 0.95, 0.08)); // sewer water bottom 1
        this->environmentAreas.push_back(Area(15, 0.05, 0.55, 0.08, 1.2, 0.95, 0.47)); // sewer water 1
        this->environmentAreas.push_back(Area(17, 0.05, 0.55, 0.47, 1.2, 0.95, 0.5)); // sewer water surface 1
        this->environmentAreas.push_back(Area(19, 0.05, 0.55, 0.5, 1.2, 0.95, 0.95)); // sewer air 1
        // Left tunnel 1 (21, 24)
        this->environmentAreas.push_back(Area(13, 1, 0.95, 0.05, 1.2, 1.45, 0.08)); // sewer water bottom left 1
        this->environmentAreas.push_back(Area(15, 1, 0.95, 0.08, 1.2, 1.45, 0.47)); // sewer water left 1
        this->environmentAreas.push_back(Area(17, 1, 0.95, 0.47, 1.2, 1.45, 0.5)); // sewer water surface left 1
        this->environmentAreas.push_back(Area(19, 1, 0.95, 0.5, 1.2, 1.45, 0.95)); // sewer air left 1
        // Right tunnel 1 (25, 28)
        this->environmentAreas.push_back(Area(13, 1, 0.05, 0.05, 1.2, 0.55, 0.08)); // sewer water bottom right 1
        this->environmentAreas.push_back(Area(15, 1, 0.05, 0.08, 1.2, 0.55, 0.47)); // sewer water right 1
        this->environmentAreas.push_back(Area(17, 1, 0.05, 0.47, 1.2, 0.55, 0.5)); // sewer water surface right 1
        this->environmentAreas.push_back(Area(19, 1, 0.05, 0.5, 1.2, 0.55, 0.95)); // sewer air right 1
        // Left tunnel 2 (29, 32)
        this->environmentAreas.push_back(Area(14, 1.2, 1.3, 0.05, 1.8, 1.45, 0.08)); // sewer water bottom left 2
        this->environmentAreas.push_back(Area(16, 1.2, 1.3, 0.08, 1.8, 1.45, 0.47)); // sewer water left 2
        this->environmentAreas.push_back(Area(18, 1.2, 1.3, 0.47, 1.8, 1.45, 0.5)); // sewer water surface left 2
        this->environmentAreas.push_back(Area(19, 1.2, 1.3, 0.5, 1.8, 1.45, 0.95)); // sewer air left 2
        // Right tunnel 2 (33, 36)
        this->environmentAreas.push_back(Area(14, 1.2, 0.05, 0.05, 1.8, 0.2, 0.08)); // sewer water bottom right 2
        this->environmentAreas.push_back(Area(16, 1.2, 0.05, 0.08, 1.8, 0.2, 0.47)); // sewer water right 2
        this->environmentAreas.push_back(Area(18, 1.2, 0.05, 0.47, 1.8, 0.2, 0.5)); // sewer water surface right 2
        this->environmentAreas.push_back(Area(19, 1.2, 0.05, 0.5, 1.8, 0.2, 0.95)); // sewer air right 2
        // Left tunnel 3 (37, 40)
        this->environmentAreas.push_back(Area(20, 1.8, 0.95, 0.05, 2, 1.45, 0.08)); // sewer water bottom left 3
        this->environmentAreas.push_back(Area(20, 1.8, 0.95, 0.08, 2, 1.45, 0.47)); // sewer water left 3
        this->environmentAreas.push_back(Area(20, 1.8, 0.95, 0.47, 2, 1.45, 0.5)); // sewer water surface left 3
        this->environmentAreas.push_back(Area(20, 1.8, 0.95, 0.5, 2, 1.45, 0.95)); // sewer air left 3
        // Right tunnel 3 (41, 44)
        this->environmentAreas.push_back(Area(20, 1.8, 0.05, 0.05, 2, 0.55, 0.08)); // sewer water bottom right 3
        this->environmentAreas.push_back(Area(20, 1.8, 0.05, 0.08, 2, 0.55, 0.47)); // sewer water right 3
        this->environmentAreas.push_back(Area(20, 1.8, 0.05, 0.47, 2, 0.55, 0.5)); // sewer water surface right 3
        this->environmentAreas.push_back(Area(20, 1.8, 0.05, 0.5, 2, 0.55, 0.95)); // sewer air right 3
        // The last 4 are at index 45, etc and need to be there for quest 103 (update quest 103 if this changes)
        this->environmentAreas.push_back(Area(14, 1.8, 0.55, 0.05, 2.95, 0.95, 0.08)); // sewer water bottom 2
        this->environmentAreas.push_back(Area(16, 1.8, 0.55, 0.08, 2.95, 0.95, 0.47)); // sewer water 2
        this->environmentAreas.push_back(Area(18, 1.8, 0.55, 0.47, 2.95, 0.95, 0.5)); // sewer water surface 2
        this->environmentAreas.push_back(Area(19, 1.8, 0.55, 0.5, 2.95, 0.95, 0.95)); // sewer air 2
        this->thePlayer.setXLocation(0.06); // set player start location
        this->thePlayer.setYLocation(0.75);
        this->thePlayer.setZLocation(0.9);
        this->thePlayer.setFacingCartesian(0.1, 0, 0.9);
        this->addUnit(aiUnit(87, 1.6, 1.38, 0.4)); // baby crocodile
        this->addUnit(aiUnit(88, 1.6, 0.12, 0.4)); // baby alligator
        this->addUnit(aiUnit(core_functions::randomInt(94, 97), 2.85, 0.75, 0.3)); // end boss
        this->addUnit(aiUnit(core_functions::randomInt(94, 97), 2.85, 0.15, 0.665)); // corner boss
        this->addUnit(aiUnit(core_functions::randomInt(94, 97), 2.85, 1.35, 0.665)); // corner boss
        // Gnat (scavenger)
        this->addUnitRandomlyInArea(aiUnit(521), 10, 2);
        this->addUnitRandomlyInArea(aiUnit(521), 15, 2);
        this->addUnitRandomlyInArea(aiUnit(521), 20, 2);
        this->addUnitRandomlyInArea(aiUnit(521), 24, 2);
        this->addUnitRandomlyInArea(aiUnit(521), 28, 2);
        this->addUnitRandomlyInArea(aiUnit(521), 32, 2);
        this->addUnitRandomlyInArea(aiUnit(521), 36, 2);
        this->addUnitRandomlyInArea(aiUnit(521), 40, 2);
        this->addUnitRandomlyInArea(aiUnit(521), 44, 2);
        this->addUnitRandomlyInArea(aiUnit(521), 48, 2);
        // Fly (collector)
        this->addUnitRandomlyInArea(aiUnit(522), 10, 2);
        this->addUnitRandomlyInArea(aiUnit(522), 15, 2);
        this->addUnitRandomlyInArea(aiUnit(522), 20, 2);
        this->addUnitRandomlyInArea(aiUnit(522), 24, 2);
        this->addUnitRandomlyInArea(aiUnit(522), 28, 2);
        this->addUnitRandomlyInArea(aiUnit(522), 32, 2);
        this->addUnitRandomlyInArea(aiUnit(522), 36, 2);
        this->addUnitRandomlyInArea(aiUnit(522), 40, 2);
        this->addUnitRandomlyInArea(aiUnit(522), 44, 2);
        this->addUnitRandomlyInArea(aiUnit(522), 48, 2);
        // Grub (scavenger)
        this->addUnitRandomlyInArea(aiUnit(523), 17, 2);
        this->addUnitRandomlyInArea(aiUnit(523), 21, 2);
        this->addUnitRandomlyInArea(aiUnit(523), 25, 2);
        this->addUnitRandomlyInArea(aiUnit(523), 29, 2);
        this->addUnitRandomlyInArea(aiUnit(523), 33, 2);
        this->addUnitRandomlyInArea(aiUnit(523), 37, 2);
        this->addUnitRandomlyInArea(aiUnit(523), 41, 2);
        this->addUnitRandomlyInArea(aiUnit(523), 45, 2);
        // Grub (collector)
        this->addUnitRandomlyInArea(aiUnit(524), 17, 2);
        this->addUnitRandomlyInArea(aiUnit(524), 21, 2);
        this->addUnitRandomlyInArea(aiUnit(524), 25, 2);
        this->addUnitRandomlyInArea(aiUnit(524), 29, 2);
        this->addUnitRandomlyInArea(aiUnit(524), 33, 2);
        this->addUnitRandomlyInArea(aiUnit(524), 37, 2);
        this->addUnitRandomlyInArea(aiUnit(524), 41, 2);
        this->addUnitRandomlyInArea(aiUnit(524), 45, 2);
        // Flee (peddler)
        this->addUnitRandomlyInArea(aiUnit(525), 10, 2);
        this->addUnitRandomlyInArea(aiUnit(525), 15, 2);
        this->addUnitRandomlyInArea(aiUnit(525), 20, 2);
        this->addUnitRandomlyInArea(aiUnit(525), 24, 2);
        this->addUnitRandomlyInArea(aiUnit(525), 28, 2);
        this->addUnitRandomlyInArea(aiUnit(525), 32, 2);
        this->addUnitRandomlyInArea(aiUnit(525), 36, 2);
        this->addUnitRandomlyInArea(aiUnit(525), 40, 2);
        this->addUnitRandomlyInArea(aiUnit(525), 44, 2);
        this->addUnitRandomlyInArea(aiUnit(525), 48, 2);
        // Fly (vendor)
        this->addUnitRandomlyInArea(aiUnit(526), 10, 2);
        this->addUnitRandomlyInArea(aiUnit(526), 15, 2);
        this->addUnitRandomlyInArea(aiUnit(526), 20, 2);
        this->addUnitRandomlyInArea(aiUnit(526), 24, 2);
        this->addUnitRandomlyInArea(aiUnit(526), 28, 2);
        this->addUnitRandomlyInArea(aiUnit(526), 32, 2);
        this->addUnitRandomlyInArea(aiUnit(526), 36, 2);
        this->addUnitRandomlyInArea(aiUnit(526), 40, 2);
        this->addUnitRandomlyInArea(aiUnit(526), 44, 2);
        this->addUnitRandomlyInArea(aiUnit(526), 48, 2);
        // Larva (peddler)
        this->addUnitRandomlyInArea(aiUnit(527), 17, 2);
        this->addUnitRandomlyInArea(aiUnit(527), 21, 2);
        this->addUnitRandomlyInArea(aiUnit(527), 25, 2);
        this->addUnitRandomlyInArea(aiUnit(527), 29, 2);
        this->addUnitRandomlyInArea(aiUnit(527), 33, 2);
        this->addUnitRandomlyInArea(aiUnit(527), 37, 2);
        this->addUnitRandomlyInArea(aiUnit(527), 41, 2);
        this->addUnitRandomlyInArea(aiUnit(527), 45, 2);
        // Larva (vendor)
        this->addUnitRandomlyInArea(aiUnit(528), 17, 2);
        this->addUnitRandomlyInArea(aiUnit(528), 21, 2);
        this->addUnitRandomlyInArea(aiUnit(528), 25, 2);
        this->addUnitRandomlyInArea(aiUnit(528), 29, 2);
        this->addUnitRandomlyInArea(aiUnit(528), 33, 2);
        this->addUnitRandomlyInArea(aiUnit(528), 37, 2);
        this->addUnitRandomlyInArea(aiUnit(528), 41, 2);
        this->addUnitRandomlyInArea(aiUnit(528), 45, 2);
        // Minnow (broker)
        this->addUnitRandomlyInArea(aiUnit(529), 18, 2);
        this->addUnitRandomlyInArea(aiUnit(529), 22, 2);
        this->addUnitRandomlyInArea(aiUnit(529), 26, 2);
        this->addUnitRandomlyInArea(aiUnit(529), 30, 2);
        this->addUnitRandomlyInArea(aiUnit(529), 34, 2);
        this->addUnitRandomlyInArea(aiUnit(529), 38, 2);
        this->addUnitRandomlyInArea(aiUnit(529), 42, 2);
        this->addUnitRandomlyInArea(aiUnit(529), 46, 2);
        // Toxic GloFish (researcher)
        this->addUnitRandomlyInArea(aiUnit(530), 18, 1);
        this->addUnitRandomlyInArea(aiUnit(530), 22, 1);
        this->addUnitRandomlyInArea(aiUnit(530), 26, 1);
        this->addUnitRandomlyInArea(aiUnit(530), 30, 1);
        this->addUnitRandomlyInArea(aiUnit(530), 34, 1);
        this->addUnitRandomlyInArea(aiUnit(530), 38, 1);
        this->addUnitRandomlyInArea(aiUnit(530), 42, 1);
        this->addUnitRandomlyInArea(aiUnit(530), 46, 1);
        // Toxic Cichlid (trainer)
        this->addUnitRandomlyInArea(aiUnit(531), 18, 1);
        this->addUnitRandomlyInArea(aiUnit(531), 22, 1);
        this->addUnitRandomlyInArea(aiUnit(531), 26, 1);
        this->addUnitRandomlyInArea(aiUnit(531), 30, 1);
        this->addUnitRandomlyInArea(aiUnit(531), 34, 1);
        this->addUnitRandomlyInArea(aiUnit(531), 38, 1);
        this->addUnitRandomlyInArea(aiUnit(531), 42, 1);
        this->addUnitRandomlyInArea(aiUnit(531), 46, 1);
        // Toxic Bottom Feeder (solicitor)
        this->addUnitRandomlyInArea(aiUnit(532), 17, 1);
        this->addUnitRandomlyInArea(aiUnit(532), 21, 1);
        this->addUnitRandomlyInArea(aiUnit(532), 25, 1);
        this->addUnitRandomlyInArea(aiUnit(532), 29, 1);
        this->addUnitRandomlyInArea(aiUnit(532), 33, 1);
        this->addUnitRandomlyInArea(aiUnit(532), 37, 1);
        this->addUnitRandomlyInArea(aiUnit(532), 41, 1);
        this->addUnitRandomlyInArea(aiUnit(532), 45, 1);
        // Pilot Fish (handler)
        this->addUnitRandomlyInArea(aiUnit(533), 18, 1);
        this->addUnitRandomlyInArea(aiUnit(533), 22, 1);
        this->addUnitRandomlyInArea(aiUnit(533), 26, 1);
        this->addUnitRandomlyInArea(aiUnit(533), 30, 1);
        this->addUnitRandomlyInArea(aiUnit(533), 34, 1);
        this->addUnitRandomlyInArea(aiUnit(533), 38, 1);
        this->addUnitRandomlyInArea(aiUnit(533), 42, 1);
        this->addUnitRandomlyInArea(aiUnit(533), 46, 1);
        // Carp (smelter)
        this->addUnitRandomlyInArea(aiUnit(534), 18, 1);
        this->addUnitRandomlyInArea(aiUnit(534), 22, 1);
        this->addUnitRandomlyInArea(aiUnit(534), 26, 1);
        this->addUnitRandomlyInArea(aiUnit(534), 30, 1);
        this->addUnitRandomlyInArea(aiUnit(534), 34, 1);
        this->addUnitRandomlyInArea(aiUnit(534), 38, 1);
        this->addUnitRandomlyInArea(aiUnit(534), 42, 1);
        this->addUnitRandomlyInArea(aiUnit(534), 46, 1);
        // Bass (plover)
        this->addUnitRandomlyInArea(aiUnit(535), 18, 1);
        this->addUnitRandomlyInArea(aiUnit(535), 22, 1);
        this->addUnitRandomlyInArea(aiUnit(535), 26, 1);
        this->addUnitRandomlyInArea(aiUnit(535), 30, 1);
        this->addUnitRandomlyInArea(aiUnit(535), 34, 1);
        this->addUnitRandomlyInArea(aiUnit(535), 38, 1);
        this->addUnitRandomlyInArea(aiUnit(535), 42, 1);
        this->addUnitRandomlyInArea(aiUnit(535), 46, 1);
        // Turtle (smith)
        this->addUnitRandomlyInArea(aiUnit(536), 9, 1);
        this->addUnitRandomlyInArea(aiUnit(536), 14, 1);
        this->addUnitRandomlyInArea(aiUnit(536), 30, 1);
        this->addUnitRandomlyInArea(aiUnit(536), 34, 1);
        this->addUnitRandomlyInArea(aiUnit(536), 46, 2);
        // Catfish (forger)
        this->addUnitRandomlyInArea(aiUnit(535), 38, 1);
        this->addUnitRandomlyInArea(aiUnit(535), 42, 1);
        this->addUnitRandomlyInArea(aiUnit(535), 46, 1);
        this->updateQuests(-1);
    }
    else if (environmentName.compare("Lake") == 0) { // dimension III
        this->xLimit = 10.0; // length
        this->yLimit = 10.0; // width
        this->zLimit = 10.0; // height
        this->environmentAreas.push_back(Area(42, 0, 0, 0, 20, 0.1, 10)); // cliff (bottom)
        this->environmentAreas.push_back(Area(42, 0, 0, 0, 0.1, 4.6, 10)); // cliff (left-bottom)
        this->environmentAreas.push_back(Area(42, 0, 4.6, 0, 0.1, 5.4, 10)); // sewers (impenetrable)
        this->environmentAreas.push_back(Area(42, 0, 5.4, 0, 0.1, 10, 10)); // cliff (left-top)
        this->environmentAreas.push_back(Area(42, 0, 9.9, 0, 20, 10, 10)); // cliff (top)
        this->environmentAreas.push_back(Area(42, 19.9, 0, 0, 20, 10, 10)); // cliff (right)
        this->environmentAreas.push_back(Area(37, 0.1, 4.6, 0, 4, 5.4, 2)); // ground
        this->environmentAreas.push_back(Area(21, 0.1, 4.6, 2.0, 4, 5.4, 2.2)); // runoff mud
        this->environmentAreas.push_back(Area(22, 0.1, 4.6, 2.2, 4, 5.4, 3)); // runoff water
        this->environmentAreas.push_back(Area(23, 0.1, 4.6, 3.0, 4, 5.4, 3.1)); // runoff surface
        this->environmentAreas.push_back(Area(24, 0.1, 4.6, 3.1, 4, 5.4, 10)); // runoff air
        this->environmentAreas.push_back(Area(37, 1, 7, 0, 1.2, 9, 2)); // ground
        this->environmentAreas.push_back(Area(25, 1, 7, 2.0, 1.2, 9, 2.2)); // spring pebbles 1
        this->environmentAreas.push_back(Area(26, 1, 7, 2.2, 1.2, 9, 3.0)); // spring water 1
        this->environmentAreas.push_back(Area(27, 1, 7, 3.0, 1.2, 9, 3.1)); // spring surface 1
        this->environmentAreas.push_back(Area(28, 1, 7, 3.1, 1.2, 9, 10)); // spring air 1
        this->environmentAreas.push_back(Area(37, 1, 6.6, 0, 3, 7, 2)); // ground
        this->environmentAreas.push_back(Area(25, 1, 6.6, 2.0, 3, 7, 2.2)); // spring pebbles 2
        this->environmentAreas.push_back(Area(26, 1, 6.6, 2.2, 3, 7, 3.0)); // spring water 2
        this->environmentAreas.push_back(Area(27, 1, 6.6, 3.0, 3, 7, 3.1)); // spring surface 2
        this->environmentAreas.push_back(Area(28, 1, 6.6, 3.1, 3, 7, 10)); // spring air 2
        this->environmentAreas.push_back(Area(37, 2.4, 5.4, 0, 3, 6.6, 2)); // ground
        this->environmentAreas.push_back(Area(21, 2.4, 5.4, 2.0, 3, 6.6, 2.2)); // toxic mud
        this->environmentAreas.push_back(Area(26, 2.4, 5.4, 2.2, 3, 6.6, 3.0)); // spring water 3
        this->environmentAreas.push_back(Area(27, 2.4, 5.4, 3.0, 3, 6.6, 3.1)); // spring surface 3
        this->environmentAreas.push_back(Area(28, 2.4, 5.4, 3.1, 3, 6.6, 10)); // spring air 3
        this->environmentAreas.push_back(Area(37, 4, 2, 0, 6.5, 8, 1.5)); // ground
        this->environmentAreas.push_back(Area(29, 4, 2, 1.3, 6.5, 8, 1.5)); // shallow lake mud
        this->environmentAreas.push_back(Area(31, 4, 2, 1.5, 9, 8, 3)); // shallow lake water
        this->environmentAreas.push_back(Area(32, 4, 2, 3.0, 9, 8, 3.1)); // lake surface
        this->environmentAreas.push_back(Area(33, 4, 2, 3.1, 9, 8, 10)); // lake air
        this->environmentAreas.push_back(Area(37, 6.5, 2, 0, 9, 8, 0.1)); // ground
        this->environmentAreas.push_back(Area(44, 6.5, 2, 0.1, 9, 8, 0.4)); // deep lake mud
        this->environmentAreas.push_back(Area(30, 6.5, 2, 0.4, 9, 8, 1.5)); // deep lake water
        this->environmentAreas.push_back(Area(37, 0.1, 0.1, 0, 4, 4.6, 3.2)); // ground (field)
        this->environmentAreas.push_back(Area(34, 0.1, 2, 3.2, 4, 4.6, 3.4)); // grass (field1)
        this->environmentAreas.push_back(Area(45, 0.1, 2, 3.4, 4, 4.6, 10)); // air (field1)
        this->environmentAreas.push_back(Area(47, 0.1, 0.1, 3.2, 4, 2, 3.4)); // grass (field2)
        this->environmentAreas.push_back(Area(48, 0.1, 0.1, 3.4, 4, 2, 10)); // air (field2)
        this->environmentAreas.push_back(Area(37, 0.1, 5.4, 0, 2.4, 6.6, 3.2)); // ground (rock)
        this->environmentAreas.push_back(Area(37, 3, 5.4, 0, 4, 7, 3.2)); // ground (rock)
        this->environmentAreas.push_back(Area(37, 0.1, 6.6, 0, 1, 9, 3.45)); // ground (mountain)
        this->environmentAreas.push_back(Area(37, 1.2, 7, 0, 4, 9, 3.45)); // ground (mountain)
        this->environmentAreas.push_back(Area(35, 0.1, 5.4, 3.2, 2.4, 6.6, 3.4)); // surface (rock)
        this->environmentAreas.push_back(Area(35, 3, 5.4, 3.2, 4, 7, 3.4)); // surface (rock)
        this->environmentAreas.push_back(Area(51, 0.1, 6.6, 3.45, 1, 9, 3.65)); // surface (mountain)
        this->environmentAreas.push_back(Area(51, 1.2, 7, 3.45, 4, 9, 3.65)); // surface (mountain)
        this->environmentAreas.push_back(Area(46, 0.1, 5.4, 3.4, 2.4, 6.6, 10)); // air (rock)
        this->environmentAreas.push_back(Area(46, 3, 5.4, 3.4, 4, 7, 10)); // air (rock)
        this->environmentAreas.push_back(Area(49, 0.1, 6.6, 3.65, 1, 9, 10)); // air (mountain)
        this->environmentAreas.push_back(Area(49, 1.2, 7, 3.65, 4, 9, 10)); // air (mountain)
        this->environmentAreas.push_back(Area(37, 0.1, 9, 0, 4, 9.9, 3.75)); // ground (snow)
        this->environmentAreas.push_back(Area(52, 0.1, 9, 3.75, 4, 9.9, 4)); // surface (snow)
        this->environmentAreas.push_back(Area(50, 0.1, 9, 4, 4, 9.9, 10)); // air (snow)
        this->environmentAreas.push_back(Area(37, 4, 8, 0, 9.9, 9.9, 3.2)); // ground (forest) 1
        this->environmentAreas.push_back(Area(37, 9, 2, 0, 9.9, 8, 3.2)); // ground (forest) 2
        this->environmentAreas.push_back(Area(37, 4, 0.1, 0, 9.9, 2, 3.2)); // ground (forest) 3
        this->environmentAreas.push_back(Area(36, 4, 8, 3.2, 9.9, 9.9, 3.6)); // underbrush (forest) 1
        this->environmentAreas.push_back(Area(36, 9, 2, 3.2, 9.9, 8, 3.6)); // underbrush (forest) 2
        this->environmentAreas.push_back(Area(36, 4, 0.1, 3.2, 9.9, 2, 3.6)); // underbrush (forest) 3
        this->environmentAreas.push_back(Area(39, 4, 8, 3.6, 9.9, 9, 8)); // tree1 (forest) 1
        this->environmentAreas.push_back(Area(40, 4, 9, 3.6, 9.9, 9.9, 8)); // tree2 (forest) 1
        this->environmentAreas.push_back(Area(39, 9, 2, 3.6, 9.9, 8, 8)); // tree1 (forest) 2
        this->environmentAreas.push_back(Area(39, 4, 1, 3.6, 9.9, 2, 8)); // tree1 (forest) 3
        this->environmentAreas.push_back(Area(41, 4, 0.1, 3.6, 9.9, 1, 8)); // tree3 (forest) 3
        this->environmentAreas.push_back(Area(38, 4, 8, 8, 9.9, 9.9, 10)); // air (forest) 1
        this->environmentAreas.push_back(Area(38, 9, 2, 8, 9.9, 8, 10)); // air (forest) 2
        this->environmentAreas.push_back(Area(38, 4, 0.1, 8, 9.9, 2, 10)); // air (forest) 3
        this->thePlayer.setXLocation(0.11); // set player start location
        this->thePlayer.setYLocation(5.0);
        this->thePlayer.setZLocation(2.5);
        this->thePlayer.setFacingCartesian(0.1, 0, 0.9);
        this->addUnit(aiUnit(87, 1.6, 1.38, 0.4)); // ???
        this->updateQuests(-1);
    }
    else {
        std::cout << "ERROR: Environment name " << environmentName << " not found in environment reference.";
    }
}

// forward functions to player so I don't have to make getPlayer() return as reference
bool Environment::turnPlayer(std::string direction, int degrees) {
    return this->thePlayer.turnPlayer(direction, degrees);
}
bool Environment::facePlayer(std::string direction) {
    return this->thePlayer.facePlayer(direction);
}
void Environment::turnPlayerToward(Unit targetUnit) {
    this->thePlayer.turnToward(targetUnit);
}
bool Environment::movePlayer(double distance) {
    if ((distance < 0) || (distance > this->thePlayer.getMaxMoveDistance())) {
        distance = this->thePlayer.getMaxMoveDistance();
    }
    bool successfulMove = true;
    //this->thePlayer.movePlayer(distance, this->xLimit, this->yLimit, this->zLimit);
    if (distance > this->intersectionPoint[3]) {
        if (this->thePlayer.canMoveIntoArea(this->environmentAreas.at(static_cast<int>(std::round(this->intersectionPoint[4]))).getID())) {
            std::cout << "You moved " << static_cast<int>(std::round(1000.0 * this->intersectionPoint[3])) / 10.0 << " cm into " <<
            this->environmentAreas.at(static_cast<int>(std::round(this->intersectionPoint[4]))).getName() << ".\n";
            // NOTE: the intersection point is a maximum of sqrt(3) * smallDistance from the actual intersection
            // Which occurs when each component is smallDistance from the intersection (diagonal of cube)
            // Move player into new area by using 2 * smallDistance since sqrt(3) ~ 1.7
            this->thePlayer.movePlayer(this->intersectionPoint[3] + 2 * constants::smallDistance, this->xLimit, this->yLimit, this->zLimit);
            double distanceLeft{ distance - this->intersectionPoint[3] };
            this->updateCurrArea();
            this->updateIntersectionPoint();
            this->movePlayer(distanceLeft);
        }
        else {
            // moved into area the player is not allowed to move into
            std::cout << "You moved " << static_cast<int>(std::round(1000.0 * this->intersectionPoint[3])) / 10.0 << " cm into " <<
                this->environmentAreas.at(static_cast<int>(std::round(this->intersectionPoint[4]))).getName() << " and had to stop.\n";
            this->thePlayer.setXLocation(this->intersectionPoint[0]);
            this->thePlayer.setYLocation(this->intersectionPoint[1]);
            this->thePlayer.setZLocation(this->intersectionPoint[2]);
        }
    }
    else {
        successfulMove = this->thePlayer.movePlayer(distance, this->xLimit, this->yLimit, this->zLimit);
        std::cout << "You moved " << static_cast<int>(std::round(1000.0 * distance)) / 10.0 << " cm through " <<
            this->environmentAreas.at(this->currArea).getName() << ".\n";
    }
    return successfulMove;
}

// Returns whether player is in an area where he will fall (i.e. air)
bool Environment::isPlayerFalling() {
    bool isFalling{ false };
    switch (this->environmentAreas.at(this->currArea).getID()) {
    case 7: // aquarium air
    case 19: // sewer air
    case 24:
    case 28:
    case 33:
    case 38:
    case 45:
    case 46:
    case 48:
        isFalling = true;
        break;
    }
    return isFalling;
}
// Makes player fall for the specified amount of time
void Environment::makePlayerFall(double timeElapsed) {
    // First calculate time to fall into the next area (quadratic formula on kinematic equation)
    double distanceToNextArea{ this->thePlayer.getZLocation() - this->environmentAreas.at(this->currArea).getZ1() };
    double timeToFall{ (std::sqrt(this->thePlayer.getVelocity()[2] * this->thePlayer.getVelocity()[2] +
        2 * constants::gravitationalPull * distanceToNextArea) + this->thePlayer.getVelocity()[2])
        / constants::gravitationalPull };

    // Kinematic equation to calculate distance fell
    if (timeToFall > timeElapsed) {
        double distanceFell{ -this->thePlayer.getVelocity()[2] * timeElapsed +
            0.5 * constants::gravitationalPull * timeElapsed * timeElapsed }; // positive
        this->thePlayer.setZLocation(this->thePlayer.getZLocation() - distanceFell);
        this->thePlayer.addDistanceTraveled(distanceFell);
        this->thePlayer.setZVelocity(this->thePlayer.getVelocity()[2] - constants::gravitationalPull * timeElapsed);
        std::cout << "Fell " << static_cast<int>(std::round(1000.0 * distanceFell)) / 10.0 << " cm through " <<
            this->environmentAreas.at(this->currArea).getName() << ".\n";
        this->resolveVelocityComponent(timeElapsed, 0, false);
        this->resolveVelocityComponent(timeElapsed, 1, false);
    }
    // Fall into next area
    else {
        // use virtual point (0.1 mm) to find new area, set player there, then evaluate
        double virtualPoint[3]{ this->thePlayer.getXLocation(), this->thePlayer.getYLocation(),
            this->thePlayer.getZLocation() - distanceToNextArea - constants::smallDistance };
        for (size_t i = 0; i < this->environmentAreas.size(); i++) {
            if (this->environmentAreas.at(i).pointIn(virtualPoint)) {
                // Recursively fall into next area
                if (this->thePlayer.canMoveIntoArea(this->environmentAreas.at(i).getID())) {
                    this->currArea = i;
                    this->thePlayer.setZLocation(this->thePlayer.getZLocation() -
                        distanceToNextArea - constants::smallDistance);
                    this->thePlayer.addDistanceTraveled(distanceToNextArea);
                    double newVelocity{ this->thePlayer.getVelocity()[2] - constants::gravitationalPull * timeToFall };
                    this->thePlayer.setZVelocity(newVelocity);
                    std::cout << "Fell " << static_cast<int>(std::round(1000.0 * distanceToNextArea)) / 10.0 <<
                        " cm into " << this->environmentAreas.at(i).getName() << ".\n";
                    double timeLeft{ timeElapsed - timeToFall }; // must be >= 0
                    if (this->isPlayerFalling()) { // if player falls in new area
                        this->resolveVelocityComponent(timeToFall, 0, false);
                        this->resolveVelocityComponent(timeToFall, 1, false);
                        this->makePlayerFall(timeLeft);
                    }
                    else {
                        // Resolve xy velocity for time already used before moving onto next variable
                        this->resolveVelocityComponent(timeToFall, 0, false);
                        this->resolveVelocityComponent(timeToFall, 1, false);
                        this->resolveVelocityComponent(timeLeft, 2, true);
                        this->resolveVelocityComponent(timeLeft, 0, true);
                        this->resolveVelocityComponent(timeLeft, 1, true);
                    }
                }
                // Or land and get damaged
                else {
                    this->thePlayer.setZLocation(this->thePlayer.getZLocation() - distanceToNextArea + constants::smallDistance);
                    this->thePlayer.addDistanceTraveled(distanceToNextArea);
                    // Need to calculate new velocity, then calculate damage, then set velocity to 0
                    double newVelocity{ this->thePlayer.getVelocity()[2] - constants::gravitationalPull * timeToFall };
                    int landDamage{ static_cast<int>(std::floor(std::abs(constants::landDamageCoefficient * newVelocity))) };
                    this->thePlayer.setZVelocity(0.0);
                    this->thePlayer.takeDamage(landDamage);
                    std::cout << "Fell " << static_cast<int>(std::round(1000.0 * distanceToNextArea)) / 10.0 <<
                        " cm onto " << this->environmentAreas.at(i).getName();
                    if (landDamage > 0) {
                        std::cout << " and took " << landDamage << " damage.\n";
                    }
                    else {
                        std::cout << ".\n";
                    }
                    this->resolveVelocityComponent(timeElapsed, 0, false);
                    this->resolveVelocityComponent(timeElapsed, 1, false);
                }
                break;
            }
        }
    }
}

// Resolves velocity vector
void Environment::resolveVelocity(double timeElapsed) {
    if (this->isPlayerFalling()) {
        std::cout << "ERROR: Resolve player falling before resolving velocity component.\n";
    }
    else {
        this->resolveVelocityComponent(timeElapsed, 0, true);
        this->resolveVelocityComponent(timeElapsed, 1, true);
        this->resolveVelocityComponent(timeElapsed, 2, true);
    }
}
void Environment::resolveVelocityComponent(double timeElapsed, int component, bool friction) {
    if (std::abs(this->thePlayer.getVelocity()[component]) > constants::smallVelocity) {
        int areaComponent{ component };
        if (this->thePlayer.getVelocity()[component] > 0) { // access x2/y2/z2 of area
            areaComponent += 3;
        }
        double distanceToNextArea{ this->environmentAreas.at(this->currArea).getPoint(areaComponent) - this->thePlayer.getLocation(component) }; // When I perform the subtraction here it is just wrong (??)
        double timeToReach{};
        double distanceMoved{};
        double frictionCoeff{ 0 };
        // Calculate distance moved if 
        if (friction) {
            frictionCoeff = constants::frictionCoefficient;
            distanceMoved = (this->thePlayer.getVelocity()[component] / constants::frictionCoefficient) * (1 - std::exp(-constants::frictionCoefficient * timeElapsed));
        }
        else {
            distanceMoved = this->thePlayer.getVelocity()[component] * timeElapsed;
        }
        double newVelocity{this->thePlayer.getVelocity()[component] - distanceMoved * frictionCoeff};
        if (std::abs(newVelocity) < constants::smallVelocity) {
            newVelocity = 0.0;
        }
        int hitDamage{};
        // Move within an area
        if (std::abs(distanceToNextArea) > std::abs(distanceMoved)) {
            this->thePlayer.setLocationComponent(this->thePlayer.getLocation(component) + distanceMoved, component);
            this->thePlayer.addDistanceTraveled(distanceMoved);
            this->thePlayer.setVelocityComponent(newVelocity, component);
            this->printVelocityComponentMovedInformation(distanceMoved, component);
        }
        // Move into new area
        else {
            // Set virtual point in new area
            double virtualPoint[3]{ this->thePlayer.getXLocation(), this->thePlayer.getYLocation(), this->thePlayer.getZLocation()};
            virtualPoint[component] += distanceToNextArea * (1 + constants::smallDistance);
            for (size_t i = 0; i < this->environmentAreas.size(); i++) {
                // Find new area
                if (this->environmentAreas.at(i).pointIn(virtualPoint)) {
                    // Recursively move into area
                    if (this->thePlayer.canMoveIntoArea(this->environmentAreas.at(i).getID())) {
                        // adjust distance / velocity for smaller distance traveled
                        distanceMoved = distanceToNextArea * (1 + constants::smallDistance);
                        newVelocity = this->thePlayer.getVelocity()[component] - distanceToNextArea * frictionCoeff;
                        if (std::abs(newVelocity) < constants::smallVelocity) {
                            newVelocity = 0.0;
                        }
                        if (friction) {
                            timeToReach = - std::log(1 - distanceToNextArea * constants::frictionCoefficient / this->thePlayer.getVelocity()[component]) / constants::frictionCoefficient;
                        }
                        else {
                            timeToReach = distanceToNextArea / this->thePlayer.getVelocity()[component] ;
                        }
                        this->thePlayer.setLocationComponent(this->thePlayer.getLocation(component) + distanceMoved, component);
                        this->thePlayer.addDistanceTraveled(distanceMoved);
                        this->thePlayer.setVelocityComponent(newVelocity, component);
                        this->printVelocityComponentMovedInformation(distanceMoved, component);
                        this->currArea = i;
                        double timeLeft{ timeElapsed - timeToReach }; // must be >= 0
                        if (this->isPlayerFalling()) { // if player falls in new area
                            this->makePlayerFall(timeLeft);
                        }
                        else { // new area is a liquid
                            this->resolveVelocityComponent(timeLeft, component, true);
                        }
                    }
                    // Or hit wall and get damaged
                    else {
                        // Adjust distance moved / velocity and calculate damage
                        distanceMoved = distanceToNextArea * (1 - constants::smallDistance);
                        // Need to calculate new velocity, then calculate damage, then set velocity to 0.0
                        newVelocity = this->thePlayer.getVelocity()[component] - distanceToNextArea * frictionCoeff;
                        hitDamage = static_cast<int>(std::floor(std::abs(constants::landDamageCoefficient * newVelocity)));
                        this->thePlayer.setVelocityComponent(0.0, component);
                        this->printVelocityComponentMovedInformation(distanceMoved, component);
                        this->thePlayer.takeDamage(hitDamage);
                        this->thePlayer.setLocationComponent(this->thePlayer.getLocation(component) + distanceMoved, component);
                        this->thePlayer.addDistanceTraveled(distanceMoved);
                        std::cout << "Moved into " << this->environmentAreas.at(i).getName();
                        if (hitDamage > 0) {
                            std::cout << " and took " << hitDamage << " damage";
                        }
                        std::cout << ".\n";
                    }
                    // break out of searching for new environment areas
                    break;
                }
            } // for loop
        } // else moving into new area
    } // if velocity large enough to be relevant (needed to avoid divide by 0)
}
void Environment::printVelocityComponentMovedInformation(double distanceMoved, int component) {
    if (this->thePlayer.getUpgradeAttention2()) {
        std::cout << "Moved " << static_cast<int>(std::round(1000.0 * distanceMoved)) / 10.0 << " cm in " <<
            this->environmentAreas.at(this->currArea).getName() << " in the ";
        if (component == 0) {
            std::cout << "x direction.\n";
        }
        else if (component == 1) {
            std::cout << "y direction.\n";
        }
        else {
            std::cout << "z direction.\n";
        }
    }
    else {
        std::cout << "Moved " << static_cast<int>(std::round(std::abs(1000.0 * distanceMoved))) / 10.0 << " cm in " <<
            this->environmentAreas.at(this->currArea).getName() << ".\n";
    }
}

// Player looks around; returns indiced vector of unit/key pairs one can see
void Environment::playerLook() {
    this->updateUnitsSeen();
    this->updateItemsSeen();
    this->updateCurrArea();
    this->updateIntersectionPoint();
    this->printPlayerView();
}
void Environment::updateUnitsSeen() {
    this->unitsSeen.clear();
    for (std::pair<const int, aiUnit>& currUnit : this->otherUnits) { // see units
        if (this->thePlayer.playerCanSee(currUnit.second)) {
            this->unitsSeen.push_back(currUnit.first);
            // quest counter
            if (this->totalUnitsSeen.find(currUnit.second.getUnitID()) == this->totalUnitsSeen.end()) {
                this->totalUnitsSeen.emplace(currUnit.second.getUnitID(), 1);
            }
            else {
                this->totalUnitsSeen.at(currUnit.second.getUnitID())++;
            }
        }
    }
}
void Environment::updateItemsSeen() {
    this->itemsSeen.clear();
    for (std::pair<const int, Item>& currItem : this->droppedItems) { // see items
        if (this->thePlayer.playerCanSee(currItem.second)) {
            this->itemsSeen.push_back(currItem.first);
            // quest counter
            if (this->totalItemsSeen.find(currItem.second.getID()) == this->totalItemsSeen.end()) {
                this->totalItemsSeen.emplace(currItem.second.getID(), 1);
            }
            else {
                this->totalItemsSeen.at(currItem.second.getID())++;
            }
        }
    }
}

// Forward function to remove player energy
int Environment::addPlayerEnergy(int amount, bool maxout) {
    return this->thePlayer.increaseEnergy(amount, maxout);
}
// Forward function to use player energy
void Environment::removePlayerEnergy(int amount) {
    this->thePlayer.lowerEnergy(amount);
}

// Updates the currArea
void Environment::updateCurrArea() {
    for (size_t i = 0; i < this->environmentAreas.size(); i++) {
        if (this->environmentAreas.at(i).unitIn(this->thePlayer)) { // reset currArea
            this->currArea = i;
            break;
        }
    }
}
// Checks the currArea to see if player still in it
bool Environment::inNewArea() {
    bool inNewArea = false;
    for (size_t i = 0; i < this->environmentAreas.size(); i++) {
        if (this->environmentAreas.at(i).unitIn(this->thePlayer)) {
            if (i != this->currArea) {
                inNewArea = true;
            }
            break;
        }
    }
    return inNewArea;
}
// Returns index of area player is in (doesn't update currArea)
int Environment::areaInNow() {
    int areaIn{};
    for (size_t i = 0; i < this->environmentAreas.size(); i++) {
        if (this->environmentAreas.at(i).unitIn(this->thePlayer)) {
            areaIn = i;
            break;
        }
    }
    return areaIn;
}
int Environment::areaInNow(Unit inputUnit) {
    int areaIn{};
    for (size_t i = 0; i < this->environmentAreas.size(); i++) {
        if (this->environmentAreas.at(i).unitIn(inputUnit)) {
            areaIn = i;
            break;
        }
    }
    return areaIn;
}
int Environment::areaInNow(Item inputItem) {
    int areaIn{};
    for (size_t i = 0; i < this->environmentAreas.size(); i++) {
        if (this->environmentAreas.at(i).itemIn(inputItem)) {
            areaIn = i;
            break;
        }
    }
    return areaIn;
}

// Updates the current intersection point. Should always come after updating CurrArea or turning
void Environment::updateIntersectionPoint() {
    // first calculate 'time' for the playerFacing vector to reach each component's wall
    double xTime{};
    double yTime{};
    double zTime{};
    bool infinityTracker[3] = { false, false, false }; // track infinite time but avoid divide by 0
    if (this->thePlayer.getXFacing() > 0) { // 'distance' / 'speed' = 'time'
        xTime = (this->environmentAreas.at(this->currArea).getX2() -
            this->thePlayer.getXLocation()) / this->thePlayer.getXFacing();
    }
    else if (this->thePlayer.getXFacing() < 0) {
        xTime = (this->environmentAreas.at(this->currArea).getX1() -
            this->thePlayer.getXLocation()) / this->thePlayer.getXFacing();
    }
    else {
        infinityTracker[0] = true;
    }
    if (this->thePlayer.getYFacing() > 0) {
        yTime = (this->environmentAreas.at(this->currArea).getY2() -
            this->thePlayer.getYLocation()) / this->thePlayer.getYFacing();
    }
    else if (this->thePlayer.getYFacing() < 0) {
        yTime = (this->environmentAreas.at(this->currArea).getY1() -
            this->thePlayer.getYLocation()) / this->thePlayer.getYFacing();
    }
    else {
        infinityTracker[1] = true;
    }
    if (this->thePlayer.getZFacing() > 0) {
        zTime = (this->environmentAreas.at(this->currArea).getZ2() -
            this->thePlayer.getZLocation()) / this->thePlayer.getZFacing();
    }
    else if (this->thePlayer.getZFacing() < 0) {
        zTime = (this->environmentAreas.at(this->currArea).getZ1() -
            this->thePlayer.getZLocation()) / this->thePlayer.getZFacing();
    }
    else {
        infinityTracker[2] = true;
    }

    // now see which component will reach its wall first and create virtual point
    double virtualPoint[3] { this->thePlayer.getXLocation(), this->thePlayer.getYLocation(),
        this->thePlayer.getZLocation() }; // these initial values necessary in case of infinity
    this->intersectionPoint[0] = this->thePlayer.getXLocation();
    this->intersectionPoint[1] = this->thePlayer.getYLocation();
    this->intersectionPoint[2] = this->thePlayer.getZLocation();
    double smallestTime{}; // 'time' it would take to reach area border
    if (((xTime < yTime) || (infinityTracker[1])) && ((xTime < zTime) || (infinityTracker[2])) &&
        (!infinityTracker[0])) { // xTime smallest
        smallestTime = xTime;
    }
    else if (((yTime < zTime) || (infinityTracker[2])) && (!infinityTracker[1])) { // yTime smallest
        smallestTime = yTime;
    }
    else if (!infinityTracker[2]) { // zTime smallest
        smallestTime = zTime;
    }
    else {
        std::cout << "ERROR: All times to vitual point infinite. Check player facing direction.\n";
    }
    // intersectX = xLoc + time * xFac
    if (!(infinityTracker[0])) {
        virtualPoint[0] = this->thePlayer.getXLocation() +
            (smallestTime + constants::smallDistance) * this->thePlayer.getXFacing();
        this->intersectionPoint[0] = this->thePlayer.getXLocation() +
            (smallestTime - constants::smallDistance) * this->thePlayer.getXFacing();
    }
    if (!(infinityTracker[1])) {
        virtualPoint[1] = this->thePlayer.getYLocation() +
            (smallestTime + constants::smallDistance) * this->thePlayer.getYFacing();
        this->intersectionPoint[1] = this->thePlayer.getYLocation() +
            (smallestTime - constants::smallDistance) * this->thePlayer.getYFacing();
    }
    if (!(infinityTracker[2])) {
        virtualPoint[2] = this->thePlayer.getZLocation() +
            (smallestTime + constants::smallDistance)* this->thePlayer.getZFacing();
        this->intersectionPoint[2] = this->thePlayer.getZLocation() +
            (smallestTime - constants::smallDistance) * this->thePlayer.getZFacing();
    }

    // determine distance from player to border (minus small amount)
    this->intersectionPoint[3] = std::sqrt((this->thePlayer.getXLocation() - this->intersectionPoint[0]) *
        (this->thePlayer.getXLocation() - this->intersectionPoint[0]) + (this->thePlayer.getYLocation() -
            this->intersectionPoint[1]) * (this->thePlayer.getYLocation() - this->intersectionPoint[1]) +
        (this->thePlayer.getZLocation() - this->intersectionPoint[2]) * (this->thePlayer.getZLocation() -
            this->intersectionPoint[2])); // distance formula
        // determine area the player is looking at using the virtual point
    for (size_t i = 0; i < this->environmentAreas.size(); i++) {
        if (this->environmentAreas.at(i).pointIn(virtualPoint)) {
            this->intersectionPoint[4] = i; // area index found
            break;
        }
    }
}

// Prints to screen environment information the player can view
void Environment::printPlayerView() {
    // so (0 = front, 1 = right, 2 = left-above, 3 = above, 4 = right-above, etc...)
    if ((this->thePlayer.getUpgradeAttention2()) || (constants::TESTMODE)) {
        std::cout << "In: " << this->environmentAreas.at(this->currArea).getName() << "\n";
        std::cout << "Front: ";
        if (this->intersectionPoint[3] > this->thePlayer.getViewDistance()) {
            std::cout << "more " << this->environmentAreas.at(this->currArea).getName();
        }
        else {
            std::cout << this->environmentAreas.at(static_cast<int>(this->intersectionPoint[4])).getName();
        }
        using clock_t = std::unordered_map<int, std::vector<std::string>>;
        clock_t playerViewStrings = { // clock code : messages
            {0, std::vector<std::string>{}}, {1, std::vector<std::string>{}}, {2, std::vector<std::string>{}},
            {3, std::vector<std::string>{}}, {4, std::vector<std::string>{}}, {5, std::vector<std::string>{}},
            {6, std::vector<std::string>{}}, {7, std::vector<std::string>{}}, {8, std::vector<std::string>{}} };
        if ((this->unitsSeen.size() > 0) && (!ignore_units)) {
            std::cout << "\n\nindex: (dimension, level) unit name (notes)\n";
            for (size_t i = 0; i < this->unitsSeen.size(); i++) {
                std::string inputString{ std::to_string(i + 1) + ": (" + std::to_string(this->otherUnits.at(unitsSeen.at(i)).getLevel()
                    / 25 + 1) + ", " + std::to_string(this->otherUnits.at(unitsSeen.at(i)).getLevel()) + ") " +
                    this->otherUnits.at(unitsSeen.at(i)).getName() };
                if ((this->otherUnits.at(unitsSeen.at(i)).getView_Distance() <= this->thePlayer.getMaxMoveDistance()) && (this->thePlayer.canMoveIntoArea(
                        this->environmentAreas.at(this->areaInNow(this->otherUnits.at(unitsSeen.at(i)))).getID()))) {
                    if (this->otherUnits.at(unitsSeen.at(i)).getCoolDown() > 0) {
                        inputString += " (cooldown: " + core_functions::secondsToTimeString(this->otherUnits.at(unitsSeen.at(i)).getCoolDown(), 2) + ")";
                    }
                    else {
                        inputString += " (in range)";
                    }
                }
                if (this->ignore_spatial) {
                    std::cout << inputString << "\n";
                }
                else {
                    // add to appropriate vector
                    playerViewStrings.at(this->otherUnits.at(unitsSeen.at(i)).getView_Clock()).push_back(inputString);
                }
            }
            if (!this->ignore_spatial) {
                this->printPlayerViewStrings(playerViewStrings);
            }
        }
        playerViewStrings = { // clock code : messages
            {0, std::vector<std::string>{}}, {1, std::vector<std::string>{}}, {2, std::vector<std::string>{}},
            {3, std::vector<std::string>{}}, {4, std::vector<std::string>{}}, {5, std::vector<std::string>{}},
            {6, std::vector<std::string>{}}, {7, std::vector<std::string>{}}, {8, std::vector<std::string>{}} };
        if ((this->itemsSeen.size() > 0) && (!this->ignore_items)) {
            std::cout << "\n\nindex: (dimension) item name (notes)\n";
            for (size_t i = 0; i < this->itemsSeen.size(); i++) {
                std::string inputString{ std::to_string(i + 1) + ": (" + std::to_string(this->droppedItems.at(itemsSeen.at(i)).getLevel()
                    / 25 + 1) + ", " + std::to_string(this->droppedItems.at(itemsSeen.at(i)).getLevel()) + ") " +
                    this->droppedItems.at(itemsSeen.at(i)).getName() };
                if ((this->droppedItems.at(itemsSeen.at(i)).getView_Distance() <= this->thePlayer.getMaxMoveDistance()) && (this->thePlayer.canMoveIntoArea(
                        this->environmentAreas.at(this->areaInNow(this->droppedItems.at(itemsSeen.at(i)))).getID()))) {
                    inputString += " (in range)";
                }
                if (this->ignore_spatial) {
                    std::cout << inputString << "\n";
                }
                else {
                    // add to appropriate vector
                    playerViewStrings.at(this->droppedItems.at(itemsSeen.at(i)).getView_Clock()).push_back(inputString);
                }
            }
            if (!this->ignore_spatial) {
                this->printPlayerViewStrings(playerViewStrings);
            }
        }
    }
    else if (this->thePlayer.getUpgradeAttention1()) {
        std::cout << "In " << this->environmentAreas.at(this->currArea).getName() << ".\n";
        if (this->intersectionPoint[3] > this->thePlayer.getViewDistance()) {
            std::cout << "All you see is more " << this->environmentAreas.at(this->currArea).getName()
                << " as far as you can see.\n";
        }
        else {
            std::cout << "You see " << this->environmentAreas.at(static_cast<int>(this->intersectionPoint[4])).getName()
                << " in front of you.\n";
        }
        std::unordered_map<int, std::vector<std::string>> playerViewStrings = { // clock code : messages
            {0, std::vector<std::string>{}}, {1, std::vector<std::string>{}}, {2, std::vector<std::string>{}} };
        if ((this->unitsSeen.size() > 0) && (!this->ignore_units)) {
            std::cout << "Units seen (with index to interact):\n";
            for (size_t i = 0; i < this->unitsSeen.size(); i++) {
                std::string inputString{ std::to_string(i + 1) + ": (lev " + std::to_string(
                    this->otherUnits.at(unitsSeen.at(i)).getLevel()) + ") " + this->otherUnits.at(unitsSeen.at(i)).getName() };
                if ((this->thePlayer.distanceToUnit(this->otherUnits.at(unitsSeen.at(i))) <=
                    this->thePlayer.getMaxMoveDistance()) && (this->thePlayer.canMoveIntoArea(
                        this->environmentAreas.at(this->areaInNow(this->otherUnits.at(unitsSeen.at(i)))).getID()))) {
                    if (this->otherUnits.at(unitsSeen.at(i)).getCoolDown() > 0) {
                        inputString += " (cooldown: " + core_functions::secondsToTimeString(this->otherUnits.at(unitsSeen.at(i)).getCoolDown(), 2) + ")";
                    }
                    else {
                        inputString += " (in range)";
                    }
                }
                if (this->ignore_spatial) {
                    std::cout << inputString << "\n";
                }
                else {
                    // add to appropriate vector (just have left, front, right)
                    playerViewStrings.at(this->otherUnits.at(unitsSeen.at(i)).getView_Clock() % 3).push_back(inputString);
                }
            }
            if (!this->ignore_spatial) {
                this->printPlayerViewStringsShort(playerViewStrings);
            }
        }
        playerViewStrings = { {0, std::vector<std::string>{}}, {1, std::vector<std::string>{}}, {2, std::vector<std::string>{}} };
        if ((this->itemsSeen.size() > 0) && (!this->ignore_items)) {
            std::cout << "Items seen (with index to interact):\n";
            for (size_t i = 0; i < this->itemsSeen.size(); i++) {
                std::string inputString{ std::to_string(i + 1) + ": " + this->droppedItems.at(itemsSeen.at(i)).getName() };
                if ((this->thePlayer.distanceToItem(this->droppedItems.at(itemsSeen.at(i))) <=
                    this->thePlayer.getMaxMoveDistance()) && (this->thePlayer.canMoveIntoArea(
                        this->environmentAreas.at(this->areaInNow(this->droppedItems.at(itemsSeen.at(i)))).getID()))) {
                    inputString += " (in range)";
                }
                if (this->ignore_spatial) {
                    std::cout << inputString << "\n";
                }
                else {
                    // add to appropriate vector (just have left, front, right)
                    playerViewStrings.at(this->droppedItems.at(itemsSeen.at(i)).getView_Clock() % 3).push_back(inputString);
                }
            }
            if (!this->ignore_spatial) {
                this->printPlayerViewStringsShort(playerViewStrings);
            }
        }
    }
    else {
        std::cout << "In " << this->environmentAreas.at(this->currArea).getName() << ".\n";
        if (this->intersectionPoint[3] > this->thePlayer.getViewDistance()) {
            std::cout << "All you see is more " << this->environmentAreas.at(this->currArea).getName()
                << " as far as you can see.\n";
        }
        else {
            std::cout << "You see " << this->environmentAreas.at(static_cast<int>(this->intersectionPoint[4])).getName()
                << " in front of you.\n";
        }
        if ((this->unitsSeen.size() > 0) && (!this->ignore_units)) {
            std::cout << "Units seen (with index to interact):\n";
            for (size_t i = 0; i < this->unitsSeen.size(); i++) {
                std::cout << (i + 1) << ": " << this->otherUnits.at(unitsSeen.at(i)).getName();
                if (this->otherUnits.at(unitsSeen.at(i)).getCoolDown() > 0) {
                    std::cout << " (cooldown: " << core_functions::secondsToTimeString(this->otherUnits.at(unitsSeen.at(i)).getCoolDown(), 2) << ")";
                }
                std::cout << "\n";
            }
        }
        if ((this->itemsSeen.size() > 0) && (!this->ignore_items)) {
            std::cout << "Items seen (with index to interact):\n";
            for (size_t i = 0; i < this->itemsSeen.size(); i++) {
                std::cout << (i + 1) << ": " << this->droppedItems.at(itemsSeen.at(i)).getName() << "\n";
            }
        }
    }
    std::cout << "\n";
}
// (0 = top-left, 1 = top-front, 2 = top-right, 3 = left, 4 = front, 5 = right, 6 = bottom-left, ...)
void Environment::printPlayerViewStrings(std::unordered_map<int, std::vector<std::string>> inputMap) {
    size_t largestVector{ 0 };
    for (size_t i = 0; i < 3; i++, largestVector = 0) { // for each row
        // find largest grouping
        for (size_t j = 0; j < 3; j++) {
            if (inputMap.at(j + 3 * i).size() > largestVector) {
                largestVector = inputMap.at(j + 3 * i).size();
            }
        }
        // fill in gaps
        for (size_t j = 0; j < 3; j++) {
            for (size_t k = 0; k < largestVector - inputMap.at(j + 3 * i).size(); ) {
                inputMap.at(j + 3 * i).push_back("");
            }
        }
        // print header
        if (i == 0) { // top
            if (largestVector > 0) {
                std::cout << "Top Left:" + core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - 9) +
                    "Top:" + core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - 4) + "Top Right:\n";
            }
        }
        else if (i == 1) { // front
            if (largestVector > 0) {
                std::cout << "Left:" + core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - 5) +
                    "Front:" + core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - 6) + "Right:\n";
            }
        }
        else { // bottom
            if (largestVector > 0) {
                std::cout << "Bottom Left:" + core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - 12) +
                    "Bottom:" + core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - 7) + "Bottom Right:\n";
            }
        }
        // print each line
        for (size_t j = 0; j < largestVector; j++) {
            // truncate if > 29 characters
            for (size_t k = 0; k < 3; k++) {
                if (inputMap.at(k + 3 * i).at(j).size() > constants::printViewSpatialSize / 3 - 1) {
                    std::string tests = inputMap.at(k + 3 * i).at(j).substr(0, constants::printViewSpatialSize / 3 - 4) + "...";
                    inputMap.at(k + 3 * i).at(j) = tests;
                }
            }
            // print lines
            std::cout << inputMap.at(3 * i).at(j) << core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - inputMap.at(3 * i).at(j).size());
            std::cout << inputMap.at(1 + 3 * i).at(j) << core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - inputMap.at(1 + 3 * i).at(j).size());
            std::cout << inputMap.at(2 + 3 * i).at(j) << "\n";
        }
        std::cout << "\n";
    }
}
void Environment::printPlayerViewStringsShort(std::unordered_map<int, std::vector<std::string>> inputMap) {
    size_t largestVector{ 0 };
    // find largest grouping
    for (size_t j = 0; j < 3; j++) {
        if (inputMap.at(j).size() > largestVector) {
            largestVector = inputMap.at(j).size();
        }
    }
    // fill in gaps
    for (size_t j = 0; j < 3; j++) {
        for (size_t k = 0; k < largestVector - inputMap.at(j).size(); ) {
            inputMap.at(j).push_back("");
        }
    }
    // print header
    if (largestVector > 0) {
        std::cout << "Left:" + core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - 5) +
            "Front:" + core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - 6) + "Right:\n";
    }
    // print each line
    for (size_t j = 0; j < largestVector; j++) {
        // truncate if > 29 characters
        for (size_t k = 0; k < 3; k++) {
            if (inputMap.at(k).at(j).size() > constants::printViewSpatialSize / 3 - 1) {
                std::string tests = inputMap.at(k).at(j).substr(0, constants::printViewSpatialSize / 3 - 4) + "...";
                inputMap.at(k).at(j) = tests;
            }
        }
        // print lines
        std::cout << inputMap.at(0).at(j) << core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - inputMap.at(0).at(j).size());
        std::cout << inputMap.at(1).at(j) << core_functions::stringMultiply(" ", constants::printViewSpatialSize / 3 - inputMap.at(1).at(j).size());
        std::cout << inputMap.at(2).at(j) << "\n";
    }
    std::cout << "\n";
}

// Adds a new unit to the environment
void Environment::addUnit(aiUnit newUnit, int areaIndex) {
    this->otherUnits.emplace(this->unitKey, newUnit);
    if (areaIndex < 0) {
        for (Area& i : this->environmentAreas) {
            if (i.unitIn(newUnit)) {
                i.addUnitKey(this->unitKey);
                break;
            }
        }
    }
    else if (areaIndex >= this->environmentAreas.size()) {
        std::cout << "ERROR: area index " << areaIndex << " out of range.\n";
    }
    else {
        this->environmentAreas.at(areaIndex).addUnitKey(this->unitKey);
    }
    this->unitKey++;
}
void Environment::addUnitRandomlyInArea(aiUnit newUnit, int areaIndex, int amount) {
    if (areaIndex < 0 || areaIndex >= this->environmentAreas.size()) {
        std::cout << "ERROR: area index " << areaIndex << " out of range.\n";
        return;
    }
    for (size_t i = 0; i < amount; i++) {
        newUnit.setXLocation(core_functions::randomDouble(this->environmentAreas.at(areaIndex).getX1(),
            this->environmentAreas.at(areaIndex).getX2()));
        newUnit.setYLocation(core_functions::randomDouble(this->environmentAreas.at(areaIndex).getY1(),
            this->environmentAreas.at(areaIndex).getY2()));
        newUnit.setZLocation(core_functions::randomDouble(this->environmentAreas.at(areaIndex).getZ1(),
            this->environmentAreas.at(areaIndex).getZ2()));
        this->addUnit(newUnit, areaIndex);
    }
}

// Updates after a battle
void Environment::updateCurrUnit(aiUnit currUnit) {
    this->otherUnits.at(this->currKey) = currUnit;
}
void Environment::removeCurrUnit() {
    std::vector<std::string> dropMessages{};
    dropMessages.push_back(this->otherUnits.at(this->currKey).getName() + " dropped:\n");
    for (std::pair<int, int> i : this->otherUnits.at(this->currKey).getDrops()) {
        int maxDrop{ 1 };
        double probDrop{ constants::baseDropProbability };
        double luckFactor{ this->thePlayer.getLuckFactor() };
        switch (i.second) {
            case -1: // guaranteed drop
                probDrop = 1.0;
                break;
            case -2: // 80% chance
                probDrop = constants::largeDropProbability;
                break;
            case -3: // 50% chance (same as default)
                break;
            case -4: // 20% chance
                probDrop = constants::smallDropProbability;
                break;
            case -5: // 5% chance
                probDrop = constants::tinyDropProbability;
                break;
            case -8:
                luckFactor *= constants::itemDropWorseLuck;
                break;
            case -9: // less luck
                luckFactor *= constants::itemDropBadLuck;
                break;
            case -10: // default luck
                break;
            case -11: // more luck
                luckFactor *= constants::itemDropGoodLuck;
                break;
            case -12:
                luckFactor *= constants::itemDropBetterLuck;
                break;
            default: // 50%
                maxDrop = i.second;
                break;
        }
        probDrop *= this->thePlayer.getLuckFactor(); // player luck affects drop probability
        int numDropped{ 0 }; // subsequent drops have less probability
        for (int j = 0; j < maxDrop; j++) {
            Item newItem = Item(i.first, luckFactor,
                this->otherUnits.at(this->currKey).getXLocation(),
                this->otherUnits.at(this->currKey).getYLocation(),
                this->otherUnits.at(this->currKey).getZLocation());
            if (core_functions::linearProbability(probDrop / (1.0 + constants::subsequentDropMultiplier * numDropped))) {
                dropMessages.push_back("   -" + newItem.getName() + "\n");
                if (this->pickup_drops) {
                    this->inventoryItem(newItem);
                }
                else {
                    this->addItem(newItem);
                }
                numDropped++;
            }
            // Drop materials of each item as well
            for (int mat : newItem.getItemMaterials()) {
                if (core_functions::linearProbability(constants::materialDropRate * this->thePlayer.getLuckFactor())) {
                    Item matItem = Item(mat, luckFactor,
                        this->otherUnits.at(this->currKey).getXLocation(),
                        this->otherUnits.at(this->currKey).getYLocation(),
                        this->otherUnits.at(this->currKey).getZLocation());
                    dropMessages.push_back("   -" + matItem.getName() + "\n");
                    if (this->pickup_drops) {
                        this->inventoryItem(matItem);
                    }
                    else {
                        this->addItem(matItem);
                    }
                }
            } // newItem mats
        }
    } // drop loop
    if (dropMessages.size() > 1) {
        std::cout << this->otherUnits.at(this->currKey).getName() << " dropped:\n";
        for (std::string i : dropMessages) {
            std::cout << i;
        }
    }
    // quest counter
    if (this->totalUnitsKilled.find(this->otherUnits.at(this->currKey).getUnitID()) == this->totalUnitsKilled.end()) {
        this->totalUnitsKilled.emplace(this->otherUnits.at(this->currKey).getUnitID(), 1);
    }
    else {
        this->totalUnitsKilled.at(this->otherUnits.at(this->currKey).getUnitID())++;
    }
    // actually remove unit now
    this->otherUnits.erase(this->currKey);
    // remove from area index
    for (Area& i : this->environmentAreas) {
        if (i.removeUnitKey(this->currKey)) {
            break;
        }
    }
}

// Add a new item to the environment
void Environment::addItem(Item newItem) {
    this->droppedItems.emplace(this->itemKey, newItem);
    this->itemKey++;
}

// Function to pass player rewards through the environment
void Environment::playerRewards(std::vector<int> rewards) {
    if (rewards.size() == 3) {
        this->playerRewards(rewards.at(0), rewards.at(1), rewards.at(2));
    }
    else {
        std::cout << "ERROR: rewards vector not correct size.\n";
    }
}
void Environment::playerRewards(int xpReward, int creditReward, int foulReward) {
    if (this->xpBonusLength > 0) {
        xpReward *= 2;
    }
    if (this->creditBonusLength > 0) {
        creditReward *= 2;
    }
    if (this->foulBonusLength > 0) {
        foulReward *= 2;
    }
    std::cout << "You earned " << xpReward << " XP, " << creditReward <<
        " credits, and " << foulReward << " fouls.\n";
    this->playerIntersectionBuffer += this->thePlayer.addExperience(xpReward);
    this->thePlayer.addCredits(creditReward);
    this->thePlayer.addFouls(foulReward);
}
// Function to pass player upgrades through the environment
int Environment::upgradePlayer(int tier) {
    return this->thePlayer.chooseNextUpgrade(tier);
}

// All the temporal events in the environment happen here
bool Environment::timeEvents(double timeElapsed, bool reloadEnvironment) {
    bool enemyAttack{ false };
    this->spawnUnits(timeElapsed);
    this->thePlayer.regenerate(timeElapsed);
    xpBonusLength = std::max(0.0, xpBonusLength - timeElapsed);
    creditBonusLength = std::max(0.0, creditBonusLength - timeElapsed);
    foulBonusLength = std::max(0.0, foulBonusLength - timeElapsed);
    luckBonusLength = std::max(0.0, luckBonusLength - timeElapsed);
    visionBonusLength = std::max(0.0, visionBonusLength - timeElapsed);
    speedBonusLength = std::max(0.0, speedBonusLength - timeElapsed);
    spawnBonusLength = std::max(0.0, spawnBonusLength - timeElapsed);
    // Unit cooldown timers and ally unit timers
    for (std::pair<const int, aiUnit>& i : this->otherUnits) {
        i.second.reduceCoolDown(timeElapsed);
        if (i.second.getAllyState() == 0) {
            switch (i.second.getMaxHerd()) {
                // Energy = # items selling
                case -1: // peddler
                case -2: // vendor
                case -3: // huckster
                case -7: // broker
                case -8: // merchant
                case -9: // master merchant
                    i.second.setAttackProbability(i.second.getAttackProbability() - timeElapsed);
                    if (i.second.getAttackProbability() < 0) {
                        i.second.setAttackProbability(constants::shopRestockTime);
                        i.second.shuffleItemInventory();
                    }
                    break;
                // Energy = # upgrades/abilities/quests/pets available
                case -11: // researcher
                    i.second.setAttackProbability(i.second.getAttackProbability() - timeElapsed);
                    if (i.second.getAttackProbability() < 0) {
                        i.second.setAttackProbability(constants::upgradeRestockTime);
                        i.second.shuffleUpgradeInventory();
                    }
                    break;
                case -12: // trainer
                    i.second.setAttackProbability(i.second.getAttackProbability() - timeElapsed);
                    if (i.second.getAttackProbability() < 0) {
                        i.second.setAttackProbability(constants::abilityRestockTime);
                        i.second.shuffleAbilityInventory();
                    }
                    break;
                case -13: // solicitor
                    break;
                case -14: // handler
                    break;
            }
        }
    }
    if (reloadEnvironment) { // if loading save game don't allow for enemy to attack you or velocity resolution/creation
        return false;
    }
    // Check if other unit attacks you
    if (this->thePlayer.getStatusAlive()) {
        for (size_t i = 0; i < this->unitsSeen.size(); i++) {
            if (this->otherUnits.at(unitsSeen.at(i)).getAllyState() == 2) { // if enemy
                // Check for cooldown
                if (this->otherUnits.at(unitsSeen.at(i)).getCoolDown() > constants::autofightCooldown) {
                    continue;
                }
                // if enemy wants to fight you
                if (core_functions::linearProbability(this->otherUnits.at(unitsSeen.at(i)).getAttackProbability())) {
                    // if enemy close enough to fight
                    if (this->otherUnits.at(unitsSeen.at(i)).distanceToUnit(this->thePlayer) <
                        this->otherUnits.at(unitsSeen.at(i)).getAttackDistance()) {
                        this->currKey = this->unitsSeen.at(i);
                        enemyAttack = true;
                    }
                }
            }
        }
    }
    if (this->isPlayerFalling()) {
        std::cout << "\n";
        this->makePlayerFall(timeElapsed);
    }
    else {
        this->resolveVelocity(timeElapsed);
    }
    return enemyAttack;
}

// Spawns units in each area based on time elapsed (in s) since last call of this function
void Environment::spawnUnits(double timeElapsed) {
    for (size_t i = 0; i < this->environmentAreas.size(); i++) { // for each area
        std::vector<aiUnit> unitsInArea{};
        for (int key : this->environmentAreas.at(i).getUnitKeys()) { // get units currently in area
            if (this->otherUnits.count(key) == 0) {
                std::cout << "ERROR: unit key " << key << " not found. Update area unit keys properly.\n";
            }
            else {
                unitsInArea.push_back(this->otherUnits.at(key));
            }
        }
        std::vector<aiUnit> unitsSpawned{ this->environmentAreas.at(i).spawnUnits(timeElapsed * this->thePlayer.getMonsterSpawn(), unitsInArea) };
        for (size_t j = 0; j < unitsSpawned.size(); j++) {
            this->addUnit(unitsSpawned.at(j), i);
        }
    }
}

// Prints environment information (for debugging)
void Environment::printEnvironmentInfo() {
    std::cout << "Units in Environment:\n";
    for (std::pair<int, aiUnit> currUnit : this->otherUnits) { // print info for each unit in environment
        for (size_t j = 0; j < this->environmentAreas.size(); j++) {
            if (this->environmentAreas.at(j).unitIn(currUnit.second)) {
                std::cout << currUnit.second.getName() << " in " << this->environmentAreas.at(j).getName() << "\n";
                break;
            }
        }
    }
    std::cout << "\n";
}

// Pickup item specified by itemSeen index
void Environment::pickupItem(int index) {
    if (this->droppedItems.find(this->itemsSeen.at(index)) != this->droppedItems.end()) {
        this->thePlayer.inventoryItem(this->droppedItems.at(this->itemsSeen.at(index)));
        std::cout << "Picked up " << this->droppedItems.at(this->itemsSeen.at(index)).getName() << "\n";
        this->droppedItems.erase(this->itemsSeen.at(index));
        this->updateItemsSeen();
    }
    else {
        std::cout << "ERROR: Item index out of range.\n";
    }
}
// Consume item specified by item key
void Environment::consumeItem(int index) {
    if (this->droppedItems.find(index) != this->droppedItems.end()) {
        this->consumeItem(this->droppedItems.at(index));
        // remove item
        this->droppedItems.erase(index);
        // update items seen
        this->updateItemsSeen();
    }
    else {
        std::cout << "ERROR: Item index out of range.\n";
    }
}
// Consume item
void Environment::consumeItem(Item i) {
    int newSubtier{ this->thePlayer.consumeItem(i) };
    if (i.getXPBonus()) {
        this->startXPBonus(600);
    }
    if (i.getCreditBonus()) {
        this->startCreditBonus(600);
    }
    if (i.getFoulBonus()) {
        this->startFoulBonus(600);
    }
    // quest counter
    if (this->totalItemsConsumed.find(i.getID()) == this->totalItemsConsumed.end()) {
        this->totalItemsConsumed.emplace(i.getID(), 1);
    }
    else {
        this->totalItemsConsumed.at(i.getID())++;
    }
    std::cout << "\n";
    this->playerIntersectionBuffer += newSubtier;
}
// Use item from player inventory
void Environment::useItem(int index) {
    if ((index >= 0) && (index < this->thePlayer.getInventory().size())) {
        this->consumeItem(this->thePlayer.getInventory().at(index));
        this->thePlayer.removeItem(index, 1);
    }
    else {
        std::cout << "ERROR: index " << std::to_string(index) << " out of range when using item.\n";
    }
}
// Equip item from player inventory
void Environment::equipItem(int index) {
    this->thePlayer.equipItem(index);
}
// Dismantle item from player inventory
void Environment::dismantleItem(int index) {
    if ((index < 0) || (index >= this->thePlayer.getInventory().size())) {
        std::cout << "ERROR: Inventory index out of range.\n";
        return;
    }
    if (this->thePlayer.getInventory().at(index).getItemMaterials().size() == 0) {
        std::cout << this->thePlayer.getInventory().at(index).getName() << " cannot be dismantled.\n\n";
        return;
    }
    std::vector<int> mats{ this->thePlayer.getInventory().at(index).getItemMaterials() };
    this->thePlayer.removeItem(index, 1);
    for (int i : mats) {
        this->inventoryItem(Item(i));
    }
}
// Unequip item from player inventory
void Environment::unequipItem(std::string slot) {
    this->thePlayer.unequipItem(slot);
}
// Drops the specified item
void Environment::dropItem(int index) {
    if ((index >= 0) && (index < this->thePlayer.getInventory().size())) {
        Item droppedItem{ this->thePlayer.getInventory().at(index) };
        // place item right in front of player
        droppedItem.setXLocation(this->thePlayer.getXLocation() + this->thePlayer.getXFacing() * constants::smallDistance);
        droppedItem.setYLocation(this->thePlayer.getYLocation() + this->thePlayer.getYFacing() * constants::smallDistance);
        droppedItem.setZLocation(this->thePlayer.getZLocation() + this->thePlayer.getZFacing() * constants::smallDistance);
        this->addItem(droppedItem);
        this->thePlayer.removeItem(index);
        this->itemsSeen.clear();
        std::cout << "Dropped " << droppedItem.getName() << "\n";
        for (std::pair<const int, Item>& currItem : this->droppedItems) { // see items
            if (this->thePlayer.playerCanSee(currItem.second)) {
                this->itemsSeen.push_back(currItem.first);
            }
        }
    }
    else {
        std::cout << "ERROR: Inventory index out of range.\n";
    }
}
// Tries to inventory the item but if can't then drops it right in front of player
void Environment::inventoryItem(Item i) {
    if ((this->thePlayer.hasInventorySpace()) ||
        ((this->thePlayer.hasItem(i.getID()) != -1) && (i.isConsumable() || i.isMaterial()))) {
        this->thePlayer.inventoryItem(i);
    }
    else {
        i.setXLocation(this->thePlayer.getXLocation() + this->thePlayer.getXFacing() * constants::smallDistance);
        i.setYLocation(this->thePlayer.getYLocation() + this->thePlayer.getYFacing() * constants::smallDistance);
        i.setZLocation(this->thePlayer.getZLocation() + this->thePlayer.getZFacing() * constants::smallDistance);
        this->addItem(i);
        this->itemsSeen.clear();
        std::cout << "No room in inventory. Dropped " << i.getName() << " instead.\n";
        for (std::pair<const int, Item>& currItem : this->droppedItems) { // see items
            if (this->thePlayer.playerCanSee(currItem.second)) {
                this->itemsSeen.push_back(currItem.first);
            }
        }
    }
}

// Start reward bonuses for the player
void Environment::startXPBonus(double duration) {
    this->xpBonusLength = duration; // in s
    std::cout << "You are now receiving double xp for " << core_functions::secondsToTimeString(duration) << "\n";
}
void Environment::startCreditBonus(double duration) {
    this->creditBonusLength = duration; // in s
    std::cout << "You are now receiving double credits for " << core_functions::secondsToTimeString(duration) << "\n";
}
void Environment::startFoulBonus(double duration) {
    this->foulBonusLength = duration; // in s
    std::cout << "You are now receiving double fouls for " << core_functions::secondsToTimeString(duration) << "\n";
}
void Environment::startLuckBonus(double duration) {
    this->luckBonusLength = duration; // in s
    std::cout << "You now have double luck for " << core_functions::secondsToTimeString(duration) << "\n";
}
void Environment::startVisionBonus(double duration) {
    this->visionBonusLength = duration; // in s
    std::cout << "You now have increased vision for " << core_functions::secondsToTimeString(duration) << "\n";
}
void Environment::startSpeedBonus(double duration) {
    this->speedBonusLength = duration; // in s
    std::cout << "You now have increased speed for " << core_functions::secondsToTimeString(duration) << "\n";
}
void Environment::startSpawnBonus(double duration) {
    this->spawnBonusLength = duration; // in s
    std::cout << "More units will spawn for " << core_functions::secondsToTimeString(duration) << "\n";
}

// Forward function when completing achievement
void Environment::completedAchievement(Achievement i) {
    this->thePlayer.addAchievement(i);
}

// Add/Update quests based on key code
void Environment::addQuests(std::vector<int> questKeys) {
    for (size_t i = 0; i < questKeys.size(); i++) {
        this->environmentQuests.push_back(Quest(questKeys.at(i)));
    }
}
void Environment::updateQuests(int i) {
    std::cout << "\n--- Quests Updated ---\n\n";
    core_functions::pauseProgram(constants::shortPauseTime);
    int j{ 0 };
    bool first{};
    if (this->name.compare("DanielsAquarium") == 0) {
        switch (i) {
            case -1: // initializer
                std::cout << "There must be more to see.\n";
                this->addQuests({ 1, 2 });
                break;
            case 1:
                std::cout << "I wonder if other aquarium creatures have consciousness.\n";
                this->addQuests({ 3, 4, 8 });
                break;
            case 2:
                std::cout << "Somehow with consciousness comes much better fighting abilities.\n"
                    "I will hunt my enemies.\n";
                this->addQuests({ 5, 9 });
                // Add 10 blackworms
                for (j = 0; j < 10; j++) {
                    this->addUnit(aiUnit(12, core_functions::randomDouble(0.02, 0.98),
                        core_functions::randomDouble(0.02, 0.48), core_functions::randomDouble(0.03, 0.1)));
                }
                break;
            case 3:
                std::cout << "I must re-experience everything in this aquarium.\n";
                this->addQuests({ 7 });
                break;
            case 4:
                first = false;
                for (Quest i : this->environmentQuests) {
                    if (i.getID() == 8) {
                        first = true;
                        break;
                    }
                }
                if (first) {
                    std::cout << "Well the conscious snail only cares about selling me items.\n"
                        "I still wonder about the guppy.\n";
                }
                else {
                    std::cout << "Well if both the snail and guppy are just peddlers I'll try to "
                        "find a conscious frog.\n";
                    this->addQuests({ 10 });
                    this->addUnit(aiUnit(47, core_functions::randomDouble(0.07, 0.93),
                        core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.2, 0.25)));
                }
                break;
            case 5:
                std::cout << "My appetite is still not satiated.\n";
                this->addQuests({ 6 });
                break;
            case 6:
                std::cout << "I should leave the aquarium before I eat everything in it.\n";
                break;
            case 7:
                std::cout << "I think I've seen everything in this aquarium.\n";
                break;
            case 8:
                first = false;
                for (Quest i : this->environmentQuests) {
                    if (i.getID() == 4) {
                        first = true;
                        break;
                    }
                }
                if (first) {
                    std::cout << "Well the conscious guppy only cares about selling me items.\n"
                        "I still wonder about the snail.\n";
                }
                else {
                    std::cout << "Well if both the guppy and snail are just peddlers I'll try to "
                        "find a conscious frog.\n";
                    this->addQuests({ 10 });
                    this->addUnit(aiUnit(47, core_functions::randomDouble(0.07, 0.93),
                        core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.2, 0.25)));
                }
                break;
            case 9:
                std::cout << "Bloodworms have also messed with me over the years.\n";
                this->addQuests({ 11 });
                // Add 7 bloodworms
                for (j = 0; j < 7; j++) {
                    this->addUnit(aiUnit(22, core_functions::randomDouble(0.02, 0.98),
                        core_functions::randomDouble(0.02, 0.48), core_functions::randomDouble(0.15, 0.3)));
                }
                break;
            case 10:
                std::cout << "I guess I'm the only conscious frog here. I need to leave this aquarium.\n";
                break;
            case 11:
                std::cout << "I used to fear the worm chief.\n"
                    "He can stay at the bottom of the aquarium for months without drowning.\n";
                this->addQuests({ 12 });
                this->addUnit(aiUnit(49, core_functions::randomDouble(0.07, 0.93),
                    core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.015, 0.025)));
                break;
            case 12:
                std::cout << "The worm chief seems to have weird control of the water.\n"
                    "No wonder he doesn't drown.\n";
                core_functions::pauseProgram(constants::shortPauseTime);
                std::cout << "If I kill the rainbow shark I am king of the aquarium.\n"
                    "He dwells near the surface.\n";
                this->addQuests({ 13 });
                this->addUnit(aiUnit(48, core_functions::randomDouble(0.07, 0.93),
                    core_functions::randomDouble(0.07, 0.43), core_functions::randomDouble(0.36, 0.39)));
                break;
            case 13:
                std::cout << "Call me king of the aquarium...";
                core_functions::pauseProgram(constants::shortPauseTime);
                std::cout << "\nWell now that I've conquered all my enemies here I'm ready to leave.\n";
                break;
            default:
                break;
        }
    }
    else if (this->name.compare("Sewers") == 0) {
        switch (i) {
            case -1: // initializer
                std::cout << "I need to find my way out of this sewer.\n";
                this->addQuests({ 101 });
                break;
            case 101:
                std::cout << "I hear something large in the tunnel ahead.\n";
                core_functions::pauseProgram(constants::shortPauseTime);
                std::cout << "The current is too strong to go back; I will have to kill whatever's guarding this tunnel.\n";
                this->environmentAreas.at(17) = Area(20, 0.05, 0.55, 0.05, 1.2, 0.95, 0.08);
                this->environmentAreas.at(18) = Area(20, 0.05, 0.55, 0.08, 1.2, 0.95, 0.47);
                this->environmentAreas.at(19) = Area(20, 0.05, 0.55, 0.47, 1.2, 0.95, 0.5);
                this->environmentAreas.at(20) = Area(20, 0.05, 0.55, 0.5, 1.2, 0.95, 0.95);
                this->addQuests({ 102 });
                break;
            case 102:
                std::cout << "Well that was easier said then done.\n";
                core_functions::pauseProgram(constants::shortPauseTime);
                std::cout << "I should keep going.\n";
                this->environmentAreas.at(37) = Area(14, 1.8, 0.95, 0.05, 2, 1.45, 0.08);
                this->environmentAreas.at(38) = Area(16, 1.8, 0.95, 0.08, 2, 1.45, 0.47);
                this->environmentAreas.at(39) = Area(18, 1.8, 0.95, 0.47, 2, 1.45, 0.5);
                this->environmentAreas.at(40) = Area(19, 1.8, 0.95, 0.5, 2, 1.45, 0.95);
                this->environmentAreas.at(41) = Area(14, 1.8, 0.05, 0.05, 2, 0.55, 0.08);
                this->environmentAreas.at(42) = Area(16, 1.8, 0.05, 0.08, 2, 0.55, 0.47);
                this->environmentAreas.at(43) = Area(18, 1.8, 0.05, 0.47, 2, 0.55, 0.5);
                this->environmentAreas.at(44) = Area(19, 1.8, 0.05, 0.5, 2, 0.55, 0.95);
                this->addQuests({ 103 });
                break;
            case 103:
                std::cout << "Is that a large turtle guarding the exit to this tunnel?\n";
                this->environmentAreas.at(37) = Area(20, 1.8, 0.95, 0.05, 2, 1.45, 0.08);
                this->environmentAreas.at(38) = Area(20, 1.8, 0.95, 0.08, 2, 1.45, 0.47);
                this->environmentAreas.at(39) = Area(20, 1.8, 0.95, 0.47, 2, 1.45, 0.5);
                this->environmentAreas.at(40) = Area(20, 1.8, 0.95, 0.5, 2, 1.45, 0.95);
                this->environmentAreas.at(41) = Area(20, 1.8, 0.05, 0.05, 2, 0.55, 0.08);
                this->environmentAreas.at(42) = Area(20, 1.8, 0.05, 0.08, 2, 0.55, 0.47);
                this->environmentAreas.at(43) = Area(20, 1.8, 0.05, 0.47, 2, 0.55, 0.5);
                this->environmentAreas.at(44) = Area(20, 1.8, 0.05, 0.5, 2, 0.55, 0.95);
                this->addQuests({ 104 });
                break;
            case 104:
                std::cout << "Well now I can leave; fresh air sounds really nice.\n";
                break;
            default:
                break;
        }
    }
    else {
        std::cout << "ERROR: Environment name " << this->name << " not found.\n";
    }
    std::cout << "\n";
    core_functions::requireEnter();
    std::cout << "\n";
}

// Quest functions
int Environment::getUniqueThingsSeen() { // returns the unique things seen
    int count{};
    count += this->totalUnitsSeen.size(); // # unique units seen
    count += this->totalItemsSeen.size(); // # unique items seen
    return count;
}
int Environment::getThingsEaten() {
    int count{};
    for (std::pair<int, int> i : this->totalUnitsKilled) { // units killed (eaten when killed)
        count += i.second;
    }
    for (std::pair<int, int> i : this->totalItemsConsumed) { // items consumed
        count += i.second;
    }
    return count;
}
void Environment::checkQuestCompletion() {
    for (size_t i = 0; i < this->environmentQuests.size(); i++) {
        if (this->environmentQuests.at(i).checkCondition(this)) {
            this->playerRewards(this->environmentQuests.at(i).meetCondition());
            this->updateQuests(this->environmentQuests.at(i).getID());
            this->environmentQuests.erase(this->environmentQuests.begin() + i);
            i--;
        }
    }
}
bool Environment::hasSeenUnit(int unitCode) {
    for (std::pair<int, int> i : this->totalUnitsSeen) {
        if (i.first == unitCode) {
            return true;
        }
    }
    return false;
}
bool Environment::hasSeenItem(int itemCode) {
    for (std::pair<int, int> i : this->totalItemsSeen) {
        if (i.first == itemCode) {
            return true;
        }
    }
    return false;
}
bool Environment::hasKilledUnit(int unitCode) {
    for (std::pair<int, int> i : this->totalUnitsKilled) {
        if (i.first == unitCode) {
            return true;
        }
    }
    return false;
}
bool Environment::hasKilledUnitKey(int unitKey) {
    if (this->otherUnits.find(unitKey) == this->otherUnits.end()) {
        return true;
    }
    return false;
}
bool Environment::hasConsumedItem(int itemCode) {
    for (std::pair<int, int> i : this->totalItemsConsumed) {
        if (i.first == itemCode) {
            return true;
        }
    }
    return false;
}
void Environment::printQuests() {
    std::cout << "+++ Current Quests +++\n";
    int largestName{ 0 };
    for (Quest i : this->environmentQuests) {
        if (i.getName().size() > largestName) {
            largestName = i.getName().size();
        }
    }
    for (Quest i : this->environmentQuests) {
        i.printQuestProgress(this, largestName);
    }
}

// Toggle functions
void Environment::toggleIgnoreItems() {
    if (this->ignore_items) {
        this->ignore_items = false;
        std::cout << "You are no longer ignoring items.\n";
    }
    else {
        this->ignore_items = true;
        std::cout << "You are ignoring items now.\n";
    }
}
void Environment::toggleIgnoreUnits() {
    if (this->ignore_units) {
        this->ignore_units = false;
        std::cout << "You are no longer ignoring units.\n";
    }
    else {
        this->ignore_units = true;
        std::cout << "You are ignoring units now.\n";
    }
}
void Environment::toggleIgnoreSpatial() {
    if (this->ignore_spatial) {
        this->ignore_spatial = false;
        std::cout << "You are no longer ignoring the spatial dimension.\n";
    }
    else {
        this->ignore_spatial = true;
        std::cout << "You are ignoring the spatial dimension now.\n";
    }
}
void Environment::togglePickupDrops() {
    if (this->pickup_drops) {
        this->pickup_drops = false;
        std::cout << "You are no longer auto-picking up drops.\n";
    }
    else {
        this->pickup_drops = true;
        std::cout << "You are auto-picking up drops.\n";
    }
}

// Talk to unit -> this function checks currKey, prints message, then forwards into actual "talk"
void Environment::talkToCurrUnit() {
    if ((this->currKey < 0) || (this->currKey > this->otherUnits.size() - 1)) {
        std::cout << "ERROR: Curr key not in range.\n";
        return;
    }
    switch (this->otherUnits.at(this->currKey).getMaxHerd()) {
        // Energy = # dif items selling
        case -1: // peddler (sells at bad price)
            std::cout << "I'm not convinced this peddler will give me fair prices.\n\n";
            core_functions::requireEnter();
            this->talk_sell(constants::badPriceConstant);
            break;
        case -2: // vendor (sells at normal price)
            std::cout << "Let's see what goods this vendor has to offer.\n\n";
            core_functions::requireEnter();
            this->talk_sell(constants::normalPriceConstant);
            break;
        case -3: // huckster (sells at good price)
            std::cout << "I hear a huckster will always give good deals on items.\n\n";
            core_functions::requireEnter();
            this->talk_sell(constants::goodPriceConstant);
            break;
        // Energy = max items buying (-1 = infinite)
        case -4: // scavenger (buys at bad price)
            std::cout << "I don't trust this scavenger to offer me fair prices.\n\n";
            core_functions::requireEnter();
            this->talk_buys(constants::badPriceConstant);
            break;
        case -5: // collector (buys at normal price)
            std::cout << "Let's see what this collector offers for my items.\n\n";
            core_functions::requireEnter();
            this->talk_buys(constants::normalPriceConstant);
            break;
        case -6: // hoarder (buys at good price)
            std::cout << "A hoarder should offer good prices since they are so desperate for items.\n\n";
            core_functions::requireEnter();
            this->talk_buys(constants::goodPriceConstant);
            break;
        // Energy = # dif items selling (max items buying = 10x that)
        case -7: // broker (buys / sells at bad price)
            std::cout << "This broker will make me broke if I'm not careful.\n\n";
            core_functions::requireEnter();
            this->talk_shop(constants::badPriceConstant);
            break;
        case -8: // merchant (buys / sells at normal price)
            std::cout << "Let's see what business we can do with this merchant.\n\n";
            core_functions::requireEnter();
            this->talk_shop(constants::normalPriceConstant);
            break;
        // Energy = # dif items selling (max items buying = infinite)
        case -9: // master merchant (buys / sells at good price)
            std::cout << "A master merchant always has good deals available.\n\n";
            core_functions::requireEnter();
            this->talk_shop(constants::goodPriceConstant);
            break;
        // Energy = # upgrades/abilities/quests/pets available
        case -11: // researcher (sells upgrades for fouls)
            std::cout << "This researcher might provide valuable upgrades.\n\n";
            core_functions::requireEnter();
            this->talk_researcher();
            break;
        case -12: // trainer (sells abilities for fouls)
            std::cout << "This trainer might be able to teach me new battle abilities.\n\n";
            core_functions::requireEnter();
            this->talk_trainer();
            break;
        case -13: // solicitor (gives quests)
            std::cout << "Let's see what this soliciter wants me to do now.\n\n";
            core_functions::requireEnter();
            this->talk_soliciter();
            break;
        case -14: // handler (buys / sells pets)
            std::cout << "This handler might have valuable pets for sale.\n\n";
            core_functions::requireEnter();
            this->talk_handler();
            break;
        // Energy = max # smelters (-1 = infinite)
        case -15: // smelter
            std::cout << "This smelter can smelt my items into their materials.\n\n";
            core_functions::requireEnter();
            this->talk_smelt(constants::badPriceConstant);
            break;
        // Energy = max # upgrades/smelters (-1 = infinite)
        case -16: // plover (upgrades items to level 4)
            std::cout << "I'm not convinced this plover can make my equipment much better.\n\n";
            core_functions::requireEnter();
            this->talk_smith(constants::ploverLimit, constants::badPriceConstant);
            break;
        case -17: // smith (upgrades items to level 7)
            std::cout << "A smith might be able to make my equipment better.\n\n";
            core_functions::requireEnter();
            this->talk_smith(constants::smithLimit, constants::normalPriceConstant);
            break;
        case -18: // blacksmith (upgrades items to level 10)
            std::cout << "A blacksmith can upgrade any equipment.\n\n";
            core_functions::requireEnter();
            this->talk_smith(constants::blacksmithLimit, constants::goodPriceConstant);
            break;
        // Energy = max # reforges
        case -19: // forger (reforges items to shuffle quality with low luck)
            std::cout << "I'd be skeptical to let a forger reforge my gear.\n\n";
            core_functions::requireEnter();
            this->talk_forge(constants::lowLuck, constants::badPriceConstant);
            break;
        case -20: // expert forger (reforges items to shuffle quality with medium luck)
            std::cout << "Perhaps an expert forger can reforge my gear into better quality.\n\n";
            core_functions::requireEnter();
            this->talk_forge(constants::normalLuck, constants::normalPriceConstant);
            break;
        // Energy = max # masterforges (infinite other forges / item ugprades)
        case -21: // masterforger (reforges items with high luck and upgrades items to level 11)
            std::cout << "A real masterforge. What an honor to meet you.\n\n";
            core_functions::requireEnter();
            this->talk_masterforge();
            break;
        // Energy = max # items crafted
        case -22: // crafter (crafts items with low luck and high price)
            std::cout << "I don't believe it's the best deal to have a crafter make me items.\n\n";
            core_functions::requireEnter();
            this->talk_craft(constants::badPriceConstant, constants::lowLuck);
            break;
        case -23: // manufacturer (crafts items with medium luck and medium price)
            std::cout << "A manufacturer should be able to make pretty good items.\n\n";
            core_functions::requireEnter();
            this->talk_craft(constants::normalPriceConstant, constants::normalLuck);
            break;
        default:
            std::cout << "ERROR: Unable to talk with unit.\n";
            break;
    }
}

// Sell item to you menu (outside main while loop since don't want to get attacked/etc.)
void Environment::talk_sell(double priceFactor) {
    std::cout << "\n" << this->otherUnits.at(this->currKey).getName() << ": Let's see if anything "
        "I have is of interest to you.\n\n";
    core_functions::requireEnter();
    std::vector<Item> storeInventory{};
    for (std::pair<int, int> itemPair : this->otherUnits.at(this->currKey).getDrops()) {
        Item nextItem = Item(itemPair.first, 1.0, this->otherUnits.at(this->currKey).getXLocation(),
            this->otherUnits.at(this->currKey).getYLocation(), this->otherUnits.at(this->currKey).getZLocation(), true);
        nextItem.setStack(itemPair.second);
        storeInventory.push_back(nextItem);
    }
    while (true) {
        std::cout << "\n --- Offered Items --- (restocks in " << core_functions::secondsToTimeString(
            this->otherUnits.at(this->currKey).getAttackProbability(), 2) << ")\n";
        for (int i{ 0 }; i < storeInventory.size(); i++) {
            if ((storeInventory.size() > 9) && (i < 10)) {
                std::cout << " ";
            }
            if ((storeInventory.size() > 99) && (i < 100)) {
                std::cout << " ";
            }
            if ((storeInventory.size() > 999) && (i < 1000)) {
                std::cout << " ";
            }
            std::cout << (i + 1) << ": " << static_cast<int>(std::round(storeInventory.at(i).getItemWorth() * priceFactor)) << " credits for "
                << storeInventory.at(i).getName();
            if (storeInventory.at(i).getStack() == 0) {
                std::cout << " (out of stock)\n";
            }
            else {
                std::cout << "\n";
            }
        }
        std::string input{};
        std::cout << "\nCredits: " << this->thePlayer.getCredits() << "\n";
        input = core_functions::getInputString("\nEnter an integer to buy an item or \"leave\" to leave.\n", true);
        if (input.compare("leave") == 0) {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back anytime to "
                "buy more items.\n\n";
            std::vector<std::pair<int, int>> updatedStock{};
            for (Item i : storeInventory) {
                updatedStock.push_back({ i.getID(), i.getStack() });
            }
            this->otherUnits.at(this->currKey).setDrops(updatedStock);
            break;
        }
        else if (core_functions::isPositiveInteger(input)) {
            int inputNumber{ static_cast<int>(stoul(input) - 1) };
            if ((inputNumber >= 0) && (inputNumber < storeInventory.size())) {
                if (storeInventory.at(inputNumber).getStack() == 0) {
                    std::cout << "That item is out of stock.\n";
                    core_functions::requireEnter();
                    continue;
                }
                if (static_cast<int>(std::round(storeInventory.at(inputNumber).
                    getItemWorth() * priceFactor)) > this->thePlayer.getCredits()) {
                    std::cout << "You don't have enough credits for that item.\n";
                    core_functions::requireEnter();
                    continue;
                }
                std::cout << this->otherUnits.at(this->currKey).getName() << ": Pleasure doing "
                    "business with you.\n\nYou bought " << storeInventory.at(inputNumber).getName()
                    << " for " << static_cast<int>(std::round(storeInventory.at(inputNumber).
                    getItemWorth() * priceFactor)) << " credits.\n\n";
                this->thePlayer.removeCredits(static_cast<int>(std::round(storeInventory.at(inputNumber).getItemWorth() * priceFactor)));
                this->inventoryItem(storeInventory.at(inputNumber));
                storeInventory.at(inputNumber).removeStack();
                core_functions::requireEnter();
            }
            else {
                std::cout << this->otherUnits.at(this->currKey).getName() << ": That's not an item.\n";
            }
        }
        else {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": I don't know what that "
                "means.\n";
        }
    }
}

// Buys items from you
void Environment::talk_buys(double priceFactor) {
    if (priceFactor == 0) {
        std::cout << "ERROR: Price factor cannot be 0.\n";
        return;
    }
    if (this->thePlayer.getInventory().size() == 0) {
        std::cout << "\n" << this->otherUnits.at(this->currKey).getName() << ": Come back when you "
            "have items to sell me.\n\n";
        core_functions::requireEnter();
        return;
    }
    std::cout << "\n" << this->otherUnits.at(this->currKey).getName() << ": I'll take some of "
        "those items off your hands for you.\n\n";
    core_functions::requireEnter();
    while (true) {
        std::cout << "\n --- Offered Prices ---\n";
        std::vector<Item> playerInventory{ this->thePlayer.getInventory() };
        for (int i{ 0 }; i < playerInventory.size(); i++) {
            if ((playerInventory.size() > 9) && (i < 10)) {
                std::cout << " ";
            }
            if ((playerInventory.size() > 99) && (i < 100)) {
                std::cout << " ";
            }
            if ((playerInventory.size() > 999) && (i < 1000)) {
                std::cout << " ";
            }
            std::cout << (i + 1) << ": " << static_cast<int>(std::round(playerInventory.at(i).getItemWorth() / priceFactor)) << " credits for "
                << playerInventory.at(i).getName() << "\n";
        }
        std::string input{};
        std::cout << "\nCredits: " << this->thePlayer.getCredits() << "\n";
        input = core_functions::getInputString("\nEnter an integer to sell an item or \"leave\" to leave.\n", true);
        if (input.compare("leave") == 0) {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back anytime to "
                "sell me more items.\n\n";
            break;
        }
        else if (core_functions::isPositiveInteger(input)) {
            int inputNumber{ static_cast<int>(stoul(input) - 1) };
            if ((inputNumber >= 0) && (inputNumber < playerInventory.size())) {
                std::cout << this->otherUnits.at(this->currKey).getName() << ": Pleasure doing "
                    "business with you.\n\nYou earned " << static_cast<int>(std::round(
                        playerInventory.at(inputNumber).getItemWorth() / priceFactor)) << " credits.\n";
                this->thePlayer.addCredits(static_cast<int>(std::round(playerInventory.at(inputNumber).getItemWorth() / priceFactor)));
                this->thePlayer.removeItem(inputNumber, false);
                this->otherUnits.at(this->currKey).setEnergyValue(this->otherUnits.at(this->currKey).getEnergyValue() - 1);
                if (this->otherUnits.at(this->currKey).getEnergyValue() <= 0) {
                    this->otherUnits.at(this->currKey).setEnergyValue(constants::defaultSmithEnergy *
                        (this->otherUnits.at(this->currKey).getLevel() / constants::dimensionLevels + 1));
                    this->otherUnits.at(this->currKey).setCoolDown(constants::talkCooldown);
                    std::cout << this->otherUnits.at(this->currKey).getName() << ": I'm out of energy for now.\n\n";
                    core_functions::requireEnter();
                    return;
                }
                core_functions::requireEnter();
            }
            else {
                std::cout << this->otherUnits.at(this->currKey).getName() << ": That's not an item.\n";
            }
        }
        else {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": I don't know what that "
                "means.\n";
        }
    }
}

// Combines selling and buying
void Environment::talk_shop(double priceFactor) {
    if (priceFactor == 0) {
        std::cout << "ERROR: Price factor cannot be 0.\n";
        return;
    }
    std::cout << "\n" << this->otherUnits.at(this->currKey).getName() << ": Here I can sell you "
        "items or buy them from you.\n\n";
    core_functions::requireEnter();
    std::vector<Item> storeInventory{};
    for (std::pair<int, int> itemPair : this->otherUnits.at(this->currKey).getDrops()) {
        Item nextItem = Item(itemPair.first, 1.0, this->otherUnits.at(this->currKey).getXLocation(),
            this->otherUnits.at(this->currKey).getYLocation(), this->otherUnits.at(this->currKey).getZLocation(), true);
        nextItem.setStack(itemPair.second);
        storeInventory.push_back(nextItem);
    }
    std::vector<Item> playerInventory{ this->thePlayer.getInventory() };
    bool buying{ true };
    while (true) {
        std::string input{};
        if (buying) {
            goto BUYING;
        }
        std::cout << "\n --- Offered Prices ---\n";
        playerInventory = this->thePlayer.getInventory();
        for (int i{ 0 }; i < playerInventory.size(); i++) {
            if ((playerInventory.size() > 9) && (i < 10)) {
                std::cout << " ";
            }
            if ((playerInventory.size() > 99) && (i < 100)) {
                std::cout << " ";
            }
            if ((playerInventory.size() > 999) && (i < 1000)) {
                std::cout << " ";
            }
            std::cout << (i + 1) << ": " << static_cast<int>(std::round(playerInventory.at(i).getItemWorth() / priceFactor)) << " credits for "
                << playerInventory.at(i).getName() << "\n";
        }
        std::cout << "\nCredits: " << this->thePlayer.getCredits() << "\n";
        input = core_functions::getInputString("\nEnter an integer to sell an item, \"buy\" to buy "
            "items, or \"leave\" to leave.\n", true);
        if (input.compare("leave") == 0) {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back anytime for "
                "more great business.\n\n";
            std::vector<std::pair<int, int>> updatedStock{};
            for (Item i : storeInventory) {
                updatedStock.push_back({ i.getID(), i.getStack() });
            }
            this->otherUnits.at(this->currKey).setDrops(updatedStock);
            break;
        }
        else if (input.compare("buy") == 0) {
            buying = true;
            continue;
        }
        else if (core_functions::isPositiveInteger(input)) {
            int inputNumber{ static_cast<int>(stoul(input) - 1) };
            if ((inputNumber >= 0) && (inputNumber < playerInventory.size())) {
                std::cout << this->otherUnits.at(this->currKey).getName() << ": Pleasure doing "
                    "business with you.\n\nYou earned " << static_cast<int>(std::round(
                        playerInventory.at(inputNumber).getItemWorth() / priceFactor)) << " credits.\n";
                this->thePlayer.addCredits(static_cast<int>(std::round(playerInventory.at(inputNumber).getItemWorth() / priceFactor)));
                this->thePlayer.removeItem(inputNumber, false);
                core_functions::requireEnter();
            }
            else {
                std::cout << this->otherUnits.at(this->currKey).getName() << ": That's not an item.\n";
            }
        }
        else {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": I don't know what that "
                "means.\n";
        }
        continue;
BUYING:
        std::cout << "\n --- Offered Items --- (restocks in " << core_functions::secondsToTimeString(
            this->otherUnits.at(this->currKey).getAttackProbability(), 2) << ")\n";
        for (int i{ 0 }; i < storeInventory.size(); i++) {
            if ((storeInventory.size() > 9) && (i < 10)) {
                std::cout << " ";
            }
            if ((storeInventory.size() > 99) && (i < 100)) {
                std::cout << " ";
            }
            if ((storeInventory.size() > 999) && (i < 1000)) {
                std::cout << " ";
            }
            std::cout << (i + 1) << ": " << static_cast<int>(std::round(storeInventory.at(i).getItemWorth() * priceFactor)) << " credits for "
                << storeInventory.at(i).getName();
            if (storeInventory.at(i).getStack() == 0) {
                std::cout << " (out of stock)\n";
            }
            else {
                std::cout << "\n";
            }
        }
        std::cout << "\nCredits: " << this->thePlayer.getCredits() << "\n";
        input = core_functions::getInputString("\nEnter an integer to buy an item, \"sell\" to "
            "sell items, or \"leave\" to leave.\n", true);
        if (input.compare("leave") == 0) {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back anytime for "
                "more great business.\n\n";
            std::vector<std::pair<int, int>> updatedStock{};
            for (Item i : storeInventory) {
                updatedStock.push_back({ i.getID(), i.getStack() });
            }
            this->otherUnits.at(this->currKey).setDrops(updatedStock);
            break;
        }
        else if (input.compare("sell") == 0) {
            buying = false;
            continue;
        }
        else if (core_functions::isPositiveInteger(input)) {
            int inputNumber{ static_cast<int>(stoul(input) - 1) };
            if ((inputNumber >= 0) && (inputNumber < storeInventory.size())) {
                if (storeInventory.at(inputNumber).getStack() == 0) {
                    std::cout << "That item is out of stock.\n";
                    core_functions::requireEnter();
                    continue;
                }
                if (static_cast<int>(std::round(storeInventory.at(inputNumber).
                    getItemWorth() * priceFactor)) > this->thePlayer.getCredits()) {
                    std::cout << "You don't have enough credits for that item.\n";
                    core_functions::requireEnter();
                    continue;
                }
                std::cout << this->otherUnits.at(this->currKey).getName() << ": Pleasure doing "
                    "business with you.\n\nYou bought " << storeInventory.at(inputNumber).getName()
                    << " for " << static_cast<int>(std::round(storeInventory.at(inputNumber).
                    getItemWorth() * priceFactor)) << " credits.\n\n";
                this->thePlayer.removeCredits(static_cast<int>(std::round(storeInventory.at(inputNumber).getItemWorth() * priceFactor)));
                this->inventoryItem(storeInventory.at(inputNumber));
                storeInventory.at(inputNumber).removeStack();
                core_functions::requireEnter();
            }
            else {
                std::cout << this->otherUnits.at(this->currKey).getName() << ": That's not an item.\n";
            }
        }
        else {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": I don't know what that "
                "means.\n";
        }
    }
}

// Sells upgrades
void Environment::talk_researcher() {
    std::cout << "\n" << this->otherUnits.at(this->currKey).getName() << ": I can use those fly "
        "souls to upgrade your capabilities.\n\n";
    core_functions::requireEnter();
    std::vector<int> upgradesAvailable{};
    for (std::pair<int, int> i : this->otherUnits.at(this->currKey).getDrops()) {
        upgradesAvailable.push_back(i.first); // second in pair is nothing
    }
    while (true) {
        std::cout << "\n --- Offered Upgrades --- (restocks in " << core_functions::secondsToTimeString(
            this->otherUnits.at(this->currKey).getAttackProbability(), 2) << ")\n";
        for (int i{ 0 }; i < upgradesAvailable.size(); i++) {
            if ((upgradesAvailable.size() > 9) && (i < 10)) {
                std::cout << " ";
            }
            if ((upgradesAvailable.size() > 99) && (i < 100)) {
                std::cout << " ";
            }
            std::cout << (i + 1) << ": " << this->thePlayer.getUpgradeName(upgradesAvailable.at(i));
            if (this->thePlayer.hasActivatedUpgrade(upgradesAvailable.at(i))) {
                std::cout << " (already upgraded)\n";
            }
            else {
                std::cout << " (" << std::to_string(this->thePlayer.getUpgradeCost(upgradesAvailable.at(i))) << " fouls)\n";
            }
        }
        std::string input{};
        std::cout << "\nFouls: " << this->thePlayer.getFouls() << "\n";
        input = core_functions::getInputString("\nEnter an integer to purchase an upgrade or "
            "\"leave\" to leave.\n", true);
        if (input.compare("leave") == 0) {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back anytime to "
                "purchase more upgrades.\n\n";
            break;
        }
        else if (core_functions::isPositiveInteger(input)) {
            int inputNumber{ static_cast<int>(stoul(input) - 1) };
            if ((inputNumber >= 0) && (inputNumber < upgradesAvailable.size())) {
                if (this->thePlayer.hasActivatedUpgrade(upgradesAvailable.at(inputNumber))) {
                    std::cout << "You already have that upgrade.\n";
                    core_functions::requireEnter();
                    continue;
                }
                if (this->thePlayer.getUpgradeCost(upgradesAvailable.at(inputNumber)) >
                    this->thePlayer.getFouls()) {
                    std::cout << "You don't have enough fouls for that item.\n";
                    core_functions::requireEnter();
                    continue;
                }
                std::cout << this->otherUnits.at(this->currKey).getName() << ": Pleasure doing "
                    "business with you.\n\nYou upgraded " << this->thePlayer.getUpgradeName(
                    upgradesAvailable.at(inputNumber)) << " for " << this->thePlayer.getUpgradeCost(
                    upgradesAvailable.at(inputNumber)) << " fouls.\n\n";
                this->thePlayer.removeFouls(this->thePlayer.getUpgradeCost(upgradesAvailable.at(inputNumber)));
                this->thePlayer.activateUpgrade(upgradesAvailable.at(inputNumber));
                core_functions::requireEnter();
            }
            else {
                std::cout << this->otherUnits.at(this->currKey).getName() << ": That's not an upgrade.\n";
            }
        }
        else {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": I don't know what that "
                "means.\n";
        }
    }
}

// Sells battle abilities
void Environment::talk_trainer() {
    std::cout << "\n" << this->otherUnits.at(this->currKey).getName() << ": I can use those fly "
        "souls to teach you more battle abilities.\n\n";
    core_functions::requireEnter();
    std::vector<Ability> abilitiesAvailable{};
    for (Ability i : this->otherUnits.at(this->currKey).getBattleAbilities()) {
        abilitiesAvailable.push_back(i);
    }
    while (true) {
        std::cout << "\n --- Offered Abilties --- (restocks in " << core_functions::secondsToTimeString(
            this->otherUnits.at(this->currKey).getAttackProbability(), 2) << ")\n";
        for (int i{ 0 }; i < abilitiesAvailable.size(); i++) {
            if ((abilitiesAvailable.size() > 9) && (i < 10)) {
                std::cout << " ";
            }
            if ((abilitiesAvailable.size() > 99) && (i < 100)) {
                std::cout << " ";
            }
            std::cout << (i + 1) << ": " << abilitiesAvailable.at(i).getName();
            if (this->thePlayer.hasLearnedAbility(abilitiesAvailable.at(i).getName())) {
                std::cout << " (already learned)\n";
            }
            else {
                std::cout << " (" << std::to_string(abilitiesAvailable.at(i).getFoulCost()) << " fouls)\n";
            }
        }
        std::string input{};
        std::cout << "\nFouls: " << this->thePlayer.getFouls() << "\n";
        input = core_functions::getInputString("\nEnter an integer to learn an ability or "
            "\"leave\" to leave.\n", true);
        if (input.compare("leave") == 0) {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back anytime to "
                "learn more abilities.\n\n";
            break;
        }
        else if (core_functions::isPositiveInteger(input)) {
            int inputNumber{ static_cast<int>(stoul(input) - 1) };
            if ((inputNumber >= 0) && (inputNumber < abilitiesAvailable.size())) {
                if (this->thePlayer.hasLearnedAbility(abilitiesAvailable.at(inputNumber).getName())) {
                    std::cout << "You already have that ability.\n";
                    core_functions::requireEnter();
                    continue;
                }
                if (abilitiesAvailable.at(inputNumber).getFoulCost() > this->thePlayer.getFouls()) {
                    std::cout << "You don't have enough fouls for that item.\n";
                    core_functions::requireEnter();
                    continue;
                }
                std::cout << this->otherUnits.at(this->currKey).getName() << ": Pleasure doing "
                    "business with you.\n\nYou learned " << abilitiesAvailable.at(inputNumber).getName()
                    << " for " << abilitiesAvailable.at(inputNumber).getFoulCost() << " fouls.\n\n";
                this->thePlayer.removeFouls(abilitiesAvailable.at(inputNumber).getFoulCost());
                this->thePlayer.addBattleAbility(abilitiesAvailable.at(inputNumber));
                core_functions::requireEnter();
            }
            else {
                std::cout << this->otherUnits.at(this->currKey).getName() << ": That's not an ability.\n";
            }
        }
        else {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": I don't know what that "
                "means.\n";
        }
    }
}

// Provides quests
void Environment::talk_soliciter() {
    //
}

// Sells pets
void Environment::talk_handler() {
    //
}

// Smelt items
void Environment::talk_smelt(double priceFactor) {
    if (priceFactor == 0) {
        std::cout << "ERROR: Price factor cannot be 0.\n";
        return;
    }
    std::vector<int> smeltableItems{};
    for (int i{ 0 }; i < this->thePlayer.getInventory().size(); i++) {
        if (this->thePlayer.getInventory().at(i).getItemMaterials().size() == 0) {
            continue; // not smeltable
        }
        smeltableItems.push_back(i); // to map the display index to actual index
    }
    if (smeltableItems.size() == 0) {
        std::cout << "\n" << this->otherUnits.at(this->currKey).getName() << ": You have no items to "
            "smelt.\n\n";
        return;
    }
    std::cout << "\n" << this->otherUnits.at(this->currKey).getName() << ": Here I can smelt your "
        "equipment down to its materials.\n\n";
    core_functions::requireEnter();
    while (true) {
        std::string input{};
        std::cout << "\n --- Smeltable Items ---\n";
        for (int i{ 0 }; i < smeltableItems.size(); i++) {
            if ((smeltableItems.size() > 9) && (i < 10)) {
                std::cout << " ";
            }
            if ((smeltableItems.size() > 99) && (i < 100)) {
                std::cout << " ";
            }
            if ((smeltableItems.size() > 999) && (i < 1000)) {
                std::cout << " ";
            }
            std::cout << (i + 1) << ": " << this->thePlayer.getInventory().at(smeltableItems.at(i)).getName() << "\n";
        }
        input = core_functions::getInputString("\nEnter an integer to view smelting details on an "
            "item or \"leave\" to leave.\n", false);
        if (input.compare("leave") == 0) {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back anytime to "
                "smelt more items.\n\n";
            return;
        }
        else if (core_functions::isPositiveInteger(input)) {
            int inputNumber{ static_cast<int>(stoul(input) - 1) };
            if ((inputNumber >= 0) && (inputNumber < smeltableItems.size())) {
                while (true) {
                    int creditRefund{ static_cast<int>(std::round(this->thePlayer.getInventory().at(smeltableItems.at(inputNumber)).
                        getItemWorth() * this->thePlayer.getInventory().at(smeltableItems.at(inputNumber)).
                        getDimension() * constants::smeltConstant / priceFactor)) };
                    std::cout << "Smelt " << this->thePlayer.getInventory().at(smeltableItems.at(
                        inputNumber)).getName() << " for:\nCredits: " << creditRefund << "\n";
                    for (int mat : this->thePlayer.getInventory().at(smeltableItems.at(inputNumber)).getItemMaterials()) {
                        std::cout << Item(mat).getName() << "\n";
                    }
                    input = core_functions::getInputString("\nEnter \"smelt\" to smelt your item "
                        "or \"back\" to go back\n", false);
                    if (input.compare("leave") == 0) {
                        std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back "
                            "anytime to smelt more items.\n\n";
                        return;
                    }
                    else if (input.compare("smelt") == 0) {
                        this->thePlayer.addCredits(creditRefund);
                        for (int mat : this->thePlayer.getInventory().at(smeltableItems.at(inputNumber)).getItemMaterials()) {
                            this->inventoryItem(Item(mat));
                        }
                        this->thePlayer.removeItem(smeltableItems.at(inputNumber), 1);
                        this->otherUnits.at(this->currKey).setEnergyValue(this->otherUnits.at(this->currKey).getEnergyValue() - 1);
                        if (this->otherUnits.at(this->currKey).getEnergyValue() <= 0) {
                            this->otherUnits.at(this->currKey).setEnergyValue(constants::defaultSmithEnergy *
                                (this->otherUnits.at(this->currKey).getLevel() / constants::dimensionLevels + 1));
                            this->otherUnits.at(this->currKey).setCoolDown(constants::talkCooldown);
                            std::cout << this->otherUnits.at(this->currKey).getName() << ": I'm out of energy for now.\n\n";
                            core_functions::requireEnter();
                            return;
                        }
                        std::cout << this->otherUnits.at(this->currKey).getName() << ": Pleasure "
                            "doing business with you.\n\n";
                        break;
                    }
                    else if (input.compare("back") == 0) {
                        break;
                    }
                }
            }
            else {
                std::cout << this->otherUnits.at(this->currKey).getName() << ": That's not an item.\n";
            }
        }
        else {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": I don't know what that "
                "means.\n";
        }
    }
}

// Upgrades/smelts items
void Environment::talk_smith(int itemLevelLimit, double priceFactor) {
    if (priceFactor == 0) {
        std::cout << "ERROR: Price factor cannot be 0.\n";
        return;
    }
    std::cout << "\n" << this->otherUnits.at(this->currKey).getName() << ": Here I can upgrade "
        "your equipment or smelt it down to materials.\n\n";
    core_functions::requireEnter();
    std::vector<int> upgradableItems{};
    for (int i{ 0 }; i < this->thePlayer.getInventory().size(); i++) {
        if (this->thePlayer.getInventory().at(i).getItemMaterials().size() == 0) {
            continue; // not upgradable
        }
        if (itemLevelLimit > this->thePlayer.getInventory().at(i).getLevel()) {
            upgradableItems.push_back(i); // to map the display index to actual index
        }
    }
    std::vector<int> smeltableItems{};
    for (int i{ 0 }; i < this->thePlayer.getInventory().size(); i++) {
        if (this->thePlayer.getInventory().at(i).getItemMaterials().size() == 0) {
            continue; // not smeltable
        }
        smeltableItems.push_back(i); // to map the display index to actual index
    }
    bool smelting{ false };
    std::string input{};
    while (true) {
        if (smelting) {
            goto SMELTING;
        }
        std::cout << "\n --- Upgradable Items ---\n";
        for (int i{ 0 }; i < upgradableItems.size(); i++) {
            if ((upgradableItems.size() > 9) && (i < 10)) {
                std::cout << " ";
            }
            if ((upgradableItems.size() > 99) && (i < 100)) {
                std::cout << " ";
            }
            if ((upgradableItems.size() > 999) && (i < 1000)) {
                std::cout << " ";
            }
            std::cout << (i + 1) << ": " << this->thePlayer.getInventory().at(upgradableItems.at(i)).getName() << "\n";
        }
        input = core_functions::getInputString("\nEnter an integer to view upgrade details on an "
            "item, \"smelt\" to smelt items, or \"leave\" to leave.\n", false);
        if (input.compare("leave") == 0) {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back anytime to "
                "smelt more items.\n\n";
            return;
        }
        else if (input.compare("smelt") == 0) {
            smelting = true;
            continue;
        }
        else if (core_functions::isPositiveInteger(input)) {
            int inputNumber{ static_cast<int>(stoul(input) - 1) };
            if ((inputNumber >= 0) && (inputNumber < upgradableItems.size())) {
                while (true) {
                    int creditCost{ static_cast<int>(std::round(this->thePlayer.getInventory().at(
                        upgradableItems.at(inputNumber)).getItemWorth() * this->thePlayer.
                        getInventory().at(upgradableItems.at(inputNumber)). getDimension() *
                        constants::upgradeConstant * priceFactor)) };
                    std::cout << "Upgrade " << this->thePlayer.getInventory().at(upgradableItems.at(
                        inputNumber)).getName() << " for:\nCredits: " << creditCost << "\n";
                    int matCost{ this->thePlayer.getInventory().at(upgradableItems.at(inputNumber)).
                        getMatUpgradeCost(priceFactor) };
                    for (int mat : this->thePlayer.getInventory().at(upgradableItems.at(inputNumber)).getItemMaterials()) {
                        std::cout << Item(mat).getName() << ": " << matCost << "\n";
                    }
                    input = core_functions::getInputString("\nEnter \"upgrade\" to upgrade your item "
                        "or \"back\" to go back\n", false);
                    if (input.compare("leave") == 0) {
                        std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back "
                            "anytime to upgrade more items.\n\n";
                        return;
                    }
                    else if (input.compare("upgrade") == 0) {
                        bool cantUpgrade{ false };
                        if (this->thePlayer.getCredits() < creditCost) {
                            std::cout << "You don't have enough credits.\n";
                            cantUpgrade = true;
                        }
                        for (int mat : this->thePlayer.getInventory().at(upgradableItems.at(inputNumber)).getItemMaterials()) {
                            if (this->thePlayer.hasItem(mat) == -1) {
                                std::cout << "You don't have enough " << Item(mat).getName() << ".\n";
                                cantUpgrade = true;
                            }
                            else if (this->thePlayer.getInventory().at(this->thePlayer.hasItem(
                                mat)).getStack() < matCost) {
                                std::cout << "You don't have enough " << Item(mat).getName() << ".\n";
                                cantUpgrade = true;
                            }
                        }
                        if (cantUpgrade) {
                            continue;
                        }
                        this->thePlayer.upgradeItem(upgradableItems.at(inputNumber));
                        this->thePlayer.removeCredits(creditCost);
                        for (int mat : this->thePlayer.getInventory().at(upgradableItems.at(inputNumber)).getItemMaterials()) {
                            this->thePlayer.removeItem(this->thePlayer.hasItem(mat), matCost);
                        }
                        this->otherUnits.at(this->currKey).setEnergyValue(this->otherUnits.at(this->currKey).getEnergyValue() - 1);
                        if (this->otherUnits.at(this->currKey).getEnergyValue() <= 0) {
                            this->otherUnits.at(this->currKey).setEnergyValue(constants::defaultSmithEnergy *
                                (this->otherUnits.at(this->currKey).getLevel() / constants::dimensionLevels + 1));
                            this->otherUnits.at(this->currKey).setCoolDown(constants::talkCooldown);
                            std::cout << this->otherUnits.at(this->currKey).getName() << ": I'm out of energy for now.\n\n";
                            core_functions::requireEnter();
                            return;
                        }
                        std::cout << this->otherUnits.at(this->currKey).getName() << ": Pleasure "
                            "doing business with you.\n\n";
                        break;
                    }
                    else if (input.compare("back") == 0) {
                        break;
                    }
                }
            }
            else {
                std::cout << this->otherUnits.at(this->currKey).getName() << ": That's not an item.\n";
            }
        }
        else {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": I don't know what that "
                "means.\n";
        }
        continue;
SMELTING:
        std::cout << "\n --- Smeltable Items ---\n";
        for (int i{ 0 }; i < smeltableItems.size(); i++) {
            if ((smeltableItems.size() > 9) && (i < 10)) {
                std::cout << " ";
            }
            if ((smeltableItems.size() > 99) && (i < 100)) {
                std::cout << " ";
            }
            if ((smeltableItems.size() > 999) && (i < 1000)) {
                std::cout << " ";
            }
            std::cout << (i + 1) << ": " << this->thePlayer.getInventory().at(smeltableItems.at(i)).getName() << "\n";
        }
        input = core_functions::getInputString("\nEnter an integer to view smelting details on an "
            "item, \"upgrade\" to upgrade, or \"leave\" to leave.\n", false);
        if (input.compare("leave") == 0) {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back anytime to "
                "smelt more items.\n\n";
            return;
        }
        else if (input.compare("upgrade") == 0) {
            smelting = false;
            continue;
        }
        else if (core_functions::isPositiveInteger(input)) {
            int inputNumber{ static_cast<int>(stoul(input) - 1) };
            if ((inputNumber >= 0) && (inputNumber < smeltableItems.size())) {
                while (true) {
                    int creditRefund{ static_cast<int>(std::round(this->thePlayer.getInventory().at(smeltableItems.at(inputNumber)).
                        getItemWorth() * this->thePlayer.getInventory().at(smeltableItems.at(inputNumber)).
                        getDimension() * constants::smeltConstant / priceFactor)) };
                    std::cout << "Smelt " << this->thePlayer.getInventory().at(smeltableItems.at(
                        inputNumber)).getName() << " for:\nCredits: " << creditRefund << "\n";
                    for (int mat : this->thePlayer.getInventory().at(smeltableItems.at(inputNumber)).getItemMaterials()) {
                        std::cout << Item(mat).getName() << "\n";
                    }
                    input = core_functions::getInputString("\nEnter \"smelt\" to smelt your item "
                        "or \"back\" to go back\n", false);
                    if (input.compare("leave") == 0) {
                        std::cout << this->otherUnits.at(this->currKey).getName() << ": Come back "
                            "anytime to smelt more items.\n\n";
                        return;
                    }
                    else if (input.compare("smelt") == 0) {
                        this->thePlayer.addCredits(creditRefund);
                        for (int mat : this->thePlayer.getInventory().at(smeltableItems.at(inputNumber)).getItemMaterials()) {
                            this->inventoryItem(Item(mat));
                        }
                        this->otherUnits.at(this->currKey).setEnergyValue(this->otherUnits.at(this->currKey).getEnergyValue() - 1);
                        if (this->otherUnits.at(this->currKey).getEnergyValue() <= 0) {
                            this->otherUnits.at(this->currKey).setEnergyValue(constants::defaultSmithEnergy *
                                (this->otherUnits.at(this->currKey).getLevel() / constants::dimensionLevels + 1));
                            this->otherUnits.at(this->currKey).setCoolDown(constants::talkCooldown);
                            std::cout << this->otherUnits.at(this->currKey).getName() << ": I'm out of energy for now.\n\n";
                            core_functions::requireEnter();
                            return;
                        }
                        std::cout << this->otherUnits.at(this->currKey).getName() << ": Pleasure "
                            "doing business with you.\n\n";
                        break;
                    }
                    else if (input.compare("back") == 0) {
                        break;
                    }
                }
            }
            else {
                std::cout << this->otherUnits.at(this->currKey).getName() << ": That's not an item.\n";
            }
        }
        else {
            std::cout << this->otherUnits.at(this->currKey).getName() << ": I don't know what that "
                "means.\n";
        }
    }
}

// Reforges/smelts items (to shuffle item quality)
void Environment::talk_forge(double luckFactor, double priceFactor) {
    //
}

// Combine smith and forge
void Environment::talk_masterforge() {
    //
}

// Crafts/smelts items
void Environment::talk_craft(double priceFactor, double luckFactor) {
    //
}

// Prints player status
void Environment::printStatus() {
    this->thePlayer.printPlayerInfo();
    if (xpBonusLength > 0) {
        std::cout << "  -- XP Bonus Active: " << core_functions::secondsToTimeString(xpBonusLength) << "\n";
    }
    if (creditBonusLength > 0) {
        std::cout << "  -- Credit Bonus Active: " << core_functions::secondsToTimeString(creditBonusLength) << "\n";
    }
    if (foulBonusLength > 0) {
        std::cout << "  -- Foul Bonus Active: " << core_functions::secondsToTimeString(foulBonusLength) << "\n";
    }
    if (luckBonusLength > 0) {
        std::cout << "  -- Luck Bonus Active: " << core_functions::secondsToTimeString(luckBonusLength) << "\n";
    }
    if (visionBonusLength > 0) {
        std::cout << "  -- Vision Bonus Active: " << core_functions::secondsToTimeString(visionBonusLength) << "\n";
    }
    if (speedBonusLength > 0) {
        std::cout << "  -- Speed Bonus Active: " << core_functions::secondsToTimeString(speedBonusLength) << "\n";
    }
    if (spawnBonusLength > 0) {
        std::cout << "  -- Spawn Bonus Active: " << core_functions::secondsToTimeString(spawnBonusLength) << "\n";
    }
}

// Returns the file string for the environment savegame file
void Environment::saveGame(std::string filePath) {
    std::ofstream environmentFile{ filePath, std::ios::trunc };
    environmentFile << "*STARTFILE\n";
    environmentFile << "*STRING=name\n" + this->name + "\n*END\n";
    environmentFile << this->thePlayer.saveGame();
    environmentFile << "playerIntersectionBuffer=" << this->playerIntersectionBuffer << "\n";
    environmentFile << "*MAP=otherUnits\n";
    for (std::pair<int, aiUnit> i : this->otherUnits) {
        environmentFile << "*KEY=" << i.first << "\n";
        environmentFile << i.second.saveGame();
    }
    environmentFile << "*END\n";
    environmentFile << "unitKey=" << this->unitKey << "\n";
    environmentFile << "currKey=" << this->currKey << "\n";
    environmentFile << "*MAP=droppedItems\n";
    for (std::pair<int, Item> i : this->droppedItems) {
        environmentFile << "*KEY=" << i.first << "\n";
        environmentFile << "*DEFINE=Item\n" << i.second.saveGame() << "*END\n";
    }
    environmentFile << "*END\n";
    environmentFile << "itemKey=" << this->itemKey << "\n";
    environmentFile << "*VECTOR=environmentAreas\n";
    for (Area i : this->environmentAreas) {
        environmentFile << i.saveGame();
    }
    environmentFile << "*END\n";
    environmentFile << "currArea=" << this->currArea << "\n";
    environmentFile << "xLimit=" << this->xLimit << "\n";
    environmentFile << "yLimit=" << this->yLimit << "\n";
    environmentFile << "zLimit=" << this->zLimit << "\n";
    environmentFile << "*VECTOR=unitsSeen\n";
    for (int i : this->unitsSeen) {
        environmentFile << i << "\n";
    }
    environmentFile << "*END\n";
    environmentFile << "*VECTOR=itemsSeen\n";
    for (int i : this->itemsSeen) {
        environmentFile << i << "\n";
    }
    environmentFile << "*END\n";
    environmentFile << "intersectionPoint0=" << this->intersectionPoint[0] << "\n";
    environmentFile << "intersectionPoint1=" << this->intersectionPoint[1] << "\n";
    environmentFile << "intersectionPoint2=" << this->intersectionPoint[2] << "\n";
    environmentFile << "intersectionPoint3=" << this->intersectionPoint[3] << "\n";
    environmentFile << "intersectionPoint4=" << this->intersectionPoint[4] << "\n";
    environmentFile << "xpBonusLength=" << this->xpBonusLength << "\n";
    environmentFile << "creditBonusLength=" << this->creditBonusLength << "\n";
    environmentFile << "foulBonusLength=" << this->foulBonusLength << "\n";
    environmentFile << "luckBonusLength=" << this->luckBonusLength << "\n";
    environmentFile << "visionBonusLength=" << this->visionBonusLength << "\n";
    environmentFile << "speedBonusLength=" << this->speedBonusLength << "\n";
    environmentFile << "spawnBonusLength=" << this->spawnBonusLength << "\n";
    environmentFile << "*VECTOR=environmentQuests\n";
    for (Quest i : this->environmentQuests) {
        environmentFile << i.saveGame();
    }
    environmentFile << "*END\n";
    environmentFile << "*MAP=totalUnitsSeen\n";
    for (std::pair<int, int> i : this->totalUnitsSeen) {
        environmentFile << "*KEY=" << i.first << "=" << i.second << "\n";
    }
    environmentFile << "*END\n";
    environmentFile << "*MAP=totalItemsSeen\n";
    for (std::pair<int, int> i : this->totalItemsSeen) {
        environmentFile << "*KEY=" << i.first << "=" << i.second << "\n";
    }
    environmentFile << "*END\n";
    environmentFile << "*MAP=totalUnitsKilled\n";
    for (std::pair<int, int> i : this->totalUnitsKilled) {
        environmentFile << "*KEY=" << i.first << "=" << i.second << "\n";
    }
    environmentFile << "*END\n";
    environmentFile << "*MAP=totalItemsConsumed\n";
    for (std::pair<int, int> i : this->totalItemsConsumed) {
        environmentFile << "*KEY=" << i.first << "=" << i.second << "\n";
    }
    environmentFile << "*END\n";
    environmentFile << "ignore_items=" << core_functions::boolToString(this->ignore_items) << "\n";
    environmentFile << "ignore_units=" << core_functions::boolToString(this->ignore_units) << "\n";
    environmentFile << "ignore_spatial=" << core_functions::boolToString(this->ignore_spatial) << "\n";
    environmentFile << "pickup_drops=" << core_functions::boolToString(this->pickup_drops) << "\n";
    environmentFile.close();
}


// Area Class
Area::Area(int areaType, double x1, double y1, double z1, double x2, double y2, double z2,
    int maxSpace) : Area(areaType, x1, y1, z1, x2, y2, z2) {
    this->maxSpace = maxSpace;
}
Area::Area(int areaType, double x1, double y1, double z1, double x2, double y2, double z2) {
    this->areaType = areaType;
    this->x1 = x1;
    this->y1 = y1;
    this->z1 = z1;
    this->x2 = x2;
    this->y2 = y2;
    this->z2 = z2;
    if (x1 > x2) {
        std::cout << "ERROR: Area x2 coordinate not larger than x1. Will flip coordinates.\n";
        this->x1 = x2;
        this->x2 = x1;
    }
    if (y1 > y2) {
        std::cout << "ERROR: Area y2 coordinate not larger than y1. Will flip coordinates.\n";
        this->y1 = y2;
        this->y2 = y1;
    }
    if (z1 > z2) {
        std::cout << "ERROR: Area z2 coordinate not larger than z1. Will flip coordinates.\n";
        this->z1 = z2;
        this->z2 = z1;
    }
}

double Area::getPoint(int component) {
    switch (component) {
        case 0:
            return this->x1;
            break;
        case 1:
            return this->y1;
            break;
        case 2:
            return this->z1;
            break;
        case 3:
            return this->x2;
            break;
        case 4:
            return this->y2;
            break;
        case 5:
            return this->z2;
            break;
        default:
            std::cout << "ERROR: Area " << this->getName() << " point component " << component << " not found.\n";
            return -1;
            break;
    }
}

// Area reference
std::string Area::getName() {
    std::string areaName{};
    switch (this->areaType) {
        // Dimension I
        case 1:
            areaName = "aquarium glass";
            break;
        case 2:
            areaName = "aquarium rock";
            break;
        case 3:
            areaName = "aquarium water";
            break;
        case 4:
            areaName = "aquarium water";
            break;
        case 5:
            areaName = "aquarium water";
            break;
        case 6:
            areaName = "aquarium water surface";
            break;
        case 7:
            areaName = "aquarium air";
            break;
        case 8:
            areaName = "aquarium lid";
            break;

        // Dimension II
        case 11:
            areaName = "sewer stone";
            break;
        case 12:
            areaName = "stone surface";
            break;
        case 13:
            areaName = "sewer bottom";
            break;
        case 14:
            areaName = "sewer bottom";
            break;
        case 15:
            areaName = "sewer water";
            break;
        case 16:
            areaName = "sewer water";
            break;
        case 17:
            areaName = "water surface";
            break;
        case 18:
            areaName = "water surface";
            break;
        case 19:
            areaName = "sewer air";
            break;
        case 20:
            areaName = "strong current";
            break;

        // Dimension III
        case 21: // toxic mud
            areaName = "toxic mud";
            break;
        case 22: // sewer runoff
            areaName = "sewer runoff";
            break;
        case 23: // sewer runoff surface
            areaName = "water surface";
            break;
        case 24: // sewer runoff air
            areaName = "air";
            break;
        case 25: // pebbles
            areaName = "pebbles";
            break;
        case 26: // spring water
            areaName = "stream";
            break;
        case 27: // spring water surface
            areaName = "water surface";
            break;
        case 28: // spring water air
            areaName = "air";
            break;
        case 29: // muddy bottom
            areaName = "mud";
            break;
        case 30: // deep lake water
            areaName = "deep water";
            break;
        case 31: // shallow lake water
            areaName = "shallow water";
            break;
        case 32: // lake water surface
            areaName = "water surface";
            break;
        case 33: // lake water air
            areaName = "air";
            break;
        case 34: // grass (movable - field)
            areaName = "grass";
            break;
        case 35: // surface (rock)
            areaName = "rock";
            break;
        case 36: // underbrush (movable - trees)
            areaName = "underbrush";
            break;
        case 37: // ground (immovable for all)
            areaName = "ground";
            break;
        case 38: // forest air
            areaName = "air";
            break;
        case 39: // tree1 (forest)
            areaName = "tree";
            break;
        case 40: // tree2 (light forest)
            areaName = "tree";
            break;
        case 41: // tree3 (dark forest)
            areaName = "tree";
            break;
        case 42: // sewers
            areaName = "sewers";
            break;
        case 43: // cliff
            areaName = "cliff face";
            break;
        case 44: // deep lake mud
            areaName = "mud";
            break;
        case 45: // field air
            areaName = "air";
            break;
        case 46: // mountain air (rock)
            areaName = "air";
            break;
        case 47: // field grass 2
            areaName = "grass";
            break;
        case 48: // field air 2
            areaName = "air";
            break;
        case 49: // mountain air 2 (mountain)
            areaName = "air";
            break;
        case 50: // mountain air 3 (snow)
            areaName = "air";
            break;
        case 51: // mountain surface 2 (mountain)
            areaName = "mountain";
            break;
        case 52: // mountain surface 3 (snow)
            areaName = "snow";
            break;

        default:
            std::cout << "ERROR: Area name not found in area reference.\n";
            break;
    }
    return areaName;
}

// Returns whether the inputted unit / item is in the area
bool Area::unitIn(Unit unit) {
    double point[3] = { unit.getXLocation(), unit.getYLocation(), unit.getZLocation() };
    return this->pointIn(point);
}
bool Area::itemIn(Item item) {
    double point[3] = { item.getXLocation(), item.getYLocation(), item.getZLocation() };
    return this->pointIn(point);
}
// Returns whether the inputted point is in the area
bool Area::pointIn(double point[3]) {
    bool isIn = false;
    if ((point[0] > this->x1) && (point[0] < this->x2) &&
        (point[1] > this->y1) && (point[1] < this->y2) &&
        (point[2] > this->z1) && (point[2] < this->z2)) {
        isIn = true;
    }
    return isIn;
}

// Returns vector of units spawned in area
std::vector<aiUnit> Area::spawnUnits(double timeElapsed, std::vector<aiUnit> currUnits) {
    std::vector<aiUnit> unitsSpawned{};
    std::vector<aiUnit> possibleSpawns{ this->getPossibleUnits() }; // units allowed to spawn here
    for (size_t i = 0; i < currUnits.size(); i++) { // subtract out units already there
        for (size_t j = 0; j < possibleSpawns.size(); j++) {
            if (currUnits.at(i).getUnitID() == possibleSpawns.at(j).getUnitID()) {
                if (possibleSpawns.at(j).getMaxHerd() > 1) {
                    possibleSpawns.at(j).setMaxHerd(possibleSpawns.at(j).getMaxHerd() - 1);
                } else {
                    possibleSpawns.erase(possibleSpawns.begin() + j);
                }
                break;
            }
        }
    }
    int areaSpace{ this->getMaxSpace() };
    int areaTaken{ 0 };
    for (size_t i = 0; i < currUnits.size(); i++) { // calculate space taken
        areaTaken += currUnits.at(i).getSpaceTaken();
    }
    while ((areaTaken < areaSpace) && (possibleSpawns.size() > 0)) {
        for (size_t i = 0; i < possibleSpawns.size(); i++) { // try spawning 1 unit at a time for each type
            if (core_functions::checkSpawn(possibleSpawns.at(i).getSpawnProbability(), timeElapsed)) {
                unitsSpawned.push_back(possibleSpawns.at(i)); // add to units spawned
                // NOTE: the unit will be spawned even if there's not enough space (just no more will spawn)
                areaTaken += possibleSpawns.at(i).getSpaceTaken();
                if (areaTaken >= areaSpace) {
                    break;
                }
            }
            else { // spawn failed
            }
            if (possibleSpawns.at(i).getMaxHerd() > 1) {
                possibleSpawns.at(i).setMaxHerd(possibleSpawns.at(i).getMaxHerd() - 1);
            } else {
                possibleSpawns.erase(possibleSpawns.begin() + i);
                i -= 1;
            }
        }
    }
    this->randomizePositions(unitsSpawned);
    return unitsSpawned;
}

// Given a set of units in the area randomize their positions in the area
void Area::randomizePositions(std::vector<aiUnit> &units) {
    for (size_t i = 0; i < units.size(); i++) {
        units.at(i).setLocation(core_functions::randomDouble(this->x1, this->x2),
            core_functions::randomDouble(this->y1, this->y2),
            core_functions::randomDouble(this->z1, this->z2));
    }
}

// Returns vector of units possible to spawn in this area
std::vector<aiUnit> Area::getPossibleUnits() {
    std::vector<aiUnit> possibleUnits{};
    switch (this->areaType) {
        // Dimension I
        case 1: // aquarium glass
            core_functions::addUnits(possibleUnits, std::vector<int>{});
            break;
        case 2: // aquarium rock
            core_functions::addUnits(possibleUnits, std::vector<int>{7, 13, 20, 21, 31, 41});
            break;
        case 3: // aquarium water bottom
            core_functions::addUnits(possibleUnits, std::vector<int>{1, 2, 3, 4, 11, 12, 16});
            break;
        case 4: // aquarium water middle
            core_functions::addUnits(possibleUnits, std::vector<int>{5, 14, 17, 18, 19, 22, 23, 24, 26, 27, 32, 46});
            break;
        case 5: // aquarium water top
            core_functions::addUnits(possibleUnits, std::vector<int>{6, 15, 25, 28, 33, 35, 36, 37, 42, 46});
            break;
        case 6: // aquarium water surface
            core_functions::addUnits(possibleUnits, std::vector<int>{8, 34, 43});
            break;
        case 7: // aquarium air
            core_functions::addUnits(possibleUnits, std::vector<int>{44, 45});
            break;
        case 8: // aquarium lid
            core_functions::addUnits(possibleUnits, std::vector<int>{});
            break;

        // Dimension II
        case 11: // sewer stone
            core_functions::addUnits(possibleUnits, std::vector<int>{});
            break;
        case 12: // sewer stone surface
            core_functions::addUnits(possibleUnits, std::vector<int>{64, 74, 75, 84, 93});
            break;
        case 13: // sewer water bottom 1/2/3/4
            core_functions::addUnits(possibleUnits, std::vector<int>{51, 52, 56, 61, 71, 81, 82});
            break;
        case 14: // sewer water bottom 2/3/4/5
            core_functions::addUnits(possibleUnits, std::vector<int>{61, 71, 81, 82, 91});
            break;
        case 15: // sewer water 1/2/3
            core_functions::addUnits(possibleUnits, std::vector<int>{55, 56, 74, 75, 76, 77});
            break;
        case 16: // sewer water 1/2/3/4/5
            core_functions::addUnits(possibleUnits, std::vector<int>{55, 64, 74, 75, 76, 77, 84, 85, 86, 93});
            break;
        case 17: // sewer water surface 1/2/3/4
            core_functions::addUnits(possibleUnits, std::vector<int>{53, 62, 72, 83});
            break;
        case 18: // sewer water surface 2/3/4/5
            core_functions::addUnits(possibleUnits, std::vector<int>{62, 72, 83, 92, 93});
            break;
        case 19: // sewer air
            core_functions::addUnits(possibleUnits, std::vector<int>{54, 63, 73});
            break;
        case 20: // strong currect
            break;

        // Dimension III
        case 21: // toxic mud
            core_functions::addUnits(possibleUnits, std::vector<int>{109, 110, 111, 112, 113, 114, 138});
            break;
        case 22: // sewer runoff
            core_functions::addUnits(possibleUnits, std::vector<int>{76, 77, 86, 93, 107, 108, 113, 114, 117});
            break;
        case 23: // sewer runoff surface
            core_functions::addUnits(possibleUnits, std::vector<int>{72, 85, 87, 88, 117, 134, 164});
            break;
        case 24: // sewer runoff air
            core_functions::addUnits(possibleUnits, std::vector<int>{101, 102, 103, 104});
            break;
        case 25: // pebbles
            core_functions::addUnits(possibleUnits, std::vector<int>{110, 111, 112, 115, 121, 122, 123, 152, 154, 231});
            break;
        case 26: // spring water
            core_functions::addUnits(possibleUnits, std::vector<int>{113, 114, 140, 142, 147, 153, 154, 172});
            break;
        case 27: // spring water surface
            core_functions::addUnits(possibleUnits, std::vector<int>{135, 140, 141, 142, 162, 163, 164, 202});
            break;
        case 28: // spring water air
            core_functions::addUnits(possibleUnits, std::vector<int>{101, 102, 103, 104, 131, 200, 220});
            break;
        case 29: // shallow lake mud
            core_functions::addUnits(possibleUnits, std::vector<int>{109, 110, 111, 112, 113, 114, 115, 116, 138, 173});
            break;
        case 30: // deep lake water
            core_functions::addUnits(possibleUnits, std::vector<int>{174, 175, 176, 228, 229, 230});
            break;
        case 31: // shallow lake water
            core_functions::addUnits(possibleUnits, std::vector<int>{117, 140, 141, 142, 143, 144, 145, 146, 147, 148, 172, 196, 226, 227});
            break;
        case 32: // lake water surface
            core_functions::addUnits(possibleUnits, std::vector<int>{117, 133, 135, 140, 141, 142, 143, 149, 150, 151, 162, 163, 164, 226, 227});
            break;
        case 33: // lake water air
            core_functions::addUnits(possibleUnits, std::vector<int>{101, 102, 103, 104, 105, 106, 131, 132, 161, 199, 200, 220});
            break;
        case 34: // field grass 1
            core_functions::addUnits(possibleUnits, std::vector<int>{118, 119, 120, 136, 137, 165, 167, 168, 171, 181, 182, 192, 203, 204, 205, 206, 208, 211, 212});
            break;
        case 35: // dirt (movable - rocks)
            core_functions::addUnits(possibleUnits, std::vector<int>{119, 136, 165, 168, 169, 192, 198, 201, 203, 204, 207, 236});
            break;
        case 36: // underbrush (movable - trees)
            core_functions::addUnits(possibleUnits, std::vector<int>{125, 130, 136, 139, 159, 165, 167, 168, 170, 180, 190, 192, 197, 203, 204, 209, 223, 245});
            break;
        case 37: // ground (immovable for all)
            core_functions::addUnits(possibleUnits, std::vector<int>{});
            break;
        case 38: // forest air
            core_functions::addUnits(possibleUnits, std::vector<int>{128, 129, 157, 158});
            break;
        case 39: // forest tree 1
            core_functions::addUnits(possibleUnits, std::vector<int>{106, 128, 129, 157, 158, 160, 186, 188, 189, 210, 213, 253});
            break;
        case 40: // forest tree 2 (light)
            core_functions::addUnits(possibleUnits, std::vector<int>{186, 188, 254, 256, 258, 260, 262, 264, 266, 269});
            break;
        case 41: // forest tree 3 (dark)
            core_functions::addUnits(possibleUnits, std::vector<int>{186, 188, 255, 257, 259, 261, 263, 265, 267, 270});
            break;
        case 42: // sewers
            core_functions::addUnits(possibleUnits, std::vector<int>{});
            break;
        case 43: // cliff
            core_functions::addUnits(possibleUnits, std::vector<int>{});
            break;
        case 44: // deep lake mud
            core_functions::addUnits(possibleUnits, std::vector<int>{177, 178, 179, 193, 194, 195, 228, 229, 230});
            break;
        case 45: // field air
            core_functions::addUnits(possibleUnits, std::vector<int>{124, 126, 127, 155, 156});
            break;
        case 46: // mountain air (rock)
            core_functions::addUnits(possibleUnits, std::vector<int>{183, 184, 185, 214});
            break;
        case 47: // field grass 2
            core_functions::addUnits(possibleUnits, std::vector<int>{120, 137, 166, 167, 191, 192, 201, 203, 204, 212, 221, 225, 237, 238, 239, 240, 242});
            break;
        case 48: // field air 2
            core_functions::addUnits(possibleUnits, std::vector<int>{127, 155, 156, 183, 185, 187});
            break;
        case 49: // mountain air 2
            core_functions::addUnits(possibleUnits, std::vector<int>{183, 214, 215, 216, 232});
            break;
        case 50: // mountain air 3 (snow)
            core_functions::addUnits(possibleUnits, std::vector<int>{217, 218, 219});
            break;
        case 51: // mountain surface 2 (mountain)
            core_functions::addUnits(possibleUnits, std::vector<int>{166, 168, 170, 191, 222, 233, 234, 235, 241, 243, 244});
            break;
        case 52: // mountain surface 3 (snow)
            core_functions::addUnits(possibleUnits, std::vector<int>{224, 246, 247, 248, 249, 250, 251, 252});
            break;
    }
    return possibleUnits;
}

// Prints area info (for debugging)
void Area::printAreaInfo() {
    std::cout << this->getName() << ":\n";
}

// Add and remove environment keys for units
void Area::addUnitKey(int key) {
    auto index = std::find(this->unitKeys.begin(), this->unitKeys.end(), key);
    if (index == this->unitKeys.end()) {
        this->unitKeys.push_back(key);
    }
}
bool Area::removeUnitKey(int key) {
    bool removeSuccessful{ false };
    auto index = std::find(this->unitKeys.begin(), this->unitKeys.end(), key);
    if (index != this->unitKeys.end()) {
        this->unitKeys.erase(index);
        removeSuccessful = true;
    }
    return removeSuccessful;
}

// Return string for saved game files
std::string Area::saveGame() {
    std::string fileString{};
    fileString += "*DEFINE=Area\n";
    fileString += "areaType=" + std::to_string(areaType) + "\n";
    fileString += "x1=" + std::to_string(x1) + "\n";
    fileString += "y1=" + std::to_string(y1) + "\n";
    fileString += "z1=" + std::to_string(z1) + "\n";
    fileString += "x2=" + std::to_string(x2) + "\n";
    fileString += "y2=" + std::to_string(y2) + "\n";
    fileString += "z2=" + std::to_string(z2) + "\n";
    fileString += "maxSpace=" + std::to_string(maxSpace) + "\n";
    fileString += "*VECTOR=unitKeys\n";
    for (int i : this->unitKeys) {
        fileString += std::to_string(i) + "\n";
    }
    fileString += "*END\n"; // end vector
    fileString += "*END\n"; // end area
    return fileString;
}