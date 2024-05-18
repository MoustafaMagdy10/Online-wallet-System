#ifndef LOGS_H
#define LOGS_H

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Person.h"
#include "imgui.h"
#include "rlImGui.h"
#include "Menu.h"
#include "User.h"
#include "Admin.h"

using namespace std;

class Logs
{
public:
    Logs();
    void register_();
    void logIn();
    void static logOut();

private:
};

#endif