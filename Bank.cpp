#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>

using namespace std;

//---------------------------------------------------------------------------------------------------//

const int maxName = 50;
const int maxMoney = 7;
const int maxNumber = 12;
const int typeSize = 4;
const string sep = " |";
const int totalLen = maxName + maxNumber + typeSize + maxMoney + sep.size() * 4;
const string sepLine = sep + string(totalLen - 1, '=') + '|';

class Bank {
    private:
        unsigned long long account_number;
        char holder_name[51];
        int deposit;
        char type;
    public:
        void System_clear();
        void Get_Data();
        void Write_Data();
        void deposit_withdraw(int n, int option);
        void Display_Invidual_Records(unsigned long long n);
        void report() const;
        void Show_account() const;
        void dep(int);
        void draw(int x);
        unsigned long long retacno() const;
        int retdeposit() const;
        char rettype() const;
        void Modification_data();
};

void Bank::Get_Data() {
    cout << "\n\n===========CREATE BANK ACCOUNT===========\n\n";
    cout << "\nEnter the Account Number:";
    cin >> account_number;
    while ((int)to_string(account_number).size() != 10) {
        cout << "The account number has to be of 10 digits. Please try again.\n";
        cin.clear();
        fflush(stdin);
        cin >> account_number;
    }
    cout << "\n\nEnter Account Holder Name: ";
    cin.clear();
    fflush(stdin);
    cin.getline(holder_name, 51);
    cout << "\nWhich type of Account \n[S for Saving Account] (or)[C for Current Account]: ";
    cin.clear();
    fflush(stdin);
    cin >> type;
    type = toupper(type);
    while (type != 'S' && type != 'C') {
        cout << "Please enter either S or C to avoid data corruption: ";
        cin.clear();
        fflush(stdin);
        cin >> type;
        type = toupper(type);
    }
    if (type == 'S') {
        cout << "\nEnter the Initial Amount for Saving Account [Minimum 500/-]: ";
        cin >> deposit;
        while (deposit >= 1000000) {
            cout << "Maximum money is 1000000/-\nPlease try again: ";
            cin >> deposit;
        }
        cout << "\n\nAccount has been Created Sucessfully.";
    } else if (type == 'C') {
        cout << "\nEnter the Initial Amount for Current Account [Minimum 1000/-]: ";
        cin >> deposit;
        while (deposit >= 1000000) {
            cout << "Maximum money is 1000000/-\nPlease try again: ";
            cin >> deposit;
        }
        cout << "\n\nAccount has been Created Sucessfully.";
    }
}

void Bank::Write_Data() {
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    Get_Data();
    outFile.write((char*) this, sizeof(*this));
    outFile.close();
}

void Bank::Modification_data() {
    cout << "\nAccount No: " << account_number;
    cout << "\nModify Account Holder Name: ";
    cin.clear();
    fflush(stdin);
    cin.getline(holder_name, 51);
    cout << "\nModify Type of Account : ";
    cin.clear();
    fflush(stdin);
    cin >> type;
    type = toupper(type);
    cout << "\nModify Total Balance Amount : ";
    cin >> deposit;
    while (deposit >= 1000000) {
        cout << "Maximum money is 1000000/-\nPlease try again: ";
        cin >> deposit;
    }
}

