#include <AFMotor.h>
#include <Servo.h>
#define spoint 103
#define Echo A0
#define Trig A1
char value;
int distance;
int Left;
int Right;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;
String command;
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo head;
Servo l_arm;
Servo r_arm;
Servo l_palm;
Servo r_palm; 
void setup() 
{
  Serial.begin(9600);
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);
  head.attach(10);
  l_palm.attach(4);
  l_arm.attach(5);
  r_arm.attach(6);
  r_palm.attach(7);
  head.write(90);
  l_palm.write(0);
  r_palm.write(0);
  l_arm.write(90);
  r_arm.write(90);
}

void loop() 
{  
  delay(10);
  while(Serial.available()) 
  {
  command = "";  
  command = Serial.readString();
    Serial.print(command);
  }
  //surround();
  if(command == "*move forward#")
  {
     forward();
  }
  else if(command == "*Move forward#")
  {
    forward();
  }
  else if(command == "*back#")
  {
    backward();
  }else if(command == "*Back#")
  {
    backward();
  }
  else if(command == "*left#")
  {
    left();
  } else if(command == "*Left#")
  {
    left();
  }
  else if(command == "*right#")
  {
    right();
  }else if(command == "*Right#")
  {
    right();
  }
  else if(command == "*stop#")
  {
    Stop();
  }else if(command == "*Run#")
  {
    run();
  }else if(command== "*free#")
  {
    surround();
  }
   else if(command== "*Jimmy#")
   {
    jimmy();
  }
  else if(command== "*rotate#")
  {
    roll();
  }
   else if(command== "*Rotate#")
  {
    roll();
  }
}

void forward() {
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  delay(1500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
}

void backward() {
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  delay(1500);
    motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void left() {
  head.write(180);
  delay(500);
  head.write(90);
  delay(500);
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void right() {
  head.write(0);
  delay(500);
  head.write(90);
  delay(500);
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void run() {
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
}
void surround() 
{
  distance = ultrasonic();
  if (distance < 15) 
  {
    Stop();
    backward();
    delay(100);
    Stop();
    L = leftsee();
    head.write(spoint);
    delay(800);
    R = rightsee();
    head.write(spoint);
    if (L < R) 
    {
      right();
      delay(500);
      Stop();
      delay(200);
    } 
    else if (L > R) 
    {
      left();
      delay(500);
      Stop();
      delay(200);
    }
  } 
  else 
  {
    forward();
  }

}
int rightsee() 
{
  head.write(0);
  delay(800);
  Left = ultrasonic();
  return Left;
}

int leftsee() 
{
  head.write(180);
  delay(800);
  Right = ultrasonic();
  return Right;
}
int ultrasonic() 
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2; //time convert distance
  return cm;
}
void jimmy()
{
  head.write(0);
  delay(500);
  head.write(90);
  delay(500);
  head.write(180);
  delay(500);
  head.write(90);
  delay(500);
}
void roll() 
{
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
   delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void boot()
{
  head.write(180);
  l_arm.write(90);
  l_palm.write(180);
  delay(1000);
  head.write(0);
  l_arm.write(0);
  l_palm.write(0);
  r_arm.write(90);
  r_palm.write(180);
}
