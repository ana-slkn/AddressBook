#include "Functions.h"
#include "FileFunctions.h"
#include "Contact.h"
#include "HelpFunctions.h"
#include <vector>
#include <algorithm>
#include <limits>

bool Functions::editContactDirectly(Contact* contactToEdit, const string &fileName, list<Contact*>& addressBook) {
    FileFunctions::readFromFile(fileName, addressBook);
    if (!contactToEdit) return false; 

    string input;
    bool updateSuccess = true;

    cout << "Enter new last name (leave empty to keep the same): ";
    getline(cin, input);
    if (!input.empty()) {
        if (!contactToEdit->updateLastName(input)) {
            cout << "Failed to update last name." << endl;
            updateSuccess = false;
        }
    }

    cout << "Enter new first name (leave empty to keep the same): ";
    getline(cin, input);
    if (!input.empty()) {
        if (!contactToEdit->updateFirstName(input)) {
            cout << "Failed to update first name." << endl;
            updateSuccess = false;
        }
    }

    cout << "Enter new phone number (leave empty to keep the same): ";
    getline(cin, input);
    if (!input.empty()) {
        if (!contactToEdit->updatePhoneNumber(input)) {
            cout << "Failed to update phone number." << endl;
            updateSuccess = false;
        }
    }

    cout << "Enter new email address (leave empty to keep the same): ";
    getline(cin, input);
    if (!input.empty()) {
        if (!contactToEdit->updateEmailAddress(input)) {
            cout << "Failed to update email address." << endl;
            updateSuccess = false;
        }
    }


    BusinessContact* bc = dynamic_cast<BusinessContact*>(contactToEdit);
    PersonalContact* pc = dynamic_cast<PersonalContact*>(contactToEdit);
    FamilyContact* fc = dynamic_cast<FamilyContact*>(contactToEdit);
    if (bc) {
        cout << "Enter new company name (leave empty to keep the same): ";
        getline(cin, input);
        if (!input.empty() && !bc->updateCompanyName(input)) {
            cout << "Failed to update company name." << endl;
            updateSuccess = false;
        }

        cout << "Enter new job title (leave empty to keep the same): ";
        getline(cin, input);
        if (!input.empty() && !bc->updateJobTitle(input)) {
            cout << "Failed to update job title." << endl;
            updateSuccess = false;
        }

        cout << "Enter new business phone (leave empty to keep the same): ";
        getline(cin, input);
        if (!input.empty() && !bc->updateBusinessPhone(input)) {
            cout << "Failed to update business phone." << endl;
            updateSuccess = false;
        }
    } else if (pc) {
        cout << "Enter new birthday (leave empty to keep the same): ";
        getline(cin, input);
        if (!input.empty() && !pc->updateBirthday(input)) {
            cout << "Failed to update birthday." << endl;
            updateSuccess = false;
        }

        cout << "Enter new personal website (leave empty to keep the same): ";
        getline(cin, input);
        if (!input.empty() && !pc->updatePersonalWebsite(input)) {
            cout << "Failed to update personal website." << endl;
            updateSuccess = false;
        }
    } else if (fc) {
        cout << "Enter new relationship type (leave empty to keep the same): ";
        getline(cin, input);
        if (!input.empty() && !fc->updateRelationship(input)) {
            cout << "Failed to update relationship." << endl;
            updateSuccess = false;
        }

        cout << "Enter new important date (leave empty to keep the same): ";
        getline(cin, input);
        if (!input.empty() && !fc->updateImportantDates(input)) {
            cout << "Failed to update important dates." << endl;
            updateSuccess = false;
        }
    }
    FileFunctions::writeContactsToFile(fileName, addressBook);
    return updateSuccess;
}

