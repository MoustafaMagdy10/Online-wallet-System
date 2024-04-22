#include "User.h"

User::User(const string &userName,const string &password)
: Person(userName,password)
{
    admin = false;
}

User::~User()
{
}