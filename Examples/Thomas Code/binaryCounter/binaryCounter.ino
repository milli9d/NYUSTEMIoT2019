int myCounter=0;

void setup() {
   
 Serial.begin(9600);
                                                                               // put your setup code here, to run once:
   pinMode(15,OUTPUT); // 1st LED
   pinMode(13,OUTPUT); // 2nd LED
   pinMode(12,OUTPUT); // 3rd LED
   pinMode(14,OUTPUT); // 4th LED

}

void loop() {
       
   delay(1000);                                                                              // put your main code here, to run repeatedl
  if((myCounter & 1) !=0)
  {
    digitalWrite(14, HIGH);
  }
  else
    digitalWrite(14, LOW);


 //1st LED ^


 

  if((myCounter & 2) !=0)
  {
    digitalWrite(12, HIGH);
  }
  else
    digitalWrite(12, LOW);
 
//2nd LED ^




   if((myCounter & 4) !=0)
   {
    digitalWrite(13, HIGH);
   }
   else
    digitalWrite(13, LOW);

//3rd LED ^




   if((myCounter & 8) !=0)
   {
    digitalWrite(15, HIGH);
   }
   else
    digitalWrite(15, LOW);
  myCounter++;

  Serial.println(myCounter);
//4th LED ^


}
