// Project 31 - Creating a Temperature History Monitor

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

 #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int tcurrent = 0;
int tempArray[120];

char currentString[3];

void getTemp() // function to read temperature from TMP36
{
  float sum = 0;
  float voltage = 0;
  float sensor = 0;
  float celsius;

  // read the temperature sensor and convert the result to degrees C
  sensor   = analogRead(5);
  voltage  = (sensor * 5000) / 1024;
  voltage  = voltage - 500;
  celsius  = voltage / 10;
  tcurrent = int(celsius);

  // insert the new temperature at the start of the array of past temperatures
  for (int a = 119 ; a >= 0 ; --a )
  {
    tempArray[a] = tempArray[a - 1];
  }
  tempArray[0] = tcurrent;
}

void drawScreen() // generate TFT LCD display effects
{
  int q;
  // display current temperature
  
  tft.setTextColor(ST77XX_BLUE); // blue text
  tft.setTextSize(2);
  tft.setCursor(20,0);
  tft.print("Current:");

  String tempString = String(tcurrent);
  tempString.toCharArray(currentString, 3);
  tft.setCursor(115,0);
  tft.print(currentString);
  // draw scale for graph
  tft.setTextSize(1);
  tft.setCursor(0,20);
  tft.print ("50");
  tft.setCursor(0,30);
  tft.print ("45");
  tft.setCursor(0,40);
  tft.print("40");
  tft.setCursor(0,50);
  tft.print("35");
  tft.setCursor(0,60);
  tft.print("30");
  tft.setCursor(0,70);
  tft.print("25");
  tft.setCursor(0,80);
  tft.print("20");
  tft.setCursor(0,90);
  tft.print("15");
  tft.setCursor(0,100);
  tft.print("10");
  tft.setCursor(0,110);
  tft.print("5");
  tft.setCursor(0,120);
  tft.print("0");

  tft.drawLine(20, 20, 20, 127,ST77XX_BLUE);
  // plot temperature data points
  for (int a = 25 ; a < 145 ; a++)
  {
    // convert the temperature value to a suitable y-axis position on the LCD
    q = (123 - (tempArray[a - 25] * 2));
    tft.drawPixel(a, q,ST77XX_BLUE);
  }
}

void setup()
{
  tft.init(240, 320);             // activate LCD
  tft.fillScreen(ST77XX_BLACK);
}

void loop()
{
  getTemp();
  drawScreen();
  for (int a = 0 ; a < 20 ; a++) // wait 20 minutes until the next reading
  {
    delay(60000);                // wait 1 minute
  }
}