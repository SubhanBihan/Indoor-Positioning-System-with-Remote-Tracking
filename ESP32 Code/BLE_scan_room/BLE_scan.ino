#include <WiFi.h>
#include "ThingSpeak.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "Definition.h"
#include "accessories.h"
//Server1
/*
const char* ssid=      "Galaxy M106E46";
const char* password=  "figp6207";
unsigned long myChannelNumber = 1;
unsigned long FieldNumber = 1;
#define myWriteAPIKey  "D6VEJ4T9EYP94COA"
*/

//Server2

 const char* ssid=      "TP-Link_8A9C";
 const char* password=  "0123456789";
 unsigned long myChannelNumber = 1;
unsigned long FieldNumber = 1;
#define myWriteAPIKey  "8VWJ1K35MFF53IOZ"

WiFiClient  client;


// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 20000;

int scanTime = 5; //In seconds
BLEScan* pBLEScan;
int client_status = 0;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      std::string a = advertisedDevice.getAddress().toString();
      if((advertisedDevice.getServiceUUID().toString()==SERVICE_UUID)&&(advertisedDevice.getRSSI()>RSSI_TH)&&((a==TAG1)||(a==TAG2)))
      {
        Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
        delay(20);
        std::string name = advertisedDevice.getName();
        int temp = name[3]-48;
        client_status |=(1<<(temp-1)); 
      }
    }
};

void BLE_init(void)
{
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void WiFi_init(void)
{
    Serial.println();
    Serial.print("[WiFi] Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    int tryDelay = 500;
    int numberOfTries = 20;

    // Wait for the WiFi event
    while (true) {
        
        switch(WiFi.status()) {
          case WL_NO_SSID_AVAIL:
            Serial.println("[WiFi] SSID not found");
            break;
          case WL_CONNECT_FAILED:
            Serial.print("[WiFi] Failed - WiFi not connected! Reason: ");
            return;
            break;
          case WL_CONNECTION_LOST:
            Serial.println("[WiFi] Connection was lost");
            break;
          case WL_SCAN_COMPLETED:
            Serial.println("[WiFi] Scan is completed");
            break;
          case WL_DISCONNECTED:
            Serial.println("[WiFi] WiFi is disconnected");
            break;
          case WL_CONNECTED:
            Serial.println("[WiFi] WiFi is connected!");
            Serial.print("[WiFi] IP address: ");
            Serial.println(WiFi.localIP());
            blink(HIGH);
            return;
            break;
          default:
            Serial.print("[WiFi] WiFi Status: ");
            Serial.println(WiFi.status());
            break;
        }
        delay(tryDelay);
        
        if(numberOfTries <= 0){
          Serial.print("[WiFi] Failed to connect to WiFi!");
          // Use disconnect function to force stop trying to connect
          WiFi.disconnect();
          return;
        } else {
          numberOfTries--;
        }
    }
}
void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");
  pinMode(LED,OUTPUT);
  delay(100);
  WiFi_init();
  vTaskDelay(500);
  ThingSpeak.begin(client);
  Serial.println("Scanning...");
  BLE_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(2000);


    if(WiFi.status()==WL_CONNECTED)
    {
    int x = ThingSpeak.writeField(myChannelNumber, FieldNumber, client_status, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
      Serial.println(client_status,BIN);
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
    }
    client_status=0;
    delay(timerDelay);
}
