#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
#define HEATER 3
#define COOLER 4

#define HEATER_TEMP_MIN 17
#define HEATER_TEMP_MAX 20

#define COOLER_TEMP_MIN 4
#define COOLER_TEMP_MAX 6
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 
void setup(void)
{

  Serial.begin(9600);
  
  pinMode(HEATER, OUTPUT);
  pinMode(COOLER, OUTPUT);
  
  digitalWrite(HEATER, LOW); 
  digitalWrite(COOLER, LOW); 

  
  // Start up the library
  sensors.begin();
}
 
String action;
float temp;
float delta = -13;

void loop(void)
{
  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0) + delta;
  
  if((temp >= HEATER_TEMP_MAX and action == "none") or (temp >= HEATER_TEMP_MIN and action == "cooling")) {
    action = "cooling";
    digitalWrite(COOLER, HIGH);
    digitalWrite(HEATER, LOW);
  } else if((temp <= COOLER_TEMP_MIN and action == "none") or (temp <= COOLER_TEMP_MAX and action == "heating")) {
    action = "heating";
    digitalWrite(HEATER, HIGH);
    digitalWrite(COOLER, LOW);
  } else {
    action = "none";
    digitalWrite(HEATER, LOW);
    digitalWrite(COOLER, LOW);
  }
  Serial.print("Temperature is: ");
  Serial.println(temp); 
  Serial.print("Action is: ");
  Serial.println(action); 
  delay(1500);

}
