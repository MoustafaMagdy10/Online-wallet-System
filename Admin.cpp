#include "Admin.h"
#include "Menu.h"

Admin::Admin()
    : Person()
{
}
Admin::Admin(const string &userName, const string &password)
    : Person(userName, password)
{
    admin = true;
}

Admin::Admin(const string &userName, const uint64_t &password)
    :Person(userName,password)
{
    admin = true;
}

void Admin::viewAllUsers()
{
    bool done = false;
    vector<char> userName(15);
    string _userName;

    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();

        bool notFound = true;
        ImGui::InputTextWithHint("User Name", "Search User", userName.data(), userName.size());
        _userName = userName.data();
        ImGui::NewLine();

        for (auto &it : Person::personStore)
        {
            if (!it.second->admin and (it.first.find(_userName) != string::npos or _userName.empty()))
            {
                notFound = false;
                User *user = static_cast<User *>(it.second);
                if (ImGui::Selectable(it.second->getUserName().c_str()))
                {
                    user->viewTransactionHistory(user);
                }
                ImGui::SameLine();
                ImGui::SetCursorPosX(700);
                ImGui::Text(to_string(user->getBalance()).c_str());
            }
        }
        if (notFound)
        {
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "No User With This Name");
        }
        ImGui::NewLine();

        if (ImGui::Button("Back"))
            done = true;

        if (WindowShouldClose())
            exit(0);
    }
}
void Admin ::viewAllTransactions()
{

    bool done = false;
    while (!done)
    {

        Menu::EndFrame();
        Menu::RenderFrame();
        Admin::currentAdmin->ShowCredential();

        stack<Transaction> transactionStore;

        transactionStore = Transaction::getTransactions();

        if (transactionStore.empty())
        {
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "No Transactions:");
        }
        else
        {

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

            while (!transactionStore.empty())
            {
                ImGui::NewLine();
                ImGui::SetWindowFontScale(1.5f);

                ImGui::Text(transactionStore.top().getSender().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(250);

                ImGui::Text(transactionStore.top().getRecipient().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(450);

                ImGui::Text(transactionStore.top().getTransactionDate().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(650);

                ImGui::Text(transactionStore.top().getType().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(800);
                ImGui::Text(to_string(transactionStore.top().getAmount()).c_str());

                transactionStore.pop();
            }

            ImGui::NewLine();
        }
        if (ImGui::Button("Back"))
            done = true;

        if (WindowShouldClose())
            exit(0);
    }
}
void Admin::editUserBalance()
{

    bool done = false;
    int steps = 0;
    double amount = 0;
    vector<char> userName(10);
    string _userName;
    bool notFound = true;

    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();

        Admin::currentAdmin->ShowCredential();

        switch (steps)
        {
        case 0:
            ImGui::InputDouble("amount to add for user", &amount);
            if (amount <= 0)
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not a valid amount");

            ImGui::SetCursorPosX(700);

            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) and amount > 0)
                steps++;

            break;

        case 1:
            ImGui::InputTextWithHint("User Name", "Search User", userName.data(), userName.size());
            _userName = userName.data();
            ImGui::NewLine();

            for (auto &it : Person::personStore)
            {
                if (!it.second->admin and (it.first.find(_userName) != string::npos or _userName.empty()))
                {
                    notFound = false;
                    if (ImGui::Selectable(it.second->getUserName().c_str()))
                    {
                        User *user = static_cast<User *>(it.second);

                        string type = amount >= user->getBalance() ? "Money Added" : "Money Deducted";
                        double _amount = abs(user->getBalance() - amount);

                        string AdminName = "Admin " + Admin::currentAdmin->getUserName();
                        Transaction T(AdminName, user->getUserName(), _amount, type);
                        T.addTransactionToStore(T);
                        user->setBalance(amount);
                        user->addTransaction(T);
                        user->Notify("An admin has changed your balance");
                        Menu::SleepForSec("Money set successfully :)");
                        done = true;
                    }
                }
            }
            if (notFound)
            {
                ImGui::TextColored(ImVec4(0, 121, 241, 255), "No User With This Name");
                ImGui::NewLine();
            }

            break;
        }

        notFound ? ImGui::SameLine() : ImGui::NewLine();
        ImGui::SetCursorPosX(0);

        if (ImGui::Button("Back"))
            done = true;

        if (WindowShouldClose())
            exit(0);
    }
}

