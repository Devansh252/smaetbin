#include <Servo.h>   //servo library
Servo servo; 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(8, 9); // RX | TX    
int sensorPin = A0;
int sensorValue = 0;
int trigPin = 4;    
int echoPin = 5;   
int servoPin = 7;
int led=11;
long duration, dist, average;   
long aver[3];   //array for average
int ir=3;
int val;


void setup() {       
    Serial.begin(9600);
    BTserial.begin(9600);
    
    pinMode(ir,INPUT);
    pinMode(led,OUTPUT);
    servo.attach(servoPin);  
    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT);  
    servo.write(0);         //close cap on power on
    delay(100);
    servo.detach(); 
  
} 

void measure() {  
digitalWrite(10,HIGH);
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1;    //obtain distance
}
void loop() { 
  sensorValue = analogRead(sensorPin);
  val=digitalRead(ir);
  if(val==HIGH){
    delay(2000);
    digitalWrite(led,LOW);
    BTserial.print("BIN EMPTY");
    

BTserial.print(",");


BTserial.print("ADD TRASH");

BTserial.print(";");
    Serial.print(val);
  }
  else{
    delay(1000);
    digitalWrite(led,HIGH);
    BTserial.print("BIN FULL");
    BTserial.print(",");


BTserial.print("THROW TRASH");

BTserial.print(";");
    Serial.print(val);
    
    
  }
  
  for (int i=0;i<=2;i++) {   //average distance
    measure();               
   aver[i]=dist;            
    delay(10);              //delay between measurements
  }
 dist=(aver[0]+aver[1]+aver[2])/3;    

if ( dist<20 ) {
//Change distance as per your need

 servo.attach(servoPin);
  delay(1);
 servo.write(0);  
 delay(3000);       
 servo.write(80);    
 delay(200);
 servo.detach();      
}
//Serial.print(dist);
}
