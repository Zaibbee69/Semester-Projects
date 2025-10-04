// Declaring the required header files
#include<iostream>
#include<cstdlib>

#include"ticTacToe.h"

using namespace std;


// Declaring all the required global variables
char space[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };
int row;
int column;
char token = 'x'; // Initialize token to 'x' for player 1
string n1 = "";    //for player1 name
string n2 = "";    //for player2 name
bool tie = false;


// Function declarations
void starting_credits_TIC();
void ending_credits_TIC();
void functionOne();
void functionTwo();
bool functionThree();
void name_asker();
void rules_setter();


//main body

void playTicTacToe()
{
    //EHEHHEHEHEHEH

    // Calling function to display staring credits
    starting_credits_TIC();

    // Calling function to ask for names
    name_asker();

    //The first person will have 'x'
    //The second person will have '0'
    //COMMON SENSE HAI BHAII

    // Function for displaying which user will play first or not
    rules_setter();

    //Yahn saray functions ko call karay gaii

    while (!functionThree()) 
    {
        functionOne();
        functionTwo();
    }

    if (token == 'x' && !tie)
    {
        cout << endl;
        cout << "      "<< n2 << " WINS!!!" << endl;
        cout << "      PLAYED WELL!"<<endl;
        cout << "      <3"<<endl;
        cout << "      "<< n1 << " MOYE MOYE";
        cout << endl;
    }
    else if (token == '0' && !tie) 
    {
        cout << endl;
        cout << "         " << n1 << " WINS!!!" << endl; 
        cout << "        PLAYED WELL!"<<endl;
        cout << "        <3"<<endl;
        cout << "        "<< n2 << " MOYE MOYE";
        cout << endl;
    }
    else
    {
        cout << endl;
        cout << "      It's a tie!" << endl;
    }

    ending_credits_TIC();
}


// +------------------------------------------- FUNCTIONS ---------------------------------------------------------+
void starting_credits_TIC()
{
    cout << endl << endl;

    cout << " TTTTT IIIII   CCC    TTTTT   AAA   CCC    TTTTT   OOO   EEEEEE       X     X      OOO   " << endl;
    cout << "   T     I    C   C     T    A   A C   C     T    O   O  E             X  X       O   O  " << endl;
    cout << "   T     I    C         T    AAAAA C         T    O   O  EEEEEE          X        O   O  " << endl;
    cout << "   T     I    C   C     T    A   A C   C     T    O   O  E             X    X     O   O  " << endl;
    cout << "   T   IIIII   CCC      T    A   A  CCC      T     000   EEEEEE       X      X     OOO   " << endl;

    cout << endl;
    cout << endl;
    cout << endl;

    cout << endl << endl;
	cout << "+-----------------------WELCOME TO  TIC TAC TOE !--------------------------+" << endl << endl << endl;

	cout << "\t\t\t🌸 Made By Aniqa Jamil 🌸  " << endl << endl;
}

// Ending credits
void ending_credits_TIC()
{
    cout << endl;
    cout << endl;
    cout << "With Love to MAM MARIYAM" << endl;
    cout << endl;
    cout << endl;
    cout << "BY FREASH PARATHIS" << endl;
}


//function one for the stucture
void functionOne()
{

    // Structure of tic tac toe

    cout << "        |       | \n";
    cout << "     " << space[0][0] << "  |   " << space[0][1] << "   |  " << space[0][2] << "  \n";
    cout << "  _____||____  \n";
    cout << "        |       |  \n";
    cout << "    " << space[1][0] << "   |   " << space[1][1] << "   |  " << space[1][2] << "  \n";
    cout << "        |       |  \n";
    cout << "  _____||____  \n";
    cout << "    " << space[2][0] << "   |   " << space[2][1] << "   |  " << space[2][2] << "  \n";
    cout << "        |       |  \n";
}

//function two for accessing each place 

void functionTwo()
{
    int digit;

    // For player One
    if (token == 'x') 
    {
        cout << endl;
        cout << n1 << " please enter:" << endl;
        cout << " ";
        cin >> digit;
    }

    // For player Two
    else 
    {
        cout << endl;
        cout << n2 << " please enter:" << endl;
        cout << " ";
        cin >> digit;
    }

    if (digit == 1) 
    {
        row = 0;
        column = 0;
    }
    else if (digit == 2)
    {
        row = 0;
        column = 1;
    }
    else if (digit == 3)
    {
        row = 0;
        column = 2;
    }
    else if (digit == 4)
    {
        row = 1;
        column = 0;
    }
    else if (digit == 5)
    {
        row = 1;
        column = 1;
    }
    else if (digit == 6)
    {
        row = 1;
        column = 2;
    }
    else if (digit == 7)
    {
        row = 2;
        column = 0;
    }
    else if (digit == 8) 
    {
        row = 2;
        column = 1;
    }
    else if (digit == 9) 
    {
        row = 2;
        column = 2;
    }
    else 
    {
        cout << "Invalid !!!" << endl;
        return;       // Added return to exit the function after printing error message
    }

    if (space[row][column] != 'x' && space[row][column] != '0')
    {
        space[row][column] = token;
        if (token == 'x')
            token = '0';
        else
            token = 'x';
    }
    else
    {
        cout << "Invalid move! Please try again." << endl;
        functionTwo();   // DOBARA FUNCTION RECALL KARAY AGR GHALAT HO
    }
}


//Third function for DRAW

bool functionThree()
{
    for (int i = 0; i < 3; i++) 
    {
        if (space[i][0] == space[i][1] && space[i][0] == space[i][2] || space[0][i] == space[1][i] && space[0][i] == space[2][i])
            return true;
    }
    if (space[0][0] == space[1][1] && space[1][1] == space[2][2] || space[0][2] == space[1][1] && space[1][1] == space[2][0]) 
    {
        return true;
    }
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++)
        {
            if (space[i][j] != 'x' && space[i][j] != '0') 
            {
                return false;
            }
        }
    }
    tie = true;
    return true;
}

void name_asker()
{
    
    cout << "Enter the name of the first player: \n";
    cin >> n1;
    cout << "Enter the name of second player : \n";
    cin >> n2;
    cout << endl;

}

void rules_setter()
{
    cout << n1 << " is player1 so he/she will play first \n";
    cout << n2 << " is player2 so he/she will play second \n ";
    cout << endl;
    cout << endl;
}
