#include "FileHandler.h"
// Original
// void FileHandler::readDataFromFile(const string &filename)
// {
//     ifstream infile(filename);
//     // infile.open("DataMap", ios::trunc);

//     if (infile.is_open())
//     {
//         Person::personStore.clear(); // Clear existing data in the map

//         string key, username, role;
//         uint64_t password;
//         // cout<<"begin of loop"<<endl;
//         while (infile >> key >> username >> password >> role)
//         {
//             if (role == "Admin")
//             {
//                 // Create and store Admin object
//                 Person::personStore[key] = new Admin(username, password);
//             }
//             else if (role == "User")
//             {
//                 // Read balance
//                 double balance;
//                 infile >> balance;

//                 // Create User object
//                 User *user = new User(username, password);
//                 user->setBalance(balance);

//                 // Read transaction details
//                 string marker;
//                 infile >> marker;
//                 if (marker != "BeginningOfTransactions")
//                 {
//                     cerr << "Error: Expected marker 'whileForTransactions' not found." << endl;
//                     break; // Exit loop or handle error appropriately
//                 }

//                 // Read transactions until the marker is encountered again or end of file
//                 while (true)
//                 {
//                     string sender, recipient, type, date, check;
//                     double amount;
//                     infile >> sender;
//                     using namespace std;
//                     if (sender == "EndOfTransactions")
//                     {
//                         break; // End of transactions for this user
//                     }
//                     infile >> recipient >> type >> amount >> check;
//                     getline(infile >> ws, date); // Read remaining part of the line (including spaces) into date
//                     // Create Transaction object
//                     Transaction transaction(sender, recipient, date, type, amount);
//                     // Add transaction to user
//                     user->addTransaction(transaction);
//                 }
//                 string stackBegin, stackEnd, inboxString;
//                 infile >> stackBegin;
//                 if (stackBegin == "beginOfStrings")
//                 {
//                     while (infile >> inboxString)
//                     {
//                         if (inboxString == "endOfStrings")
//                         {
//                             break;
//                         }
//                         user->addForInbox(inboxString);
//                     }
//                 }
//                 int suspend;
//                 infile >> suspend;
//                 user->setSuspended(suspend);
//                 // Store User object
//                 Person::personStore[key] = user;
//             }
//         }
//         cout << "Data read from file." << endl;
//     }
//     else
//     {
//         cerr << "Error: Unable to open file for reading." << endl;
//     }

//     // if(infile.is_open())
//     infile.close();

// }

// // For Modified
// void FileHandler::writeDataToFile(const string &filename)
// {
//     ofstream outfile(filename);
//     // outfile.open("DataMap", ios::trunc);

//     if (outfile.is_open())
//     {
//         for (const auto &pair : Person::personStore)
//         {
//             outfile << pair.first << " "                  // Key (username)
//                     << pair.second->getUserName() << " "  // User name
//                     << pair.second->getPassword() << " "; // Password
//                                                           // cout<<"done"<<endl;
//             if (pair.second != nullptr && !pair.second->getAdminRole())
//             {
//                 User *user = static_cast<User *>(pair.second);

//                 outfile << "User ";            // Role
//                 outfile << user->getBalance(); // Write balance
//                 // Write transaction history
//                 stack<Transaction> history = user->getTransactionHistory();
//                 outfile << endl
//                         << "BeginningOfTransactions" << endl;
//                 while (!history.empty())
//                 {
//                     Transaction t = history.top();
//                     outfile << " " << t.getSender() << " " << t.getRecipient() << " " << t.getType() << " " << t.getAmount() << " " << " " << "check" << " " << t.getTransactionDate();
//                     history.pop();
//                 }
//                 outfile << "EndOfTransactions" << endl;
//                 outfile << "beginOfStrings" << endl;
//                 stack<string> inbox = user->getInbox();
//                 if (inbox.size() > 0)
//                 {
//                     while (!inbox.empty())
//                     {
//                         outfile << inbox.top() << " ";
//                         inbox.pop();
//                     }
//                 }

