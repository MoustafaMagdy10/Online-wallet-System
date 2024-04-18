#ifndef LOGS_H
#define LOGS_H

#pragma once

#include<iostream>
#include <string>
using namespace std;

class Logs
{
public:
    Logs();
    bool register_(string userName , string Password);
    bool logIn(string userName , string Password);
    void static logOut();

private:

};

#endif