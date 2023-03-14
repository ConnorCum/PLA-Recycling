// Include sensor libraries
#include <Adafruit_MAX31856.h> 
#include <Adafruit_MLX90614.h>

// Set up thermocouple
Adafruit_MAX31856 maxthermotc1 = Adafruit_MAX31856(10,11,12,13);
Adafruit_MAX31856 maxthermotc2 = Adafruit_MAX31856(9,11,12,13);
Adafruit_MAX31856 maxthermotc3 = Adafruit_MAX31856(8,11,12,13);
Adafruit_MLX90614 fans = Adafruit_MLX90614();

// Define pins for relays
#define RELAY_1_PIN 2
#define RELAY_2_PIN 6
#define RELAY_3_PIN 7
#define FAN_PIN 5

// #define MC_in1 6
// #define MC_in2 7

// Motor B connections
int enB = 3; //3
int in3 = 5; //5
int in4 = 4; //4

//Desired temps
int desired_temp1 = 100;
int desired_temp2 = 100;
int desired_temp3 = 100;
int desired_tempF = 20;

// Initialize variables for timing
unsigned long one_sec = 1000;
unsigned long relay1StartTime = 0;
unsigned long relay2StartTime = 0;
unsigned long relay3StartTime = 0;
const int minDelay = 500;
const int maxDelay = 1000;

int Heat1 = 10;
int Heat2 = 10;
int Heat3 = 10;
int HeatF = 10;

bool heat_on_1 = false;
bool heat_on_2 = false;
bool heat_on_3 = false;

float tempMid1;
float tempMid2;
float tempMid3;
float tempMidF;

float current_percent1 = 0.5;
float current_percent2 = 0.5;
float current_percent3 = 0.5;
float current_percentF = 0.5;

float increment1 = 0.0005;
float increment2 = 0.0005;
float increment3 = 0.0005;
float incrementF = 0.0005;
//float time_on_1 = 1;

// Start check


void setup() {
  Serial.begin(9600);

  // Set relay pins as outputs
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(RELAY_3_PIN, OUTPUT);
//Set Motor Controller pins as outputs
pinMode(enB, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);

// Set up Thermocouple settings:
//Thermocouple 1
maxthermotc1.begin();
maxthermotc1.setThermocoupleType(MAX31856_TCTYPE_K);
maxthermotc1.setConversionMode(MAX31856_ONESHOT_NOWAIT);

//Thermocouple 2
maxthermotc2.begin();
maxthermotc2.setThermocoupleType(MAX31856_TCTYPE_K);
maxthermotc2.setConversionMode(MAX31856_ONESHOT_NOWAIT);

//Thermocouple 3
maxthermotc3.begin();
maxthermotc3.setThermocoupleType(MAX31856_TCTYPE_K);
maxthermotc3.setConversionMode(MAX31856_ONESHOT_NOWAIT);

//Fans
fans.begin();


//Thermocouple start checks
if (!maxthermotc1.begin()) {
Serial.println("Could not initialize thermocouple.");
while (1) delay(10);
}

if (!maxthermotc2.begin()) {
Serial.println("Could not initialize thermocouple.");
while (1) delay(10);
}

if (!maxthermotc3.begin()) {
Serial.println("Could not initialize thermocouple.");
while (1) delay(10);
}
}

