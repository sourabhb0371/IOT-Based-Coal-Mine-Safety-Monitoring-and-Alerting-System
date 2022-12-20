//IOT Based Coal Mine Safety Monitoring and Alerting System

#define BLYNK_TEMPLATE_ID "TMPLPyzuJL2F"
#define BLYNK_DEVICE_NAME "coalmine safety"
#define BLYNK_AUTH_TOKEN "T8YhqiNkvsXAjWeJGNq__7BsIwJ-OCJw"

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
char auth[] = "T8YhqiNkvsXAjWeJGNq__7BsIwJ-OCJw";


#include <Wire.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MQ2pin D4
#define relay D7

int sensorValue;  //variable to store sensor value
//pinMode (D7, OUTPUT);
void setup() {
pinMode (relay, OUTPUT);
pinMode(MQ2pin, INPUT);
Serial.begin(9600); // sets the serial port to 9600
Serial.println("MQ2 warming up!");
Wire.begin(4, 5);
lcd.begin();   // initializing the LCD
lcd.backlight(); // Enable or Turn On the backlight
lcd.print(" Coalmine safety "); // Start Printing
delay(5000);
lcd.clear();
lcd.print(" Sensor warming up"); // Start Printing
Blynk.begin(auth, "113", "12345678");

delay(20000); // allow the MQ2 to warm up
}

void loop() {
sensorValue = digitalRead(MQ2pin); // read analog input pin 0
Blynk.run();

lcd.clear();
lcd.print(" parameters "); // Start Printing

Serial.print("Sensor Value: ");
Serial.println(sensorValue);
  if (sensorValue == 0)
  {
lcd.clear();
Blynk.virtualWrite(V0, "smoke detected");

lcd.print("smoke detected "); // Start Printing
delay(500);
digitalWrite(relay, HIGH);
lcd.clear();
lcd.print("turning on alarm"); // Start Printing
delay(500);
delay(100);
  }
  else {
digitalWrite(relay, LOW);
Blynk.virtualWrite(V0, " no smoke detected");

lcd.clear();
lcd.print("No smoke"); // Start Printi
delay(1000);
  }

Serial.print(analogRead(A0));
  if (analogRead(A0) > 850) {
lcd.clear();
lcd.print("FIRE detected "); // Start Printing
Blynk.virtualWrite(V1, "fire detected");

delay(500);
digitalWrite(relay, HIGH);
lcd.clear();
lcd.print("turning on alarm"); // Start Printing
delay(500);
  }
  else {
digitalWrite(relay, LOW);
Blynk.virtualWrite(V1, "no fire detected");

lcd.clear();
lcd.print("No FIRE"); // Start Printing
delay(1000);
  }
delay(1000); // wait 2s for next reading
}
