#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <memory>
#include <algorithm>
#include <random>
#include <unordered_map>
#include "Game.h"
#include "TextDisplay.h"
#include "Err.h"

using namespace std;

const int maxOfEachAbility = 2;
const int numPlayers = 2; // to quickly change player counts

string randomLinkGenerator();
void areAbilitiesValid(const string &abilities, const string &validAbilities);
string retrieveLink(fstream &file);


int main(int argc, const char* argv[]){
    string validAblities = "LFDSP";
    vector<string> playerAbilities(numPlayers, "LFDSP"); // index + 1 represents player number
    vector<string> playerLinkOrders(numPlayers); // same here
    for (int i = 0; i < numPlayers; ++i) {
        playerLinkOrders[i] = randomLinkGenerator();
    }
    bool graphicsEnabled = false;
    try { 
        for (int i = 1; i < argc; ++i) {
            string arg = argv[i];
            if (arg == "-ability1") {
                ++i;
                if (i >= argc) throw out_of_range(Err::insufficientArgs);
                playerAbilities[0] = string(argv[i]);
                areAbilitiesValid(playerAbilities[0], validAblities);
            } else if (arg == "-ability2") {
                ++i;
                if (i >= argc) throw out_of_range(Err::insufficientArgs);
                playerAbilities[1] = string(argv[i]);
                areAbilitiesValid(playerAbilities[1], validAblities);                
            } else if (arg == "-link1") {
                ++i;
                if (i >= argc) throw out_of_range(Err::insufficientArgs);
                ifstream file{argv[i]};
                playerLinkOrders[0] = retrieveLink(file);
            } else if (arg == "-link2") {
                ++i;
                if (i >= argc) throw out_of_range(Err::insufficientArgs);
                ifstream file{argv[i]};
                playerLinkOrders[1] = retrieveLink(file);
            } else if (arg == "graphics") {
                graphicsEnabled = true;
            } else {
                throw invalid_argument(Err::invalidCommandLineArg + ": " + string(argv[i]));
            }
        }
    } catch(const exception &e) {
        cerr << e.what() << endl;
        return 1;
    }
}

string randomLinkGenerator() {
    vector<string> links = {
        "D1", "D2", "D3", "D4",
        "V1", "V2", "V3", "V4"
    };
    random_device rd;  
    mt19937 rng(rd()); 
    shuffle(links.begin(), links.end(), rng);
    string linkOrder;
    for (const auto& link : links) {
        linkOrder += link;
    }
    return linkOrder;
}

void areAbilitiesValid(const string &s, const string &validAbilities) {
    unordered_map<char, int> mp;
    for (int i = 0; i < validAbilities.size(); ++i) {
        mp[validAbilities[i]] = 0;
    }
    for (int i = 0; i < s.size(); ++i) {
        char c = toupper(s[i]);
        if (mp.find(c) != mp.end() && mp[c] < maxOfEachAbility) {
            ++mp[c];
        } else {
            throw invalid_argument(Err::invalidAbilities);
        }
    }
}

string retrieveLink(ifstream &file) {
    const int requiredCount = 1;
    vector<string> links = {
        "D1", "D2", "D3", "D4",
        "V1", "V2", "V3", "V4"
    };
    unordered_map<string, int> mp;
    for (int i = 0; i < links.size(); ++i) {
        mp[links[i]] = 0;
    }
    string s, linkOrder;
    while (file >> s) {
        transform(s.begin(), s.end(), s.begin(), [] (unsigned char c) {
            return toupper(c);
        });
        if (mp.find(s) != mp.end()) {
            ++mp[s];
            linkOrder += s;
        } else {
            throw invalid_argument(Err::invalidLinks);
        }
    }
    for (const auto &elem : mp) {
        if (elem.second != requiredCount) {
            throw invalid_argument(Err::invalidLinks);
        }
    }
    return linkOrder;
}
