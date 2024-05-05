#ifndef MENU_H
#define MENU_H

#pragma once

#include <unordered_set>

class Menu
{
public:
    Menu();
    ~Menu();

private:
    unordered_set<string>st{"1","2","3","4","5","6","7","8","9"};
};

#endif