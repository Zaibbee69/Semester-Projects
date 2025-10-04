#include <iostream>
#include <cstdlib>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"


using namespace std;

int main() {
    int choice;
    while (true) {
        cout << CYAN << R"(
            ░██████╗░███████╗███╗░░██╗███████╗██╗░░░░░██╗███╗░░██╗██╗░██╗██╗
            ██╔════╝░██╔════╝████╗░██║██╔════╝██║░░░░░██║████╗░██║██║██╔╝██║
            ██║░░██╗░█████╗░░██╔██╗██║█████╗░░██║░░░░░██║██╔██╗██║█████═╝░██║
            ██║░░╚██╗██╔══╝░░██║╚████║██╔══╝░░██║░░░░░██║██║╚████║██╔═██╗░╚═╝
            ╚██████╔╝███████╗██║░╚███║███████╗███████╗██║██║░╚███║██║░╚██╗██╗
            ░╚═════╝░╚══════╝╚═╝░░╚══╝╚══════╝╚══════╝╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚═╝
            )" << RESET << endl;

        cout << MAGENTA << BOLD << R"(              🔬 DNA Analysis Suite by 
                             _                     _                        
                            |_ ._ _   _.  _ |_    |_) _. ._ _. _|_ |_  o  _ 
                            |  | (/_ (_| _> | |   |  (_| | (_|  |_ | | | _> ❤️)" << RESET << endl;

    
        cout << endl << endl;
        cout << GREEN << BOLD << "1. " << RESET << YELLOW << "DNA Relation Detection\n";
        cout << GREEN << BOLD << "2. " << RESET << YELLOW << "Mutation Detection\n";
        cout << GREEN << BOLD << "3. " << RESET << YELLOW << "Ancestral Gene Detection\n";
        cout << RED   << BOLD << "4. " << RESET << YELLOW << "Exit\n";
        cout << MAGENTA << "\nEnter your choice: " << RESET;

        cin >> choice;

        switch (choice) {
            case 1:
                cout << GREEN << "Launching Relation Detection...\n" << RESET;
                system("./relation");
                break;
            case 2:
                cout << GREEN << "Launching Mutation Detection...\n" << RESET;
                system("./mutation");
                break; 
            case 3:
                cout << GREEN << "Launching Ancestral Detection...\n" << RESET;
                system("./ancestral");
                break;
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << RED << "Invalid choice. Try again.\n" << RESET;

        }
    }
}
