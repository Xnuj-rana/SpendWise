#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Transaction::Transaction(int id, const std::string& type, double amount,
                         const std::string& category, const std::string& date,
                         const std::string& description)
    : id(id), type(type), amount(amount), category(category),
      date(date), description(description) {}

int Transaction::getId() const { return id; }
std::string Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
std::string Transaction::getCategory() const { return category; }
std::string Transaction::getDate() const { return date; }
std::string Transaction::getDescription() const { return description; }

void Transaction::display() const {
    std::cout << std::left
              << std::setw(5) << id
              << std::setw(10) << type
              << std::setw(12) << std::fixed << std::setprecision(2) << amount
              << std::setw(16) << category
              << std::setw(14) << date
              << description << '\n';
}

std::string Transaction::toFileLine() const {
    std::ostringstream line;
    line << id << '|'
         << type << '|'
         << std::fixed << std::setprecision(2) << amount << '|'
         << category << '|'
         << date << '|'
         << description;
    return line.str();
}
