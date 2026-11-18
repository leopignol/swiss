#include "main.hpp"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    size_t longestName = 0;
    // Initialize game with contestants
    vector<Contestant> contestants;
    for (uint8_t i = 0; i < 8; ++i){
        string name = input(true);
        longestName = max(name.size(), longestName);
        contestants.push_back(Contestant{name});
    }

    uint8_t games = 0;

    vector<pair<Contestant &, Contestant &>> versuses;
    for (size_t i = 0; i < contestants.size(); i += 2)
        versuses.push_back(
            pair<Contestant &, Contestant &>(contestants[i], contestants[i + 1])
        );

    while (games < 5) {
        /*for (auto versus : versuses){
            cout
                << setw(longestName) << versus.first.name  << " (" << (unsigned)versus.first.victories  << ") vs "
                << setw(longestName) << versus.second.name << " (" << (unsigned)versus.second.victories << ")" << endl;
        }*/

        for (auto versus : versuses){
            Contestant &contestant = versus.first;
            Contestant &opponent = versus.second;

            /*        -------- HEADS OR TAILS --------        */

            // Contestant guess, opponent takes opposite
            string inputGuess = input();
            HT guess;
            if      (inputGuess == "heads") guess = HT::HEADS;
            else if (inputGuess == "tails") guess = HT::TAILS;
            else {
                cerr
                    << "D Expected \"heads\" or \"tails\", got \""
                    << inputGuess << "\"." << endl;
                exit(1);
            }

            string inputResult = input();
            HT result;
            if      (inputResult == "heads") result = HT::HEADS;
            else if (inputResult == "tails") result = HT::TAILS;
            else {
                cerr
                    << "Expected \"heads\" or \"tails\", got \""
                    << inputResult << "\"." << endl;
                exit(1);
            }

            bool victory = (guess == result);

            // Update scores
            if (victory)
                ++contestant.victories;
            else
                ++opponent.victories;

            /*        -------- ROCK PAPER SCISSORS --------        */

            RPS guessC = RPS::ROCK;
            RPS guessO = RPS::ROCK;

            while (guessC == guessO) {
                string inputGuessC = input();
                string inputGuessO = input();

                // Contestant move
                if      (inputGuessC == "rock")     guessC = RPS::ROCK;
                else if (inputGuessC == "paper")    guessC = RPS::PAPER;
                else if (inputGuessC == "scissors") guessC = RPS::SCISSORS;
                else {
                    cerr
                        << "Expected \"rock\", \"paper\" or \"scissors\", got \""
                        << inputGuessC << "\"." << endl;
                    exit(1);
                }

                // Opponent move
                if      (inputGuessO == "rock")     guessO = RPS::ROCK;
                else if (inputGuessO == "paper")    guessO = RPS::PAPER;
                else if (inputGuessO == "scissors") guessO = RPS::SCISSORS;
                else {
                    cerr
                        << "Expected \"rock\", \"paper\" or \"scissors\", got \""
                        << inputGuessC << "\"." << endl;
                    exit(1);
                }
            }

            victory = false;
            if      (guessC == RPS::ROCK     && guessO == RPS::SCISSORS) victory = true;
            else if (guessC == RPS::PAPER    && guessO == RPS::ROCK    ) victory = true;
            else if (guessC == RPS::SCISSORS && guessO == RPS::PAPER   ) victory = true;

            // Update scores
            if (victory)
                ++contestant.victories;
            else
                ++opponent.victories;

            /*        -------- HEADS OR TAILS (RIGGED) --------        */

            // Opponent guess, contestant takes opposite
            inputGuess = input();
            if (inputGuess == "heads")
                guess = HT::HEADS;
            else if (inputGuess == "tails")
                guess = HT::TAILS;
            else {
                cerr << "R Expected \"heads\" or \"tails\", got \"" << inputGuess << "\"." << endl;
                exit(1);
            }

            inputResult = input();
            if (inputResult == "heads")
                result = HT::HEADS;
            else if (inputResult == "tails")
                result = HT::TAILS;
            else {
                cerr << "Expected \"heads\" or \"tails\", got \"" << inputResult << "\"." << endl;
                exit(1);
            }

            victory = (guess == result);

            // Update scores
            if (victory)
                ++opponent.victories;
            else
                ++contestant.victories;
        }

        versuses.clear();
        sort(contestants.begin(), contestants.end(), sortContestants);
        for (size_t i = 0; i < contestants.size(); i += 2)
            versuses.push_back(
                pair<Contestant &, Contestant &>(contestants[i], contestants[i + 1])
            );

        ++games;
    }

    // Sort contestants based on score
    sort(contestants.begin(), contestants.end(), sortContestants);

    // Display results
    size_t placement = 0;
    for (const Contestant &contestant : contestants)
        cout << setw(longestName) << contestant.name
             << ": " << ++placement << endl;

    return 0;
}
