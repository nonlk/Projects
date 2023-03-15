# -*- coding: utf-8 -*-
"""
Created on Mon Nov 29 23:12:31 2021

@author: HP
"""

from terminale import Terminale

if __name__ == "__main__":

    terminale1 = Terminale()
    print(terminale1)
    while True:
        terminale1.show_menu()
        choice = input()
        terminale1.process(choice)
        