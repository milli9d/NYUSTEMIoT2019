#define IO_USERNAME  "tdhoffmann"
#define IO_KEY       "0f05a15274ab4663aef5a2e58834b79d"
void setup() {
                                                // put your setup code here, to run once:

Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(15, OUTPUT); //1st LED
  pinMode(13, OUTPUT); //2nd LED
  pinMode(12, OUTPUT); //3rd LED
  pinMode(14, OUTPUT); //4th LED
 
}
int myAnalog=0;
void loop() 
{
                                                  // put your main code here, to run repeatedly:

delay(100);
Serial.println(analogRead(A0));
myAnalog=analogRead(A0);

if (myAnalog < 700)
 {
   digitalWrite(15, LOW);
   digitalWrite(13, LOW);
   digitalWrite(12, LOW);
   digitalWrite(14, LOW); // All LED's off with less than 600 light
   
 }
else if (myAnalog < 800)
 {
  digitalWrite(15, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(14, LOW); // 1 LED on less than 800 light
 }

else if (myAnalog < 900)
 {
  digitalWrite(15, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(14, LOW); // 2 LED's on less than 900 light
 }

else if (myAnalog < 1000)
 {
  digitalWrite(15, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(14, LOW); // 3 LED on less than 1000 light
 }
 
else if (myAnalog > 1020)
{
  digitalWrite(15, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(14, HIGH); // 4 LED's on more than 1000 light
}
 
}
