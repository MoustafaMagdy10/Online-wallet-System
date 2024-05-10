#include "User.h"
#include "Menu.h"
#include "Admin.h"

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

        currentUser->ShowCredential();
        ImGui::NewLine();

        switch (step)
        {
        case 0:

            ImGui::InputDouble("Amount", &amount);

            if (amount > User::currentUser->getBalance())
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "No Sufficient Amount");
            }

            if (amount <= 0)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "enter valid amount");
            }

            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) and (amount <= User::currentUser->getBalance()) and amount > 0)
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

                if (it == nullptr or it->getAdminRole() == true or (_userName == Person::currentPerson->getUserName()))
                {
                    valid = false;
                }
                else
                {
                    auto it = Person::getUserByName(_userName);
                    User *recipient = static_cast<User *>(it);
                    recipient->setBalance((recipient->getBalance() + amount));
                    User::currentUser->setBalance(User::currentUser->getBalance() - amount);
                    Transaction T(User::currentUser->getUserName(), recipient->getUserName(), amount, "Transfer");
                    User::currentUser->addTransaction(T);
                    recipient->addTransaction(T);
                    done = true;
                    Menu::SleepForSec("Money has been sent successfully :)");
                }
            }
            if (!valid)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not a valid User");
            }
        }

        if (ImGui::Button("Back"))
        {
            return;
        }
        if (WindowShouldClose())
            exit(0);
    }
}

void User::requestMoney()
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

        currentUser->ShowCredential();
        ImGui::NewLine();

        switch (step)
        {
        case 0:

            ImGui::InputDouble("Amount You wish to request", &amount);

            if (amount <= 0)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "enter valid amount");
            }

            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) and balance > 0)
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

                if (it == nullptr or it->getAdminRole() == true or (_userName == Person::currentPerson->getUserName()))
                {
                    valid = false;
                }
                else
                {
                    auto it = Person::getUserByName(_userName);
                    User *recipient = static_cast<User *>(it);
                    string message = Person::currentPerson->getUserName() + " have requested from you " + to_string(amount) + " pounds.";
                    recipient->Notification(message);
                    done = true;
                    Menu::SleepForSec("Money has been requested successfully :)");
                }
            }
            if (!valid)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not a valid User");
            }
        }

        if (ImGui::Button("Back"))
        {
            return;
        }
        if (WindowShouldClose())
            exit(0);
    }
}
void User::ShowInbox()
{
    bool done = false;
    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();
        currentUser->ShowCredential();

        if (currentUser->inbox.empty())
        {

            ImGui::TextColored(ImVec4(0, 121, 241, 255), "No New Notifications");
        }
        else
        {
            stack<string> _inbox = currentUser->inbox;

            while (!_inbox.empty())
            {
                string message = _inbox.top();
                ImGui::TextColored(ImVec4(0, 121, 241, 255), message.c_str());
                _inbox.pop();
            }
        }

        ImGui::NewLine();
        ImGui::NewLine();

        if (ImGui::Button("Back"))
            done = true;

        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 700);

        if (ImGui::Button("Clear Inbox"))
        {
            while (!currentUser->inbox.empty())
                currentUser->inbox.pop();
        }

        if (WindowShouldClose())
            exit(0);
    }
}

void User::Notification(const string &message)
{
    inbox.push(message);
}
bool User::hasNotification()
{
    return !currentUser->inbox.empty();
}
void User::setSuspended(const bool &suspended)
{
    this->suspended = suspended;
}
bool User::getSuspended(){
    return this->suspended;
}
long double User::getBalance()
{
    return this->balance;
}
void User::setBalance(const double &balance)
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

void User::viewTransactionHistory()
{
    bool done = false;
    bool show = false;

    while (!done)
    {

        Menu::EndFrame();
        Menu::RenderFrame();
        currentUser->ShowCredential();

        if (User::currentUser->transactionHistory.empty())
        {
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "No Transactions yet :(");
        }
        else
        {
            stack<Transaction> history = User::currentUser->transactionHistory;

            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Transaction History");
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Sender");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 100);
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "recipient");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150);
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Date");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 100);
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Type");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 100);
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Amount");

            while (!history.empty())
            {
                ImGui::SetWindowFontScale(1.5f);

                ImGui::Text(history.top().getSender().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(250);

                ImGui::Text(history.top().getRecipient().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(450);

                ImGui::Text(history.top().getTransactionDate().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(650);

                ImGui::Text(history.top().getType().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(800);
                ImGui::Text(to_string(history.top().getAmount()).c_str());

                history.pop();

                ImGui::SetWindowFontScale(2.0f);
            }
            ImGui::NewLine();
        }
        if (ImGui::Button("Back"))
            done = true;

        if (WindowShouldClose())
            exit(0);
    }
}
void User::viewTransactionHistory(const User *user)
{
    bool done = false;
    bool show = false;

    while (!done)
    {

        Menu::EndFrame();
        Menu::RenderFrame();
        Admin::currentAdmin->ShowCredential();

        if (user->transactionHistory.empty())
        {
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "No Transactions yet :(");
        }
        else
        {
            stack<Transaction> history = user->transactionHistory;

            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Transaction History");
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Sender");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 100);
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "recipient");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150);
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Date");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 100);
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Type");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 100);
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Amount");

            while (!history.empty())
            {
                ImGui::SetWindowFontScale(1.5f);

                ImGui::Text(history.top().getSender().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(250);

                ImGui::Text(history.top().getRecipient().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(450);

                ImGui::Text(history.top().getTransactionDate().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(650);

                ImGui::Text(history.top().getType().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(800);
                ImGui::Text(to_string(history.top().getAmount()).c_str());

                history.pop();

                ImGui::SetWindowFontScale(2.0f);
            }
            ImGui::NewLine();
        }
        if (ImGui::Button("Back"))
            done = true;

        if (WindowShouldClose())
            exit(0);
    }
}
void User::viewTansForAdmin()
{
    stack<Transaction> history = this->transactionHistory;

    cout << "Sender            recipient           Date            Type            amount\n";
    while (!history.empty())
    {
        cout << (history.top()).getSender() << "            " << history.top().getRecipient() << "            " << history.top().getTransactionDate() << "            " << history.top().getType() << "            " << history.top().getAmount() << "\n";
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

void User::ShowCredential()
{
    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::SetWindowFontScale(2.0f);
    ImGui::TextColored(ImVec4(0, 228, 48, 255), "Balance: ");
    ImGui::SameLine();
    ImGui::Text(to_string(User::currentUser->getBalance()).c_str());
    ImGui::SameLine();

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 350);
    ImGui::TextColored(ImVec4(0, 228, 48, 255), "Name: ");
    ImGui::SameLine();
    ImGui::Text(Person::currentPerson->getUserName().c_str());
    ImGui::NewLine();
}
User::~User()
{
}