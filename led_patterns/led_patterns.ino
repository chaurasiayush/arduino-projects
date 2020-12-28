int redPin = 3;
int bluePin = 5;
int greenPin = 4;
int nol = 3;
int delay_time = 0;
boolean close_LED = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT); 
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
  delay_time = 1000/nol;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Starting red LED...");
  onLED(redPin);
  if(close_LED)
    offLED(redPin, delay_time);

  Serial.println("Starting green LED...");
  onLED(greenPin);
  if(close_LED)
    offLED(greenPin, delay_time);

  Serial.println("Starting blue LED...");
  onLED(bluePin);
  if(close_LED)
    offLED(bluePin, delay_time);

  if(!close_LED){
    offLED(redPin, delay_time);
    offLED(greenPin, delay_time);
    offLED(bluePin, delay_time);
  }
}

void onLED(int pin) {
  digitalWrite(pin, HIGH);
}

void offLED(int pin, int delayTime) {
  delay(delayTime);
  digitalWrite(pin, LOW);
}
