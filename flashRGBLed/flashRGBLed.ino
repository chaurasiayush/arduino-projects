int aLED[] = {3,5,6}; 
int pinOn = 0;

void setup() {
  pinMode(aLED[0], OUTPUT);
  pinMode(aLED[1], OUTPUT);
  pinMode(aLED[2], OUTPUT);
//  Serial.begin(9600);
}

void loop() {

  int tmp = 0;
//  while((tmp = random(0, sizeof(aLED))) == pinOn);
  tmp = random(0, 3);
  pinOn = tmp;
  fadeIn(aLED[pinOn]);
  fadeOut(aLED[pinOn]);
}

void fadeIn(int pinOnn){
   for(int intensity=0; intensity<=255; intensity += 5){
     analogWrite(pinOnn, intensity);
     delay(3);
   }
  
}

void fadeOut(int pinOnn){
   for(int intensity=255 ;intensity >=0; intensity -= 5){
     analogWrite(pinOnn, intensity);
     delay(3);
   }
}
