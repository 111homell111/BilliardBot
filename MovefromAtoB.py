import cv2
import numpy as np

def detect_circles(image):
    # Convert the image to grayscale
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Apply Gaussian blur to reduce noise
    blurred = cv2.GaussianBlur(gray, (9, 9), 8)

    # Apply Hough Circle Transform
    circles = cv2.HoughCircles(
        blurred, cv2.HOUGH_GRADIENT, dp=1, minDist=20, param1=50, param2=30, minRadius=5, maxRadius=100
    )
    return circles


def display_circles(circles, image):
    # If circles are found, draw them on the original image
    if circles is not None:
        circles = np.round(circles[0, :]).astype("int")
        for (x, y, r) in circles:
            cv2.circle(image, (x, y), r, (0, 255, 0), 4)
        # Display the image with circles
        cv2.imshow("Circles Detected", image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    else:
        print("No circles detected.")


def connect_with_line(image, start_point, end_point):
    cv2.line(image, start_point, end_point, (0, 0, 0), 2)
    cv2.imshow("Line drawn", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


image_path = "pink.png"  # Replace with the actual path of your image
image = cv2.imread(image_path)
if image is not None:
    height, width, channels = image.shape
    circles = detect_circles(image)
    print(width, height)

    print(circles)

    dot_coordinates = (3000,1000)
    circle_coordinates = (int(circles[0][0][0]), int(circles[0][0][1]))

    image = cv2.circle(image, dot_coordinates, radius=50, color=(0, 0, 255), thickness=-1)
    
    connect_with_line(image, dot_coordinates, circle_coordinates)
    #display_circles(circles, image)


   






    

