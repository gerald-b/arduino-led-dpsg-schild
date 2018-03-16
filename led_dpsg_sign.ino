#include <Adafruit_NeoPixel.h>
//#include <cmath>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NEOPIN         3
#define NUMPIXELS      16

// ********************
// * Variables
// ********************
boolean const debug = false;
int ND_MT = 9;
int ND_MM = 8;
int ND_MB = 5;
int ND_LT = 7;
int ND_LB = 6;
int ND_RT = 10;
int ND_RB = 11;
int ND_DOT = 12;
int TASTER = 4;
int mode = 1;
int mode2ArrCount = 0;
uint32_t mode2Arr[5];

uint32_t cOrange = 0;
uint32_t cBlue = 0;
uint32_t cGreen = 0;
uint32_t cRed = 0;
uint32_t cYellow = 0;
uint32_t cBlack = 0;
uint32_t cWhite = 0;


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

// ********************
// Forward declarations
// ********************
void mode1Run();
uint32_t Wheel(byte WheelPos);
boolean readKey();
void reset();
void nummer_0();
void nummer_1();
void nummer_2();
void nummer_3();
void nummer_4();
void nummer_5();
void nummer_6();
void nummer_7();
void nummer_8();
void nummer_9();
void modeSetColor(uint32_t c);

// ********************
// * Setup
// ********************
void setup() {
  pinMode(ND_MT, OUTPUT);
  pinMode(ND_MM, OUTPUT);
  pinMode(ND_MB, OUTPUT);
  pinMode(ND_LT, OUTPUT);
  pinMode(ND_LB, OUTPUT);
  pinMode(ND_RT, OUTPUT);
  pinMode(ND_RB, OUTPUT);
  pinMode(ND_DOT, OUTPUT);
  pinMode(TASTER,INPUT);
  reset();
  if (debug) { Serial.begin(9600); }
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show();
  pixels.setBrightness(64);
  
  cOrange = pixels.Color(255,88,0);
  cBlue   = pixels.Color(0,0,255);
  cGreen  = pixels.Color(0,255,0);
  cRed    = pixels.Color(255,0,0);
  cYellow = pixels.Color(255,255,0);
  cBlack  = pixels.Color(0,0,0);
  cWhite  = pixels.Color(255,255,255);
  
  mode2Arr[0] = cOrange;
  mode2Arr[1] = cBlue;
  mode2Arr[2] = cGreen;
  mode2Arr[3] = cRed;
  mode2Arr[4] = cYellow;
  
  mode = 1;
  nummer_1();
}

// ********************
// * Loop
// ********************
void loop() {
  readKey();
  switch(mode)
  {
    case 0:
      modeSetColor(cBlack);
      break;
    case 1:
      mode1Run();
      break;
    case 2:
      mode2ArrCount = mode2ArrCount>=5 ? 0 : mode2ArrCount;
      for(int i=0; i<19; i++)
      {
        modeSetColor(mode2Arr[mode2ArrCount]);
        delay(250);
        if (readKey()) { break; }
      }      
      mode2ArrCount++;
      break;
    case 3:
      modeSetColor(cOrange);
      break;
    case 4:
      modeSetColor(cBlue);
      break;
    case 5:
      modeSetColor(cGreen);
      break;
    case 6:
      modeSetColor(cRed);
      break;
    case 7:
      modeSetColor(cYellow);
      break;
    case 8:
      modeSetColor(cWhite);
      break;
    case 9:
      for(uint16_t j=0; j<256; j++) {
        for(uint16_t i=0; i<pixels.numPixels(); i++) {
          pixels.setPixelColor(i, Wheel((i+j) & 255));
        }
        if (readKey()) { break; }
        pixels.show();
        delay(100);
      }
      break;
    default:
      break;
  }
}

