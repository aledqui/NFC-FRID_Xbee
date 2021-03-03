#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

MFRC522::MIFARE_Key key;
String a;
int c = 0;

Servo miServo;

void setup() {
    miServo.attach(3);
    pinMode(7,OUTPUT);
    Serial.begin(9600); // Initialize serial communications with the PC
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

//    Serial.println(F("Scan a MIFARE Classic PICC to demonstrate read and write."));
    Serial.print(F("Sistema armado"));
    dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
    Serial.println();
    miServo.write(90);
}

void loop() {
  delay(500);
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;
    unsigned char comando = 0;
        
    a = "";
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    if (a =="812514943" || a =="16621619459" || a == "1261125135" || 
    a == "44159189126" || a == "14713117463" || a == "179256663" || a =="15813657212" ){
      digitalWrite(7,HIGH);      
      if (c == 1){
      Serial.println("Cerrando  el estante");
      miServo.write(180);
      delay (450);
      miServo.write(90);
      c = 0;
      }
      else{
      Serial.println("Abriendo el estante");
      miServo.write(0);
      delay (500);
      miServo.write(90);
      c = 1;
      }
      digitalWrite(7,LOW);     
       }      
      }


void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        a = a + String(buffer[i]);
        } 
     //   Serial.println(a);                   // Se ocupa para ingresar otra base
    }
