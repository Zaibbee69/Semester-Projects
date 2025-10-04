#include <iostream>


/*cd /mnt/c/Coding_Files/PF_Games_Project/
g++ menu.cpp hang_man_HK-NM.cpp tic_tac_toe_AJ.cpp number_guessing_ZH.cpp rock_scissor_RN.cpp pac_man_JZ-AJ.cpp  -o menu*/ 
#include "hangman.h"
#include "ticTacToe.h"
#include "numberGuessing.h"
#include "rockPaperScissors.h"
#include "pacMan.h"



using namespace std;

void showMenu() 
{
    cout << endl << endl;
    cout << "+----------------------------- WELCOME TO OUR FUN LITTLE ARCADE -------------------------------------+" << endl << endl;
    cout << "Select a game to play:\n"; 
    cout << "1. Hang Man\n";
    cout << "2. Tic Tac Toe\n"; 
    cout << "3. Numbers Guessing\n";
    cout << "4. Rock Paper Scissors\n";
    cout << "5. Pac Man\n";
    cout << "0. Exit\n";
}

int main()
{
    int choice;

    while (true) 
    {
        showMenu();
        cin >> choice;

        switch (choice) 
        {
            case 1:
                playHangMan();
                break;
            case 2:
                playTicTacToe();
                break;
            case 3:
                playNumberGuessing();
                break;
            case 4:
                playRockPaperScissors();
                break;
            case 5:
                playPacMan();
                break;
            case 0:
                cout << "Exiting... TATTA BUBYEEEEEE" << endl;
                return 0;
            default:
                cout << "Invalid choice, please select again." << endl;
        }
    }
    return 0;
}