void Functions::addContactAlphabetically(const string &fileName, list<Contact*>& addressBook){
    addressBook.clear();
    FileFunctions::readFromFile(fileName, addressBook);
    int type;
    std::cout << "Select the type of contact to add:\n";
    cout << "1. Generic\n2. Business\n3. Personal\n4. Family\n";
    type = HelpFunctions::getValidChoice(1, 4);
    if (type == -1){
        cout << "\nYou will be redirected to the main menu.\n";
        return;
    } 

    string lastName, firstName, phoneNumber, emailAddress;

    cout << "Enter the last name of the person: ";
    getline(cin >> ws, lastName); 
    lastName = HelpFunctions::toUpperCase(lastName);

    cout << "Enter the first name of the person: ";
    getline(cin, firstName);
    firstName = HelpFunctions::toUpperCase(firstName);

    cout << "Enter the phone number of the person: ";
    getline(cin, phoneNumber);

    cout << "Enter the email address of the person: ";
    getline(cin, emailAddress);

    Contact* newContact = nullptr;
    bool addContact = true;

    switch (type){
        case 1:{
            newContact = new Contact(lastName, firstName, phoneNumber, emailAddress);
            break;
        }

        case 2: {
            string companyName, jobTitle, businessPhone;
            cout << "Enter the company name: ";
            getline (cin, companyName);
            cout << "Enter the job title: ";
            getline (cin, jobTitle);
            cout << "Enter the business phone: ";
            getline (cin, businessPhone);
            newContact = new BusinessContact(lastName, firstName, phoneNumber, emailAddress, companyName, jobTitle, businessPhone); 
            break;
        }
        
        case 3: {
            string birthday, personalWebsite;
            cout << "Enter the birthday (YYYY-MM-DD): ";
            getline (cin, birthday);
            cout << "Enter the personal website URL: ";
            getline (cin, personalWebsite);
            newContact = new PersonalContact(lastName, firstName, phoneNumber, emailAddress, birthday, personalWebsite);
            break;
        }
        case 4:{
            string relationship, importantDates;
            cout << "Enter the relationship: ";
            getline (cin, relationship);
            cout << "Enter the important dates): ";
            getline (cin, importantDates);
            newContact = new FamilyContact(lastName, firstName, phoneNumber, emailAddress, relationship, importantDates);
            break;
        }
        default: {
            cout << "Unavailable choice.";
            break; 
        }
    }
    
    for (Contact* existingContact : addressBook) {
        bool contactExists = (existingContact->lastName == newContact->lastName &&
                      existingContact->firstName == newContact->firstName ||
                      existingContact->phoneNumber == newContact->phoneNumber ||
                      existingContact->emailAddress == newContact->emailAddress);

        if(contactExists == true){
            cout << "The contact already exists!\nWould you like:\n";
            cout << "1. to edit the contact\n";
            cout << "2. to cancel adding a new contact\n"; // Clarified the option
            //cout << "Your choice (1 / 2) -> ";
            int choice = HelpFunctions::getValidChoice(1, 2);
            if (choice == -1){
                cout << "\nYou will be redirected to the main menu.\n";
                return;
            } 

            if (choice == 1){
                if(editContactDirectly(newContact, fileName, addressBook) == true){
                    cout << "Contact edited succesfully!\n";
                }
                addContact = false;
            } else if (choice == 2) {
                addContact = false;
                cout << "Contact addition cancelled.\n";
            } 
            break;
        }
    }
    if (addContact == true) {
        auto it = addressBook.begin();
        for(; it != addressBook.end(); it++){
            if(HelpFunctions::compareContacts(newContact, *it)) break;      
        }
        addressBook.insert(it, newContact);
        cout << "Contact added successfully!\n";
    }
    if (!addContact && newContact) {
        delete newContact;  
    }
    FileFunctions::writeContactsToFile(fileName, addressBook);
    return;
} 

void display(list<Contact*>& addressBook){
    for (const Contact* contact : addressBook) {
        contact->display();
        cout << endl;
    }
}

void display(list<Contact*>& addressBook, int type){
    bool displayedAny = false;
     for (Contact* contact : addressBook) {
        BusinessContact* bc = dynamic_cast<BusinessContact*>(contact);
        PersonalContact* pc = dynamic_cast<PersonalContact*>(contact);
        FamilyContact* fc = dynamic_cast<FamilyContact*>(contact);

        // Display specific types 
        if ((type == 2 && bc) || (type == 3 && pc) || (type == 4 && fc)) {
            contact->display();
            cout << endl;
            displayedAny = true;
        }
        else if (type == 1 && !bc && !pc && !fc) {
            contact->display();
            cout << endl;
            displayedAny = true;
        }
    }

    if (!displayedAny) {
        string typeStr;
        switch (type) {
            case 1: typeStr = "Generic"; break;
            case 2: typeStr = "Business"; break;
            case 3: typeStr = "Personal"; break;
            case 4: typeStr = "Family"; break;
            default: typeStr = "Unknown"; 
        }
        cout << "No " << typeStr << " contacts found." << endl;
    }
}

