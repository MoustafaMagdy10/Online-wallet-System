#include "Admin.h"
Admin::Admin()
: Person()
{
    
}
Admin::Admin(const string &userName,const string &password)
: Person(userName,password)
{
    admin = true;
}

Admin::~Admin()
{

}