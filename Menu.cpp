#include "Menu.h"

map<string, Person *> Person::personStore;
Person *Person::currentPerson = nullptr;
User *User::currentUser = nullptr;
Admin *Admin::currentAdmin = nullptr;

Menu::Menu()
{
    if (User::currentUser != nullptr and User::currentUser->getSuspended())
    {
        User::currentUser->ShowCredential();
        ImGui::TextColored(ImVec4(0, 121, 241, 255), "Unfortunately, Your account has been suspended :(");
        ImGui::NewLine();

        if (ImGui::Button("logout"))
        {
            Logs::logOut();
        }
    }
    else if (Person::currentPerson == nullptr)
    {
        Logs();
    }
    else
    {
        if (User::currentUser != nullptr)
        {
            User::currentUser->ShowCredential();
        }
        else if (Admin::currentAdmin != nullptr)
        {
            Admin::currentAdmin->ShowCredential();
        }

        ImGui::NewLine();

        if (ImGui::Button("Edit User Name"))
        {

            Person::currentPerson->editUserName();
        }
        ImGui::NewLine();
        if (ImGui::Button("Edit password"))
        {
            Person::currentPerson->editPassword();
        }
        ImGui::NewLine();

        if (User::currentUser != nullptr)
        {
            if (ImGui::Button("Send Money"))
            {
                User::currentUser->sendMoney();
            }
            ImGui::NewLine();
            if (ImGui::Button("Request Money"))
            {
                User::currentUser->requestMoney();
            }
            ImGui::NewLine();
            if (ImGui::Button("Show Transactions History"))
            {
                User::currentUser->viewTransactionHistory();
            }
            ImGui::NewLine();
            if (ImGui::Button("Inbox"))
            {
                User::currentUser->ShowInbox();
            }

            if (User::currentUser->hasNotification())
            {
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                ImGui::Bullet();
                ImGui::PopStyleColor();
            }
            ImGui::NewLine();
        }
        else if (Admin::currentAdmin != nullptr)
        {
            if (ImGui::Button("View All Users"))
            {
                Admin::currentAdmin->viewAllUsers();
            }
            ImGui::NewLine();

            if (ImGui::Button("View All Transactions"))
            {
                Admin::currentAdmin->viewAllTransactions();
            }
            ImGui::NewLine();
            if (ImGui::Button("Edit User Balance"))
            {
                Admin::currentAdmin->editUserBalance();
            }
            ImGui::NewLine();
            if (ImGui::Button("Add User Balance"))
            {
                Admin::currentAdmin->addUserBalance();
            }
            ImGui::NewLine();
            if (ImGui::Button("Add User"))
            {
                Admin::currentAdmin->addUser();
            }
            ImGui::NewLine();
            if (ImGui::Button("Delete User"))
            {
                Admin::currentAdmin->deleteUser();
            }
            ImGui::NewLine();
            if (ImGui::Button("Suspend User"))
            {
                Admin::currentAdmin->suspendUser();
            }
            ImGui::NewLine();
            if (ImGui::Button("Activate User"))
            {
                Admin::currentAdmin->ActivateUser();
            }
        }
        ImGui::NewLine();

        if (ImGui::Button("logout"))
        {
            Logs::logOut();
        }
    }
}

void Menu::SleepForSec(const std::string &message)
{
    auto startTime = std::chrono::steady_clock::now();
    auto endTime = startTime + std::chrono::milliseconds(1500);

    while (std::chrono::steady_clock::now() < endTime)
    {
        Menu::EndFrame();
        Menu::RenderFrame();
        ImGui::TextColored(ImVec4(0, 228, 48, 255), message.c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Menu::RenderFrame()
{
    BeginDrawing();
    ClearBackground(BLACK);
    rlImGuiBegin();
    ImGui::Begin("online wallet system", NULL, FLAG_FULLSCREEN_MODE | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
    ImGui::SetWindowFontScale(2.0f);
}

bool Menu::WarningMessage(const std::string &name, const std::string &message)
{

    bool done = false;

    while (!done)
    {
        Menu::EndFrame();
        Menu::RenderFrame();

        ImGui::SetCursorPos(ImVec2(150, 300));
        string s = "Are You Sure You Want To " + message + " " + name;
        ImGui::TextColored(ImVec4(253, 249, 0, 255), s.c_str());
        ImGui::NewLine();
        ImGui::SetCursorPosX(200);

        if (ImGui::Button("cancel"))
        { 
            return false;
        }

        ImGui::SameLine();

        ImGui::SetCursorPosX(600);
        if (ImGui::Button("Yes"))
        {
            return true;
        }

        if (WindowShouldClose())
           Menu::safeEnd();
    }
}

void Menu::EndFrame()
{
    ImGui::End();
    rlImGuiEnd();
    EndDrawing();
}

void Menu::safeEnd()
{
    FileHandler::writeDataToFile();
    FileHandler::WriteStackIntoFile();
    exit(0);
}

Menu::~Menu()
{
}