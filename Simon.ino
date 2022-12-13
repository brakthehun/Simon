#include <Adafruit_NeoPixel.h>
#define LED_PIN    6
#define LED_COUNT 24
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

byte simon[LED_COUNT];
int mem;
int current;

byte pinputs[4]={2,3,5,4};
byte clrs[4][3]={{0,0,255},
                {255,0,0},
                {0,255,0},
                {155,100,0}};

void setup() {
  //Serial.begin(115200);
  strip.begin();
//  for(int a=0;a<LED_COUNT;a++){
//    strip.setPixelColor(a,strip.ColorHSV(random(65536)));
//    strip.show();
//    delay(50);
//    strip.setPixelColor(a,0,0,0);
//  }
  strip.show();
  for(int a=0;a<4;a++){
    pinMode(pinputs[a],INPUT_PULLUP);
  }
  randomSeed(analogRead(2));
  clearPixels();
}

bool guess;
bool win=1;
bool latch;

void loop() {
  //randomSeed(analogRead(random(5)+1));
  simon[mem]=random(4);
  //Serial.println(simon[mem]);
  mem++;
  for(int a=0;a<mem;a++){
    setSimon(simon[a]);
    strip.show();
    delay(400);
    clearPixels();
    strip.show();
    delay(100);
  }
  for(int a=0;a<mem;a++){
    guess=0;
    current=a;
    while(!guess){
      for(int b=0;b<4;b++){
        if(!digitalRead(pinputs[b])&&!latch){
          guess=1;
          latch=1;
          if(b==simon[a]){
            setSimon(b);
            strip.show();
            delay(150);
            clearPixels();
            strip.show();
          } else {
            win=0;
            a=60;
          }
          while(!digitalRead(pinputs[b])){
            delay(12);
          }
        }
        if(digitalRead(pinputs[b])&&latch){
          latch=0;
          delay(50);
        }
      }
    }
  }
  if(win){
    //Serial.print("hooray");
    for(int a=0;a<50;a++){
      strip.setPixelColor(random(LED_COUNT),85,85,85);
      strip.show();
      delay(20);
      clearPixels();
    }
    strip.show();
    delay(500);
  }
  if(!win){
    //Serial.println("loser!");
    //Serial.print("memory:");
    //Serial.println(mem);
    
    for(int a=0;a<10;a++){
      setSimon(simon[current]);
      strip.show();
      delay(50);
      clearPixels();
      strip.show();
      delay(50);
    }
    for(int a=0;a<LED_COUNT;a++){
      strip.setPixelColor(a,0,0,0);
    }
    for(int a=0;a<mem;a++){
      strip.setPixelColor(a,strip.ColorHSV(((1024/LED_COUNT)*a)*64));
      strip.show();
      delay(100);
    }
    mem=0;
    win=1;
    delay(2000);
    clearPixels();
    strip.show();
    delay(500);
  }
}

void setSimon(int secz){
  for(int a=0;a<6;a++){
    strip.setPixelColor((secz*6)+a,clrs[secz][0],clrs[secz][1],clrs[secz][2]);
  }
}
void clearPixels(){
  for(int a=0;a<4;a++){
    for(int b=0;b<6;b++){
      strip.setPixelColor((a*6)+b,clrs[a][0]/64,clrs[a][1]/64,clrs[a][2]/64);
    }
  }
}
