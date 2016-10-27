// This #include statement was automatically added by the Particle IDE.
#include "SparkFunMicroOLED/SparkFunMicroOLED.h"

// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_TCS34725/Adafruit_TCS34725.h"
#include <math.h>

// This #include statement was automatically added by the Particle IDE.
#include "neopixel/neopixel.h"


//Below are the variables defined to be used for NeoPixel ring
#define NO_OF_PIXELS 24
#define PIXEL_PIN D2
#define PIXEL_TYPE WS2812B //NEO_GRB + NEO_KHZ800


//Below are the variables used for flora color sensor TCS34725
boolean commonAnode = false;
char szInfo[128];


#define PIN A0
int i=0;


//Below is a statement that would allot values to the variable strip which is of type Adafruit_neopixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NO_OF_PIXELS, PIXEL_PIN, PIXEL_TYPE);


//Below is a statement that would allot values to the variable tcs which is of type Adafruit_TCS34725
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


//below is a commans to initialize OLED
MicroOLED oled;


void setup() {
//setup for led on D7
//setup for neopixel sensor
    strip.begin();
	strip.setBrightness(5);
	strip.show();
	pinMode (PIN, INPUT);
	
	
//setup for flora color sensor
    Serial.begin(9600);
    Serial.println("\nColor View Test!");
    
    //initializing sensor and checking for errors
    if (tcs.begin()) {
        Serial.println("Found sensor");
    } else {
        Serial.println("No TCS34725 found ... check your connections");
        while (1); // halt!
    }
    
//setup for OLED
    // Initialize the OLED
    oled.begin();
    oled.clear(ALL); // Clear the display's internal memory
    oled.display();  // Display what's in the buffer (splashscreen)
    delay(1000);     // Delay 1000 ms
    oled.clear(PAGE); // Clear the buffer.
    randomSeed(analogRead(A0) + analogRead(A1));
    Serial.println("OLED Initialized");

//subscribe function setup
    if(!Particle.subscribe("colorinfo", myHandler))
    {
        Serial.println("Error Subscribing");
        while(1);
    }
    else
    {
        Serial.println("Subscribed to the local event: colorinfo");
    }
}

//handler function, this function takes care of the data recieved from the cloud.
void myHandler(const char *event, const char *data)
{
//initialize variables. RGS color variables and counter in order to seperate values.
    int red, green, blue, counter= 0;
//char array created in order to copy data from const data arg in order to manipulate data
    char data1[11];
//copy data to estination from source
    strcpy(data1, data);
//char pointer created in order to store result from tokenizer function
    char *pch;
//data recieved from token function saves in above char pointer.
    pch = strtok (data1,":");
//seperate RGB values
    while (pch != NULL)
    {
        if(counter==0)
        {
            red= atoi(pch);
            counter++;
        }
        else if(counter==1)
        {
            green= atoi(pch);
            counter++;
        }
        else if(counter==2)
        {
            blue= atoi(pch);
            counter++;
        }
        pch = strtok (NULL, ":");
    }
//check if the value is acceptable
    if(red>15 && red<30 && green>85 && green<100 && blue>115 && blue<130)
    {
        Serial.println("OPEN");
        ring(red, green, blue);
        printOnOLED("OPEN!", 2);
        delay(1000);
    }    
    else 
    {
        Serial.println("\nREMAINS CLOSED: ");
        printOnOLED("TRY\nAGAIN", 1);
        pulse(red, green, blue);
        delay(500);
        resetNeo();
    }

}


void loop() {
    uint16_t clear, red, green, blue;
//    char OLEDinfo[20];
	uint16_t value = analogRead(PIN);

	if(value>2500)  
    {
        delay(500);
        tcs.setInterrupt(false);
        delay(100);
        tcs.getRawData(&red, &green, &blue, &clear);
        tcs.setInterrupt(true);

        int re= getRGB(red, clear);
        int gr= getRGB(green, clear);
        int bl= getRGB(blue, clear);
        
        sprintf(szInfo, "%d:%d:%d", re, gr, bl);
    
        Serial.print("\nSERIAL: ");
        Serial.println(szInfo);
        
        Particle.publish("colorinfo", szInfo);
    }
}

//convert input values into usable RGB values
int getRGB( uint32_t color,  uint32_t clear)
{
    float tempColor= 0.0;
    if(clear>10)
    {
        tempColor = ((float)color)/clear;
    }
    return (int)(tempColor*255);
        
}

//works when input values are rejected.
void pulse(int red, int green, int blue)
{
    for(int j=0; j<strip.numPixels(); j++)
    {
        strip.setPixelColor(j, 255, 0, 0);
    }
    strip.show();
    for(int i=1; i<100; i++)
    {
        strip.setBrightness(i);
        strip.show();
        delay(5);
    }
    for(int j=0; j<strip.numPixels(); j++)
    {
        strip.setPixelColor(j, red, green, blue);
    }
    strip.show();
    delay(500);
    for(int j=0; j<strip.numPixels(); j++)
    {
        strip.setPixelColor(j, 255, 0, 0);
    }
    strip.show();
    for(int i=100; i<1; i--)
    {
        strip.setBrightness(i);
        strip.show();
        delay(5);
    }
}

//reset the whole neopixel	
void resetNeo()
{
	for(int i=0; i<strip.numPixels(); i++)
	{
	    strip.setPixelColor(i ,0, 0, 0);
	}
	strip.show();
	delay(100);
}

//display data on OLED display
void printOnOLED(String title, int font)
{
  oled.clear(PAGE);
  oled.setFontType(font);
  // Try to set the cursor in the middle of the screen
  oled.setCursor(0, 0);
  // Print the title:
  oled.print(title);
  oled.display();
  delay(1000);
  oled.clear(PAGE);
} 


//flash the intended color    
void ring(int re, int gr, int bl)
{
    for(int i=1; i<strip.numPixels(); i++)
	{
	    strip.setPixelColor(i ,strip.Color( re,gr, bl));
    	strip.show();
		delay(100);
	}
	resetNeo();
}
