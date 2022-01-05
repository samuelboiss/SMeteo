
uint32_t delayMS;

// constant pour anemometre/ girouette 
const int m_time = 1;  
int wind_ct = 0;
float wind = 0.0;
unsigned long time = 0;

void setup() {
  Serial.begin(9600);
  time = millis();
}

void loop() {
  meassure();
  girouette();
  delay(1000);
  Serial.println("");
}

void countWind() {
  wind_ct ++;
}

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
  Serial.println(sensorValue);
  
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
