#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype> // For isalpha() function
using namespace std;

// Color Definitions
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"

struct DNAProfile {
    string name;
    string sequence;
    DNAProfile* next;

    DNAProfile(string n, string seq) {
        name = n;
        sequence = seq;
        next = nullptr;
    }
};

class DNADatabase {
private:
    DNAProfile* head;

public:
    DNADatabase() {
        head = nullptr;
    }

    void addProfile(string name, string sequence) {
        sequence = cleanSequence(sequence);
        DNAProfile* newNode = new DNAProfile(name, sequence);
        newNode->next = head;
        head = newNode;
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << RED <<"Error: Could not open file " << RESET << filename << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, sequence;
            getline(ss, name, ',');
            getline(ss, sequence);
            if (!name.empty() && !sequence.empty()) {
                addProfile(name, sequence);
            }
        }
        file.close();
        cout << GREEN << "Data loaded successfully from " << CYAN << filename << RESET << "\n";
    }

    void displayAll() {
        if (head == nullptr) {
            cout << "No DNA profiles available.\n";
            return;
        }
        DNAProfile* current = head;
        while (current != nullptr) {
            cout << MAGENTA << "Name: " << GREEN << current->name << MAGENTA << ", DNA: " << GREEN << current->sequence << RESET << endl;
            current = current->next;
        }
    }

    string cleanSequence(const string& seq) {
        string cleanedSeq;
        for (char ch : seq) {
            if (isalpha(ch)) {
                cleanedSeq.push_back(toupper(ch));
            }
        }
        return cleanedSeq;
    }

    double calculateSimilarity(const string& a, const string& b) {
        int match = 0;
        int minLen = min(a.size(), b.size());
        for (int i = 0; i < minLen; ++i) {
            if (a[i] == b[i]) {
                match++;
            }
        }
        return ((double)match / max(a.size(), b.size())) * 100.0;
    }

    void detectMutations(const string& a, const string& b) {
        int minLen = min(a.size(), b.size());
        bool mutationFound = false;

        for (int i = 0; i < minLen; ++i) {
            if (a[i] != b[i]) {
                cout << CYAN <<  "Position " << i + 1 << ": Expected " << b[i] << ", Found " << a[i] << " (substitution)" << endl;
                mutationFound = true;
            }
        }

        if (a.size() > b.size()) {
            cout << "Extra nucleotides in input sequence (insertion): ";
            for (size_t i = b.size(); i < a.size(); ++i) {
                cout << i + 1 << "(" << a[i] << ") ";
                mutationFound = true;
            }
            cout << endl;
        } else if (b.size() > a.size()) {
            cout << "Missing nucleotides in input sequence (deletion): ";
            for (size_t i = a.size(); i < b.size(); ++i) {
                cout << i + 1 << "(" << b[i] << ") ";
                mutationFound = true;
            }
            cout << endl;
        }

        if (!mutationFound) {
            cout << GREEN << "\nNo mutations detected. Perfect match.\n";
        }
    }

    void matchDNAWithDisease(string patientFile, string diseaseFile) {
        ifstream patientFileStream(patientFile);
        if (!patientFileStream.is_open()) {
            cout << "Error: Could not open patient DNA file " << patientFile << endl;
            return;
        }

        string patientLine;
        while (getline(patientFileStream, patientLine)) {
            stringstream ss(patientLine);
            string patientName, patientDNA;
            getline(ss, patientName, ',');
            getline(ss, patientDNA);
            if (!patientName.empty() && !patientDNA.empty()) {
                patientDNA = cleanSequence(patientDNA);
                cout << CYAN << "\n+----------Analyzing DNA for: " << GREEN << patientName << CYAN << "----------+" <<RESET << endl;
                matchDNAWithPattern(patientDNA, diseaseFile);
            }
        }
        patientFileStream.close();
    }

    void matchDNAWithPattern(const string& inputSequence, string diseaseFile) {
        ifstream file(diseaseFile);
        if (!file.is_open()) {
            cout << RED <<  "Error: Could not open disease patterns file " << diseaseFile << RESET << endl;
            return;
        }

        string line;
        bool diseaseFound = false;
        while (getline(file, line)) {
            stringstream ss(line);
            string diseaseName, pattern;
            getline(ss, diseaseName, ',');
            getline(ss, pattern);

            if (!diseaseName.empty() && !pattern.empty()) {
                pattern = cleanSequence(pattern);
                double similarity = calculateSimilarity(inputSequence, pattern);
                cout << MAGENTA << "\nDisease: " << YELLOW << diseaseName << MAGENTA << ", Match Percentage: " << YELLOW << similarity << "%" << endl;

                if (similarity > 70) {
                    cout << RED <<  "\n\nPotential mutation detected for " << CYAN <<  diseaseName << YELLOW << " . "<<endl<< " Detailed report:" << endl;
                    detectMutations(inputSequence, pattern);
                    diseaseFound = true;
                }
            }
        }

        if (!diseaseFound) {
            cout << "No matching diseases or significant mutations found for the patient.\n";
        }
        file.close();
    }
};

int main() {
    DNADatabase db;
    int choice;
    string patientFile, diseaseFile;

    while (true) {
        cout << YELLOW << "\n+----------DNA Mutation Detection Simulator Menu----------+\n\n" << RESET;
        cout << MAGENTA << "1. Load DNA from file\n";
        cout << "2. Display all DNA profiles\n";
        cout << "3. Match and detect mutations\n";
        cout << "4. Exit\n\n";
        cout << CYAN <<"Enter your choice: " << YELLOW ;
        cin >> choice;
        cout << RESET;

        if (choice == 1) {
            cout << CYAN << "Enter filename for patient DNA file: " << YELLOW;
            cin >> patientFile;
            db.loadFromFile(patientFile);
        } else if (choice == 2) {
            db.displayAll();
        } else if (choice == 3) {
            cout << CYAN << "Enter patient DNA filename: " << YELLOW;
            cin >> patientFile;
            cout << CYAN << "Enter disease patterns filename: " << YELLOW;
            cin >> diseaseFile;
            db.matchDNAWithDisease(patientFile, diseaseFile);
        } else if (choice == 4) {
            cout << RED << "Exiting program.\n";
            cout << GREEN << "Thankyou for using GeneLink: DNA matching Simulator!\n\n\n" << RESET;
            break;
        } else {
            cout << RED << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
