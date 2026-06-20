<h1 align="center">StarField WX</h1>

<img width="1410" height="2000" alt="starfield" src="https://github.com/user-attachments/assets/0497373b-94ad-4294-acd0-bd4dcab92ebc" />


<p align="center">
<i>Portable Arduino‑powered dew‑risk weather station with LCD and LED halo.</i>
</p>



---

##  1. What is STARFIELD WX?

<p>
Starfield WX is a pocket-sized weather station that tells you when dew is about to become a problem for stargazing/ astrophotography.
</p>

---

##  2. Why did I make it?

<p>
I Love being outside with my telescope, but because of where I live, I always end up with dew messing up my session before I could photograph anything. Starfield WX is my companion project for ORBTIZ. it can warn you about dew forming before it ruins your session.

---

##  3. How does it work?

<p>
The brains of the operation is the arduino uno. 
    It:
Reads temperature and humidity from a DHT11 module.
Calculates an approximate dew point from those readings.
Classifies dew risk (LOW, MEDIUM, HIGH) based on the spread between temperature and dew point.
Shows live values on a 16×2 character LCD while auto‑cycling between temperature, humidity, and dew‑point screens.
Uses a WS2812B LED halo as a status ring: green for low risk, orange for medium, red when dew is imminent.

</p>

---

##  4.Hardware schematic

<p>
You can view the full schematic for the ORBITZ PCB below.
  

The custom STARFIELD pcb plugs directly onto an Arduino Uno and breaks out all parts needed for weather station

key pins:
DHT11 data -> Arduino digital pin 2
WS2812B LED strip -> Arduino digital pin 6
1602 LCD (parallel) -> Arduino digital pins 7–12
Trimmer potentiometer -> LCD contrast
Series resistors for the LCD backlight and LED strip data line

you can view the full schematic here.
![STARFIELD schematic](hardware/starfield_schem.svg)

</p>

---

##  5. How do you use it?

<p>

</p>

Assembly:
Power on the arduino uno via USB or a **5v** supply ( you can also power it using the usb hub on orbitz!!)
StarField WX boots, then starts cycling through three screens on the LCD:
  - Temperature in C
  - Relative humiditry in %
  - Dew point in C
The led halo color shows dew risk : green (low), orange ( medium), red (high)
when it turns red, conditions are close to the dew point and you should protect your optics or wrap up the session , unfortunately :( 


## ASSEMBLED DESIGN 
Below is what your fully assembled design should look like.

order all parts from the Starfield BOM
solder headers, resistors, the DHT11 module connector, LCD header, LED strip header to the PCB
Mounts the potentiometer and adjust until the LCD text is clearly visible 
Attach the 1602 LCD to the enclosure using standoffs
cut the WS2812B strip to length and mount it around the inside top of the enclosure, then wire it 5v, GND , and the data pin
Insert the arduino UNO under the shield and secure the PCB in the 3d printed enclosure.
upload the code and enjoy!


![STARFIELD enclosure interior](hardware/STARFIELD_ASSEMBLED.png)  

---

## 6. Firmware
The firmware is a single Arduino sketch that runs on the Uno
Features:
  Periodically reads DHT11 temperature and humidity
  computes dew point using a simple approximation formula
  cycle LCD screens every few seconds (temperature, humidty, dew point)
  computes dew risk catergory and updates the LED halo color

how to flash
1. open firmware/starfield_wx.ino in the arduino uno
2. select arduino uno as the board and choose the correct serial port
3. click upload
4. after reseting, the splash screen appears, then live readings start
Feel free to tweak the threshold and LED colors to match your local climate and conditions

##  7. Images

<table>
  <tr>
    <td align="center">
      <strong>FINAL PCB SCREENSHOTS</strong><br><br>
      <img width="400" alt="FINAL PCB SCREENSHOTS"
      src="https://github.com/user-attachments/assets/7b5fe4da-4521-4e2a-a171-5e88641a7de7" />
  </tr>
  <tr>
    <td align="center">
      <strong>PCB</strong><br><br>
      <img width="400" alt="PCB"
        src="https://github.com/user-attachments/assets/2214754b-7cf8-4715-8803-0e71fc0c60cc" />
    </td>
  </tr>
  <tr>
    <td align="center">
      <strong>FINAL BUILD</strong><br><br>
      <img width="300" alt="FINAL BUILD"
        src="https://github.com/user-attachments/assets/9e2097c5-6bb4-4d4d-ba1c-d7aec5207ba7" />

  </tr>
</table>

##  8. Bill of Materials (BOM)

The full detailed BOM is included in this repository:

- [[`/STARFIELD_BILL_OF_MATERIALS.csv`](https://github.com/marvyluvu/Starfield-WX/blob/69a2b140c6205f69048c935fe2e7507fc950f91d/hardware/STARFIELD_BOM.csv)

You can open this file in Excel, Google Sheets, or any spreadsheet tool.
It includes part names, descriptions, quantities, prices, and direct purchase links.

Key components

| Product name          | Description                                 | Qty |
| --------------------- | ------------------------------------------- | --- |
| Arduino Uno           | Main microcontroller board                  | 1   |
| STARFIELD custom PCB  | Shield that holds all weather‑station parts | 1   |
| DHT11 module          | Temperature and humidity sensor             | 1   |
| 1602A LCD display     | 16×2 character display for readings         | 1   |
| WS2812B LED strip     | RGB halo to show dew‑risk color             | 1   |
| Trimmer potentiometer | Adjusts LCD contrast                        | 1   |
