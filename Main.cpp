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
#include "Admin.h"
#include "FileHandler.h"

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

        Menu();
        Menu::EndFrame();
    }

    Menu::RenderFrame();

    if (WindowShouldClose())
    {
        Menu::safeEnd();
    }
}
