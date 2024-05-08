#include "Menu.h"
#include "Person.h"
#include "Admin.h"
#include "User.h"
#include "Logs.h"
// #include "UserMenu.h"
#include "imgui.h"

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
        if (ImGui::Button("Edit User Name"))
        {

            Person::currentPerson->editUserName();
        }
        if(ImGui::Button("Edit password")){
            Person::currentPerson->editPassword();
        }
        if(ImGui::Button("logout")){
            Logs::logOut();
        }
        //ImGui::Button("");
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