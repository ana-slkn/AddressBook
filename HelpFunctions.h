#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include "Contact.h"
#include <sys/stat.h>
#include <limits>

class HelpFunctions{
    public:
    static bool compareContacts(const Contact* a, const Contact* b);
    static std::string toUpperCase(const string& str);
    static int getValidChoice(int from, int to);
    static char getYesOrNo();
};

#endif