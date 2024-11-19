#include "err.h"

string Err::insufficientArgs = "Insufficent arguments provided";
string Err::invalidArg = "Invalid arguments provided";
string Err::invalidCommandLineArg = 
    "Invalid command-line arguments provided\nArguments must be of one of the forms: [-ability1 <abilities>] [-ability2 <abilities>] [-link1 <placementFile>] [-link2 <placementFile] [graphics]. Invalid argument is: ";
string Err::invalidRuntimeCommand = 
"Invalid rumtime command provided\n Commands must be of one of the forms: [move <linkID> <dir>] [abilities] [ability <N>] [sequence <sequenceFile>]";
string Err::invalidAbilities = "Abilities can only be of the form [L] [F] [D] [S] [P], and you may have a total of 5 and a maximum of 2 of each ability";
string Err::invalidAbility = "Abilities can only be of the form [L] [F] [D] [S] [P]";
string Err::invalidAbilityIndex = "Expected an ability index from [1, 5]";
string Err::invalidLinks = "Links may only be of the form [D1] [D2] [D3] [D4] [V1] [V2] [V3] [V4], and there must be exactly one of each form";
string Err::invalidFile = "File not found: ";
string Err::abilityUsedThisTurn = "You may only use one ability per turn. You must move a link before you use any more abilites.";
string Err::reenterCommand = "Re-enter your command";