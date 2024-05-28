#include "FileFunctions.h"
#include "Functions.h"
#include "HelpFunctions.h"
#include <iostream>
#include <list>
#include <string>
#include <cstdio>


using namespace std;


bool fileExists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

int main (void){
    list<Contact*> addressBook;

    cout << "--------------------Address Book--------------------" << endl;
    cout << "Do you want to:\n1. Open an existing address book\n2. Create a new address book\n ";
    
    int initialChoice = HelpFunctions::getValidChoice(1, 2);
    if (initialChoice == -1){
            cout << "\nYou will be exited from the program.\n";
            return 0;
    }
    // cin >> initialChoice;
    cin.ignore();
    
    string fileName;
    switch (initialChoice) {
        case 1:
            cout << "Enter the filename of the existing address book (format: filename.txt): ";
            break;
        case 2:
            cout << "Enter the filename for the new address book (format: filename.txt): ";
            break;
        default:
            cout << "Invalid choice. Exiting program." << endl;
            return 0;
    }
    
    getline(cin, fileName); 
    if (initialChoice == 1 && fileExists(fileName)){
        FileFunctions::readFromFile(fileName, addressBook);
    }else if (initialChoice == 1 && FileFunctions::handleFileAccess(fileName, initialChoice) && !FileFunctions::fileExists(fileName)){
        if (FileFunctions::isFileEmpty(fileName)){
            Functions::addContactAlphabetically(fileName, addressBook);
        }
    } else if (initialChoice == 2 && FileFunctions::handleFileAccess(fileName, initialChoice)){
        Functions::addContactAlphabetically(fileName, addressBook);
      } else {
        return 0;
    }

    int choice;
    while (choice != 0)
    {
        cout << "\nMenu:\n";
        cout << "1. Display contacts\n";
        cout << "2. Search contact\n";
        cout << "3. Add contact\n";
        cout << "4. Edit contact\n";
        cout << "5. Delete contact\n";
        cout << "6. Delete address book\n";
        cout << "0. Quit\n";
        choice = HelpFunctions::getValidChoice(0, 6);
        if (choice == -1){
            cout << "\nYou will be exited from the program.\n";
            return 0;
        } 


        switch (choice){
            case 1: Functions::displayContacts(fileName, addressBook); break;
            case 2: Functions::searchContact(fileName, addressBook); break;
            case 3: Functions::addContactAlphabetically(fileName, addressBook); break;
            case 4: Functions::editContacts(fileName, addressBook); break;
            case 5: Functions::deleteContact(fileName, addressBook); break;
            case 6: 
            // {
            // cout << "Are you sure you want to delete the address book?\n";
            // char confirm = HelpFunctions::getYesOrNo();
            // if (confirm == ' '){
            //     cout << "\nYou will be exited from the program.\n";
            //     return 0;
            // }else if (confirm == 'y' || confirm == 'Y') {
            //     addressBook.clear();
            //     if(remove(fileName.c_str()) == 0) {
            //         cout << "Address book deleted successfully!" << endl;
            //         return 0;
            //     } else {
            //         std::perror("Error deleting file");
            //     }
            // } else if (confirm == 'n' || confirm == 'N'){
            //     cout << "Deletion cancelled" << endl;
            // } }
            Functions::deleteAddressBook(fileName, addressBook); break;
            case 0: 
                cout << "You decided to quit. Bye!" << endl;
                exit(0);
            break;
            default: cout << "Invalid choice" << endl; break;
        }
    }

    return 0;
}