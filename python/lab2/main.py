# Паншин Сергей ИУ7-23Б
# Вариант 5


import sys

from PyQt6.QtWidgets import QApplication

from gui import MainWindow


ERROR_MSG = "ERROR"


def main():
    app = QApplication([])
    window = MainWindow()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
