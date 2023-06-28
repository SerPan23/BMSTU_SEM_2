from PyQt6 import uic, QtCore, QtGui
from PyQt6.QtCore import pyqtSignal
from PyQt6.QtGui import QPainter, QColor
from PyQt6.QtWidgets import QMainWindow, QTableWidgetItem, QLabel

import math

circles = []
need_circle = ()
dot = ()


def minimal_circle(circles):
    min_l = math.sqrt((circles[0][0] - dot[0])**2 + (circles[0][1] - dot[1])**2)
    need_circle = circles[0]
    for circle in circles:
        length = math.sqrt((circle[0] - dot[0])**2 + (circle[1] - dot[1])**2)
        if length < min_l:
            min_l = length
            need_circle = circle
    return need_circle


class BtnLabel(QLabel):
    clicked = pyqtSignal()
    mModified = False
    counted = False

    def __init__(self, parent=None):
        super(BtnLabel, self).__init__(parent)
        self.x = 0
        self.y = 0

    def paintEvent(self, e):
        if self.mModified:
            qp = QPainter()
            qp.begin(self)
            # if self.counted:
            self.draw_circles(qp)
            self.draw_dot(qp)
            qp.end()
            self.mModified = False
            self.counted = False

    def draw_dot(self, qp):
        pen = QtGui.QPen()
        pen.setWidth(5)
        pen.setColor(QColor(255, 255, 255))
        qp.setPen(pen)
        try:
            qp.drawPoint(dot[0], dot[1])
        except:
            return

    def draw_circles(self, qp):
        pen = QtGui.QPen()
        pen.setWidth(2)
        try:
            for circle in circles:
                pen.setColor(QColor(200, 25, 195))
                # pen.setColor(QColor(circle[4]))
                qp.setPen(pen)
                x = circle[0] - (circle[2] // 2)
                y = circle[1] - (circle[2] // 2)
                qp.drawEllipse(x, y, circle[2], circle[2])
            circle = need_circle

            pen.setColor(QColor(100, 5, 195))
            # pen.setColor(QColor(circle[4]))
            qp.setPen(pen)
            x = circle[0] - (circle[2] // 2)
            y = circle[1] - (circle[2] // 2)
            qp.drawEllipse(x, y, circle[2], circle[2])
        except:
            return


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi('DefendWindow.ui', self)
        self.show()
        # self.mModified = False
        self.paint_lable = BtnLabel()
        # self.paint_lable.paintEvent = self.paintEvent
        self.paint_lable.setStyleSheet("background-color: grey;")

        self.paint_lt.addWidget(self.paint_lable)


        self.add_circle_btn.clicked.connect(self.add_coord_form)
        self.add_dot_btn.clicked.connect(self.add_dot)

        self.count_btn.clicked.connect(self.start_count)
        self.clear_btn.clicked.connect(self.clear)

    def add_coord_form(self):
        try:
            x = int(self.x_input.text())
            y = int(self.y_input.text())
            r = int(self.r_input.text())
            self.add_coord((x, y, r))
            self.x_input.setText("")
            self.y_input.setText("")
            self.r_input.setText("")
        except:
            return None

    def add_dot(self):
        try:
            x = int(self.dot_x_le.text())
            y = int(self.dot_y_le.text())
            global dot
            dot = (x, y)
            self.paint_lable.mModified = True
            self.paint_lable.update()
        except:
            return None

    def add_coord(self, circle):
        circles.append((*circle, False))
        self.add_circle_in_table(circle)
        self.paint_lable.mModified = True
        self.paint_lable.update()

    def add_circle_in_table(self, circle):
        self.circles_table.setRowCount(len(circles))
        i = len(circles) - 1
        for j in range(len(circle)):
            item = QTableWidgetItem(str(circles[i][j]))
            item.setTextAlignment(4)
            self.circles_table.setItem(i, j, item)
        self.circles_table.show()

    def start_count(self):
        global circles
        global need_circle
        need_circle = minimal_circle(circles)
        # print(res)
        self.paint_lable.counted = True
        self.paint_lable.mModified = True
        # self.paint_lable.paintEvent(QtGui.QPaintEvent)
        self.paint_lable.update()

    def clear(self):
        global circles
        global need_circle
        global dot
        circles = []
        dot = ()
        need_circle = ()
        self.circles_table.setRowCount(len(circles))
        self.dot_x_le.setText("")
        self.dot_y_le.setText("")
        self.paint_lable.update()
