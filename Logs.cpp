#include "Logs.h"
#include "Person.h"
#include "imgui.h"
#include "rlImGui.h"
#include <vector>
#include "Menu.h"
#include "User.h"
#include "Admin.h"

Logs::Logs()
{
    ImVec2 windowSize = ImGui::GetWindowSize();
    float centerX = windowSize.x * 0.5f;
    float centerY = windowSize.y * 0.5f;

    ImGui::SetCursorPosX(centerX - ImGui::CalcTextSize("Log In").x * 0.5f - ImGui::GetStyle().FramePadding.x * 2);
    ImGui::SetCursorPosY(centerY - ImGui::CalcTextSize("Log In").y * 0.5f - ImGui::GetStyle().FramePadding.y * 2);
    if (ImGui::Button("Log In", ImVec2(170, 70)))
    {
        logIn();
    }

    centerY -= 130;
    ImGui::SetCursorPosX(centerX - ImGui::CalcTextSize("Register").x * 0.5f - ImGui::GetStyle().FramePadding.x * 2 + 15);
    ImGui::SetCursorPosY(centerY - ImGui::CalcTextSize("Register").y * 0.5f - ImGui::GetStyle().FramePadding.y * 2);
    if (ImGui::Button("Register", ImVec2(170, 70)))
    {
        register_();
    }
    return;
}

void Logs::register_()
{

    vector<char> userName(15), password(20);
    bool done = false;
    bool wrongUser = false;
    bool duplicatedUserName = false;
    bool wrongPassword = true;
    string _userName, _password;
    int step = 0;
Person* it = nullptr;
    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();

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
                 it = Person::getUserByName(_userName);

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
                Person::currentPerson = Person::getUserByName(_userName);
                Person::initializeUser();
                done = true;
            }
            break;
        }

        if (WindowShouldClose())
            exit(0);
    }
    return;
}

void Logs::logIn()
{

    vector<char> userName(15), password(20);
    string _userName, _password;
    bool done = false;
    bool wrongUser = false;
    int steps = 0;
    bool wrongPassword = false;
    Person* it = nullptr;
    
    while (!done)
    {

        Menu::EndFrame();
        Menu::RenderFrame();

        switch (steps)
        {
        case 0:
            ImGui::InputText("Name", userName.data(), userName.size());
            _userName = userName.data();

            if (ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter))
            {
                _userName = userName.data();
                 it = Person::getUserByName(_userName);

                if (it == nullptr)
                {
                    wrongUser = true;
                }
                else
                {
                    steps++;
                }

                if (wrongUser)
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "No such user exists");
                break;

            case 1:

                ImGui::InputTextWithHint("enter your password", "password", password.data(), password.size(), ImGuiInputTextFlags_Password);

                if (ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter))
                {
                    _password = password.data();

                    if (!it->checkPassword(_password, it))
                    {
                        wrongPassword = true;
                    }

                    else
                    {
                        Person::currentPerson = Person::getUserByName(_userName);
                        Person::initializeUser();
                        done = true;
                    }
                }
                if (wrongPassword)
                {
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Wrong Password");
                }
            }
        }

        if (ImGui::Button("Back"))
        {
            done = true;
        }
        if (WindowShouldClose())
            exit(0);
    }
}

void Logs::logOut()
{
    Person::currentPerson = nullptr;
    User::currentUser = nullptr;
    Admin::currentAdmin = nullptr;
}
