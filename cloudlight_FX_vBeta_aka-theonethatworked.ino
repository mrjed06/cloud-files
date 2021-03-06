#include <Adafruit_NeoPixel.h>

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

//-----------Color Palette----------------------------
//255,80,20 fluorescent orange
//255, 147, 41 candle light
//255, 69, 0 soft orange
//250, 105, 30 My soft,warm
//-----------------------------------------------------

#include <SoftwareSerial.h>// import the serial library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6

SoftwareSerial ddawg(10, 11); // RX, TX
uint8_t BoardLed=13; // led on D13 will show blink on / off
String BluetoothData; // the data given from Computer

Adafruit_NeoPixel strip = Adafruit_NeoPixel(108, PIN, NEO_GRB + NEO_KHZ800);
//Global Variables
uint8_t r; //////////////////
uint8_t g;////Global RGB////
uint8_t b;//////////////////
uint8_t ro=150; uint8_t go=20; uint8_t bo=100;  //(yellowgreen 160,120,10) //(blue 25, 25, 112)
uint8_t rf=50; uint8_t gf=50; uint8_t bf=150;    //(purple 120,0,90)
short level; //brightness level

void setup() {
//BLUETOOTH SETUP
  ddawg.begin(9600);
  ddawg.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(BoardLed,OUTPUT);

//Serial Setup for Debuging
  Serial.begin(9600);

//RGB STRIP SETUP
  strip.begin();  
  strip.show(); // Initialize all pixels to 'off'
  r=255;g=255;b=255;///Set Global RGB


//Startup Sequence
  colorWipe(strip.Color(255, 255,255), .1); 
  colorWipe(strip.Color(0, 0,0), .1); 
  delay(500);

//Global Variable Defaults  
  setGlobalRGB (250, 150, 30); //Setup Starting Color (Custom RGB Ambient Light)
}

void loop() {
//STROBE();
if (ddawg.available()){
BluetoothData=ddawg.readString();
    if(BluetoothData=="ledon"){  
       Serial.println(BluetoothData); 
       ON();
    }
    
    if (BluetoothData=="ledoff"){
      Serial.println(BluetoothData);       
      OFF(); 
    }
    
    if (BluetoothData=="brighten"){
      Serial.println(BluetoothData);
      brighten();  
    }
    
    if (BluetoothData=="dim"){
      Serial.println(BluetoothData); 
      dim(); 
    }
    
    if (BluetoothData=="cloud1"){
      Serial.println(BluetoothData);
       ro=150; go=20; bo=100;  //Vibe Purple
       rf=50;  gf=50; bf=150;   //Vibe Blue
      crossFade(ro,go,bo,rf,gf,bf);
    }
    if(BluetoothData=="cloud2"){  //TIMBERWOLVES
       ro=0; go=144; bo=0;   //timberwolves green
       rf=1; gf=0; bf=132;   //timberwolves blue
       crossFade(ro,go,bo,rf,gf,bf);
    }
}

  
 //test = strip.Color(120,130,160);
  //Serial.println(test);
/*
if (ddawg.available()){
BluetoothData=ddawg.readString();
   if(BluetoothData=="111111"){   // if number 1 pressed ....
    Serial.println(BluetoothData); //when arduino detects command
    digitalWrite(BoardLed,1);
    ddawg.println("LED  On D13 ON ! ");
    brighten(2);
   }
  if (BluetoothData=="0"){// if number 0 pressed ....
    Serial.println(BluetoothData); //when arduino detects command
    digitalWrite(BoardLed,0);
    ddawg.println("LED  On D13 Off ! ");
    dim(2);
  }
}
delay(100);// prepare for next data ...
*/

//  ON();
//  OFF();
//  crossFade(ro,go,bo,rf,gf,bf); ///fade to this color
  //rainbowCycle(10);

  //Brighten and Dim Loop
  /*r=4,g=2;b=1;
  setStripColor(r,g,b);
  delay(2000);
  brighten(); //Brighten global RGB to max ensity
  delay(2000);
   brighten(); //Brighten global RGB to max ensity
  delay(2000);
   brighten(); //Brighten global RGB to max ensity
  delay(2000);
  brighten(); //Brighten global RGB to max ensity
  delay(2000);
   
  dim(); //Brighten global RGB to max ensity
  delay(2000);
   dim(); //Brighten global RGB to max ensity
  delay(2000);
   dim(); //Brighten global RGB to max ensity
  delay(2000);
  dim(); //Brighten global RGB to max ensity
  delay(2000);
  Serial.println("end");
  Serial.println(' ');
*/

  
  // Some example procedures showing how to display to the pixels. Test RGB and Full Intensity separately:
  //colorWipe(strip.Color(255, 0, 0), 3); // Red
  //colorWipe(strip.Color(0, 255, 0), 3); // Green
  //colorWipe(strip.Color(0, 0, 255), 3); // Blue
  //colorWipe(strip.Color(255, 244,229), 10); // Warm White Values
  
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127, 0, 0), 50); // Red
  //theaterChase(strip.Color(0, 0, 127), 50); // Blue

  //rainbow(20);
  //rainbowCycle(20);
  //theaterChaseRainbow(50);
}


