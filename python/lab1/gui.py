from PyQt6.QtCore import Qt
from PyQt6.QtGui import QAction, QKeySequence, QShortcut
from PyQt6.QtWidgets import (
    QGridLayout,
    QLineEdit,
    QMainWindow,
    QPushButton,
    QVBoxLayout,
    QWidget, QDialog, QDialogButtonBox, QLabel, QMessageBox,
)

ERROR_MSG = "ERROR"
WINDOW_SIZE = 300
DISPLAY_HEIGHT = 50
BUTTON_SIZE = 50

keyBoard = [
    ['3', '4', '+'],
    ['1', '2', '-'],
    ["0", ".", "="],
]


class MyQLineEdit(QLineEdit):
    def __init__(self, keybuttonMap):
        super().__init__()
        self.keybuttonMap = keybuttonMap

    def keyPressEvent(self, e):
        key_text = e.text()
        # print(e.key())
        # print(repr(key_text))
        if key_text in '01234+-.=':
            # super().keyPressEvent(e)
            for row, keys in enumerate(keyBoard):
                for col, key in enumerate(keys):
                    if key == key_text:
                        self.keybuttonMap[key].trigger()

        elif key_text == '\r':
            super().keyPressEvent(e)
        else:
            dlg = QMessageBox(self)
            dlg.setText("Можно вводить только числа от 0 до 4 и символы =, +, - или .")
            dlg.exec()


class CalcWindow(QMainWindow):

    def __init__(self):
        super().__init__()
        self.setWindowTitle("Calc")
        self.setFixedSize(WINDOW_SIZE, WINDOW_SIZE)
        self.generalLayout = QVBoxLayout()
        centralWidget = QWidget(self)
        centralWidget.setLayout(self.generalLayout)
        self.setCentralWidget(centralWidget)
        self._createKeyButtons()
        self._createDisplay()
        self._createButtons()

        menu = self.menuBar()

        menu = menu.addMenu("Меню")
        button_clear = QAction("&Заданные действия", self)
        button_clear.triggered.connect(self.showPossibleAction)

        menu.addAction(button_clear)

        button_clear = QAction("&Очистить", self)
        button_clear.triggered.connect(self.clearDisplay)

        menu.addAction(button_clear)

        button_clear = QAction("&Информация", self)
        button_clear.triggered.connect(self.showInfo)

        menu.addAction(button_clear)

    def _createDisplay(self):
        # self.display = QLineEdit()
        self.display = MyQLineEdit(self.keybuttonMap)
        self.display.setFixedHeight(DISPLAY_HEIGHT)
        self.display.setAlignment(Qt.AlignmentFlag.AlignRight)
        # self.display.setReadOnly(True)
        self.generalLayout.addWidget(self.display)

    def _createButtons(self):
        self.buttonMap = {}
        buttonsLayout = QGridLayout()

        for row, keys in enumerate(keyBoard):
            for col, key in enumerate(keys):
                self.buttonMap[key] = QPushButton(key)
                self.buttonMap[key].setFixedSize(BUTTON_SIZE, BUTTON_SIZE)
                buttonsLayout.addWidget(self.buttonMap[key], row, col)

        self.generalLayout.addLayout(buttonsLayout)

    def _createKeyButtons(self):
        self.keybuttonMap = {}

        for row, keys in enumerate(keyBoard):
            for col, key in enumerate(keys):
                # self.keybuttonMap[key] = QShortcut(QKeySequence(key), self)
                self.keybuttonMap[key] = QAction(key, self)

    def setDisplayText(self, text):
        self.display.setText(text)
        self.display.setFocus()

    def getDisplayText(self):
        return self.display.text()

    def clearDisplay(self):
        self.setDisplayText("")

    def showPossibleAction(self):
        dlg = QMessageBox(self)
        dlg.setText("Заданные действия: <br>Сложение <br>Вычитания")
        dlg.exec()

    def showInfo(self):
        dlg = QMessageBox(self)
        dlg.setText("Автор: Паншин Сергей ИУ7-23Б <br>"
                    "Программа представляет собой калькулятор в 5-ой системе счисления")
        dlg.exec()
