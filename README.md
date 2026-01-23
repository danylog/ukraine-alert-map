# ESP32 Ukraine Air Alert Map

This project uses an ESP32 development board and 25 WS2812B LEDs to display real-time air raid alerts for each region in Ukraine. Alert data is fetched from the [alerts.in.ua](https://alerts.in.ua) API.

The device is still in development, further upgrades will be added

<img width="2566" height="1924" alt="image" src="https://github.com/user-attachments/assets/d5c81af3-9ea2-42e1-a451-2b4ca09acd7f" />


## Setup Guide

### Code (Arduino IDE)

1. **Get an API key** by filling out [this form](https://alerts.in.ua/api-request). The instructions are in Ukrainian, but you can submit your request in English.

2. **Configure your credentials**: Create an `env.h` file in the `esp32code` folder and add your API key following the [example](env_example.h).

3. Install the necessary libraries: 
   1. [WiFi Manager](https://github.com/tzapu/WiFiManager)
   2. [WS2812FX](https://github.com/kitesurfer1404/WS2812FX)

4. **Upload to your ESP32** using the Arduino IDE. I used an [AZDelivery ESP32 with CP2102](https://www.amazon.de/dp/B08BTWJGFX), but any ESP32 board should work.

### Wiring

The wiring is straightforward. [WS2812B LEDs](https://www.amazon.de/dp/B088K8DVMQ) are addressable, so you only need 3 wires to connect the first LED to the ESP32: **5V**, **GND**, and **GPIO23** (data). The remaining LEDs are daisy-chained together—connect DOUT of each LED to DIN of the next. Use around 7cm of cable in between LEDs.

> **Tip:** To use a different GPIO pin, simply change the `LED_PIN` value in the code.

#### Connection Diagram

```
    ESP32                   LED 1                LED 2                LED 25
┌───────────┐           ┌─────────┐          ┌─────────┐          ┌─────────┐
│           │           │  DIN ●──┼── DOUT ──┼── DIN ●─┼── DOUT ──┼── DIN   │
│    GPIO23 ├───────────┤         │          │         │   ....   │         │
│           │           │   VCC ●─┼──────────┼── VCC ●─┼──────────┼── VCC ● │
│        5V ├───────────┤         │          │         │          │         │
│           │           │   GND ●─┼──────────┼── GND ●─┼──────────┼── GND ● │
│       GND ├───────────┤         │          │         │          │         │
│           │           └─────────┘          └─────────┘          └─────────┘
└───────────┘   
                
```

> **Note:** Use sufficiently thick wires for 5V and GND to prevent voltage drop on the LEDs at the end of the chain.

### 3D printing

To make the casing you will need 2 types of filament: an opaque one (I used Black PLA) for the back and a Translucent (I used Natural PETG) for the 25 Regions. You can download all the files from my [Printables page]()

### Assembly

<img width="2566" height="1924" alt="image" src="https://github.com/user-attachments/assets/e6e3bd48-f4a0-4485-955a-50fb2b1dfe94" />


1. Once you have the LEDs soldered and the casing printed, first glue the opaque parts together, to make a map of Ukraine. Epoxy 2-component resin works the best here.

2. Glue the LEDs into their respective holes, following the order of the regions, as in the image or this list:

```
1. Crimea Autonomous Republic
2. Kherson Oblast
3. Zaporizhzhia Oblast
4. Donetsk Oblast
5. Luhansk Oblast
6. Kharkiv Oblast
7. Dnipropetrovsk Oblast
8. Mykolaiv Oblast
9. Odesa Oblast
10. Kirovohrad Oblast
11. Poltava Oblast
12. Sumy Oblast
13. Chernihiv Oblast
14. Kyiv Oblast
15. Cherkasy Oblast
16. Zhytomyr Oblast
17. Vinnytsia Oblast
18. Khmelnytskyi Oblast
19. Rivne Oblast
20. Volyn Oblast
21. Ternopil Oblast
22. Chernivtsi Oblast
23. Ivano-Frankivsk Oblast
24. Zakarpattia Oblast
25. Lviv Oblast
```

> **Tip:** To use a different order, simply change the const regions list in the code. Simply replace the entries.

3. Now glue the traslucent Regions and the ESP32 board in the back.

<img width="2566" height="1924" alt="image" src="https://github.com/user-attachments/assets/cf23af14-fe47-43cc-a30e-ccc943bdd9a3" />


### First power-on

The first time you turn the device on, it will create a Wifi AP, where you need to connect with another device (phone or laptop). After this, a web interface will appear, where you'll need to select and add your home WiFi network. Follow the instructions of the portal. 

After that, the device will connect automatically each time to your network and receive the latest air alert data every 10 seconds and light the regions.





## Planned upgrades

V1: An improvement, still designed as a wall decoration
- [ ] Migrate to PlatformIO
- [ ] Add settings to the captive portal
- [ ] Add light indication of issues (wifi disconnected, API error codes)
- [ ] Add brightness adjustment. Either Physical or mobile App
- [ ] Improve the 3D printed map.
  - [ ] Find a better SVG map
  - [ ] Add the cities of Kyiv and Sevastopol as their own regions
  - [ ] Add another LED to Odesa Oblast to make better lighting
  - [ ] Make it possible to assemble the map with screws or joints
- [ ] Google Home and Alexa integration
- [ ] OTA updates

V2: A smaller map with power from a Lipo battery for events:
- [ ] Research Microcontroller alternatives (STM32 + Wifi Module, ESP8266)
- [ ] Try out different LED configurations
  - [ ] Improve the light dissipation (light chamber, edge lighting, etc.)
  - [ ] Increase the amount of LEDs per province if needed
- [ ] PCB design to include:
  - [ ] Microcontroller
  - [ ] Battery charging circuit
  - [ ] OLED display for Settings and QR code for donations
  - [ ] Encoder
  - [ ] DC-DC 5V regulator circuit
- [ ] Redesign the 3D models to include battery and PCB

