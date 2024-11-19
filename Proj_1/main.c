#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data structure to store information about a transaction
typedef struct Transaction
{
    char date[20];
    char description[100];
    double amount;
    char type; // 'I' for income, 'E' for expense
} Transaction;

// Function to record a new transaction
void recordTransaction(Transaction *transactions, int *transactionCount) // 1
{
    Transaction newTransaction;

    printf("Enter transaction date (MM/DD/YYYY): ");
    scanf("%s", newTransaction.date);
    printf("Enter transaction description: ");
    scanf(" %[^\n]", newTransaction.description);
    printf("Enter transaction amount: ");
    scanf("%lf", &newTransaction.amount);
    printf("Enter transaction type (I for income, E for expense): ");
    scanf(" %c", &newTransaction.type);

    transactions[(*transactionCount)++] = newTransaction;
}

// Function to calculate the account balance
double calculateBalance(Transaction *transactions, int transactionCount) // 2
{
    double balance = 0.0;
    int i;
    for (i = 0; i < transactionCount; ++i)
    {
        if (transactions[i].type == 'I')
        {
            balance += transactions[i].amount;
        }
        else
        {
            balance -= transactions[i].amount;
        }
    }
    return balance;
}

// Function to display a list of previous transactions
void displayTransactions(Transaction *transactions, int transactionCount) // 3
{
    printf("Transaction History:\n");
    int i;
    for (i = 0; i < transactionCount; ++i)
    {
        printf("Date: %s, Description: %s, Amount: %.2lf, Type: %c\n",transactions[i].date, transactions[i].description, transactions[i].amount, transactions[i].type);
    }
}

// Function to generate a simple financial report
void generateReport(Transaction *transactions, int transactionCount) // 4
{
    double totalIncome = 0.0, totalExpenses = 0.0;
    int i;
    for (i = 0; i < transactionCount; ++i)
    {
        if (transactions[i].type == 'I')
        {
            totalIncome += transactions[i].amount;
        }
        else
        {
            totalExpenses += transactions[i].amount;
        }
    }

    printf("Financial Report:\n");
    printf("Total Income: %.2lf\n", totalIncome);
    printf("Total Expenses: %.2lf\n", totalExpenses);
    printf("Account Balance: %.2lf\n", calculateBalance(transactions, transactionCount));
}

// Function to save financial data to a file
void saveDataToFile(Transaction *transactions, int transactionCount) // 5
{
    FILE *file = fopen("financial_data.txt", "w");

    if (file == NULL)
    {
        printf("Error: Unable to open the file for writing.\n");
        return;
    }

    int i;
    for (i = 0; i < transactionCount; ++i)
    {
        fprintf(file, "%s,%s,%.2lf,%c\n", transactions[i].date, transactions[i].description, transactions[i].amount, transactions[i].type);
    }

    fclose(file);
    printf("Financial data has been saved to the file.\n");
}

// Function to load financial data from a file
int loadDataFromFile(Transaction *transactions)
{
    FILE *file = fopen("financial_data.txt", "r");
    if (file == NULL)
    {
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%19[^,],%99[^,],%lf,%c\n", transactions[count].date, transactions[count].description, &transactions[count].amount, &transactions[count].type) == 4)
    {
        count++;
    }

    fclose(file);
    return count;
}

int main()
{
    Transaction transactions[100];
    int transactionCount = 0;

    // Load existing financial data from a file, if available
    transactionCount = loadDataFromFile(transactions);

    int choice;
    do
    {
        printf("\nFinancial Data Management Menu:\n");
        printf("1. Record a new transaction\n");
        printf("2. Calculate account balance\n");
        printf("3. Display transaction history\n");
        printf("4. Generate a financial report\n");
        printf("5. Save financial data to a file\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            recordTransaction(transactions, &transactionCount);
            break;
        case 2:
            printf("Account Balance: %.2lf\n", calculateBalance(transactions, transactionCount));
            break;
        case 3:
            displayTransactions(transactions, transactionCount);
            break;
        case 4:
            generateReport(transactions, transactionCount);
            break;
        case 5:
            saveDataToFile(transactions, transactionCount);
            break;
        case 6:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    while (choice != 6);

    return 0;
}
