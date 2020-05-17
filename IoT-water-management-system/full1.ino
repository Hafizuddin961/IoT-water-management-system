#define BLYNK_PRINT Serial
#define TCP_MSS whatever
#define LWIP_IPV6 whatever
#define LWIP_FEATURES whatever
#define LWIP_OPEN_SRC whatever


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const int trigPin = D2;
const int echoPin = D1;
long duration;
int distance;

int X;
int Y;
float TIME ;
float FREQUENCY ;
float WATER ;
float TOTAL ;
float LS ;
const int input = D3;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f45a06236ac14ade94e11f1dd8493a93";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "huh?";
char pass[] = "qwertyuiop";

void setup() {
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(input,INPUT);

}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.037/2;
// Prints the distance on the Serial Monitor
delay(200);



X = pulseIn(input, HIGH);
Y = pulseIn(input, LOW);
TIME = X + Y;
FREQUENCY = 1000000/TIME;
WATER = FREQUENCY/7.5;
LS = WATER/60;

if(FREQUENCY >= 0)
{
if(isinf(FREQUENCY))
{
Serial.print ("0 L/M  ");
Serial.print (TOTAL);
}
else
{
TOTAL = TOTAL + LS;
Serial.print (TOTAL); //Prints the number calculated above
Serial.print (" L"); //Prints "L/hour" and returns a  new line
}
}
delay(1000);

Serial.print(" Distance: ");
Serial.println(distance);
Blynk.virtualWrite(V5, distance);

/*Serial.print (WATER); //Prints the number calculated above
Serial.print (" L/M  "); //Prints "L/hour" and returns a  new line
Serial.print (TOTAL); //Prints the number calculated above
Serial.print (" L"); //Prints "L/hour" and returns a  new line*/

Blynk.virtualWrite(V6, TOTAL);

delay(200);  
  
Blynk.run();

}

