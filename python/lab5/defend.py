import pygame
from math import sin, pi, radians, atan, cos, degrees

black = (0, 0, 0)
white = (255, 255, 255)
HEIGHT = 640
WIDTH = 480
FPS = 60


class Ship:
    def __init__(self, amplitude, wave):
        self.wave = wave
        self.amplitude = amplitude
        self.x = WIDTH // 2
        self.y = HEIGHT // 2
        self.angle = 0
        self.surface = pygame.Surface((50, 50), pygame.SRCALPHA)
        pygame.draw.arc(self.surface, black, (0, 25, 50, 25), pi, 2 * pi)
        pygame.draw.line(self.surface, black, (0, 37), (50, 37))
        pygame.draw.line(self.surface, black, (0, 37), (50, 37))
        pygame.draw.line(self.surface, black, (25, 0), (25, 37))
        pygame.draw.line(self.surface, black, (25, 0), (40, 18))
        pygame.draw.line(self.surface, black, (25, 18), (40, 18))

    def update(self):
        # self.x += 1
        self.y = HEIGHT // 2 + sin(self.wave.offset + radians(self.x) / self.wave.width) * self.amplitude - 50

        self.angle = atan(-cos((self.wave.offset + radians(self.x) / self.wave.width)))



class Wave:
    def __init__(self, screen, amplitude, w):
        self.surface = screen
        self.offset = 0
        self.width = w
        self.y = HEIGHT // 2
        self.x = 0
        self.amplitude = amplitude

    def update(self):
        for x in range(WIDTH + 200):
            self.x = x
            pygame.draw.line(self.surface, black,
                             (x, self.y + sin(self.offset + radians(x) / self.width) * self.amplitude),
                             (x + 1, self.y + sin(self.offset + radians(x) / self.width) * self.amplitude + 1))

        self.offset += 0.05


pygame.init()
screen = pygame.display.set_mode((HEIGHT, WIDTH))
pygame.display.set_caption("My Game")
clock = pygame.time.Clock()

running = True

amplitude = 75

wave = Wave(screen, amplitude, 3)
ship = Ship(amplitude, wave)

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill(white)

    wave.update()
    ship.update()

    new_ship = pygame.transform.rotate(ship.surface, degrees(ship.angle))

    screen.blit(wave.surface, (0, 0))

    screen.blit(new_ship, (ship.x - 10, ship.y - 10))

    pygame.display.flip()

    clock.tick(FPS)

pygame.quit()
