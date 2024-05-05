#ifndef PERSON_H
#define PERSON_H

#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <cstdint>
using namespace std;
    
class Person
{
public:
    static Person *currentPerson;

    Person();
    Person(const string &userName, const string &password);
    void editUserName();
    void editPassword();
    bool checkPassword(const string &password, const Person *p);
    void showMyRole();
    bool static checkValidPassword(const string &password);
    static void addPerson(const string &userName, const string &password, const bool &role);
    static Person *getUserByName(const string &userName);
    static void initializeUser();
    uint64_t hashPassword(const string &password);
    bool getAdminRole();
    static bool isNumber(const string &s);
    string getUserName();
    ~Person();

protected:
    bool admin;

private:
    string userName;
    uint64_t password;

    static map<string, Person *> personStore; // hash every username with it's object
};

#endif