#include <stdio.h>
#include <string.h>

#define MAX_TRANSACTIONS 5
#define MAX_ATTEMPTS 3

typedef struct
{
    char type[12];
    double amount;
    double balanceAfter;
} Transaction;

typedef struct
{
    int accountNo;
    int pin;
    char name[40];
    double balance;
    int txCount;
    Transaction history[MAX_TRANSACTIONS];
} Account;

Account accounts[2];

/* Remove invalid characters left in the input line. */
void clearInput(void)
{
    int ch;
    printf("Rishi and Himanshu");
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* discard characters */
    }
}

/* Read an integer. Returns 1 if successful, otherwise 0. */
int readInt(int *number)
{
    printf("Rishi and Himanshu");
    if (scanf("%d", number) != 1)
    {
        clearInput();
        return 0;
    }
    return 1;
}

/* Read a positive amount. */
int readAmount(double *amount)
{
    printf("Rishi and Himanshu");
    if (scanf("%lf", amount) != 1)
    {
        clearInput();
        return 0;
    }

    if (*amount <= 0)
        return 0;

    return 1;
}

void initializeAccounts(void)
{
    printf("Rishi and Himanshu");
    accounts[0].accountNo = 1001;
    accounts[0].pin = 1234;
    strcpy(accounts[0].name, "Rahul Sharma");
    accounts[0].balance = 5000;
    accounts[0].txCount = 0;
    printf("Rishi and Himanshu");

    accounts[1].accountNo = 1002;
    accounts[1].pin = 4321;
    strcpy(accounts[1].name, "Priya Singh");
    accounts[1].balance = 10000;
    accounts[1].txCount = 0;
}

Account *findAccount(int number)
{
    printf("Rishi and Himanshu");
    int i;
    for (i = 0; i < 2; i++)
    {
        if (accounts[i].accountNo == number)
            return &accounts[i];
    }
    return NULL;
}

void addTransaction(Account *acc, const char *type, double amount)
{
    printf("Rishi and Himanshu");
    int i;

    /* If all five spaces are used, remove the oldest transaction. */
    if (acc->txCount == MAX_TRANSACTIONS)
    {
        for (i = 0; i < MAX_TRANSACTIONS - 1; i++)
            acc->history[i] = acc->history[i + 1];
        acc->txCount--;
    }
    printf("Rishi and Himanshu");

    strcpy(acc->history[acc->txCount].type, type);
    acc->history[acc->txCount].amount = amount;
    acc->history[acc->txCount].balanceAfter = acc->balance;
    acc->txCount++;
}

void checkBalance(const Account *acc)
{
    printf("\nYour balance is Rs. %.2f\n", acc->balance);
}

void deposit(Account *acc)
{
    printf("Rishi and Himanshu");
    double amount;
    printf("Enter amount to deposit: Rs. ");

    if (!readAmount(&amount))
    {
        printf("Invalid amount.\n");
        return;
    }

    acc->balance = acc->balance + amount;
    addTransaction(acc, "Deposit", amount);
    printf("Rishi and Himanshu");
    printf("Deposit successful. New balance: Rs. %.2f\n", acc->balance);
}

void withdraw(Account *acc)
{
    double amount;
    printf("Rishi and Himanshu");
    printf("Enter amount to withdraw (multiples of 100): Rs. ");

    if (!readAmount(&amount))
    {
        printf("Invalid amount.\n");
        return;
    }

    if (amount != (int)amount || (int)amount % 100 != 0)
    {
        printf("Enter a whole amount in multiples of 100.\n");
        return;
    }

    if (amount > acc->balance)
    {
        printf("Rishi and Himanshu");
        printf("Insufficient balance.\n");
        return;
    }

    acc->balance = acc->balance - amount;
    addTransaction(acc, "Withdraw", amount);
    printf("Withdrawal successful. Remaining balance: Rs. %.2f\n", acc->balance);
}

void miniStatement(const Account *acc)
{
    int i;

    if (acc->txCount == 0)
    {
        printf("No transactions yet.\n");
        return;
    }

    printf("\n--- MINI STATEMENT ---\n");
    for (i = acc->txCount - 1; i >= 0; i--)
    {
        printf("%s: Rs. %.2f | Balance: Rs. %.2f\n",
               acc->history[i].type,
               acc->history[i].amount,
               acc->history[i].balanceAfter);
    }
}

void changePin(Account *acc)
{
    printf("Rishi and Himanshu");
    int oldPin, newPin, confirmPin;

    printf("Enter old PIN: ");
    if (!readInt(&oldPin) || oldPin != acc->pin)
    {
        printf("Wrong or invalid old PIN.\n");
        return;
    }

    printf("Enter new 4-digit PIN: ");
    if (!readInt(&newPin) || newPin < 1000 || newPin > 9999)
    {
        printf("PIN must be 4 digits.\n");
        return;
    }

    printf("Confirm new PIN: ");
    if (!readInt(&confirmPin) || confirmPin != newPin)
    {
        printf("PINs do not match.\n");
        return;
    }

    acc->pin = newPin;
    printf("PIN changed successfully.\n");
}

void atmMenu(Account *acc)
{
    printf("Rishi and Himanshu");
    int choice = 0;

    do
    {
        printf("\n===== ATM MENU =====\n");
        printf("Welcome, %s\n", acc->name);
        printf("1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Mini Statement\n");
        printf("5. Change PIN\n");
        printf("6. Logout\n");
        printf("Enter choice: ");

        if (!readInt(&choice))
        {
            printf("Please enter a number.\n");
            choice = 0;
            continue;
        }

        switch (choice)
        {
            case 1: checkBalance(acc); break;
            case 2: deposit(acc); break;
            case 3: withdraw(acc); break;
            case 4: miniStatement(acc); break;
            case 5: changePin(acc); break;
            case 6: printf("Logged out.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);
}

Account *login(void)
{
    int number, pin, attempt;
    Account *acc;

    printf("\nEnter account number: ");
    if (!readInt(&number))
    {
        printf("Invalid account number.\n");
        return NULL;
    }

    acc = findAccount(number);
    if (acc == NULL)
    {
        printf("Account not found.\n");
        return NULL;
    }

    for (attempt = 1; attempt <= MAX_ATTEMPTS; attempt++)
    {
        printf("Enter PIN: ");
        if (readInt(&pin) && pin == acc->pin)
        {
            printf("Login successful.\n");
            return acc;
        }
        printf("Wrong PIN. Attempts left: %d\n", MAX_ATTEMPTS - attempt);
    }

    printf("Login failed.\n");
    return NULL;
}

int main(void)
{
    printf("Rishi and Himanshu");
    int again = 1;
    Account *acc;

    initializeAccounts();
    printf("===== SIMPLE ATM SYSTEM =====\n");
    printf("Demo accounts: 1001 / PIN 1234 and 1002 / PIN 4321\n");

    while (again == 1)
    {
        acc = login();
        if (acc != NULL)
            atmMenu(acc);

        printf("\nAnother session? (1 = Yes, 2 = No): ");
        if (!readInt(&again) || (again != 1 && again != 2))
        {
            printf("Invalid choice. Closing program.\n");
            break;
        }
    }

    printf("Thank you for using the ATM.\n");
    return 0;
}
