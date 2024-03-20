
#include <LiquidCrystal.h>

LiquidCrystal lcd_1(6, 7, 8, 9, 10, 11);

const int numSensors = 3; 
int sensorPins[numSensors] = {A0, A1, A2}; 
int sensorReadings[numSensors]; 
int voltage[numSensors]; 
int temperatures[numSensors]; 
int relay1 = 12;
int relay2 = 13;

int h1 = 25;
const int h2 = 22;

const int pinTermistor = A3;
const float valorResistencia = 10000.0;
const float tempNominal = 25.0; 
const float resistenciaNominal = 10000.0; 
const float valorBeta = 3950.0; // Valor beta del termistor


void setup()
{
  Serial.begin(9600);
  lcd_1.begin(20, 4); 
  lcd_1.setCursor(0, 0);
  lcd_1.print("Temperaturas:");
  lcd_1.setCursor(0, 2);
  lcd_1.print("Promedio:");
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop() 
{
  int sum = 0;
  for (int i = 0; i < numSensors; i++) {
    sensorReadings[i] = analogRead(sensorPins[i]);
    voltage[i] = sensorReadings[i] * (5000 / 1024); 
    temperatures[i] = voltage[i]/10;
    sum += temperatures[i];
  }
  int lecturaCruda = analogRead(pinTermistor); // Leer el valor analógico
  float voltaje = lecturaCruda * (5.0 / 1023.0); // Convertir la lectura a voltaje
  float resistencia = valorResistencia * (5.0 / voltaje - 1); // Calcular la resistencia del termistor
  float temp_termistor = (1.0 / ((log(resistencia / resistenciaNominal) / valorBeta) + (1.0 / (tempNominal + 273.15)))) - 273.15; 
  int prom = (sum+temp_termistor)/(numSensors+1);
  lcd_1.setCursor(1, 3);
  lcd_1.print(prom);
  lcd_1.setCursor(0, 1);
  lcd_1.print("                ");
    
  lcd_1.setCursor(1, 1);
  for (int i = 0; i < numSensors; i++) {
    lcd_1.print(temperatures[i]);
    Serial.println(temperatures[i]);
    lcd_1.print(","); 
  }
  lcd_1.print(temp_termistor);
  Serial.println(temp_termistor);
  Serial.println(prom);
   
  if (prom >= h1){
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      h1 = h2;
    }
  else if (prom <= h2){
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    h1 = 24;
  }

  delay(1500); 

}
