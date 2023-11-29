import requests

esp32_ip = "192.168.137.62"  # Replace with your ESP32's IP address

while True:
    command = input("Enter 1 to turn on the LED, 0 to turn it off: ")
    if command == "1" or command == "0":
        response = requests.get(f"http://{esp32_ip}/control?cmd={command}")
        print(response.text)
    else:
        print("Invalid command. Enter '1' or '0'.")