#include "MQ135.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include "DHT.h"
#define DHTTYPE DHT11
DHT dht(9, DHTTYPE);

int val;
int sensorPin = A0;
int sensorValue = 0;
MQ135 gasSensor = MQ135(A0);

void setup() {
  Serial.begin(9600);
  lcd.init();
  dht.begin();
  pinMode(A0, INPUT); //MQ135
  pinMode(8, OUTPUT); //Rele
  pinMode(4, INPUT);  //Botao
}

void loop() {
  lcd.setBacklight(HIGH);

  int h = dht.readHumidity();
  float t = dht.readTemperature();

  MQ135 gasSensor = MQ135(A0); // Attach sensor to pin A0
  float rzero = gasSensor.getRZero();
  int sensorIn = A0;
  val = analogRead(A0);
  float ppm = gasSensor.getPPM()/100000000;

  if (t > 50){
    digitalWrite(8, LOW);
    lcd.setCursor(0,0);
    lcd.print("SUPERAQUECIMENTO");
    lcd.setCursor(2,1);
    lcd.print("DESLIGUE JA");
    delay(500);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
  }
  else if (ppm > 2000){
    //digitalWrite(8, LOW);
    lcd.setCursor(1,0);
    lcd.print("EXCESSO DE CO2");
    lcd.setCursor(6,1);
    lcd.print("NO AR");
    delay(500);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
  }
  else if (digitalRead(4) == 0){
    digitalWrite(8, LOW);
    lcd.setCursor(1,0);
    lcd.print("APERTE O BOTAO");
    lcd.setCursor(2,1);
    lcd.print("PARA INICIAR");
    delay(500);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
  }else{
    digitalWrite(8, HIGH);
    lcd.setCursor(1,0);
    lcd.print("U:");
    lcd.setCursor(3,0);
    lcd.print(h);
    lcd.setCursor(5,0);
    lcd.print("%");
    lcd.setCursor(7,0);
    lcd.print("T:");
    lcd.setCursor(9,0);
    lcd.print(t);
    lcd.setCursor(13,0);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("CO2:");
    lcd.setCursor(4,1);
    lcd.print(ppm); //MQ135 AIR QUALITY
    lcd.setCursor(12,1);
    lcd.print("ppm");
    delay(500);
  }
}
