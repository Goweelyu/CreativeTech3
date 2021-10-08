import processing.serial.*;
Serial myPort;  
int val;      
Ball[] balls = new Ball[500];

void setup(){
  size(1000,1000);
  
  String portName = Serial.list()[3];
  myPort = new Serial(this, portName, 9600);
  
  for(int i = 0; i < balls.length; i++ ){
     balls[i] = new Ball(int(random(0,1000)),int(random(0,1000)),int(random(6)),int(random(6)),int(random(20)));
  }
}

void draw(){
  
  background(0);
  fill(255);
  noStroke();
  
   if ( myPort.available() > 0) {  
    val = myPort.read();     
  }  
  
  for(int i = 0; i < val; i++){
     balls[i].display();
     balls[i].update();
  }
}