void loop() {

//Current time setup
unsigned long currentMillis = millis();

//Thermocouple 1 setup:
   maxthermotc1.triggerOneShot();
  // Take temperature; assign to tempMid float
  tempMid1 = maxthermotc1.readThermocoupleTemperature();

  // if Temperature is between +- 1 degree of desired:
  if (desired_temp1 -1 < tempMid1 && tempMid1 < desired_temp1 +1){
  // Do not do anything. Temperature is in a happy range.
  }
 
 // if Temperature is above this range:
  else if (tempMid1 > desired_temp1 && Heat1 <= 250){
    // if temp is greater than 10 degrees away, move 20% down.
    if (tempMid1 > desired_temp1 + 10) {increment1 = 4;}
    else {increment1 = 1;} // Otherwise move 5% down.

    current_percent1 += -increment1;

    // Move Temperature Stepper
    Heat1 += -5*increment1;
  }

  else if (tempMid1 < desired_temp1 && Heat1 >= 0){
    // if temp is greater than 10 degrees away, move 20% up.
    if (tempMid1 < desired_temp1 - 10) {increment1 = 4;}
    else {increment1 = 1;} // Otherwise move 5% down.
    current_percent1 += increment1;
    Heat1 += 5*increment1;
  }
  //Limits on the Heat ammount so it doesnt run over
 if (Heat1 <= 0) {Heat1 = 0;}
 if (Heat1 >= 250) {Heat1 = 250;}

 float time_off_1 = (Heat1 * 0.00392157) * one_sec; // 1/255
 float time_on_1 = one_sec - time_off_1;
  Serial.println(Heat1);
  Serial.println("------------");
  Serial.println("Heat1");
  Serial.println(time_on_1);
  Serial.println(tempMid1);


  // Check if it's time to turn off relay 1
  if (currentMillis - relay1StartTime >= time_on_1 && heat_on_1 == false) {
    digitalWrite(RELAY_1_PIN, LOW);
    relay1StartTime = currentMillis;
    heat_on_1 = true;
  }

  // Check if it's time to turn on relay 1
  if (currentMillis - relay1StartTime >= time_off_1 && heat_on_1 == true) {
    digitalWrite(RELAY_1_PIN, HIGH);
    relay1StartTime = currentMillis;
    heat_on_1 = false;


//create flowchart to keep track of what is going 
// if starting a job but current millis is already at a time
//when a button is hit reset millis to zero
// can you reset the millis counter
//get ceramic tubing
//put it in a box for safety
//Ceramic insulators over plywood

  }

// /////////////////////////////////////////////////////////
//Thermocouple 2 setup:
   maxthermotc2.triggerOneShot();
  // Take temperature; assign to tempMid float
  tempMid2 = maxthermotc2.readThermocoupleTemperature();

  // if Temperature is between +- 1 degree of desired:
  if (desired_temp2 -1 < tempMid2 && tempMid2 < desired_temp2 +1){
  // Do not do anything. Temperature is in a happy range.
  }
 
 // if Temperature is above this range:
  else if (tempMid2 > desired_temp2 && Heat2 <= 250){
    // if temp is greater than 10 degrees away, move 20% down.
    if (tempMid2 > desired_temp2 + 10) {increment2 = 4;}
    else {increment2 = 1;} // Otherwise move 5% down.

    current_percent2 += -increment2;

    // Move Temperature Stepper
    Heat2 += -5*increment2;
  }

  else if (tempMid2 < desired_temp2 && Heat2 >= 0){
    // if temp is greater than 10 degrees away, move 20% up.
    if (tempMid2 < desired_temp2 - 10) {increment2 = 4;}
    else {increment2 = 1;} // Otherwise move 5% down.
    current_percent2 += increment2;
    Heat2 += 5*increment2;
  }
 if (Heat2 <= 0) {Heat2 = 0;}
 if (Heat2 >= 250) {Heat2 = 250;}

 float time_off_2 = (Heat2 * 0.00392157) * one_sec; 
 float time_on_2 = one_sec - time_off_2;
  // Serial.println(Heat);
  Serial.println("------------");
  Serial.println("Heat2");
  Serial.println(time_on_2);
  Serial.println(tempMid2);


  // Check if it's time to turn off relay 2
  if (currentMillis - relay2StartTime >= time_on_2 && heat_on_2 == false) {
  // if (relay1StartTime != 0 && currentMillis - relay1StartTime >= random(minDelay, maxDelay)) {
    //  if (relay1StartTime != 0) {
    // Serial.println("it worked lol");
    digitalWrite(RELAY_2_PIN, LOW);
    relay2StartTime = currentMillis;
    heat_on_2 = true;
    // Serial.println("Check1");
  }

  // Check if it's time to turn on relay 2
  if (currentMillis - relay2StartTime >= time_off_2 && heat_on_2 == true) {
    digitalWrite(RELAY_2_PIN, HIGH);
    relay2StartTime = currentMillis;
  //  Serial.println(currentMillis - relay1StartTime);
    heat_on_2 = false;

  }

///////////////////////////////////////////////////////////////////////////////
//Thermocouple 3 setup:
   maxthermotc3.triggerOneShot();
  // Take temperature; assign to tempMid float
  tempMid3 = maxthermotc3.readThermocoupleTemperature();

  // if Temperature is between +- 1 degree of desired:
  if (desired_temp3 -1 < tempMid3 && tempMid3 < desired_temp3 +1){
  // Do not do anything. Temperature is in a happy range.
  }
 
 // if Temperature is above this range:
  else if (tempMid3 > desired_temp3 && Heat3 <= 250){
    // if temp is greater than 10 degrees away, move 20% down.
    if (tempMid3 > desired_temp3 + 10) {increment3 = 4;}
    else {increment3 = 1;} // Otherwise move 5% down.

    current_percent3 += -increment3;

    // Move Temperature Stepper
    Heat3 += -5*increment3;
  }

  else if (tempMid3 < desired_temp3 && Heat3 >= 0){
    // if temp is greater than 10 degrees away, move 20% up.
    if (tempMid3 < desired_temp3 - 10) {increment3 = 4;}
    else {increment3 = 1;} // Otherwise move 5% down.
    current_percent3 += increment3;
    Heat3 += 5*increment3;
  }
 if (Heat3 <= 0) {Heat3 = 0;}
 if (Heat3 >= 250) {Heat3 = 250;}

 float time_off_3 = (Heat3 * 0.00392157) * one_sec; 
 float time_on_3 = one_sec - time_off_3;
  // Serial.println(Heat);
  Serial.println("------------");
  Serial.println("Heat3");
  Serial.println(time_on_3);
  Serial.println(tempMid3);


  // Check if it's time to turn off relay 1
  if (currentMillis - relay3StartTime >= time_on_3 && heat_on_3 == false) {
  // if (relay1StartTime != 0 && currentMillis - relay1StartTime >= random(minDelay, maxDelay)) {
    //  if (relay1StartTime != 0) {
    // Serial.println("it worked lol");
    digitalWrite(RELAY_3_PIN, LOW);
    relay3StartTime = currentMillis;
    heat_on_3 = true;
    // Serial.println("Check1");
  }

  // Check if it's time to turn on relay 1
  if (currentMillis - relay3StartTime >= time_off_3 && heat_on_3 == true) {
    digitalWrite(RELAY_3_PIN, HIGH);
    relay3StartTime = currentMillis;
  //  Serial.println(currentMillis - relay1StartTime);
    heat_on_3 = false;

  }
/////////////////////////////////////////////////////////////////////////////////
//Fan code

tempMidF = fans.readObjectTempC();

  // if Temperature is between +- 1 degree of desired:
  if (desired_tempF -1 < tempMidF && tempMidF < desired_tempF +1){
  // Do not do anything. Temperature is in a happy range.
  }
 
 // if Temperature is above this range:
  else if (tempMidF > desired_tempF && HeatF <= 250){
    // if temp is greater than 10 degrees away, move 20% down.
    if (tempMidF > desired_tempF + 10) {incrementF = 4;}
    else {incrementF = 1;} // Otherwise move 5% down.

    current_percentF += -incrementF;

    // Move Temperature Stepper
    HeatF += -5*incrementF;
  }

  else if (tempMidF < desired_tempF && HeatF >= 0){
    // if temp is greater than 10 degrees away, move 20% up.
    if (tempMidF < desired_tempF - 10) {incrementF = 4;}
    else {incrementF = 1;} // Otherwise move 5% down.
    current_percentF += incrementF;
    HeatF += 5*incrementF;
  }
 if (HeatF <= 0) {HeatF = 0;}
 if (HeatF >= 250) {HeatF = 250;}

  // analogWrite(FAN_PIN, HeatF);
// analogWrite(FAN_PIN, 200);

	analogWrite(enB, HeatF);

	// Now change motor directions
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);

