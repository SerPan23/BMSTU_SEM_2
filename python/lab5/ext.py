import random
import pygame


class AnimateSprite:
    def __init__(self, image, frame_size, horiz_cell, vert_cell, animation_speed):
        self.animation_speed = animation_speed
        self.image = image
        self.imageSize = self.image.get_size()
        self.horiz_cell = horiz_cell
        self.vert_cell = vert_cell
        # self.cell_width = self.imageSize[0] / horiz_cell
        # self.cell_height = self.imageSize[1] / vert_cell
        self.cell_width = frame_size[0]
        self.cell_height = frame_size[1]
        self.cell_list = self.get_sprite_list()
        self.cell_position = 0
        self.current_image = self.cell_list[0]

    def update(self):
        if self.cell_position // self.animation_speed < len(self.cell_list) - 1:
            self.cell_position += 1
        else:
            self.cell_position = 0

        self.current_image = self.cell_list[self.cell_position // self.animation_speed]

    def get_sprite_list(self):
        cell_list = []

        for y in range(0, self.vert_cell):
            for x in range(0, self.horiz_cell):
                surface = pygame.Surface((self.cell_width, self.cell_height), pygame.SRCALPHA)
                surface.blit(self.image.convert_alpha(), (0, 0),
                             (x * self.imageSize[0] // self.horiz_cell,
                              y * self.imageSize[1] // self.vert_cell,
                              self.cell_width, self.cell_height))
                cell_list.append(surface)

        return cell_list


class Player:
    def __init__(self, image, frame_size, horiz_cell, vert_cell, baseline, gravity):
        self.is_jumping = None
        self.max_y_change = None
        self.y_change = None
        self.sprite = AnimateSprite(image, frame_size, horiz_cell, vert_cell, 5)

        self.rect = self.sprite.current_image.get_rect()

        self.player_baseline = baseline + 25
        self.gravity = gravity

        self.init_settings()

    def init_settings(self):
        self.rect.x = 30
        self.rect.y = self.player_baseline
        self.y_change = 0
        self.max_y_change = 15
        self.is_jumping = False

    def update(self):
        self.sprite.update()

        if abs(self.y_change) >= 0 and self.rect.y <= self.player_baseline:
            self.rect.y -= self.y_change
            self.y_change -= self.gravity
        if self.rect.y > self.player_baseline:
            self.rect.y = self.player_baseline
        if self.rect.y == self.player_baseline and self.y_change < 0:
            self.y_change = 0
            self.is_jumping = False

    def jump(self):
        self.y_change = self.max_y_change
        self.is_jumping = True


class Obstacle:
    def __init__(self, x, baseline, image, speed):
        # self.surf = pygame.Surface((50, 50))
        # self.surf.fill((255, 82, 82))
        self.image = image
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = baseline + 90
        self.is_counted = False
        self.speed = speed

    def update(self):
        self.rect.x -= self.speed
        if self.rect.x < -50:
            self.rect.x = random.randint(1500, 1700)
            self.is_counted = False

    def counted(self):
        self.is_counted = True
