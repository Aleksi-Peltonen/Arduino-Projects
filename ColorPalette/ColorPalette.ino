#include <FastLED.h>
#define LED_PIN     10
#define BUTTON      3
#define NUM_LEDS    120
#define BRIGHTNESS  100
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
unsigned long previous_mills = 0;
unsigned long previous_debounce = 0;
short int brightness = 1;
short int interval = 10;
short int debounce = 30;
short int speedX = 1;
int buttonState = LOW;            
int lastButtonState = LOW;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    //Serial.begin(9600);
    
    //CHOOSE ONE DEMO PALETTE
    //currentPalette = RainbowColors_p;
    currentPalette = RainbowStripeColors_p;
    //currentPalette = CloudColors_p;
    //currentPalette = PartyColors_p;
    
    //CHOOSE EITHER BLEND MODE
    currentBlending = LINEARBLEND;
    //currentBlending = NOBLEND;  
}

void loop()
{

    static uint8_t startIndex = 0;
 
    //Read brightness every 10 ms to reduce flicker
    if(millis() - previous_mills >= interval){
        brightness = map(analogRead(0), 0, 1023, 1, 255);
        previous_mills = millis();
    }

    int reading = digitalRead(BUTTON);

     if (reading != lastButtonState) {
    // reset the debouncing timer
    previous_debounce = millis();
    }

     if ((millis() - previous_debounce) > debounce) {
    // Button has remained in the same state for the duration of debounce

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // Do something when the button is pressed
      if (buttonState == HIGH) {
        //Serial.println("BUTTON PRESSED");
        if (speedX < 6) 
          speedX++;
        else
          speedX = 1;        
        }
      }
    }

    lastButtonState = reading;
    
    //Serial.println(brightness);
    
    startIndex = startIndex + speedX; /* motion speed */

    
    FillLEDsFromPaletteColors(startIndex,brightness);
    //FillLEDsFromPaletteColors2(startIndex);
    
    FastLED.show();
    FastLED.delay(10);
    
}

void FillLEDsFromPaletteColors( uint8_t colorIndex, uint8_t brightness)
{  
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
/*
void FillLEDsFromPaletteColors2( uint8_t colorIndex2)
{  
    for( int i = 30; i < 60; i++) {
        leds[i] = ColorFromPalette( RainbowStripeColors_p, colorIndex2, BRIGHTNESS, currentBlending);
        colorIndex2 += 3;
    }
}
*/
