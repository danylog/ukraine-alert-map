# ESP32 Ukraine Air Alert Map

This project uses an ESP32 development board and 25 WS2812B LEDs to display real-time air raid alerts for each region in Ukraine. Alert data is fetched from the [alerts.in.ua](https://alerts.in.ua) API.

The device is still in development; further upgrades will be added.

<img width="2566" height="1924" alt="image" src="https://github.com/user-attachments/assets/d5c81af3-9ea2-42e1-a451-2b4ca09acd7f" />


## Requirements

### Functional Requirements

#### Data & Connectivity
- [x] Fetch alert data from the alerts.in.ua API
- [x] Automatically connect to a configured WiFi network on startup
- [x] Provide a captive portal for initial WiFi configuration
- [ ] Add settings to the captive portal (brightness, update interval, etc.)
- [ ] Visual indication of connectivity issues (WiFi disconnected, API errors)
- [ ] Support OTA (over-the-air) firmware updates
- [ ] Google Home and Alexa integration

#### Display & Indication
- [x] Display real-time air raid alert status for all 25 regions of Ukraine
- [x] Indicate active alerts with distinct LED colors/effects per region
- [ ] Adjustable LED brightness (physical control or mobile app)
- [ ] Support for additional regions (Kyiv city, Sevastopol)
- [ ] Improved light dissipation per region

#### Hardware (V2 - Portable)
- [ ] Battery-powered operation with LiPo
- [ ] Battery charging circuit
- [ ] OLED display for settings and information
- [ ] Rotary encoder for physical controls
- [ ] Custom PCB design

### Non-Functional Requirements

#### Performance
- [x] Update alert status at least every 10 seconds
- [x] Operate continuously without manual intervention

#### Usability
- [x] Compact form factor for wall mounting or desk display
- [ ] Tool-less assembly (screws or snap-fit joints instead of glue)
- [ ] Improved 3D model based on better SVG source map

#### Maintainability
- [ ] Migrate codebase to PlatformIO
- [ ] Modular code structure for easy feature additions

#### Power
- [x] Low power consumption suitable for always-on USB operation
- [ ] Battery life optimization for portable version

## Setup Guide

### Code (Arduino IDE)

1. **Get an API key** by filling out [this form](https://alerts.in.ua/api-request). The instructions are in Ukrainian, but you can submit your request in English.

2. **Configure your credentials**: Create an `env.h` file in the `esp32code` folder and add your API key following the [example](env_example.h).

3. **Install the necessary libraries:**
   - [WiFi Manager](https://github.com/tzapu/WiFiManager)
   - [WS2812FX](https://github.com/kitesurfer1404/WS2812FX)

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

### 3D Printing

To make the casing, you will need two types of filament: an opaque one (I used black PLA) for the back and a translucent one (I used natural PETG) for the 25 regions. You can download all the files from my [Printables page](https://www.printables.com/model/1567498-esp32-ukraine-air-alert-map-v01)

### Assembly

<img width="2566" height="1924" alt="image" src="https://github.com/user-attachments/assets/e6e3bd48-f4a0-4485-955a-50fb2b1dfe94" />


1. Once you have the LEDs soldered and the casing printed, glue the opaque parts together to form the map of Ukraine. Two-component epoxy resin works best here.

2. Glue the LEDs into their respective holes, following the order of the regions as shown in the image or the list below:

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

> **Tip:** To use a different order, simply change the `regions` list in the code.

3. Glue the translucent regions and mount the ESP32 board on the back.

<img width="2566" height="1924" alt="image" src="https://github.com/user-attachments/assets/cf23af14-fe47-43cc-a30e-ccc943bdd9a3" />


### First Power-On

The first time you turn on the device, it will create a WiFi access point. Connect to it with another device (phone or laptop). A web interface will appear where you can select and add your home WiFi network. Follow the instructions in the portal.

After that, the device will automatically connect to your network each time and fetch the latest air alert data every 10 seconds to light up the regions.





## Planned Upgrades

### V1: Improved Wall Decoration
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

### V2: Portable Version with LiPo Battery
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

