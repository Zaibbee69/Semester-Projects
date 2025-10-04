#include<iostream>// for input and output operations
#include<vector>// for dynamic arrays
#include<string>// for text manupulation
#include<ctime>// for random seed
#include<cstdlib>// for rand()
#include<algorithm>// for transform

#include "hangman.h"

using namespace std;

// Function declarations
void drawhangman(int tries);
void finallizer(string secretword, string displayword);
void starting_credits_HANG();
void ending_credits_HANG();

void playHangMan()
{
    // Displaying the starting credits
    starting_credits_HANG();

    // List of words for the game
    vector<string> words = { "garamanday", "biryani", "pakoray", "koftay", "kachori", "golgappay", "moyemoye", "badobaddi" };

    // Ensures that each time you run the program, you get a different sequence of random numbers
    srand(static_cast<unsigned>(time(0)));
    
    // Selects a random word from a collection of words 
    string secret_word = words[rand() % words.size()];

    // Words to be displayed,
    string display_word(secret_word.length(), '-');

    vector<char> incorrect_guesses;
    int max_tries = 6;

    while (incorrect_guesses.size() < max_tries && display_word != secret_word) 
    {
        // Draw the hangman based on incorrect guesses
        drawhangman(incorrect_guesses.size());

        cout << "Current word= " << display_word << endl;
        cout << "Incorrect guesses= ";
        for (const auto& c : incorrect_guesses) 
        {
            cout << c << ' ';
        }
        cout << endl;

        // Get the player's guess
        cout << "Enter a letter= ";
        char guess;
        cin >> guess;

        // to convert uppercase letters into lowercase
        guess = tolower(guess);

        // Check if the guess is in the word
        if (count(secret_word.begin(), secret_word.end(), guess))
        {
            for (size_t i = 0; i < secret_word.size(); i++) 
            {
                // Correct guess, update display_word
                if (secret_word[i] == guess)
                {
                    display_word[i] = guess;
                }
            }
        }
        else
        {
            // Incorrect guess, add to incorrect_guesses if not already there
            if (find(incorrect_guesses.begin(), incorrect_guesses.end(), guess) == incorrect_guesses.end()) 
            {
                incorrect_guesses.push_back(guess);
            }
        }
    }
    // Game outcome
    drawhangman(incorrect_guesses.size());

    // Final hangman drawing
    finallizer(display_word, secret_word);

    // Ending credits
    ending_credits_HANG();
}


// +--------------------------------- FUNCTIONS ------------------------------------------+ 

// Makes decision based on wether user won or not
void finallizer(string display_word, string secret_word)
{
    if (display_word == secret_word) 
    {
        cout << "Mubarakan On The Right Guess. " << secret_word << endl;
    }
    else 
    {
        cout << "OOPS Wrong Guess."<<endl;
        cout<<"(Sorry to say but MOYE MOYE)" << endl << "The word was : " << secret_word << endl;
    }
}

// Function to draw the hangman based on the number of incorrect guesses
void drawhangman(int tries)
{
    cout << "  ----" << endl;
    cout << "  |  |" << endl;
    cout << "  |  " << (tries > 0 ? "O" : "") << endl;
    cout << "  | " << (tries > 1 ? "/" : "") << (tries > 2 ? "|" : "") << (tries > 3 ? "\\" : "") << endl;
    cout << "  | " << (tries > 4 ? "/" : "") << (tries > 5 ? " \\" : "") << endl;
    cout << "  | " << endl;
    cout << "_____ " << endl;
}

// Starting credits
void starting_credits_HANG()
{
    cout << endl << endl;
    cout << "+------------------------Welcome to Hang Man-------------------------+" << endl << endl;
    cout << "\t\t💟 Made By Hamna Khan && Nimra Nisab 💟" << endl << endl;
}

// Ending credits
void ending_credits_HANG()
{
    cout << endl;
    cout << endl;
    cout << "With Love to MAM MARIYAM" << endl;
    cout << endl;
    cout << endl;
    cout << "BY FREASH PARATHIS" << endl;
}
