 void setup() {
  Serial.begin(9600);
  
}

void loop() {
  girouette();
  delay(100);
}

void girouette(){
  int sensorValue = analogRead(A1);
  Serial.print("La direction du vent est :");
  if(sensorValue>200 && sensorValue<300){
    Serial.print("SUD " );
  }
  else if(sensorValue>100 && sensorValue<200){
    Serial.print("SUD-EST ");
  }
  else if(sensorValue>10 && sensorValue<100){
    Serial.print("EST ");
  }
  else if(sensorValue>400 && sensorValue<500){
    Serial.print("NORD EST ");
  }
  else if(sensorValue>750 && sensorValue<800){
    Serial.print("NORD ");
  }
  else if(sensorValue>800 && sensorValue<900){
    Serial.print("NORD-OUEST");
  }
  else if(sensorValue>900 && sensorValue<1023){
    Serial.print("OUEST");
  }
  else if(sensorValue>600 && sensorValue<700){
    Serial.print("SUD-OUEST ");
  }
}
