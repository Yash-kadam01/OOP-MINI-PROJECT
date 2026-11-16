#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ================= BACKEND (classes) =================

// Base class
class Account {
private:                       // ENCAPSULATION: data is hidden
    int accNo;
    string name;
    double balance;

public:
    // Constructor: runs when an object is created
    Account(int n, string nm, double b) {
        accNo = n;
        name = nm;
        balance = b;
    }

    // Getters: the only way to read private data
    int getAccNo() {
        return accNo;
    }
    double getBalance() {
        return balance;
    }

    // ABSTRACTION: user just calls deposit(), logic is hidden inside
    void deposit(double amt) {
        if (amt <= 0) {
            cout << "Invalid amount!\n";
        } else {
            balance = balance + amt;
            cout << "Deposited. New balance: " << balance << "\n";
        }
    }

    void withdraw(double amt) {
        if (amt <= 0) {
            cout << "Invalid amount!\n";
        } else if (amt > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance = balance - amt;
            cout << "Withdrawn. New balance: " << balance << "\n";
        }
    }

    void display() {
        cout << "Acc No: " << accNo << " | Name: " << name
             << " | Balance: " << balance << "\n";
    }
};

// INHERITANCE: SavingsAccount gets everything from Account
class SavingsAccount : public Account {
private:
    double interestRate;       // extra data only for savings

public:
    // Calls the parent constructor, then sets its own data
    SavingsAccount(int n, string nm, double b, double r) : Account(n, nm, b) {
        interestRate = r;
    }

    void addInterest() {
        double interest = getBalance() * interestRate / 100;
        deposit(interest);     // reusing the parent's function
    }

    // POLYMORPHISM: same function name display(), different behaviour
    void display() {
        Account::display();    // first run the parent's display()
        cout << "Interest rate: " << interestRate << "%\n";
    }
};

// ================= FRONTEND (menu) =================

vector<SavingsAccount> accounts;   // std::vector stores all accounts

// Returns position of the account in the vector, or -1 if not found
int findAccount(int no) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].getAccNo() == no) {
            return i;
        }
    }
    return -1;
}

int main() {
    int choice;

    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Add Interest\n";
        cout << "5. Show All Accounts\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int no;
            string name;
            double bal, rate;
            cout << "Account No: ";
            cin >> no;
            cout << "Name: ";
            cin >> name;
            cout << "Opening balance: ";
            cin >> bal;
            cout << "Interest rate (%): ";
            cin >> rate;

            if (findAccount(no) != -1) {
                cout << "Account number already exists!\n";
            } else {
                SavingsAccount acc(no, name, bal, rate);
                accounts.push_back(acc);       // add to vector
                cout << "Account created!\n";
            }
        }
        else if (choice == 2 || choice == 3 || choice == 4) {
            int no;
            cout << "Account No: ";
            cin >> no;
            int pos = findAccount(no);

            if (pos == -1) {
                cout << "Account not found!\n";
            } else if (choice == 2) {
                double amt;
                cout << "Amount: ";
                cin >> amt;
                accounts[pos].deposit(amt);
            } else if (choice == 3) {
                double amt;
                cout << "Amount: ";
                cin >> amt;
                accounts[pos].withdraw(amt);
            } else {
                accounts[pos].addInterest();
            }
        }
        else if (choice == 5) {
            if (accounts.empty()) {
                cout << "No accounts yet.\n";
            }
            for (int i = 0; i < accounts.size(); i++) {
                accounts[i].display();
            }
        }
    } while (choice != 6);

    cout << "Thank you!\n";
    return 0;
}