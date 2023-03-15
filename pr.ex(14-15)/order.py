# -*- coding: utf-8 -*-
"""
Created on Thu Nov 25 13:11:21 2021

@author: HP
"""

import time

class order:
    """Класс Заказ содержит информацию о заказе."""

    # Переменная класса для определения номера заказа
    ord_num = 0

    def __init__(self):
        """Конструктор класса."""
        # Хранит экземпляры класса Пицца и его потомков
        self.ordered_pizza = []
        order.ord_num += 1

    def __str__(self):
        """Вернуть содержимое заказа и его сумму.

        Формат вывода:

        Заказ №2
        1. Пицца: Пепперони | Цена: 350.00 р.
           Тесто: тонкое Соус: томатный
           Начинка: пепперони, сыр моцарелла
        2. Пицца: Барбекю | Цена: 450.00 р.
           Тесто: тонкое Соус: барбекю
           Начинка: бекон, ветчина, зелень, сыр моцарелла
        Сумма заказа: 800.00 р.

        """
        print("Заказ №{}".format(self.ord_num))
        for i in range(len(self.ordered_pizza)):
            print("{:<}.".format(i + 1), self.ordered_pizza[i]) 
        res = self.summa()
        return "Сумма заказа: {:.2f} p.".format(res)

    def plus(self, pizzza):
        """Добавить пиццу в заказ."""
        self.ordered_pizza.append(pizzza)
        

    def summa(self):
        """Вернуть сумму заказа."""
        summ = 0
        for i in self.ordered_pizza:
            summ += i.price
            
        return int(summ)

    def execute(self):
        """Выполнить заказ.

        Для каждой пиццы в заказе: подготовить, испечь, нарезать и упаковать.
        Сообщить, что заказ готов и пожелать приятного аппетита.

        Для визуального эффекта, каждое действие осуществляется с "задержкой",
        используя time.sleep(1).

        Формат вывода:

        Заказ поступил на выполнение...
        1. Пепперони
        Начинаю готовить пиццу Пепперони
          - замешиваю тонкое тесто...
          - добавляю соус: томатный...
          - и, конечно: пепперони, сыр моцарелла...
        Выпекаю пиццу... Готово!
        Нарезаю на аппетитные кусочки...
        Упаковываю в фирменную упаковку и готово!

        Заказ №2 готов! Приятного аппетита!
        """
        print("\nЗаказ поступил на выполнение...")
        for i in range(len(self.ordered_pizza)):
            print(i + 1, ".", self.ordered_pizza[i].name)
            self.ordered_pizza[i].prepare()
            time.sleep(1)
            self.ordered_pizza[i].bake()
            time.sleep(1)
            self.ordered_pizza[i].cut()
            time.sleep(1)
            self.ordered_pizza[i].pack()
            time.sleep(2)
        print("\nЗаказ №{} готов! Приятного аппетита!".format(self.ord_num))
            