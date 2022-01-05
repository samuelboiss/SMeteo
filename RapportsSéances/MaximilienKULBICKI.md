
# Rapports de séance

## Séance du 01/12 

### Tâches effectuées : 

Lors de cette séance, nous avons fait l’étude du capteur DHT11 (température et humidité) et l’avons mis en marche.
Des tests ont été menés et les résultats obtenus paraissent cohérents. 

Nous avons poursuivi avec le même travail pour le module BMP180 (pression et température). Nous avons dû soudre les pins au module.
Les tests menés ont été satisfaisants. 


### Travail personnel :
-	Recherche sur le fonctionnement du module DHT11 (principe de la thermistance et capteur d’humidité capacitif) et étude de la bibliothèque « DHT Sensor » pour en dégager les fonctions utiles (readHumidity et readTemperature).
-	Soudure de pins sur le module BMP180.
-	Recherche sur le fonctionnement du module BMP180 et étude de la bibliothèque « SFE_BMP180 » pour obtenir les fonctions utiles (startTemp, getTemp, startPressure, getPressure).


## Séance du 15/12 :
### Tâches effectuées :

Lors de cette séance nous avons récupérer l’anémomètre d’un précédent projet (celui de Victor Girard et Benjamin Ferrer) que nous avons démonter pour en connaitre les composants et le fonctionnement. Nos tentatives de mise en marche de l’anémomètre n’étant pas fructueuses, nous l’avons mis de côté et avons débuté l’étude du capteur de luminosité LDR.

Nous avons fait l’étude du capteur LDR (luminosité) et l’avons mis en marche. 
Nous avons mené nos tests dans différentes conditions (plein soleil, ombre, salle de classe) et sommes satisfaits des résultats obtenus. Nous avons à présent pour but de convertir les mesures du capteur en lumens.


### Travail personnel :
-	Recherche sur la Base Shield V2.1 utilisée dans l’anémomètre, permettant de faire le raccord entre la girouette/ anémomètre (utilisant un câble RJ11) et l’arduino via des câbles JST 4P.
-	Etude du code de l’anémomètre pour en comprendre le fonctionnement. L’anémomètre fonctionne grâce à 2 fonctions (meassure() pour la vitesse du vent et  girouette()) créées par les auteurs du projet.
-	Recherche sur la fonction attachInterrupt utilisée pour compter les tours de l’anémomètre. 
-	Recherche sur le module LDR et écriture du code permettant de récupérer une tension variant selon la luminosité de la pièce. 
-	Les tests retournent une valeur (analogique) aux alentours de 900 à l’ombre, 400 en salle de classe et 50 en plein jour.

### Objectifs pour la prochaine séance :

-	Finir la conversion des mesures du capteur LDR en lumens.
-	Adapter le code de l’anémomètre pour nos besoins.

## Séance du 05/01 :
### Tâches effectuées :

Au cours de cette séance, je me suis repenché sur l’anémomètre (de Victor Girard et Benjamin Ferrer) que nous avions mis de côté lors de la dernière séance. 

La documentation de ce projet m’a fait comprendre l’ensemble du montage du boitier et le code utilisé dans l’anémomètre/ girouette. J’ai ainsi repris et modifié ce code afin de le faire fonctionner dans notre projet (suppression de code inutile et adaptation des I/O utilisées). Lors des tests de l’appareil, l’anémomètre renvoie des valeurs (vitesses) satisfaisantes.

Cependant, la girouette était complètement déréglée et renvoyait des directions qui ne collaient pas avec celles de la boussole de mon téléphone. Puisque la girouette renvoie un signal analogique (0-1023) selon sa direction, j’ai arrangé les plages de valeurs pour que la direction de la girouette corresponde à celle de la boussole en orientant initialement l’anémomètre plein ouest.

Une fois l’anémomètre opérationnel, j’ai repris l’étude du capteur LDR et mené des recherches afin de convertir les valeurs renvoyées par celui-ci en lumens. Il s’est avéré qu’établir une échelle en lumens était trop complexe car cela demande d’avoir à disposition différentes sources de lumières dont on connait le flux lumineux et en déduire une relation avec les valeurs du capteur. On se contentera donc d’une échelle « simple » situant la valeur de notre capteur entre « Plein ciel »/ « Ciel nuageux »/ « Ciel obscurci »/ « Nuit ».


