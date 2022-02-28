
// Communication vers MEGA2560 // 
#include <SoftwareSerial.h> 
const int txSf = 12;
const int rxSf = 13;
SoftwareSerial MySerial(rxSf,txSf);

struct mesureToSend{
  double pressure_mesure;
  float wind_mesure;
  char* girouette_mesure;
};

struct mesureToSend dataToSend;

// Pression //
#include "Wire.h"
#include "SFE_BMP180.h"

SFE_BMP180 pressure;
#define ALTITUDE 116.0

// Anemometre //
uint32_t delayMS;

// constant pour anemometre/ girouette 
const int m_time = 1;  
int wind_ct = 0;
float wind = 0.0;
unsigned long time_1 = 0;

void setup() {
   Serial.begin(9600);
   MySerial.begin(4800);
   
   //Pression//
   pressure.begin();
   
   // Anemometre // 
   time_1 = millis();

}

void loop() {
  dataToSend.pressure_mesure = pression();
  dataToSend.wind_mesure = meassure();
  dataToSend.girouette_mesure = girouette();
  sendData();

}
// ########################################## //

// ########################################## //
double pression(){
   char status;
   double T,P,p0,a;
   status = pressure.startTemperature();
   
   if (status != 0){
      delay(status);
      status = pressure.getTemperature(T);
      //Serial.print("Pression: ");
      
      if (status != 0){
         status = pressure.startPressure(3);
         if (status != 0){
            delay(status);
            status = pressure.getPressure(P,T);
            if (status != 0){
               return P;
               //Serial.println(" mb");
           }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}

// ########################################## //
// ########################################## //
float meassure() {
  wind_ct = 0;
  time_1 = millis();
  attachInterrupt(1, countWind, RISING);
  delay(1000 * m_time);
  detachInterrupt(1);
  wind = (float)wind_ct / (float)m_time * 2.4/3; // vitesse en km/h
  return wind/3.6;
}
//##########################################//
char* girouette(){
  int sensorValue = analogRead(1);
  
  //Serial.print("La direction du vent : ");
  
  if(sensorValue>200 && sensorValue<300){
    return "EST " ;
  }
  else if(sensorValue>100 && sensorValue<200){
    return "NORD-EST ";//
  }
  else if(sensorValue>10 && sensorValue<100){
    return "NORD "; ///
  }
  else if(sensorValue>400 && sensorValue<500){
    return "NORD-OUEST";//
  }
  else if(sensorValue>750 && sensorValue<800){
    return "OUEST "; ///
  }
  else if(sensorValue>800 && sensorValue<900){
    return "SUD-OUEST";//
  }
  else if(sensorValue>900 && sensorValue<1023){
    return "SUD"; ///
  }
  else if(sensorValue>600 && sensorValue<700){
    return "SUD-EST ";
  }
}
// ############################################ //
void countWind() {
  wind_ct ++;
}

   
//############################################ //
void sendData(){
  MySerial.print(dataToSend.pressure_mesure);MySerial.print('$');MySerial.print(0);Serial.print("---SENT---> ");Serial.println(dataToSend.pressure_mesure);
  MySerial.print(dataToSend.wind_mesure);MySerial.print('$');MySerial.print(1);Serial.print("---SENT---> ");Serial.println(dataToSend.wind_mesure);
  MySerial.print(dataToSend.girouette_mesure);MySerial.print('$');MySerial.print(2);Serial.print("---SENT---> ");Serial.println(dataToSend.girouette_mesure);
  Serial.println("###############");
}
