/*
 This code is released under the the Open Source ISC License and the WTFPL License.
 Feel free to do anything you want to, but change the name of the project.
 201305171614 Alex Shure
 */

unsigned int brightness = 0;
const int gain = 255; // 0..255, whereas 255 equals a gain of 1 - thus this is an attenuation.
const int rPin = 5; // arms up \o/
const int gPin = 6; // arms down /o\
int cp=0;

void l(byte _pin, byte _br=255){
  analogWrite(_pin, _br);
}

void invade(int _m=255,unsigned int _s=0){ //default stepover duration: 10ms
if (_s==0) _s=1; // workaround due to bug in <AR1.53
if ( _m > brightness ){
  for(int _i = brightness ; _i <= _m; _i+=1) { 
    // Serial.println("+1");
    l(rPin,_i); // set lower arm's PWM (range from 0 to 255):
    l(gPin,(255-_i)); // set upper arm's PWM (range from 0 to 255):
    delayMicroseconds(_s); // stepover duration
    brightness=_i;    
  } 
}
else {
  for(int _i = brightness ; _i >= _m; _i--) { 
    // Serial.println("-1");    
    l(rPin,_i); // set lower arm's PWM (range from 0 to 255):
    l(gPin,(255-_i)); // set upper arm's PWM (range from 0 to 255):
    delayMicroseconds(_s); // stepover duration
    brightness=_i;
  } 
}
}

void setup() {
//  Serial.begin(115200);   // initialize the serial communication
  pinMode(rPin, OUTPUT);   // set pins as outputs
  pinMode(gPin, OUTPUT); 
  digitalWrite(rPin,LOW);
  digitalWrite(gPin,LOW);
  }

void loop() {
  unsigned int fadeSpeed=analogRead(0);
  unsigned long interval=analogRead(1);
//  Serial.println("DEB");
//  Serial.println(fadeSpeed,DEC);
//  Serial.println(interval,DEC);
  unsigned long cycle=interval*10;
  fadeSpeed=fadeSpeed*5;
//  Serial.println(fadeSpeed,DEC);
//  Serial.println(cycle,DEC);
//  interval=1000;
//  fadeSpeed=20;
  invade(255,fadeSpeed);
  delay(cycle);
  invade(0,fadeSpeed);
  delay(cycle);
}
