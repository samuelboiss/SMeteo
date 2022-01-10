// Pression //
#include "Wire.h"
#include "SFE_BMP180.h"

SFE_BMP180 pressure;
#define ALTITUDE 116.0

// Lumiere //
#define LDR A3 // composante photorésistance sur la pin A0
int lightValue;

// Temperature // 
#include <DHT.h>
DHT dht(4, DHT11);

// Anemometre //
uint32_t delayMS;

// constant pour anemometre/ girouette 
const int m_time = 1;  
int wind_ct = 0;
float wind = 0.0;
unsigned long time = 0;


void setup() {
   Serial.begin(9600);
   
   //Pression//
   pressure.begin();
   
   // Lumiere //
   pinMode(LDR, INPUT);
   
   // Temperature //
   dht.begin();

   // Anemometre // 
   time = millis();

}

void loop() {
  light();
  pression();
  temperature();
  girouette();
  meassure();
  Serial.println();
  delay(1000);

}
// ########################################## //
void light(){
   lightValue = analogRead(LDR);
   
   if (lightValue <= 150){
    Serial.println("Plein jour ");
   }
   
   else if(lightValue > 150 & lightValue <= 400){
    Serial.println("Ciel nuageux ");
   }
   else if(lightValue > 400 & lightValue <=700){
    Serial.println("Ciel obscurci ");
   }

   else{Serial.println("Nuit noire");}
}


// ########################################## //
void pression(){
   char status;
   double T,P,p0,a;
  
   status = pressure.startTemperature();
   if (status != 0){
      delay(status);

      status = pressure.getTemperature(T);
      Serial.print("Pression: ");
      
      if (status != 0){
         status = pressure.startPressure(3);
         if (status != 0){
            delay(status);
            status = pressure.getPressure(P,T);
            if (status != 0){
               Serial.print(P,2);
               Serial.println(" mb");
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
void temperature(){
   float h = dht.readHumidity();
   float t = dht.readTemperature();

   Serial.print("Humidité: ");
    Serial.print(h);
    Serial.println(" %");
   Serial.print("Temperature: ");
   Serial.print(t);
   Serial.println(" C°");
  
}
// ########################################## //
void meassure() {
  wind_ct = 0;
  time = millis();
  attachInterrupt(1, countWind, RISING);
  delay(1000 * m_time);
  detachInterrupt(1);
  wind = (float)wind_ct / (float)m_time * 2.4/3;
  Serial.print("VITESSE DU VENT ");
  Serial.print(wind);       //Speed in Km/h
  Serial.print(" km/h - ");
  Serial.print(wind / 3.6); //Speed in m/s
  Serial.println(" m/s");
}

void girouette(){
  int vent=0;
  int sensorValue = analogRead(A1);
  
  
  Serial.print("La direction du vent : ");
  
  if(sensorValue>200 && sensorValue<300){
    Serial.println("EST " );
    vent=1;
  }
  else if(sensorValue>100 && sensorValue<200){
    Serial.println("NORD-EST ");//
    vent=2;
  }
  else if(sensorValue>10 && sensorValue<100){
    Serial.println("NORD "); ///
    vent=3;
  }
  else if(sensorValue>400 && sensorValue<500){
    Serial.println("NORD-OUEST ");//
    vent=4;
  }
  else if(sensorValue>750 && sensorValue<800){
    Serial.println("OUEST "); ///
    vent=5;
  }
  else if(sensorValue>800 && sensorValue<900){
    Serial.println("SUD-OUEST");//
    vent=6;
  }
  else if(sensorValue>900 && sensorValue<1023){
    Serial.println("SUD"); ///
    vent=7;
  }
  else if(sensorValue>600 && sensorValue<700){
    Serial.println("SUD-EST ");
    vent=8;
  }
}

void countWind() {
  wind_ct ++;
}
