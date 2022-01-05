#define LDR A0 // composante photorésistance sur la pin A0

int lightValue;
 
void setup() {
   Serial.begin(9600);
   pinMode(LDR, INPUT);
}

void loop() {
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

   delay(1000);
}
