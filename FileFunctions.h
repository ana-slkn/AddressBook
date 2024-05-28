#ifndef FILEFUNCTIONS_H
#define FILEFUNCTIONS_H
#include "Contact.h"

class FileFunctions{
    public:
    static bool handleFileAccess(const string& filename, int choice);
    static bool createFile(const string& filename);
    static void readFromFile(const string &fileName, list<Contact*> &addressbook);
    static void writeContactsToFile(const string& fileName, const list<Contact*> &addressBook);
    static bool isFileEmpty(const string& filename);
    static bool fileExists(const string& filename);
};

#endif