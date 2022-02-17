
// Communication vers ESP32 // 
#include <SoftwareSerial.h> 
const int txSf = 12;
const int rxSf = 13;
SoftwareSerial MySerial(rxSf,txSf);

String mesureToSend[10]; // tableau qui contiendra les mesures
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
unsigned long time_1 = 0;

// Qualité de l'air //
SoftwareSerial pmsSerial(8, 9); // 2,3

// Radiation // 10 et 11
#include <RadiationWatch.h>
RadiationWatch radiationWatch;
String rad_texte;

void setup() {
   Serial.begin(9600);
   MySerial.begin(4800);
   
   //Pression//
   //pressure.begin();
   
   // Lumiere //
   pinMode(LDR, INPUT);
   
   // Temperature //
   dht.begin();

   // Anemometre // 
   time_1 = millis();

   // Qualité de l'air //
   pmsSerial.begin(9600);

   // Radiation //
  // radiationWatch.setup();
   //radiationWatch.registerRadiationCallback(&onRadiation);
   //radiationWatch.registerNoiseCallback(&onNoise);

}

void loop() {
  //radiationWatch.loop();

  //mesureToSend[0] = "Plein_jou"; // au delà de 9 caracteres, le site n'affiche plus la chaine
  mesureToSend[0] = light(); // string
  //mesureToSend[1] = convert(pression()); // converti pression_float en string
  mesureToSend[1]=convert(1013);
  mesureToSend[2] = convert(temperature());
  mesureToSend[3] = convert(humidity());
  //mesureToSend[4] = convert(meassure()); // vent
  mesureToSend[4] = convert(20);
  //mesureToSend[5] = girouette(); // orientation
  mesureToSend[5] = "Ouest";
  //mesureToSend[6] = qualite_air();
  mesureToSend[6] = "bien";
  //mesureToSend[7] = radiationString();
  mesureToSend[7] = "beaucoup";

  sendList(); // on envoie toute la liste de mesures dans le buffer
  
  Serial.println("###############");
  delay(1000);


}
// ########################################## //
String light(){
   lightValue = analogRead(LDR);
   
   if (lightValue <= 150){
    return "Jour";
   }
   else if(lightValue > 150 & lightValue <= 400){
    return "Nuageux";
   }
   else if(lightValue > 400 & lightValue <=700){
    return "Obscurci";
   }
   else{return "Nuit";}
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
  time_1 = millis();
  attachInterrupt(1, countWind, RISING);
  delay(1000 * m_time);
  detachInterrupt(1);
  wind = (float)wind_ct / (float)m_time * 2.4/3; // vitesse en km/h
  return wind/3.6;
}
//##########################################//
String girouette(){
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

// ########################################### // qualité air 
struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};
 
struct pms5003data data;

// ########################################### // qualité air
boolean readPMSdata(Stream *s) {
  if (! s->available()) {
    return false;
  }
  
  // Read a byte at a time until we get to the special '0x42' start-byte
  if (s->peek() != 0x42) {
    s->read();
    return false;
  }
 
  // Now read all 32 bytes
  if (s->available() < 32) {
    return false;
  }
    
  uint8_t buffer[32];    
  uint16_t sum = 0;
  s->readBytes(buffer, 32);
 
  // get checksum ready
  for (uint8_t i=0; i<30; i++) {
    sum += buffer[i];
  }
  
  // The data comes in endian'd, this solves it so it works on all platforms
  uint16_t buffer_u16[15];
  for (uint8_t i=0; i<15; i++) {
    buffer_u16[i] = buffer[2 + i*2 + 1];
    buffer_u16[i] += (buffer[2 + i*2] << 8);
  }
 
  // put it into a nice struct :)
  memcpy((void *)&data, (void *)buffer_u16, 30);
 
  if (sum != data.checksum) {
    Serial.println("Checksum failure");
    return false;
  }
  // success!
  return true;
}

// ########################################### //
String qualite_air () {

  String res="";
  if (readPMSdata(&pmsSerial)) {
    // reading data was successful!
    res+="---------------------------------------\n";
    res+="Concentration Units (standard)\n";
    res+="PM 1.0: "; res+=data.pm10_standard;res+="\n";
    res+="\t\tPM 2.5: "; res+=data.pm25_standard;res+="\n";
    res+="\t\tPM 10: "; res+=data.pm100_standard;res+="\n";
    res+="---------------------------------------\n";
    res+="Concentration Units (environmental)\n";
    res+="PM 1.0: "; res+=data.pm10_env;res+="\n";
    res+="\t\tPM 2.5: "; res+=data.pm25_env;res+="\n";
    res+="\t\tPM 10: "; res+=data.pm100_env;res+="\n";
    res+="---------------------------------------\n";
    res+="Particles > 0.3um / 0.1L air:"; res+=data.particles_03um;res+="\n";
    res+="Particles > 0.5um / 0.1L air:"; res+=data.particles_05um;res+="\n";
    res+="Particles > 1.0um / 0.1L air:"; res+=data.particles_10um;res+="\n";
    res+="Particles > 2.5um / 0.1L air:"; res+=data.particles_25um;res+="\n";
    res+="Particles > 5.0um / 0.1L air:"; res+=data.particles_50um;res+="\n";
    res+="Particles > 10.0 um / 0.1L air:"; res+=data.particles_100um;res+="\n";
    res+="---------------------------------------\n";
  }
  return res;

}

// ########################################### // 
String radiationString () {
  if (radiationWatch.uSvh() > 0.20 or radiationWatch.uSvh() < 0.04) {
    rad_texte = radiationWatch.uSvh() + ' uSv/h +/- --> Be careful outside';
    return rad_texte;
  }
  else {
    rad_texte = radiationWatch.uSvh() + ' uSv/h +/- --> Everything OK';
    return rad_texte;
  }
}

//############################################ //
void onNoise()
{
  Serial.println("Argh, noise, please stop moving");
}
// ########################################### //
void onRadiation()
{
  Serial.println("A wild gamma ray appeared");
  Serial.print(radiationWatch.uSvh());
  Serial.print(" uSv/h +/- ");
  Serial.println(radiationWatch.uSvhError());
}
   
//############################################ //
void sendData(String msg, int e){
  MySerial.print(msg);
  MySerial.print('$');
  MySerial.print(e);
  Serial.print("---SENT---> ");
  Serial.println(msg);
}

//###########################################

//##########################################
String convert(int res){
  char convert[20];
  sprintf(convert, "%d",res);
  return convert;
}
// ##########################################

void sendList(){
    for (int j=0;j<10;j++){
    sendData(mesureToSend[j],j);
  }
}
