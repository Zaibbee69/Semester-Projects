#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <climits>
#include <iomanip>
#include <fstream>

using namespace std;


// Color Definitions
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"


// Function Declarations
int levenshtein_distance(string str1, string str2);
void compare_against_all_people(const map<string, string>& people, const string& target_person);
void compare_against_two_people(map<string, string> people, string &person_1, string &person_2);
void display_similarity_bar(float similarity);
void display_alignment(const string& dna1, const string& dna2);

void get_user_data_one(const map<string, string>& people, string &person_1, string &person_2);
void get_user_data_all(const map<string, string>& people, string &targeted_person);
map<string, string> loadDNAFromFile(const string& filename);
pair<string, int> find_best_match(const map<string, string>& people, const string& target_person);


int main()
{
    // Declaring required variables
    string person_1;
    string person_2;
    char choice;

    // First making a hard coded DNA of people for now
    string file_name = "dna_sequences.txt";
    map<string, string> people = loadDNAFromFile(file_name);

    // Making a prompt for user to select the type of relation they want to do
    cout << MAGENTA << "\n\n Select the type of Relation to do: \n\n" << YELLOW << "a) Against Two People \nb) One Person Relation With All\n\n";
    cin >> choice;

    if (choice == 'a')
    {
        // Getting data for comparison of two people
        get_user_data_one(people, person_1, person_2);

        // Making a check if the user selected correct names
        if (!people.count(person_1) || !people.count(person_2))
        {
            cout << RED << "\n\n +----------Please Select From the Given People Name's----------+ \n \n";
            get_user_data_one(people, person_1, person_2);
        }

        // Comparing the two selected people
        compare_against_two_people(people, person_1, person_2);
    }

    else if (choice == 'b')
    {
        // Getting data for a singular person
        get_user_data_all(people, person_1);
        
        // Making a check if the user selected correct names
        if (!people.count(person_1))
        {
            cout << RED << "\n\n +----------Please Select From the Given People Name's----------+ \n \n";
            get_user_data_all(people, person_1);
        }

        // Comparing the selected person against all people
        compare_against_all_people(people, person_1);
    }

    // If user selected some invalid option
    else
    {
        cout << RED << "\n\n Invalid option selected!\n\n"; 
    }
}

// +-------------------------Levenshtein Distance Algorithm Implementation-----------------------------+
int levenshtein_distance(string str1, string str2)
{
    // Getting the length of the strings
    const int m = str1.length();
    const int n = str2.length();

    // Creating a Dynamic Programming Table of the M X N matrix
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Initializing first row and columns (Base cases)
    for (int i = 1; i <= m; i ++) dp[i][0] = i;
    for (int j = 1; j <= n; j ++) dp[0][j] = j;

    // Now it's levenshtein _ distancing time

    // For Rows
    for (int i = 1; i <= m; i ++)
    {
        // For columns
        for (int j = 1; j <= n; j ++)
        {
            // Base Case (Match Found)
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];

            // Match Not Found
            else
            {
                dp[i][j] = 1 + min(
                    dp[i - 1][j],    // delete
                    min(dp[i][j - 1], dp[i - 1][j - 1]) // insert and substitute
                );
            }
        }   
    }

    // Returning the distance
    return dp[m][n]; 
}


map<string, string> loadDNAFromFile(const string& filename) 
{
    map<string, string> dnaData;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return dnaData;
    }

    string name, sequence;
    while (file >> name >> sequence) {
        dnaData[name] = sequence;
    }

    file.close();
    return dnaData;
}

void get_user_data_one(const map<string, string>& people, string &person_1, string &person_2)
{
    cout << CYAN << "\nSelect Between The People To Relate: \n\n";
    for (auto person : people)
    {
        cout << YELLOW << person.first << MAGENTA << setw(4) << "|" << setw(4) << " " << RESET;
    }
    cout << endl << endl;
    cin >> person_1 >> person_2;
}

void get_user_data_all(const map<string, string>& people, string &targeted_person)
{
    cout << CYAN << "\nSelect a Person Below to Relate: \n\n";
    for (auto person : people)
    {
        cout << YELLOW << person.first << MAGENTA << setw(4) << "|" << setw(4) << " " << RESET;
    }
    cout << endl << endl;
    cin >> targeted_person;
}

