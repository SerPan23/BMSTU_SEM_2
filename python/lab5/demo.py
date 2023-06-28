import math
import pygame

# colors
red = (255, 0, 0)
green = (0, 122, 0)
black = (0, 0, 0)
white = (255, 255, 255)

size = (500, 500)
screen = pygame.display.set_mode(size)

a = b = 200
i = 0

clock = pygame.time.Clock()
FPS = 60

running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            break

    screen.fill(white)
    pygame.draw.circle(screen, red, (int(a), int(b)), 20, draw_top_right=True)

    if i <= 360:  # здесь мы ставим ограничения, что-бы питон не выдал нам ошибку.
        angle = i * (3.14 / 180)  # перевод из градусов в радианы
        a = 100 * math.cos(angle) + 300
        b = 100 * math.sin(angle) + 300
        i += 3  # здесь мы увеличиваем угол перемещения.

    else:
        i = 0

    pygame.display.flip()
    clock.tick(FPS)

pygame.quit()
