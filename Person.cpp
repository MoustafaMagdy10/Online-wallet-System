#include <iostream>
#include <stack>
#include "Person.h"
#include "imgui.h"
#include <vector>
#include "Menu.h"
#include <chrono>
#include <thread>
#include "Admin.h"
#include "User.h"

Person::Person() {}
Person::Person(const string &userName, const string &password)
{
    this->userName = userName;
    this->password = hashPassword(password);
}
Person::Person(const string &userName, const uint64_t &password)
{
    this->userName = userName;
    this->password = password;
}
void Person::addPerson(const string &userName, const string &password, const bool &role)
{
    if (role)
        Person::personStore[userName] = new Admin(userName, password);
    else
        Person::personStore[userName] = new User(userName, password);
}

Person *Person::getUserByName(const string &userName)
{
    map<string, Person *>::iterator temp;
    temp = personStore.find(userName);
    if (temp == personStore.end())
        return nullptr;
    return temp->second;
}
uint64_t Person::getPassword()
{
    return this->password;
}
void Person::editUserName()
{
    vector<char> userName(265);
    string _userName;
    bool done = false;
    bool wrongUserName = false;
    bool tooShort = true;

    ImVec2 windowSize = ImGui::GetWindowSize();
    float centerX = windowSize.x * 0.5f;
    float centerY = windowSize.y * 0.5f;

    ImGui::SetCursorPosX(centerX - ImGui::CalcTextSize("Log In").x * 0.5f - ImGui::GetStyle().FramePadding.x * 2);
    ImGui::SetCursorPosY(centerY - ImGui::CalcTextSize("Log In").y * 0.5f - ImGui::GetStyle().FramePadding.y * 2);

    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();

        ImGui::NewLine();
        ImGui::InputTextWithHint("Username", "enter the name you want to change", userName.data(), userName.size());

        _userName = userName.data();
        if (_userName.size() < 5)
            tooShort = true;
        else
            tooShort = false;

        if (tooShort)
            ImGui::Text("User name is too short , must be at least 5 characters long");

        ImGui::NewLine();
        if ((ImGui::Button("done") or ImGui::IsKeyPressed(ImGuiKey_Enter)) and !tooShort)
        {
            auto it = getUserByName(_userName);

            if (it != nullptr)
            {
                wrongUserName = true;
            }

            else
            {
                personStore.erase(this->userName);
                personStore[_userName] = currentPerson;
                currentPerson->userName = _userName;
                done = true;
            }
        }

        ImGui::NewLine();
        if (ImGui::Button("Back"))
        {
            done = true;
        }

        if (wrongUserName)
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "User name already exists");

        if (WindowShouldClose())
            Menu::safeEnd();
    }
}

string Person::getUserName()
{
    return this->userName;
}
void Person::ShowCredential()
{
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 700);
    ImGui::TextColored(ImVec4(0, 228, 48, 255), "Name: ");
    ImGui::SameLine();
    ImGui::Text(Person::currentPerson->getUserName().c_str());
    ImGui::NewLine();
}
bool Person::checkPassword(const string &password, const Person *p)
{
    uint64_t hash = hashPassword(password);
    return p->password == hash;
}
uint64_t Person::hashPassword(const string &password)
{
    uint64_t hash = 14695981039346656037ULL;
    for (auto c : password)
    {
        hash ^= static_cast<uint64_t>(c); // xor
        hash *= 1099511628211ULL;
    }
    return hash;
}
bool Person::checkValidPassword(const string &password)
{
    bool valid = true;
    if (password.size() < 8)
    {
        ImGui::Bullet();
        ImGui::SameLine();
        ImGui::Text("Password must be more then 8 characters\n");
        valid = false;
    }
    bool number = false, upperCase = false;
    for (auto i : password)
    {
        if (isupper(i))
            upperCase = true;
        if (i <= '9' and i >= '0')
            number = true;
        if (number and upperCase)
            break;
    }
    if (!number or !upperCase)
    {
        ImGui::Bullet();
        ImGui::SameLine();
        ImGui::Text("Password must contain a number and an uppercase letter\n");
        valid = false;
    }
    ImGui::NewLine();
    return valid;
}
void Person::editPassword()
{

    vector<char> password(265), password1(265), password2(265);
    string _password, _password2;
    bool done = false;
    int steps = 0;
    bool wrongPassword = false;

    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();

        switch (steps)
        {

        case 0:

            ImGui::NewLine();
            ImGui::InputTextWithHint("enter current password", "password", password.data(), password.size(), ImGuiInputTextFlags_Password);

            ImGui::NewLine();
            if (ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter))
            {
                _password = password.data();

                if (!checkPassword(_password, Person::currentPerson))
                {
                    wrongPassword = true;
                }

                else
                {
                    steps++;
                    wrongPassword = false;
                    _password.clear();
                }
            }

            if (wrongPassword)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Wrong password");
            }
            break;

        case 1:

            ImGui::NewLine();
            ImGui::InputTextWithHint("enter new password", "password", password1.data(), password1.size(), ImGuiInputTextFlags_Password);

            ImGui::NewLine();
            ImGui::InputTextWithHint("enter new password again", "password", password2.data(), password2.size(), ImGuiInputTextFlags_Password);

            _password = password1.data();
            _password2 = password2.data();

            if (_password2 != _password)
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "passwords don't matches");

            if (Person::checkValidPassword(_password) and (ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter)) and _password2 == _password)
            {
                done = true;
                Menu::SleepForSec("Password has been changed successfully :)");
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
// cin >> password;

// passed:
//     // cout << "enter the new password\n";
//     // cin >> password;
//     if (!checkValidPassword(_password))
//         goto passed;
//     string temp;
//     cout << "enter new password again\n";
//     cin >> temp;
//     if (temp != password)
//     {
//         goto passed;
//     }
//     currentPerson->password = hashPassword(_password);

bool Person::getAdminRole()
{
    return this->admin;
}
void Person::initializeUser()
{
    if (Person::currentPerson == nullptr)
        return;

    if (Person::currentPerson->admin == false)
    {

        User::currentUser = static_cast<User *>(Person::currentPerson);
        Admin::currentAdmin = nullptr;
    }
    else
    {
        Admin::currentAdmin = static_cast<Admin *>(Person::currentPerson);
        User::currentUser = nullptr;
    }
}
bool Person::isNumber(const string &s)
{
    for (auto c : s)
    {
        if (c < '0' or c > '9')
        {
            return false;
        }
    }
    return true;
}
Person::~Person()
{
    for (auto i : personStore)
    {
        delete i.second;
    }
    Person::personStore.clear();
    Person::currentPerson = nullptr;
}