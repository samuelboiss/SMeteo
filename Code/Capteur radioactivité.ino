#include "RadiationWatch.h"
/*
This simple example tell you on serial each time a gamma radiation hits the
Pocket Geiger and print the current micro Sievert dose. It also notify you of
the presence of vibration that prevent proper measurements.
*/

RadiationWatch radiationWatch;

void onRadiation()
{
  Serial.print(radiationWatch.uSvh());
  Serial.print(" uSv/h +/- ");
  Serial.println(radiationWatch.uSvhError());
      if (radiationWatch.uSvh() > 0.20 or radiationWatch.uSvh() < 0.04){
    Serial.println("Be careful !");
  }
}

void onNoise()
{
  Serial.println("Stop moving");
}

String radiationString () {
  if (radiationWatch.uSvh() > 0.20 or radiationWatch.uSvh() < 0.04)
    return (radiationWatch.uSvh() + " uSv/h +/- " + " --> Be careful");
  else {
    return radiationWatch.uSvh() + " uSv/h +/- ";
  }
}

void setup()
{
  Serial.begin(9600);
  radiationWatch.setup();
  // Register the callbacks.
  radiationWatch.registerRadiationCallback(&onRadiation);
  radiationWatch.registerNoiseCallback(&onNoise);
}

void loop()
{
  radiationWatch.loop();
}
