// Including the required header files
#include<iostream>
#include<cstdlib>
#include<ctime>

#include"numberGuessing.h"
using namespace std;


// Function Declaration
void player_hinter(int playerchoice, int secretnumber);
void winner_displayer(int playerchoice);
void loser_displayer(int secretnumber);

// Haider's Wonderful Game On NUMBER GUESSING
void playNumberGuessing()
{ 
    // +--------------------------------FIRST PRINTING THE MENU FOR THE GAME----------------------------------+

    cout << endl << endl;
	cout << "+-----------------------WELCOME TO NUMBER GUESSING GAME !--------------------------+" << endl << endl << endl;

	cout << "\t\t\t😎 Made By Zulqarnain Haider 😎 " << endl << endl;
	cout << "You have to guess the number between 1 & 100.You have multiple choices based on level." << endl << "GOOD LUCK";
	cout << endl;

    // Here we will be looping through game until player wants to exit
	while (true)
	{
		cout << "\tENTER DIFFICULTY LEVEL!" << endl;

        // Asking user what kind of difficulty level they want to play in
		cout << "1) For easy!" << endl << "2) For medium!" << endl << "3) For hard!" << endl << "0) For exit game!" << endl;
		int difficultychoice;
		cout << "Enter a number! :  ";
		cin >> difficultychoice;


		// rand is the function use for random number guess.it is use by #include<cstdlib> headerfile.
		// syntax is int anyword= offset (rand() % range) where offset is the starting num and range is the last num.
		// srand is the function used for change the random number.
		// syntax srand(time(0)); time is also a function which is used to change the rand num with time.
		// The function time is use by this #include<ctime> headerfile and srand and rand work with same headerfile.


        // This function will basically make a random see depending upon the current users time
		srand(time(0));

        // Now we will be using a formula to make a number that exists between 1 and 100
		int secretnumber = 1 + (rand() % 100);
		int playerchoice;


        // +---------------------------------Easy Difficulty-----------------------------------------------+
		if (difficultychoice == 1)
		{
            cout << endl;
			cout << "You have 10 attempts to find the secret number between 1 & 100:" << endl;
			int choice_left = 10; // Number of tries the user has
			for (int i = 1; i <= 10; i++)
			{
                                    
                // Asking the user for his number
				cout << "Enter the number : ";
				cin >> playerchoice;

                // If user guessed correctly
				if (playerchoice == secretnumber)
				{
                    winner_displayer(playerchoice);
                    break;
				}

                // If user guessed wrong
				else
					cout << endl << "NO way.😐 it's a wrong number."<<endl;

                // Now we will be telling the user hints on where number is
                player_hinter(playerchoice, secretnumber);
                
                // Decrementing the choicer
				choice_left--;

				cout << "You have " << choice_left << " more turns left!🧡" << endl;

                // If user fails to put correct digit in specific tries
				if (choice_left == 0)
				{
                    loser_displayer(secretnumber);
				}
			}
		}

        // +-------------------------------------Medium Difficulty---------------------------------+
		else if (difficultychoice == 2)
		{
			{
				cout << "You have 7 attempts to find the secret number between 1 & 100:" << endl;
				int choice_left = 7;
				for (int i = 1; i <= 7; i++)
				{
					cout << "Enter the number : ";
					cin >> playerchoice;
					if (playerchoice == secretnumber)
					{
                        winner_displayer(playerchoice);
                        break;
					}
					else
						cout << "NO way.😐 it's a wrong number." << endl;

                    // Player Hinter Function
					player_hinter(playerchoice, secretnumber);

					choice_left--;
					cout << "You have " << choice_left << " more turns left!🧡";
					if (choice_left == 0)
					{
						loser_displayer(secretnumber);
					}
				}
			}
		}

        // +------------------------------------------Hard Difficulty--------------------------------+
		else if (difficultychoice == 3)
		{
			{
				cout << "You have 5 attempts to find the secret number between 1 & 100:" << endl;
				int choice_left = 5;
				for (int i = 1; i <= 5; i++)
				{
					cout << "Enter the number : ";
					cin >> playerchoice;
					if (playerchoice == secretnumber)
					{
                        winner_displayer(playerchoice);
                        break;
					}
					else
						cout << "NO way.😐 it's a wrong number." << endl;

                    // Player Hinter function
                    player_hinter(playerchoice, secretnumber);

					choice_left--;
					cout << "You have " << choice_left << " more turns left!🧡";
					if (choice_left == 0)
					{  
                        loser_displayer(secretnumber);
					}
				}
			}
		}
		else if (difficultychoice == 0)
		{
		exit(0);
		}
		else
		{
		cout << "You entered wrong number🙆‍.Enter number form (1-3) to play game 😉.";
		}
	}

	cout << endl;
    cout << endl;
    cout << "With Love to MAM MARIYAM" << endl;
    cout << endl;
    cout << endl;
    cout << "BY FREASH PARATHIS" << endl;
}


// Player Hinter Function
void player_hinter(int playerchoice, int secretnumber)
{
    if (playerchoice > secretnumber)
    {
        cout << "The secret number is smaller then the " << playerchoice << endl;
    }
    else
    {
        cout << "The secret number is greater then the " << playerchoice << endl;
    }
}

// Loser Function
void loser_displayer(int secretnumber)
{
    cout << endl << endl;
    cout << "OPPS!Sorry you are loser.😢"<<endl;
    cout << "And the secret number is " << secretnumber  << "🙂🙂." << endl;
    cout << "Play again hopefully you can be winer 💕💕." << endl;
}

// Winner function
void winner_displayer(int playerchoice)
{
    cout << endl;
    cout << "Well played! You have won the game.💕";
    cout << endl << playerchoice << " is the secret number." << endl;
    cout << "\t THANKS SO MUCH TO PLAYING THIS GAME.❤" << endl;
    cout << "Try to play again with us.👀" << endl;
}