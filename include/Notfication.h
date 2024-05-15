#ifndef NOTFICATION_H
#define NOTIFICATION_H

#pragma once

#include <iostream>
#include <string>
using namespace std;    
class Notification
{
public:

    Notification();
    Notification(string sender,string recipient,string date, string type, bool role , double amount);
    string getSender();
    string getRecipient();
    string getMessage();
    string getDate();
    string getType();
    bool getRole();
    double getAmount();
    ~Notification();


private:

    string sender;
    string message;
    string date;
    string type;
    string recipient;
    double amount;
    bool role;

};


#endif