
                if (similarity > 70) {
                    cout << YELLOW;
                }
                cout << "\nDisease: " << diseaseName << ", Match Percentage: " << similarity << "%" << RESET << endl;

                if (similarity > 70) {
                    cout << YELLOW << "Potential mutation detected for " << diseaseName << "." << RESET << endl;
                    cout << "Detailed report:\n";
                    detectMutations(inputSequence, pattern);
                    diseaseFound = true;
                }