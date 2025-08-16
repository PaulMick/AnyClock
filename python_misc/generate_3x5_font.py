import pygame

pygame.init()
screen = pygame.display.set_mode((600, 500))
pygame.display.set_caption("Create 3x5 Font")
button_font = pygame.font.SysFont("Arial", 20)
next_text = button_font.render("Next", True, (255, 255, 255))
back_text = button_font.render("Back", True, (255, 255, 255))

grid = [
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0]
]

grids = []

font_name = "5x5_flex"

def write_font(grids: list[list[list[int]]], fname: str) -> None:
    with open(f"python_misc/{font_name}.font", "wb") as f:
        for a in range(len(grids)):
            n = 0x00000000
            for bit in range(25):
                i = int(bit / 5)
                j = bit - i * 5
                n |= grids[a][i][j] << bit
            if n <= 0x7fff:
                pass
            elif n > 0x7fff and n <= 0xfffff:
                n |= 1 << 25
            else:
                n |= 1 << 26
            b = n.to_bytes(4, "big")
            print(f"{a}: {hex(n)}")
            f.write(b)

running = True
while running:
    if len(grids) >= 1:
        write_font(grids, "3x5.font")
        exit(0)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            click_x, click_y = event.pos
            i, j = int(click_x  / 100), int(click_y / 100)
            if i <= 4:
                if grid[i][j] == 0:
                    grid[i][j] = 1
                else:
                    grid[i][j] = 0
            elif i == 5:
                if j == 3:
                    grids.append(grid)
                    grid = [
                        [0, 0, 0, 0, 0],
                        [0, 0, 0, 0, 0],
                        [0, 0, 0, 0, 0],
                        [0, 0, 0, 0, 0],
                        [0, 0, 0, 0, 0]
                    ]
                elif j == 4:
                    if len(grids) > 0:
                        grid = grids.pop()

    pygame.draw.line(screen, (255, 255, 255), (0, 0), (500, 0), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (0, 100), (500, 100), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (0, 200), (500, 200), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (0, 300), (600, 300), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (0, 400), (600, 400), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (0, 0), (0, 500), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (100, 0), (100, 500), width = 2)
    pygame.draw.line(screen, (255, 255, 255), (200, 0), (200, 500), width = 2)
    pygame.draw.line(screen, (100, 255, 100), (300, 0), (300, 500), width = 2)
    pygame.draw.line(screen, (255, 255, 100), (400, 0), (400, 500), width = 2)
    pygame.draw.line(screen, (255, 100, 100), (500, 0), (500, 500), width = 2)
    for x in range(5):
        for y in range(5):
            pygame.draw.rect(screen, (grid[x][y] * 255, grid[x][y] * 255, grid[x][y] * 255), (x * 100 + 2, y * 100 + 2, 98, 98))
    pygame.draw.rect(screen, (100, 0, 0), (502, 402, 98, 98))
    pygame.draw.rect(screen, (0, 100, 0), (502, 302, 98, 98))
    pygame.draw.rect(screen, (0, 0, 0), (502, 2, 98, 98))
    counter_text = button_font.render(f"{len(grids)}", True, (255, 255, 255))
    screen.blit(counter_text, (533, 43))
    screen.blit(next_text, (533, 343))
    screen.blit(back_text, (533, 443))
    
    
    pygame.display.flip()

pygame.quit()

