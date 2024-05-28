#ifndef CONTACT_H
#define CONTACT_H
#include <iostream>
#include <string>
#include <list>

using namespace std;

class Contact{
    protected:
        string lastName;
        string firstName;
        string phoneNumber;
        string emailAddress;

    public:

    Contact(string lastName, string firstName, string phoneNumber, string emailAddress)
        : lastName(lastName), firstName(firstName), phoneNumber(phoneNumber), emailAddress(emailAddress) {}
    virtual char getType() const {
        return 'G';  // 'G' for Generic
    }
    virtual void display() const;
    void add(list<Contact*>& addressBook);
    bool updateLastName(const string &newLastName);
    bool updateFirstName(const string &newFirstName);
    bool updatePhoneNumber(const string &newPhoneNumber);
    bool updateEmailAddress(const string &newEmailAddress);
    string toCSV() const;
    friend class Functions;
    friend class FileFunctions;
    friend class HelpFunctions;
    virtual ~Contact() {}
};

class BusinessContact : public Contact{
    private:
        string companyName;
        string jobTitle;
        string businessPhone;
    
    public:

    BusinessContact(string lastName, string firstName, string phoneNumber, string emailAddress,
                    string companyName, string jobTitle, string businessPhone)
        : Contact(lastName, firstName, phoneNumber, emailAddress), // Call the base class constructor
          companyName(companyName), jobTitle(jobTitle), businessPhone(businessPhone) {}
    char getType() const override {
        return 'B';  
    }

    void display()const override;
    void add(list<Contact*>& addressBook);
    bool updateCompanyName(const string &newCompanyName);
    bool updateJobTitle(const string &newJobTitle);
    bool updateBusinessPhone(const string &newBusinessPhone);
    string toCSV() const;
    friend class Functions;
}; 

class PersonalContact : public Contact{
    private:
        string birthday;
        string personalWebsite;

    public:

    PersonalContact(string lastName, string firstName, string phoneNumber, string emailAddress,
                    string birthday, string personalWebsite)
        : Contact(lastName, firstName, phoneNumber, emailAddress), // Call the base class constructor
          birthday(birthday), personalWebsite(personalWebsite) {}
    char getType() const override {
        return 'P';  
    }
    void display() const override;
    void add(list<Contact*>& addressBook);
    bool updateBirthday(const string &newBirthday);
    bool updatePersonalWebsite(const string &newPersonalWebsite);
    string toCSV() const;
    friend class Functions;
};

class FamilyContact : public Contact{
    private:
        string relationship;
        string importantDates;

    public:
    FamilyContact(string lastName, string firstName, string phoneNumber, string emailAddress,
                  string relationship, string importantDates)
        : Contact(lastName, firstName, phoneNumber, emailAddress),
          relationship(relationship), importantDates(importantDates) {}
    char getType() const override {
        return 'F';  
    }

    void display() const override;
    void add(list<Contact*>& addressBook);
    bool updateRelationship(const string &newRelationship);
    bool updateImportantDates(const string &newImportantDates);
    string toCSV() const;
    friend class Functions;
};

#endif

