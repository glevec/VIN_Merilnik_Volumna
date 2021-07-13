#define Echo 6
#define Trig 7 
#define RazSenzTla 22 // Razdalja od senzorja do tal v cm
#define premer 123 //mm
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print ("Volumen: ");
  
}

void loop() {
  
  float V = volumen(Razdalja());
  if(V < 0){ //drugace kaze senzor - (negativno vrednost) zaradi debeline dna posode?
    V = 0;
    }
  Serial.print("Volumen: ");
  Serial.print(V);
  Serial.print(" L   ");
  Serial.print("Razdalja do vodene gladine: ");
  Serial.print(Razdalja());
  Serial.println(" cm");
  lcd.setCursor(0,1);
  lcd.print(V);
  lcd.setCursor(5,1);
  lcd.print(" L");
  
  
  
  delay(1000); 
}

// Izracun volumna
 
float volumen(float h){
  float visina = RazSenzTla - h;
  float volumen = (visina * 3.14 * (premer/20)*(premer/20))/1000; // delimo z 20 ker 2 --> da dobimo polmer, 10 da dobimo cm
  return volumen;
  }


// Meritev razdalje

float Razdalja(){
  float meritev;
  
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);

  float cas = pulseIn(Echo,HIGH);
  meritev = cas *0.17/10; //0.17 ker je hitrost zvoka 0.34 mm/s deljeno 2 (dol in gor) pol pa delimo z 10 da dobimo cm

  return meritev;
  }
