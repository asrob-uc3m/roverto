//-- Roverto
//--------------------------------------
#include <IBusBM.h>

//Min value of signal to start tx control
#define TX_THRESHOLD 0.2


//-- H-bridge pins
static const int m1_in1 = 2;
static const int m1_in2 = 4;
static const int m1_pwm1 = 6;
static const int m1_pwm2 = 3;

static const int m2_in1 = 8;
static const int m2_in2 = 7;
static const int m2_pwm2 = 9;

static const int enable = 5;


IBusBM IBus; // IBus object

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

bool rpi_control;


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
  IBus.begin(Serial1);
  //start rpi receiver
  Serial.begin(57600);

  rpi_control = true;
  delay(5000);
}

void loop()
{

  float speed, dir;
  dir = (((int)IBus.readChannel(0)) - 1500) / 500.0;
  speed = (((int)IBus.readChannel(1)) - 1500) / 500.0;
  if (speed > 0.2 || speed < -0.2 || dir < -0.2 || dir > 0.2) {
    rpi_control = false;
    Serial.print("rpi control ended");
  }
  if (rpi_control) {
    if (Serial.available()) {
      delay(10);
      Serial.println("START");
      //COMMAND FORMAT,VALUES BETWEEN -100 AND 100
      //V20 W30

      char command[12];
      command [0] = Serial.read();
      int i = 0;
      while (command[i] != ';' && i < 12 && Serial.available()) {
        i++;
        command [i] = Serial.read();
      }

      String input(command);
      int velIn = input.indexOf('V');
      int velEn = input.indexOf(' ');
      String vel = input.substring(velIn + 1, velEn);
      int dirIn = input.indexOf('W');
      int dirEn = input.indexOf(';');
      String dir = input.substring(dirIn + 1, dirEn);
      Serial.print("VEL: ");
      Serial.print(vel);
      Serial.print(" DIR: ");
      Serial.println(dir);

      //move(vel.toInt(), dir.toInt());
    }
  }
  else {
    //move(speed * 255, dir * 255);
  }

  delay(1);
}
