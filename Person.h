#ifndef PERSON_H
#define PERSON_H

#pragma once

#include <string>
#include <map>
using namespace std;

class Person 
{
public:

    static Person *currentUser;
    bool admin;

    Person(string userName, string password);
    void editUserName();
    void editPassword();
    bool checkPassword(string password, Person *p);
    void showMyRole();
    bool static checkValidPassword(string password);
    static void addPerson(string userName, string password, bool role);
    static Person *getUserByName(string userName);
    ~Person();

private:
    string userName;
    string password;
    static map<string, Person *> personStore; // hash every username with it's object
};

#endif