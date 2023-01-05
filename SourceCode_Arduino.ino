#include "DHT.h"
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include<LiquidCrystal_I2C.h>
#include<Wire.h>
#define DHTPIN 2
#define DHTTYPE DHT11
#define SS_PIN 53
#define RST_PIN 5
#define LED_Blind 8 
#define LED_other 9 



const int trigPin = 12;
const int echoPin = 13;

const int LED1 = A0;
const int LED2 = A1;
const int LED3 = A2;
const int LED4 = A3;
const int LED5 = A4;


int duration = 0;
int distance = 0;


int led = A2;
DHT dht(DHTPIN, DHTTYPE);

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x3F,16,2);


Servo myServo1;
Servo myServo2;
Servo myServo3;
 //define servo name
/* Database of RFID's */
String open = "E3 57 F3 2E";
String uid1 = "D3 5C 2B 2E";
String uid2 = "E3 6D 11 2E";
String uid3 = "72 FB 4B 1A";
String close = "40 97 DB 1D";

void setup() 
{
  pinMode(trigPin , OUTPUT);
  pinMode(echoPin , INPUT);
  
  pinMode(LED1 , OUTPUT);
  pinMode(LED2 , OUTPUT);
  pinMode(LED3 , OUTPUT);

  
  Serial.begin(9600);

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  dht.begin();
   lcd.begin();                    
  lcd.clear();
  lcd.backlight();

   Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo1.attach(3);
  myServo2.attach(6);
  myServo3.attach(11);
  
  
  myServo1.write(90);
  myServo2.write(0); 
  myServo3.write(0);//servo start position
    pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED_Blind, OUTPUT);
  pinMode(LED_other, OUTPUT);
  //  pinMode(BUZZER, OUTPUT);
  // noTone(BUZZER);
 
  
  Serial.println("Put your card to the reader...");
  Serial.println();

}

void loop()
{
 digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;

  if ( distance <= 8 )
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    Serial.println("Shortage of product in the container");
    
  }
  else
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
 
  

  delay(2000);
  // read humidity
  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();
  // read temperature as Fahrenheit
  float tempF = dht.readTemperature(true);
  // check if any reads failed
  if (isnan(humi) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
   
    if(tempC < 27.50) { digitalWrite(led, HIGH); Serial.println(tempC); } else { digitalWrite(led, LOW);Serial.println(tempC); }
  }
   lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Welcome ");
  lcd.setCursor(0,1);
  lcd.print("Scan Your ID    ");

   if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  lcd.clear();
 
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
   if (content.substring(1) == open) //change here the UID of the card/cards that you want to give access
  {
   
    
    myServo3.write(90);
    delay(1000);
    // myServo3.write(0);
    // delay(1000);

   
  }\
  
    else if (content.substring(1) == close) //change here the UID of the card/cards that you want to give access
  {
   
    
    myServo3.write(0);
    delay(1000);
   
  }
  else if (content.substring(1) == uid1) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
  digitalWrite(LED4, HIGH);
    
    //  lcd.setCursor(0,0);
    // lcd.print("Tag 01");
    // lcd.setCursor(0,1);
    // lcd.print("Authorized access");
    // delay(3000);
    // lcd.clear();
       myServo2.write(30);
    delay(1000);
    myServo1.write(35);
    delay(1000);
 
    myServo1.write(90);
    delay(1000);
    myServo2.write(0);
    delay(1000);
    digitalWrite(LED4, LOW);
    //  lcd.setCursor(0,0);
    // lcd.print("Tag 01");
    // lcd.setCursor(0,1);
    // lcd.print("Authorized access");
    // delay(3000);
    // lcd.clear();


  }
  else if (content.substring(1) == uid2) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(LED_Blind, HIGH);
    delay(500);
    digitalWrite(LED4, HIGH);
  //     pinMode(BUZZER, OUTPUT);
  // noTone(BUZZER);
     
    //  lcd.setCursor(0,0);
    // lcd.print("Tag 02");
    // lcd.setCursor(0,1);
    // lcd.print("Authorized access");
    // delay(3000);
    // lcd.clear();
     myServo2.write(30);
    delay(1000);
    myServo1.write(35);
    delay(1000);
   
    myServo1.write(90);
    delay(1000);
    myServo2.write(0);
    digitalWrite(LED_Blind, LOW);
    delay(1000);
    digitalWrite(LED4, LOW);
    //  lcd.setCursor(0,0);
    // lcd.print("Tag 01");
    // lcd.setCursor(0,1);
    // lcd.print("Authorized access");
    // delay(3000);
    // lcd.clear();

  }
    else if (content.substring(1) == uid3) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(LED_other, HIGH);
    delay(500);
digitalWrite(LED4, HIGH);
    //  lcd.setCursor(0,0);
    // lcd.print("Tag 03");
    // lcd.setCursor(0,1);
    // lcd.print("Authorized access");
    // delay(3000);
    // lcd.clear();

     myServo2.write(30);
    delay(1000);
    
    myServo1.write(35);
    delay(1000);
   
    myServo1.write(90);
    delay(1000);
    myServo2.write(0);
    digitalWrite(LED_other, LOW);
    delay(1000);
digitalWrite(LED4, LOW);    
    //  lcd.setCursor(0,0);
    // lcd.print("Tag 01");
    // lcd.setCursor(0,1);
    // lcd.print("Authorized access");
    // delay(3000);
    // lcd.clear();

  }
  
    

 else   {
    Serial.println(" Access Denied");
    Serial.println();
    digitalWrite(LED5, HIGH);
    
    // lcd.setCursor(0,0);
    // lcd.print("Unknown");
    // lcd.setCursor(0,1);
    // lcd.print("Access Denied");
    
    delay(3000);  
    digitalWrite(LED5,LOW);
    //  lcd.clear();  
   
  
  }
}




