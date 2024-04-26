#include <string>
#include <chrono>
using namespace std;
class Transaction {
public:
    Transaction();
    Transaction(string sender, string recipient, double amount, string type);
    static string get_current_time();
    // void setSender(string sender);
    // void setRecipient(string recipient);
    void setAmount(double amount);
    void setType(string type);
    // void setTransactionnDate();
    string getType();
    string getSender();
    string getRecipient();
    double getAmount();
    string getTransactionnDate();
private:
    string sender;
    string recipient;
    string transactionDate;
    string type;
    double amount;
};