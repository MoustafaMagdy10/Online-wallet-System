#include "LinkedList.h"

// template <class T>

LinkedList::Node::Node()
{
    this->next = nullptr;
}

LinkedList::Node::Node(const string &name)
{
    this->value = name;
    this->next = nullptr;
}

void LinkedList::append(const string &name)
{

    Node *newnode = new Node(name);

    if (head == 0)
        head = tail = newnode;

    else
    {
        tail->next = newnode;
        tail = newnode;
    }
    count++;
}

void LinkedList::deleteAt(const int &n)
{

    Node *tmp = head;

    if (n == 0)
    {
        head = head->next;
        delete tmp;
    }

    else
    {
        for (int i = 0; i < n - 1; i++)
        {
            tmp = tmp->next;
        }

        Node *del = tmp->next;
        tmp->next = del->next;
        delete del;

        if (n == count - 1)
            tail = tmp;
    }
    count--;
}

string LinkedList::at(const int &n)
{
    Node *tmp = head;

    for (int i = 0; i < n; i++)
        tmp = tmp->next;

    return tmp->value;
}

void LinkedList::addSuggestion(const string &name)
{
    for (int i = 0; i < count; i++)
    {
        if (at(i) == name)
            deleteAt(i);
    }

    if (count == 5)
        deleteAt(0);

    append(name);
}

stack<string> LinkedList::getSuggestions()
{
    stack<string>suggestions;

    for (int i = 0; i < count; i++)
    {
       suggestions.push(at(i));
    }

    return suggestions;
}

LinkedList::LinkedList()
{
    head = tail = 0;
    count = 0;
}

LinkedList::~LinkedList()
{
        while (count != 0)
        deleteAt(0);
}