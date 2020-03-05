

#include <Servo.h>
#include <NewPing.h>

Servo myservo;
 
int pos = 0;
//Conectar el ultrasonido ahi Y REVISAR OTROS PINES!!!
const int Ultrasonic = 3;
int zeroThrottle = 90; //90 Needs to be between 66 and 101.
int maxThrottle = 120; //120 seems to be where the maximum is. Above this doesn't give any extra speed.
int minThrottle = 60;  //60 This represents the "reverse" speed.

//Distancia max en cm para el sensor
const int MaxDistance = 5;
volatile int obstaculo = 1;


NewPing sonar(Ultrasonic, Ultrasonic, MaxDistance);
 
void setup()
{

  Serial.begin(9600); //Pour some serial

// CONECTAR EL DRIVER AQUI!!!!
myservo.attach(9); // attaches the servo on pin 9 to the servo object

//Ponemos una interrupcion en el pin 2 donde esta el sensor US
pinMode(Ultrasonic, INPUT);
attachInterrupt(digitalPinToInterrupt(3), sensor, CHANGE);


/*Serial.println("Zero Throttle");
myservo.write(zeroThrottle);  // Set the output to the middle or "zero" position. CONNECT THE ESC DURING THIS DELAY!!
delay(5000);       // This delay allows the ESC to be connected and powered on. The motor will beep once on
                    // power up and once when it recognises the zero position.

Serial.println("Max");
myservo.write(maxThrottle); // Make sure your test bed is safe for the motor to turn at this point. It will run at maximum speed!
delay(2000);

Serial.println("Zero");
myservo.write(zeroThrottle); // Simulates the receiver sending a zero throttle signal again
delay(2000);

Serial.println("Min");
myservo.write(minThrottle); // "engages" reverse.
delay(20);

Serial.println("Zero");
myservo.write(zeroThrottle); // back to neutral
delay(20);

Serial.println("Min");
myservo.write(minThrottle); // motor runs in reverse
delay(2000);

Serial.println("Setup Complete");*/
 
}
 
void loop()
{
 
/*for(pos = zeroThrottle; pos < maxThrottle; pos += 1)  // goes from zero to max throttle
  {                                 
    myservo.write(pos);               // tell the ESC to position in variable 'pos'
    delay(200);                       // waits 200ms for the ESC to reach the position
    Serial.println(pos);              // print "pos"
  }*/

myservo.write(maxThrottle*obstaculo);           // Hold the max position for 2 seconds
delay (2000);

myservo.write(zeroThrottle);          // Go back to zero for 2 seconds

//delay (2000);

//myservo.write(minThrottle);           // Select reverse

delay (20);

//myservo.write(zeroThrottle);          // Back to zero again

/*delay (20);
 
  for(pos = zeroThrottle; pos>=minThrottle; pos-=1)     // goes from zero to "min" or motor turns in reverse
  {                               
    myservo.write(pos);               // tell the ESC to position in variable 'pos'
    delay(200);                       // waits 200ms for the ESC to reach the position
    Serial.println(pos);              // print "pos"
  }
delay(2000);

myservo.write(zeroThrottle);          // Go back to zero position
*/
delay(2000);
 
}

void sensor (){
  if (sonar.ping_cm()> MaxDistance){
    obstaculo = 0;
    } else {
    obstaculo = 1;
    
    }

}
