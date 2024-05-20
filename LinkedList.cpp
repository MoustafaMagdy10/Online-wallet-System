#include "LinkedList.h"

LinkedList::Node::Node()
{
    this->next = nullptr;
}

LinkedList::Node::Node(const string &name)
{
    this->value = name;
    this->next = nullptr;
}

void LinkedList::addSuggestion(const string &name)
{

    if (Person::getUserByName(name) == nullptr)
        return;

    int x = count;
    Node *tmp = head;
    if (head && head->value == name)
    {
        head = head->next;
        delete tmp;
        count--;
    }
    else
    {
        while (tmp && tmp->next)
        {
            if (tmp->next->value == name)
            {
                Node *del = tmp->next;
                tmp->next = del->next;

                if (tail == del)
                {
                    tail = tmp;
                }

                delete del;
                count--;
            }
            tmp = tmp->next;
        }
    }

    tmp = head;
    if (count == 5)
    {
        head = head->next;
        delete tmp;
        count--;
    }

    Node *newNode = new Node(name);

    if (head == 0)
        head = tail = newNode;

    else
    {
        tail->next = newNode;

        tail = newNode;
    }
    count++;
}

stack<string> LinkedList::getSuggestions()
{
    stack<string> suggestions;

    Node *tmp = head;
    while (tmp)

    {
        if (Person::getUserByName(tmp->value) != nullptr)

            suggestions.push(tmp->value);
        tmp = tmp->next;
    }

    return suggestions;
}

int LinkedList::length()
{
    return count;
}
LinkedList::LinkedList()
{
    head = tail = 0;
    count = 0;
}

LinkedList::~LinkedList()
{

    while (head != nullptr)
    {

        Node *temp = head;
        head = head->next;

        delete temp;
        count--;
    }
}