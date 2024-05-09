#include "User.h"
#include "Menu.h"

User::User(const string &userName, const string &password)
    : Person(userName, password)
{
    admin = false;
    balance = 0;
}

void User::sendMoney()
{

    vector<char> userName(265);
    double amount = 0;
    string _amount, _userName;
    bool done = false;
    bool valid = true;
    int step = 0;

    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();
        ImGui::Begin("online wallet system", NULL, FLAG_FULLSCREEN_MODE | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

        Menu::ShowCredintial();
        ImGui::NewLine();

        switch (step)
        {
        case 0:

            ImGui::InputDouble("Amount", &amount);

            if (amount > User::currentUser->getBalance())
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "No Sufficient Amount");
            }

            if (amount < 0)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "enter valid amount");
            }

            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) and (amount <= User::currentUser->getBalance()))
            {
                step++;
            }
            break;

        case 1:

            ImGui::InputTextWithHint("User name of recipient ", "User Name", userName.data(), userName.size());
            _userName = userName.data();

            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                auto it = Person::getUserByName(_userName);

                if (it == nullptr or it->getAdminRole() == true or(_userName==Person::currentPerson->getUserName()))
                {
                    valid = false;
                }
                else
                {
                    auto it = Person::getUserByName(_userName);
                    User *recipient = static_cast<User *>(it);
                    recipient->setBalance((recipient->getBalance() + amount));
                    User::currentUser->setBalance(User::currentUser->getBalance() - amount);
                    done = true;
                    Menu::SleepForSec("Money has been sent successfully :)");
                }
            }
            if (!valid)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not a valid User");
            }
        }

        if(ImGui::Button("Back")){
            return;
        }
        if (WindowShouldClose())
            exit(0);
    }
    //     long double amount = 0;
    // amountGetter:
    //     cout << "Enter the amount you want to send:\n";
    //     cin >> amount;
    //     if (amount <= 0)
    //     {
    //         cout << "please enter a valid amount:\n";
    //         goto amountGetter;
    //     }
    //     else if (currentUser->balance < amount)
    //     {
    //         cout << "No sufficient balance\n";
    //     }

    //     auto it = Person::getUserByName(recipientUsername);
    //         cout << "No such a user exists\n";
    //         return;
    //     }

    //     User *recipient = static_cast<User *>(it);

    //     recipient->addMoney();
}

// void User::requestMoney(string senderUsername, double amount)
// {
// }

long double User::getBalance()
{
    return this->balance;
}
void User::setBalance(double balance)
{
    this->balance = balance;
}

stack<Transaction> User::getTransactionHistory()
{
    return this->transactionHistory;
}
void User::addTransaction(Transaction transaction)
{
    this->transactionHistory.push(transaction);
}
void User::viewCurrrentBalance()
{
    double amount = this->getBalance();
    cout << "Your Current Balance is: " << amount << "\n";
}
void User::viewTansactionHistory()
{
    stack<Transaction> history = this->transactionHistory;
    cout << "Your Transaction History :\n";
    cout << "Sender            recipient           Date            Type            amount\n";
    while (!history.empty())
    {
        cout << (history.top()).getSender() << "            " << history.top().getRecipient() << "            " << history.top().getTransactionnDate() << "            " << history.top().getType() << "            " << history.top().getAmount() << "\n";
        history.pop();
    }
}
void User::viewTansForAdmin()
{
    stack<Transaction> history = this->transactionHistory;

    cout << "Sender            recipient           Date            Type            amount\n";
    while (!history.empty())
    {
        cout << (history.top()).getSender() << "            " << history.top().getRecipient() << "            " << history.top().getTransactionnDate() << "            " << history.top().getType() << "            " << history.top().getAmount() << "\n";
        history.pop();
    }
}

//  void User::addMoney()
//  {
//     double amount;
// repeatAmount:
//     cout << "Enter the amount of Money\n";
//     cin >> amount;
//     if (amount <= 0)
//     {
//         cout << "Invalid amount\n";
//         goto repeatAmount;
//     }
//     this->balance = this->balance + amount;
//     cout << "Money added successfully\n";
// }
// void User::logOut()
// {
//     cout << "You have successfully logged out\n";
//     exit(0);
// }

User::~User()
{
}