const int IRsense1 = 8;
const int IRsense2 = 9;
const int IRsense3 = 10;

const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 200;

void setup() {

  // Set the baud rate
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(IRsense1, INPUT);
  pinMode(IRsense2, INPUT);
  pinMode(IRsense3, INPUT);
}

void loop() {

  while (1) {
    if (digitalRead(IRsense1) == LOW) {
      Serial.println(1);
      while (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
        //delay(1000);
        Serial.println(data);
        int stepstorotate = data.toInt();
        if (stepstorotate == 280) {
          for (int x = 0; x < stepstorotate ; x++) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(4500);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(4500);
          }
          Serial.println(2);
        }
        else if(stepstorotate == 380){
          for (int x = 0; x < stepstorotate ; x++) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(4500);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(4500);
          }
          Serial.println(3);
        }
      }
      delay(10);
    } else {
      if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
        //delay(1000);
        Serial.println(data);
        int stepstorotate = data.toInt();
        if(stepstorotate == 380){
          for (int x = 0; x < stepstorotate ; x++) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(4500);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(4500);
          }
          Serial.println(3);
        }
      }
      digitalWrite(13, LOW);
      Serial.println(0);
      delay(10);
    }
    delay(500);
  }

  while (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    //Serial.print("Hi Raspberry Pi! You sent me: ");
    delay(1000);
    Serial.println(data);
  }
}