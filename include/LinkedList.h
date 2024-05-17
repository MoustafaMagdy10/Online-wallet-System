#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#pragma once

#include <iostream>
#include<stack>
#include <string>

using namespace std;

class LinkedList
{
public:
    LinkedList();


    ~LinkedList();

    void addSuggestion(const string &name);
    stack<string> getSuggestions();

private:


    void append(const string &name);
    void deleteAt(const int &n);
    string at(const int &n);

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