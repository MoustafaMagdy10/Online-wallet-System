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
void Admin::viewAllUsers()
{

    bool done = false;
    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();

        ImGui::TextColored(ImVec4(0, 121, 241, 255), "Users:");

        for (auto &it : Person::personStore)
        {
            if (!it.second->admin)
            {
                User *user = static_cast<User *>(it.second);
                ImGui::Text(user->getUserName().c_str());
                ImGui::SameLine();
                ImGui::Text(":   ");
                ImGui::SameLine();
                ImGui::Text(to_string(user->getBalance()).c_str());
            }
        }
        ImGui::NewLine();
        ImGui::NewLine();

        if (ImGui::Button("Back"))
            done = true;

        if (WindowShouldClose())
            exit(0);
    }
}
void Admin::searchUser()
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
                if (ImGui::Selectable(it.second->getUserName().c_str()))
                {
                    User *user = static_cast<User *>(it.second);
                    user->viewTransactionHistory(user);
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
void Admin ::viewAllTransactions()
{

    bool done = false;
    while (!done)
    {

        Menu::EndFrame();
        Menu::RenderFrame();
        Admin::currentAdmin->ShowCredential();

        stack<Transaction *> transactions;
        // Transaction T;
        // transactions = T.getAllTransactions();
        transactions = Transaction::transactionStore;

        if (transactions.empty())
        {
            ImGui::TextColored(ImVec4(0, 121, 241, 255), "No Transactions:");
        }
        else
        {
            while (!transactions.empty())
            {
                ImGui::SetWindowFontScale(1.5f);

                ImGui::Text(transactions.top()->getSender().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(250);

                ImGui::Text(transactions.top()->getRecipient().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(450);

                ImGui::Text(transactions.top()->getTransactionDate().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(650);

                ImGui::Text(transactions.top()->getType().c_str());
                ImGui::SameLine();
                ImGui::SetCursorPosX(800);
                ImGui::Text(to_string(transactions.top()->getAmount()).c_str());

                transactions.pop();
            }
        }

        ImGui::NewLine();

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

                        user->setBalance(amount);
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
            if (_userName.size() < 8)
            {
                ImGui::Text("Username should be more then 8 characters long");
                wrongUser = true;
            }
            else
                wrongUser = false;

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
        case 2:
            Admin::currentAdmin->editUserBalance();
        }

        if (ImGui::Button("Back"))
        {
            return;
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
                    Person::personStore.erase(it.second->getUserName());
                    Menu::SleepForSec("User has been deleted successfully :)");
                    done = true;
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
                if (ImGui::Selectable(it.second->getUserName().c_str()))
                {
                    User *user = static_cast<User *>(it.second);
                    user->setSuspended(true);
                    Menu::SleepForSec("User has been suspended successfully :)");
                    done = true;
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
Admin::~Admin()
{
}