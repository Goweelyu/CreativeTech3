int trig = 3;
int echo = 4;
float Value_cm;// Define the distance value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig,0);//Initialize the port
  delayMicroseconds(20);
  digitalWrite(trig,1);//Give the port a high level
  delayMicroseconds(20);
  digitalWrite(trig,0);//Initialize the port
  Value_cm = float(pulseIn(echo,1)*17)/1000;//Transfer the high level to distance
  
  //Serial.print(Value_cm);//Display the distance
  //Serial.println("cm");//Note the unit
  int Val = Value_cm;
  Serial.write(Val);
  delay(20);
}
