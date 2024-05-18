#ifndef PERSON_H
#define PERSON_H

#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <cstdint>
#include <iostream>
#include <stack>
#include <vector>
#include <chrono>
#include <thread>

#include "imgui.h"
#include "LinkedList.h"

using namespace std;

class Person
{
public:
    static Person *currentPerson;

    Person();
    Person(const string &userName, const string &password);
    Person(const string &userName, const uint64_t &password);

    static void addPerson(const string &userName, const uint64_t &password, const bool &role);
    static void addPerson(const string &userName, const string &password, const bool &role);
    static void initializeUser();

    void editUserName();
    void editPassword();
    bool checkPassword(const string &password, const Person *p);
    bool static checkValidPassword(const string &password);
    uint64_t hashPassword(const string &password);


    virtual void ShowCredential();


    static Person *getUserByName(const string &userName);
    bool getAdminRole();
    uint64_t getPassword();
    string getUserName();

    ~Person();

    static void clean();

    static map<string, Person *> personStore; // hash every username with it's object

protected:
    bool admin = false;

private:
    string userName;
    uint64_t password;
};

#endif