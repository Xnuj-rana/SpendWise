#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    int id;
    std::string type;
    double amount;
    std::string category;
    std::string date;
    std::string description;

public:
    Transaction(int id, const std::string& type, double amount,
                const std::string& category, const std::string& date,
                const std::string& description);

    int getId() const;
    std::string getType() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getDate() const;
    std::string getDescription() const;

    void display() const;
    std::string toFileLine() const;
};

#endif
