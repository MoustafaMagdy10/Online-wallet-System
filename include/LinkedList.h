#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#pragma once

#include <iostream>
#include <stack>
#include <string>

#include"Person.h"

using namespace std;

class LinkedList
{
public:
    LinkedList();

    void addSuggestion(const string &name);
    stack<string> getSuggestions();
    int length();

    ~LinkedList();

private:

    class Node
    {
    public:
        Node *next;
        string value;
        Node();
        Node(const string &name);
    };

    int count;
    Node *head;
    Node *tail;
};

#endif