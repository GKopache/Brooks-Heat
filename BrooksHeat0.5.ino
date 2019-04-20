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

int ser_rx;

void setup(void)
{
  pinMode(WP, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(espar, OUTPUT);
  pinMode(esparEnable, OUTPUT);
  
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
}


void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus

  sensors.requestTemperatures(); 
  
  Serial.print("Temp F: ");
  Serial.println(sensors.getTempFByIndex(0));
  delay(2000);

  ser_rx=Serial.available();
  int rpi[ser_rx];
  if(ser_rx > 0){
    for(int i=0;i<ser_rx;i++){
    rpi[i] = Serial.read();
    }
  }
  
  if(rpi[0] == 2){
    digitalWrite(WP, LOW);
    digitalWrite(fan, LOW);
    digitalWrite(espar, LOW);
    digitalWrite(esparEnable, LOW);
  }

  else if(rpi[0] == 1){
    digitalWrite(WP, LOW);
    digitalWrite(fan, LOW);
    digitalWrite(espar, HIGH);
    digitalWrite(esparEnable, HIGH);      
  }

  else if(rpi[0] == 0){
    digitalWrite(WP, HIGH);
    digitalWrite(fan, HIGH);
    digitalWrite(espar, HIGH);
    digitalWrite(esparEnable, HIGH);      
  }  
  
}
