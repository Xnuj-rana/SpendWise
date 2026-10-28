
const $ = (id) => document.getElementById(id);

const today = new Date().toLocaleDateString("en-CA");

let transactions = JSON.parse(
    localStorage.getItem("spendwiseTransactions") || "null"
) || [
    { id: 1, title: "Lunch", category: "Food", amount: 120, type: "expense", date: today },
    { id: 2, title: "Bus fare", category: "Transport", amount: 40, type: "expense", date: today },
    { id: 3, title: "Pocket Money", category: "Pocket Money", amount: 1000, type: "income", date: today },
    { id: 4, title: "College books", category: "Education", amount: 250, type: "expense", date: today },
    { id: 5, title: "Freelance work", category: "Salary", amount: 500, type: "income", date: today }
];

let budget = Number(localStorage.getItem("spendwiseBudget")) || 5000;
let chart = null;

const money = (amount) =>
    "₹" + amount.toLocaleString("en-IN", {
        minimumFractionDigits: 2,
        maximumFractionDigits: 2
    });

function saveData() {
    localStorage.setItem("spendwiseTransactions", JSON.stringify(transactions));
    localStorage.setItem("spendwiseBudget", String(budget));
}

function render() {
    const income = transactions
        .filter(t => t.type === "income")
        .reduce((sum, t) => sum + t.amount, 0);

    const expenses = transactions
        .filter(t => t.type === "expense")
        .reduce((sum, t) => sum + t.amount, 0);

    $("balance").textContent = money(income - expenses);
    $("income").textContent = money(income);
    $("expenses").textContent = money(expenses);
    $("budgetAmount").textContent = money(budget);

    const currentMonth = today.slice(0, 7);

    const monthlyExpenses = transactions
        .filter(t => t.type === "expense" && t.date.startsWith(currentMonth))
        .reduce((sum, t) => sum + t.amount, 0);

    const percent = Math.min((monthlyExpenses / budget) * 100, 100);

    $("budgetBar").style.width = percent + "%";
    $("budgetText").textContent =
        money(monthlyExpenses) + " spent this month (" +
        Math.round((monthlyExpenses / budget) * 100) + "% of budget)";

    $("budgetBar").style.background =
        percent >= 100 ? "#ff7c91" : "linear-gradient(90deg, #7b61ef, #c09aff)";

    renderTransactions();
    renderChart();
}

function renderTransactions() {
    const filter = $("filter").value;

    const filtered = transactions
        .filter(t => filter === "all" || t.type === filter)
        .slice()
        .sort((a, b) => b.date.localeCompare(a.date) || b.id - a.id);

    const list = $("transactionList");
    list.replaceChildren();

    $("emptyMessage").hidden = filtered.length !== 0;

    filtered.forEach(t => {
        const row = document.createElement("tr");

        const values = [
            t.title,
            t.category,
            t.date,
            (t.type === "income" ? "+" : "−") + money(t.amount)
        ];

        values.forEach((value, index) => {
            const cell = document.createElement("td");
            cell.textContent = value;

            if (index === 3) {
                cell.className = t.type === "income" ? "green" : "red";
            }

            row.appendChild(cell);
        });

        const actionCell = document.createElement("td");
        const deleteButton = document.createElement("button");

        deleteButton.className = "delete-btn";
        deleteButton.textContent = "×";
        deleteButton.title = "Delete transaction";

        deleteButton.addEventListener("click", () => {
            if (confirm("Delete this transaction?")) {
                transactions = transactions.filter(item => item.id !== t.id);
                saveData();
                render();
            }
        });

        actionCell.appendChild(deleteButton);
        row.appendChild(actionCell);
        list.appendChild(row);
    });
}

function renderChart() {
    const totals = {};

    transactions
        .filter(t => t.type === "expense")
        .forEach(t => {
            totals[t.category] = (totals[t.category] || 0) + t.amount;
        });

    const labels = Object.keys(totals);
    const values = Object.values(totals);

    if (chart) {
        chart.destroy();
    }

    chart = new Chart($("categoryChart"), {
        type: "doughnut",
        data: {
            labels,
            datasets: [{
                data: values,
                backgroundColor: [
                    "#9275ff", "#53d6a0", "#ff7c91",
                    "#5fa9ff", "#ffc66d", "#d58bff",
                    "#55d4d4", "#ff9e70"
                ],
                borderColor: document.body.classList.contains("light")
                    ? "#ffffff" : "#151b30",
                borderWidth: 3,
                hoverOffset: 8
            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            cutout: "68%",
            plugins: {
                legend: {
                    position: "bottom",
                    labels: {
                        color: getComputedStyle(document.body)
                            .getPropertyValue("--muted").trim(),
                        padding: 16
                    }
                },
                tooltip: {
                    callbacks: {
                        label: context =>
                            context.label + ": " + money(context.raw)
                    }
                }
            }
        }
    });
}

$("addBtn").addEventListener("click", () => {
    $("date").value = today;
    $("transactionDialog").showModal();
});

$("closeDialog").addEventListener("click", () => {
    $("transactionDialog").close();
});

$("type").addEventListener("change", () => {
    const incomeCategories = ["Salary", "Pocket Money", "Other"];
    const expenseCategories = [
        "Food", "Transport", "Shopping", "Education",
        "Bills", "Entertainment", "Health", "Other"
    ];

    const categories = $("type").value === "income"
        ? incomeCategories : expenseCategories;

    $("category").replaceChildren();

    categories.forEach(category => {
        const option = document.createElement("option");
        option.value = category;
        option.textContent = category;
        $("category").appendChild(option);
    });
});

$("transactionForm").addEventListener("submit", event => {
    event.preventDefault();

    const amount = Number($("amount").value);
    const date = $("date").value;

    if (!Number.isFinite(amount) || amount <= 0 || !date) {
        alert("Enter a valid amount and date.");
        return;
    }

    if (date > today) {
        alert("Transaction date cannot be in the future.");
        return;
    }

    transactions.push({
        id: Date.now(),
        title: $("title").value.trim(),
        category: $("category").value,
        amount,
        type: $("type").value,
        date
    });

    saveData();
    render();

    $("transactionForm").reset();
    $("transactionDialog").close();
});

$("filter").addEventListener("change", renderTransactions);

$("saveBudget").addEventListener("click", () => {
    const newBudget = Number($("budgetInput").value);

    if (!Number.isFinite(newBudget) || newBudget <= 0) {
        alert("Enter a valid budget greater than zero.");
        return;
    }

    budget = newBudget;
    saveData();
    $("budgetInput").value = "";
    render();
});

$("themeBtn").addEventListener("click", () => {
    document.body.classList.toggle("light");
    localStorage.setItem(
        "spendwiseTheme",
        document.body.classList.contains("light") ? "light" : "dark"
    );
    renderChart();
});

if (localStorage.getItem("spendwiseTheme") === "light") {
    document.body.classList.add("light");
}

render();