void Functions::displayContacts(const string &fileName, list<Contact*>& addressBook){
    addressBook.clear();
    FileFunctions::readFromFile(fileName, addressBook);
    cout << "Would you like to:\n";
    cout << "1. see all contacts\n";
    cout << "2. see a specified group\n";
    int choice = HelpFunctions::getValidChoice(1, 2);
    if (choice == -1){
        cout << "\nYou will be redirected to the main menu.\n";
        return;
    }

    if (choice == 1){
        display(addressBook);
    } else if (choice == 2){
        cout << "Select the type of contact to display:\n";
        cout << "1. Generic\n2. Business\n3. Personal\n4. Family\n";
        int type = HelpFunctions::getValidChoice(1, 4);
        if (type == -1){
            cout << "\nYou will be redirected to the main menu.\n";
            return;
        } 
        display(addressBook, type);
    } 
}

int displayAndChooseCriteria(){
    cout << "Enter the number corresponding to the criteria of search term:\n";
    cout << "1. Last name\n";
    cout << "2. First name\n";
    cout << "3. Phone number\n";
    cout << "4. Email address\n";
    cout << "0. Quit\n";

    int choice = HelpFunctions::getValidChoice(0, 4);
    if (choice == -1 || choice == 0){
        cout << "\nYou will be redirected to the main menu.\n";
    } 
    return choice;
}

string chosenCriteriaInput(int choice){
    string userInput;
    if (choice == 1) {
        cout << "Enter the last name of the contact: ";
    } else if (choice == 2) {
        cout << "Enter the first name of the contact: ";
    } else if (choice == 3) {
        cout << "Enter the phone number of the contact: ";
    } else if (choice == 4) {
        cout << "Enter the email address of the contact: ";
    } else {
        cout << "Invalid choice.";
    }
    cin.ignore();
    getline(cin, userInput);
    if(choice == 1 || choice == 2){
        userInput = HelpFunctions::toUpperCase(userInput);
    }
    return userInput;
}

bool editField(string& field, const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input); // Use getline to allow empty inputs
    if (!input.empty()) {
        if(field == "contactToEdit->lastName" || field == "contactToEdit->firstName"){
            input = HelpFunctions::toUpperCase(input);
        }
        field = input;
        return true;
    }
    return false;
}

