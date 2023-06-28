# Паншин Сергей ИУ7-13Б
import sys

from PIL import Image
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

    # for fix img image in finder
    # img = Image.open("cat1.bmp")
    # img.save("cat11" + '.bmp')
