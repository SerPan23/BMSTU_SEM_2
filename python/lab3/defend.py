# Паншин Сергей ИУ7-23Б
# Перевести картинку в негатив

from PIL import Image

file_name = 'cat1.bmp'

img = Image.open('cat1.bmp')

for y in range(img.height):
    for x in range(img.height):
        r, g, b = img.getpixel((x, y))

        img.putpixel((x, y), (255-r, 255-g, 255-b))

img.save("neg_" + file_name)
