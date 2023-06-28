import pygame
import math

SIZES = WIDTH, HEIGHT = 720, 600
screen = pygame.display.set_mode(SIZES)

clock = pygame.time.Clock()
FPS = 60

running = True

white = (255, 255, 255)

while running:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            break

    screen.fill(white)

    x = 200
    y = 200
    r = 100
    pygame.draw.arc(screen, (255, 0, 0), (x, y, 100, 100), 0, math.pi / 2, r)
    pygame.draw.arc(screen, (255, 0, 0), (x, y, 100, 100), math.pi / 2, math.pi / 2, r)
    pygame.draw.arc(screen, (255, 0, 0), (x, y, 100, 100), 0, math.pi / 2, r)
    pygame.draw.arc(screen, (255, 0, 0), (x, y, 100, 100), 0, math.pi / 2, r)

    clock.tick(FPS)
    pygame.display.flip()

pygame.quit()
