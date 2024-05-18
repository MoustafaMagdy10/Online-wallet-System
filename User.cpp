#include "User.h"

User::User(const string &userName, const string &password)
    : Person(userName, password)
{
    admin = false;
    balance = 0;
    suspended = false;
}

User::User(const string &userName, const uint64_t &password)
    : Person(userName, password)
{
    admin = false;
    balance = 0;
    suspended = false;
}

void User::sendMoney()
{

    vector<char> userName(265);
    double amount = 0;
    string _amount, _userName;
    bool done = false;
    bool valid = true;
    bool go = false;
    int step = 0;
    bool suggestionExists = false;

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

            ImGui::NewLine();
            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) and (amount <= User::currentUser->getBalance()) and amount > 0)
            {
                step++;
            }
            break;

        case 1:

            ImGui::InputTextWithHint("User name of recipient ", "User Name", userName.data(), userName.size());
            _userName = userName.data();

            stack<string> _quickList = User::currentUser->getQuickList();

            ImGui::NewLine();
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Quick List:");

            while (!_quickList.empty())
            {

                auto P = getUserByName(_quickList.top());

                if (P != nullptr and P->getAdminRole() == false)
                {

                    User *U = static_cast<User *>(P);

                    if (U->getSuspended() == false)
                    {
                        if (ImGui::Selectable(_quickList.top().c_str()))
                        {
                            _userName = _quickList.top();
                            go = true;
                            break;
                        }
                        suggestionExists = true;
                        ImGui::NewLine();
                    }
                }

                _quickList.pop();
            }

            if (!suggestionExists)
            {

                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "No QuickList Yet");
            }

            ImGui::NewLine();
            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) or go)
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

                    if (recipient->getSuspended())
                    {
                        valid = false;
                        break;
                    }

                    recipient->setBalance((recipient->getBalance() + amount));
                    User::currentUser->setBalance(User::currentUser->getBalance() - amount);

                    Transaction T(User::currentUser->getUserName(), recipient->getUserName(), amount, "Transfer");
                    T.addTransactionToStore(T);

                    User::currentUser->addTransaction(T);
                    recipient->addTransaction(T);

                    Notification N(User::currentUser->getUserName(), recipient->getUserName(), T.get_current_time(), "send", 0, amount);
                    recipient->Notify(N);

                    User::currentUser->addSuggestion(recipient->getUserName());
                    Menu::SleepForSec("Money has been sent successfully :)");
                    done = true;
                    go = false;
                    userName.clear();
                }
            }
            if (!valid)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not a valid User");
            }
        }

        ImGui::NewLine();
        if (ImGui::Button("Back"))
        {
            done = true;
        }
        if (WindowShouldClose())
            Menu::safeEnd();
    }
}

void User::requestMoney()
{
    vector<char> userName(265);
    double amount = 0;
    string _amount, _userName;
    bool done = false;
    bool valid = true;
    bool go = false;
    int step = 0;
    bool suggestionExists = false;

    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();

        currentUser->ShowCredential();
        ImGui::NewLine();

        switch (step)
        {
        case 0:

            ImGui::NewLine();
            ImGui::InputDouble("Amount to request", &amount);

            if (amount <= 0)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "enter valid amount");
            }

            ImGui::NewLine();
            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) and amount > 0)
            {
                step++;
            }
            break;

        case 1:

            ImGui::InputTextWithHint("User name of recipient ", "User Name", userName.data(), userName.size());
            _userName = userName.data();

            stack<string> _quickList = User::currentUser->getQuickList();

            ImGui::NewLine();
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "Quick List:");

            while (!_quickList.empty())
            {

                auto P = getUserByName(_quickList.top());

                if (P != nullptr and P->getAdminRole() == false)
                {

                    User *U = static_cast<User *>(P);

                    if (U->getSuspended() == false)
                    {
                        if (ImGui::Selectable(_quickList.top().c_str()))
                        {
                            _userName = _quickList.top();
                            go = true;
                            break;
                        }
                        suggestionExists = true;
                        ImGui::NewLine();
                    }
                }

                _quickList.pop();
            }

            if (!suggestionExists)
            {

                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "No QuickList Yet");
            }

            ImGui::NewLine();
            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) or go)
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
                    if (recipient->getSuspended())
                    {
                        valid = false;
                        break;
                    }

                    Notification N(User::currentUser->getUserName(), recipient->getUserName(), Transaction::get_current_time(), "request", 0, amount);
                    recipient->Notify(N);

                    User::currentUser->addSuggestion(recipient->getUserName());
                    Menu::SleepForSec("Money has been requested successfully :)");

                    done = true;
                    go = false;
                    userName.clear();
                }
            }
            if (!valid)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not a valid User");
            }
        }

        ImGui::NewLine();
        if (ImGui::Button("Back"))
        {
            done = true;
        }
        if (WindowShouldClose())
            Menu::safeEnd();
    }
}
stack<Transaction> User::getTransactions()
{
    return this->transactionHistory;
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
            stack<Notification> _inbox = currentUser->inbox;

            while (!_inbox.empty())
            {
                Notification N = _inbox.top();
                string message = N.getMessage();
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
            Menu::safeEnd();
    }
}

void User::Notify(const Notification &N)
{
    this->inbox.push(N);
}

bool User::hasNotification()
{
    return !currentUser->inbox.empty();
}
void User::setSuspended(const bool &suspended)
{
    this->suspended = suspended;
}
bool User::getSuspended()
{
    return this->suspended;
}

void User::addSuggestion(const string &name)
{
    quickList.addSuggestion(name);
}

void User::clean()
{
    quickList.~LinkedList();
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
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150);
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
                ImGui::SetCursorPosX(850);
                ImGui::Text(to_string(history.top().getAmount()).c_str());

                history.pop();

                ImGui::SetWindowFontScale(2.0f);
            }
            ImGui::NewLine();
        }
        if (ImGui::Button("Back"))
            done = true;

        if (WindowShouldClose())
            Menu::safeEnd();
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
            Menu::safeEnd();
    }
}

stack<Notification> User::getInbox()
{
    return this->inbox;
}

stack<string> User::getQuickList()
{
    return quickList.getSuggestions();
}

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