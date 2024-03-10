# Indoor-Positioning-System-with-Remote-Tracking
Each room will have 1 (or more, depending on room size) servers which are ESP32 modules.
Each object will have 1 BLE client tag, for which we're also using ESP32 modules.

The server will send data to the cloud (ThingSpeak in this case) via WiFi. You should create a separate ThingSpeak Channel for each server to avoid upload-rate conflicts.
ThingSpeak then decodes the received data to determine the location of each object. This is done by running MATLAB code, which is done (via a React App) every time data is written to a Server channel.
This info is written to each Object Field/Channel and finally sent to a Mobile App upon an http request from it.

All the relevant code can be found in this repository.
