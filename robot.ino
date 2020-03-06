#include <Servo.h>
#include <NewPing.h>  //https://bitbucket.org/teckel12/arduino-new-ping/downloads/
#define TRIG_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200
#define debug true
#define test false
#define lineTrashhold 10

#define MAX_SPEED 70 // sets speed of DC  motors

int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;     //M1 Direction Control
int M2 = 7;     //M1 Direction Control

int sensors[5];

Servo myservo;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

int speedSet = 0;
boolean isStarted = false;

void setup() {
  Serial.begin(9600);
  myservo.attach(8);
  myservo.write(115);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
}

void loop() {
  if (!isStarted) {
    isStarted = true;

    delay(5000);
  }
  readLijnSensor();
  boolean isOnTrack = sensors[2] < lineTrashhold;
  boolean isMovingLeftOfTrack = (sensors[3] < lineTrashhold);
  boolean isMovingRightOfTrack = (sensors[1] < lineTrashhold);
  boolean isLost = !isOnTrack &&

                   //  delay(2000);
                   //  moveForwards();
                   //  delay(2000);
                   //  moveBackwards();
                   //  delay(2000);
                   //  turnRight();
                   //  readPing();

                   Serial.println("====");
  Serial.println("on track: " + String(isOnTrack));
  Serial.println("left of track: " + String(isMovingLeftOfTrack && !isMovingRightOfTrack));
  Serial.println("right of track: " + String(isMovingRightOfTrack && !isMovingLeftOfTrack));
  Serial.println("====");

  if(test) {
    testMovement();
  }
}

void testMovement() {
  turnLeft();
  delay(10000);
  turnRight();
  delay(10000);
  moveForwards();
  delay(10000);
  moveBackwards();
  delay(10000);
}

void readLijnSensor() {
  sensors[0] = analogRead(A0);
  sensors[1] = analogRead(A1);
  sensors[2] = analogRead(A2);
  sensors[3] = analogRead(A3);
  sensors[4] = analogRead(A4);

  if (debug) {
    Serial.print("Lijn sensors: [");
    Serial.print(sensors[0]);
    Serial.print(", ");
    Serial.print(sensors[1]);
    Serial.print(", ");
    Serial.print(sensors[2]);
    Serial.print(", ");
    Serial.print(sensors[3]);
    Serial.print(", ");
    Serial.print(sensors[4]);
    Serial.println("]");
  }
}

int readPing() {
  int afstand = sonar.ping_cm();
  if (debug) {
    Serial.print("Ping: ");
    Serial.print(afstand);
    Serial.println("cm");
  }

  return afstand;
}

void turnRight() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);

  analogWrite (E1, MAX_SPEED);
  analogWrite (E2, MAX_SPEED);
}


void turnLeft() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);

  analogWrite (E1, MAX_SPEED);
  analogWrite (E2, MAX_SPEED);
}


void moveForwards() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);

  analogWrite (E1, MAX_SPEED);
  analogWrite (E2, MAX_SPEED);

}


void moveBackwards() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);

  analogWrite (E1, MAX_SPEED);
  analogWrite (E2, MAX_SPEED);
}

void stopNow() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);

  analogWrite(E1, 0);
  analogWrite(E2, 0);
}
