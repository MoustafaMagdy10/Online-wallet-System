#include "User.h"

User::User(string userName,string password)
: Person(userName,password)
{
    admin = false;
}

User::~User()
{
    
}