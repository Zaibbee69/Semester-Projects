#include <iostream>
#include <cstdlib>
#include <ctime>

#include "rockPaperScissors.h"

#define ROCK 1      
#define PAPER 2
#define SCISSORS 3

using namespace std;

void playRockPaperScissors() {
    srand((unsigned int)time(NULL));

    int player_throw = 0;
    int roonia_throw = 0;
    bool draw = false;

    do {
        cout << endl << endl;
        cout << "+------------------------Welcome to ROCK PAPER SCISSORS-------------------------+" << endl << endl;
        cout << "\t\t\t    🧡 Made By Rania Nisar 🧡 " << endl << endl;

        cout << "Select your throw." << endl;
        cout << "1) Rock" << endl;
        cout << "2) Paper" << endl;
        cout << "3) Scissors" << endl;
        cout << "Enter the number ( 1 to 3 ) to select the throw:" << endl;
        cout << "Selection: " << endl;
        cin >> player_throw;

        cout << endl;

        roonia_throw = (rand() % 3) + 1;

        if (roonia_throw == ROCK) {
            cout << "AI throws ROCK." << endl;
        } else if (roonia_throw == PAPER) {
            cout << "AI throws PAPER." << endl;
        } else if (roonia_throw == SCISSORS) {
            cout << "AI throws SCISSORS." << endl;
        }

        draw = false;

        if (player_throw == roonia_throw) {
            draw = true;
            cout << "Draw! Play again!" << endl;
        } else if (player_throw == ROCK && roonia_throw == SCISSORS) {
            cout << "ROCK beats SCISSORS! YOU WIN." << endl;
        } else if (player_throw == ROCK && roonia_throw == PAPER) {
            cout << "PAPER beats ROCK! YOU LOSE." << endl;
        } else if (player_throw == PAPER && roonia_throw == ROCK) {
            cout << "PAPER beats ROCK! YOU WIN." << endl;
        } else if (player_throw == PAPER && roonia_throw == SCISSORS) {
            cout << "SCISSORS beats PAPER! YOU LOSE." << endl;
        } else if (player_throw == SCISSORS && roonia_throw == PAPER) {
            cout << "SCISSORS beats PAPER! YOU WIN." << endl;
        } else if (player_throw == SCISSORS && roonia_throw == ROCK) {
            cout << "ROCK beats SCISSORS! YOU LOSE." << endl;
        }

        cout << endl;

    } while (draw);

    cout << endl;
    cout << endl;
    cout << "With Love to MAM MARIYAM" << endl;
    cout << endl;
    cout << endl;
    cout << "BY FREASH PARATHIS" << endl;
}
