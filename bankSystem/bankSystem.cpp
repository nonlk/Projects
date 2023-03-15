/*Банковская система. Можно создать несколько банков. В каждом банке может быть несколько клиентов. 
Клиенты банка могут быть физическими и юридическими лицами. У каждого клиента банка существует счет (только один). 
У банка также существует аналогичный параметр – сумма собственных средств банка. Клиенты банка могут проводить операции:
  •	положить деньги на счет; 
  •	снять деньги со счета;
  •	сделать перевод суммы денег на другой счет (возможно в другом банке, только для юридических лиц). 
При переводе денег со счета на счет с суммы перевода в пользу банка взимается определенный процент. 
Необходимо предусмотреть интерфейс для создания/удаления банков, создания/удаления клиентов каждого банка, а также выполнения каждым клиентом перечисленных операций.
При этом не должны допускаться операции, в результате которых счет клиента становится отрицательным.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class TypeCustomer {
    Natural, Legal, NoType
};
string PrintTypeCustomer(TypeCustomer type) {
    switch (type) {
    case TypeCustomer::Natural:
        return "Физическое лицо";
    case TypeCustomer::Legal:
        return "Юридическое лицо";
    case TypeCustomer::NoType:
        return " ";
    }
}

class Customer {
    string FIO;
    TypeCustomer type;
    double account;
public:
    Customer() : type(TypeCustomer::NoType), account(0) {};
    void SetTypeCustomer(TypeCustomer inputType) { type = inputType; };
    void SetCustomerFIO(string inputFIO) { FIO = inputFIO; };
    bool SetCustomerFirstAccount(double inputAccount) {
        if (inputAccount > 0) {
            account = inputAccount;
            return 1;
        }
        return 0;
    };
    bool DepositMoney(double inputMoney) {
        if (inputMoney > 0) {
            account += inputMoney;
            return 1;
        }
        return 0;
    };
    bool WithdrawalMoney(double inputMoney) {
        if (inputMoney > 0 && inputMoney <= account) {
            account -= inputMoney;
            return 1;
        }
        return 0;
    };
    const string& GetCustomerFIO() { return FIO; };
    const TypeCustomer& GetCustomerType() { return type; };
    const double& GetCustomerAccount() { return account; };
    ~Customer() { type = TypeCustomer::NoType; account = 0; };
};

class Bank {
    string nameBank;
    int procent;
    double amount;
    vector <Customer> ContainerCustomers;
    int numberCustomers;
public:
    Bank() : ContainerCustomers(NULL), numberCustomers(0), amount(0) {};
    void SetBankName(string inputName) { nameBank = inputName; };
    void SetBankProcent(int inputProcent) { procent = inputProcent; };
    bool AddNewCustomer() {
        char inputItem = '0'; double inputCustAccount; string inputCustFIO; Customer newCustomer;
        cout << "Введите ФИО клиента (латиница): ";
        getline(cin, inputCustFIO); getline(cin, inputCustFIO);
        for (int i = 0; i < numberCustomers; i++)
            if (ContainerCustomers[i].GetCustomerFIO() == inputCustFIO)
                inputItem = 'r';
        if (inputItem != 'r') {
            cout << "Выберите тип клиента (1: Физическое лицо, 2:Юридическое лицо): "; cin >> inputItem;
            if (inputItem == '1')
                newCustomer.SetTypeCustomer(TypeCustomer::Natural);
            else if (inputItem == '2')
                newCustomer.SetTypeCustomer(TypeCustomer::Legal);
            else inputItem = 'r';
            if (inputItem != 'r') {
                cout << "Введите начальный счет клиента: "; cin >> inputCustAccount;
                if (newCustomer.SetCustomerFirstAccount(inputCustAccount)) {
                    numberCustomers++;
                    newCustomer.SetCustomerFIO(inputCustFIO);
                    ContainerCustomers.push_back(newCustomer);
                    return true;
                }
            }
        }
        return false;
    };
    bool DeleteCustomer() {
        string inputCustFIO; char inputItem = '0';
        cout << "Введите ФИО клиента (латиница): ";
        getline(cin, inputCustFIO); getline(cin, inputCustFIO);
        for (int i = 0; i < numberCustomers; i++)
            if (ContainerCustomers[i].GetCustomerFIO() == inputCustFIO) {
                cout << "Удаление клиента из банка \"" << GetBankName() << "\" (1: Подтверждение, 2: Отмена): "; cin >> inputItem;
                if (inputItem == '1') {
                    ContainerCustomers[i].~Customer();
                    ContainerCustomers.erase(ContainerCustomers.begin() + i);
                    numberCustomers--;
                    return true;
                }
                else if (inputItem == '2')
                    cout << "Вы отменили операцию" << endl;

            }
        return false;
    };
    bool DepasiteMoneyBankCustomer() {
        string inputCustFIO; char inputItem = '0'; double inputMoney;
        cout << "Введите ФИО клиента (латиница): ";
        getline(cin, inputCustFIO); getline(cin, inputCustFIO);
        for (int i = 0; i < numberCustomers; i++)
            if (ContainerCustomers[i].GetCustomerFIO() == inputCustFIO) {
                cout << "Введите сумму: "; cin >> inputMoney;
                if (ContainerCustomers[i].DepositMoney(inputMoney))
                    return true;
            }
        return false;
    };
    bool WithdrawalMoneyBankCustomer() {
        string inputCustFIO; char inputItem = '0'; double inputMoney;
        cout << "Введите ФИО клиента (латиница): ";
        getline(cin, inputCustFIO); getline(cin, inputCustFIO);
        for (int i = 0; i < numberCustomers; i++)
            if (ContainerCustomers[i].GetCustomerFIO() == inputCustFIO) {
                cout << "Введите сумму: "; cin >> inputMoney;
                if (ContainerCustomers[i].WithdrawalMoney(inputMoney))
                    return true;
            }
        return false;
    };
    bool TransferringMoney(vector <Bank>& ContainerBanks) {
        char inputItem; double inputMoney;
        string BankRecipientName, ClientSenderFIO, ClientRecipientFIO;
        cout << "Введите ФИО клиента-отправителя: ";
        getline(cin, ClientSenderFIO); getline(cin, ClientSenderFIO);
        for (int i = 0; i < numberCustomers; i++)
            if (ContainerCustomers[i].GetCustomerFIO() == ClientSenderFIO
                && ContainerCustomers[i].GetCustomerType() == TypeCustomer::Legal) {
                cout << "Введите ФИО клиента-получателя: ";
                getline(cin, ClientRecipientFIO);
                for (int bank = 0; bank < ContainerBanks.size(); bank++)
                    if (ContainerBanks[bank].GetBankName() != nameBank)
                        for (int j = 0; j < ContainerBanks[bank].GetNumberCustomers(); j++)
                            if (ContainerBanks[bank].GetCustomers()[j].GetCustomerFIO() == ClientRecipientFIO
                                && ContainerBanks[bank].GetCustomers()[j].GetCustomerType() == TypeCustomer::Legal) {
                                cout << "Клиент-получатель из банка \"" << ContainerBanks[bank].GetBankName();
                                cout << "\"? (1: Подтверждение, 2: Отмена): "; cin >> inputItem;
                                if (inputItem == '1') {
                                    cout << "Введите сумму: "; cin >> inputMoney;
                                    cout << "Сумма перевода с комиссией: " << GetCommission(inputMoney) << endl;
                                    if (ContainerCustomers[i].WithdrawalMoney(GetCommission(inputMoney))) {
                                        amount += inputMoney * 0.01 * procent;
                                        ContainerBanks[bank].GetCustomers()[j].DepositMoney(inputMoney);
                                        return true;
                                    }
                                }
                            }
            }
        return false;
    };
    double GetBankAmount() {
        double sum = 0;
        for (int i = 0; i < numberCustomers; i++)
            sum += ContainerCustomers[i].GetCustomerAccount();
        return (amount + sum);
    };
    double GetCommission(double inputSumma) { return (inputSumma * (1 + 0.01 * procent)); };
    int GetNumberCustomers() { return numberCustomers; };
    string GetBankName() { return nameBank; };
    vector <Customer>& GetCustomers() { return ContainerCustomers; };
    void PrintBankSystem() {
        cout << "В банке \"" << GetBankName() << "\" числится " << GetNumberCustomers() << " клиентов:" << endl;
        for (int i = 0; i < numberCustomers; i++) {
            cout << "|__" << ContainerCustomers[i].GetCustomerFIO() << " сумма на счете: " << ContainerCustomers[i].GetCustomerAccount();
            cout << " тип клиента: " << PrintTypeCustomer(ContainerCustomers[i].GetCustomerType()) << endl << endl;
        }
        cout << "Общая сумма средств банка: " << GetBankAmount() << endl << endl;
    }
    ~Bank() { ContainerCustomers.clear(); ContainerCustomers.shrink_to_fit(); };
};

int main()
{
    setlocale(0, "Rus");
    bool getMenu = 1; char inputItem = '0'; string inputBankName;
    int inputBankProcent; Bank sampleBank; vector <Bank> ContainerBanks;
    do {
        cout << "\n1: Создание банка" << "\n2: Удаление банка" << "\n3: Вывести банковскую систему" << "\n4: Создание клиента";
        cout << "\n5: Удаление клиента" << "\n6: Положить средства на счет" << "\n7: Снять средства со счета"
            << "\n8: Перевести средства" << "\n9: Выйти из программы\n" << endl;
        cout << "Введите пункт: "; cin >> inputItem;
        if (inputItem == '1') {
            cout << "Введите название банка: "; cin >> inputBankName;
            cout << "Введите процент при переводе средств: "; cin >> inputBankProcent;
            sampleBank.SetBankName(inputBankName);
            sampleBank.SetBankProcent(inputBankProcent);
            ContainerBanks.push_back(sampleBank);
            cout << "Банк создан" << endl;
        }
        else if (inputItem == '2') {
            cout << "Введите название банка: "; cin >> inputBankName;
            for (int i = 0; i < ContainerBanks.size(); i++)
                if (ContainerBanks[i].GetBankName() == inputBankName)
                    if (ContainerBanks[i].GetNumberCustomers() == 0) {
                        inputItem = 'k';
                        ContainerBanks[i].~Bank();
                        ContainerBanks.erase(ContainerBanks.begin() + i);
                        cout << "Банк удален" << endl;
                    }
            if (inputItem != 'k')
                cout << "Произошла ошибка" << endl;
        }
        else if (inputItem == '3') {
            for (auto& bank : ContainerBanks)
                bank.PrintBankSystem();
        }
        else if (inputItem == '4') {
            cout << "Введите название банка: "; cin >> inputBankName;
            for (auto& bank : ContainerBanks)
                if (bank.GetBankName() == inputBankName) {
                    if (bank.AddNewCustomer())
                        cout << "Добавлен клиент" << endl;
                    else cout << "Произошла ошибка" << endl;
                }
        }
        else if (inputItem == '5') {
            cout << "Введите название банка: "; cin >> inputBankName;
            for (auto& bank : ContainerBanks)
                if (bank.GetBankName() == inputBankName) {
                    if (bank.DeleteCustomer())
                        cout << "Удален клиент" << endl;
                    else cout << "Произошла ошибка" << endl;
                }
        }
        else if (inputItem == '6') {
            cout << "Введите название банка: "; cin >> inputBankName;
            for (auto& bank : ContainerBanks)
                if (bank.GetBankName() == inputBankName) {
                    if (bank.DepasiteMoneyBankCustomer())
                        cout << "Операция выполнена" << endl;
                    else cout << "Произошла ошибка" << endl;
                }
        }
        else if (inputItem == '7') {
            cout << "Введите название банка: "; cin >> inputBankName;
            for (auto& bank : ContainerBanks)
                if (bank.GetBankName() == inputBankName) {
                    if (bank.WithdrawalMoneyBankCustomer())
                        cout << "Операция выполнена" << endl;
                    else cout << "Произошла ошибка" << endl;
                }
        }
        else if (inputItem == '8') {
            for (int i = 0; i < ContainerBanks.size(); i++) {
                if (ContainerBanks[i].TransferringMoney(ContainerBanks)) {
                    inputItem = 'k';
                    i = ContainerBanks.size();
                    cout << "Перевод выполнен" << endl;
                }
            }
            if (inputItem != 'k')
                cout << "Произошла ошибка" << endl;
        }
        else if (inputItem == '9') getMenu = false;
    } while (getMenu);
    return 0;
}
