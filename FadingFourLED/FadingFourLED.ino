int aRed = 3;
int aGreen = 4;
int aBlue = 5;
int aYellow = 6;
int pinOn = 3;

void setup() {
  pinMode(aRed, OUTPUT);
  pinMode(aGreen, OUTPUT);
  pinMode(aBlue, OUTPUT);
  pinMode(aYellow, OUTPUT);
}

void loop() {

  int tmp = 3;
  while((tmp = random(3, 7)) == pinOn);

  pinOn = tmp;
  if(tmp == 4){
    fadeIn(9);
    fadeOut(9);
    
  }else{
    fadeIn(pinOn);
    fadeOut(pinOn);
  }

}

void fadeIn(int pinOn){
   for(int intensity=0; intensity<=255; intensity += 1){
     analogWrite(pinOn, intensity);
     delay(1);
   }
  
}

void fadeOut(int pinOn){
   for(int intensity=255 ;intensity >=0; intensity -= 1){
     analogWrite(pinOn, intensity);
     delay(1);
   }
}
