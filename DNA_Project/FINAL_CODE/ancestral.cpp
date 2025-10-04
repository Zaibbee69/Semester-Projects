#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

// Color Definitions for better visualization
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"

// Function declarations
int levenshtein_distance(const string& str1, const string& str2);
void load_ancestral_data(const string& filename, map<string, string>& ancestors);
void find_ancestral_matches(const string& dna, const map<string, string>& ancestors);
void display_alignment(const string& dna, const string& ancestral_dna);
void display_similarity_bar(float similarity);
void display_results(const vector<pair<string, float>>& matches);

int main() {
    map<string, string> ancestors;
    string dna_sequence;
    string filename;

    cout << CYAN << "\nAncestral Gene Detection System\n";
    cout << "=================================\n\n" << RESET;

    // Get ancestral data file name
    cout << YELLOW << "Enter the ancestral data file name (e.g., ancestors.txt): " << RESET;
    cin >> filename;

    // Load ancestral data
    load_ancestral_data(filename, ancestors);
    if (ancestors.empty()) {
        cout << RED << "No ancestral data loaded. Exiting program.\n" << RESET;
        return 1;
    }

    // Get DNA sequence to analyze
    cout << YELLOW << "\nEnter your DNA sequence to analyze (A,T,C,G only): " << RESET;
    cin >> dna_sequence;

    // Convert to uppercase
    transform(dna_sequence.begin(), dna_sequence.end(), dna_sequence.begin(), ::toupper);

    // Validate DNA input
    for (char c : dna_sequence) {
        if (c != 'A' && c != 'T' && c != 'C' && c != 'G') {
            cout << RED << "Invalid DNA sequence. Only A, T, C, G characters are allowed.\n" << RESET;
            return 1;
        }
    }

    // Find and display ancestral matches
    find_ancestral_matches(dna_sequence, ancestors);

    return 0;
}

// Levenshtein distance calculation
int levenshtein_distance(const string& str1, const string& str2) {
    const int m = str1.length();
    const int n = str2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) dp[i][0] = i;
    for (int j = 1; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({
                    dp[i - 1][j],    // deletion
                    dp[i][j - 1],     // insertion
                    dp[i - 1][j - 1]  // substitution
                });
            }
        }
    }

    return dp[m][n];
}

// Load ancestral data from file
void load_ancestral_data(const string& filename, map<string, string>& ancestors) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << RED << "Error: Could not open file " << filename << RESET << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t comma_pos = line.find(',');
        if (comma_pos != string::npos) {
            string ancestor = line.substr(0, comma_pos);
            string dna = line.substr(comma_pos + 1);
            // Remove any whitespace from DNA
            dna.erase(remove_if(dna.begin(), dna.end(), ::isspace), dna.end());
            ancestors[ancestor] = dna;
        }
    }

    file.close();
    cout << GREEN << "Successfully loaded " << ancestors.size() << " ancestral records.\n" << RESET;
}

// Find matches between input DNA and ancestral DNA
void find_ancestral_matches(const string& dna, const map<string, string>& ancestors) {
    vector<pair<string, float>> matches;

    for (const auto& ancestor : ancestors) {
        const string& ancestral_dna = ancestor.second;
        int distance = levenshtein_distance(dna, ancestral_dna);
        float similarity = 100.0f * (1 - (float)distance / max(dna.length(), ancestral_dna.length()));
        matches.emplace_back(ancestor.first, similarity);
    }

    // Sort matches by similarity (descending order)
    sort(matches.begin(), matches.end(), 
        [](const pair<string, float>& a, const pair<string, float>& b) {
            return a.second > b.second;
        });

    display_results(matches);

    // Show alignment with the best match
    if (!matches.empty()) {
        cout << CYAN << "\nBest match alignment:\n" << RESET;
        display_alignment(dna, ancestors.at(matches[0].first));
        display_similarity_bar(matches[0].second);
    }
}

// Display all results
void display_results(const vector<pair<string, float>>& matches) {
    cout << "\n" << MAGENTA << "Ancestral Match Results:\n";
    cout << "----------------------\n" << RESET;
    cout << fixed << setprecision(2);

    for (const auto& match : matches) {
        string color;
        if (match.second >= 75) color = GREEN;
        else if (match.second >= 50) color = YELLOW;
        else if (match.second >= 25) color = MAGENTA;
        else color = RED;

        cout << BLUE << setw(20) << left << match.first << ": " << color 
             << setw(6) << right << match.second << "%" << RESET << endl;
    }
}

// Display DNA alignment with color coding
void display_alignment(const string& dna, const string& ancestral_dna) {
    int len = min(dna.size(), ancestral_dna.size());

    cout << "\n" << CYAN << "+--------------------- DNA Alignment ---------------------+\n" << RESET;
    cout << BLUE << "Your DNA:    " << RESET;
    for (int i = 0; i < len; ++i) {
        if (dna[i] == ancestral_dna[i]) {
            cout << GREEN << dna[i] << RESET;
        } else {
            cout << RED << dna[i] << RESET;
        }
    }

    cout << "\n" << BLUE << "Ancestor DNA:" << RESET;
    for (int i = 0; i < len; ++i) {
        if (dna[i] == ancestral_dna[i]) {
            cout << GREEN << ancestral_dna[i] << RESET;
        } else {
            cout << RED << ancestral_dna[i] << RESET;
        }
    }
    cout << "\n\n";
}

// Visual similarity bar
void display_similarity_bar(float similarity) {
    int width = 50;
    int filled = static_cast<int>((similarity / 100.0) * width);

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
    cout << "] " << color << similarity << "%" << RESET << "\n";
}