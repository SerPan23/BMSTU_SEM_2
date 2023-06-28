import pygame
import random

from ext import Player, Obstacle

HEIGHT = 640
WIDTH = 480
FPS = 60

pygame.init()
pygame.mixer.init()
screen = pygame.display.set_mode((HEIGHT, WIDTH))
pygame.display.set_caption("My Game")
clock = pygame.time.Clock()
font = pygame.font.Font(None, 36)

floor = pygame.image.load("sprites/grass.png")
floorSize = floor.get_size()

# Image
player_image = pygame.image.load("sprites/horse_run_cycle-modified.png")
scale = 2
frame_size = (60 * scale, 58 * scale)
player_image = pygame.transform.flip(player_image, True, False)
player_image = pygame.transform.rotozoom(player_image, 0, scale)

running = True
is_alive = True
score = 0
obstacle_speed = 3
speed_ratio = 1

baseline = 300
gravity = 0.4
sky_color = (187, 222, 251)
text_color = (13, 71, 161)

player = Player(player_image, frame_size, 5, 1, baseline, gravity)

obstacle_image = pygame.image.load("sprites/Rock Pile.png")
obstacle_image = pygame.transform.flip(obstacle_image, True, False)
obstacle_image = pygame.transform.rotozoom(obstacle_image, 0, 1 / 3.16)

obstacles = [
    Obstacle(WIDTH + 100, baseline, obstacle_image, obstacle_speed),
    Obstacle(WIDTH + 600, baseline, obstacle_image, obstacle_speed),
    Obstacle(WIDTH + 1000, baseline, obstacle_image, obstacle_speed),
]

cloud_image = pygame.image.load("sprites/cloud.png")
cloud_image = pygame.transform.rotozoom(cloud_image, 0, 2)

clouds = [
    (cloud_image, (WIDTH + 30, 90)),
    (cloud_image, (50, 150)),
    (cloud_image, (WIDTH // 2 + 30, 120)),
]

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.KEYDOWN and is_alive:
            if event.key == pygame.K_SPACE and not player.is_jumping:
                player.jump()

        if event.type == pygame.KEYDOWN and not is_alive:
            if event.key == pygame.K_SPACE:
                obstacle_speed = 3
                speed_ratio = 1
                obstacles = [
                    Obstacle(WIDTH + 100, baseline, obstacle_image, obstacle_speed),
                    Obstacle(WIDTH + 600, baseline, obstacle_image, obstacle_speed),
                    Obstacle(WIDTH + 1000, baseline, obstacle_image, obstacle_speed),
                ]
                player.init_settings()
                score = 0
                is_alive = True

    screen.fill(sky_color)

    for cloud in clouds:
        screen.blit(cloud[0], cloud[1])

    for i in range((HEIGHT - baseline) // floorSize[1]):
        for j in range(WIDTH // floorSize[0] + 5):
            screen.blit(floor, (floorSize[0] * j, baseline + floorSize[1] * 2 + floorSize[1] * i))

    for obstacle in obstacles:
        if pygame.Rect.colliderect(player.rect, obstacle.rect) and obstacle.rect.x > 40:
            is_alive = False

        if is_alive:
            obstacle.speed *= speed_ratio
            obstacle.update()
            if obstacle.rect.x < 40 and not obstacle.is_counted:
                score += 1
                obstacle.counted()
                if score % 3 == 0:
                    speed_ratio += 0.0001
        screen.blit(obstacle.image, obstacle.rect)

    if is_alive:
        player.update()

    screen.blit(player.sprite.current_image, player.rect)

    score_text = font.render(f'Score: {score}', True, text_color, sky_color)

    screen.blit(score_text, (WIDTH + 10, 30))

    if not is_alive:
        result_text = [
            'YOU LOOSE',
            f'Your score: {score}',
            'Press SPACE to restart game'
        ]
        for i in range(len(result_text)):
            text = font.render(result_text[i],
                               True, text_color, sky_color)

            screen.blit(text, (WIDTH // 2 - 80, HEIGHT // 2 - 100 + i * 40))

    pygame.display.flip()

    clock.tick(FPS)

pygame.quit()
