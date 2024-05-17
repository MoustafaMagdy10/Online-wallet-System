#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include "Person.h"
#include "User.h"
#include"Admin.h"
#include"Transaction.h"

class FileHandler
{
public:
    static void readDataFromFile();
    static void writeDataToFile();
    static stack<Transaction> readStackFromFile();
    static void WriteStackIntoFile();

private:
};

#endif