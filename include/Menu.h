#ifndef MENU_H
#define MENU_H

#pragma once

#include <unordered_set>
#include<string>
#include"imgui.h"
#include"raylib.h"
#include"rlImGui.h"


class Menu
{
public:
    Menu();
    static void RenderFrame();
    static void EndFrame();
    ~Menu();

private:
    std::unordered_set<std::string>st{"1","2","3","4","5","6","7","8","9"};
};

#endif