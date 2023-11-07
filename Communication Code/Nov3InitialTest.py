import requests
import time

ESP32_IP = "192.168.137.158"
while True:
    command = input("Enter 1 to turn on the LED, 0 to turn it off: ")
    if command == "1" or command == "0":
        response = requests.get(f"http://{ESP32_IP}/control?cmd={command}")
        print(response.text)
    else:
        print("Invalid command. Enter '1' or '0'.")
