/*Реализация решения задачи нахождения 
полинома Лагранжа второй и третьей степени,
точности полученного интерполяционного значения
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector <double> findVec(vector <double> Vec) {
    double args;
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ": ";
        cin >> args;
        Vec.push_back(args); // добавляем элемент в конец вектора
    }
    return Vec;
}

int checkRepeat(vector <double> x, int ier) {
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (x[i] == x[j]) // проверка на повторения аргументов
                ier = 1;
        }
    }
    return ier;
}

int findThreeArguments(vector <double> x, double xx) {
    double dist = abs(x[0] - xx); // расчет модуля разницы между первым элементом в векторе и введенным хх
    int i = 0; // номер первого аргумента в векторе
    for (int j = 1; j < 4; j++)
        if (abs(x[j] - xx) > dist) { // проверка: если модуль разницы с последующим элементом больше, чем с предыдущим
            dist = abs(x[j] - xx); // то сохраняем модуль разности
            i = j; // запоминаем позицию элемента
        }
    return i;
}

double lagrange(vector <double> x, vector <double> y, double xx) {
    double dop_y, sum = 0;
    for (int i = 0; i < y.size(); i++) {
        dop_y = y[i];
        for (int j = 0; j < x.size(); j++) {
            if (i != j)
                dop_y *= (xx - x[j]) / (x[i] - x[j]); // часть формулы лагранжа
        }
        sum += dop_y;
    }
    return sum;
}

int main()
{
    vector <double> x, y;
    double xx, yy, yy3;
    cout << "find x: " << endl;
    x = findVec(x);
    cout << "\nfind y: " << endl;
    y = findVec(y);
    cout << "\nfind xx: ";
    cin >> xx;
    cout << "\nIER: " << checkRepeat(x, 0) << endl; // выводим результат работы второй функции
    if (checkRepeat(x, 0) != 1) { // если нет повторений, выводим все результаты
        yy3 = lagrange(x, y, xx); // полином Лагранжа третьей степени
        int i = findThreeArguments(x, xx); // номер элемента самого дальнего от хх
        x.erase(x.begin() + i); // удаление самого дальнего элемента из вектора
        y.erase(y.begin() + i); // удаление соответствующего значения функции
        yy = lagrange(x, y, xx); // полином Лагранжа второй степени
        cout << "YY: " << yy << "\nYY3: " << yy3 << endl;
        cout << "EPS_YY: " << abs(yy3 - yy) << endl; // точность полученного интерполяционного значения
    }
    x.clear(); // очистка памяти 
    y.clear(); // очистка памяти
    system("pause");
    return 0;
}