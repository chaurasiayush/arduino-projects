 
#include <IRremote.h>  //including infrared remote header file  
\
#define RED 0xC110
#define GREEN 0x74110
#define BLUE 0x8C110
#define DOWN 0x640C   
#define UP 0x240C  
#define FUNCTION 0x4B0D


int RECV_PIN = 11;
int RGB_PIN[] = {9, 6, 10};   
int selected = 0;
int MAX_STEPS = 255;
int MIN_STEPS = 0;
int bright[] = {100, 10, 255};
int steps = 5;
bool autometic = false;
long int receivedCode = 0;

IRrecv irrecv(RECV_PIN);     
decode_results results;  

//int blinkDelay = 1;


void blinkSelected(int times, int blinkDelay){
  for(int i=0; i<3; i++){
    analogWrite(RGB_PIN[i], 0);
  }
  
  for(int j = 0; j<times; j++){
    
    for(int i=0; i<255; i+=1){
        analogWrite(RGB_PIN[selected], i);
        delay(blinkDelay);
      }
    for(int i=255; i>=0; i-=1){
        analogWrite(RGB_PIN[selected], i);
        delay(blinkDelay);
      }
      
  }
    for(int i=0; i<3; i++){
    analogWrite(RGB_PIN[i], bright[i]);
  }
}

void interpretCode(long int code){

    if(code == FUNCTION && autometic){
      autometic = false;
    }
    else if (!autometic){
      switch(code){
        case RED:
          selected = 0;
          blinkSelected(1, 1);
          Serial.println("SELECTED RED:");
          break;
          
        case GREEN:
          selected = 1;
          blinkSelected(1, 1);
          Serial.println("SELECTED GREEN:");
          break;
  
        case BLUE:
          selected = 2;
          blinkSelected(1, 1);
          Serial.println("SELECTED BLUE:");
          break;

        case FUNCTION:
          autometic = true;
          receivedCode = 0;
          break;
  
        case UP:
         
          Serial.print("Intensity : ");
          bright[selected] += steps;
          if( bright[selected] > MAX_STEPS) {
             bright[selected] = MAX_STEPS;
             blinkSelected(3, 0);
          }
          Serial.println(bright[selected]);
          analogWrite(RGB_PIN[selected], bright[selected]);
          break;
  
         case DOWN:
          Serial.print("Intensity : ");
          bright[selected] -= steps;
          if( bright[selected] < MIN_STEPS) {
             bright[selected] = MIN_STEPS;
             blinkSelected(2, 0);
          }
          Serial.println(bright[selected]);
          analogWrite(RGB_PIN[selected], bright[selected]);
          break;
      }
    }

}

void transitionTo(int rgb[], int stepsMultiplier, int transitionDelay){
  int difference[] = {0, 0, 0};
  difference[0] = rgb[0] - bright[0];
  difference[1] = rgb[1] - bright[1];
  difference[2] = rgb[2] - bright[2];
  
  int max;
  if(abs(difference[0]) >= abs(difference[1])){
    if(abs(difference[0]) >= abs(difference[2]))
      max = 0;
    else
      max = 1;
  }else{
    if(abs(difference[1]) >= abs(difference[2]))
      max = 1;
    else 
      max = 2;
  }
  if(difference[max] == 0){
    return;
  }

  float steps[] = {
      (float)(stepsMultiplier*difference[0])/abs(difference[max]), 
      (float)(stepsMultiplier*difference[1])/abs(difference[max]), 
      (float)(stepsMultiplier*difference[2])/abs(difference[max])
    };

    float temp[] = {(float)(bright[0]),
                    (float)(bright[1]),
                    (float)(bright[2])
                  };
    while(true){
      
      temp[0] += steps[0];
      temp[1] += steps[1];
      temp[2] += steps[2];

      bright[0] = temp[0];
      bright[1] = temp[1];
      bright[2] = temp[2];

      if(
        (steps[max] < 0 && bright[max] < rgb[max]) || 
        (steps[max] > 0 && bright[max] > rgb[max])){
        
        bright[0] = rgb[0];
        bright[1] = rgb[1];
        bright[2] = rgb[2];
        break;
      }

      analogWrite(RGB_PIN[0], bright[0]);
      analogWrite(RGB_PIN[1], bright[1]);
      analogWrite(RGB_PIN[2], bright[2]);

      delay(transitionDelay);

    }

}

void displayRandomColor(){
  int randomColor[3];
  int fullBright = rand()%2;
  for(int i=0; i<3; i++){
    
     if(i == fullBright){
      randomColor[i] = 255;
     }else{
     randomColor[i] = rand()%255;
     }
  }
  transitionTo(randomColor, 1);
}

void setup()     
{     
Serial.begin(115200);     
irrecv.enableIRIn();

  pinMode(RGB_PIN[0], OUTPUT);
  pinMode(RGB_PIN[1], OUTPUT);
  pinMode(RGB_PIN[2], OUTPUT);

  analogWrite(RGB_PIN[0], bright[0]);
  analogWrite(RGB_PIN[1], bright[1]);
  analogWrite(RGB_PIN[2], bright[2]);

}
void loop()     
{     
  if (irrecv.decode(&results))
  {  
   irrecv.printResultShort(&Serial);   
   receivedCode = results.value;   
    
    Serial.println(results.value, HEX);     
    interpretCode(receivedCode);
    Serial.print("RECEIVED ");
    Serial.println(receivedCode);
    irrecv.resume();
  }
  if(autometic){
    displayRandomColor();
  }
delay(10);
}  
