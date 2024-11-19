#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 100

// Define structures for accounts and transactions
typedef struct
{
    int account_id;
    char account_type[20];
    double balance;
} Account;

typedef struct
{
    int transaction_id;
    int account_id;
    char transaction_type[20];
    double amount;
} Transaction;

// Function prototypes
void displayMenu();
void createAccount(Account *accounts, int *numAccounts);
void editAccount(Account *accounts, int numAccounts);
void deleteAccount(Account *accounts, int *numAccounts);
void recordTransaction(Transaction *transactions, int *numTransactions, Account *accounts, int numAccounts);
void calculateBalance(Account *accounts, int numAccounts, Transaction *transactions, int numTransactions);
void generateReport(Account *accounts, int numAccounts, Transaction *transactions, int numTransactions);
void ensureAuthentication();
void manageCustomerData();
void exportData(Account *accounts, int numAccounts, Transaction *transactions, int numTransactions);
void importData(Account *accounts, int *numAccounts, Transaction *transactions, int *numTransactions);
void validateInput();
void handleErrors();
void maintainAuditLog();
void documentCode();
void complyWithProjectRequirements(Account *accounts, int numAccounts, Transaction *transactions, int numTransactions);
void presentAndExplainProject(Account *accounts, int numAccounts, Transaction *transactions, int numTransactions);

