#include <LiquidCrystal.h>
#include <WiFi.h>
#include <ThingSpeak.h>

#include <LiquidCrystal.h>

float  Tc, adc1, adc2, adc3, adc4 = 0;
int PinoNTC1 = 25;
int PinoNTC2 = 33;
int PinoNTC3 = 14;
int PinoNTC4 = 27;
LiquidCrystal lcd_1(22, 23, 5, 18, 19, 21);

const char* ssid = "IZZI-5114-5G";
const char* password = "704FB81E5114";

unsigned long channelID = 2466910;
const char* WriteAPIKey = "VS1B5KYWXYEXCIJY";

WiFiClient cliente;


void setup() {
Serial.begin(115200);

ThingSpeak.begin(cliente);
WiFi.begin(ssid,password);

lcd_1.begin(20, 4); // Set up the number of columns and rows on the LCD.
lcd_1.setCursor(0, 0);
lcd_1.print("La temperatura es");
lcd_1.setCursor(0, 2);
}

void loop() {
adc1 = (analogRead(PinoNTC1))*5000/1024;
adc2 = (analogRead(PinoNTC2))*5000/1024;
adc3 = (analogRead(PinoNTC3))*5000/1024;
adc4 = (analogRead(PinoNTC4))*5000/1024;
Tc = (adc1+adc2+adc3+adc4)/4;
lcd_1.setCursor(0, 0);
lcd_1.print(Tc);
Serial.println(adc1);
Serial.println(adc2);
Serial.println(adc3);
Serial.println(adc4);
ThingSpeak.setField(1, Tc);
ThingSpeak.writeFields(channelID, WriteAPIKey);

delay(1000);
}
