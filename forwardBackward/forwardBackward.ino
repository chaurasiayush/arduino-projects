int led[] = {2,3,4,5,6,7,8,9,10,11};
int delayTime = 11;
int delayStep = 2;
//int delayStepStep = 2;
boolean delayMode = true;   //true means increasing and false means decreasing
//boolean delayStepMode = true;

void setup() {
  for(int i=0; i<sizeof(led)/sizeof(led[0]); i++)
    pinMode(led[i], OUTPUT);

}

void loop() {
  runPattern();
}

void runPattern(){
  dostep(true);
  dostep(false);
  changeDelay();
}

void dostep(boolean type){    //type 0 means forward and 1 means backword
  if(type){
    for(int i=0; i<sizeof(led)/sizeof(led[0]); i++){
      digitalWrite(led[i], HIGH);
      delay(delayTime);
//      changeDelay();
      digitalWrite(led[i], LOW);
    }
  }else{
    for(int i=sizeof(led)/sizeof(led[0])-1; i>=0; i--){
      digitalWrite(led[i], HIGH);
      delay(delayTime);
//      changeDelay();
//      changeDelayStep();
      digitalWrite(led[i], LOW);
    }
  }
}

void changeDelay(){
  if(delayMode){
    delayTime += delayStep/2;
    if(delayTime >= 14)
      delayMode = false;
  }else{
    delayTime -= delayStep*2;
    if(delayTime <= 4)
      delayMode = true;
  }
}

//void changeDelayStep(){
//  if(delayStepMode){
//    delayStep += delayStepStep;
//    if(delayStep >= 30)
//      delayStepMode = false;
//  }else{
//    delayStep -= delayStepStep;
//    if(delayStep <= 0)
//      delayStepMode = true;
//  }
//}
