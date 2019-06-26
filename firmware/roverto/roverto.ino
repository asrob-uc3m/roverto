//-- Roverto
//--------------------------------------
#include <IBusBM.h>

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

//-- Speed limit
static const int lower_speed_limit = 120;

//#define PARENTAL_CONTROL
#ifdef PARENTAL_CONTROL
static const int upper_speed_limit = lower_speed_limit;
#else
static const int upper_speed_limit = 255;
#endif

#define FAILSAFE
#ifdef FAILSAFE
static const int FAILSAFE_CHANNEL = 3; //-- Starts at 0
static const int FAILSAFE_VALUE = -1;
#endif

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
      r_speed = map(r_speed, 1, 255, lower_speed_limit, upper_speed_limit);
      digitalWrite(m1_in1, HIGH);
      digitalWrite(m1_in2, LOW);
      digitalWrite(m1_pwm1, LOW); //-- To be removed
      analogWrite(m1_pwm2, r_speed);
    }
    else if (r_speed < 0)
    {
      r_speed = map(r_speed, -255, -1, lower_speed_limit, upper_speed_limit);
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
      l_speed = map(l_speed, 1, 255, lower_speed_limit, upper_speed_limit);
      digitalWrite(m2_in1, LOW);
      digitalWrite(m2_in2, HIGH);
      analogWrite(m2_pwm2, l_speed);
    }
    else if (l_speed < 0)
    {
      l_speed = map(l_speed, -255, -1, lower_speed_limit, upper_speed_limit);
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
  IBus.begin(Serial1);

  Serial.begin(57600);
}

void loop()
{
  float speed=0, dir=0;
  int failsafe=0;
  dir = (((int)IBus.readChannel(0))-1500)/500.0;
  speed = (((int)IBus.readChannel(1))-1500)/500.0;
  failsafe = (((int)IBus.readChannel(FAILSAFE_CHANNEL))-1500)/500.0;
  Serial.print(speed);
  Serial.print(" ");
  Serial.print(dir);
  Serial.print(" ");
  Serial.println(failsafe);

  if (failsafe==FAILSAFE_VALUE)
  {
    move(speed*255, dir*255);
  }
  else
  {
    move(0, 0);
  }
  
  delay(20);
}