//Print outs
Serial.println("------------");
Serial.println("Fan temp");
Serial.println(tempMidF);
Serial.println("Fan Heat");
Serial.println(HeatF);  







  ////////////////////////////////////////////////////////////////
  //Random testing
  // // Check if it's time to turn off relay 2
  // if (relay2StartTime != 0 && currentMillis - relay2StartTime >= random(minDelay, maxDelay)) {
  //   digitalWrite(RELAY_2_PIN, LOW);
  //   relay2StartTime = 0;
  // }

  // // Check if it's time to turn on relay 2
  // if (relay2StartTime == 0 && currentMillis - relay3StartTime >= minDelay) {
  //   digitalWrite(RELAY_2_PIN, HIGH);
  //   relay2StartTime = currentMillis;
  // }

  // // Check if it's time to turn off relay 3
  // if (relay3StartTime != 0 && currentMillis - relay3StartTime >= random(minDelay, maxDelay)) {
  //   digitalWrite(RELAY_3_PIN, LOW);
  //   relay3StartTime = 0;
  // }

  // // Check if it's time to turn on relay 3
  // if (relay3StartTime == 0 && currentMillis - relay2StartTime >= minDelay) {
  //   digitalWrite(RELAY_3_PIN, HIGH);
  //   relay3StartTime = currentMillis;
  // }
// Serial.println(heat_on_1);
}


