
// Communication vers ESP32 // 

/*esp sur serial1 TX19 RX18
serial1
*/

String inputString ="";
String resultFromArd[3];

struct mesureToSend{
  char* light_mesure;
  String pressure_mesure;
  int temp_mesure;
  int hum_mesure;
  String wind_mesure;
  String girouette_mesure;
  float part_03_mesure;
  float part_10_mesure;
  float part_50_mesure;
  float rad_mesure;
};
struct mesureToSend dataToSend;


// Lumiere //
#define LDR A3 // composante photorésistance sur la pin A0
int lightValue;

// Temperature // 
#include <DHT.h>
DHT dht(4, DHT11);

// Qualité de l'air //
/*Serial2
  Serial2 tx16 rx17
*/

// Radiation // 2 et 3
#include <RadiationWatch.h>
RadiationWatch radiationWatch;


void setup() {
   Serial.begin(9600);
   Serial1.begin(4800);
   Serial3.begin(4800);
   
   // Lumiere //
   pinMode(LDR, INPUT);
   
   // Temperature //
   dht.begin();

   // Qualité de l'air //
   Serial2.begin(9600);
   

   // Radiation //
   radiationWatch.setup();
   radiationWatch.registerRadiationCallback(&onRadiation);
   radiationWatch.registerNoiseCallback(&onNoise);
}

void loop() {
  radiationWatch.loop();
  readData();
  
 // Favoriser une structure pour le stockage des mesures au lieu d'une liste
  collect_data();
  sendAllData();
}
// ########################################## //
void collect_data(){ // stores all the collected data in the dataToSend structure
  dataToSend.light_mesure = light();
  dataToSend.pressure_mesure = resultFromArd[0];
  dataToSend.temp_mesure = temperature();
  dataToSend.hum_mesure = humidity();
  dataToSend.wind_mesure = resultFromArd[1];
  dataToSend.girouette_mesure = resultFromArd[2];
  qualite_air();
  dataToSend.rad_mesure = radiationWatch.uSvh();
 
  
}

// ########################################## //
char* light(){
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
int temperature(){
  float t = dht.readTemperature();
  return t;
}
// ######################################### //
int humidity(){
  float h = dht.readHumidity();
  return h;
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
 
   /*//debugging
  for (uint8_t i=2; i<32; i++) {
    Serial.print("0x"); Serial.print(buffer[i], HEX); Serial.print(", ");
  }
  Serial.println();
  */
  
  // The data comes in endian'd, this solves it so it works on all platforms
  uint16_t buffer_u16[15];
  for (uint8_t i=0; i<15; i++) {
    buffer_u16[i] = buffer[2 + i*2 + 1];
    buffer_u16[i] += (buffer[2 + i*2] << 8);
  }
 
  // put it into a nice struct :)
  memcpy((void *)&data, (void *)buffer_u16, 30);
 
  if (sum != data.checksum) {
    Serial.println("Checksum failure$$$$$$$$$$");
    data.checksum = 0;
    sum =0;
    return false;
  }
  // success!
  return true;
}

// ########################################### //
void qualite_air() {

  if (readPMSdata(&Serial2)) {
    // reading data was successful!
    dataToSend.part_03_mesure = data.particles_03um;
    dataToSend.part_10_mesure = data.particles_10um;
    dataToSend.part_50_mesure = data.particles_50um;
  }
}

// ########################################### // 

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

// #####################################
void sendAllData(){
  Serial1.print(dataToSend.light_mesure);Serial1.print('$');Serial1.print(0);Serial.print("---SENT---> ");Serial.println(dataToSend.light_mesure);
  Serial1.print(dataToSend.pressure_mesure);Serial1.print('$');Serial1.print(1);Serial.print("---SENT---> ");Serial.println(dataToSend.pressure_mesure);
  Serial1.print(dataToSend.temp_mesure);Serial1.print('$');Serial1.print(2);Serial.print("---SENT---> ");Serial.println(dataToSend.temp_mesure);
  Serial1.print(dataToSend.hum_mesure);Serial1.print('$');Serial1.print(3);Serial.print("---SENT---> ");Serial.println(dataToSend.hum_mesure);
  Serial1.print(dataToSend.wind_mesure);Serial1.print('$');Serial1.print(4);Serial.print("---SENT---> ");Serial.println(dataToSend.wind_mesure);
  Serial1.print(dataToSend.girouette_mesure);Serial1.print('$');Serial1.print(5);Serial.print("---SENT---> ");Serial.println(dataToSend.girouette_mesure);
  Serial1.print(dataToSend.part_03_mesure);Serial1.print('$');Serial1.print(6);Serial.print("---SENT---> ");Serial.println(dataToSend.part_03_mesure);
  Serial1.print(dataToSend.part_10_mesure);Serial1.print('$');Serial1.print(7);Serial.print("---SENT---> ");Serial.println(dataToSend.part_10_mesure);
  Serial1.print(dataToSend.part_50_mesure);Serial1.print('$');Serial1.print(8);Serial.print("---SENT---> ");Serial.println(dataToSend.part_50_mesure);
  Serial1.print(dataToSend.rad_mesure);Serial1.print('$');Serial1.print(9);Serial.print("---SENT---> ");Serial.println(dataToSend.rad_mesure);
  Serial.println("###############");
}
// #######################################
void readData() {
  while (Serial3.available()) {
    char inChar = (char)Serial3.read();
    if (inChar != '$') {
      inputString += inChar;
    }
    else{ // if  == $
      char indice = Serial3.read(); // on recolte l'indice de l'info
      int e = indice - '0'; //  technique illegale pour convertir un caractere en entier
      resultFromArd[e] = inputString; // on ajoute la données dans le tableau resultat
      inputString = ""; // on vide la chaine
      }
  }
}
