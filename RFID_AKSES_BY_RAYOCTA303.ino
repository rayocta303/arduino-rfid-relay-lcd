/*CODING INI DIBUAT OLEH RAYOCTA303*/
/*Facebook : www.facebook.com/rayocta303 */
/*E-mail : OctaZoneID@gmail.com*/
/*INDONESIAN CODER*/
#include <SPI.h> 
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10 
#define RST_PIN 9 

#define LED_DENIED_PIN 8  //LED INDIKATOR AKSES DITOLAK PIN D8
#define LED_ACCESS_PIN 4//LED INDIKATOR AKSES DITERIMA PIN D4
#define relay1 A2 //RELAY1 ANALOG2
#define relay2 A3//RELAY ANALOG3
#define alarm 7//BUZZER AKSES DITOLAK D7
LiquidCrystal_I2C lcd(0x27, 16, 2);//SETTING ALAMAT/ADDRESS LiquidCrystal_I2C
MFRC522 mfrc522(SS_PIN, RST_PIN); // Instance of the class
int button  = 2;// TOMBOL RESET D2
int code[] = {47,181,32,107,209}; //SETTING UID/RFID DISINI (Unlock Card)
int codeRead = 0;
String uidString;
/*CODING INI DIBUAT OLEH RAYOCTA303*/
/*Facebook : www.facebook.com/rayocta303 */
/*E-mail : OctaZoneID@gmail.com*/
/*INDONESIAN CODER*/
void setup() {
   Serial.begin(9600); 
   SPI.begin();       // Init SPI bus
   mfrc522.PCD_Init(); // Init MFRC522 
   Serial.println("Arduino RFID reading UID");
   pinMode(button, INPUT);
   pinMode(relay1, OUTPUT);
   pinMode(relay2, OUTPUT);
   pinMode( LED_DENIED_PIN , OUTPUT); 
   pinMode( LED_ACCESS_PIN , OUTPUT);
              digitalWrite(relay1, HIGH);
              digitalWrite(relay2, HIGH);
   lcd.begin();
  // Melampilkan Pesan/Text Pada LCD.
  //BAGIAN INTRO :v
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" System Locked!");
  lcd.setCursor(0,1);
  lcd.print(" Dev.RayOcta303");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" System Locked!");
  lcd.setCursor(0,1);
  lcd.print(" Scan Your Card");
}
void loop() {
/*CODING INI DIBUAT OLEH RAYOCTA303*/
/*Facebook : www.facebook.com/rayocta303 */
/*E-mail : OctaZoneID@gmail.com*/
/*INDONESIAN CODER*/
if ( mfrc522.PICC_IsNewCardPresent())
    {
        if ( mfrc522.PICC_ReadCardSerial())
        {
           lcd.clear();
           Serial.print("Tag UID:");
           lcd.setCursor(0,0);
           lcd.print("Tag UID:");
           lcd.setCursor(0,1);
           for (byte i = 0; i < mfrc522.uid.size; i++) {  
                  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "); 
                  Serial.print(mfrc522.uid.uidByte[i], HEX);
                  
                  lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                  lcd.print(mfrc522.uid.uidByte[i], HEX);
                //  lcd.print(" ");
            }
            
            Serial.println();

            int i = 0;
            boolean match = true;
            while(i<mfrc522.uid.size)
            {
    
               if(!(int(mfrc522.uid.uidByte[i]) == int(code[i])))
               {
                  match = false;
               }
              i++;
            }

            delay(3000);
           lcd.clear();
           lcd.setCursor(0,0);
           /*CODING INI DIBUAT OLEH RAYOCTA303*/
           /*Facebook : www.facebook.com/rayocta303 */
           /*E-mail : OctaZoneID@gmail.com*/
           /*INDONESIAN CODER*/
           
           if(match)
           {
              digitalWrite( LED_ACCESS_PIN , HIGH);//INDIKATOR LED HIJAU MENYALA
              digitalWrite(relay1, LOW);//RELAY 1 MENYALA
              digitalWrite(relay2, LOW);//RELAY 2 MENYALA
              lcd.print("    Welcome!");//PESAN/TEXT PADA LCD
              lcd.setCursor(0,1);
              lcd.print("   RayOcta303");//GANTI NAMA ATAU LINK BOKEP :v
    
           }else{
              digitalWrite( LED_DENIED_PIN , HIGH);//INDIKATOR LED MERAH MENYALA
              digitalWrite(alarm, HIGH);//BUZZER MENYALA
              lcd.print("Access denied!");//MENAMPILKAN PESAN -_-
              lcd.setCursor(0,1);
              lcd.print("Bapak Kau Hacker");// CAPEK NGETIK GUA GAN -___-
    digitalWrite( LED_ACCESS_PIN , LOW);
    digitalWrite( LED_DENIED_PIN , LOW);
    digitalWrite( relay1 , HIGH);
    digitalWrite( relay2 , HIGH);
             Serial.println("\nUnknown Card");
           }
             
             Serial.println("============================");
            
             mfrc522.PICC_HaltA();

             if (digitalRead(button) == HIGH)// JIKA BUTTON DITEKAN AKAN MENGUNCI
             reset_state();
        }
}
}
void reset_state()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" System Locked!");
    
    digitalWrite( LED_ACCESS_PIN , LOW);
    digitalWrite( LED_DENIED_PIN , LOW);
    digitalWrite( relay1 , HIGH);
    digitalWrite( relay2 , HIGH);
}
/*THANKS TO RAYOCTA303 - OCTAZONE - INFINITYZONE*/
