import cv2
import requests

esp32_ip = "192.168.137.62" 

# Load the pre-trained Haar Cascade classifier for face detection
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# Capture video from the default camera using DirectShow backend
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

# Initialize a variable to track the last state of face detection
last_state = None

while True:
    # Read each frame from the video capture
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1)  # Flip the frame horizontally

    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Perform face detection
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    # Current state of face detection
    current_state = '1' if len(faces) > 0 else '0'

    # Compare the current state with the last state
    if current_state != last_state:
        response = requests.get(f"http://{esp32_ip}/control?cmd={current_state}")
        print(response.text)

        print(current_state)  # Output to terminal if state changes
        last_state = current_state  # Update the last state

    # Draw rectangles around the faces
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)

    # Display the face detection status on the video feed
    face_label = f'Face Detected: {current_state}'
    cv2.putText(frame, face_label, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 255), 2, cv2.LINE_AA)

    # Display the resulting frame
    cv2.imshow('Video', frame)

    # Break the loop when 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
cap.release()
cv2.destroyAllWindows()