//                 outfile << "endOfStrings" << endl;
//                 outfile << user->getSuspended() << endl;
//             }
//             else
//             {
//                 outfile << "Admin" << endl; // Role for admin
//             }
//         }
//         outfile << "endOfMap" << endl;
//     }
//     else
//     {
//         cerr << "Error: Unable to open file for writing." << endl;
//     }

//     // if (outfile.is_open())
//         outfile.close();
// }

// void FileHandler::WriteStackIntoFile(const string &name)
// {

//     ofstream outfile(name);
//     // outfile.open("DataStack", ios::trunc);
//     if (outfile.is_open())
//     {
//         stack<Transaction> st = Transaction::getTransactions();
//         while (!st.empty())
//         {
//             Transaction t = st.top();
//             outfile << t.getSender() << " " << t.getRecipient() << " " << t.getType() << " " << t.getAmount() << " " << t.getTransactionDate();
//             st.pop();
//         }
//         outfile << "endOfStack" << endl;
//         // outfile.close();
//         cout << "Data written to file." << endl;
//     }
//     else
//     {
//         cerr << "Error: Unable to open file for writing." << endl;
//     }

//     // if (outfile.is_open())
//         outfile.close();
// }
// stack<Transaction> FileHandler::readStackFromFile(const string &filename)
// {
//     stack<Transaction> transactionsStack;
//     ifstream infile(filename);
//     // infile.open("DataStack", ios::trunc);
//     if (infile.is_open())
//     {
//         string line;
//         while (getline(infile, line))
//         {
//             if (line == "endOfStack")
//             {
//                 break; // End of transactions
//             }
//             istringstream iss(line);
//             string sender, recipient, type, date;
//             double amount;
//             iss >> sender >> recipient >> type >> amount >> date;
//             // Construct Transaction object and push it onto stack
//             Transaction transaction(sender, recipient, date, type, amount);
//             transactionsStack.push(transaction);
//         }
//         // infile.close();
//     }
//     else
//     {
//         cerr << "Error: Unable to open file for reading." << endl;
//     }
//     // if (infile.is_open())
//         infile.close();
//     return transactionsStack;
// }

void FileHandler::readDataFromFile()
{
    fstream inputFile;
    inputFile.open("input.txt", ios::in);

    if (inputFile.is_open())
    {
        while (!inputFile.eof())
        {

            string username, password, role;
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
                inputFile >> transactionSize;
                string message;

                while (message != "endOfStrings")
                {
                    if (message == "endOfStrings")
                        break;
                    getline(inputFile, message);
                    U->addForInbox(message);
                }
                // inputFile >> transactionSize;
                for (int i = 0; i < transactionSize; i++)
                {
                    string sender, recipient, date, type;
                    double amount;
                    inputFile >> sender >> recipient >> date >> type >> amount;
                    Transaction T(sender, recipient, date, type, amount);
                    U->addTransaction(T);
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
            stack<string> inbox = U->getInbox();
            // outputFile << inbox.size() << " ";

            stack<Transaction> transactions = U->getTransactionHistory();
            outputFile << transactions.size() << endl;
            while (!inbox.empty())
            {
                outputFile << inbox.top() << endl;
                inbox.pop();
            }
            outputFile << "endOfStrings" << endl;
            while (!transactions.empty())
            {
                Transaction T = transactions.top();
                outputFile << T.getSender() << " " << T.getRecipient() << " " << T.getTransactionDate() << " " << T.getType() << " " << T.getAmount() << endl;
                transactions.pop();
            }
        }
    }
    // outputFile.clear();
    outputFile.close();
    return;
}

stack<Transaction> FileHandler::readStackFromFile()
{
    fstream inputFile;
    inputFile.open("stack.txt", ios::in);
    stack<Transaction> transactions;
    if (inputFile.is_open())
    {
        while (!inputFile.eof())
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
    while (!transactions.empty())
    {
        Transaction T = transactions.top();
        outputFile << T.getSender() << " " << T.getRecipient() << " " << T.getTransactionDate() << " " << T.getType() << " " << T.getAmount() << endl;
        transactions.pop();
    }
    outputFile.clear();
    outputFile.close();
    return;
}
