int led12 = 11;
int led9 = 10;
unsigned long count = 0;
bool countSet = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led12,OUTPUT);
  pinMode(led9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();
  if (now-count>=10000 && now-count<15000){
    analogWrite(led12,0);
    analogWrite(led9,0);
    
  }
  if ( now - count >= 15000 && !countSet){
    count = now;
    countSet = true;
  }
  if (now - count >= 0 && now - count < 10000)  {
    analogWrite(led12,200);
    analogWrite(led9,200);
    countSet = false;
  }
  Serial.println(now);
  

}
