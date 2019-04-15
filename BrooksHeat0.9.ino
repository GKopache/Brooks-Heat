#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5


// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

/*
water pump(WP) blue wire on relay 2 pin 10
fan relay 3 pin 11
espar relay 4 pin 12
esparEnable relay 1 pin 9
*/

int WP = 10, fan = 11, espar = 12, esparEnable = 9; 
float airTemp =0;

void setup(void)
{
  pinMode(WP, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(espar, OUTPUT);
  pinMode(esparEnable, OUTPUT);

  digitalWrite(WP, HIGH);
  digitalWrite(fan, HIGH);
  digitalWrite(espar, HIGH);
  digitalWrite(esparEnable, HIGH);
  
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
}


void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus

  
  sensors.requestTemperatures(); 
  
  Serial.print(" - Fahrenheit temperature: ");
  airTemp = sensors.getTempFByIndex(0);
  Serial.println(airTemp);

  if(airTemp < 50) {
  digitalWrite(WP, LOW);
  digitalWrite(fan, LOW);
  digitalWrite(espar, LOW);
  digitalWrite(esparEnable, LOW);
  }

  if else(airTemp > 65) {
  digitalWrite(WP, LOW);
  digitalWrite(fan, LOW);
  digitalWrite(espar, HIGH);
  digitalWrite(esparEnable, HIGH);
  }

  else{
  digitalWrite(WP, HIGH);
  digitalWrite(fan, HIGH);
  digitalWrite(espar, HIGH);
  digitalWrite(esparEnable, HIGH); 
  }
}
