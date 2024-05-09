#include "Logs.h"
#include "Person.h"
#include "imgui.h"
#include "rlImGui.h"
#include <vector>
#include "Menu.h"
Logs::Logs()
{

    // string login; // to login if 1 , register if 2
    // cout << "to login choose 1 , to register choose 2 \n";
    // cin.ignore('\n');
    // getline(cin,login);
    // if (login != "1" and login != "2")
    // {
    //     cout << "please choose a valid number\n";
    //     Logs();
    //     return;
    // }
    ImVec2 windowSize = ImGui::GetWindowSize();
    float centerX = windowSize.x * 0.5f;
    float centerY = windowSize.y * 0.5f;

    // Center the Log In button
    ImGui::SetCursorPosX(centerX - ImGui::CalcTextSize("Log In").x * 0.5f - ImGui::GetStyle().FramePadding.x * 2);
    ImGui::SetCursorPosY(centerY - ImGui::CalcTextSize("Log In").y * 0.5f - ImGui::GetStyle().FramePadding.y * 2);
    if (ImGui::Button("Log In", ImVec2(170, 70)))
    {
        logIn();
    }

    centerY -= 130;
    // Center the Register button
    ImGui::SetCursorPosX(centerX - ImGui::CalcTextSize("Register").x * 0.5f - ImGui::GetStyle().FramePadding.x * 2 + 15);
    ImGui::SetCursorPosY(centerY - ImGui::CalcTextSize("Register").y * 0.5f - ImGui::GetStyle().FramePadding.y * 2);
    if (ImGui::Button("Register", ImVec2(170, 70)))
    {
        register_();
    }
    return;
    // if (ImGui::Button("Log In"))
    // {
    //     logIn();
    // }
    // else if (ImGui::Button("Register"))
    // {
    //     register_();
    // }
}

void Logs::register_()
{

    //     string userName, password;
    //     string choice;

    //     cout << "Enter username:\n";
    //     cin.ignore();
    //     getline(cin, userName);

    // name:
    //     if (Person::getUserByName(userName) != nullptr)
    //     {
    //         cout << "name is already taken\n";
    //     choiceName:
    //         cout << "select 1 to enter username again , 2 to back:\n";
    //         cin >> choice;
    //         if (choice != "1" and choice != "2")
    //         {
    //             cout << "Enter a valid number:\n";
    //             goto choiceName;
    //         }
    //         if (choice == "2")
    //             return;
    //         cout << "Enter username:\n";
    //         cin.ignore(); // Ignore the newline character left in the input stream
    //         getline(cin, userName);
    //         goto name;
    //     }

    //     cout << "password must be more then 8 characters containing uppercase letter and a number:\n";
    //     cout << "Enter password:\n";
    //     getline(cin, password);
    // pass:
    //     if (!Person::checkValidPassword(password))
    //     {
    //     choicePass:
    //         string choice;
    //         cout << "select 1 to enter password again  , 2 to back:\n";
    //         cin >> choice;
    //         if (choice != "1" and choice != "2")
    //         {
    //             cout << "Enter a valid number:\n";
    //             goto choicePass;
    //         }
    //         if (choice == "2")
    //             return;
    //         cout << "Enter your password:\n";
    //         cin.ignore();
    //         getline(cin, password);
    //         goto pass;
    //     }
    vector<char> userName(265), password(265);
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
        // bool open = true;
        //     ImGui::ShowDemoWindow(&open);
        ImGui::Begin("online wallet system", NULL, FLAG_FULLSCREEN_MODE | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
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

    // cout << "bono bono" << endl;
}

void Logs::logIn()
{

    vector<char> userName(265), password(265);
    string _userName;
    bool done = false;
    bool wrongUser = false;

    while (!done)
    {

        Menu::EndFrame();
        Menu::RenderFrame();

        ImGui::Begin("online wallet system", NULL, FLAG_FULLSCREEN_MODE | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

        ImGui::InputText("Name", userName.data(), userName.size());

        if (ImGui::Button("Next") or ImGui::IsKeyPressed(ImGuiKey_Enter))
        {
            _userName = userName.data();
            auto it = Person::getUserByName(_userName);

            if (it == nullptr)
            {
                wrongUser = true;
            }
            else
            {
                Person::currentPerson = Person::getUserByName(_userName);
                Person::initializeUser();
                done = true;
            }
        }
        if (wrongUser)
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f),"No such user exists");

        if (WindowShouldClose())
            exit(0);
    }
    // // name:

    //         cout << "No such user:\n";
    //     choiceName:
    //         string choice;
    //         cout << "1 to enter username again , 2 to go back:\n";
    //         cin >> choice;
    //         if (choice != "1" and choice != "2")
    //         {
    //             cout << "Enter a valid number:\n";
    //             goto choiceName;
    //         }
    //         if (choice == "2")
    //             return;
    //         cout << "Enter your username:\n";
    //         cin.ignore();
    //         getline(cin, userName);
    //         goto name;
    //     }

    //     cout << "password must be more then 8 characters containing uppercase letter and a number:\n";
    //     cout << "Enter password:\n";
    //     getline(cin, password);

    // pass:
    //     if (!it->checkPassword(password, it))
    //     {
    //         cout << "passwords does not match:\n";
    //     choicePass:
    //         string choice;
    //         cout << "1 to enter password again  , 2 to go back:\n";
    //         cin >> choice;
    //         if (choice != "1" and choice != "2")
    //         {
    //             cout << "Enter a valid number:\n";
    //             goto choicePass;
    //         }
    //         if (choice == "2")
    //             return;
    //         cout << "Enter your password:\n";
    //         cin.ignore();
    //         getline(cin, password);
    //         goto pass;
    //     }

    //     Person::currentPerson = Person::getUserByName(userName);
    //     Person::initializeUser();
    //     cout << "bono bono\n";
}

void Logs::logOut()
{
    Person::currentPerson = nullptr;
    // User::currentUser = nullptr;
    // Admin::currentAdmin = nullptr;
}
