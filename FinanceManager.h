#ifndef FINANCE_MANAGER_H
#define FINANCE_MANAGER_H

#include "Transaction.h"
#include <vector>
#include <string>

class FinanceManager {
private:
    std::vector<Transaction> transactions;
    int nextId;
    const std::string fileName = "transactions.txt";

    void loadFromFile();
    void saveToFile() const;

public:
    FinanceManager();

    void addTransaction();
    void showTransactions() const;
    void showSummary() const;
};

#endif
