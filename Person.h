#ifndef PERSON_H
#define PERSON_H

#pragma once

#include <string>
#include <map>
using namespace std;

class Person
{
public:
    static Person* currentUser;
    
    Person(string userName, string password);

    void editUserName();
    void editPassword();
    bool checkPassword(string password,Person* p);
    bool static checkValidPassword(string password);
    static void addPerson(string userName, string password);
    static Person *getUserByName(string userName);
    ~Person();

private:
    static map<string, Person*> personStore; // hash every username with it's object
    bool admin;
    string userName;
    string password;
};

#endif