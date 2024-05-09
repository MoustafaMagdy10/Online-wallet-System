#include "Menu.h"
#include "Person.h"
#include "Admin.h"
#include "User.h"
#include "Logs.h"
#include "UserMenu.h"
#include "imgui.h"
#include <chrono>
#include <thread>

map<string, Person *> Person::personStore;
Person *Person::currentPerson = nullptr;
User *User::currentUser = nullptr;
Admin *Admin::currentAdmin = nullptr;
Menu::Menu()
{
    if (Person::currentPerson == nullptr)
    {
        Logs();
    }
    else
    {
        if (User::currentUser != nullptr)
        {
            Menu::ShowCredential();
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
        ImGui::NewLine();

        if (ImGui::Button("logout"))
        {
            Logs::logOut();
        }
    }
}
void Menu::ShowCredential()
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
void Menu::SleepForSec(const std::string &message)
{
    auto startTime = std::chrono::steady_clock::now();
    auto endTime = startTime + std::chrono::milliseconds(1500);

    while (std::chrono::steady_clock::now() < endTime)
    {
        Menu::EndFrame();
        Menu::RenderFrame();
        ImGui::Begin("online wallet system", NULL, FLAG_FULLSCREEN_MODE | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
        ImGui::TextColored(ImVec4(0, 228, 48, 255), message.c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
void Menu::RenderFrame()
{
    BeginDrawing();
    ClearBackground(BLACK);
    rlImGuiBegin();
}

void Menu::EndFrame()
{
    ImGui::End();
    rlImGuiEnd();
    EndDrawing();
}

Menu::~Menu()
{
}