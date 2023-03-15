/*Иерархия графических компонентов. Имеется набор компонентов: окно, надпись,
список, кнопка, панель, линия. Компоненты окно и панель могут содержать
другие компоненты. Компоненты могут быть видимы или скрыты,
компоненты можно перемещать в пределах контейнера. Отобразить
иерархию компонентов и навигацию по ней в виде дерева.*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class GraphicComponent { //Базовый класс для графических компонентов
protected:
    int id; //Поле номера компонента
    string visitable; //Поле видимости компонента
public:
    GraphicComponent() : id(0), visitable(" <+> ") {};
    void SetId(const int InpId) { id = InpId; };
    const int GetId() { return id; };
    void SetVisitable() { visitable = (visitable == " <+> ") ? " <-> " : " <+> "; }; //Изменение видимости
    const string GetVisitable() { return visitable; };
    virtual string GetName() {}; //Абстрактный метод для полиморфизма
};

class Line : public GraphicComponent { //Производный класс Линия
public:
    string GetName() override { return "Линия"; };
};

class Title : public GraphicComponent { //Производный класс Надпись
public:
    string GetName() override { return "Надпись"; };
};

class Button :public GraphicComponent { //Производный класс Кнопка
public:
    string GetName() override { return "Кнопка"; };
};

class List :public GraphicComponent { //Производный класс Список
public:
    string GetName() override { return "Список"; };
};

class Panel :public GraphicComponent { //Дочерний класс Панель
private:
    vector <Line> ContainerLines; //Контейнер хранения прикрепленных Линий
    vector <List> ContainerLists; //Контейнер хранения прикрепленных Списков
    vector <Title> ContainerTitle; //Контейнер хранения прикрепленных Надписей
    vector <Button> ContainerButton; //Контейнер хранения прикрепленных Кнопок
public:
    Panel() : ContainerButton(NULL), ContainerLines(NULL), ContainerLists(NULL), ContainerTitle(NULL) {};
    string GetName() override { return "Панель"; };
    bool AddNewComponent(char input, int IdNewComp) { //Добавление определенного компонента в соответствующий контейнер
        if (input == '1') {
            Line newComp;
            ContainerLines.push_back(newComp);
            ContainerLines[ContainerLines.size() - 1].SetId(IdNewComp);
            return true;
        }
        else if (input == '2') {
            Title newComp;
            ContainerTitle.push_back(newComp);
            ContainerTitle[ContainerTitle.size() - 1].SetId(IdNewComp);
            return true;
        }
        else if (input == '3') {
            Button newComp;
            ContainerButton.push_back(newComp);
            ContainerButton[ContainerButton.size() - 1].SetId(IdNewComp);
            return true;
        }
        else if (input == '4') {
            List newComp;
            ContainerLists.push_back(newComp);
            ContainerLists[ContainerLists.size() - 1].SetId(IdNewComp);
            return true;
        }
        else return false;
    };
    bool DeleteComponent(char input, int IdComp) { //Удаление компонента из контейнера
        if (input == '4') {
            for (int i = 0; i < ContainerLists.size(); i++)
                if (ContainerLists[i].GetId() == IdComp) {
                    ContainerLists.erase(ContainerLists.begin() + i);
                    return true;
                }

        }
        else if (input == '1') {
            for (int i = 0; i < ContainerLines.size(); i++)
                if (ContainerLines[i].GetId() == IdComp) {
                    ContainerLines.erase(ContainerLines.begin() + i);
                    return true;
                }
        }
        else if (input == '3') {
            for (int i = 0; i < ContainerButton.size(); i++)
                if (ContainerButton[i].GetId() == IdComp) {
                    ContainerButton.erase(ContainerButton.begin() + i);
                    return true;
                }
        }
        else if (input == '2') {
            for (int i = 0; i < ContainerTitle.size(); i++)
                if (ContainerTitle[i].GetId() == IdComp) {
                    ContainerTitle.erase(ContainerTitle.begin() + i);
                    return true;
                }
        }
        return false;
    };
    bool SetVisitableForComponent(char input, int IdComp) { //Изменение видимости для конпонентов в контейнерах
        cout << "У какого компонента вы хотите изменить видимость? (1: Линия, 2: Надпись, 3: Кнопка, 4: Список): "; cin >> input;
        cout << "Введите номер компонента: "; cin >> IdComp;
        if (input == '1') {
            ContainerLines[IdComp - 1].SetVisitable();
            return true;
        }
        else if (input == '2') {
            ContainerTitle[IdComp - 1].SetVisitable();
            return true;
        }
        else if (input == '3') {
            ContainerButton[IdComp - 1].SetVisitable();
            return true;
        }
        else if (input == '4') {
            ContainerLists[IdComp - 1].SetVisitable();
            return true;
        }
        else return false;
    };
    void PrintComponents() { //Печать всех прикрепленных к Панели компонентов 
        for (int j = 0; j < ContainerLists.size(); j++)
            cout << "     |__" << ContainerLists[j].GetName() << " " << ContainerLists[j].GetId() << ContainerLists[j].GetVisitable() << endl;
        for (int j = 0; j < ContainerLines.size(); j++)
            cout << "     |__" << ContainerLines[j].GetName() << " " << ContainerLines[j].GetId() << ContainerLines[j].GetVisitable() << endl;
        for (int j = 0; j < ContainerTitle.size(); j++)
            cout << "     |__" << ContainerTitle[j].GetName() << " " << ContainerTitle[j].GetId() << ContainerTitle[j].GetVisitable() << endl;
        for (int j = 0; j < ContainerButton.size(); j++)
            cout << "     |__" << ContainerButton[j].GetName() << " " << ContainerButton[j].GetId() << ContainerButton[j].GetVisitable() << endl;
    }
    ~Panel() { ContainerTitle.clear(); ContainerButton.clear(); ContainerLists.clear(); ContainerLines.clear(); }; //Очищение памяти
};

class Window :public GraphicComponent { //Дочерний класс Окно
private:
    vector <Panel> ContainerPanels; //Контейнер Панелей, принадлежащих окну
public:
    Window() :ContainerPanels(NULL) {};
    string GetName() { return "Окно"; };
    int GetSizeContainerPanels() { return ContainerPanels.size(); };
    void OrderContainerPanels() { //Пересчет номеров после удаления Панели
        for (int i = 0; i < ContainerPanels.size(); i++)
            ContainerPanels[i].SetId(i + 1);
    }
    void AddNewPanel() { //Добавление Панели в контейнер
        Panel newPanel;
        ContainerPanels.push_back(newPanel);
        ContainerPanels[ContainerPanels.size() - 1].SetId(ContainerPanels.size());
    };
    bool AddNewPanelComponent(int inpIdPanel, int IdNewComp, char input) { //Добавление компонента в контейнер определенной Панели
        if (inpIdPanel <= ContainerPanels.size()) {
            cout << "Какой компонент вы хотите добавить в панель? (1: Линия, 2: Надпись, 3: Кнопка, 4: Список): "; cin >> input;
            cout << "Введите номер компонента: "; cin >> IdNewComp;
            ContainerPanels[inpIdPanel - 1].AddNewComponent(input, IdNewComp);
            return true;
        }
        else return false;
    };
    void DeletePanelById(int inpIdPanel) { //Удаление Панели по номеру
        ContainerPanels[inpIdPanel - 1].~Panel(); //Удаление всех вложенных компонентов, очистка памяти
        ContainerPanels.erase(ContainerPanels.begin() + (inpIdPanel - 1));
        OrderContainerPanels();
    };
    bool DeletePanelComponent(char input, int inpIdPanel, int IdComp) { //Удаление компонента, закрепленного за определенной Панелью
        if (inpIdPanel <= ContainerPanels.size()) {
            cout << "Какой компонент вы хотите удалить? (1: Линия, 2: Надпись, 3: Кнопка, 4: Список): "; cin >> input;
            cout << "Введите номер компонента: "; cin >> IdComp;
            ContainerPanels[inpIdPanel - 1].DeleteComponent(input, IdComp);
            return true;
        }
        return false;
    };
    bool ChangePanelsForComponents(char input, int IdPresentPanel, int IdFuturePanel, int IdComp) { //Перемещение компонента между Панелями
        cout << "Какой компонент вы хотите переместить? (1: Линия, 2 : Надпись, 3 : Кнопка, 4 : Список) : "; cin >> input;
        cout << "Введите номер компонента: "; cin >> IdComp;
        if (input == '1' || input == '2' || input == '3' || input == '4') {
            ContainerPanels[IdPresentPanel - 1].DeleteComponent(input, IdComp); //Удаление из начальной Панели
            ContainerPanels[IdFuturePanel - 1].AddNewComponent(input, IdComp); //Добаление в будущую Панель
            return true;
        }
        else return false;
    };
    bool SetVisitableForPanel(int IdPanel) { //Изменение видимости у Панели
        if (IdPanel <= ContainerPanels.size()) {
            ContainerPanels[IdPanel - 1].SetVisitable();
            return true;
        }
        else return false;
    };
    bool SetVisistableForComponent(int IdPanel, int IdComp, char input) { //Изменение видимости у компонента Панели
        if (IdPanel <= ContainerPanels.size()) {
            cout << "Введите номер компонента: "; cin >> IdComp;
            ContainerPanels[IdPanel].SetVisitableForComponent(input, IdComp);
            return true;
        }
        else return false;
    };
    void PrintHierar() { //Вывод всей иерархии компонентов Окна
        cout << "-" << GetName() << " " << GetId() << GetVisitable() << endl;
        for (int i = 0; i < ContainerPanels.size(); i++) {
            cout << "  |__" << ContainerPanels[i].GetName() << " " << ContainerPanels[i].GetId() << ContainerPanels[i].GetVisitable() << endl;
            ContainerPanels[i].PrintComponents(); //Вывод иерархии компонентов Панели
        }
    }
    ~Window() {
        for (auto& tmp : ContainerPanels)
            tmp.~Panel(); //Очищение памяти
        ContainerPanels.clear(); //Очищение памяти
    };
};

int main()
{
    setlocale(0, "Rus");
    vector <Window> vecWindows; //Контейнер Окон
    char inpOption, input = '0'; bool option = true;
    int idComp = 0, idWindow, idPanel, idPanel2;
    while (option) {
        cout << "\n\n1: Создать кoмпонент\n2: Удалить компонент\n3: Вывести иерархию компонентов\n4: Переместить компонент\n5: Поменять видимость компоненту\n6: Выйти\n";
        cout << "Введите пункт: "; cin >> inpOption;
        if (inpOption == '1') {
            cout << "Какой компонент создать? (1: Окно, 2: Панель, 3: Другой графический компонент): "; cin >> input;
            if (input == '1') {
                Window W;
                vecWindows.push_back(W);
                vecWindows[vecWindows.size() - 1].SetId(vecWindows.size());
                cout << "Вы добавили окно" << endl;
            }
            else if (input == '2') {
                cout << "Введите номер окна: "; cin >> idWindow;
                if (idWindow <= vecWindows.size()) {
                    vecWindows[idWindow - 1].AddNewPanel();
                    cout << "Вы добавили панель" << endl;
                }
                else cout << "Нет такого окна" << endl;
            }
            else if (input == '3') {
                cout << "Введите номер окна: "; cin >> idWindow;
                if (idWindow <= vecWindows.size()) {
                    cout << "Введите номер панели: "; cin >> idPanel;
                    if (vecWindows[idWindow - 1].AddNewPanelComponent(idPanel, idComp, input))
                        cout << "Вы добавили компонент" << endl;
                    else  cout << "Нет такой панели" << endl;
                }
                else cout << "Нет такого окна" << endl;
            }
        }
        else if (inpOption == '2') {
            cout << "Какой компонент удалить? (1: Окно, 2: Панель, 3: Другой графический компонент): "; cin >> input;
            if (input == '1') {
                cout << "Введите номер окна: "; cin >> idWindow;
                if (idWindow <= vecWindows.size()) {
                    vecWindows[idWindow - 1].~Window();
                    vecWindows.erase(vecWindows.begin() + idWindow - 1);
                    for (int i = 0; i < vecWindows.size(); i++)
                        vecWindows[i].SetId(i + 1);
                    cout << "Вы удалили окно" << endl;
                }
                else cout << "Нет такого окна" << endl;
            }
            else if (input == '2') {
                cout << "Введите номер окна: "; cin >> idWindow;
                if (idWindow <= vecWindows.size()) {
                    cout << "Введите номер панели: "; cin >> idPanel;
                    if (idPanel <= vecWindows[idWindow - 1].GetSizeContainerPanels()) {
                        vecWindows[idWindow - 1].DeletePanelById(idPanel);
                        cout << "Вы удалили панель" << endl;
                    }
                    else  cout << "Нет такой панели" << endl;
                }
                else cout << "Нет такого окна" << endl;
            }
            else if (input == '3') {
                cout << "Введите номер окна: "; cin >> idWindow;
                if (idWindow <= vecWindows.size()) {
                    cout << "Введите номер панели: "; cin >> idPanel;
                    if (vecWindows[idWindow - 1].DeletePanelComponent(input, idPanel, idComp))
                        cout << "Вы удалили компонент" << endl;
                    else  cout << "Нет такой панели" << endl;
                }
                else cout << "Нет такого окна" << endl;
            }
        }
        else if (inpOption == '3') {
            for (auto& wind : vecWindows)
                wind.PrintHierar();
        }
        else if (inpOption == '4') {
            cout << "Введите номер окна: "; cin >> idWindow;
            if (idWindow <= vecWindows.size()) {
                cout << "Введите номер панели, в котором находится компонент: "; cin >> idPanel;
                cout << "Введите номер панели, в котором будет находиться компонент: "; cin >> idPanel2;
                if (vecWindows[idWindow - 1].ChangePanelsForComponents(input, idPanel, idPanel2, idComp))
                    cout << "Вы переместили компонент" << endl;
                else  cout << "Нет такой панели" << endl;
            }
            else cout << "Нет такого окна" << endl;
        }
        else if (inpOption == '5') {
            cout << "Какому компоненту поменять видимость? (1: Окно, 2: Панель, 3: Другой графический компонент): "; cin >> input;
            if (input == '1') {
                cout << "Введите номер окна: "; cin >> idWindow;
                if (idWindow <= vecWindows.size()) {
                    vecWindows[idWindow - 1].SetVisitable();
                    cout << "Вы поменяли видимость окна" << endl;
                }
                else cout << "Нет такого окна" << endl;
            }
            else if (input == '2') {
                cout << "Введите номер окна: "; cin >> idWindow;
                if (idWindow <= vecWindows.size()) {
                    cout << "Введите номер панели: "; cin >> idPanel;
                    if (vecWindows[idWindow - 1].SetVisitableForPanel(idPanel))
                        cout << "Вы поменяли видимость панели" << endl;
                    else  cout << "Нет такой панели" << endl;
                }
                else cout << "Нет такого окна" << endl;
            }
            else if (input == '3') {
                cout << "Введите номер окна: "; cin >> idWindow;
                if (idWindow <= vecWindows.size()) {
                    cout << "Введите номер панели: "; cin >> idPanel;
                    if (vecWindows[idWindow - 1].SetVisistableForComponent(idPanel, idComp, input))
                        cout << "Вы поменяли видимость компонента" << endl;
                    else  cout << "Нет такой панели" << endl;
                }
                else cout << "Нет такого окна" << endl;
            }
        }
        else if (inpOption == '6') {
            option = false; //Выход из цикла
        }
        else cout << "Такой операции нет" << endl;
    }
    for (auto& wind : vecWindows)
        wind.~Window(); //Очищение памяти
    vecWindows.clear(); //Очищение памяти
    return 0;
}

