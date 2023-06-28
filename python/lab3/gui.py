from PyQt6 import uic, QtWidgets
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QPixmap, QImage
from PyQt6.QtWidgets import QMainWindow, QMessageBox
from PIL.ImageQt import ImageQt

from PIL import Image

DATA_SIZE_LEN = 128


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi('MainWindow.ui', self)
        self.show()
        self.browse_file.clicked.connect(self._browse_file_code)
        self.code_btn.clicked.connect(self.start_code)
        self.save_file_btn.clicked.connect(self.save_file)
        self.browse_file_decode.clicked.connect(self._browse_file_decode)
        self.decode_btn.clicked.connect(self.start_decode)


    def error_msg(self, msg):
        dlg = QMessageBox()
        dlg.setText(msg)
        dlg.exec()

    def set_avaible_pixels(self, avaible_chars, data_len):
        self.enable_chars.setText('Доступно символов = ' + str((avaible_chars * 8 - data_len) // 8))

    def _browse_file_code(self):
        try:
            file = QtWidgets.QFileDialog.getOpenFileName(self, 'Выберите картинку', filter='Images (*.bmp)')
            Image.open(file[0])
        except:
            self.error_msg("Файл не корректен!")
            return

        if file:
            self.file_name.setText(file[0])

            img = QPixmap(file[0])

            self.draw_img(img, self.img_place1)
            avaible_chars = (img.width() * img.height() * 3 - DATA_SIZE_LEN) // 8
            self.set_avaible_pixels(avaible_chars, 0)

        self.file_code = file

    def draw_img(self, pixmap, img_place):
        img_place.setScaledContents(True)
        img_place.setPixmap(pixmap)

    def get_pillow_img(self, file):
        img = Image.open(file[0])

        return img

    def get_pixmap_from_pillow(self, img):
        qim = ImageQt(img)
        pix = QPixmap(QImage(qim))
        return pix

    def bin_num(self, num):
        return bin(num)[2:].zfill(8)

    def bin_text(self, text):
        result = ''
        # print(text)
        for i in text:
            # print(chr(i))
            # result += self.bin_num(ord(i))
            result += self.bin_num(i)

        return result

    def code(self, img, text):
        bin_text = self.bin_text(text)
        len_bin_text = len(bin_text)
        if ((img.width * img.height * 3 - DATA_SIZE_LEN - len_bin_text) // 8) < 0:
            return None
        bin_len_bin_text = bin(len_bin_text)[2:].zfill(DATA_SIZE_LEN)
        # print(len_bin_text, bin_len_bin_text)
        i = 0
        k = 0
        flag = False
        flag_len = True
        for y in range(img.height):
            for x in range(img.width):
                c = list(img.getpixel((x, y)))
                for j in range(len(c)):
                    if flag_len:
                        if k < DATA_SIZE_LEN:
                            c[j] = int(self.bin_num(c[j])[:-1] + bin_len_bin_text[k], 2)
                            k += 1
                        else:
                            flag_len = False
                    else:
                        if i < len_bin_text:
                            c[j] = int(self.bin_num(c[j])[:-1] + bin_text[i], 2)
                            i += 1
                        else:
                            flag = True
                            break
                img.putpixel((x, y), tuple(c))
                if flag:
                    break
            if flag:
                break
        return img

    def start_code(self):
        try:
            self.coded_img = self.code(self.get_pillow_img(self.file_code), self.text.toPlainText().encode('cp1251'))
        except:
            self.error_msg("Что-то пошло не так при открытие/кодирование файла")
            return
        if self.coded_img is None:
            self.error_msg("Количество элементов превышает допустимое")
            return
        pix = self.get_pixmap_from_pillow(self.coded_img)
        self.draw_img(pix, self.img_place2)

    def save_file(self):
        try:
            name = self.file_name_save.text().split('.')[0]
            self.coded_img.save(name + '.bmp')
            self.error_msg("Файл сохранен!")
        except:
            self.error_msg("Файл не может быть сохранен!")

    def _browse_file_decode(self):
        try:
            file = QtWidgets.QFileDialog.getOpenFileName(self, 'Выберите картинку', filter='Images (*.bmp)')
            Image.open(file[0])
        except:
            self.error_msg("Файл не корректен!")
            return

        if file:
            self.file_name_decode.setText(file[0])

        self.file_decode = file

    def decode_text(self, img):
        bin_text = ''
        i = 0
        k = 0
        bin_size = ''
        size = 0
        flag_size = True
        flag = False
        for y in range(img.height):
            for x in range(img.width):
                c = list(img.getpixel((x, y)))
                # print(c)
                for j in range(len(c)):
                    if flag_size:
                        if k < DATA_SIZE_LEN:
                            bin_size += self.bin_num(c[j])[-1]
                            k += 1
                        else:
                            size = int(bin_size, 2)
                            # print(size, bin_size)
                            flag_size = False
                    else:
                        if i < size:
                            bin_text += self.bin_num(c[j])[-1]
                            i += 1
                        else:
                            flag = True
                            break

            if flag:
                break
        # print(bin_text[80])
        text = ''
        for i in range(0, len(bin_text), 8):
            # text += chr(int(bin_text[i:i + 8], 2))
            text += int(bin_text[i:i + 8], 2).to_bytes(1, 'big').decode('cp1251')

        return text

    def start_decode(self):
        try:
            detext = self.decode_text(self.get_pillow_img(self.file_decode))
        except:
            self.error_msg("Что-то пошло не так при открытие/кодирование файла")
            return
        self.text_out.setText(detext)
