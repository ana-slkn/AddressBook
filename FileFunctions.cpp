#include "FileFunctions.h"
#include "Contact.h"
#include "HelpFunctions.h"
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <limits>

bool FileFunctions::isFileEmpty(const string& filename) {
    std::ifstream file(filename);
    char buffer;
    return file.read(&buffer, 1).gcount() == 0;
}

bool FileFunctions::fileExists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

bool FileFunctions::handleFileAccess(const string& filename, int choice) {
    ifstream file(filename);
    // Check if the file stream failed to open the file
    if(!file && choice == 2){
        return FileFunctions::createFile(filename);
    } else if (!file) {
        cout << "The file '" << filename << "' does not exist." << endl;
        cout << "Would you like to:\n1. Retry entering the filename\n2. Create a new file\n3. Exit\n";
        int choice = HelpFunctions::getValidChoice(1, 3);
        switch (choice) {
            case 1: return false;  // Retry
            case 2: return FileFunctions::createFile(filename);  
            case 3: cout << "Exiting the program.\n";
                    return false;  // Exit
            default: cout << "Invalid choice. Exiting program.\n";
                    return false;
        }
    } else {
        cout << "The file '" << filename << "' already exists!" << endl;
        cout << "Would you like to:\n1. Open the file\n2. Exit\n";
        int choice = HelpFunctions::getValidChoice(1, 2);
        if (choice == -1 || choice == 2) {
            cout << "\nExiting the program.\n";
            return false;
        }
        return true;  
    }
}


bool FileFunctions::createFile(const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        cout << "File created successfully: " << filename << endl;
        file.close();
        return true;
        } else {
            cout << "Failed to create file: " << filename << endl;
            return false;
    }
}

void FileFunctions::readFromFile(const string &fileName, list<Contact*> &addressBook) {
    ifstream file(fileName);

    if(!file.is_open()){
        cerr << "Failed to open the file" << endl;
        return;
    }

    string line;
    while(getline(file, line)){
        stringstream ss(line);
        char type;
        string lastName, firstName, phoneNumber, emailAddress;
        
        
        ss >> type;
        ss.ignore(numeric_limits<streamsize>::max(), ',');    
        getline(ss, lastName, ',');
        getline(ss, firstName, ',');
        getline(ss, phoneNumber, ',');
        getline(ss, emailAddress, ',');
        
        if (type == 'B'){
            string companyName, jobTitle, businessPhone;
            getline(ss, companyName, ',');
            getline(ss, jobTitle, ',');
            getline(ss, businessPhone, ',');
            addressBook.push_back(new BusinessContact(lastName, firstName, phoneNumber, emailAddress, companyName, jobTitle, businessPhone));
        } else if (type == 'P'){
            string birthday, personalWebsite;
            getline(ss, birthday, ',');
            getline(ss, personalWebsite, ',');
            addressBook.push_back(new PersonalContact(lastName, firstName, phoneNumber, emailAddress, birthday, personalWebsite));
        } else if (type == 'F'){
            string relationship, importantDates;
            getline(ss, relationship, ',');
            getline(ss, importantDates, ',');
            addressBook.push_back(new FamilyContact(lastName, firstName, phoneNumber, emailAddress, relationship, importantDates));
        } else if (type == 'G') {
            addressBook.push_back(new Contact(lastName, firstName, phoneNumber, emailAddress));
        } else {
            cerr << "Unrecognizable contact type: " << type << endl;
            continue;
        }
    }
    file.close();
}

void FileFunctions::writeContactsToFile(const string& fileName, const list<Contact*> &addressBook){
    ofstream file(fileName);
    if(!file.is_open()) {
        cerr << "Error: could not open file '" << fileName << "' for writing." << endl;
        return;
    }

    for (const Contact* contact : addressBook) {
        char typeContact;
        const BusinessContact* bc = dynamic_cast<const BusinessContact*>(contact);
        const PersonalContact* pc = dynamic_cast<const PersonalContact*>(contact);
        const FamilyContact* fc = dynamic_cast<const FamilyContact*>(contact);

        if(bc != nullptr) {
            typeContact = 'B';
            file << typeContact << "," << bc->toCSV() << endl;
        }

        else if(pc != nullptr) {
            typeContact = 'P';
            file << typeContact << "," << pc->toCSV() << endl;
        }

        else if(fc != nullptr) {
            typeContact = 'F';
            file << typeContact << "," << fc->toCSV() << endl;
        }
    
        else {
            typeContact = 'G';
            file << typeContact << "," << contact->toCSV() << endl;
        }
    }
    file.close();
}

