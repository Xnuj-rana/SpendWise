# 💰 SpendWise — Personal Expense Tracker

A beginner-friendly, menu-driven **Personal Expense Tracker built using C++ and Object-Oriented Programming (OOP)**, with a web frontend created using HTML, CSS, and JavaScript. SpendWise helps users record income and expenses and review their financial summary.

![image alt](https://github.com/Xnuj-rana/SpendWise/blob/8288730a4f42c54c718fb5de55414b850089705c/Screenshot%202026-10-28%20220345.png)

![image alt](https://github.com/Xnuj-rana/SpendWise/blob/e67154184ad2bb5938629532677a9373764e5447/Screenshot%202026-10-30%20120850.png)

![image alt](https://github.com/Xnuj-rana/SpendWise/blob/e67154184ad2bb5938629532677a9373764e5447/Screenshot%202026-10-30%20120857.png)

## ✨ Features

- ➕ Add income and expense transactions
- 📋 View all recorded transactions
- 📊 View a financial summary
- 🗂️ Organize transactions by category
- 💾 Store C++ transaction records in a local text file
- 🌐 Web dashboard with transaction management
- 🔍 Search and filter transactions in the frontend
- 🌓 Light and dark theme support

## 🛠️ Technologies Used

- **C++** — Core application logic
- **HTML5** — Frontend structure
- **CSS3** — Styling and layout
- **JavaScript** — Frontend interactions
- **File Handling** — Local transaction storage in the C++ application
- **Git and GitHub** — Version control and project hosting

## 🧠 OOP Concepts Used

| Concept | Implementation |
|---|---|
| Classes and Objects | `Transaction` and `FinanceManager` |
| Encapsulation | Organizing transaction data and finance-management operations within classes |
| Functions | Adding transactions, displaying records, and calculating summaries |
| File Handling | Saving and retrieving transaction records |
| Conditional Statements | Handling menu options and transaction types |
| Loops | Processing menu operations and transaction records |

## 🚀 How to Run the C++ Application

**Step 1:** Install a C++ compiler such as GCC.

**Step 2:** Clone this repository:

```bash
git clone https://github.com/Xnuj-rana/SpendWise.git
```

**Step 3:** Open the project folder in VS Code.

**Step 4:** Open the terminal in the project directory and compile the program:

```bash
g++ -std=c++17 main.cpp Transaction.cpp FinanceManager.cpp -o SpendWise.exe
```

**Step 5:** Run the program in Windows PowerShell:

```powershell
.\SpendWise.exe
```

## 🌐 How to Run the Web Frontend

1. Open the `frontend` folder in VS Code.
2. Open `index.html`.
3. Run it using the Live Server extension, or open the HTML file in a browser.

> **Note:** The C++ application and web frontend currently operate separately. The frontend does not automatically read or update the C++ application's transaction file.

## 📂 Project Structure

```text
SpendWise/
│
├── main.cpp
├── Transaction.cpp
├── Transaction.h
├── FinanceManager.cpp
├── FinanceManager.h
├── frontend/
│   ├── index.html
│   ├── style.css
│   └── script.js
├── .gitignore
└── README.md
```

## ⚠️ Limitations

- The C++ application and web frontend do not share transaction data.
- C++ transaction records are stored locally on the computer.
- The frontend uses browser-side storage and does not have a shared database.
- The project is intended for learning and demonstration, not as a secure banking application.

## 🔮 Future Improvements

- 🔗 Connect the frontend to the C++ application through a backend or API.
- 🗄️ Add database integration.
- 📈 Improve financial reports and spending analysis.
- 📅 Add monthly budgets and spending alerts.
- 📤 Add transaction export functionality.
- 🔐 Add secure user accounts if multi-user support is introduced.

## 🎯 Project Objective

The objective of SpendWise is to practise C++ programming, Object-Oriented Programming, file handling, frontend development, and Git/GitHub workflows by building a personal finance tracking application.

## 👨‍💻 Author

**Anuj Rana**

## 📄 License

This project is intended for educational and learning purposes.

