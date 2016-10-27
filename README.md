# IA2 : SecureBox


Input Sensors:
1. Proximity Sensor
2. Flora Color Sensor

Output Sensor:
1. OLED display
2. NeoPixel Ring 24

Circuit:
2 resistors 470 Ohms
1 Photon
jumper cables
1 breadboard


Pin configuration: OLED
Photon            OLED
CS                A2
DC                D6
RST               D7
D1                A5
D0                A3
3V3               VCC
GND               GND

Pin configuration: FLORA Color Sensor
Photon            FLORA CCOLOR SENSOR
3V3               VCC
GND               GND
D1 ->resistor->  SDA
D2 ->resistor->  SCL

Pin Configuration: PROXIMITY Sensor
Photon            PROXIMITY Sensor
VIN               VCC
GND               GND
A0                data

Pin Configuration: NEO-PIXEL RING 24
Photon            NEO-PIXEL RING 24
D0                DATA IN
3V3               VCC
GND               GND

