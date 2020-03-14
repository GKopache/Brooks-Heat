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

int WP = 10, fan = 12, espar = 11, esparEnable = 9; 

String ser_rpi;

int cabin_temp, heat_status;

void setup(void)
{
  pinMode(WP, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(espar, OUTPUT);
  pinMode(esparEnable, OUTPUT);

  ser_rpi = "0";
  
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
}

int heat_cycle( int heat_mode){
  int esp_status;
  //heat cabin
  if(heat_mode == '3'){
    digitalWrite(WP, LOW);
    digitalWrite(fan, LOW);
    digitalWrite(espar, LOW);
    digitalWrite(esparEnable, LOW);
    esp_status = 3;
  } 
  //pre-heat
  else if(heat_mode == '2'){
    digitalWrite(WP, LOW);
    digitalWrite(fan, HIGH);
    digitalWrite(espar, LOW);
    digitalWrite(esparEnable, LOW);
    esp_status = 2;
  }
  //rest
  else if(heat_mode == '1'){
    digitalWrite(WP, LOW);
    digitalWrite(fan, LOW);
    digitalWrite(espar, HIGH);
    digitalWrite(esparEnable, HIGH);
    esp_status = 1;      
  }
  //kill
  else if(heat_mode == '0'){
    digitalWrite(WP, HIGH);
    digitalWrite(fan, HIGH);
    digitalWrite(espar, HIGH);
    digitalWrite(esparEnable, HIGH); 
    esp_status = 0;     
  }
  Serial.print("heat mode changed");
  Serial.println(esp_status);
  return esp_status;
}

void ser_tx(){
  Serial.print(ser_rpi);                    //print what was recieved
  Serial.print(sensors.getTempFByIndex(0)); //send temps 
}

void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  cabin_temp = sensors.getTempFByIndex(0);  
  //check serial input
  if(Serial.available() > 0){
    ser_rpi = Serial.readString();
    heat_status = heat_cycle(ser_rpi[0]);}
  
  
  Serial.println(cabin_temp);
}
  /* ((((dubugging serial))) else{
    Serial.println("no input");
  }*/