//------------------------------------------My Functions----------------------------------------------
//Set a Global RGB values
void setGlobalRGB (uint8_t Ro, uint8_t Go, uint8_t Bo) {
  r=Ro;
  g=Go;
  b=Bo;
}

// Set the entire strip to one color
void setStripColor(uint8_t Ro, uint8_t Go, uint8_t Bo) {
 uint16_t i;
 for(i=0; i< strip.numPixels(); i++) {
          strip.setPixelColor(i, Ro, Go, Bo);
        }
        strip.show();
}


//----------CUSTOM PARAMETERS----------
uint16_t speedfade = 60;      // 10ms internal crossFade delay; increase for slower fades
boolean DEBUG = 0;      // DEBUG counter; if set to 1, will write values back via serial
uint16_t loopCount = 60; // How often should DEBUG report?
short CONTRAST=1020; //specifies how many crossfade (intermediate colors between first and second colors) are to be calculated
//-------------------------------------

//uint8_t ro=160; uint8_t go=120; uint8_t bo=10;
//uint8_t rf=120; uint8_t gf=0; uint8_t bf=90;
void crossFade(uint8_t Ro, uint8_t Go, uint8_t Bo, uint8_t Rf, uint8_t Gf, uint8_t Bf) { 
if (DEBUG){  // for debugging....flash initial and final color before displaying transition
  setStripColor(Ro,Go,Bo);delay(1000);
  setStripColor(Rf,Gf,Bf);delay(1000);
  setStripColor(0,0,0);delay(500);
}

uint8_t Rn[strip.numPixels()]; //Initialize RGB arrays that will store incremented RGB values
uint8_t Gn[strip.numPixels()]; 
uint8_t Bn[strip.numPixels()];
uint8_t Rmod[strip.numPixels()]; //Initialize RGB arrays that will modify the arrangement of values in the Rn, Gn, & Bn arrays...
uint8_t Gmod[strip.numPixels()]; //...so that the crossfade pattern can be seen more than once along the strip
uint8_t Bmod[strip.numPixels()];

short stepR = calculateStep(Ro, Rf); //values used to calculate each crossfade RGB color
short stepG = calculateStep(Go, Gf); 
short stepB = calculateStep(Bo, Bf);
uint16_t redVal=Ro; //value used to calculate each crossfade RGB color
uint16_t grnVal=Go;
uint16_t bluVal=Bo;

uint16_t n=0; //Crossfade color array index
uint32_t i=0; //Contrast resolution index
for (i = 0; i <= CONTRAST; i++) {
    redVal = calculateVal(stepR, redVal, i); //Calculate the next contrast value between crossfade colors
      if (abs(redVal-Ro)>abs(Rf-Ro)) {    //Also ensure that the rgb values do not pass their final values
        redVal = Rf;
        }
    grnVal = calculateVal(stepG, grnVal, i);                    
      if (abs(grnVal-Go)>abs(Gf-Go)){
        grnVal = Gf;
        }
    bluVal = calculateVal(stepB, bluVal, i);                   
      if (abs(bluVal-Bo)>abs(Bf-Bo)){
        bluVal = Bf;
        }

    if (DEBUG) { // Displays crossfade colors being calculated
      if (i == 0 or i % loopCount == 0) { 
        Serial.print("Loop/RGB: #");Serial.print(i);
        Serial.print(" | "); Serial.print(redVal);
        Serial.print(" / ");Serial.print(grnVal);
        Serial.print(" / ");  Serial.println(bluVal); 
      } 
      DEBUG += 1;
    }
    
    if (i*strip.numPixels()/CONTRAST >= n && n < strip.numPixels()){  //NOTE: the pixel count of the LED strip limits the number of intermediate
        Rn[n] = redVal;                                              //colors (between the initial and final color) that can be displayed.
        Gn[n] = grnVal;                                              // This "if" statement only display somes of the intermediate colors calculated 
        Bn[n] = bluVal;                                              //above (redVal, grenVal, and bluVal), because the Pixel Resolution is lower than
        n++;                                                         //the Contrast Resolution.
    }                 
}

for (n=0; n<strip.numPixels(); n++){ //create modified R G and B arrays with colors arranged in a particular way (C1 <-> C2 <-> C1)
  if (2*n<strip.numPixels()){
     Rmod[n]=Rn[2*n];
     Gmod[n]=Gn[2*n];
     Bmod[n]=Bn[2*n];
     }
  else{
     Rmod[n]=Rn[2*(strip.numPixels()-n)-1];
     Gmod[n]=Gn[2*(strip.numPixels()-n)-1];
     Bmod[n]=Bn[2*(strip.numPixels()-n)-1];
     }
}

for (n=0; n<strip.numPixels(); n++) { //DEBUGGING PURPOSES...DELETE
    strip.setPixelColor(n,Rmod[n],Gmod[n],Bmod[n]); //set each pixel to different color
}  
//strip.show();  //freeze the colors before moving...DEBUGING Purposes
//delay(3000);

      /////////INFINITE LOOP SECTION////////////////
      uint16_t m; //infinite loop index
      uint16_t k; //pixel number index
      uint16_t p; //Rn, Gn, & Bn index calculated from m and k
          for(m=1; m<=strip.numPixels();m++){
            if(m==108){                    //Causes Infinite Loop
              m=1;
              }
              for (k=1; k<=strip.numPixels(); k++) {//loop index that points to crossfade values
                p=k+m-2;        //start at position 0 and index p to 107
                if(p>=strip.numPixels()){ //if p tries to point to a position outside of the Rn Gn & Bn arrays... 
                  p=p-strip.numPixels();  //...make p point back to the beginning of the array.
                }
                  strip.setPixelColor(strip.numPixels()-k,Rmod[p],Gmod[p],Bmod[p]); //set each pixel to different color
                     
                  if (ddawg.available()){                               //RETURN TO VOID LOOP
                    BluetoothData=ddawg.readString();
                    Serial.println(BluetoothData);
                    if(BluetoothData=="cloudoff" || BluetoothData=="ledoff"){ 
                    OFF();  
                    return;
                    }
                  }
              }
              strip.show();  
              delay(speedfade);   
          } 
       ///////////////////////////////////   
}
            short calculateStep(short prevValue, short endValue) {
              short step = endValue - prevValue; // What's the overall gap?
              if (step) {                      // If its non-zero, 
                step = CONTRAST/step;              //   divide by 1020
              } 
              return step;
            }
            
            short calculateVal(short step, short val, short i) {
                if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
                  if (step > 0) {              //   increment the value if step is positive...
                    val += 1;           
                  } 
                  else if (step < 0) {         //   ...or decrement it if step is negative
                    val -= 1;
                  } 
                }
                // make sure val stays in the range 0-255
                if (val > 255) {
                  val = 255;
                } 
                else if (val < 0) {
                  val = 0;
                }
                return val;
              }



