
//------------- Output Pin Definitions ----------------//

int RegularLightsPin1= 3;
int RegularLightsPin2= 11;
int HalogenLightsPin1= 4;
int HalogenLightsPin2= 12;
int WaterPumpPin= 5;
int AirFanPin= 6;
int SurvoMotorPin= 7;

//------------- Input Pin Dinitions ------------//

int LightSensore= A0;
int WaterSensore=A1;
int HeatSensore= 2;

//-------------------------
#include <LiquidCrystal.h>
#include "DHT.h"

//#define DHTPIN 2         
#define DHTTYPE DHT11
DHT dht(HeatSensore, DHTTYPE);

//---------------------------------
char incoming_values;
//-------------- Flages ----------------//
int PumpFlag=0;
int FanFlag=0;
int HalLightFlag=0;
int RegLightFlag=0;

void setup() {
  // put your setup code here, to run once:
  
  initHumidity();
  initPump();
  initFan();
  setupWaterSensore();
  setupHaloginLights();
  setupRegularLight();
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
 
  
  loopPumpControl(loopWaterSensore());
  loopFanControl(loophumidityControlFan());
  
  loopHaloginLights(loophumidityControlHalogenLights());
  loopRegularLight();
 // delay(800);
  
}
//--------------------------- Humidity Sensore ---------------------------------------//
void initHumidity()
{
  Serial.begin(9600);
  dht.begin();
}

int loophumidityControlFan()
{
   //delay(2000); // Wait a few seconds between measurements
  // float humi = dht.readHumidity();
   // Reading temperature or humidity takes about 250 milliseconds!
   float temp = dht.readTemperature();
   // Read temperature as Celsius (the default)
   //float f = dht.readTemperature(true);
   // Read temperature as Fahrenheit (isFahrenheit = true)
   // Check if any reads failed and exit early (to try again).
   if (isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return 0;
   }
   
   // Compute heat index in Fahrenheit (the default)
  // float hif = dht.computeHeatIndex(f, h);
   // Compute heat index in Celsius (isFahreheit = false)
//   float hic = dht.computeHeatIndex(temp, humi, false);
   Serial.print ("Temperature: ");
   Serial.print (temp);
   Serial.print (" C\n");
   //if humid goes above 60% fan will turn on
   if(temp > 30)
   {
    return 1;
   }
   else
   {
    return 0;
   }
}

int loophumidityControlHalogenLights()
{
   //delay(2000); // Wait a few seconds between measurements
  // float humi = dht.readHumidity();
   // Reading temperature or humidity takes about 250 milliseconds!
   float temp = dht.readTemperature();
   // Read temperature as Celsius (the default)
   //float f = dht.readTemperature(true);
   // Read temperature as Fahrenheit (isFahrenheit = true)
   // Check if any reads failed and exit early (to try again).
   if (isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return 0;
   }
   
   // Compute heat index in Fahrenheit (the default)
  // float hif = dht.computeHeatIndex(f, h);
   // Compute heat index in Celsius (isFahreheit = false)
//   float hic = dht.computeHeatIndex(temp, humi, false);
   Serial.print ("Temperature: ");
   Serial.print (temp);
   Serial.print (" C\n");
   //if humid goes above 60% fan will turn on
   if(temp < 30)
   {
    return 1;
   }
   else
   {
    return 0;
   }
}

//------------------------------ Water Pump ---------------------------------------------------//
void initPump()
{
  pinMode(WaterPumpPin, OUTPUT);
}

void loopPumpControl(int i)
{
  digitalWrite(WaterPumpPin, LOW);
  
  if(i == 1){
    digitalWrite(WaterPumpPin, HIGH);// if pusheed is equal LOW, turn the pin 10 HIGH (give it 5v)
  }else{
    digitalWrite(WaterPumpPin, LOW);// else set pin 10 to low or zero volt
  }
}
//-------------------------------- Air Fan -----------------------------------------------------//
void initFan()
{
  pinMode(AirFanPin, OUTPUT);// pin 12 output for relay 3
}

void loopFanControl(int flag)
{
  if(flag == 1){
    digitalWrite(AirFanPin, HIGH);// if pusheed is equal LOW, turn the pin 10 HIGH (give it 5v)
  }else{
    digitalWrite(AirFanPin, LOW);// else set pin 10 to low or zero volt
  }
   
}

//----------------------------- Water Sensore -------------------------------------------------//

void setupWaterSensore()
{
  Serial.begin(9600);
}

int loopWaterSensore()
{

  int val = analogRead(WaterSensore); // read input value

  Serial.print("Water Level: ");

  Serial.println(val);
  if(val<200){
    return 0;
  }
  else
  return 1;
}

//----------------------------------- Light System ----------------------------------------//
int analogValue = 0;
void setupRegularLight() {
  //Set pins to outputs
  pinMode(RegularLightsPin1, OUTPUT);
  pinMode(RegularLightsPin2, OUTPUT);
  Serial.begin(9600);
}

void loopRegularLight(){
  analogValue = analogRead(LightSensore);
  
    digitalWrite(RegularLightsPin1, LOW);
    digitalWrite(RegularLightsPin2, LOW);
  if(analogValue < 20){     
 
    digitalWrite(RegularLightsPin1, HIGH);
    digitalWrite(RegularLightsPin2, HIGH);
  }
  else{
  
    digitalWrite(RegularLightsPin1, LOW);
    digitalWrite(RegularLightsPin2, LOW);
  }
  Serial.println(analogValue);
 // delay(500);
  /*digitalWrite(regularLedPin1, LOW);
  digitalWrite(regularLedPin2, LOW);
  digitalWrite(halgoenLedPin1, LOW);
  digitalWrite(halgoenLedPin2, LOW);*/
}


//------------------------------------- Halgoen Light System ---------------------------------------//
void setupHaloginLights() {
  //Set pins to output
  pinMode(HalogenLightsPin1,OUTPUT);
  pinMode(HalogenLightsPin2,OUTPUT);
  Serial.begin(9600);
}

void loopHaloginLights(int i){
  if(i==1){     
 
    digitalWrite(HalogenLightsPin1, HIGH);
    digitalWrite(HalogenLightsPin2, HIGH);
  }
  else{
  
    digitalWrite(HalogenLightsPin1, LOW);
    digitalWrite(HalogenLightsPin2, LOW);
  }
 // delay(500);
  /*digitalWrite(halgoenLedPin1, LOW);
  digitalWrite(halgoenLedPin2, LOW);*/
}