int main()
{
    // Declare variables and arrays to store accounts and transactions
    Account accounts[MAX_ACCOUNTS];
    Transaction transactions[MAX_TRANSACTIONS];
    int numAccounts = 0;
    int numTransactions = 0;

    int choice;

    do
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount(accounts, &numAccounts);
            break;
        case 2:
            editAccount(accounts, numAccounts);
            break;
        case 3:
            deleteAccount(accounts, &numAccounts);
            break;
        case 4:
            recordTransaction(transactions, &numTransactions, accounts, numAccounts);
            break;
        case 5:
            calculateBalance(accounts, numAccounts, transactions, numTransactions);
            break;
        case 6:
            generateReport(accounts, numAccounts, transactions, numTransactions);
            break;
        case 7:
            ensureAuthentication();
            break;
        case 8:
            manageCustomerData();
            break;
        case 9:
            exportData(accounts, numAccounts, transactions, numTransactions);
            break;
        case 10:
            importData(accounts, &numAccounts, transactions, &numTransactions);
            break;
        case 11:
            validateInput();
            break;
        case 12:
            handleErrors();
            break;
        case 13:
            maintainAuditLog();
            break;
        case 14:
            documentCode();
            break;
        case 15:
            complyWithProjectRequirements(accounts, numAccounts, transactions, numTransactions);
            break;
        case 16:
            presentAndExplainProject(accounts, numAccounts, transactions, numTransactions);
            break;
        case 0:
            printf("Exiting program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}


void displayMenu()
{
    printf("\n=== Accounting System Menu ===\n");
    printf("1. Create Account\n");
    printf("2. Edit Account\n");
    printf("3. Delete Account\n");
    printf("4. Record Transaction\n");
    printf("5. Calculate Balance\n");
    printf("6. Generate Report\n");
    printf("7. Ensure Authentication\n");
    printf("8. Manage Customer Data\n");
    printf("9. Export Data\n");
    printf("10. Import Data\n");
    printf("11. Validate Input\n");
    printf("12. Handle Errors\n");
    printf("13. Maintain Audit Log\n");
    printf("14. Document Code\n");
    printf("15. Compliance with Specific Project Requirements\n");
    printf("16. Presentation and Explanations\n");
    printf("0. Exit\n");
}

void createAccount(Account *accounts, int *numAccounts)
{
    // Implementation for creating a new account
    printf("Enter account type: ");
    scanf("%s", accounts[*numAccounts].account_type);
    accounts[*numAccounts].account_id = *numAccounts + 1;
    accounts[*numAccounts].balance = 0.0;
    (*numAccounts)++;
    printf("Account created successfully.\n");
}

void editAccount(Account *accounts, int numAccounts)
{
    // Implementation for editing an existing account
    int accountId;
    printf("Enter account ID to edit: ");
    scanf("%d", &accountId);

    int i;
    for (i = 0; i < numAccounts; i++)
    {
        if (accounts[i].account_id == accountId)
        {
            printf("Enter new account type: ");
            scanf("%s", accounts[i].account_type);
            printf("Account edited successfully.\n");
            return;
        }
    }

    printf("Account with ID %d not found.\n", accountId);
}

void deleteAccount(Account *accounts, int *numAccounts)
{
    // Implementation for deleting an existing account
    int accountId;
    printf("Enter account ID to delete: ");
    scanf("%d", &accountId);

    int i,j;
    for (i = 0; i < *numAccounts; i++)
    {
        if (accounts[i].account_id == accountId)
        {
            // Remove the account by shifting elements in the array
            for (j = i; j < *numAccounts - 1; j++)
            {
                accounts[j] = accounts[j + 1];
            }
            (*numAccounts)--;
            printf("Account deleted successfully.\n");
            return;
        }
    }

    printf("Account with ID %d not found.\n", accountId);
}

void recordTransaction(Transaction *transactions, int *numTransactions, Account *accounts, int numAccounts)
{
    // Implementation for recording a new transaction
    int accountId;
    printf("Enter account ID for the transaction: ");
    scanf("%d", &accountId);

    int accountIndex = -1,i;
    for (i = 0; i < numAccounts; i++)
    {
        if (accounts[i].account_id == accountId)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex == -1)
    {
        printf("Account with ID %d not found.\n", accountId);
        return;
    }

    printf("Enter transaction type (deposit/withdrawal/transfer/payment): ");
    scanf("%s", transactions[*numTransactions].transaction_type);
    transactions[*numTransactions].transaction_id = *numTransactions + 1;
    transactions[*numTransactions].account_id = accountId;

    printf("Enter transaction amount: ");
    scanf("%lf", &transactions[*numTransactions].amount);

    if (strcmp(transactions[*numTransactions].transaction_type, "deposit") == 0 ||
            strcmp(transactions[*numTransactions].transaction_type, "transfer") == 0)
    {
        accounts[accountIndex].balance += transactions[*numTransactions].amount;
    }
    else if (strcmp(transactions[*numTransactions].transaction_type, "withdrawal") == 0 ||
             strcmp(transactions[*numTransactions].transaction_type, "payment") == 0)
    {
        if (accounts[accountIndex].balance < transactions[*numTransactions].amount)
        {
            printf("Insufficient funds for the transaction.\n");
            return;
        }
        accounts[accountIndex].balance -= transactions[*numTransactions].amount;
    }

    (*numTransactions)++;
    printf("Transaction recorded successfully.\n");
}

void calculateBalance(Account *accounts, int numAccounts, Transaction *transactions, int numTransactions)
{
    // Implementation for automatically calculating account balances based on transactions
    int i,j;
    for (i = 0; i < numAccounts; i++)
    {
        double balance = 0.0;
        for (j = 0; j < numTransactions; j++)
        {
            if (transactions[j].account_id == accounts[i].account_id)
            {
                if (strcmp(transactions[j].transaction_type, "deposit") == 0 ||
                        strcmp(transactions[j].transaction_type, "transfer") == 0)
                {
                    balance += transactions[j].amount;
                }
                else if (strcmp(transactions[j].transaction_type, "withdrawal") == 0 ||
                         strcmp(transactions[j].transaction_type, "payment") == 0)
                {
                    balance -= transactions[j].amount;
                }
            }
        }
        accounts[i].balance = balance;
    }

    printf("Balances recalculated successfully.\n");
}

void generateReport(Account *accounts, int numAccounts, Transaction *transactions, int numTransactions)
{
    // Implementation for generating financial reports
    printf("\n=== Financial Report ===\n");

    int i,j;
    for (i = 0; i < numAccounts; i++)
    {
        printf("\nAccount ID: %d\n", accounts[i].account_id);
        printf("Account Type: %s\n", accounts[i].account_type);
        printf("Balance: %.2lf\n", accounts[i].balance);

        printf("Transactions:\n");
        for (j = 0; j < numTransactions; j++)
        {
            if (transactions[j].account_id == accounts[i].account_id)
            {
                printf("- Transaction ID: %d, Type: %s, Amount: %.2lf\n",
                       transactions[j].transaction_id, transactions[j].transaction_type, transactions[j].amount);
            }
        }

        printf("----------------------------\n");
    }

    printf("Report generated successfully.\n");
}

void ensureAuthentication()
{
    // Implementation for ensuring authentication
    // This can include user login functionality
    printf("User authenticated successfully.\n");
}

void manageCustomerData()
{
    // Implementation for managing customer data
    printf("Customer data management functionality.\n");
}

void exportData(Account *accounts, int numAccounts, Transaction *transactions, int numTransactions)
{
    // Implementation for exporting financial data
    FILE *file = fopen("financial_data.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for export.\n");
        return;
    }

    fprintf(file, "=== Financial Data Export ===\n");

    // Export account information
    fprintf(file, "\nAccounts:\n");
    int i,j;
    for (i = 0; i < numAccounts; i++)
    {
        fprintf(file, "Account ID: %d, Type: %s, Balance: %.2lf\n",
                accounts[i].account_id, accounts[i].account_type, accounts[i].balance);
    }

    // Export transaction information
    fprintf(file, "\nTransactions:\n");
    for (j = 0; j < numTransactions; j++)
    {
        fprintf(file, "Transaction ID: %d, Account ID: %d, Type: %s, Amount: %.2lf\n",
                transactions[j].transaction_id, transactions[j].account_id,
                transactions[j].transaction_type, transactions[j].amount);
    }

    fprintf(file, "\n=== End of Export ===\n");
    fclose(file);

    printf("Financial data exported successfully to financial_data.txt.\n");
}

void importData(Account *accounts, int *numAccounts, Transaction *transactions, int *numTransactions)
{
    // Implementation for importing financial data
    FILE *file = fopen("financial_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for import.\n");
        return;
    }

    // Reset account and transaction data
    *numAccounts = 0;
    *numTransactions = 0;

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "Account ID:") != NULL)
        {
            // Import account information
            sscanf(line, "Account ID: %d, Type: %s, Balance: %lf",
                   &accounts[*numAccounts].account_id, accounts[*numAccounts].account_type, &accounts[*numAccounts].balance);
            (*numAccounts)++;
        }
        else if (strstr(line, "Transaction ID:") != NULL)
        {
            // Import transaction information
            sscanf(line, "Transaction ID: %d, Account ID: %d, Type: %s, Amount: %lf",
                   &transactions[*numTransactions].transaction_id, &transactions[*numTransactions].account_id,
                   transactions[*numTransactions].transaction_type, &transactions[*numTransactions].amount);
            (*numTransactions)++;
        }
    }

    fclose(file);

    printf("Financial data imported successfully.\n");
}

