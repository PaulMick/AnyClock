import numpy as np
import cv2

animation = input("Animation? (y/n): ")

if animation == "y":
    animation_name = input("Animation folder name: ")
    fps = float(input("Frames per second: "))
else:
    image_name = input("Image name (include extension): ")
    cv_im = cv2.LoadImage(image_name)
    np_im = np.asarray(cv_im)