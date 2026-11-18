#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#ifndef __SWISS_HPP
#define __SWISS_HPP

enum HT { HEADS, TAILS };

enum RPS { ROCK, PAPER, SCISSORS };

struct Contestant {
  std::string name;
  uint8_t victories = 0;
};

std::string input(bool keepCase = false) {
  std::string val;
  while (val.empty() || val[0] == '#')
    getline(std::cin, val);
  if (!keepCase)
    for (char &c : val)
      c = tolower(c);
  return val;
}

bool sortContestants(const Contestant &left, const Contestant &right) {
  return left.victories > right.victories;
}

#endif
