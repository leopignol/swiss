#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#pragma once

using namespace std;

enum HT {
    HEADS, TAILS
};

enum RPS {
    ROCK, PAPER, SCISSORS
};

struct Contestant {
    string name;
    uint8_t victories = 0;

    vector<Contestant> opponents(const vector<Contestant> &contestants){
        vector<Contestant> _contestants;
        copy_if(
            contestants.begin(),
            contestants.end(),
            back_inserter(_contestants),
            [this](const Contestant &c){
                return c.name != this->name;
            }
            );
        return _contestants;
    }
};

string input(bool keepCase = false);
