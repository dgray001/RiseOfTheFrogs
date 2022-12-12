/*
commandClass.cpp
The command class allows any possible command (from quitting the application to moving to
fighting) to be grouped as a common type.
*/

#include <iostream>
#include <string>
#include <vector>

#include "commandClass.h"
#include "abilityClass.h"
#include "unitClass.h"
#include "battleClass.h"
#include "coreFunctions.h"
#include "environmentClass.h"

// base constructor
Command::Command(std::string name, std::string shortDescription, std::string longDescription,
    std::vector<std::string> otherNames) {
    this->name = name;
    this->shortDescription = shortDescription;
    this->longDescription = longDescription;
    this->otherNames = otherNames;
}

// constructor just from unique name (this is the command class references)
Command::Command(std::string name) : Command(name, Player()) {
}
Command::Command(std::string name, Player player) {
    this->name = name;

    // basic commands
    if (this->name.compare("quit") == 0) {
        this->shortDescription = "Save and quit.";
        this->longDescription = "Saves current progress and quits the game. Alternate: \"exit\"\n\n";
        this->otherNames = std::vector<std::string>{ "exit", "Quit", "Exit" };
    }
    else if (this->name.compare("options") == 0) {
        this->shortDescription = "Opens the options menu.";
        this->longDescription = "Open the options menu to change options such as autosave, time lengths, etc.\n\n";
        this->otherNames = std::vector<std::string>{ "Options", "settings", "Settings" };
    }
    else if (this->name.compare("commands") == 0) {
        this->shortDescription = "Displays the current list of possible commands.";
        this->longDescription = "Prints out a list of the commands possible to use at this moment "
            "with a short description of each.\n\n";
        this->otherNames = std::vector<std::string>{ "command", "Commands", "Command" };
    }
    else if (this->name.compare("help") == 0) {
        this->shortDescription = "Prints general instructions or long description for a specific "
            "command.";
        this->longDescription = "Using \"help\" prints general instructions of how the "
            "game works and how to interact with it. With argument \"help 'command'\" prints a "
            "long description of the specified command.\n\n";
        this->otherNames = std::vector<std::string>{ "Help", "?" };
    }
    else if (this->name.compare("achievements") == 0) {
        this->shortDescription = "Displays the player's achievements.";
        this->longDescription = "Displays the list of achievements the player has accomplished.\n\n";
        this->otherNames = std::vector<std::string>{ "Achievements", "Achievement", "achievement" };
    }
    else if (this->name.compare("credits") == 0) {
        this->shortDescription = "Prints credits.\n"; // this extra newline separates these from battle/environment commands
        this->longDescription = "Prints credits to the screen.\n\n";
        this->otherNames = std::vector<std::string>{ "Credits" };
    }

    // battle commands
    // NOTE: I do not set energy cost for battle abilities (only environment commands)
    if (this->name.compare("battleInfo") == 0) {
        this->shortDescription = "Displays battle info.";
        this->longDescription = "Prints current battle state.\n\n";
        this->otherNames = std::vector<std::string>{ "BattleInfo", "battleinfo", "Battleinfo" };
    }
    else if (this->name.compare("nothing") == 0) {
        this->shortDescription = "Skips your turn.";
        this->longDescription = "Do nothing and skip your turn.\n\n";
        this->otherNames = std::vector<std::string>{ "Nothing" };
    }
    else if (this->name.compare("item") == 0) {
        this->shortDescription = "Consume an item.";
        this->longDescription = "Consume an item. Use \"item index\" where \"index\" is the index of "
            "the item you want to consume. Use \"item\" with no argument to see a list of consumable "
            "items and their respective indices.\n\n";
        this->otherNames = std::vector<std::string>{ "Item", "items", "Items" };
    }
    // Flee abilities
    if (this->name.compare("flee") == 0) {
        this->shortDescription = "Flee from battle.";
        this->longDescription = "Attempt to flee the current battle and return to the environment.\n\n";
        this->otherNames = std::vector<std::string>{ "Flee" };
    }
    else if (this->name.compare("swimaway") == 0) {
        this->shortDescription = "Swim away from battle.";
        this->longDescription = "Attempt to flee the battle with a small boost to dexterity.\n\n";
        this->otherNames = std::vector<std::string>{ "Swimaway" };
    }
    else if (this->name.compare("jumpaway") == 0) {
        this->shortDescription = "Jump away from battle.";
        this->longDescription = "Attempt to flee the battle with a moderate boost to dexterity.\n\n";
        this->otherNames = std::vector<std::string>{ "Jumpaway" };
    }
    else if (this->name.compare("flyaway") == 0) {
        this->shortDescription = "Fly away from battle.";
        this->longDescription = "Attempt to flee the battle with a large boost to dexterity.\n\n";
        this->otherNames = std::vector<std::string>{ "Flyaway" };
    }
    else if (this->name.compare("recoil") == 0) {
        this->shortDescription = "Attack and flee from battle.";
        this->longDescription = "Send a weak blow as you turn and flee.\n\n";
        this->otherNames = std::vector<std::string>{ "Recoil" };
    }
    // Weak status effect causer abilities
    if (this->name.compare("bleed") == 0) {
        this->shortDescription = "Bleed your opponent.";
        this->longDescription = "Large chance to cause your opponent to bleed.\n\n";
        this->otherNames = std::vector<std::string>{ "Bleed" };
    }
    else if (this->name.compare("wilt") == 0) {
        this->shortDescription = "Wilt your opponent.";
        this->longDescription = "Large chance to cause your opponent to wilt.\n\n";
        this->otherNames = std::vector<std::string>{ "Wilt" };
    }
    else if (this->name.compare("dunk") == 0) {
        this->shortDescription = "Dunk your opponent underwater.";
        this->longDescription = "Large chance to cause your opponent to be drowning.\n\n";
        this->otherNames = std::vector<std::string>{ "Dunk" };
    }
    else if (this->name.compare("burn") == 0) {
        this->shortDescription = "Burn your opponent.";
        this->longDescription = "Large chance to cause your opponent to burn.\n\n";
        this->otherNames = std::vector<std::string>{ "Burn" };
    }
    else if (this->name.compare("rot") == 0) {
        this->shortDescription = "Rot your opponent.";
        this->longDescription = "Large chance to cause your opponent to rot.\n\n";
        this->otherNames = std::vector<std::string>{ "Rot" };
    }
    else if (this->name.compare("chill") == 0) {
        this->shortDescription = "Chill your opponent.";
        this->longDescription = "Large chance to cause your opponent to be chilled.\n\n";
        this->otherNames = std::vector<std::string>{ "Chill" };
    }
    else if (this->name.compare("infect") == 0) {
        this->shortDescription = "Infect your opponent.";
        this->longDescription = "Large chance to cause your opponent to be infected.\n\n";
        this->otherNames = std::vector<std::string>{ "Infect" };
    }
    else if (this->name.compare("shake") == 0) {
        this->shortDescription = "Shake your opponent.";
        this->longDescription = "Large chance to cause your opponent to be shaken.\n\n";
        this->otherNames = std::vector<std::string>{ "Shake" };
    }
    else if (this->name.compare("shock") == 0) {
        this->shortDescription = "Shock your opponent.";
        this->longDescription = "Large chance to cause your opponent to be shocked.\n\n";
        this->otherNames = std::vector<std::string>{ "Shock" };
    }
    else if (this->name.compare("destabilize") == 0) {
        this->shortDescription = "Destabilize your opponent.";
        this->longDescription = "Large chance to cause your opponent to be nuclearly destabilized.\n\n";
        this->otherNames = std::vector<std::string>{ "Destabilize" };
    }
    else if (this->name.compare("obscure") == 0) {
        this->shortDescription = "Obscure events from your opponent.";
        this->longDescription = "Large chance to obscure what's going on from your opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Obscure" };
    }
    else if (this->name.compare("brighten") == 0) {
        this->shortDescription = "Brighten your opponent's future to you.";
        this->longDescription = "Large chance to brighten your opponent's future to you.\n\n";
        this->otherNames = std::vector<std::string>{ "Brighten" };
    }
    // Strong status effect causer abilities
    if (this->name.compare("hemorrhage") == 0) {
        this->shortDescription = "Hemorrhage your opponent.";
        this->longDescription = "Large chance to cause your opponent to hemorrhage.\n\n";
        this->otherNames = std::vector<std::string>{ "Hemorrhage" };
    }
    else if (this->name.compare("wither") == 0) {
        this->shortDescription = "Wither your opponent.";
        this->longDescription = "Large chance to cause your opponent to wither.\n\n";
        this->otherNames = std::vector<std::string>{ "Wither" };
    }
    else if (this->name.compare("drown") == 0) {
        this->shortDescription = "Drown your opponent.";
        this->longDescription = "Large chance to cause your opponent to drown.\n\n";
        this->otherNames = std::vector<std::string>{ "Drown" };
    }
    else if (this->name.compare("char") == 0) {
        this->shortDescription = "Char your opponent.";
        this->longDescription = "Large chance to cause your opponent to be charred.\n\n";
        this->otherNames = std::vector<std::string>{ "Char" };
    }
    else if (this->name.compare("decay") == 0) {
        this->shortDescription = "Decay your opponent.";
        this->longDescription = "Large chance to cause your opponent to decay.\n\n";
        this->otherNames = std::vector<std::string>{ "Decay" };
    }
    else if (this->name.compare("freeze") == 0) {
        this->shortDescription = "Freeze your opponent.";
        this->longDescription = "Large chance to cause your opponent to freeze.\n\n";
        this->otherNames = std::vector<std::string>{ "Freeze" };
    }
    else if (this->name.compare("disease") == 0) {
        this->shortDescription = "Disease your opponent.";
        this->longDescription = "Large chance to cause your opponent to be diseased.\n\n";
        this->otherNames = std::vector<std::string>{ "Disease" };
    }
    else if (this->name.compare("fell") == 0) {
        this->shortDescription = "Fell your opponent.";
        this->longDescription = "Large chance to cause your opponent to fall over.\n\n";
        this->otherNames = std::vector<std::string>{ "Fell" };
    }
    else if (this->name.compare("paralyze") == 0) {
        this->shortDescription = "Paralyze your opponent.";
        this->longDescription = "Large chance to cause your opponent to be paralyzed.\n\n";
        this->otherNames = std::vector<std::string>{ "Paralyze" };
    }
    else if (this->name.compare("radiate") == 0) {
        this->shortDescription = "Radiate your opponent.";
        this->longDescription = "Large chance to cause your opponent to become radioactive.\n\n";
        this->otherNames = std::vector<std::string>{ "Radiate" };
    }
    else if (this->name.compare("hide") == 0) {
        this->shortDescription = "Hide the truth from your opponent.";
        this->longDescription = "Large chance to hide events from your opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Hide" };
    }
    else if (this->name.compare("illuminate") == 0) {
        this->shortDescription = "Illuminate your opponent's future to you.";
        this->longDescription = "Large chance to illuminate your opponent's future.\n\n";
        this->otherNames = std::vector<std::string>{ "Illuminate" };
    }
    // Weak basic attacks
    if (this->name.compare("attack") == 0) {
        this->shortDescription = "Your basic attack.";
        this->longDescription = "Your basic attack. Small chance to cause bleeding.\n\n";
        this->otherNames = std::vector<std::string>{ "Attack" };
    }
    else if (this->name.compare("nibble") == 0) {
        this->shortDescription = "Nibble at your opponent.";
        this->longDescription = "Nibble at your opponent, increasing attack but decreasing "
            "dexterity and piercing. Small lifesteal. Small chance to cause bleeding and infect.\n\n";
        this->otherNames = std::vector<std::string>{ "Nibble" };
    }
    else if (this->name.compare("lunge") == 0) {
        this->shortDescription = "Lunge at your opponent.";
        this->longDescription = "Lunge at your opponent with increased dexterity but decreased "
            "attack and piercing. Small chance to cause bleeding.\n\n";
        this->otherNames = std::vector<std::string>{ "Lunge" };
    }
    else if (this->name.compare("bite") == 0) {
        this->shortDescription = "Bite your opponent.";
        this->longDescription = "Bite your opoonent, increasing piercing but decreasing dexterity."
            " Moderate lifesteal. Small chance to cause bleeding and infect.\n\n";
        this->otherNames = std::vector<std::string>{ "Bite" };
    }
    else if (this->name.compare("charge") == 0) {
        this->shortDescription = "Charge at your opponent.";
        this->longDescription = "Charge at your opponent with increased attack but a small decrease "
            "to piercing and dexterity. Small chance to cause bleeding.\n\n";
        this->otherNames = std::vector<std::string>{ "Charge" };
    }
    else if (this->name.compare("pinch") == 0) {
        this->shortDescription = "Pinch your opponent.";
        this->longDescription = "Pinch your opponent, increasing piercing with a small decrease "
            "to dexterity. Small chance to cause bleed or infect.\n\n";
        this->otherNames = std::vector<std::string>{ "Pinch" };
    }
    else if (this->name.compare("flail") == 0) {
        this->shortDescription = "Attack by flailing at your opponent.";
        this->longDescription = "Alternate blue basic attack. Increased dexterity but small "
            "decrease in attack and piercing. Small chance to cause drowning.\n\n";
        this->otherNames = std::vector<std::string>{ "Flail" };
    }
    else if (this->name.compare("rub") == 0) {
        this->shortDescription = "Quickly rub your opponent.";
        this->longDescription = "Alternate red basic attack. Small increase to attack but small "
            "decrease to piercing. Small chance to burn.\n\n";
        this->otherNames = std::vector<std::string>{ "Rub" };
    }
    else if (this->name.compare("excrete") == 0) {
        this->shortDescription = "Excrete toxins at your opponent.";
        this->longDescription = "Alternate brown basic attack. Decreaed attack and piercing but "
            "small lifesteal and large chance to cause rot.\n\n";
        this->otherNames = std::vector<std::string>{ "Excrete" };
    }
    else if (this->name.compare("coldslash") == 0) {
        this->shortDescription = "Attack with a chilled claw.";
        this->longDescription = "Alternate cyan basic attack. Increased attack but decreased "
            "piercing and dexterity. Medium chance to chill opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Coldslash" };
    }
    else if (this->name.compare("dive") == 0) {
        this->shortDescription = "Dive at your opponent.";
        this->longDescription = "Alternate orange basic attack. Increased piercing and small "
            "chance to cause infect.\n\n";
        this->otherNames = std::vector<std::string>{ "Dive" };
    }
    else if (this->name.compare("magicattack") == 0) {
        this->shortDescription = "Use your weapon to deal magic damage.";
        this->longDescription = "Deal magic damage from your attack stat. Small chance to cause "
            "wilt.\n\n";
        this->otherNames = std::vector<std::string>{ "Magicattack" };
    }
    else if (this->name.compare("waterstrike") == 0) {
        this->shortDescription = "Strike with water.";
        this->longDescription = "Blue basic attack. Small chance to cause drowning.\n\n";
        this->otherNames = std::vector<std::string>{ "Waterstrike" };
    }
    else if (this->name.compare("firestrike") == 0) {
        this->shortDescription = "Strike with fire.";
        this->longDescription = "Red basic attack. Small chance to burn.\n\n";
        this->otherNames = std::vector<std::string>{ "Firestrike" };
    }
    else if (this->name.compare("earthstrike") == 0) {
        this->shortDescription = "Strike with earth.";
        this->longDescription = "Brown basic attack. Small chance to cause rot.\n\n";
        this->otherNames = std::vector<std::string>{ "Earthstrike" };
    }
    else if (this->name.compare("icestrike") == 0) {
        this->shortDescription = "Strike with ice.";
        this->longDescription = "Cyan basic attack. Small chance to chill.\n\n";
        this->otherNames = std::vector<std::string>{ "Icestrike" };
    }
    else if (this->name.compare("airstrike") == 0) {
        this->shortDescription = "Strike with air.";
        this->longDescription = "Orange basic attack. Small chance to cause infect.\n\n";
        this->otherNames = std::vector<std::string>{ "Airstrike" };
    }
    else if (this->name.compare("gravitystrike") == 0) {
        this->shortDescription = "Strike with gravity.";
        this->longDescription = "Purple basic attack. Small chance to shake opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Gravitystrike" };
    }
    else if (this->name.compare("electricitystrike") == 0) {
        this->shortDescription = "Strike with electricity.";
        this->longDescription = "Yellow basic attack. Small chance to shock.\n\n";
        this->otherNames = std::vector<std::string>{ "Electricitystrike" };
    }
    else if (this->name.compare("nuclearstrike") == 0) {
        this->shortDescription = "Strike with nuclear forces.";
        this->longDescription = "Magenta basic attack. Small chance to destabilize opponent's nuclei.\n\n";
        this->otherNames = std::vector<std::string>{ "Nuclearstrike" };
    }
    else if (this->name.compare("darkstrike") == 0) {
        this->shortDescription = "Strike with darkness.";
        this->longDescription = "Black basic attack. Small chance to obscure opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Darkstrike" };
    }
    else if (this->name.compare("lightstrike") == 0) {
        this->shortDescription = "Strike with light.";
        this->longDescription = "White basic attack. Small chance to brighten opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Lightstrike" };
    }
    else if (this->name.compare("naturestrike") == 0) {
        this->shortDescription = "Strike with nature itself.";
        this->longDescription = "Green basic attack. Small chance to balance opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Naturestrike" };
    }
    // Weak basic spells
    if (this->name.compare("wisp") == 0) {
        this->shortDescription = "Send a wisp of energy to your opponent.";
        this->longDescription = "Basic weak spell directly using your magic stats. Small chance to "
            "cause opponent to wilt.\n\n";
        this->otherNames = std::vector<std::string>{ "Wisp" };
    }
    else if (this->name.compare("magicstrike") == 0) {
        this->shortDescription = "Use magic to deal physical damage.";
        this->longDescription = "Deal physical damage from your magic stat. Small chance to cause "
            "bleed.\n\n";
        this->otherNames = std::vector<std::string>{ "Magicstrike" };
    }
    else if (this->name.compare("drain") == 0) {
        this->shortDescription = "Drain a small amount of lifeforce from your opponent.";
        this->longDescription = "Drains life from your opponent. Small decrease to magic and "
            "small lifesteal.\n\n";
        this->otherNames = std::vector<std::string>{ "Drain" };
    }
    else if (this->name.compare("bandage") == 0) {
        this->shortDescription = "Use magic to bandage your wounds.";
        this->longDescription = "Use magic to bandage your wounds, restoring 15 health.\n\n";
        this->otherNames = std::vector<std::string>{ "Bandage" };
    }
    else if (this->name.compare("heal") == 0) {
        this->shortDescription = "Use magic to heal your wounds.";
        this->longDescription = "Use magic to heal your wounds, restoring 30 health.\n\n";
        this->otherNames = std::vector<std::string>{ "Heal" };
    }
    else if (this->name.compare("splash") == 0) {
        this->shortDescription = "Splash water on your opponent.";
        this->longDescription = "Basic blue weak spell. Small chance to cause drowning.\n\n";
        this->otherNames = std::vector<std::string>{ "Splash" };
    }
    else if (this->name.compare("flame") == 0) {
        this->shortDescription = "Shoot a flame at your opponent.";
        this->longDescription = "Basic red weak spell. Small chance to burn.\n\n";
        this->otherNames = std::vector<std::string>{ "Flame" };
    }
    else if (this->name.compare("dust") == 0) {
        this->shortDescription = "Conjure the dust to attack your opponent.";
        this->longDescription = "Basic brown weak spell. Small chance to cause rot.\n\n";
        this->otherNames = std::vector<std::string>{ "Dust" };
    }
    else if (this->name.compare("frost") == 0) {
        this->shortDescription = "Send frost at your opponent.";
        this->longDescription = "Basic cyan weak spell. Small chance to chill.\n\n";
        this->otherNames = std::vector<std::string>{ "Frost" };
    }
    else if (this->name.compare("breeze") == 0) {
        this->shortDescription = "Shoot a breeze at your opponent.";
        this->longDescription = "Basic orange weak spell. Small chance to cause infect.\n\n";
        this->otherNames = std::vector<std::string>{ "Breeze" };
    }
    else if (this->name.compare("pull") == 0) {
        this->shortDescription = "Pull your opponent.";
        this->longDescription = "Basic purple weak spell. Small chance to shake opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Pull" };
    }
    else if (this->name.compare("spark") == 0) {
        this->shortDescription = "Shoot a spark at your opponent.";
        this->longDescription = "Basic yellow weak spell. Small chance to cause shock.\n\n";
        this->otherNames = std::vector<std::string>{ "Spark" };
    }
    else if (this->name.compare("gammaray") == 0) {
        this->shortDescription = "Shoot a gamma ray at your opponent.";
        this->longDescription = "Basic magenta weak spell. Small chance to destabilize opponen't "
            "nuclei.\n\n";
        this->otherNames = std::vector<std::string>{ "Gammaray" };
    }
    else if (this->name.compare("shadow") == 0) {
        this->shortDescription = "Send a shadow onto your opponent.";
        this->longDescription = "Basic black weak spell. Small chance to obscure events from your "
            "opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Shadow" };
    }
    else if (this->name.compare("ray") == 0) {
        this->shortDescription = "Send a ray to your opponent.";
        this->longDescription = "Basic white weak spell. Small chance to brighten opponent's future.\n\n";
        this->otherNames = std::vector<std::string>{ "Ray" };
    }
    // Strong basic attacks
    if (this->name.compare("hammer") == 0) {
        this->shortDescription = "Hammer your opponent hard.";
        this->longDescription = "Strong basic attack. Small chance to cause hemorrhage.\n\n";
        this->otherNames = std::vector<std::string>{ "Hammer" };
    }
    else if (this->name.compare("jump") == 0) {
        this->shortDescription = "Jump at your opponent.";
        this->longDescription = "Jump at your opponent with increased dexterity but decreased "
            "attack and piercing. Small chance to cause bleed.\n\n";
        this->otherNames = std::vector<std::string>{ "Jump" };
    }
    else if (this->name.compare("toxicbite") == 0) {
        this->shortDescription = "Bite your opponent with toxins.";
        this->longDescription = "Bite your opponent with toxins. Lifesteal and medium chance to "
            "cause bleed, rot, infect, decay, and disease.\n\n";
        this->otherNames = std::vector<std::string>{ "Toxicbite", "toxicBite", "ToxicBite" };
    }
    else if (this->name.compare("chomp") == 0) {
        this->shortDescription = "Chomp into your opponent's flesh.";
        this->longDescription = "Chomp into your opponent's flesh. Large attack, dexterity decrease, "
            "lifesteal, and large chance to cause bleeding.\n\n";
        this->otherNames = std::vector<std::string>{ "Chomp" };
    }
    else if (this->name.compare("slash") == 0) {
        this->shortDescription = "Slash your opponent.";
        this->longDescription = "Slash your opponent. Increased attack and large chance to "
            "cause bleeding.\n\n";
        this->otherNames = std::vector<std::string>{ "Slash" };
    }
    else if (this->name.compare("suck") == 0) {
        this->shortDescription = "Suck your opponent's blood.";
        this->longDescription = "Suck your opponent's blood for large lifesteal and a small chance "
            "to cause infect, disease, and bleeding.\n\n";
        this->otherNames = std::vector<std::string>{ "Suck" };
    }
    else if (this->name.compare("poison") == 0) {
        this->shortDescription = "Attack with poison.";
        this->longDescription = "Poison your opponent for a medium chance to cause infect, disease, "
            "wilt, and wither.\n\n";
        this->otherNames = std::vector<std::string>{ "Poison" };
    }
    else if (this->name.compare("claw") == 0) {
        this->shortDescription = "Claw at your opponent.";
        this->longDescription = "Claw at your opponent for increased attack, a small increase in "
            "dexterity, and medium chance to cause bleed.\n\n";
        this->otherNames = std::vector<std::string>{ "Claw" };
    }
    else if (this->name.compare("maul") == 0) {
        this->shortDescription = "Maul your opponent hard.";
        this->longDescription = "Maul your opponent hard. Large attack and a medium chance to cause "
            "bleed or hemorrhage.\n\n";
        this->otherNames = std::vector<std::string>{ "Maul" };
    }
    else if (this->name.compare("peck") == 0) {
        this->shortDescription = "Peck your opponent.";
        this->longDescription = "Peck your opponent hard. Increased piercing and small chance to "
            "cause infect and bleed.\n\n";
        this->otherNames = std::vector<std::string>{ "Peck" };
    }
    else if (this->name.compare("thrash") == 0) {
        this->shortDescription = "Attack by thrashing at your opponent.";
        this->longDescription = "Alternate blue strong basic attack. Increased dexterity and small "
            "chance to cause drowning and drowned.\n\n";
        this->otherNames = std::vector<std::string>{ "Thrash" };
    }
    else if (this->name.compare("ignite") == 0) {
        this->shortDescription = "Ignite your opponent.";
        this->longDescription = "Alternate red strong basic attack. Small increase to attack and "
            "small chance to burn or char.\n\n";
        this->otherNames = std::vector<std::string>{ "Rub" };
    }
    else if (this->name.compare("ooze") == 0) {
        this->shortDescription = "Ooze toxins at your opponent.";
        this->longDescription = "Alternate brown strong basic attack. Lifesteal and large chance "
            "to cause rot and decay.\n\n";
        this->otherNames = std::vector<std::string>{ "Ooze" };
    }
    else if (this->name.compare("coldmaul") == 0) {
        this->shortDescription = "Maul your opponent with a frozen claw.";
        this->longDescription = "Alternate cyan strong basic attack. Increased attack and medium "
            "chance to chill and freeze opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Coldmaul", "coldMaul", "ColdMaul" };
    }
    else if (this->name.compare("flurry") == 0) {
        this->shortDescription = "Attack in a flurry.";
        this->longDescription = "Alternate orange strong basic attack. Attack 3 times with a small "
            "chance to infect or cause disease.\n\n";
        this->otherNames = std::vector<std::string>{ "Flurry" };
    }
    else if (this->name.compare("magichammer") == 0) {
        this->shortDescription = "Use your weapon to hammer down magic damage.";
        this->longDescription = "Deal magic damage from your attack stat. Small chance to cause "
            "wither.\n\n";
        this->otherNames = std::vector<std::string>{ "Magichammer", "magicHammer", "MagicHammer" };
    }
    else if (this->name.compare("waterseal") == 0) {
        this->shortDescription = "Seal your opponent's fate with water.";
        this->longDescription = "Blue strong basic attack. Small chance to cause drowned.\n\n";
        this->otherNames = std::vector<std::string>{ "Waterseal" };
    }
    else if (this->name.compare("fireseal") == 0) {
        this->shortDescription = "Seal your opponent's fate with fire.";
        this->longDescription = "Red strong basic attack. Small chance to char.\n\n";
        this->otherNames = std::vector<std::string>{ "Fireseal" };
    }
    else if (this->name.compare("earthseal") == 0) {
        this->shortDescription = "Seal your opponent's fate with earth.";
        this->longDescription = "Brown strong basic attack. Small chance to cause decay.\n\n";
        this->otherNames = std::vector<std::string>{ "Earthseal" };
    }
    else if (this->name.compare("iceseal") == 0) {
        this->shortDescription = "Seal your opponent's fate with ice.";
        this->longDescription = "Cyan strong basic attack. Small chance to freeze.\n\n";
        this->otherNames = std::vector<std::string>{ "Iceseal" };
    }
    else if (this->name.compare("airseal") == 0) {
        this->shortDescription = "Seal your opponent's fate with air.";
        this->longDescription = "Orange strong basic attack. Small chance to cause disease.\n\n";
        this->otherNames = std::vector<std::string>{ "Airseal" };
    }
    else if (this->name.compare("gravityseal") == 0) {
        this->shortDescription = "Seal your opponent's fate with gravity.";
        this->longDescription = "Purple strong basic attack. Small chance to cause opponent to fall.\n\n";
        this->otherNames = std::vector<std::string>{ "Gravityseal" };
    }
    else if (this->name.compare("electricityseal") == 0) {
        this->shortDescription = "Seal your opponent's fate with electricity.";
        this->longDescription = "Yellow strong basic attack. Small chance to paralyze.\n\n";
        this->otherNames = std::vector<std::string>{ "Electricityseal" };
    }
    else if (this->name.compare("nuclearseal") == 0) {
        this->shortDescription = "Seal your opponent's fate with nuclear force.";
        this->longDescription = "Magenta strong basic attack. Small chance to make opponent radioactive.\n\n";
        this->otherNames = std::vector<std::string>{ "Nuclearseal" };
    }
    else if (this->name.compare("darkseal") == 0) {
        this->shortDescription = "Seal your opponent's fate with darkness.";
        this->longDescription = "Black strong basic attack. Small chance to hide opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Darkseal" };
    }
    else if (this->name.compare("lightseal") == 0) {
        this->shortDescription = "Seal your opponent's fate with light.";
        this->longDescription = "White strong basic attack. Small chance to illuminate opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Lightseal" };
    }
    else if (this->name.compare("natureseal") == 0) {
        this->shortDescription = "Seal your opponent's fate with nature itself.";
        this->longDescription = "Green strong basic attack. Small chance to equalize opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Natureseal" };
    }
    // Strong basic spells
    if (this->name.compare("bolt") == 0) {
        this->shortDescription = "Send a bolt of energy to your opponent.";
        this->longDescription = "Basic strong spell directly using your magic stats. Small chance to "
            "cause opponent to wither.\n\n";
        this->otherNames = std::vector<std::string>{ "Bolt" };
    }
    else if (this->name.compare("magicseal") == 0) {
        this->shortDescription = "Use strong magic to deal physical damage.";
        this->longDescription = "Deal strong physical damage from your magic stat. Small chance to "
            "cause hemorrhage.\n\n";
        this->otherNames = std::vector<std::string>{ "Magicseal" };
    }
    else if (this->name.compare("siphon") == 0) {
        this->shortDescription = "Siphon the lifeforce of your opponent.";
        this->longDescription = "Siphon your opponent's lifeforce with moderate lifesteal.\n\n";
        this->otherNames = std::vector<std::string>{ "Siphon" };
    }
    else if (this->name.compare("revive") == 0) {
        this->shortDescription = "Use magic to revive yourself.";
        this->longDescription = "Revive yourself with magic, restoring 50 health.\n\n";
        this->otherNames = std::vector<std::string>{ "Revive" };
    }
    else if (this->name.compare("venom") == 0) {
        this->shortDescription = "Attack with venom.";
        this->longDescription = "Use venom to deal magic damage with a medium chance to cause "
            "infect, disease, wilt, and wither.\n\n";
        this->otherNames = std::vector<std::string>{ "Venom" };
    }
    else if (this->name.compare("stream") == 0) {
        this->shortDescription = "Stream water toward your opponent.";
        this->longDescription = "Basic blue strong spell. Small chance to cause drowned.\n\n";
        this->otherNames = std::vector<std::string>{ "Stream" };
    }
    else if (this->name.compare("fire") == 0) {
        this->shortDescription = "Shoot fire at your opponent.";
        this->longDescription = "Basic red strong spell. Small chance to char.\n\n";
        this->otherNames = std::vector<std::string>{ "Fire" };
    }
    else if (this->name.compare("dirt") == 0) {
        this->shortDescription = "Conjure dirt to attack your opponent.";
        this->longDescription = "Basic brown strong spell. Small chance to cause decay.\n\n";
        this->otherNames = std::vector<std::string>{ "Dirt" };
    }
    else if (this->name.compare("crystal") == 0) {
        this->shortDescription = "Send ice crytals at your opponent.";
        this->longDescription = "Basic cyan strong spell. Small chance to frozen.\n\n";
        this->otherNames = std::vector<std::string>{ "Crystal" };
    }
    else if (this->name.compare("wind") == 0) {
        this->shortDescription = "Shoot wind at your opponent.";
        this->longDescription = "Basic orange strong spell. Small chance to cause disease.\n\n";
        this->otherNames = std::vector<std::string>{ "Wind" };
    }
    else if (this->name.compare("orbit") == 0) {
        this->shortDescription = "Cause your opponent to orbit around you.";
        this->longDescription = "Basic purple strong spell. Small chance make opponent fall.\n\n";
        this->otherNames = std::vector<std::string>{ "Orbit" };
    }
    else if (this->name.compare("static") == 0) {
        this->shortDescription = "Shoot static electricity at your opponent.";
        this->longDescription = "Basic yellow strong spell. Small chance to cause paralyze.\n\n";
        this->otherNames = std::vector<std::string>{ "Static" };
    }
    else if (this->name.compare("betaray") == 0) {
        this->shortDescription = "Shoot a beta ray at your opponent.";
        this->longDescription = "Basic magenta strong spell. Small chance to make opponent radioactive.\n\n";
        this->otherNames = std::vector<std::string>{ "Betaray" };
    }
    else if (this->name.compare("darkness") == 0) {
        this->shortDescription = "Send darkness over your opponent.";
        this->longDescription = "Basic black strong spell. Small chance to hide events from your "
            "opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Darkness" };
    }
    else if (this->name.compare("beam") == 0) {
        this->shortDescription = "Send a beam of light to your opponent.";
        this->longDescription = "Basic white strong spell. Small chance to illuminate opponent's future.\n\n";
        this->otherNames = std::vector<std::string>{ "Beam" };
    }
    // Stat change abilities
    if (this->name.compare("grow") == 0) {
        this->shortDescription = "Grow in size.";
        this->longDescription = "Small increase to health.\n\n";
        this->otherNames = std::vector<std::string>{ "Grow" };
    }
    else if (this->name.compare("enlarge") == 0) {
        this->shortDescription = "Enlarge yourself greatly.";
        this->longDescription = "Large increase to health.\n\n";
        this->otherNames = std::vector<std::string>{ "Enlarge" };
    }
    else if (this->name.compare("strength") == 0) {
        this->shortDescription = "Increase in strength.";
        this->longDescription = "Small increase to attack.\n\n";
        this->otherNames = std::vector<std::string>{ "Strength" };
    }
    else if (this->name.compare("berserk") == 0) {
        this->shortDescription = "Make yourself beserk.";
        this->longDescription = "Large increase to attack.\n\n";
        this->otherNames = std::vector<std::string>{ "Berserk" };
    }
    else if (this->name.compare("weak") == 0) {
        this->shortDescription = "Make opponent weak.";
        this->longDescription = "Small decrease to attack for opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Weak" };
    }
    else if (this->name.compare("feeble") == 0) {
        this->shortDescription = "Make opponent feeble.";
        this->longDescription = "Large decrease to attack for opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Feeble" };
    }
    else if (this->name.compare("cogent") == 0) {
        this->shortDescription = "Make your magic more cogent.";
        this->longDescription = "Small increase to magic.\n\n";
        this->otherNames = std::vector<std::string>{ "Cogent" };
    }
    else if (this->name.compare("potent") == 0) {
        this->shortDescription = "Make your magic much more potent.";
        this->longDescription = "Large increase to magic.\n\n";
        this->otherNames = std::vector<std::string>{ "Potent" };
    }
    else if (this->name.compare("inept") == 0) {
        this->shortDescription = "Make opponent inept.";
        this->longDescription = "Small decrease to magic for opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Inept" };
    }
    else if (this->name.compare("impotent") == 0) {
        this->shortDescription = "Make opponent impotent.";
        this->longDescription = "Large decrease to magic for opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Impotent" };
    }
    else if (this->name.compare("defend") == 0) {
        this->shortDescription = "Defend yourself.";
        this->longDescription = "Small increase to defense.\n\n";
        this->otherNames = std::vector<std::string>{ "Defend" };
    }
    else if (this->name.compare("bulwark") == 0) {
        this->shortDescription = "Set up a bulwark.";
        this->longDescription = "Large increase to defense.\n\n";
        this->otherNames = std::vector<std::string>{ "Bulwark" };
    }
    else if (this->name.compare("break") == 0) {
        this->shortDescription = "Break opponent's defense.";
        this->longDescription = "Small decrease to defense for opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Break" };
    }
    else if (this->name.compare("smash") == 0) {
        this->shortDescription = "Smash opponent's defense.";
        this->longDescription = "Large decrease to defense for opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Smash" };
    }
    else if (this->name.compare("resolve") == 0) {
        this->shortDescription = "Make your magic more cogent.";
        this->longDescription = "Small increase to penetration.\n\n";
        this->otherNames = std::vector<std::string>{ "Resolve" };
    }
    else if (this->name.compare("dauntless") == 0) {
        this->shortDescription = "Make your magic much more potent.";
        this->longDescription = "Large increase to penetration.\n\n";
        this->otherNames = std::vector<std::string>{ "Dauntless" };
    }
    else if (this->name.compare("outwill") == 0) {
        this->shortDescription = "outwill your opponent.";
        this->longDescription = "Small decrease to penetration for opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Outwill" };
    }
    else if (this->name.compare("shatter") == 0) {
        this->shortDescription = "Shatter your opponent's will.";
        this->longDescription = "Large decrease to penetration for opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Shatter" };
    }
    else if (this->name.compare("swiftness") == 0) {
        this->shortDescription = "Make yourself swift.";
        this->longDescription = "Small increase to dexterity.\n\n";
        this->otherNames = std::vector<std::string>{ "Swiftness" };
    }
    else if (this->name.compare("deftness") == 0) {
        this->shortDescription = "Make yourself deft.";
        this->longDescription = "Large increase to dexterity.\n\n";
        this->otherNames = std::vector<std::string>{ "Deftness" };
    }
    else if (this->name.compare("slow") == 0) {
        this->shortDescription = "Slow your opponent.";
        this->longDescription = "Small decrease to dexterity for opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Slow" };
    }
    else if (this->name.compare("lethargy") == 0) {
        this->shortDescription = "Make opponent lethargic.";
        this->longDescription = "Large decrease to dexterity for opponent.\n\n";
        this->otherNames = std::vector<std::string>{ "Lethargic" };
    }

    // environment commands
    if (this->name.compare("status") == 0) {
        this->shortDescription = "Display your current status.";
        this->longDescription = "Displays your current status. What's displayed will depend on "
            "what you have the capacity to see.\n\n";
        this->otherNames = std::vector<std::string>{ "Status" };
    }
    else if (this->name.compare("quests") == 0) {
        this->shortDescription = "Displays your quests.";
        if (player.getUpgradeAttention1()) {
            this->longDescription = "Display the quests your character is on and their rewards.\n\n";
        }
        else {
            this->longDescription = "Display the quests your character is on. Complete these for rewards.\n\n";
        }
        this->otherNames = std::vector<std::string>{ "Quests", "quest", "Quest" };
    }
    else if (this->name.compare("look") == 0) {
        this->shortDescription = "Look around you.";
        this->longDescription = "You look around you and display what you can see.\n\n";
        this->otherNames = std::vector<std::string>{ "Look" };
    }
    else if (this->name.compare("turn") == 0) {
        this->shortDescription = "Turn another direction.";
        if (player.getUpgradeAttention2()) {
            this->longDescription = "Turn another direction. Specify direction using \"turn "
                "'direction'\" where 'direction' is 'left', 'right', 'up', 'down', or 'around.' "
                "Default turn is 45 degrees in the specified direction for normal turns and 180 "
                "degrees for 'around.' For normal turns specify turn amount with an integer "
                "between 0-180 specifying the degrees to turn (i.e. 'turn left=111' will turn "
                "111 degrees to the left). Note 'up' and 'down' affect phi (z axis turns) while "
                "all other turns affect theta (xy plane turns).\n\n";
        }
        else if ((player.getUpgradeAttention1()) && ((player.getUpgradeForelegs()) || (player.getUpgradeHindlegs()))) {
            this->longDescription = "Turn another direction. Specify direction using \"turn "
                "'direction'\" where 'direction' is 'left', 'right', 'up', 'down', or 'around.' "
                "Turning is 45 degrees in the specified direction for normal turns and 180 degrees "
                "for 'around.'\n\n";
        }
        else if (player.getUpgradeAttention1()) {
            this->longDescription = "Turn another direction. Specify direction using \"turn "
                "'direction'\" where 'direction' is 'left', 'right', or 'around.' "
                "Turning is 45 degrees in the specified direction for normal turns and 180 degrees "
                "for 'around.'\n\n";
        }
        else if ((player.getUpgradeForelegs()) || (player.getUpgradeHindlegs())) {
            this->longDescription = "Turn another direction. Specify direction using \"turn "
                "'direction'\" where 'direction' is 'left', 'right', 'up', 'down.' "
                "Turning is 30 degrees in the specified direction.\n\n";
        }
        else {
            this->longDescription = "Turn another direction. Specify direction using \"turn "
                "'direction'\" where 'direction' is 'left' or 'right.' Turning is "
                "30 degrees in the specified direction.\n\n";
        }
        this->otherNames = std::vector<std::string>{ "Turn" };
        this->energyCost = 1;
    }
    else if (this->name.compare("move") == 0) {
        this->shortDescription = "Move forward.";
        this->longDescription = "Move forward. Use \"move 'number'\" where 'number' is an integer "
            "that specifies how far (in cm) you want to move. Note you cannot move more than your "
            "maximum move distance in one command.\n\n";
        this->otherNames = std::vector<std::string>{ "Move" };
        this->energyCost = 1;
    }
    else if (this->name.compare("fight") == 0) {
        this->shortDescription = "Fight with the creature you specify.";
        this->longDescription = "Begins a battle with the specified creature. Use \"fight 'number'\""
            " where 'number' is the integer specifying which creature to fight. Note creature must "
            "be in the player's move range which is shorter than the view range.\n\n";
        this->otherNames = std::vector<std::string>{ "Fight" };
        this->energyCost = 1;
    }
    else if (this->name.compare("talk") == 0) {
        this->shortDescription = "Talk to the creature you specify.";
        this->longDescription = "Talk to the specified creature. Use \"talk 'number'\" where "
            "'number' is the integer specifying which unit to talk to. Note creature must be in "
            "the player's move range which is shorter than the view range.\n\n";
        this->otherNames = std::vector<std::string>{ "Talk" };
        this->energyCost = 1;
    }
    else if (this->name.compare("pickup") == 0) {
        this->shortDescription = "Pickup and inventory the item you specify.";
        this->longDescription = "Pick up and inventory the specified item. Use \"pickup 'number'\""
            " where 'number' is the integer specifying which item to pick up. Note the item must "
            "be in the player's move range which is shorter than the view range.\n\n";
        this->otherNames = std::vector<std::string>{ "Pickup", "pickUp", "PickUp" };
        this->energyCost = 1;
    }
    else if (this->name.compare("drop") == 0) {
        this->shortDescription = "Drop the specified item from your inventory.";
        this->longDescription = "Drop the specified item from your inventory. Use \"drop 'integer'\""
            " where 'integer' is the number specifying which item to drop from the inventory menu.\n\n";
        this->otherNames = std::vector<std::string>{ "Drop" };
        this->energyCost = 0;
    }
    else if (this->name.compare("use") == 0) {
        this->shortDescription = "Use the specified item in your inventory.";
        this->longDescription = "Use the specified item in your inventory. Use \"use 'integer'\""
            " where 'integer' is the number specifying which item to use from your inventory. "
            "Note this command is only for consumable items.\n\n";
        this->otherNames = std::vector<std::string>{ "Use" };
        this->energyCost = 0;
    }
    else if (this->name.compare("equip") == 0) {
        this->shortDescription = "Equip the specified item in your inventory.";
        this->longDescription = "Equip the specified item in your inventory. Use "
            "\"equip 'integer'\" where 'integer' is the number specifying which item to equip. "
            "Note the item will automatically equip into the slot it corresponds to.\n\n";
        this->otherNames = std::vector<std::string>{ "Equip" };
        this->energyCost = 0;
    }
    else if (this->name.compare("unequip") == 0) {
        this->shortDescription = "Unequip the specified item you have equipped.";
        this->longDescription = "Unequip the specified item you have equipped. Use "
            "\"equip 'location'\" where 'location' specifies which item to unequip (i.e. 'weapon')."
            " Note the item will be returned to your inventory.\n\n";
        this->otherNames = std::vector<std::string>{ "Unequip" };
        this->energyCost = 0;
    }
    else if (this->name.compare("inventory") == 0) {
        this->shortDescription = "Displays your inventory.";
        this->longDescription = "Displays your inventory with the numbered index allowing you to "
            "specify which inventoried item you want to interact with.\n\n";
        this->otherNames = std::vector<std::string>{ "Inventory", "Inv", "inv" };
        this->energyCost = 0;
    }
    else if (this->name.compare("consume") == 0) {
        this->shortDescription = "Consume the item you specify.";
        this->longDescription = "Consume the specified item. Use \"consume 'number'\" where "
            "'number' is the integer specifying which item to consume. Note the item must "
            "be in the player's move range which is shorter than the view range.\n\n";
        this->otherNames = std::vector<std::string>{ "Consume" };
        this->energyCost = 1;
    }
    else if (this->name.compare("moveto") == 0) {
        this->shortDescription = "Moves toward the specified creature.";
        this->longDescription = "Moves the player toward the specified creature. Use \"moveto "
            "'number'\" where 'number' is the integer specifying which creature to move toward. "
            "Note the distance will be either enough to interact with the unit or the max move "
            "distance\n\n";
        this->otherNames = std::vector<std::string>{ "Moveto", "movetoward", "Movetoward" };
        this->energyCost = 2;
    }
    else if (this->name.compare("turnto") == 0) {
        this->shortDescription = "Turns toward the specified creature.";
        this->longDescription = "Turns the player toward the specified creature. Use \"turnto "
            "'number'\" where 'number' is the integer specifying which creature to turn toward.\n\n";
        this->otherNames = std::vector<std::string>{ "Turnto", "TurnTo", "turnTo", "turntoward", "Turntoward", "turnToward", "TurnToward" };
        this->energyCost = 2;
    }
    else if (this->name.compare("ignore") == 0) {
        this->shortDescription = "Toggle ignoring the specified thing.";
        this->longDescription = "Toggles ignoring / not ignoring the specified thing. Use \"ignore "
            "'thing'\" where 'thing' is 'units', 'items', or 'spatial' to ignore units, items, and "
            "spatial awareness, respectively.\n\n";
        this->otherNames = std::vector<std::string>{ "Ignore" };
    }
    else if (this->name.compare("face") == 0) {
        this->shortDescription = "Face the specified direction.";
        this->longDescription = "Face the specified direction. Use \"face 'direction'\" where "
            "'argument' is 'up', 'down', or 'flat'. Note this command only affects your phi angle.\n\n";
        this->otherNames = std::vector<std::string>{ "Face" };
        this->energyCost = 2;
    }
    else if (this->name.compare("inquire") == 0) {
        this->shortDescription = "Inquire about the creature specified.";
        this->longDescription = "Prints all known information about the creature specified. Use "
            "\"inquire 'number'\" where 'number' is the integer specifying which creature to "
            "inquire about. Note some information may need to be unlocked as the game progresses.\n\n";
        this->otherNames = std::vector<std::string>{ "Inquire", "inq", "Inq" };
    }
    else if (this->name.compare("ascend") == 0) {
        this->shortDescription = "Ascend into the next dimension.";
        this->longDescription = "You have discovered enough intersections to ascend into the next "
            "dimension. Be warned when you ascend you may not return.\n\n";
        this->otherNames = std::vector<std::string>{ "Ascend" };
    }
    else if (this->name.compare("dismantle") == 0) {
        this->shortDescription = "Dismantle an item into its materials.";
        this->longDescription = "Dismantle the specified item into its constituent materials. Use "
            "\"dismantle index\" where \"index\" is the inventory index of the item you want to dismantle.\n\n";
        this->otherNames = std::vector<std::string>{ "Dismantle" };
    }
    
    // Testmode commands
    if (this->name.compare("levelup") == 0) {
        this->shortDescription = "Level up the player.";
        this->longDescription = "Levels up the player the number of times specified or once "
            "if no argument (or an incorrect argument) given.\n\n";
        this->otherNames = std::vector<std::string>{ "Levelup", "levelUp", "LevelUp" };
    }

    if (this->shortDescription.compare("") == 0) {
        std::cout << "ERROR: command name " << this->name << " not found in command reference.\n";
    }
}

// checks input string against name and otherNames and returns whether it triggers this command
bool Command::checkNames(std::string inputName) {
    bool trigger = false;
    if (this->name.compare(inputName) == 0) {
        trigger = true;
    }
    else {
        for (size_t i = 0; i < this->otherNames.size(); i++) {
            if (this->otherNames.at(i).compare(inputName) == 0) {
                trigger = true;
                break;
            }
        }
    }
    return trigger;
}

// Return save game file for command
std::string Command::saveGame() {
    std::string fileString{};
    fileString += "*DEFINE=Command\n";
    fileString += "*STRING=name\n" + this->name + "\n*END\n";
    // Name (and player) is unique identifier so rest is unnecessary
    /*
    fileString += "*STRING=shortDescription\n" + this->shortDescription + "\n*END\n";
    fileString += "*STRING=longDescription\n" + this->longDescription + "\n*END\n";
    fileString += "energyCost=" + std::to_string(this->energyCost) + "\n";
    fileString += "*VECTOR=otherNames\n";
    for (std::string i : this->otherNames) {
        fileString += "*STRING=otherName\n" + i + "\n*END\n";
    }
    fileString += "*END\n"; // end vector
    */
    fileString += "*END\n"; // end command
    return fileString;
}