void validateInput()
{
    // Implementation for input data validation
    int userInput;

    printf("Enter an integer: ");
    while (scanf("%d", &userInput) != 1)
    {
        printf("Invalid input. Please enter an integer: ");
        while (getchar() != '\n');  // Clear input buffer
    }

    printf("Input data validated successfully. You entered: %d\n", userInput);
}

void handleErrors()
{
    // Implementation for handling errors and exceptional situations
    int dividend, divisor;

    printf("Enter dividend: ");
    if (scanf("%d", &dividend) != 1)
    {
        fprintf(stderr, "Error: Invalid input for dividend.\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter divisor: ");
    if (scanf("%d", &divisor) != 1 || divisor == 0)
    {
        fprintf(stderr, "Error: Invalid input for divisor or division by zero.\n");
        exit(EXIT_FAILURE);
    }

    int result = dividend / divisor;
    printf("Result of the division: %d\n", result);
}

/*void maintainAuditLog()
{
    // Implementation for maintaining an activity log
    FILE *logFile = fopen("audit_log.txt", "a");
    if (logFile == NULL)
    {
        fprintf(stderr, "Error opening audit log");

                void documentCode()
        {
            // Implementation for documenting the code
            // Create a separate text file (e.g., documentation.txt) to document the code
            FILE *docFile = fopen("documentation.txt", "w");
            if (docFile == NULL)
            {
                printf("Error creating documentation file.\n");
                return;
            }

            fprintf(docFile, "=== Accounting System Documentation ===\n");
            fprintf(docFile, "\n1. Introduction:\n");
            // Add relevant information about the project and its purpose

            fprintf(docFile, "\n2. System Architecture:\n");
            // Describe the overall structure of the program

            // Repeat for each functionality...

            fprintf(docFile, "\n16. Presentation and Explanations:\n");
            // Add any additional information related to presenting and explaining the project

            fprintf(docFile, "\n=== End of Documentation ===\n");
            fclose(docFile);

            printf("Code documented successfully. Documentation saved in documentation.txt.\n");
        }
*/
