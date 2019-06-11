//-- Roverto
//--------------------------------------


//-- H-bridge pinout
static const int m1_in1 = 2;
static const int m1_in2 = 4;
static const int m1_pwm1 = 6;
static const int m1_pwm2 = 3;

static const int m2_in1 = 8;
static const int m2_in2 = 7;
static const int m2_pwm2 = 9;

static const int enable = 5;

/*
  move - move the robot
  v -> linear velocity
  w -> angular velocity
*/
void move(int v, int w)
{
    //-- Compute left and right wheel speeds
    int l_speed = constrain(v - w, -255, 255);
    int r_speed = constrain(v + w, -255, 255);

    //-- Enable motors
    digitalWrite(enable, HIGH);

    //-- Set left motor
    if (r_speed > 0)
    {
      digitalWrite(m1_in1, HIGH);
      digitalWrite(m1_in2, LOW);
      digitalWrite(m1_pwm1, LOW); //-- To be removed
      analogWrite(m1_pwm2, 190);
    }
    else
    {
      digitalWrite(m1_in1, LOW);
      digitalWrite(m1_in2, HIGH);
      digitalWrite(m1_pwm1, LOW); //-- To be removed
      analogWrite(m1_pwm2, 190);
    }

    //-- Set right motor
    if (l_speed > 0)
    {
      digitalWrite(m2_in1, LOW);
      digitalWrite(m2_in2, HIGH);
      analogWrite(m2_pwm2, 190);
    }
    else
    {
      digitalWrite(m2_in1, HIGH);
      digitalWrite(m2_in2, LOW);
      analogWrite(m2_pwm2, 190);
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
}

void loop()
{

  move(255, 0);


  while(true) {}

}
