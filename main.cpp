#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#define outPin 8
#define s0 9
#define s1 10
#define s2 11
#define s3 12
#define buzzerPin 13

boolean DEBUG = true;

int red, grn, blu;
String color = "";
long startTiming = 0;
long elapsedTime = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(outPin, INPUT); 
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Welcome To");
  lcd.setCursor(1, 1);
  lcd.print("Color Detector");
  delay(2000);
  lcd.clear();
  startTiming = millis();
}

void loop() {
  getColor();
  
  if (DEBUG) printData();
  elapsedTime = millis() - startTiming;
  if (elapsedTime > 1000) {
    showDataLCD();
    startTiming = millis();
  }
  soundBuzzer();
}

void readRGB() {
  red = 0, grn = 0, blu = 0;
  
  int n = 10;
  for (int i = 0; i < n; ++i) {
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    red = red + pulseIn(outPin, LOW);
 
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    grn = grn + pulseIn(outPin, LOW);
    
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    blu = blu + pulseIn(outPin, LOW);
  }
  red = red / n;
  grn = grn / n;
  blu = blu / n;
}

void printData(void) {
  Serial.print("red= ");
  Serial.print(red);
  Serial.print("   green= ");
  Serial.print(grn);
  Serial.print("   blue= ");
  Serial.print(blu);
  Serial.print(" - ");
  Serial.print(color);
  Serial.println(" detected!");
}

void showDataLCD(void) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R");
  lcd.print(red);
  lcd.setCursor(6, 0);
  lcd.print("G");
  lcd.print(grn);
  lcd.setCursor(12, 0);
  lcd.print("B");
  lcd.print(blu);  
  lcd.setCursor(0, 1);
  lcd.print("Color: ");  
  lcd.print(color);  
}

void getColor() {  
  readRGB();
  if (red >= 4 && red <= 5 && grn >= 5 && grn <= 8 && blu >= 5 && blu <= 8) color = "WHITE";
  else if (red >= 8  && red <= 10 && grn >= 7 && grn <= 8 && blu >= 6 && blu <= 8) color = "BLUE";
  else if (red >= 10 && red <= 13 && grn >= 11 && grn <= 16 && blu >= 13 && blu <= 16) color = "GREEN";
  else if (red >= 6 && red <= 7 && grn >= 15 && grn <= 18 && blu >= 13 && blu <= 16) color = "RED";
  else if (red >= 4 && red <= 6 && grn >= 6 && grn <= 8 && blu >= 9 && blu <= 11) color = "YELLOW";
  else if (red >= 5 && red <= 7 && grn >= 12 && grn <= 16 && blu >= 13 && blu <= 18) color = "ORANGE";
  else if (red >= 8 && red <= 10 && grn >= 15 && grn <= 18 && blu >= 14 && blu <= 16) color = "BROWN";
  else color = "NO_COLOR";
}

void soundBuzzer() {
  if (color == "WHITE") tone(buzzerPin, 1000); 
  else if (color == "BLUE") tone(buzzerPin, 2000); 
  else if (color == "GREEN") tone(buzzerPin, 3000); 
  else if (color == "RED") tone(buzzerPin, 4000); 
  else if (color == "YELLOW") tone(buzzerPin, 5000); 
  else if (color == "ORANGE") tone(buzzerPin, 6000); 
  else if (color == "BROWN") tone(buzzerPin, 7000); 
  else noTone(buzzerPin); 
}
