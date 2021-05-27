int Count=0;
int Relay1=0;
int Relay2=0;
int Relay3=0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  //Serial.begin(9600);
}
  
void loop() {
  Count=analogRead(A1);
  //Serial.println(Count);
  
  if(Count > 500 && Count < 600)
  {
    delay(250);
    for(int t=0; t<=500; t++)
    {
      delay(2);
      Count=analogRead(A0);
      if(Count > 450 && Count < 600)
      {
        Relay1++;
        break;
        delay(200);
      }
    }
  }
  if (Relay1 == 4) {
    Relay1 = 0;
  }
  if (Relay1 == 0) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  if (Relay1 == 1) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  if (Relay1 == 2) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }
  if (Relay1 == 3) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
  }
}
