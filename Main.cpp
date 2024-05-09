#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"
#include "Menu.h"
#include <string>
#include <vector>
#include <iostream>
#include "Person.h"
#include "User.h"
// using namespace std;
int main()
{
    int width = 1024;
    int hight = 1024;
    InitWindow(width, hight, "Online Wallet System");
    SetTargetFPS(60);

    bool showtext = false;
    std::string s;
    std::vector<char> buffer(6);
    rlImGuiSetup(true);
    char userName, password;
    bool done = false;
    Person::addPerson("Moustafa", "Moustafa2004", false);
    Person::currentPerson = Person::getUserByName("Moustafa");
    Person::addPerson("Musa", "Moustafa2004", false);
    Person::currentPerson = Person::getUserByName("Moustafa");
    User::currentUser = static_cast<User *>(Person::currentPerson);
    User::currentUser->setBalance(500);
    while (!WindowShouldClose())
    {

        Menu::RenderFrame();

        ImGui::SetNextWindowPos(ImVec2(GetWindowPosition().x, GetWindowPosition().y));
        ImGui::SetNextWindowSize(ImVec2(GetScreenWidth(), GetScreenHeight()));
        ImGui::Begin("online wallet system", NULL, FLAG_FULLSCREEN_MODE | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
        Menu();

        Menu::EndFrame();
    }
    rlImGuiShutdown();
    CloseWindow();
}