// Function to find the best possible match for a given targeted person in map
pair<string, int> find_best_match(const map<string, string>& people, const string& target_person)
{
    string best_match;
    int min_distance = INT_MAX;

    for (auto person : people)
    {
        // Skip the selected person
        if (person.first == target_person)
            continue;

        // Calculate Levenshtein Distance
        int distance = levenshtein_distance(person.second, people.at(target_person));

        // Update the best match if a smaller distance is found
        if (distance < min_distance)
        {
            min_distance = distance;
            best_match = person.first;
        }
    }

    return {best_match, min_distance};
}

void compare_against_two_people(map<string, string> people, string &person_1, string &person_2)
{
    // Finding distance and similarity
    int distance = levenshtein_distance(people[person_1], people[person_2]);
    double similarity = 100.0f * (1 - (double)distance / max(people[person_1].length(), people[person_2].length()));

    cout << endl << MAGENTA << person_1 << YELLOW << " relates with " << CYAN << person_2 << fixed << setprecision(2) << YELLOW << " with a Similarity: " << GREEN << similarity << "%" << YELLOW << " and a Distance: " << GREEN << distance << RESET << endl << endl;

    // Displaying DNA alignment and similarity in CLI
    display_alignment(people[person_1], people[person_2]);
    display_similarity_bar(similarity);
}

// Function after getting the match and displaying it
void compare_against_all_people(const map<string, string>& people, const string& target_person)
{
    // Getting result and similarity
    auto result = find_best_match(people, target_person);
    cout << YELLOW << "\nBest match is: " << CYAN << result.first << YELLOW << " with" << MAGENTA << " Distance: " << GREEN << result.second << RESET << endl;

    float similarity = 100.0f * (1 - (float)result.second / people.at(target_person).size());
    cout << fixed << setprecision(2);
    cout << YELLOW << "Similarity Score: " << GREEN << similarity << "%" << endl << RESET;

    // Displaying DNA alignment and similarity in CLI
    display_alignment(people.at(result.first), people.at(target_person));
    display_similarity_bar(similarity);
}

void display_alignment(const string& dna1, const string& dna2)
{
    int len = min(dna1.size(), dna2.size());

    cout << "\n\n\033[1;36m+---------------------------- DNA Alignment ----------------------------+\033[0m\n\n";

    cout << "\033[1;34mPerson 1: \033[0m";
    for (int i = 0; i < len; ++i)
    {
        if (dna1[i] == dna2[i])
            cout << "\033[1;32m" << dna1[i] << "\033[0m";  // Green for match
        else
            cout << "\033[1;31m" << dna1[i] << "\033[0m";  // Red for mismatch
    }

    cout << "\n          ";
    for (int i = 0; i < len; ++i)
    {
        if (dna1[i] == dna2[i])
            cout << "\033[1;32m|\033[0m";  // Green bar for match
        else
            cout << " ";  // No bar for mismatch
    }

    cout << "\n\033[1;34mPerson 2: \033[0m";
    for (int i = 0; i < len; ++i)
    {
        if (dna1[i] == dna2[i])
            cout << "\033[1;32m" << dna2[i] << "\033[0m";  // Green for match
        else
            cout << "\033[1;31m" << dna2[i] << "\033[0m";  // Red for mismatch
    }
    cout << "\n\n";
}


void display_similarity_bar(float similarity) 
{
    int width = 50;
    int filled = static_cast<int>((similarity / 100.0) * width);

    // I will be choosing a color based upon user similarity
    string color;
    if (similarity >= 75) color = GREEN;        
    else if (similarity >= 50) color = YELLOW;  
    else if (similarity >= 25) color = MAGENTA;   
    else color = RED;                         

    cout << CYAN << "Similarity:" << RESET << " [";
    cout << color; 
    for (int i = 0; i < filled; ++i) cout << '#';
    cout << RESET;
    for (int i = filled; i < width; ++i) cout << '-';
    cout << "] ";

    cout << fixed << setprecision(2);
    cout << similarity << "%\n\n";
}