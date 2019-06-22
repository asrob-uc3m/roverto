//-- Roverto
//--------------------------------------
//#include <IBusBM.h>

//-- H-bridge pins
static const int m1_in1 = 2;
static const int m1_in2 = 4;
static const int m1_pwm1 = 6;
static const int m1_pwm2 = 3;

static const int m2_in1 = 8;
static const int m2_in2 = 7;
static const int m2_pwm2 = 9;

static const int enable = 5;

//IBusBM IBus; // IBus object

/*
  move - move the robot
 v -> linear velocity
 w -> angular velocity
 */
void move(int v, int w)
{
  //-- Compute left and right wheel speeds
  int l_speed = constrain(v + w, -255, 255);
  int r_speed = constrain(v - w, -255, 255);

  //-- Enable motors
  digitalWrite(enable, HIGH);

  //-- Set left motor
  if (r_speed > 0)
  {
    r_speed = map(r_speed, 1, 255, 1, 255); //-- Motor range is 190-255, convert to that range
    digitalWrite(m1_in1, HIGH);
    digitalWrite(m1_in2, LOW);
    digitalWrite(m1_pwm1, LOW); //-- To be removed
    analogWrite(m1_pwm2, r_speed);
  }
  else if (r_speed < 0)
  {
    r_speed = map(r_speed, -255, -1, 1, 255); //-- Motor range is 190-255, convert to that range
    digitalWrite(m1_in1, LOW);
    digitalWrite(m1_in2, HIGH);
    digitalWrite(m1_pwm1, LOW); //-- To be removed
    analogWrite(m1_pwm2, r_speed);
  }
  else
  {
    digitalWrite(m1_in1, LOW);
    digitalWrite(m1_in2, LOW);
    digitalWrite(m1_pwm1, HIGH); //-- To be removed
    analogWrite(m1_pwm2, 0);
  }

  //-- Set right motor
  if (l_speed > 0)
  {
    l_speed = map(l_speed, 1, 255, 1, 255); //-- Motor range is 190-255, convert to that range
    digitalWrite(m2_in1, LOW);
    digitalWrite(m2_in2, HIGH);
    analogWrite(m2_pwm2, l_speed);
  }
  else if (l_speed < 0)
  {
    l_speed = map(l_speed, -255, -1, 1, 255); //-- Motor range is 190-255, convert to that range
    digitalWrite(m2_in1, HIGH);
    digitalWrite(m2_in2, LOW);
    analogWrite(m2_pwm2, l_speed);
  }
  else
  {
    digitalWrite(m2_in1, LOW);
    digitalWrite(m2_in2, LOW);
    analogWrite(m2_pwm2, 0);
  }
}

void setup()
{
  // Configure motor pins
  pinMode(m1_in1, OUTPUT);
  pinMode(m1_in2, OUTPUT);
  pinMode(m1_pwm1, OUTPUT);
  pinMode(m1_pwm2, OUTPUT);

  pinMode(m2_in1, OUTPUT);
  pinMode(m2_in2, OUTPUT);
  pinMode(m2_pwm2, OUTPUT);

  pinMode(enable, OUTPUT);
  digitalWrite(enable, LOW);

  // Start RC receiver
  Serial1.begin(9600);
  //  IBus.begin(Serial1);
  //start rpi receiver
  Serial.begin(57600);
}

String input;

void loop()
{

/*  float speed, dir;
   dir = (((int)IBus.readChannel(0))-1500)/500.0;
   speed = (((int)IBus.readChannel(1))-1500)/500.0;
   Serial.print(speed);
   Serial.print(" ");
   Serial.println(dir);
   
   move(speed*255, dir*255);
   delay(20);*/

  if (Serial.available()){
    //COMMAND FORMAT
    //V20 W30
    input = Serial.readStringUntil('\n');
    int velIn = input.indexOf('V');
    int velEn = input.indexOf(' ');
    String vel = input.substring(velIn + 1,velEn);
    int dirIn = input.indexOf('W');
    String dir = input.substring(dirIn + 1);
    move(vel.toInt(),dir.toInt());
   /* Serial.print("speed ");
    Serial.print(vel.toInt());
    Serial.print("\tdirection");
    Serial.println(dir.toInt());*/
    
    //********************Convivencia Raspberry-emisora********************
    
  }    
  delay(1);
}