//Find Maximum of 3 RGB values
uint16_t maxRGB(uint16_t Ro, uint16_t Go, uint16_t Bo)
{
  uint16_t maxguess;

  maxguess = max(Ro,Go);  // biggest of A and B
  maxguess = max(maxguess, Bo);  // but maybe C is bigger?

  return(maxguess);
}


//Incrementally brighten the global RGB values
//----------CUSTOM PARAMETERS----------
uint16_t speed_brighten=2; //transition speed
uint8_t level2=150; //light brightness level 0-255
//-------------------------------------
void brighten() {
      Serial.println("start rgb");
      Serial.println(r);
      Serial.println(g);
      Serial.println(b);
      Serial.println(' ');

    while(level!=level2){
      setStripColor(r*level/255, g*level/255, b*level/255);
      if (level>level2){
        level--;
      }
      else if (level<level2){
        level++;
      }
      delay(speed_brighten);
    }   
      Serial.println("final rgb");
      Serial.println(r);
      Serial.println(g);
      Serial.println(b);
      Serial.println(' ');                      
}


//Turn global RGB values to max intensity
//----------CUSTOM PARAMETERS----------
uint16_t speed_ON=5; //transition speed
//-------------------------------------
void ON() {
  while(level<=255){
   setStripColor(r*level/255, g*level/255, b*level/255);
   level++;
   delay(speed_ON);
  } 
            
            //setStripColor(0,0,0);
              //  delay(100);
            //setStripColor(r, g, b);
             //   delay(100); //DELETE WHEN DONE TESTING           
}


//Incrementally dim the global RGB values
//----------CUSTOM PARAMETERS----------
uint16_t speed_dim=2;//transition speed
uint8_t level1=50; //light brightness level 0-255

void dim() {
      Serial.println("start rgb");
      Serial.println(r);
      Serial.println(g);
      Serial.println(b);
      Serial.println(' ');
  
    while(level!=level1){
      setStripColor(r*level/255, g*level/255, b*level/255);
      if (level>level1){
        level--;
      }
      else if (level<level1){
        level++;
      }
      delay(speed_dim);
    }   
      Serial.println("final rgb");
      Serial.println(r);
      Serial.println(g);
      Serial.println(b);
      Serial.println(' ');                       
}



//Turn global RGB values off
//----------CUSTOM PARAMETERS----------
uint16_t speed_OFF=.01; //transition speed
//-------------------------------------

void OFF() {
 if (level<=0){
   setStripColor(0,0,0);
 }
 while(level>=0){
   setStripColor(r*level/255, g*level/255, b*level/255);
   level--;
   delay(speed_OFF);
 }           
}

//Strobe light function
//---------Custom Parameters----------
uint16_t speed_STROBE=200; //speed of strobe light
//------------------------------------

void STROBE() {
 setStripColor(200,200,200);
 delay(speed_STROBE);
 setStripColor(0,0,0);
 delay(speed_STROBE);
 
 if (ddawg.available()){                               //RETURN TO VOID LOOP
    BluetoothData=ddawg.readString();
    Serial.println(BluetoothData);
   if(BluetoothData=="cloudoff" || BluetoothData=="ledoff"){ 
    OFF();  
    return;
   }
 }
}

//-------------------------------STOCK FUNCTIONS--------------------------------------
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

