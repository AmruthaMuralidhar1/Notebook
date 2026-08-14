/*
 @ YouTube | Tech at Home
 @ RFID Basics
 @ Tutorial video link: https://youtu.be/8YCoigIOOxU
*/

#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9

#define Green_Led 3
#define Red_Led   2 

MFRC522 mfrc522(SS_PIN, RST_PIN);   
 
void setup() 
{
  Serial.begin(9600);   
  SPI.begin();     
  mfrc522.PCD_Init();   
  pinMode(Green_Led, OUTPUT);
  pinMode(Red_Led, OUTPUT);
  Serial.println("Place your card...");
  Serial.println();
}

void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  if (content.substring(1) == "EB 32 FF 03") //Add your UID
  {
    Serial.println("Access Granted");
    Serial.println();
    digitalWrite(Green_Led, HIGH);
    delay(2000);
    digitalWrite(Green_Led, LOW);
  }
 else
 {
    Serial.println("Access Denied");
    digitalWrite(Red_Led, HIGH);
    delay(2000);
    digitalWrite(Red_Led, LOW);
  }
} 
