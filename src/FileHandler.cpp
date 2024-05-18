#include "../include/FileHandler.h"

void FileHandler::readDataFromFile()
{
    fstream inputFile;
    inputFile.open("input.txt", ios::in);

    if (inputFile.is_open())
    {
        while (!inputFile.eof())
        {

            string username, role;
            u_int64_t password;

            inputFile >> username >> password >> role;
            if (role == "User")
            {
                Person::addPerson(username, password, 0);
                User *U = static_cast<User *>(Person::getUserByName(username));
                double balance;
                int suspended;
                inputFile >> balance >> suspended;
                U->setBalance(balance);
                U->setSuspended(suspended);
                int inboxSize;
                int transactionSize;
                int quickListSize;

                inputFile >> transactionSize;
                inputFile >> inboxSize;
                inputFile >> quickListSize; 

                string sender, recipient, date, type;
                double amount;
                bool role;

                stack<Transaction> transactions;
                stack<Notification> inbox;

                for (int i = 0; i < inboxSize; i++)
                {
                    inputFile >> sender >> recipient >> date >> type >> role >> amount;
                    Notification N(sender, recipient, date, type, role, amount);
                    U->Notify(N);
                }

                for (int i = 0; i < transactionSize; i++)
                {
                    inputFile >> sender >> recipient >> date >> type >> amount;
                    Transaction T(sender, recipient, date, type, amount);
                    U->addTransaction(T);
                }

    
                for (int i = 0; i < quickListSize; i++)
                {
                    string name;
                    inputFile >> name;
                    U->addSuggestion(name);
                }
            }
            else if (role == "Admin")
            {
                Person::addPerson(username, password, 1);
            }
        }
        inputFile.clear();
        inputFile.close();
    }
    return;
}

void FileHandler::writeDataToFile()
{
    fstream outputFile;
    outputFile.open("input.txt", ios::out);

    for (auto it = Person::personStore.begin(); it != Person::personStore.end(); it++)
    {
        outputFile << it->second->getUserName() << " " << it->second->getPassword() << " ";
        if (it->second->getAdminRole())
        {
            outputFile << "Admin" << endl;
        }
        else
        {
            outputFile << "User" << endl;
            User *U = static_cast<User *>(it->second);
            outputFile << U->getBalance() << " " << U->getSuspended() << endl;

            stack<Notification> inbox = U->getInbox();
            stack<Notification> inboxTemp;

            stack<Transaction> transactions = U->getTransactionHistory();
            stack<Transaction> transactionsTemp;

            stack<string> quickList = U->getQuickList(); 
            stack<string> quickListTemp;

            int inboxSize = inbox.size(), transactionSize = transactions.size() , quickListSize = quickList.size();
            outputFile << transactionSize << " " << inboxSize<<" "<<quickListSize << endl;  // size

            while (!inbox.empty())
            {
                inboxTemp.push(inbox.top());
                inbox.pop();
            }

            for (int i = 0; i < inboxSize; i++)
            {
                Notification N = inboxTemp.top();
                outputFile << N.getSender() << " " << N.getRecipient() << " " << N.getDate() << " " << N.getType() << " " << N.getRole() << " " << N.getAmount() << endl;
                inboxTemp.pop();
            }

            while (!transactions.empty())
            {
                transactionsTemp.push(transactions.top());
                transactions.pop();
            }

            for (int i = 0; i < transactionSize; i++)
            {
                Transaction T = transactionsTemp.top();
                outputFile << T.getSender() << " " << T.getRecipient() << " " << T.getTransactionDate() << " " << T.getType() << " " << T.getAmount() << endl;
                transactionsTemp.pop();
            }

            while(!quickList.empty()){
                quickListTemp.push(quickList.top());
                quickList.pop();
            }

            for (int i = 0; i < quickListSize; i++)
            {
                outputFile <<quickListTemp.top() << " ";
                quickListTemp.pop();
            }
        }
    }
    outputFile.close();
    return;
}

stack<Transaction> FileHandler::readStackFromFile()
{
    fstream inputFile;
    inputFile.open("stack.txt", ios::in);

    if (inputFile.is_open())
    {

        stack<Transaction> transactions;
        int sz = 0;
        inputFile >> sz;

        for (int i = 0; i < sz; i++)
        {
            string sender, recipient, date, type;
            double amount;
            inputFile >> sender >> recipient >> date >> type >> amount;
            Transaction T(sender, recipient, date, type, amount);
            transactions.push(T);
        }
        inputFile.clear();
        inputFile.close();
        return transactions;
    }
    return stack<Transaction>();
}

void FileHandler::WriteStackIntoFile()
{
    fstream outputFile;
    outputFile.open("stack.txt", ios::out);
    stack<Transaction> transactions = Transaction::getTransactions();

    int sz = transactions.size();
    outputFile << sz << endl;

    for (int i = 0; i < sz; i++)
    {
        Transaction T = transactions.top();
        outputFile << T.getSender() << " " << T.getRecipient() << " " << T.getTransactionDate() << " " << T.getType() << " " << T.getAmount() << endl;
        transactions.pop();
    }

    outputFile.close();
    return;
}
