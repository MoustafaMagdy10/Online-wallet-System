#include "Admin.h"

Admin::Admin(string userName, string password)
: Person(userName,password)
{
    admin = true;
}

Admin::~Admin()
{

}