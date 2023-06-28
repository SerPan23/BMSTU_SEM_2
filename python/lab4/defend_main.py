# Паншин Сергей ИУ7-23Б
# Дана точка и мн-во окружностей
# Найти окр-ть наиболее близкую к точке


import sys

from PyQt6.QtWidgets import QApplication

from defend_gui import MainWindow

ERROR_MSG = "ERROR"


def main():
    app = QApplication([])
    window = MainWindow()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
