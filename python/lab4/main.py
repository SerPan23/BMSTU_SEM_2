# Паншин Сергей ИУ7-23Б
# На плоскости задано множество точек. Определить количество выпуклых четырехугольников,
# которые можно построить на этих точках.
# Дать графическое изображение результатов.


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