void Bank::Display_Invidual_Records(unsigned long long n) {
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "\n\nAn Error Occurred. Please try again.";
        return;
    }
    cout << "\nBALANCE DETAILS\n";
    while (inFile.read((char*) this, sizeof(*this))) {
        if (retacno() == n) {
            Show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccounts Details not Found.";
}

void Bank::report() const {
    cout << sep <<
        setw(maxNumber) << account_number << sep <<
        setw(maxName) << holder_name << sep <<
        setw(typeSize) << type << sep <<
        setw(maxMoney) << deposit << sep << endl << sepLine << endl;
}

void Bank::dep(int x) {
    deposit = deposit + x;
}

void Bank::draw(int x) {
    deposit -= x;
}

void Bank::Show_account() const {
    cout << "\nAccount No: " << account_number;
    cout << "\nAccount Holder Name: ";
    cout << holder_name;
    if (type == 'S') {
        cout << "\nType of Account: Saving ";
    } else {
        cout << "\nType of Account: Current ";
    }
    cout << "\nTotal Balance: " << deposit;
}

unsigned long long Bank::retacno() const {
    return account_number;
}

int Bank::retdeposit() const {
    return deposit;
}

char Bank::rettype() const {
    return type;
}

void Bank::System_clear() {
    system("cls");
}

//-------------------------------------------------------------------------------------------------------//

void Delete_Account(unsigned long long);
void system_clear() {
    system("cls");
}
void Get_All_Data();
void Deposit_Withdraw(unsigned long long, int);
void Credit();
void Account_Modification(unsigned long long);

int main() {
    char my_url;
    char choice;
    unsigned long long account_number;
    Bank call;
    Credit();
    do {
        system_clear();
        cout << "\n===========================";
        cout << "\n  BANKING RECORD SYSTEM";
        cout << "\n===========================\n\n";
        cout << "\n\n01. CREATE NEW ACCOUNT";
        cout << "\n\n02. MODIFY AN ACCOUNT";
        cout << "\n\n03. BALANCE ENQUIRY OF ACCOUNT";
        cout << "\n\n04. DEPOSIT IN ACCOUNT";
        cout << "\n\n05. WITHDRAW FROM ACCOUNT";
        cout << "\n\n06. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n07. CLOSE AN ACCOUNT";
        cout << "\n\n08. EXIT FROM PROGRAM";
        cout << "\n\nSELECT THE OPTION: ";
        cin >> choice;
        system_clear();
        switch (choice) {
            case '1':
                call.Write_Data();
                break;
            case '2':
                cout << "\n\n\tAccount No: ";
                cin >> account_number;
                Account_Modification(account_number);
                break;
            case '3':
                cout << "\n\nAccount No: ";
                cin >> account_number;
                call.Display_Invidual_Records(account_number);
                break;
            case '4':
                cout << "\n\nAccount No: ";
                cin >> account_number;
                Deposit_Withdraw(account_number, 1);
                break;
            case '5':
                cout << "\n\nAccount No: ";
                cin >> account_number;
                Deposit_Withdraw(account_number, 2);
                break;
            case '6':
                Get_All_Data();
                break;
            case '7':
                cout << "\n\nAccount No: ";
                cin >> account_number;
                Delete_Account(account_number);
                break;
            case '8':
                cout << "\n\n\tThanks for using Bank Record System.";
               
               
                break;
            default:
                cout << "\a";
        }
        cin.clear();
        fflush(stdin);
        cin.get();
        system_clear();
    } while (choice != '8');
}

//-------------------------------------------------------------------------------------------------------//

void Get_All_Data() {
    Bank call;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "An Error Occurred. Please try again.";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << sepLine << endl << sep <<
        setw(maxNumber) << "A/C NO." << sep <<
        setw(maxName) << "NAME" << sep <<
        setw(typeSize) << "TYPE" << sep <<
        setw(maxMoney) << "BALANCE" << sep << endl <<
        sepLine << endl;
    while (inFile.read((char*) &call, sizeof(Bank))) {
        call.report();
    }
    inFile.close();
}

void Deposit_Withdraw(unsigned long long n, int option) {
    int amt;
    Bank call;
    bool found = false;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "An Error Occurred. Please try again.";
        return;
    }
    while (!File.eof() && found == false) {
        File.read((char*) &call, sizeof(Bank));
        if (call.retacno() == n) {
            call.Show_account();
            if (option == 1) {
                cout << "\n\nEnter Amount to be Deposited: ";
                cin >> amt;
                call.dep(amt);
            } else if (option == 2) {
                cout << "\n\nEnter Amount to be Withdrawn: ";
                cin >> amt;
                int bal = call.retdeposit() - amt;
                if (bal < 0) {
                    cout << "Sorry, Balance is Insufficient";
                } else if ((bal < 500 && call.rettype() == 'S')) {
                    cout << "\nInsufficient balance. Minimum required for Savings account is 500/-.";
                } else if ((bal < 1000 && call.rettype() == 'C')) {
                    cout << "\nInsufficient balance. Minimum required for Current account is 1000/-.";
                } else {
                    call.draw(amt);
                }
            }
            int pos = (-1) * sizeof(call);
            File.seekp(pos, ios::cur);
            File.write((char*) &call, sizeof(Bank));
            cout << "\n\nAccount Balance Updated.";
            found = true;
        }
    }
    File.close();
    if (found == false) {
        cout << "\n\nAn Error Occurred. Please try again.";
    }
}

void Delete_Account(unsigned long long n) {
    Bank call;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "An Error Occurred. Please try again.";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read((char*) &call, sizeof(Bank))) {
        if (call.retacno() != n) {
            outFile.write((char*) &call, sizeof(Bank));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\nAccount has been Deleted Successfully.";
}

void Account_Modification(unsigned long long n) {
    bool found = false;
    Bank call;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "An Error Occurred. Please try again.";
        return;
    }
    while (!File.eof() && found == false) {
        File.read((char*) &call, sizeof(Bank));
        if (call.retacno() == n) {
            call.Show_account();
            cout << "\n\nEnter New Details for Account: ";
            call.Modification_data();
            int pos = (-1) * sizeof(call);
            File.seekp(pos, ios::cur);
            File.write((char*) &call, sizeof(Bank));
            cout << "\n\nAccount has been Updated.";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\nAn Error Occurred. Please try again.";
}

void Credit() {
    cout << "\n\t\t--------------------------";
    cout << "\n\t\tBANK MANAGEMENT SYSTEM ";
    cout << "\n\t\tCREATED BY: RUPAK";
    cout << "\n\t\t--------------------------";
    cout << "\n\n\n\n\n\n\n\t\t\t\tPress Enter to Continue....";
    fflush(stdin);
    cin.get();
}
