

static const int m1_in1 = 2;
static const int m1_in2 = 4;
static const int m1_pwm1 = 6;
static const int m1_pwm2 = 3;

static const int m2_in1 = 8;
static const int m2_in2 = 7;
static const int m2_pwm2 = 9;

static const int enable = 5;


void setup() {
  // Configure motor pins
  pinMode(m1_in1, OUTPUT);
  pinMode(m1_in2, OUTPUT);
  pinMode(m1_pwm1, OUTPUT);
  pinMode(m1_pwm2, OUTPUT);

  pinMode(m2_in1, OUTPUT);
  pinMode(m2_in2, OUTPUT);
  pinMode(m2_pwm2, OUTPUT);
  
  pinMode(enable, OUTPUT);

}

void loop() {
  digitalWrite(m1_in1, HIGH);
  digitalWrite(m1_in2, LOW);
  digitalWrite(m1_pwm1, LOW);
  analogWrite(m1_pwm2, 190);

  digitalWrite(m2_in1, LOW);
  digitalWrite(m2_in2, HIGH);
  analogWrite(m2_pwm2, 190);
  
  digitalWrite(enable, LOW);

  while(true) {}

}
