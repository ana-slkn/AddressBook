#include "Contact.h"
#include "Functions.h"
#include "HelpFunctions.h"
#include <sstream>


#pragma region Contact

void Contact::display() const{
    cout << getType() << ", " << lastName << " " << firstName << ", " << phoneNumber << ", " << emailAddress;
}

void Contact::add(list<Contact*>& addressBook){
    addressBook.push_back(this);
}

bool Contact::updateLastName(const string &newLastName){
    lastName = HelpFunctions::toUpperCase(newLastName);
    cout << "Last name updated succesfully";
    return true;
}

bool Contact::updateFirstName(const string &newFirstName){
    firstName = HelpFunctions::toUpperCase(newFirstName);
    cout << "First name updated succesfully";
    return true;
}

bool Contact::updatePhoneNumber(const string &newPhoneNumber){
    phoneNumber = newPhoneNumber;
    cout << "Phone number updated succesfully";
    return true;
}

bool Contact::updateEmailAddress(const string &newEmailAddress){
    emailAddress = newEmailAddress;
    cout << "Email address updated succesfully";
    return true;
}

string Contact::toCSV() const{
    stringstream ss;
    ss << HelpFunctions::toUpperCase(lastName) << "," 
       << HelpFunctions::toUpperCase(firstName) << "," 
       << phoneNumber << "," 
       << emailAddress;

    return ss.str();
}

#pragma endregion

#pragma region BusinessContact

void BusinessContact::display() const{
    Contact::display(); 
    cout << ", " << companyName << ", " << jobTitle << ", " << businessPhone;
}


void BusinessContact::add(list<Contact*>& addressBook){
    addressBook.push_back(this);
}

bool BusinessContact::updateCompanyName(const string &newCompanyName){
    companyName = newCompanyName;
    cout << "Company name updated succesfully";
    return true;
}

bool BusinessContact::updateJobTitle(const string &newJobTitle){
    jobTitle = newJobTitle;
    cout << "Job title updated succesfully";
    return true;
}

bool BusinessContact::updateBusinessPhone(const string &newBusinessPhone){
    businessPhone = newBusinessPhone;
    cout << "Business phone updated succesfully";
    return true;
}

string BusinessContact::toCSV() const {
    stringstream ss;
    ss << Contact::toCSV() << ","
       << companyName << ","
       << jobTitle << ","
       << businessPhone;

    return ss.str();
}
#pragma endregion

#pragma region PersonalContact

void PersonalContact::display() const{
    Contact::display();
    cout <<", " << birthday << ", " << personalWebsite;
}

void PersonalContact::add(list<Contact*>& addressBook){
    addressBook.push_back(this);
}

bool PersonalContact::updateBirthday(const string &newBirthday){
    birthday = newBirthday;
    cout << "Birthday updated succesfully!";
    return true;
}

bool PersonalContact::updatePersonalWebsite(const string &newPersonalWebsite){
    personalWebsite = newPersonalWebsite;
    cout << "Personal website updates succesfully!";
    return true;
}

string PersonalContact::toCSV() const{
    stringstream ss;

    ss << Contact::toCSV() << ","
       << birthday << ","
       << personalWebsite;

    return ss.str();
}

#pragma endregion

#pragma region FamilyContact

void FamilyContact::display() const{
    Contact::display();
    cout << ", " << relationship << ", " << importantDates;
}

void FamilyContact::add(list<Contact*>& addressBook){
    addressBook.push_back(this);
}

bool FamilyContact::updateRelationship(const string &newRelationship){
    relationship = newRelationship;
    cout << "relationship updates succesfully!";
    return true;
}

bool FamilyContact::updateImportantDates(const string &newImportantDates){
    importantDates = newImportantDates;
    cout << "Important dates updated succesfully!";
    return true;
}

string FamilyContact::toCSV() const{
    stringstream ss;

    ss << Contact::toCSV() << ","
       << relationship << ","
       << importantDates;

    return ss.str();
}


#pragma endregion