void mode1Run()
{
  // Orange
  for(int i=0; i<255; i=i+2)
  {
     modeSetColor(pixels.Color(i, round(((float)i)*88/255.0f),0));
     if (readKey()) { return; }
     delay(25);
  }
  for(int i=0; i<19; i++)
  {
    modeSetColor(cOrange);
    delay(250);
    if (readKey()) { return; }
  }
  for(int i=255; i>0; i=i-2)
  {
     modeSetColor(pixels.Color(i, round(((float)i)*88/255.0f),0));
     if (readKey()) { return; }
     delay(25);
  }
  
  // Blue
  for(int i=0; i<255; i=i+2)
  {
     modeSetColor(pixels.Color(0,0,i));
     if (readKey()) { return; }
     delay(25);
  }
  for(int i=0; i<19; i++)
  {
    modeSetColor(cBlue);
    delay(250);
    if (readKey()) { return; }
  }
  for(int i=255; i>0; i=i-2)
  {
     modeSetColor(pixels.Color(0,0,i));
     if (readKey()) { return; }
     delay(25);
  }
  
  // Green
  for(int i=0; i<255; i=i+2)
  {
     modeSetColor(pixels.Color(0,i,0));
     if (readKey()) { return; }
     delay(25);
  }
  for(int i=0; i<19; i++)
  {
    modeSetColor(cGreen);
    delay(250);
    if (readKey()) { return; }
  }
  for(int i=255; i>0; i=i-2)
  {
     modeSetColor(pixels.Color(0,i,0));
     if (readKey()) { return; }
     delay(25);
  }
  
  // Red
  for(int i=0; i<255; i=i+2)
  {
     modeSetColor(pixels.Color(i,0,0));
     if (readKey()) { return; }
     delay(25);
  }
  for(int i=0; i<19; i++)
  {
    modeSetColor(cRed);
    delay(250);
    if (readKey()) { return; }
  }
  for(int i=255; i>0; i=i-2)
  {
     modeSetColor(pixels.Color(i,0,0));
     if (readKey()) { return; }
     delay(25);
  }
  
  // Yellow
  for(int i=0; i<255; i=i+2)
  {
     modeSetColor(pixels.Color(i,i,0));
     if (readKey()) { return; }
     delay(25);
  }
  for(int i=0; i<19; i++)
  {
    modeSetColor(cYellow);
    delay(250);
    if (readKey()) { return; }
  }
  for(int i=255; i>0; i=i-2)
  {
     modeSetColor(pixels.Color(i,i,0));
     if (readKey()) { return; }
     delay(25);
  }
  
  for(int i=0; i<100; i++)
  { 
    modeSetColor(cBlack);
    if (readKey()) { return; }
    delay(25);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

boolean readKey()
{
  int tmpRead = digitalRead(TASTER);
  if (debug) { Serial.println(tmpRead); }
  if (1 == tmpRead)
  {
    mode++;
    mode = mode > 9 ? 0 : mode;
    reset();
    switch(mode)
    {
      case 0:
        nummer_0();
        break;
      case 1:
        nummer_1();
        break;
      case 2:
        nummer_2();
        break;
      case 3:
        nummer_3();
        break;
      case 4:
        nummer_4();
        break;
      case 5:
        nummer_5();
        break;
      case 6:
        nummer_6();
        break;
      case 7:
        nummer_7();
        break;
      case 8:
        nummer_8();
        break;
      case 9:
        nummer_9();
        break;
      default:
        break;
    }
    delay(400);
    return true;
  }
  return false;
}

void reset()
{
  digitalWrite(ND_MT, HIGH);
  digitalWrite(ND_MM, HIGH);
  digitalWrite(ND_MB, HIGH);
  digitalWrite(ND_LT, HIGH);
  digitalWrite(ND_LB, HIGH);
  digitalWrite(ND_RT, HIGH);
  digitalWrite(ND_RB, HIGH);
  digitalWrite(ND_DOT, LOW);
}

void nummer_0()
{
  digitalWrite(ND_RT, LOW);
  digitalWrite(ND_RB, LOW);
  digitalWrite(ND_LT, LOW);
  digitalWrite(ND_LB, LOW);
  digitalWrite(ND_MT, LOW);
  digitalWrite(ND_MB, LOW);
}

void nummer_1()
{
  digitalWrite(ND_RT, LOW);
  digitalWrite(ND_RB, LOW);
}

void nummer_2()
{
  digitalWrite(ND_MT, LOW);
  digitalWrite(ND_RT, LOW);
  digitalWrite(ND_MM, LOW);
  digitalWrite(ND_LB, LOW);
  digitalWrite(ND_MB, LOW);
}

void nummer_3()
{
  digitalWrite(ND_MT, LOW);
  digitalWrite(ND_RT, LOW);
  digitalWrite(ND_MM, LOW);
  digitalWrite(ND_RB, LOW);
  digitalWrite(ND_MB, LOW);
}

void nummer_4()
{
  digitalWrite(ND_LT, LOW);
  digitalWrite(ND_RT, LOW);
  digitalWrite(ND_MM, LOW);
  digitalWrite(ND_RB, LOW);
}

void nummer_5()
{
  digitalWrite(ND_LT, LOW);
  digitalWrite(ND_MT, LOW);
  digitalWrite(ND_MM, LOW);
  digitalWrite(ND_RB, LOW);
  digitalWrite(ND_MB, LOW);
}
void nummer_6()
{
  digitalWrite(ND_LT, LOW);
  digitalWrite(ND_LB, LOW);
  digitalWrite(ND_MT, LOW);
  digitalWrite(ND_MM, LOW);
  digitalWrite(ND_MB, LOW);
  digitalWrite(ND_RB, LOW);
}

void nummer_7()
{
  digitalWrite(ND_MT, LOW);
  digitalWrite(ND_RT, LOW);
  digitalWrite(ND_RB, LOW);
}

void nummer_8()
{
  digitalWrite(ND_MT, LOW);
  digitalWrite(ND_MM, LOW);
  digitalWrite(ND_MB, LOW);
  digitalWrite(ND_LT, LOW);
  digitalWrite(ND_LB, LOW);
  digitalWrite(ND_RT, LOW);
  digitalWrite(ND_RB, LOW);
}

void nummer_9()
{
  digitalWrite(ND_LT, LOW);
  digitalWrite(ND_MT, LOW);
  digitalWrite(ND_MM, LOW);
  digitalWrite(ND_MB, LOW);
  digitalWrite(ND_RT, LOW);
  digitalWrite(ND_RB, LOW);
}

void modeSetColor(uint32_t c)
{
  for(int i=0; i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, c);
  }
  pixels.show();
}
