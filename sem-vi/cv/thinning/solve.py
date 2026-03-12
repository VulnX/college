# Algorithm taken from: https://rosettacode.org/wiki/Zhang-Suen_thinning_algorithm

import numpy as np
import subprocess
import cv2

FOREGROUND = 1
BACKGROUND = 0

subprocess.run(['rm', '-r', 'frames'])
subprocess.run(['mkdir', 'frames'])

img = cv2.imread('input.png', cv2.IMREAD_GRAYSCALE)
_, img = cv2.threshold(img, 127, 1, cv2.THRESH_BINARY_INV)

h, w = img.shape

def step1():
    marked = []
    for i in range(1, h - 1):
        for j in range(1, w - 1):
            pixel = img[i][j]
            # Step-1: Pixel should be foreground
            if pixel != FOREGROUND:
                continue

            p = [
                img[i - 1][j + 0],
                img[i - 1][j + 1],
                img[i + 0][j + 1],
                img[i + 1][j + 1],
                img[i + 1][j],
                img[i + 1][j - 1],
                img[i + 0][j - 1],
                img[i - 1][j - 1],
            ]
            # Step-2: B(P1) should be in range
            b = sum(p)
            if b < 2 or b > 6:
                continue

            a = 0
            for k in range(len(p)):
                if p[k] == 0 and p[(k + 1) % len(p)] == 1:
                    a += 1
            # Step-3: A(P1) should be 1
            if a != 1:
                continue

            # Step-4: At least one of P2 and P4 and P6 should be white
            if p[2 - 2] * p[4 - 2] * p[6 - 2] != 0:
                continue

            # Step-5: At least one of P4 and P6 and P8 should be white
            if p[4 - 2] * p[6 - 2] * p[8 - 2] != 0:
                continue

            marked.append((i, j))
    return marked

def step2():
    marked = []
    for i in range(1, h - 1):
        for j in range(1, w - 1):
            pixel = img[i][j]
            # Step-1: Pixel should be foreground
            if pixel != FOREGROUND:
                continue

            p = [
                img[i - 1][j + 0],
                img[i - 1][j + 1],
                img[i + 0][j + 1],
                img[i + 1][j + 1],
                img[i + 1][j],
                img[i + 1][j - 1],
                img[i + 0][j - 1],
                img[i - 1][j - 1],
            ]
            # Step-2: B(P1) should be in range
            b = sum(p)
            if b < 2 or b > 6:
                continue

            a = 0
            for k in range(len(p)):
                if p[k] == 0 and p[(k + 1) % len(p)] == 1:
                    a += 1
            # Step-3: A(P1) should be 1
            if a != 1:
                continue

            # Step-4: At least one of P2 and P4 and P8 should be white
            if p[2 - 2] * p[4 - 2] * p[8 - 2] != 0:
                continue

            # Step-5: At least one of P2 and P6 and P8 should be white
            if p[2 - 2] * p[6 - 2] * p[8 - 2] != 0:
                continue

            marked.append((i, j))
    return marked

frame = 0
while True:
    step1_marked = step1()
    for (i, j) in step1_marked:
        img[i][j] = 0

    step2_marked = step2()
    for (i, j) in step2_marked:
        img[i][j] = 0

    display = (img * 255).astype(np.uint8)
    cv2.imwrite(f'frames/output_{frame}.png', display)
    print(f'saved {frame = }')
    frame += 1
    if len(step1_marked) + len(step2_marked) == 0:
        break

subprocess.run(['ffmpeg', '-framerate', '2', '-i', 'frames/output_%d.png', '-c:v', 'mpeg4', 'thinning.mp4'])
