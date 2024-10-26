#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
const int voltage_sensor=A0;
//Initialize the LCD display
//LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <LiquidCrystal_I2C.h>

 #include <Wire.h>
 LiquidCrystal_I2C lcd(0x27, 16, 2);

 #define BLYNK_TEMPLATE_NAME "energy monitor and controlling"
char auth[] = "--LYuxoW5VNYfXqMP4gAqFE3ar7i5D_u";
char ssid[] = "ciet";
char pass[] = "123456789";

BlynkTimer timer;
bool Relay = 0;

#define Battery D3 
#define buz D4

void setup() {
  Serial.begin(9600);
  pinMode(Battery, OUTPUT);
   pinMode(buz, OUTPUT);
  digitalWrite(Battery, HIGH);
  digitalWrite(buz, HIGH);
  pinMode(voltage_sensor, INPUT);
  lcd.begin();
lcd.home();
lcd.print("Welcome");
Serial.println("Connecting to ");

  lcd.backlight();

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  lcd.setCursor(1, 0);
  lcd.print("System Loading");
  for (int a = 0; a <= 15; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(500);
  }
  lcd.clear();


  timer.setInterval(100L, volageSensor);
}

BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(Battery, LOW);
    lcd.setCursor(0, 1);
    lcd.print("fan ON ");
  } else {
    digitalWrite(Battery, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("fan is OFF");
  }
}
void volageSensor() 
{
  
float sensorValue = analogRead(voltage_sensor);
  float vol = sensorValue * (12 / 1023.0);
  Serial.print("voltage_sensor_state: ");
  Serial.println(vol);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("voltage:");
  lcd.print(vol);
  delay(1000); 
  Blynk.virtualWrite(V0, vol);
  
  
  
  lcd.print(" ");
if ( vol>8) {
    digitalWrite(buz, LOW);
     //delay(500);
    // digitalWrite(waterPump, HIGH);
     //delay(500);
    //lcd.setCursor(0, 1);
    //lcd.print("fireing is ON ");
  } else {
    digitalWrite(buz, HIGH);
    //lcd.setCursor(0, 1);
    //lcd.print("fireing is OFF");
  }
}

void loop() {
  Blynk.run();
  timer.run();
}
