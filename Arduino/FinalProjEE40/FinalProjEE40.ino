float val, threshold;
//function to calibrate IR sensor
float initialVal(){
  float tmp = 0, maxTmp = 0;
  for(int i = 0; i<500; i++){
    tmp = analogRead(A5);
    if(maxTmp < tmp){
      maxTmp = tmp;
    } 
  }
  return maxTmp;
}
int r2 = 5;
int r1 = 7;
int r3 = 6;
int r4 = 4;
int speakerOut = 12;
int speakerState = 11;
int stateLock = 0;
void setup(){
  Serial.begin(9600);
  pinMode(speakerOut, OUTPUT);
  pinMode(speakerState, OUTPUT);
  digitalWrite(speakerOut, LOW);
  digitalWrite(speakerState, LOW);
  val = initialVal();
  threshold = val + 100;
  //Serial.println(threshold);
  pinMode(r2, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);

}

void loop(){
  if(Serial.available() > 0){
    char data = Serial.read();
    //if lock is clicked
    if(data == '1' && !stateLock){
      //assign statevariable to not state variable 
      //so doesn't receive any more lock commands
      //also activate speaker
      stateLock = !stateLock;
      //move motor into locked position
      digitalWrite(r1, LOW);
      digitalWrite(r2, LOW);
      digitalWrite(r3, HIGH);
      digitalWrite(r4, HIGH);
      delay(300);
      digitalWrite(r1, HIGH);
      digitalWrite(r2, HIGH);
      digitalWrite(r3, HIGH);
      digitalWrite(r4, HIGH);
    }
    //if unlock is clicked
    else if(data == '0' && stateLock){
      //assign statevariable to not state variable 
      //so doesn't receive any more unlock commands
      stateLock = !stateLock;
      //move motor into unlocked position
      digitalWrite(r1, HIGH);
      digitalWrite(r2, HIGH);
      digitalWrite(r3, LOW);
      digitalWrite(r4, LOW);
      delay(300);
      digitalWrite(r1, HIGH);
      digitalWrite(r2, HIGH);
      digitalWrite(r3, HIGH);
      digitalWrite(r4, HIGH);
      //deactivate speaker
      digitalWrite(speakerOut, LOW);
    }
 
  }
     //speaker code
    if(stateLock){
      val = analogRead(A5);
//      Serial.println(val);
//      delay(100);
      if(val > threshold){
        digitalWrite(speakerState, HIGH);
        tone(speakerOut, val*5, 10);
      }
      else{
        digitalWrite(speakerState, LOW);
        digitalWrite(speakerOut, LOW);
      }
    }
}
