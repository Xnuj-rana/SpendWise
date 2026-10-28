#include "FinanceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

FinanceManager::FinanceManager() : nextId(1) {
    loadFromFile();
}

void FinanceManager::loadFromFile() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idText, type, amountText, category, date, description;

        if (!std::getline(ss, idText, '|') ||
            !std::getline(ss, type, '|') ||
            !std::getline(ss, amountText, '|') ||
            !std::getline(ss, category, '|') ||
            !std::getline(ss, date, '|') ||
            !std::getline(ss, description)) {
            continue;
        }

        try {
            int id = std::stoi(idText);
            double amount = std::stod(amountText);
            if (amount <= 0 || (type != "Income" && type != "Expense")) {
                continue;
            }

            transactions.emplace_back(id, type, amount, category, date, description);
            if (id >= nextId) {
                nextId = id + 1;
            }
        } catch (...) {
            continue;
        }
    }
}

void FinanceManager::saveToFile() const {
    std::ofstream file(fileName);
    for (const auto& transaction : transactions) {
        file << transaction.toFileLine() << '\n';
    }
}

void FinanceManager::addTransaction() {
    int choice;
    double amount;
    std::string category, date, description;

    std::cout << "\n1. Expense\n2. Income\nChoose type: ";
    if (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cout << "Invalid choice.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    std::cout << "Enter amount (INR): ";
    if (!(std::cin >> amount) || amount <= 0) {
        std::cout << "Amount must be a positive number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter category (e.g. Food, Travel, Salary): ";
    std::getline(std::cin, category);
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::getline(std::cin, date);
    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    if (category.empty() || date.empty()) {
        std::cout << "Category and date cannot be empty.\n";
        return;
    }

    std::string type = (choice == 1) ? "Expense" : "Income";
    transactions.emplace_back(nextId++, type, amount, category, date, description);
    saveToFile();

    std::cout << type << " added successfully!\n";
}

void FinanceManager::showTransactions() const {
    if (transactions.empty()) {
        std::cout << "\nNo transactions found yet.\n";
        return;
    }

    std::cout << '\n'
              << std::left
              << std::setw(5) << "ID"
              << std::setw(10) << "Type"
              << std::setw(12) << "Amount"
              << std::setw(16) << "Category"
              << std::setw(14) << "Date"
              << "Description\n";
    std::cout << std::string(75, '-') << '\n';

    for (const auto& transaction : transactions) {
        transaction.display();
    }
}

void FinanceManager::showSummary() const {
    double totalIncome = 0;
    double totalExpenses = 0;

    for (const auto& transaction : transactions) {
        if (transaction.getType() == "Income") {
            totalIncome += transaction.getAmount();
        } else {
            totalExpenses += transaction.getAmount();
        }
    }

    std::cout << "\n========== FINANCIAL SUMMARY ==========\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total income:   Rs. " << totalIncome << '\n';
    std::cout << "Total expenses: Rs. " << totalExpenses << '\n';
    std::cout << "Balance:        Rs. " << totalIncome - totalExpenses << '\n';
    std::cout << "=======================================\n";
}
