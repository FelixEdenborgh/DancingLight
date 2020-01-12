#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN 10  //6
#define trig_PIN 9 //13
#define echo_PIN 8 //12
#define NUMPIXELS 350 // Popular NeoPixel 

long randomNumber;
byte rand1, rand2 , rand3;

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50


void setup() {
  Serial.begin(9600);
  pinMode(echo_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(trig_PIN, OUTPUT);
  
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  pixels.begin(); 
  randomSeed(analogRead(0));
  

}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  long duration, distance;
  digitalWrite(trig_PIN, LOW);
  delay(2);
  digitalWrite(trig_PIN, HIGH);
  delay(10);
  digitalWrite(trig_PIN, LOW);

  duration = pulseIn(echo_PIN, HIGH);
  distance = (duration/2) /29.1;

  randomNumber = random(255);
  rand1 = random(0, 255);
  rand2 = random(75, 255);
  rand3 = random(150, 255);


  if(distance > 15){
    for(int i=0; i<NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(rand1, rand2, rand3));
      pixels.show();
    }
  }
  else{
    for(int i=0; i<NUMPIXELS; i++) {
       pixels.setPixelColor(i, pixels.Color(0, 0, 0));
       pixels.show();
    }
  }
  Serial.print(distance);
  Serial.println("CM");

  delay(DELAYVAL);
}
