#include "../include/raylib.h"
#include "../include/raymath.h"
#include "../include/imgui.h"
#include "../include/rlImGui.h"
#include "../include/Menu.h"
#include <string>
#include <vector>
#include <iostream>
#include "../include/Person.h"
#include "../include/User.h"
#include "../include/Admin.h"
#include "../include/FileHandler.h"

int main()
{

    FileHandler::readDataFromFile();
    stack<Transaction> st = FileHandler::readStackFromFile();

    while (!st.empty())
    {
        Transaction::addTransactionToStore(st.top());
        st.pop();
    }

    int width = 1024;
    int hight = 1024;
    InitWindow(width, hight, "Online Wallet System");
    SetTargetFPS(60);
    rlImGuiSetup(true);

    while (!WindowShouldClose())
    {

        Menu::RenderFrame();

        // ImGui::SetNextWindowPos(ImVec2(GetWindowPosition().x, GetWindowPosition().y));
        // ImGui::SetNextWindowSize(ImVec2(GetScreenWidth(), GetScreenHeight()));
        Menu();
        // ImGui::SetNextWindowSize(ImVec2(1000, 600)); // Set the window size to 800x600 pixels
        // ImGui::ShowDemoWindow();
        Menu::EndFrame();
    }

    Menu::RenderFrame();

    if (WindowShouldClose())
    {
        Menu::safeEnd();
    }
}
