# Паншин Сергей ИУ7-23Б
# Вариант 14


import sys

from PyQt6.QtWidgets import QApplication

from gui import CalcWindow
from logic import CalcController, evaluateExpression

ERROR_MSG = "ERROR"


def main():
    app = QApplication([])
    window = CalcWindow()
    window.show()
    CalcController(model=evaluateExpression, view=window)
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
