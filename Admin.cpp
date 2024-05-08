#include "Admin.h"

Admin::Admin()
    : Person()
{
}
Admin::Admin(const string &userName, const string &password)
    : Person(userName, password)
{
    admin = true;
}
void Admin::ViewAllUsers()
{

    // User::currentUser = static_cast<User *>(Person::currentPerson);
    for (auto &person : Person::personStore)
    {
        if (!person.second->admin)
        {
            User *user = static_cast<User *>(person.second);

            cout << "Name:" << user->getUserName() << "       "
                 << "balance:" << user->getBalance() << endl;
        }
    }
    cout << "for more details Enter user name :\npress 0 to return ";
    string name;
    cin >> name;
    if (name == "0")
        menueAdmin();
    else
        ViewUser(name);
}
void Admin::ViewUser(string name)
{
    if (!personStore[name]->admin)
    {
        User *user = static_cast<User *>(personStore[name]);

        if (!user->getTransactionHistory().empty())
            user->viewTansactionHistory();
        else
            cout << "no transaction yet\n";
    }

    else
        cout << "invalid Name ";
}
void Admin ::ViewAlltransactions()
{
    int flag = 0;
    cout << "the transaction history:\n";
    for (auto &person : Person::personStore)
    {
        if (!person.second->admin)
        {
            User *user = static_cast<User *>(person.second);
            if (!user->getTransactionHistory().empty())
            {
                user->viewTansForAdmin();
                flag = 1;
            }
        }
    }
    if (flag == 0)
        cout << "no transaction yet\n";
}
void Admin::EditBalance()
{
    cout << "enter user name :";
    string name;
    cin >> name;
    int choice;
    auto it = Person::getUserByName(name);
    if (it == nullptr)
    {
        cout << "User not found\n";
        return;
    }

    User *user = static_cast<User *>(it);
    cout << "1-edit balance\n"
         << "2-add balance\n"
         << "Enter your choice:";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "enter the new balance:";
        double balance;
        cin >> balance;
        user->setBalance(balance);
        cout << "done:)\n";
        break;
    case 2:
        cout << "enter the amount to add:";
        double amount;
        cin >> amount;
        user->setBalance(amount + user->getBalance());
        cout << "done:)\n";
        break;
    default:
        cout << "invalid choice:(\n";
    }
}
void Admin::menueAdmin()
{
    cout << "1- view all transactions\n"
         << "2-veiw all registered users\n"
         << "3-edit balance for user\n";
    int choice;
    cin >> choice;
    switch (choice)
    {

    case 1:
        ViewAlltransactions();
        menueAdmin();
        break;
    case 2:
        ViewAllUsers();
        menueAdmin();
        break;
    case 3:
        EditBalance();
        menueAdmin();
        break;
    default:
        cout << "invalid choice;";
        menueAdmin();
        break;
    }
}

Admin::~Admin()
{
}