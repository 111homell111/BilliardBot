#include <BluetoothSerial.h>


#define ledPIN 5
#define IN1 16
#define IN2 4

BluetoothSerial SerialBT;
byte BTData;

/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void setup()
{
  pinMode(ledPIN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin();
  Serial.println("Bluetooth Started! Ready to pair...");
}

void loop()
{
  if(SerialBT.available())
  {
    BTData = SerialBT.read();
    Serial.write(BTData);
  }


 if(BTData == '2')
  {
    digitalWrite(ledPIN, HIGH);
    //Backward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH); 
  }
  

  if(BTData == '1')
  {
    digitalWrite(ledPIN, HIGH);
    //Forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW); 
  }
  
  if(BTData == '0')
  {
    digitalWrite(ledPIN, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW); 
  }
}