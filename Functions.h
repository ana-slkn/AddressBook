#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <list>
#include <string>
#include "Contact.h"
#include <fstream>

using namespace std;

class Functions{
    public:
    static void addContactAlphabetically(const string &filename, list<Contact*>& addressbook);
    static void displayContacts(const string &fileName, list<Contact*>& adrressBook);
    static void editContacts(const string &fileName, list<Contact*>& adrressBook);
    static bool editContactDirectly(Contact* contactToEdit, const string &fileName, list<Contact*>& addressBook);
    static void searchContact(const string &fileName, list<Contact*>& addressBook);
    static void deleteContact(const string &fileName, list<Contact*>& addressBook);
    static void deleteAddressBook(const string &fileName, list<Contact*>& addressBook);
};

#endif