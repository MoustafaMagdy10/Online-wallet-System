#ifndef MENU_H
#define MENU_H

#pragma once

#include <chrono>
#include <thread>
#include<string>

#include "Transaction.h"
#include"imgui.h"
#include"raylib.h"
#include"rlImGui.h"
#include "Person.h"
#include "Admin.h"
#include "User.h"
#include "Logs.h"
#include "FileHandler.h"
#include "imgui.h"



class Menu
{
public:
    Menu();
    static void RenderFrame();
    static void EndFrame();
    static void safeEnd();
    static bool WarningMessage(const std::string &name, const std::string &message);
    static void SleepForSec(const std::string &message);
    ~Menu();
};

#endif