void Admin::addUserBalance()
{
    bool done = false;
    int steps = 0;
    double amount = 0;

    vector<char> userName(10);
    string _userName;
    bool notFound = true;
    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();
        Admin::currentAdmin->ShowCredential();
        switch (steps)
        {
        case 0:
            ImGui::InputDouble("amount to add for user", &amount);
            if (amount <= 0)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not a valid amount");

            }
                ImGui::SetCursorPosX(700);
            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) and amount > 0)
                steps++;
            break;
        case 1:
            ImGui::InputTextWithHint("User Name", "Search User", userName.data(), userName.size());
            _userName = userName.data();
            ImGui::NewLine();
            for (auto &it : Person::personStore)
            {
                if (!it.second->admin and (it.first.find(_userName) != string::npos or _userName.empty()))
                {
                    notFound = false;
                    if (ImGui::Selectable(it.second->getUserName().c_str()))
                    {
                        User *user = static_cast<User *>(it.second);
                        string adminName = "admin:" + Admin::currentAdmin->getUserName();

                        Transaction T(adminName, user->getUserName(), amount, "Money Added");
                        T.addTransactionToStore(T);
                        user->setBalance(amount + user->getBalance());
                        user->addTransaction(T);
                        user->Notify("An admin has changed your balance");
                        Menu::SleepForSec("Money added successfully :)");
                    }
                }
            }
            if (notFound)
            {
                ImGui::TextColored(ImVec4(0, 121, 241, 255), "No User With This Name");
                ImGui::NewLine();
            }

            break;
        }

        notFound ? ImGui::SameLine() : ImGui::NewLine();
        ImGui::SetCursorPosX(0);

        if (ImGui::Button("Back"))
            done = true;

        if (WindowShouldClose())
            exit(0);
    }
}
void Admin::addUser()
{
    vector<char> userName(15), password(20);
    bool done = false;
    bool wrongUser = false;
    bool duplicatedUserName = false;
    bool wrongPassword = true;
    string _userName, _password;
    int step = 0;

    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();
        Admin::currentAdmin->ShowCredential();

        switch (step)
        {
        case 0:

            ImGui::InputText("Name", userName.data(), userName.size());
            _userName = userName.data();
            if (_userName.size() < 5)
            {
                ImGui::Text("Username should be more then 5 characters long");
                wrongUser = true;
            }
            else
                wrongUser = false;

            ImGui::NewLine();
            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) and !wrongUser)
            {

                _userName = userName.data();
                auto it = Person::getUserByName(_userName);

                if (it == nullptr)
                {
                    step++;
                }
                else
                {
                    duplicatedUserName = true;
                }
            }
            if (duplicatedUserName)
                ImGui::Text("User name already exists");
            break;

        case 1:
            ImGui::InputText("Password", password.data(), password.size(), ImGuiInputTextFlags_Password);
            _password = password.data();
            if (Person::checkValidPassword(_password))
                wrongPassword = false;
            if ((ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) and !wrongPassword)
            {

                Person::addPerson(_userName, _password, false);
                done = true;
            }
            break;
        }

        ImGui::NewLine();
        if (ImGui::Button("Back"))
        {
           done = true;
        }

        if (WindowShouldClose())
            exit(0);
    }
}

void Admin::deleteUser()
{
    bool done = false;
    vector<char> userName(15);
    string _userName;
    bool userToBeDeleted = false;
    User *U = nullptr;
    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();

        bool notFound = true;
        ImGui::InputTextWithHint("User Name", "Search User", userName.data(), userName.size());
        _userName = userName.data();
        ImGui::NewLine();

        for (auto &it : Person::personStore)
        {
            if (!it.second->admin and (it.first.find(_userName) != string::npos or _userName.empty()))
            {
                notFound = false;
                if (ImGui::Selectable(it.second->getUserName().c_str()))
                {
                    _userName = it.first;
                    userToBeDeleted = true;
                    break;
                }
            }
        }

        if (userToBeDeleted)
        {
            bool toDo = Menu::WarningMessage(_userName,"Delete");
            if(!toDo) continue;

            auto it = getUserByName(_userName);
            personStore.erase(_userName);
            //  delete it;
            // it = nullptr;
            userToBeDeleted = false;
            Menu::SleepForSec("User has been deleted successfully :)");
        }
        if (notFound)
        {
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "No User With This Name");
        }
        ImGui::NewLine();

        if (ImGui::Button("Back"))
            done = true;

        if (WindowShouldClose())
            exit(0);
    }
}

void Admin::suspendUser()
{
    bool done = false;
    vector<char> userName(15);
    string _userName;

    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();

        bool notFound = true;
        ImGui::InputTextWithHint("User Name", "Search User", userName.data(), userName.size());
        _userName = userName.data();
        ImGui::NewLine();

        for (auto &it : Person::personStore)
        {
            if (!it.second->admin and (it.first.find(_userName) != string::npos or _userName.empty()))
            {
                notFound = false;
                User *user = static_cast<User *>(it.second);
                if (user->getSuspended())
                    continue;

                if (ImGui::Selectable(it.second->getUserName().c_str()))
                {
                    bool toDo = Menu::WarningMessage(user->getUserName(), "Suspend");

                    if (toDo)
                    {
                        user->setSuspended(true);
                        Menu::SleepForSec("User has been suspended successfully ");
                    }
                }
            }
        }
        if (notFound)
        {
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "No User With This Name");
        }
        ImGui::NewLine();

        if (ImGui::Button("Back"))
            done = true;

        if (WindowShouldClose())
            exit(0);
    }
}
void Admin::ActivateUser()
{
    bool done = false;
    vector<char> userName(15);
    string _userName;
    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();
        bool notFound = true;
        ImGui::InputTextWithHint("User Name", "Search User", userName.data(), userName.size());
        _userName = userName.data();
        ImGui::NewLine();

        for (auto &it : Person::personStore)
        {

            if (!it.second->admin and (it.first.find(_userName) != string ::npos or _userName.empty()))
            {
                notFound = false;
                User *user = static_cast<User *>(it.second);
                if (user->getSuspended() && ImGui::Selectable(it.second->getUserName().c_str()))
                {

                    bool todo = Menu::WarningMessage(user->getUserName(), "activate");
                    if (todo)
                    {

                        user->setSuspended(false);
                        Menu::SleepForSec("User has been activated successfully ");
                    }
                }
            }
        }

        if (notFound)
        {
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "No User With This Name");
        }

        if (ImGui::Button("Back"))
            done = true;

        if (WindowShouldClose())
            exit(0);
    }
}
Admin::~Admin()
{
}