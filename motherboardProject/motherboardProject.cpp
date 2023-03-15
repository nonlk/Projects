/*Персональный компьютер. Реализуемые объекты: процессор, память, системная плата,
устройства ввода вывода. Реализовать процедуры ввода/вывода с учетом
возможностей оборудования.*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class TypeDevice {
    Monitor, Keyboard, Mouse, Speakers, Processor, RAM, Nothing
}; //Разграничение УВВ, ОЗУ, Процессора

string PrintNameDevice(TypeDevice Type) {
    switch (Type) {
    case TypeDevice::Monitor:
        return "Монитор";
    case TypeDevice::Keyboard:
        return "Клавиатура";
    case TypeDevice::Mouse:
        return "Мышь";
    case TypeDevice::Speakers:
        return "Колонки";
    case TypeDevice::Processor:
        return "Процессор";
    case TypeDevice::RAM:
        return "ОЗУ";
    case TypeDevice::Nothing:
        return " ";
    default:
        return " ";
    }
};

class Device {
protected:
    bool connect; //Подключение
    string name;
    TypeDevice type;
public:
    Device() : connect(0), type(TypeDevice::Nothing) {};
    void SetName(string inputName) { name = inputName; };
    void SetConnect() { connect = (connect) ? false : true; }; //Изменение подключения
    virtual void SetType(TypeDevice inputType) { type = inputType; }; //Изменение типа устройства
    string GetName() { return name; };
    bool GetConnect() { return connect; };
    TypeDevice GetType() { return type; };
};

class Memory : public Device {
    int amount; //Объем ОЗУ
public:
    Memory() : Device(), amount(2) {};
    bool SetAmount(int inputAmount) {
        if (inputAmount >= 2 && inputAmount <= 16) { //Допустимый объем ОЗУ от 2 до 16 гб
            amount = inputAmount;
            return true;
        }
        return false;
    };
    void SetType(TypeDevice inputType = TypeDevice::RAM) override { type = inputType; }; //Переопределение типа устройства
    int GetAmount() { return amount; };
    ~Memory() { amount = 0; };
};

class Processor : public Device {
    int numberCores; //Кол-во ядер
    string typeProcessor; //Тип процессора
public:
    Processor() : Device(), numberCores(2) {};
    bool SetNumberCores(int inputNumber) {
        if (inputNumber >= 2 && inputNumber <= 8) { //Допустимое число ядер от 2 до 8
            numberCores = inputNumber;
            return true;
        }
        return false;
    };
    void SetProcessorType(string inputType) { typeProcessor = inputType; };
    void SetType(TypeDevice inputType = TypeDevice::Processor) override { type = inputType; }; //Переопределение типа устройства
    int GetNumberCores() { return numberCores; };
    string GetProcessorType() { return typeProcessor; };
    ~Processor() { numberCores = 0; typeProcessor = " "; };
};

class Motherboard {
    Device* ContainerDevices = new Device[4]; //Массив УВВ
    Memory RAM_Memory; //ОЗУ платы
    Processor SystemProcessor; //Процессор платы
public:
    Motherboard() {
        ContainerDevices[0].SetType(TypeDevice::Monitor);
        ContainerDevices[1].SetType(TypeDevice::Keyboard);
        ContainerDevices[2].SetType(TypeDevice::Mouse);
        ContainerDevices[3].SetType(TypeDevice::Speakers);
        for (int i = 0; i < 4; i++)
            ContainerDevices[i].SetName(PrintNameDevice(ContainerDevices[i].GetType())); //Определение имен
    };
    bool CreateMotherboard() { //Создание новой платы
        char inputItem = '0'; int inputIntItem = 0;
        SystemProcessor = Processor();
        cout << "Выберите тип процессора (1 - Intel, 2 - AMD): "; cin >> inputItem;
        if (inputItem == '1') {
            SystemProcessor.SetProcessorType("Intel");
            cout << "Укажите количество ядер: "; cin >> inputIntItem;
            if (SystemProcessor.SetNumberCores(inputIntItem))
                SystemProcessor.SetConnect(); //Подключение процессора
        }
        else if (inputItem == '2') {
            SystemProcessor.SetProcessorType("AMD");
            cout << "Укажите количество ядер: "; cin >> inputIntItem;
            if (SystemProcessor.SetNumberCores(inputIntItem))
                SystemProcessor.SetConnect(); //Подключение процессора
        }
        RAM_Memory = Memory();
        cout << "Укажите объем ОЗУ: "; cin >> inputIntItem;
        if (RAM_Memory.SetAmount(inputIntItem))
            RAM_Memory.SetConnect(); //Подключение ОЗУ
        RAM_Memory.SetType(); SystemProcessor.SetType(); //Переопределние типов
        RAM_Memory.SetName(PrintNameDevice(RAM_Memory.GetType())); //Переопределние имен
        SystemProcessor.SetName(PrintNameDevice(SystemProcessor.GetType()));
        if (RAM_Memory.GetConnect() == 1 && SystemProcessor.GetConnect() == 1) { //Проверка успешности подключения ОЗУ и процессора
            cout << "Системная плата создана" << endl;
            return true;
        }
        else cout << "Произошла ошибка" << endl;
        return false;
    };
    bool AddNewDevice() { //Подключение УВВ
        char inputItem = '0';
        cout << "Выберите подключаемое устройство (1 - Монитор, 2 - Клавиатура, 3 - Мышь, 4 - Колонки): "; cin >> inputItem;
        if (inputItem == '1') {
            if (ContainerDevices[0].GetConnect() == 1) {
                cout << "Монитор уже подключен" << endl;
                return false;
            }
            else ContainerDevices[0].SetConnect(); //Подключение монитора
        }
        else if (inputItem == '2') {
            if (ContainerDevices[1].GetConnect() == 1) {
                cout << "Клавиатура уже подключена" << endl;
                return false;
            }
            else ContainerDevices[1].SetConnect(); //Подключение клавиатуры
        }
        else if (inputItem == '3') {
            if (ContainerDevices[2].GetConnect() == 1) {
                cout << "Мышь уже подключена" << endl;
                return false;
            }
            else ContainerDevices[2].SetConnect(); //Подключение мышт
        }
        else if (inputItem == '4') {
            if (ContainerDevices[3].GetConnect() == 1) {
                cout << "Колонки уже подключены" << endl;
                return false;
            }
            else ContainerDevices[3].SetConnect(); //Подключение колонок
        }
        else return false;
        return true;
    };
    bool DeleteDevice() { //Отключение УВВ
        char inputItem = '0';
        cout << "Выберите отключаемое устройство (1 - Монитор, 2 - Клавиатура, 3 - Мышь, 4 - Колонки): "; cin >> inputItem;
        if (inputItem == '1') {
            if (ContainerDevices[0].GetConnect() == 0) {
                cout << "Монитор уже отключен" << endl;
                return false;
            }
            else ContainerDevices[0].SetConnect(); //Отключение монитора
        }
        else if (inputItem == '2') {
            if (ContainerDevices[1].GetConnect() == 0) {
                cout << "Клавиатура уже отключена" << endl;
                return false;
            }
            else ContainerDevices[1].SetConnect(); //Отключение клавиатуры
        }
        else if (inputItem == '3') {
            if (ContainerDevices[2].GetConnect() == 0) {
                cout << "Мышь уже отключена" << endl;
                return false;
            }
            else ContainerDevices[2].SetConnect(); //Отключение мыши
        }
        else if (inputItem == '4') {
            if (ContainerDevices[3].GetConnect() == 0) {
                cout << "Колонки уже отключены" << endl;
                return false;
            }
            else ContainerDevices[3].SetConnect(); //Отключение колонок
        }
        else return false;
        return true;
    };
    void DeleteAllDevices() { //Отключение всех УВВ
        for (int i = 0; i < 4; i++)
            if (ContainerDevices[i].GetConnect() == 1)
                ContainerDevices[i].SetConnect(); //Отключение каждого подключенного УВВ
    };
    void PrintHierarMotherboard() { //Печать платы
        cout << "Системная плата: " << endl;
        cout << "   *" << SystemProcessor.GetName() << " " << SystemProcessor.GetProcessorType() << " " << SystemProcessor.GetNumberCores() << " ядер" << endl;
        cout << "   *" << RAM_Memory.GetName() << " " << RAM_Memory.GetAmount() << " ГБ" << endl;
        cout << "   *" << "Порты ввода-вывода:" << endl;
        for (int i = 0; i < 4; i++)
            if (ContainerDevices[i].GetConnect() == 1)
                cout << "      *" << ContainerDevices[i].GetName() << endl;
        cout << endl;
    };
    ~Motherboard() { ContainerDevices = nullptr; };
};

int main()
{
    setlocale(0, "rus");
    vector <Motherboard> ContainerMotherboards; int numberMotherboadrs = 0, inputItem;
    bool point = 1; char menuItem = '0';
    while (point) {
        cout << "\n\n1: Создать системную плату с устройствами" << "\n2: Подключить УВВ" << "\n3: Отключить УВВ" << "\n4: Отключить все УВВ";
        cout << "\n5: Удалить системную плату" << "\n6: Вывести все созданные платы" << "\n7: Выйти из программы" << endl;
        cout << "Введите пункт: "; cin >> menuItem;
        if (menuItem == '1') {
            Motherboard MB1;
            if (MB1.CreateMotherboard()) {
                ContainerMotherboards.push_back(MB1);
                numberMotherboadrs++;
            }
            else cout << "Ошибка" << endl;
        }
        else if (menuItem == '2') {
            cout << "Введите номер системной платы: "; cin >> inputItem;
            if (inputItem <= numberMotherboadrs) {
                if (ContainerMotherboards[inputItem - 1].AddNewDevice())
                    cout << "УВВ подключено" << endl;
                else cout << "Ошибка" << endl;
            }
            else cout << "Данная плата не была создана" << endl;
        }
        else if (menuItem == '3') {
            cout << "Введите номер системной платы: "; cin >> inputItem;
            if (inputItem <= numberMotherboadrs) {
                if (ContainerMotherboards[inputItem - 1].DeleteDevice())
                    cout << "УВВ отключено" << endl;
                else cout << "Ошибка" << endl;
            }
            else cout << "Данная плата не была создана" << endl;
        }
        else if (menuItem == '4') {
            cout << "Введите номер системной платы: "; cin >> inputItem;
            if (inputItem <= numberMotherboadrs) {
                ContainerMotherboards[inputItem - 1].DeleteAllDevices();
                cout << "УВВ отключены" << endl;
            }
            else cout << "Данная плата не была создана" << endl;
        }
        else if (menuItem == '5') {
            cout << "Введите номер системной платы: "; cin >> inputItem;
            if (inputItem <= numberMotherboadrs) {
                ContainerMotherboards.erase(ContainerMotherboards.begin() + inputItem - 1);
                cout << "Системная плата удалена" << endl;
                numberMotherboadrs--;
            }
            else cout << "Данная плата не была создана" << endl;
        }
        else if (menuItem == '6') {
            for (int i = 0; i < numberMotherboadrs; i++) {
                cout << i + 1 << " "; ContainerMotherboards[i].PrintHierarMotherboard();
            }
        }
        else if (menuItem == '7')
            point = 0;
        else cout << "Ошибка" << endl;
    }
    ContainerMotherboards.clear(); ContainerMotherboards.shrink_to_fit();
    return 0;
}