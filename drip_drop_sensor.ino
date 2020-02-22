// hello world
#include <LiquidCrystal.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 9

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int cs=13;// pin 13 for contrast PWM
const int contrast = 100;// default contrast
int h=4;
int m=59;
int s=45;
int flag=0; //PM
int bluePin=10;
int redPin=8;

// For accurate Time reading, use Arduino Real Time Clock and not just delay()
static uint32_t last_time, now = 0; // RTC


void setup() 
{
  Serial.begin(9600);
  pinMode(bluePin,OUTPUT);
  pinMode(redPin,OUTPUT);

  lcd.begin(16,2);
  analogWrite(cs,contrast);// Adjust Contrast VO
  now=millis(); // read RTC initial value  


// For accurate Time reading, use Arduino Real Time Clock and not just delay()
static uint32_t last_time, now = 0; // RTC
}


void loop()
{
  lcd.begin(16,2);// every second
// Update LCD Display
// Print TIME in Hour, Min, Sec + AM/PM
 lcd.setCursor(0,0);
 lcd.print("Time ");
 if(h<10)lcd.print("0");// always 2 digits
 lcd.print(h);
 lcd.print(":");
 if(m<10)lcd.print("0");
 lcd.print(m);
 lcd.print(":");
 if(s<10)lcd.print("0");
 lcd.print(s);

 if(flag==0) lcd.print(" AM");
 if(flag==1) lcd.print(" PM");

 if(s==60){
  s=0;
  m=m+1;
 }
 if(m==60)
 {
  m=0;
  h=h+1;
 }
 if(h==13)
 {
  h=1;
  flag=flag+1;
  if(flag==2)flag=0;
 }
 s=s+1; //increment sec. counting
 
 lcd.setCursor(0,1);// for Line 2
  int chk = DHT.read11(DHT11_PIN);
 // Serial.println(DHT.temperature);
  if(s%2 == 0)
  {
  lcd.print("Humidity = ");
  lcd.println(DHT.humidity);
  }
  delay(1000);

  if(h == 5 && m ==0 && s<5 && flag == 0 && DHT.humidity < 85)
  {
    digitalWrite(redPin,LOW);
    digitalWrite(bluePin,HIGH);
    Serial.print("i am now watering the flowers");
    Serial.print("\n");
  }
  else
  {
    digitalWrite(redPin,HIGH);
    digitalWrite(bluePin,LOW);
  }
}
