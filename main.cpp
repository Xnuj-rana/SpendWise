#include "FinanceManager.h"
#include <iostream>
#include <limits>

int main() {
    FinanceManager finance;
    int choice = 0;

    std::cout << "====================================\n";
    std::cout << "       SPENDWISE EXPENSE TRACKER\n";
    std::cout << "====================================\n";

    do {
        std::cout << "\n1. Add transaction\n";
        std::cout << "2. View all transactions\n";
        std::cout << "3. View financial summary\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Please enter a number from 1 to 4.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                finance.addTransaction();
                break;
            case 2:
                finance.showTransactions();
                break;
            case 3:
                finance.showSummary();
                break;
            case 4:
                std::cout << "Thanks for using SpendWise!\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
