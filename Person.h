#ifndef PERSON_H
#define PERSON_H

#pragma once

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
    ~Person();

protected:
    bool admin;

private:
    string userName;
    uint64_t password;
    uint64_t hashPassword(const string &password);
    static map<string, Person *> personStore; // hash every username with it's object
};

#endif