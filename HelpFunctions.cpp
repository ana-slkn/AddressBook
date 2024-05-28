#include "HelpFunctions.h"


std::string HelpFunctions::toUpperCase(const string& str) {
    string upperStr = str;
    for (char& c : upperStr) {
        c = toupper(c);
    }
    return upperStr;
}

bool HelpFunctions::compareContacts(const Contact* a, const Contact* b){ //To order the contacts alphabetically by last name, and, if needed, by first name
    if (a -> lastName != b -> lastName){
        return a -> lastName < b -> lastName;
    } else {
        return a -> firstName < b -> firstName;
    }
} 

int HelpFunctions::getValidChoice(int from, int to) {
    int choice;
    int maxAttempts = 5;
    int attempts = 0;

    do {
        try {
            cout << "Enter a number between " << from << " and " << to << endl;
            cout << "Your choice -> ";
            cin >> choice;

            if (cin.fail()) {  // Check if input failed due to inappropriate type
                throw runtime_error("Input failed due to inappropriate type");
            }

            if (choice < from || choice > to) {
                throw runtime_error("Number out of range");
            }

            // If input is successful and within range, return the choice
            return choice;
        }
        catch (const runtime_error& e) {
            // Clear error state and ignore the rest of the line
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            attempts++;
            cout << "Invalid input: " << e.what() << ". ";

            if (attempts < maxAttempts) {
                cout << "Please try again." << endl;
            } else {
                cout << "You have reached the maximum number of attempts." << endl;
                return -1;
            }
        }
    } while (attempts < maxAttempts);

    return -1;
}


char HelpFunctions::getYesOrNo() {
    int maxAttempts = 5;
    char choice;
    int attempts = 0;

    while (attempts < maxAttempts) {
        cout << "Enter 'y' for Yes or 'n' for No: ";
        cin >> choice;

        choice = tolower(choice);

        if (choice == 'y' || choice == 'n') {
            return choice;  // Return valid input
        } else {
            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        attempts++;  
        if (attempts == maxAttempts) {
            cout << "Maximum attempts reached." << endl;
        }
    }

    return ' ';  // Default or error value when max attempts are exceeded
}