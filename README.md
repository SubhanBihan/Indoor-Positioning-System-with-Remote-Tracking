# Indoor-Positioning-System-with-Remote-Tracking
Each room will have 1 (or more, depending on room size) servers which are ESP32 modules.
Each object will have 1 BLE client tag, for which we're also using ESP32 modules.

The server will send data to the cloud (ThingSpeak in this case) via WiFi.
ThingSpeak then decodes the received data to determine the location of each object.
This info is finally sent to a Mobile App upon an http request from it.

All the relevant code can be found in this repository.
