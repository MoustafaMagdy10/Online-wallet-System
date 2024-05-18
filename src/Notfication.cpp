#include "../include/Notfication.h"

Notification::Notification()
{
}
Notification::Notification(string sender, string recipient, string date, string type, bool role, double amount)
{
    this->sender = sender;
    this->recipient = recipient;
    this->date = date;
    this->type = type;
    this->role = role;
    this->amount = amount;
}

string Notification::getSender()
{
    return this->sender;
}
string Notification::getRecipient()
{
    return this->recipient;
}

string Notification::getMessage()
{
    string message;
    if (role == 0 and type == "request")
    {
         message = recipient + " has requested from you " + to_string(amount) + " pounds" + " on " + date;
    }
    else if(role == 0 and type == "send"){
         message = sender + "has sent to you "  + to_string(amount) + " pounds" + " on " + date;
    }
    else if(role == 1 and type == "send") {
        message = "An admin " + sender + " has sent to you " + to_string(amount) + " pounds" + " on " + date;
    }
    else if(role == 1 and type == "edit"){
        message = "An admin " + sender + " has edited your balance to " + to_string(amount) + " pounds" + " on " + date;
    }

    return message;
}
string Notification::getDate()
{
    return this->date;
}
string Notification::getType()
{
    return this->type;
}
bool Notification::getRole()
{
    return this->role;
}
double Notification::getAmount()
{
    return this->amount;
}

Notification::~Notification()
{
}