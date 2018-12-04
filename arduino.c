#include <SPI.h> 
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
#include <dht.h> 
 
dht = DHT; 
 
#define DHT_PIN A0 
 
#define OLED_RESET 4 Adafruit_SSD1306 display(OLED_RESET); 
 
#define XPOS 0 #define YPOS 1 
 
#define DHT_POWER A1 
 
#define LOGO16_GLCD_HEIGHT 16  #define LOGO16_GLCD_WIDTH  16  
 
static const unsigned char PROGMEM logo16_glcd_bmp[] = { B11000011, B00000000,   B11000011, B00000000,   B11000011, B00000000,   B11111111, B00000000,   B11111111, B00000000,   B11000011, B00000000,   B11000011, B00000000,   B11000011, B00000000,   B00000000, B11111111,   B00000000, B11111111,   B00000000, B00011000,   B00000000, B00011000,   B00000000, B00011000,   B00000000, B00011000, 

 
  B00000000, B00011000,   B00000000, B00011000}; 
 
#if (SSD1306_LCDHEIGHT != 64) #error("Height incorrect, please fix Adafruit_SSD1306.h!"); #endif 
 
double dewpoint(double temp, double humidity)   //function calculates the dewpoint of the environment {   double satvapour = 6.112 * exp((17.67*temp)/(temp+243.5));   double vapourpressure = satvapour * (humidity / 100);   return log(vapourpressure/6.112)*243.5/(17.67-log(vapourpressure/6.112));  } 
 
double vapourpressure(double temp, double humidity)   //function calculates the vapourpressure of the environment {   double satvapour = 6.112 * exp((17.67*temp)/(temp+243.5));   return (satvapour * (humidity / 100));  } 
 
void showbvm() 
{   Serial.print("Mini-Weather Station");   
    display.print("Mini-Weather Station");   
    display.display();      
    display.setCursor(0,20);   
    Serial.print("   BVM Engineering");   
    display.print("   BVM Engineering");   
    display.display(); 
 
    display.setCursor(0,30);   Serial.print("        College");   display.print("        College");   display.display(); } 
 
void shownames() 
{   
    Serial.print("Mini-Weather Station");   
    display.print("Mini-Weather Station"); 

 
    display.display();      
    display.setCursor(0,20);   
    Serial.print("MADE BY : ");   
    display.print("MADE BY : ");   
    display.display(); 
 
    display.setCursor(0,30);   
    Serial.print("AAKASH BANIK");  
    display.print("AAKASH BANIK");   
    display.display(); 
 
    display.setCursor(0,40);   
    Serial.print("AYUSHI SHAH");   
    display.print("AYUSHI SHAH");   
    display.display(); } 
 
void show(double temp, double hum, double dew, double vap) 
{   
    Serial.print("Mini-Weather Station");   
    display.print("Mini-Weather Station");   
    display.display(); 
 
    display.setCursor(0,20);   
    Serial.print("Temperature : ");   
    display.print("Temperature : ");  
    display.display();      
    Serial.print(temp);   
    display.print(temp);   
    display.display(); 
 
    display.setCursor(0,30);   
    Serial.print("Humidity : ");   
    display.print("Humidity : ");   
    display.display(); 
 
    Serial.print(hum);   
    display.print(hum);   
    display.display(); 
 
    display.setCursor(0,40); 

 
    Serial.print("Vapor Pressure: ");   
    display.print("Vapor Pressure: ");   
    display.display(); 
 
    Serial.print(vap);   
    display.print(vap);   
    display.display(); 
 
    display.setCursor(0,50);   
    Serial.print("Dew Point : ");   
    display.print("Dew Point : ");   
    display.display(); 
 
    Serial.print(dew);   
    display.print(dew);   
    display.display(); 
 
    delay(5000); 
 
    display.clearDisplay();   
    display.setCursor(0,0); 
 
} 
 
 
void setup() { 
    Serial.begin(9600); 
 
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
    pinMode(DHT_POWER,HIGH); 
 
    display.display();  delay(2000);  display.clearDisplay(); 
 
    display.setTextSize(1);  
    display.setTextColor(WHITE);  
    display.setCursor(0,0); 
 
    showbvm();  
    delay(5000); 
 
    display.clearDisplay(); 

 
    display.setCursor(0,0);    
    shownames();  
    delay(5000); 
 
    display.clearDisplay();  
    display.setCursor(0,0);  
    delay(1000); 
} 
 
void loop() { 
 
  DHT.read11(DHT_PIN);             //Function which enables arduino to read data from the DHT sensor 
 
  double temperatureMain = DHT.temperature;   
  double humidityMain = DHT.humidity;   
  double dewpointMain = dewpoint(temperatureMain, humidityMain);   
  double vapourpressureMain = vapourpressure(temperatureMain, humidityMain); 
 
  show(temperatureMain, humidityMain, dewpointMain, vapourpressureMain);    
} 
