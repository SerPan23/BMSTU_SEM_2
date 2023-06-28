# Паншин Сергей ИУ7-23Б
# Перевод в двоичную из дестичной целого положительного
import sys

from PyQt6 import uic
from PyQt6.QtWidgets import QMainWindow, QApplication


def convert_from_int_to_bin(num):
    result = ""

    while num:
        result += str(num % 2)
        num //= 2

    return result[::-1]


class MyWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi('MainWindow.ui', self)
        self.show()

        self.convert.clicked.connect(self.make_convert)

    def make_convert(self):
        number = int(self.input.toPlainText())

        if number != 0:
            converted = convert_from_int_to_bin(number)
        else:
            converted = "0"

        self.result.setText(converted)


def main():
    app = QApplication([])
    window = MyWindow()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
