#include <SPI.h>
#include "MFRC522.h"
#include <Adafruit_MLX90614.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "webpageCode.h";
//------------------------------------------
ESP8266WebServer server(80);
const char* ssid = "miniproject";
const char* password = "12345678";
constexpr uint8_t RST_PIN = D3;     
constexpr uint8_t SS_PIN = D4;
double temperature(void);
//------------------------------------------

MFRC522 rfid(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

String tag;
double temp;
String rfidreading;
void webpage()
{
  server.send(200,"text/html", webpageCode);
}
//=================================================================
void setup()
{
  Serial.begin(115200);
  Serial.println("Adafruit MLX90614 test");
  mlx.begin(); 
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  WiFi.begin(ssid, password);
  while(WiFi.status()!=WL_CONNECTED){delay(500);Serial.print(".");}
  Serial.println();
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());

  server.on("/", webpage);
  server.begin();
}
//=================================================================
void loop()
{
  
  server.handleClient();

   if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    
    if(tag == "24311916221"){
        rfidreading ="Employee 1"; 
      Serial.println(rfidreading);
      temp = temperature();
      String data = "{\"Name\":\""+ String(rfidreading) +"\", \"Temperature\":\""+ String(temp) +"\"}";
     server.send(200, "text/plane", data);
     
      
    }
         else if(tag == "511121617"){
        rfidreading ="Employee 2"; 
      Serial.println(rfidreading);
      temp = temperature();
      String data = "{\"Name\":\""+ String(rfidreading) +"\", \"Temperature\":\""+ String(temp) +"\"}";
     server.send(200, "text/plane", data);
     
      
    }
     delay(100);     
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  
  
 

  } 
}


double temperature(){
double temp3= mlx.readObjectTempF();
double temp2 = mlx.readObjectTempC();


  Serial.print("the temperature is ");
  Serial.print(temp2);
  Serial.print("c");
   Serial.print(temp3);
   Serial.print("f");
  Serial.println(" ");
  return temp2;
  }
