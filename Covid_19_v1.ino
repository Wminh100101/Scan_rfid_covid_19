#include <SoftwareSerial.h>
#include <PN532_SWHSU.h>
#include <PN532.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
SoftwareSerial SWSerial( 5, 4 ); // RX, TX
SoftwareSerial HCSerial( 3, 2  );
PN532_SWHSU pn532swhsu( SWSerial );
PN532 nfc( pn532swhsu );

int red = A1;
int green = A0;
int buzzer = 10;

void mot_mui() {

  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(5000);
  digitalWrite(red, LOW);

}

void hai_mui() {

  digitalWrite(green, HIGH);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(5000);
  digitalWrite(green, LOW);

}
void khong_mui() {
  digitalWrite(buzzer,LOW);
  for(int i = 1;i<=8;i++){

  digitalWrite(red,HIGH);
  delay(100);
  digitalWrite(red,LOW);
  delay(100); 
  
  }

  digitalWrite(buzzer, HIGH);


}

void mui_mot(String ten,String date){
  lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("Name:");
    lcd.print(ten);

    lcd.setCursor(0, 1);
    lcd.print("Type:");
    lcd.print("1");

    lcd.setCursor(0, 2);
    lcd.print("Date:");
    lcd.print(date);

    mot_mui();
    waiting();
}
void mui_hai(String ten,String date){
  lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("Name:");
    lcd.print(ten);

    lcd.setCursor(0, 1);
    lcd.print("Type:");
    lcd.print("2");

    lcd.setCursor(0, 2);
    lcd.print("Date:");
    lcd.print(date);

    hai_mui();
    waiting();
}
void mui_khong(String ten, String date){
  lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Name:");
    lcd.print(ten);

    lcd.setCursor(0, 1);
    lcd.print("Type:");
    lcd.print("0");

    lcd.setCursor(0, 2);
    lcd.print("Date:");
    lcd.print(date);
    
    khong_mui();
    delay(3000);
    waiting();
  
}
 
void xuat_lcd(String uid) {

  const String name1 = "Nguyen Tan Truong";
  const String name2 = "Tran Thi My Linh";
  const String name3 = "Vo Van Tung";
  
  //String name4 = "Vo Duc Huy";
  if(uid == "202217248165"){
    mui_hai(name1,"03/12/2021");
  }
  else if(uid == "18824524247"){
    mui_mot(name2,"18/10/2021");
  }
  else if(uid == "262114921"){
    mui_khong(name3,"**/**/****");
  }
  else if(uid == "436162234120114128"){
    mui_hai("Nhat Minh","25/11/2021");
  }
//  else {
//
//    lcd.clear();
//    lcd.setCursor(4,1);
//    lcd.print("NOT FOUND!");
//    for (int i = 0; i < 2; i++) {
//      digitalWrite(buzzer, LOW);
//      delay(100);
//      digitalWrite(buzzer, HIGH);
//      delay(100);
//    }
//    waiting();
//    //      tranform = "NONENONE";
//    //      Serial.print(tranform);
//  }
}

void waiting(){
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print("Cham the ben duoi");
  lcd.setCursor(2, 2);
  lcd.print("");
}

void setup() {

  Serial.begin(115200);
  HCSerial.begin(9600);
  nfc.begin();
  lcd.init();
  lcd.backlight();
  nfc.SAMConfig();

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(buzzer, HIGH);

  waiting();
  
}

void loop() {
  
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  
  String str1;
  String str2;
  uint8_t uidLength;                       
  int check = 1;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  while (!success)
  {
    delay(100);
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  }
  for (uint8_t i = 0; i < uidLength; i++)
  {
    str1 = String(uid[i]);
    str2 += str1;
  }

  Serial.println(str2);
  HCSerial.print(str2);
  xuat_lcd(str2);
  

  delay(500);
}
