#include <Servo.h> 
#include <NewPing.h>  //https://bitbucket.org/teckel12/arduino-new-ping/downloads/

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 200 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;     //M1 Direction Control
int M2 = 7;     //M1 Direction Control

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo;   

int distance = 100;
boolean goesForward = false;
int speedSet = 0;

void setup(void) 
{ 
  Serial.begin(9600);
  myservo.attach(8);  
  myservo.write(115); 
} 
 
void loop(void) 
{
 moveForward();
}

void turnRight() {
 
  analogWrite (E1,155);
  analogWrite (E2,155); 
  digitalWrite(M1,LOW);    
  digitalWrite(M2,HIGH); 
  delay(1400);
  digitalWrite(M1,HIGH);    
  digitalWrite(M2,HIGH);
} 

void turnLeft()
{
  analogWrite (E1,155);
  analogWrite (E2,155); 
  digitalWrite(M1,HIGH);     
  digitalWrite(M2,LOW);
  delay(1600);
  digitalWrite(M1,HIGH);    
  digitalWrite(M2,HIGH);
}

void stop(void)      
{
  digitalWrite(E1,0); 
  digitalWrite(M1,LOW);    
  digitalWrite(E2,0);   
  digitalWrite(M2,LOW);    
}   

void moveBackward() 
{
  goesForward=false;
  digitalWrite(M1,LOW);    
  digitalWrite(M2,LOW);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2)
  {
    analogWrite (E2,speedSet);   
    analogWrite (E1,speedSet+MAX_SPEED_OFFSET);
    delay(5);
  }
}  

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    Serial.print("Looking right. Distance:");
    Serial.println(distance);
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    Serial.print("Looking left. Distance:");
    Serial.println(distance);
    return distance;
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    digitalWrite(M1,HIGH);    
    digitalWrite(M2,HIGH); 
    
     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2)
   {
     analogWrite (E2,speedSet);
     analogWrite (E1,speedSet+MAX_SPEED_OFFSET);
     delay(5);
   }
  }
}
