# from math import *
import itertools
import math
from itertools import combinations
import random

from PyQt6 import uic, QtCore, QtGui
from PyQt6.QtCore import pyqtSignal
from PyQt6.QtGui import QPainter, QColor
from PyQt6.QtWidgets import QMainWindow, QTableWidgetItem, QLabel

coords = []
quads = []
colors = set()


def uniqueRandomColor():
    flag = True
    while flag:
        color = random.randrange(0, 2 ** 24)
        hex_color = hex(color)

        std_color = "#" + hex_color[2:]
        if std_color not in colors:
            colors.add(std_color)
            flag = False

    return std_color


# def crossProduct(A):
#     # Коэффициент направления X A[1]A[0]
#     X1 = (A[1][0] - A[0][0])
#
#     # Коэффициент направления Y A[1]A[0]
#     Y1 = (A[1][1] - A[0][1])
#
#     # Коэффициент направления X A[2]A[0]
#     X2 = (A[2][0] - A[0][0])
#
#     # Коэффициент направления Y A[2]A[0]
#     Y2 = (A[2][1] - A[0][1])
#
#     return (X1 * Y2 - Y1 * X2)
#
#
# def isConvex(points):
#     n = len(points)
#     prev = 0
#     curr = 0
#
#     for i in range(n):
#         temp = [points[i], points[(i + 1) % n],
#                 points[(i + 2) % n]]
#         curr = crossProduct(temp)
#
#         if curr != 0:
#             if curr * prev < 0:
#                 return False
#             else:
#                 prev = curr
#
#     return True


def point_above_line(p1, p2, p3):
    v1 = (p2[0] - p1[0], p2[1] - p1[1])  # Vector 1
    v2 = (p2[0] - p3[0], p2[1] - p3[1])  # Vector 2
    xp = v1[0] * v2[1] - v1[1] * v2[0]  # Cross product
    if xp > 0:
        return 1
    elif xp < 0:
        return -1
    else:
        return 0


def lines_intersect(p1, p2, p3, p4):
    x1 = p1[0]
    x2 = p2[0]
    x3 = p3[0]
    x4 = p4[0]

    y1 = p1[1]
    y2 = p2[1]
    y3 = p3[1]
    y4 = p4[1]

    first_condition = ((x2 - x1) * (y4 - y1) - (x4 - x1) * (y2 - y1)) * (
            (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)
    )
    second_condition = ((x4 - x3) * (y1 - y3) - (x1 - x3) * (y4 - y3)) * (
            (x4 - x3) * (y2 - y3) - (x2 - x3) * (y4 - y3)
    )
    if first_condition < 0 and second_condition < 0:
        return 1

    return 0


def vec_len(p1, p2):
    return ((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2) ** 0.5


def find_quadrilaterals(p1, p2, p3, p4):
    t1 = p1
    parr = [p2, p3, p4]

    for i, tmp1 in enumerate(parr):
        tmparr = []
        for tmp2 in parr:
            tmparr.append(point_above_line(t1, tmp1, tmp2))
        if len(set(tmparr)) == 3:
            t4 = tmp1
            parr.pop(i)
            break
    t2 = parr[0]
    t3 = parr[1]

    if lines_intersect(t1, t4, t2, t3):
        return [True, (t1, t2, t3, t4)]

    return [False, ()]


def convex_quadrilaterals(points):
    segments = combinations(points, 4)
    res = []
    for t in segments:
        tmp = find_quadrilaterals(*t)
        if tmp[0]:
            res.append((*tmp[1], uniqueRandomColor()))
    return res


class BtnLabel(QLabel):
    clicked = pyqtSignal()
    mModified = False
    counted = False

    def __init__(self, parent=None):
        super(BtnLabel, self).__init__(parent)
        self.x = 0
        self.y = 0

    def mouseReleaseEvent(self, e):
        super().mouseReleaseEvent(e)
        self.x = e.pos().x()
        self.y = e.pos().y()
        self.mModified = True
        self.update()
        self.clicked.emit()

    def paintEvent(self, e):
        if self.mModified:
            qp = QPainter()
            qp.begin(self)
            if self.counted:
                self.draw_quad(qp)
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
            for coord in coords:
                qp.drawPoint(coord[0], coord[1])
        except:
            return

    def draw_quad(self, qp):
        pen = QtGui.QPen()
        pen.setWidth(2)
        try:
            for coords in quads:
                # pen.setColor(QColor(100, 5, 195))
                pen.setColor(QColor(coords[4]))
                qp.setPen(pen)
                qp.drawLine(coords[0][0], coords[0][1], coords[1][0], coords[1][1])
                qp.drawLine(coords[0][0], coords[0][1], coords[2][0], coords[2][1])
                qp.drawLine(coords[3][0], coords[3][1], coords[1][0], coords[1][1])
                qp.drawLine(coords[3][0], coords[3][1], coords[2][0], coords[2][1])
        except:
            return


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi('MainWindow.ui', self)
        self.show()
        # self.mModified = False
        self.paint_lable = BtnLabel()
        # self.paint_lable.paintEvent = self.paintEvent
        self.paint_lable.setStyleSheet("background-color: grey;")

        self.paint_lt.addWidget(self.paint_lable)

        self.answer_le.setText("Количество: 0")

        self.add_coord_btn.clicked.connect(self.add_coord_form)
        self.paint_lable.clicked.connect(self.add_coord_mouse)

        self.count_btn.clicked.connect(self.start_count)
        self.clear_btn.clicked.connect(self.clear)

    def add_coord_mouse(self):
        try:
            x = int(self.paint_lable.x)
            y = int(self.paint_lable.y)
            self.add_coord((x, y))
        except:
            return None

    def add_coord_form(self):
        try:
            x = int(self.x_input.text())
            y = int(self.y_input.text())
            self.add_coord((x, y))
        except:
            return None

    def add_coord(self, coord):
        coords.append(coord)
        self.add_coord_in_table(coord)
        self.paint_lable.mModified = True
        self.paint_lable.update()

    def add_coord_in_table(self, coord):
        self.coords_table.setRowCount(len(coords))
        i = len(coords) - 1
        for j in range(len(coord)):
            item = QTableWidgetItem(str(coords[i][j]))
            item.setTextAlignment(4)
            self.coords_table.setItem(i, j, item)
        self.coords_table.show()

    def start_count(self):
        global coords
        global quads
        res = convex_quadrilaterals(coords)
        # print(res)
        quads = res
        self.paint_lable.counted = True
        self.paint_lable.mModified = True
        # self.paint_lable.paintEvent(QtGui.QPaintEvent)
        self.paint_lable.update()

        count = len(quads)

        self.answer_le.setText("Количество: " + str(count))
        print(count, len(set(quads)), len(coords))

    def clear(self):
        global coords
        global quads
        coords = []
        quads = []
        self.answer_le.setText("Количество: 0")
        self.coords_table.setRowCount(len(coords))
        self.paint_lable.update()
