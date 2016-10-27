# IA2 : SecureBox
CIRCUIT: ![20161027_132335](https://cloud.githubusercontent.com/assets/4143545/19778041/f868fed2-9c48-11e6-92ea-64fe52787a9e.jpg)


LIBRARIES USED:
1. ADAFRUIT_TCS24725
2. NEOPIXEL
3. SPARKFUNMICROOLED

Input Sensors --> type of values:
1. Proximity Sensor --> int 
2. Flora Color Sensor --> RGB (int)

Output Sensor --> type of values:
1. OLED display --> string
2. NeoPixel Ring 24 --> RGB (int)

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

WORKING:
PART I
        The PRIXIMITY SENSOR is triggered if the value recieved is more than 3000. This in turn triggers the FLORA COLOR SENSOR to take a reading which gives the photon RGB vales of the objectthat is held close ot the SENSOR.
        These RGB values thus gained through the FLORA sensor are converted into a string seperated by colons and then published using the PARTICLE.PUBLISH(). THIs uploads the string containing RGB values on the PARTICLE CLOUD. .
        The Data is then fetched using JS and then converted into respective RGB values in int which are then used to display them on the webpage.
         If the color from the object is accepted as the code, THE OLED display isplays OPENE on the display. If not then it would ask the user to TRY AGAIN.
PART II
        The DATA is then fetched from the PARTICLE CLOUD using PARTICLE.SUBSCRIBE(). This data is then again converted into int RGB values and then sent to the NEOPIXEL for output visualization.
  