void Functions::editContacts(const string &fileName, list<Contact*>& addressBook){
    addressBook.clear();
    FileFunctions::readFromFile(fileName, addressBook);
    int choice = displayAndChooseCriteria();
    if(choice == -1 || choice == 0) return;

    string userInput = chosenCriteriaInput(choice);
    if (choice == 1 || choice == 2){
        userInput = HelpFunctions::toUpperCase(userInput);
    }
    vector<Contact*> foundContacts;
    bool found = false;
    for (Contact* contact : addressBook) {
        if ((choice == 1 && contact -> lastName == userInput) ||
            (choice == 2 && contact -> firstName == userInput) ||
            (choice == 3 && contact -> phoneNumber == userInput) ||
            (choice == 4 && contact -> emailAddress == userInput)) {
            found = true;
            foundContacts.push_back(contact);
        }
    }

    if (!foundContacts.empty()) {
        cout << "Contacts found with the specified " << (choice == 1 ? "last name" :
                                                        (choice == 2 ? "first name" :
                                                         (choice == 3 ? "phone number" :
                                                          "email address"))) << ":\n";
        for (size_t i = 0; i < foundContacts.size(); ++i) {
            cout << i + 1 << ". " << foundContacts[i]->lastName << " " << foundContacts[i]->firstName
                 << ", " << foundContacts[i]->phoneNumber << ", " << foundContacts[i]->emailAddress << endl;
        }

        Contact* contactToEdit;
        if(foundContacts.size() > 1){
            cout << "Enter the number of the contact you would like to edit.\nChoose between 1 and "
                 << foundContacts.size() << ". Enter 0 to cancel.\nYour choice -> ";
            int choice = HelpFunctions::getValidChoice(1, 4);
            if (choice == -1){
                cout << "\nYou will be redirected to the main menu.\n";
                return;
            } 
            contactToEdit = foundContacts[choice - 1];
            cin.ignore();
        } else {
            contactToEdit = foundContacts[0];
        }

        BusinessContact* bc = dynamic_cast<BusinessContact*>(contactToEdit);
        PersonalContact* pc = dynamic_cast<PersonalContact*>(contactToEdit);
        FamilyContact* fc = dynamic_cast<FamilyContact*>(contactToEdit);
        bool lastNameChanged = editField(contactToEdit->lastName, "Enter new last name (leave empty to keep the same) -> ");
        bool firstNameChanged = editField(contactToEdit->firstName, "Enter new first name (leave empty to keep the same) -> ");
        editField(contactToEdit->phoneNumber, "Enter new phone number (leave empty to keep the same) -> ");
        editField(contactToEdit->emailAddress, "Enter new email address (leave empty to keep the same) -> ");
        if(bc){
            editField(bc->companyName, "Enter new company name (leave empty to keep the same) -> ");
            editField(bc->jobTitle, "Enter new job title (leave empty to keep the same) -> ");
            editField(bc->businessPhone, "Enter new business phone (leave empty to keep the same) -> ");
        } else if (pc) {
            editField(pc->birthday, "Enter new birthday (leave empty to keep the same) -> ");
            editField(pc->personalWebsite, "Enter new personal website (leave empty to keep the same) -> ");
        } else if (fc) {
            editField(fc->relationship, "Enter new birthday (leave empty to keep the same) -> ");
            editField(fc->importantDates, "Enter new personal website (leave empty to keep the same) -> ");
        }

        if (lastNameChanged == true || firstNameChanged == true) {
            // Remove the contact from the list
            addressBook.remove(contactToEdit);

            if(lastNameChanged) contactToEdit-> lastName = HelpFunctions::toUpperCase(contactToEdit->lastName);
            if(firstNameChanged) contactToEdit -> firstName = HelpFunctions::toUpperCase(contactToEdit->firstName);

            // Find the correct position for reinsertion 
            auto it = find_if(addressBook.begin(), addressBook.end(), [&](const Contact* other) {
                return HelpFunctions::compareContacts(contactToEdit, other);
            });
            
            // Reinsert the contact at the new correct position 
            addressBook.insert(it, contactToEdit);
            cout << "Contact edited and repositioned successfully.\n";
        }
    } else {
        cout << "Contact not found\n";
    }

    FileFunctions::writeContactsToFile(fileName, addressBook);
}

void Functions::searchContact(const string &fileName, list<Contact*>& addressBook){
    addressBook.clear();
    FileFunctions::readFromFile(fileName, addressBook);
    int choice = displayAndChooseCriteria();
    if(choice == -1 || choice == 0) return;
    string userInput = chosenCriteriaInput(choice);
    if(choice == 1 || choice == 2){
        userInput = HelpFunctions::toUpperCase(userInput);
    }

    vector<Contact*> foundContacts;
    bool found = false;
    for (Contact* contact : addressBook) {
        if ((choice == 1 && contact -> lastName == userInput) ||
            (choice == 2 && contact -> firstName == userInput) ||
            (choice == 3 && contact -> phoneNumber == userInput) ||
            (choice == 4 && contact -> emailAddress == userInput)) {
            found = true;
            foundContacts.push_back(contact);
        }
    }

    if (!foundContacts.empty()) {
        cout << "\nContacts found with the specified " << (choice == 1 ? "last name" :
                                                        (choice == 2 ? "first name" :
                                                         (choice == 3 ? "phone number" :
                                                          (choice == 4 ? "email address":
                                                          "type")))) << ":\n";
        for (auto it = 0; it < foundContacts.size(); it++) {
            cout << it << ". ";
            foundContacts[it]->display();
            cout << endl;
        }       
    } else {
        cout << "\nNo contact was found\n";
    }
}

