import sys
from math import *

from PyQt6 import uic
from PyQt6.QtWidgets import QMainWindow, QApplication
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg
from matplotlib.figure import Figure
import numpy as np

N_MAX = 10000
eps = 0.0001


def f(x, func):
    return eval(func)


def chord_method(func, start, end):
    a = start
    b = end
    i = 0
    while abs(b - a) > eps and i < N_MAX:
        # print(a, b, f(a, func), f(b, func))
        a = a - (b - a) * f(a, func) / (f(b, func) - f(a, func))
        b = b - (a - b) * f(b, func) / (f(a, func) - f(b, func))
        i += 1

    return b


class MyWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("DefendWindow.ui", self)
        self.show()
        self.start_btn.clicked.connect(self.start_count)

    def start_count(self):
        func = self.f_input.text()
        start = int(self.start_input.text())
        end = int(self.end_input.text())

        try:
            x = chord_method(func, start, end)
            if not(start <= x <= end):
                raise Exception
            x = f"{x:.6g}"
        except Exception:
            x = "Error"
        # print(x)
        self.result_output.setText(x)

        self.plot(start, end, func)

    def plot(self, start, end, func):
        self.cleanPlot(self.plot_layout)
        fig = Figure(figsize=(5, 5))
        af = fig.add_subplot()
        X = np.linspace(start, end, int(end - start) * 1000)
        Y = [f(i, func) for i in X]

        Y = np.array(Y)

        af.plot(X, Y)

        canvas = FigureCanvasQTAgg(fig)

        canvas.draw()
        self.plot_layout.addWidget(canvas)

    def cleanPlot(self, layout):
        if layout is not None:
            while layout.count():
                item = layout.takeAt(0)
                widget = item.widget()
                if widget is not None:
                    widget.deleteLater()
                else:
                    self.cleanPlot(item.layout())


def main():
    app = QApplication([])
    window = MyWindow()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
