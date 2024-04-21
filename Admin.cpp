#include "Admin.h"
Admin::Admin()
: Person()
{
    
}
Admin::Admin(string userName, string password)
: Person(userName,password)
{
    admin = true;
}

Admin::~Admin()
{

}

