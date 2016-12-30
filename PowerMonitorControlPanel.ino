#include <SPI.h>
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define NUMCHANNELS 7

char labels[NUMCHANNELS][17]={
  "Basement A      ",
  "Basement B      ",
  "Basement C      ",
  "Air Conditioner ",
  "Chicken Coup    ",
  "Sump Pump A     ",
  "Sump Pump B     "
};

unsigned long LastUpdate = 0;
int SourceIndex = 0;

void setup() {
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0,0);
  lcd.print("Power Monitor   "); // print a startup message
}

void loop() {
  lcd.setCursor(0,1);            // move cursor to second line "1" and 9 spaces over
  lcd.print(millis()/1000);      // display seconds elapsed since power-up
  
  
  lcd.setCursor(0,1);            // move to the begining of the second line
  lcd_key = read_LCD_buttons();  // read the buttons
  
  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
    case btnRIGHT:
    {
      //lcd.setCursor(13,1); 
      //lcd.print("RIGHT ");
      break;
    }
    case btnLEFT:
    {
      //lcd.setCursor(0,1); 
      //lcd.print("LEFT   ");
      break;
    }
    case btnUP:
    {
      SourceIndex--;
      if(SourceIndex < 0) SourceIndex = NUMCHANNELS - 1;
      lcd.setCursor(0,0);
      lcd.print(labels[SourceIndex]);
      break;
    }
    case btnDOWN:
    {
      SourceIndex++;
      if (SourceIndex >= NUMCHANNELS) SourceIndex = 0;
      lcd.setCursor(0,0); 
      lcd.print(labels[SourceIndex]);
      break;
    }
    case btnSELECT:
    {
      //lcd.print("SELECT");
      break;
    }
    case btnNONE:
    {
      
      break;
    }
 }

}

void IncrementSourceIndex(){
}

int read_LCD_buttons()
{
  // read the buttons
  adc_key_in = analogRead(0);      // read the value from the sensor 
  while(analogRead(0) < 1000) delay(1);
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in < 250)  return btnUP; 
  if (adc_key_in < 400)  return btnDOWN; 
  if (adc_key_in < 600)  return btnLEFT; 
  if (adc_key_in < 850)  return btnSELECT;


 return btnNONE;  // when all others fail, return this...
}
