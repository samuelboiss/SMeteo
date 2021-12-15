#define LDR A0 // composante photorésistance sur la pin A0

int value;
 
void setup() {
   // initialise la communication avec le PC
   Serial.begin(9600);

   // initialise les broches
   pinMode(LDR, INPUT);
}
 
void loop() {
   // mesure la tension sur la broche A0
   value = analogRead(LDR);
   Serial.println(value);

   delay(100);
}
