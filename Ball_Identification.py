import cv2
import numpy as np


# Load an image
image = cv2.imread('billiardimage1.png')

cv2.imshow('canny', image)


if image is not None:

    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (5,5), 0) #only odd nums
    canny  = cv2.Canny(blur, 125, 125)

    # Display the image
    cv2.imshow('canny', canny)

    contours, hierarchy = cv2.findContours(canny, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    # Wait for a key event and close the window when a key is pressed
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
else:
    print("Error: Unable to load the image")

    