void Functions::deleteContact(const string &fileName, list<Contact*>& addressBook){
    addressBook.clear();
    FileFunctions::readFromFile(fileName, addressBook);
    int choice = displayAndChooseCriteria();
    if(choice == -1) return;

    string userInput = chosenCriteriaInput(choice);
    if (choice == 1 || choice == 2){
        userInput = HelpFunctions::toUpperCase(userInput);
    }

    vector<Contact*> foundContacts;
    bool found = false;
    for (Contact* contact : addressBook) {
        if ((choice == 1 && contact -> lastName == userInput) ||
            (choice == 2 && contact -> firstName == userInput) ||
            (choice == 3 && contact -> phoneNumber == userInput) ||
            (choice == 4 && contact -> emailAddress == userInput)) {
            found = true;
            foundContacts.push_back(contact);
        }
    }

    if (!foundContacts.empty()) {
        cout << "\nContacts found with the specified " << (choice == 1 ? "last name" :
                                                        (choice == 2 ? "first name" :
                                                         (choice == 3 ? "phone number" :
                                                          (choice == 4 ? "email address":
                                                          "type")))) << ":\n";
                                                          //cout << "\tStart cast\t";
        BusinessContact* bc = dynamic_cast<BusinessContact*>(foundContacts[choice - 1]);
        PersonalContact* pc = dynamic_cast<PersonalContact*>(foundContacts[choice - 1]);
        FamilyContact* fc = dynamic_cast<FamilyContact*>(foundContacts[choice - 1]);
        for (int i = 0; i < foundContacts.size(); ++i) {
            cout << i+1 << ". ";
            if(bc) {
                foundContacts[i]->display();
            } else if (fc) {
                foundContacts[i]->display();
            } else if (pc) {
                foundContacts[i]->display();
            } else {
                foundContacts[i]->display();
            }
            cout << endl;
        }
        int choice;
        if(foundContacts.size() > 1){
            cout << "\nEnter the number of the contact you would like to delete.\n";
            choice = HelpFunctions::getValidChoice(1, foundContacts.size());
            if (choice == -1){
                cout << "\nYou will be exited from the program.\n";
                return;
            } 
        } else if (foundContacts.size() == 1) {
            choice = 1;
        }
            cout << "\nAre you sure you want to delete ";
            if(bc) {
                foundContacts[choice-1]->display();
            } else if (fc) {
                foundContacts[choice-1]->display();
            } else if (pc) {
                foundContacts[choice-1]->display();
            } else {
                foundContacts[choice-1]->display();
            } 
            cout << endl;
            
            char confirm = HelpFunctions::getYesOrNo();
            if (confirm == ' '){
                cout << "\nYou will be redirected to the main menu.\n";
                return;
            } 
            if (confirm == 'y') {
                for (auto it = addressBook.begin(); it != addressBook.end();) {
                    if (*it == foundContacts[choice - 1]) {
                        it = addressBook.erase(it);
                        cout << "\nContact deleted successfully.\n";
                        break;
                    } else {
                        ++it;
                    }
                }
            } else if (confirm == 'n') {
                cout << "\nDeletion cancelled.\n";
            } else {
                cout << "Invalid choice.\n";
            }
    } else {
        if (choice == 1) {
            cout << "\nNo contacts found with last name '" << userInput << "'.\n";
        } else if (choice == 2) {
            cout << "\nNo contacts found with first name '" << userInput << "'.\n";
        } else if (choice == 3) {
            cout << "\nNo contacts found with phone number '" << userInput << "'.\n";
        } else if (choice == 4) {
            cout << "\nNo contacts found with email address '" << userInput << "'.\n";
        }
    }
    FileFunctions::writeContactsToFile(fileName, addressBook);
}

void Functions::deleteAddressBook(const string &fileName, list<Contact*>& addressBook){
    cout << "Are you sure you want to delete the address book?\n";
    char confirm = HelpFunctions::getYesOrNo();
    if (confirm == ' '){
        cout << "\nYou will be exited from the program.\n";
        return;
    }else if (confirm == 'y' || confirm == 'Y') {
        addressBook.clear();
        if(remove(fileName.c_str()) == 0) {
            cout << "Address book deleted successfully!" << endl;
            return;
        } else {
            std::perror("Error deleting file");
        }
     } else if (confirm == 'n' || confirm == 'N'){
        cout << "Deletion cancelled" << endl;
    } 
}