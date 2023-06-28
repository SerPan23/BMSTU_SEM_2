import random

from PyQt6 import uic
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QAction
from PyQt6.QtWidgets import QMainWindow, QTableWidgetItem, QMessageBox

from math import *

import numpy as np

import matplotlib
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg
from matplotlib.figure import Figure

matplotlib.use('QtAgg')
import matplotlib.pyplot as plt

import mplcyberpunk

plt.style.use("cyberpunk")


def error_msg():
    dlg = QMessageBox()
    dlg.setText("Ошибка вводимых данных!")
    dlg.exec()


def f(x, func):
    try:
        result = eval(func)
    except:
        return None
    return result


def get_intervals(a, b, h, func):
    x_0 = a
    x_1 = x_0 + h
    intervals = []

    f_a = f(a, func)
    f_b = f(b, func)

    if f_a is None or f_b is None:
        return None

    if f_a == 0:
        intervals.append((a, a + h))
    if f_b == 0:
        intervals.append((b - h, b))

    while x_0 < b:
        if x_1 > b:
            x_1 = b
        if f(x_1, func) == 0 or f(x_0, func) * f(x_1, func) < 0 and a <= x_0 <= x_1 <= b:
            intervals.append((x_0, x_1))
        x_0 += h
        x_1 += h

    return intervals


# error code:
# 0 - ok
# 1 - more operation
# 2 - diapason error

def sec_method(start, end, eps, n_max, j, func):
    x_0 = start
    x_1 = end
    section = "[{:<9.3g}; {:>9.3g}]".format(start, end)
    error = (j + 1, section, "Error", "Error", "Error", 1)
    for i in range(n_max):
        x_2 = x_0 - (x_1 - x_0) * f(x_0, func) / (f(x_1, func) - f(x_0, func))
        x_0 - x_1
        x_1 = x_2
        if not (start <= x_2 <= end):
            error = (j + 1, section, "Error", "Error", "Error", 2)
            break
        if x_2 == "inf":
            error = (j + 1, section, "inf", "Error", "Error", 2)
            break
        if abs(f(x_2, func)) < eps:
            break
    else:
        return error

    return j + 1, section, format(x_2, "<9.3g"), format(f(x_2, func), "<.0g"), i + 1, 0


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi('MainWindow.ui', self)
        self.show()
        self.start.clicked.connect(self._start_counting)

        menu = self.menuBar()

        menu = menu.addMenu("Меню")
        button_error_codes = QAction("&Коды ошибок", self)
        button_error_codes.triggered.connect(self.showButtonErrorCodes)

        menu.addAction(button_error_codes)

        button_show_info = QAction("&Об авторе", self)
        button_show_info.triggered.connect(self.showInfo)

        menu.addAction(button_show_info)


    def is_input_data_correct(self):
        try:
            func = self.func_le.text()
            f(1, func)
            f(1, func) * f(1, func)
            a = float(self.a_le.text())
            b = float(self.b_le.text())
            h = float(self.h_le.text())
            n_max = int(self.n_max_le.text())
            eps = float(self.eps_le.text())
            if a > b:
                raise Exception
            if h <= 0:
                raise Exception
            if n_max <= 0:
                raise Exception
            if eps < 0 or eps > 1:
                raise Exception
        except:
            return 0

        return 1

    def _start_counting(self):
        if (self.is_input_data_correct()):
            func = self.func_le.text()
            a = float(self.a_le.text())
            b = float(self.b_le.text())
            h = float(self.h_le.text())
            n_max = int(self.n_max_le.text())
            eps = float(self.eps_le.text())
        else:
            error_msg()
            return

        # print(func, a, b, h, n_max, eps)

        intervals = get_intervals(a, b, h, func)
        if intervals is None:
            error_msg()
            return
        # print(intervals)
        table_data = []
        for i in range(len(intervals)):
            table_data.append(sec_method(intervals[i][0], intervals[i][1], eps, n_max, i, func))

        # print('len:', len(table_data))
        # for l in table_data:
        #     print(l)
        self._set_data_in_table(table_data)
        self.plot(a, b, func)

    def _set_data_in_table(self, data):
        self.tableWidget.setRowCount(len(data))
        for i in range(len(data)):
            for j in range(len(data[i])):
                item = QTableWidgetItem(str(data[i][j]))
                item.setTextAlignment(4)
                self.tableWidget.setItem(i, j, item)
        self.tableWidget.show()

    def clearLayout(self, layout):
        if layout is not None:
            while layout.count():
                item = layout.takeAt(0)
                widget = item.widget()
                if widget is not None:
                    widget.deleteLater()
                else:
                    self.clearLayout(item.layout())

    def plot(self, a, b, func):
        self.clearLayout(self.plot_layout)
        fig = Figure(figsize=(5, 5))
        a_f = fig.add_subplot()
        X = np.linspace(a, b, int((b - a) * 1000))

        Y = [f(i, func) for i in X]
        Y = np.array(Y)
        Y_diff_1 = np.diff(Y)
        y_diff_2 = np.diff(Y_diff_1)

        mask = np.abs(Y) < 1e-3
        mask_1 = np.abs(Y_diff_1) < 1e-5
        mask_2 = np.abs(y_diff_2) < 1e-8

        a_f.plot(X, Y, color="#9467bd")

        a_f.scatter(X[:-1][mask_1], Y[:-1][mask_1], color='r', s=45, marker='o', label="Экстремум")
        a_f.scatter(X[:-2][mask_2], Y[:-2][mask_2], color='#08F7FE', s=45, marker='o', label="Точка перегиба")
        a_f.scatter(X[mask], Y[mask], color='#00ff41', s=40, marker='o', label="Нули")
        a_f.legend()
        a_f.grid(True)
        a_f.set_ylabel("y = " + str(self.func_le.text()))
        a_f.set_xlabel("x")

        canvas = FigureCanvasQTAgg(fig)
        canvas.draw()
        self.plot_layout.addWidget(canvas)

    def showButtonErrorCodes(self):
        dlg = QMessageBox(self)
        dlg.setText("Коды ошибок: <br>"
                    "0 - Все хорошо<br>"
                    "1 - Превышен лимит операций<br>"
                    "2 - Нарушен заданный диапазон")
        dlg.exec()

    def showInfo(self):
        dlg = QMessageBox(self)
        dlg.setText("Автор: Паншин Сергей ИУ7-23Б <br>"
                    "Программа для уточнения корней методом секущих")
        dlg.exec()
