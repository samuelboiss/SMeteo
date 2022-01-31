
// Communication vers ESP32 // 
#include <SoftwareSerial.h> 

const int tx = 6;
const int rx = 7;
SoftwareSerial MySerial(rx,tx);

String mesureToSend[7]; // tableau qui contiendra les mesures
char text[20]; // servira pour la conversion entier -> string

// Pression //
#include <Wire.h>
#include <SFE_BMP180.h>

SFE_BMP180 pressure;
#define ALTITUDE 116.0

float pressureResult_float;
char pressResult_string[20];

// Lumiere //
#define LDR A3 // composante photorésistance sur la pin A0
int lightValue;

// Temperature // 
#include <DHT.h>
DHT dht(4, DHT11);
float tempResult_float;
char tempResult_string[20];

// Anemometre //
uint32_t delayMS;

// constant pour anemometre/ girouette 
const int m_time = 1;  
int wind_ct = 0;
float wind = 0.0;
unsigned long time = 0;


void setup() {
   Serial.begin(9600);
   MySerial.begin(4800);
   
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
  
  mesureToSend[0] = light(); // string
  mesureToSend[1] = convert(pression()); // converti pression_float en string
  //mesureToSend[1]=convert(1013);
  mesureToSend[2] = convert(temperature());
  mesureToSend[3] = convert(humidity());
  mesureToSend[4] = convert(meassure()); // vent
  //mesureToSend[4] = convert(20);
  mesureToSend[5] = girouette(); // orientation
  //mesureToSend[5] = "Ouest";

  for (int j=0;j<6;j++){
    sendData(mesureToSend[j]);
  }
  waiting();
  
  //girouette();
  //meassure();
  delay(1000);

}
// ########################################## //
String light(){
   lightValue = analogRead(LDR);
   
   if (lightValue <= 150){
    return "Plein jour ";
   }
   else if(lightValue > 150 & lightValue <= 400){
    return "Ciel nuageux";
   }
   else if(lightValue > 400 & lightValue <=700){
    return "Ciel obscurci ";
   }
   else{return "Nuit noire";}
}


// ########################################## //
double pression(){
   char status;
   double T,P,p0,a;
   Serial.println("deb press");
   status = pressure.startTemperature();
   Serial.println("fin press");
   
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
int temperature(){
  float t = dht.readTemperature();
  return t;
}
// ######################################### //
int humidity(){
  float h = dht.readHumidity();
  return h;
}
// ########################################## //
float meassure() {
  wind_ct = 0;
  time = millis();
  attachInterrupt(1, countWind, RISING);
  delay(1000 * m_time);
  detachInterrupt(1);
  wind = (float)wind_ct / (float)m_time * 2.4/3; // vitesse en km/h
  return wind/3.6;
}
//##########################################//
String girouette(){
  int sensorValue = analogRead(A1);
  
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
    return "NORD-OUEST ";//
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
void sendData(String msg){
  MySerial.println(msg);
  Serial.print("---SENT---> ");
  Serial.println(msg);
}

//###########################################
void waiting(){
  while(!MySerial.available()){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" ");
  Serial.println("Got a response");
}
//##########################################
String convert(int res){
  char convert[20];
  sprintf(convert, "%d",res);
  return convert;
}
// ##########################################
