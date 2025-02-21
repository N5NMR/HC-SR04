#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adresse des Displays: 0x27, 16 Spalten, 2 Zeilen

// Pin für den Sender
int SENDEN = D5;

// Pin für das vom Objekt reflektierte Signal
int ECHO = D6;

// Variable für die Speicherung der Entfernung
long Entfernung = 0;

void setup() 
{
  pinMode(SENDEN, OUTPUT);
  pinMode(ECHO, INPUT);
  
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight(); // Hintergrundbeleuchtung einschalten
  lcd.setCursor(0, 0);
  lcd.print("Entfernung (cm):");
}

void loop()
{
  digitalWrite(SENDEN, LOW);
  delay(5);

  digitalWrite(SENDEN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENDEN, LOW);

  long Zeit = pulseIn(ECHO, HIGH);
  Entfernung = (Zeit / 2) * 0.03432;
  delay(500);

  if (Entfernung < 100)
   {
    lcd.setCursor(0, 1);
    lcd.print("                "); // Alte Daten löschen
    lcd.setCursor(0, 1);
    lcd.print(Entfernung);
    Serial.print("Entfernung in cm: ");
    Serial.println(Entfernung);
  }
}
