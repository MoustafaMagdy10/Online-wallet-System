#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include "Person.h"
#include "User.h"
#include"Admin.h"

class FileHandler
{
public:
    // FileHandler();
    // ~FileHandler();
    static void readDataFromFile(const string &filename);
    static void writeDataToFile(const string &filename);
    static stack<Transaction> readStackFromFile(const string &filename);
    static void WriteStackIntoFile(const string &name);

private:
};

#endif