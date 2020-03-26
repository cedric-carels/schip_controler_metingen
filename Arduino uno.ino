
#include <Adafruit_GFX.h>         //Bibliotheken voor de OLED en BMP280
#include <Adafruit_SSD1306.h>     //Bibliotheken voor OLED
#include <Adafruit_BMP280.h>      //Bibliotheken voor BMP280
#define SCREEN_WIDTH 128          // OLED schermbreedte, in pixels
#define SCREEN_HEIGHT 32          // OLED schermhoogte, in pixels
#define OLED_RESET    -1          // Reset pin # (of -1 als je Arduino reset pin deelt)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declareren van de weergavenaa(display)
Adafruit_BMP280 bmp;              //voor fout melding te kunnen geven

int led_wit = 2;
int led_blauw = 3;
int led_geel = 4;
int led_groen = 5;
int led_rood = 6;

int button_wit = 8;
int button_blauw = 9;
int button_geel = 10;

int ledState_wit =LOW;
int ledState_blauw =LOW;
int ledState_geel =LOW;
int ledState_groen =LOW;
int ledState_rood =LOW;

int buttonCurrent_wit;
int buttonPrevious_wit = LOW;
int buttonCurrent_blauw;
int buttonPrevious_blauw = LOW;
int buttonCurrent_geel;
int buttonPrevious_geel = LOW;

void setup() {
bmp.begin();                                   //Start de bmp
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);     //Start the OLED scherm
display.clearDisplay();                        //reset scherm
display.display();                             //dat scherm aan staat
display.setTextColor(WHITE);                   //kleur van tekst
display.setCursor(32,10);                      //(kolom,rij)kolom kan van 0 tot 128 en rij kan van 0 tot 32
display.setTextSize(1);                        //de hoogte tekst kan van 1 tot 8
display.print("Welke keuze");                  //toon de text
display.setCursor(32,20);                      //(kolom,rij)kolom kan van 0 tot 128 en rij kan van 0 tot 32
display.setTextSize(1);                        //de hoogte tekst kan van 1 tot 8
display.print("wil je?");                      //de println zeg volgende lijn afprinten
display.display();                             //reset het scherm

pinMode(led_wit, OUTPUT);                      //dat led uitgang is
pinMode(led_blauw, OUTPUT);                    //dat led uitgang is
pinMode(led_geel, OUTPUT);                     //dat led uitgang is
pinMode(led_groen, OUTPUT);                    //dat led uitgang is
pinMode(led_rood, OUTPUT);                     //dat led uitgang is

pinMode(button_wit, INPUT);                    //dat drukknop ingang is
pinMode(button_blauw, INPUT);                  //dat drukknop ingang is
pinMode(button_geel, INPUT);                   //dat drukknop ingang is
}
void loop() {
  ledState_groen = HIGH;                      //groene led aan gaat
  
  display.clearDisplay();
  float T = bmp.readTemperature();            //Lees temperatuur in °C
  float P = bmp.readPressure()/100;           //Lees druk in Pa en conversie naar hPa
  float A = bmp.readAltitude(1019.66);        //Bij het bereken van de hoogte is de "1019.66" de druk in (hPa) op zeeniveau
   
  buttonCurrent_wit =digitalRead(button_wit);
  buttonCurrent_blauw =digitalRead(button_blauw);
  buttonCurrent_geel =digitalRead(button_geel);


  
  if (!bmp.begin())
  {   display.setCursor(0,0);
      display.setTextColor(WHITE);
      display.setCursor(16,10);
      display.setTextSize(1);
      display.print("Opgepast!");
      display.setCursor(16,20);
      display.setTextSize(1);          
      display.print("foute aansluiting!");
      display.display();
      ledState_rood = HIGH;
      ledState_groen = LOW;
      ledState_wit = LOW;
      ledState_blauw = LOW;
      ledState_geel = LOW;
      buttonCurrent_wit = LOW;
      buttonCurrent_blauw = LOW;
      buttonCurrent_geel = LOW;
  }
  if (buttonCurrent_wit == HIGH && buttonPrevious_wit == LOW)
  {
      display.setCursor(0,0);
      display.setTextColor(WHITE);
      display.setTextSize(2); 
      display.print("Hoogte");
      display.setCursor(0,18);
      display.print(A,1);
      display.setCursor(50,17);
      display.setTextSize(1);
      display.print("m");
      display.setCursor(65,23);
      display.display();
    if (ledState_geel == HIGH)
    {
      ledState_geel = LOW;
    }
    else
    {ledState_wit = HIGH;
     ledState_blauw = LOW;
     ledState_geel = LOW;
    }
  }
  if (buttonCurrent_blauw == HIGH && buttonPrevious_blauw == LOW)
  {   display.setCursor(0,0);
      display.setTextColor(WHITE);
      display.setTextSize(2); 
      display.print("Druk");
      display.setCursor(0,18);
      display.print(P,1);
      display.setCursor(56,17);
      display.setTextSize(1);
      display.print("   hPa");
      display.setCursor(65,23);
      display.display();
    if (ledState_blauw == HIGH)
    {
      ledState_blauw = LOW;
    }
    else
    {ledState_wit = LOW;
     ledState_blauw = HIGH;
     ledState_geel = LOW;
    }
  }
  if (buttonCurrent_geel == HIGH && buttonPrevious_geel == LOW)
  {   display.setCursor(0,0);
      display.setTextColor(WHITE);
      display.setTextSize(2); 
      display.print("Temp");
      display.setCursor(0,18);
      display.print(T,1);
      display.setCursor(50,17);
      display.setTextSize(1);
      display.print("C");
      display.setCursor(65,23);
      display.display();
    if (ledState_geel == HIGH)
    {
      ledState_geel = LOW;
    }
    else
    {ledState_wit = LOW;
     ledState_blauw = LOW;
     ledState_geel = HIGH;
    }
  }

digitalWrite(led_wit, ledState_wit);
digitalWrite(led_blauw, ledState_blauw);
digitalWrite(led_geel, ledState_geel);
digitalWrite(led_groen, ledState_groen);
digitalWrite(led_rood, ledState_rood);
}
