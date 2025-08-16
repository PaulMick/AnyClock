import pygame

pygame.init()
screen = pygame.display.set_mode((400, 500))
pygame.display.set_caption("Create 3x5 Font")

grid = [
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0]
]

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            x, y = event.pos
            print(f"{x}, {y}")

    pygame.draw.line(screen, (255, 255, 255), (0, 0), (300, 0), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (0, 100), (300, 100), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (0, 200), (300, 200), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (0, 300), (400, 300), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (0, 400), (400, 400), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (0, 0), (0, 500), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (100, 0), (100, 500), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (200, 0), (200, 500), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (300, 0), (300, 500), width = 2)
    for x in range(3):
        for y in range(5):
            pygame.draw.rect(screen, (grid[x][y] * 255, grid[x][y] * 255, grid[x][y] * 255), (x * 100 + 2, y * 100 + 2, 98, 98))
    
    
    pygame.display.flip()

pygame.quit()