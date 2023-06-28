from functools import partial

from PyQt6.QtGui import QKeySequence, QShortcut
from PyQt6.QtWidgets import QMessageBox

ERROR_MSG = "ERROR"


class CalcController:

    def __init__(self, model, view):
        self._evaluate = model
        self._view = view
        self._connectSignalsAndSlots()

    def _calculateResult(self):
        result = self._evaluate(expression=self._view.getDisplayText())
        self._view.setDisplayText(result)

    def _buildExpression(self, subExpression):
        if self._view.getDisplayText() == ERROR_MSG:
            self._view.clearDisplay()
        expression = self._view.getDisplayText() + subExpression
        self._view.setDisplayText(expression)

    def _connectSignalsAndSlots(self):
        for keySymbol, button in self._view.buttonMap.items():
            if keySymbol not in {"="}:
                button.clicked.connect(
                    partial(self._buildExpression, keySymbol)
                )

        for keySymbol, button in self._view.keybuttonMap.items():
            if keySymbol not in {"="}:
                button.triggered.connect(
                    partial(self._buildExpression, keySymbol)
                )

        self._view.buttonMap["="].clicked.connect(self._calculateResult)
        self._view.keybuttonMap["="].triggered.connect(self._calculateResult)
        self._view.display.returnPressed.connect(self._calculateResult)


# def toBASEint(num, base):
#     alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#     n = abs(num)
#     b = alpha[n % base]
#     while n >= base:
#         n = n // base
#         b += alpha[n % base]
#     return ('' if num >= 0 else '-') + b[::-1]
#
#
# def toBaseFrac(frac, base, n=16):
#     alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#     b = ''
#     while n:
#         frac *= base
#         frac = round(frac, n)
#         b += str(alpha[int(frac)])
#         frac -= int(frac)
#         n -= 1
#     return b


# def convertNumsTo10Base(expression):
#     converted = []
#     for i in range(len(expression)):
#         Number = expression[i]
#         if Number not in '+-':
#             alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#             if '.' in Number:
#                 num, frac = map(str, Number.split('.'))
#                 num = int(num, 5)
#                 a = toBASEint(num, 10)
#                 b = 0
#                 k = 5
#                 for i in frac:
#                     b += alpha.index(i) / k
#                     k *= 5
#                 b = str(toBaseFrac(b, 10)).rstrip('0')
#                 Number = str(a + '.' + b)
#             else:
#                 Number = toBASEint(int(Number, 5), 10)
#         converted.append(Number)
#         # print(expression[i])
#     return converted
#
#
# def convertNumsTo5Base(expression):
#     converted = []
#     for i in range(len(expression)):
#         Number = expression[i]
#         if Number not in '+-':
#             alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#             if '.' in Number:
#                 num, frac = map(str, Number.split('.'))
#                 num = int(num, 10)
#                 a = toBASEint(num, 5)
#                 b = 0
#                 k = 10
#                 for i in frac:
#                     b += alpha.index(i) / k
#                     k *= 10
#                 b = str(toBaseFrac(b, 5)).rstrip('0')
#                 Number = str(a + '.' + b)
#             else:
#                 Number = toBASEint(int(Number, 10), 5)
#         converted.append(Number)
#     return converted


# def evaluateExpression(expression):
#     try:
#         spe = splitExpression(expression)
#         expression_in_10 = convertNumsTo10Base(spe)
#         expression_in_10 = ''.join(expression_in_10)
#         result_in_10 = str(eval(expression_in_10, {}, {}))
#         # print(result_in_10)
#         result = convertNumsTo5Base([result_in_10])[0]
#     except Exception:
#         result = ERROR_MSG
#     return result


def splitExpression(expression):
    expression_array_view = []
    el = ''
    for i in expression:
        if i in '+-':
            expression_array_view.append(el)
            expression_array_view.append(i)
            el = ''
        else:
            el += i
    expression_array_view.append(el)
    return expression_array_view


def split_num(num):
    if '.' in num:
        num = num.split('.')
        num_int, num_float = num[0], num[1]
    else:
        num_int, num_float = num, ''

    return num_int, num_float


def correct_len_nums(num1, num2):
    num1_int, num1_float = split_num(num1)
    num2_int, num2_float = split_num(num2)
    max_len_int = max(len(num1_int), len(num2_int))
    num1_int = num1_int.zfill(max_len_int)
    num2_int = num2_int.zfill(max_len_int)
    max_len_float = max(len(num1_float), len(num2_float))
    temp = '{:<0' + str(max_len_float) + '}'
    num1_float = temp.format(num1_float)
    num2_float = temp.format(num2_float)

    num1 = num1_int + '.' + num1_float
    num2 = num2_int + '.' + num2_float

    return num1, num2


def sum_digits_in_5_base(a, b, tmp):
    summ = a + b + tmp
    tmp = 0
    if summ > 4:
        summ -= 5
        tmp = 1
    return summ, tmp


def sum_two_numbers(num1, num2):
    num1, num2 = correct_len_nums(num1, num2)
    num1, num2 = num1[::-1], num2[::-1]

    answer = ""
    tmp = 0

    for i in range(len(num1)):
        if num1[i] == '.':
            continue
        digit1 = int(num1[i])
        digit2 = int(num2[i])

        result, tmp = sum_digits_in_5_base(digit1, digit2, tmp)

        answer += str(result)

    if tmp == 1:
        answer += "1"

    return answer[::-1]


def minus_digits_in_5_base(a, b, tmp):
    diff = a - b - tmp
    tmp = 0
    if diff < 0:
        diff += 5
        tmp = 1
    return diff, tmp


def minus_two_numbers(num1, num2):

    if float(num1) < float(num2):
        num1, num2 = num2, num1

    num1, num2 = correct_len_nums(num1, num2)
    num1, num2 = num1[::-1], num2[::-1]

    answer = ""
    tmp = 0

    for i in range(len(num1)):
        if num1[i] == '.':
            continue
        digit1 = int(num1[i])
        digit2 = int(num2[i])

        result, tmp = minus_digits_in_5_base(digit1, digit2, tmp)
        # print(digit1, digit2, result, tmp)

        answer += str(result)

    return answer[::-1]


def evaluateExpression(expression):
    splited_exp = splitExpression(expression)
    # print(splited_exp)
    try:
        result = splited_exp[0]
        for i in range(2, len(splited_exp), 2):
            if splited_exp[i-1] == "+":
                result = sum_two_numbers(result, splited_exp[i])
            else:
                result = minus_two_numbers(result, splited_exp[i])
    except:
        result = ERROR_MSG
    return result


# print(evaluateExpression("213+43-120"))
# print(sum_digits_in_5_base(4, 4, 1))
# print(sum_two_numbers("213", "43"))
#
# print(minus_digits_in_5_base(4, 3, 0))
# print(minus_two_numbers("213", "43"))

